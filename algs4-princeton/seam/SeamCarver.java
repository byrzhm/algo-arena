import edu.princeton.cs.algs4.Picture;
import edu.princeton.cs.algs4.StdOut;

import java.awt.Color;

public class SeamCarver {
    private Picture picture;
    private static final double DEFAULT_ENERGY = 1000.0;

    // create a seam carver object based on the given picture
    public SeamCarver(Picture picture) {
        if (picture == null) {
            throw new IllegalArgumentException("picture is null");
        }
        this.picture = new Picture(picture);
    }

    // current picture
    public Picture picture() {
        return new Picture(picture);
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
            return DEFAULT_ENERGY;
        }

        int left = picture.get(x - 1, y).getRGB();
        int right = picture.get(x + 1, y).getRGB();
        int top = picture.get(x, y - 1).getRGB();
        int down = picture.get(x, y + 1).getRGB();

        int redX = ((left >> 16) & 0xff) - ((right >> 16) & 0xff);
        int redY = ((top >> 16) & 0xff) - ((down >> 16) & 0xff);
        int greenX = ((left >> 8) & 0xff) - ((right >> 8) & 0xff);
        int greenY = ((top >> 8) & 0xff) - ((down >> 8) & 0xff);
        int blueX = (left & 0xff) - (right & 0xff);
        int blueY = (top & 0xff) - (down & 0xff);

        double squaredEnergy = 0.0;
        squaredEnergy += redX * redX + greenX * greenX + blueX * blueX;
        squaredEnergy += redY * redY + greenY * greenY + blueY * blueY;

        return Math.sqrt(squaredEnergy);
    }

    // sequence of indices for horizontal seam
    public int[] findHorizontalSeam() {
        double[][] distTo = new double[width()][height()];
        int[][] edgeTo = new int[width()][height()];
        int width = width();
        int height = height();

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                distTo[x][y] = Double.POSITIVE_INFINITY;
            }
        }

        for (int y = 0; y < height; ++y) {
            distTo[0][y] = energy(0, y);
        }

        for (int x = 1; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                double energy = energy(x, y);
                double temp;

                // (x-1, y-1) -> (x, y)
                if (y - 1 >= 0) {
                    temp = energy + distTo[x - 1][y - 1];
                    if (temp < distTo[x][y]) {
                        distTo[x][y] = temp;
                        edgeTo[x][y] = y - 1;
                    }
                }

                // (x-1, y) -> (x, y)
                temp = energy + distTo[x - 1][y];
                if (temp < distTo[x][y]) {
                    distTo[x][y] = temp;
                    edgeTo[x][y] = y;
                }

                // (x-1, y+1) -> (x, y)
                if (y + 1 < height) {
                    temp = energy + distTo[x - 1][y + 1];
                    if (temp < distTo[x][y]) {
                        distTo[x][y] = temp;
                        edgeTo[x][y] = y + 1;
                    }
                }
            }
        }

        int[] seam = new int[width()];
        int minY = -1;
        double minDist = Double.POSITIVE_INFINITY;
        for (int y = 0; y < height; ++y) {
            if (distTo[width - 1][y] < minDist) {
                minDist = distTo[width - 1][y];
                minY = y;
            }
        }
        int y = minY;
        for (int x = width - 1; x >= 0; --x) {
            seam[x] = y;
            y = edgeTo[x][y];
        }
        return seam;
    }

    // sequence of indices for vertical seam
    public int[] findVerticalSeam() {
        double[][] distTo = new double[width()][height()];
        int[][] edgeTo = new int[width()][height()];
        int width = width();
        int height = height();

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                distTo[x][y] = Double.POSITIVE_INFINITY;
            }
        }

        for (int x = 0; x < width; ++x) {
            distTo[x][0] = energy(x, 0);
        }

        for (int y = 1; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double energy = energy(x, y);
                double temp;

                // (x-1, y-1) -> (x, y)
                if (x - 1 >= 0) {
                    temp = energy + distTo[x - 1][y - 1];
                    if (temp < distTo[x][y]) {
                        distTo[x][y] = temp;
                        edgeTo[x][y] = x - 1;
                    }
                }

                temp = energy + distTo[x][y - 1];
                if (temp < distTo[x][y]) {
                    distTo[x][y] = temp;
                    edgeTo[x][y] = x;
                }

                // (x+1, y-1) -> (x, y)
                if (x + 1 < width) {
                    temp = energy + distTo[x + 1][y - 1];
                    if (temp < distTo[x][y]) {
                        distTo[x][y] = temp;
                        edgeTo[x][y] = x + 1;
                    }
                }
            }
        }


        double minDist = Double.POSITIVE_INFINITY;
        int[] seam = new int[height()];
        int minX = -1;
        for (int x = 0; x < width; ++x) {
            if (distTo[x][height - 1] < minDist) {
                minDist = distTo[x][height - 1];
                minX = x;
            }
        }
        int x = minX;
        for (int y = height - 1; y >= 0; --y) {
            seam[y] = x;
            x = edgeTo[x][y];
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
        int prev = -1;
        for (int y : seam) {
            ++size;
            if (y < 0 || y >= height()) {
                throw new IllegalArgumentException("not a valid seam");
            }
            if (prev >= 0 && Math.abs(y - prev) > 1) {
                throw new IllegalArgumentException("not a valid seam");
            }
            prev = y;
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
        int prev = -1;
        for (int x : seam) {
            ++size;
            if (x < 0 || x >= width()) {
                throw new IllegalArgumentException("not a valid seam");
            }
            if (prev >= 0 && Math.abs(x - prev) > 1) {
                throw new IllegalArgumentException("not a valid seam");
            }
            prev = x;
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

    public static void main(String[] args) {
        StdOut.printf("%x\n", Color.BLACK.getRGB());
        StdOut.printf("%x\n", Color.RED.getRGB());
        StdOut.printf("%x\n", Color.GREEN.getRGB());
        StdOut.printf("%x\n", Color.BLUE.getRGB());
    }
}
