import edu.princeton.cs.algs4.Picture;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.Stack;

import java.awt.Color;

public class SeamCarver {
    private Picture picture;

    // create a seam carver object based on the given picture
    public SeamCarver(Picture picture) {
        if (picture == null) {
            throw new IllegalArgumentException("picture is null");
        }
        this.picture = picture;
    }

    // current picture
    public Picture picture() {
        return picture;
    }

    // width of current picture
    public int width() {
        return picture.width();
    }

    // height of current picture
    public int height() {
        return picture.height();
    }

    // energy of pixel at column x and row y
    public double energy(int x, int y) {
        if (x < 0 || x >= width() || y < 0 || y >= height()) {
            throw new IllegalArgumentException("Either x or y is outside its prescribed range");
        }
        if (x == 0 || x == width() - 1 || y == 0 || y == height() - 1) {
            return 1000.0;
        }

        Color left = picture.get(x - 1, y);
        Color right = picture.get(x + 1, y);
        Color top = picture.get(x, y - 1);
        Color down = picture.get(x, y + 1);

        int redX = left.getRed() - right.getRed();
        int redY = top.getRed() - down.getRed();
        int greenX = left.getGreen() - right.getGreen();
        int greenY = top.getGreen() - down.getGreen();
        int blueX = left.getBlue() - right.getBlue();
        int blueY = top.getBlue() - down.getBlue();

        double squaredEnergy = 0.0;
        squaredEnergy += redX * redX + greenX * greenX + blueX * blueX;
        squaredEnergy += redY * redY + greenY * greenY + blueY * blueY;

        return Math.sqrt(squaredEnergy);
    }

    // sequence of indices for horizontal seam
    public int[] findHorizontalSeam() {
        double minDist = Double.POSITIVE_INFINITY;
        double[][] distTo = new double[width()][height()];
        int[][] edgeTo = new int[width()][height()];
        int[] seam = new int[width()];
        Queue<Integer> queue = new Queue<>();
        Stack<Integer> stack = new Stack<>();

        for (int src = 0; src < height(); ++src) { // source is (0, src)
            for (int i = 0; i < width(); ++i) {
                for (int j = 0; j < height(); ++j) {
                    distTo[i][j] = Double.POSITIVE_INFINITY;
                }
            }
            distTo[0][src] = 1000.0; // energy
            queue.enqueue(src);
            for (int x = 0; x < width() - 1; ++x) {
                int size = queue.size();
                for (int i = 0; i < size; ++i) {
                    int y = queue.dequeue(); // (x, y)
                    double temp;

                    if (y - 1 >= 0) { // (x, y) -> (x + 1, y - 1)
                        temp = distTo[x][y] + energy(x + 1, y - 1);
                        if (distTo[x + 1][y - 1] > temp) {
                            distTo[x + 1][y - 1] = temp;
                            edgeTo[x + 1][y - 1] = y;
                        }
                        queue.enqueue(y - 1);
                    }

                    if (y + 1 < height()) { // (x, y) -> (x + 1, y + 1)
                        temp = distTo[x][y] + energy(x + 1, y + 1);
                        if (distTo[x + 1][y + 1] > temp) {
                            distTo[x + 1][y + 1] = temp;
                            edgeTo[x + 1][y + 1] = y;
                        }
                        queue.enqueue(y + 1);
                    }

                    // (x, y) -> (x + 1, y)
                    temp = distTo[x][y] + energy(x + 1, y);
                    if (distTo[x + 1][y] > temp) {
                        distTo[x + 1][y] = temp;
                        edgeTo[x + 1][y] = y;
                    }
                    queue.enqueue(y);
                }
            }

            int minIdx = -1;
            while (!queue.isEmpty()) {
                int dst = queue.dequeue();
                if (distTo[width() - 1][dst] < minDist) {
                    minIdx = dst;
                    minDist = distTo[width() - 1][dst];
                }
            }

            if (minIdx > 0) {
                int y = minIdx;
                for (int x = width() - 1; x >= 0; --x) {
                    stack.push(y);
                    y = edgeTo[x][y];
                }

                int i = 0;
                while (!stack.isEmpty()) {
                    y = stack.pop();
                    seam[i] = y;
                    ++i;
                }
            }
        }

        return seam;
    }

