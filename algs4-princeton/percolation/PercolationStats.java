import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {

    private double[] results;

    // perform independent trials on an n-by-n grid
    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0) {
            throw new IllegalArgumentException("n and trials should be positive integers");
        }
        results = new double[trials];

        for (int i = 0; i < trials; ++i) {
            Percolation perco = new Percolation(n);
            while (!perco.percolates()) {
                int row = StdRandom.uniformInt(1, n + 1);
                int col = StdRandom.uniformInt(1, n + 1);
                if (!perco.isOpen(row, col)) {
                    perco.open(row, col);
                }
            }
            results[i] = (double) perco.numberOfOpenSites() / (n * n);
        }
    }

    // sample mean of percolation threshold
    public double mean() {
        return StdStats.mean(results);
    }

    // sample standard deviation of percolation threshold
    public double stddev() {
        return StdStats.stddev(results);
    }

    // low endpoint of 95% confidence interval
    public double confidenceLo() {
        return mean() - 1.96 * stddev() / Math.sqrt(results.length);
    }

    // high endpoint of 95% confidence interval
    public double confidenceHi() {
        return mean() + 1.96 * stddev() / Math.sqrt(results.length);
    }

    // test client (see below)
    public static void main(String[] args) {
        try {
            PercolationStats pStats = new PercolationStats(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
            StdOut.println("mean                    = " + pStats.mean());
            StdOut.println("stddev                  = " + pStats.stddev());
            StdOut.println("95% confidence interval = [" + pStats.confidenceLo() 
                                                  + ", " + pStats.confidenceHi() + "]");
        } catch (NumberFormatException e) {
            System.err.println("args should be two positive integer");
        } catch (IllegalArgumentException e) {
            System.err.println(e.toString());
        }
    }

}