import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {

    private boolean[] grid;
    private int size;
    private int openCount;
    private int topIndex;
    private int bottomIndex;
    private WeightedQuickUnionUF connectUF;
    private WeightedQuickUnionUF fullUF;

    // creates n-by-n grid, with all sites initially blocked
    public Percolation(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("n is not a positive integer");
        }
        size = n;
        openCount = 0;
        topIndex = 0;
        bottomIndex = n * n + 1;
        
        grid = new boolean[n * n + 1];
        connectUF = new WeightedQuickUnionUF(n * n + 2);
        fullUF = new WeightedQuickUnionUF(n * n + 1); // connected to top doesn't mean full
    }

    private int indexOf(int row, int col) {
        return 1 + (row - 1) * size + (col - 1);
    }

    // opens the site (row, col) if it is not open already
    public void open(int row, int col) {
        if (row < 1 || row > size || col < 1 || col > size) {
            throw new IllegalArgumentException("Out of bound");
        }

        if (!isOpen(row, col)) {
            ++openCount;

            grid[indexOf(row, col)] = true;

            if (row == 1) {
                connectUF.union(indexOf(row, col), topIndex);
                fullUF.union(indexOf(row, col), topIndex);
            }

            if (row == size) {
                connectUF.union(indexOf(row, col), bottomIndex);
            }

            if (row > 1 && isOpen(row - 1, col)) {
                connectUF.union(indexOf(row, col), indexOf(row - 1, col));
                fullUF.union(indexOf(row, col), indexOf(row - 1, col));
            }

            if (row < size && isOpen(row + 1, col)) {
                connectUF.union(indexOf(row, col), indexOf(row + 1, col));
                fullUF.union(indexOf(row, col), indexOf(row + 1, col));
            }

            if (col > 1 && isOpen(row, col - 1)) {
                connectUF.union(indexOf(row, col), indexOf(row, col - 1));
                fullUF.union(indexOf(row, col), indexOf(row, col - 1));
            }

            if (col < size && isOpen(row, col + 1)) {
                connectUF.union(indexOf(row, col), indexOf(row, col + 1));
                fullUF.union(indexOf(row, col), indexOf(row, col + 1));
            }
        }
    }

    // is the site (row, col) open?
    public boolean isOpen(int row, int col) {
        if (row < 1 || row > size || col < 1 || col > size) {
            throw new IllegalArgumentException("Out of bound");
        }
        return grid[indexOf(row, col)];
    }

    // is the site (row, col) full?
    public boolean isFull(int row, int col) {
        if (row < 1 || row > size || col < 1 || col > size) {
            throw new IllegalArgumentException("Out of bound");
        }
        return fullUF.find(indexOf(row, col)) == fullUF.find(topIndex);
    }

    // returns the number of open sites
    public int numberOfOpenSites() {
        return openCount;
    }

    // does the system percolate?
    public boolean percolates() {
        return connectUF.find(topIndex) == connectUF.find(bottomIndex);
    }

    // test client (optional)
    public static void main(String[] args) {
        int n = 5;
        Percolation p = new Percolation(n);
        for (int i = 1; i <= n; ++i) {
            p.open(i, 1);
        }
        StdOut.println(p.percolates());
        StdOut.println(p.numberOfOpenSites());
    }
}