    // sequence of indices for vertical seam
    public int[] findVerticalSeam() {
        double minDist = Double.POSITIVE_INFINITY;
        int[] seam = new int[height()];
        double[][] distTo = new double[width()][height()];
        int[][] edgeTo = new int[width()][height()];
        Queue<Integer> queue = new Queue<>();
        Stack<Integer> stack = new Stack<>();

        for (int src = 0; src < width(); ++src) { // source is (src, 0)
            for (int i = 0; i < width(); ++i) {
                for (int j = 0; j < height(); ++j) {
                    distTo[i][j] = Double.POSITIVE_INFINITY;
                }
            }
            distTo[src][0] = 1000.0; // energy
            queue.enqueue(src);
            for (int y = 0; y < height() - 1; ++y) {
                int size = queue.size();
                for (int i = 0; i < size; ++i) {
                    int x = queue.dequeue(); // (x, y)
                    double temp;

                    if (x - 1 >= 0) { // (x, y) -> (x - 1, y + 1)
                        temp = distTo[x][y] + energy(x - 1, y + 1);
                        if (distTo[x - 1][y + 1] > temp) {
                            distTo[x - 1][y + 1] = temp;
                            edgeTo[x - 1][y + 1] = x;
                        }
                        queue.enqueue(x - 1);
                    }

                    if (x + 1 < width()) { // (x, y) -> (x + 1, y + 1)
                        temp = distTo[x][y] + energy(x + 1, y + 1);
                        if (distTo[x + 1][y + 1] > temp) {
                            distTo[x + 1][y + 1] = temp;
                            edgeTo[x + 1][y + 1] = x;
                        }
                        queue.enqueue(x + 1);
                    }

                    // (x, y) -> (x, y + 1)
                    temp = distTo[x][y] + energy(x, y + 1);
                    if (distTo[x][y + 1] > temp) {
                        distTo[x][y + 1] = temp;
                        edgeTo[x][y + 1] = x;
                    }
                    queue.enqueue(x);
                }
            }

            int minIdx = -1;
            while (!queue.isEmpty()) { // (dst, height - 1)
                int dst = queue.dequeue();
                if (distTo[dst][height() - 1] < minDist) {
                    minIdx = dst;
                    minDist = distTo[dst][height() - 1];
                }
            }

            if (minIdx > 0) {
                int x = minIdx;
                for (int y = height() - 1; y >= 0; --y) {
                    stack.push(x);
                    x = edgeTo[x][y];
                }

                int i = 0;
                while (!stack.isEmpty()) {
                    x = stack.pop();
                    seam[i] = x;
                    ++i;
                }

            }
        }

        return seam;
    }

    // remove horizontal seam from current picture
    public void removeHorizontalSeam(int[] seam) {
        if (seam == null) {
            throw new IllegalArgumentException("seam is null");
        }
        if (height() <= 1) {
            throw new IllegalArgumentException("height <= 1");
        }
        int size = 0;
        for (int y : seam) {
            ++size;
            if (y < 0 || y >= height()) {
                throw new IllegalArgumentException("not a valid seam");
            }
        }
        if (size != width()) {
            throw new IllegalArgumentException("not a valid seam");
        }

        Picture newPicture = new Picture(width(), height() - 1);
        for (int x = 0; x < width(); ++x) {
            for (int y = 0; y < height() - 1; ++y) {
                if (y < seam[x]) {
                    newPicture.set(x, y, picture.get(x, y));
                } else {
                    newPicture.set(x, y, picture.get(x, y + 1));
                }
            }
        }
        picture = newPicture;
    }

    // remove vertical seam from current picture
    public void removeVerticalSeam(int[] seam) {
        if (seam == null) {
            throw new IllegalArgumentException("seam is null");
        }
        if (width() <= 1) {
            throw new IllegalArgumentException("width <= 1");
        }
        int size = 0;
        for (int x : seam) {
            ++size;
            if (x < 0 || x >= width()) {
                throw new IllegalArgumentException("not a valid seam");
            }
        }
        if (size != height()) {
            throw new IllegalArgumentException("not a valid seam");
        }

        Picture newPicture = new Picture(width() - 1, height());
        for (int y = 0; y < height(); ++y) {
            for (int x = 0; x < width() - 1; ++x) {
                if (x < seam[y]) {
                    newPicture.set(x, y, picture.get(x, y));
                } else {
                    newPicture.set(x, y, picture.get(x + 1, y));
                }
            }
        }
        picture = newPicture;
    }
}
