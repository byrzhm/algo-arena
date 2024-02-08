import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class BruteCollinearPoints {
    private List<LineSegment> lineSegments = new ArrayList<>();

    public BruteCollinearPoints(Point[] points) // finds all line segments containing 4 points
    {
        checkNullArg(points);
        Point[] sortedPoints = points.clone();
        Arrays.sort(sortedPoints);
        checkRepeatedPoints(sortedPoints);

        int n = points.length;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    for (int t = k + 1; t < n; ++t) {
                        Point p = sortedPoints[i];
                        Point q = sortedPoints[j];
                        Point r = sortedPoints[k];
                        Point s = sortedPoints[t];
                        if (isCollinear(p, q, r, s)) {
                            lineSegments.add(new LineSegment(p, s));
                        }
                    }
                }
            }
        }

    }

    private void checkRepeatedPoints(Point[] sortedPoints) {
        for (int i = 0; i < sortedPoints.length - 1; ++i) {
            if (sortedPoints[i].compareTo(sortedPoints[i + 1]) == 0) {
                throw new IllegalArgumentException("points contains a repeated point");
            }
        }
    }

    private void checkNullArg(Point[] points) {
        if (points == null) {
            throw new IllegalArgumentException("points is null");
        }

        int n = points.length;

        for (int i = 0; i < n; ++i) {
            if (points[i] == null) {
                throw new IllegalArgumentException("points[" + Integer.toString(i) + "] is null");
            }
        }
    }

    private boolean isCollinear(Point p, Point q, Point r, Point s) {
        double slope1 = p.slopeTo(q);
        double slope2 = q.slopeTo(r);
        double slope3 = r.slopeTo(s);
        return slope1 == slope2 && slope2 == slope3;
    }

    public int numberOfSegments() // the number of line segments
    {
        return lineSegments.size();
    }

    public LineSegment[] segments() // the line segments
    {
        return lineSegments.toArray(new LineSegment[0]);
    }

    public static void main(String[] args) {
        // read the n points from a file
        In in = new In(args[0]);
        int n = in.readInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            int x = in.readInt();
            int y = in.readInt();
            points[i] = new Point(x, y);
        }

        // draw the points
        StdDraw.enableDoubleBuffering();
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        for (Point p : points) {
            p.draw();
        }
        StdDraw.show();

        // print and draw the line segments
        BruteCollinearPoints collinear = new BruteCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            StdOut.println(segment);
            segment.draw();
        }
        StdDraw.show();
    }
}