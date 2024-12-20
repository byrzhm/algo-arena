import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class FastCollinearPoints {
    private List<LineSegment> lineSegments = new ArrayList<>();

    public FastCollinearPoints(Point[] points) // finds all line segments containing 4 or more points
    {
        checkNullArg(points);
        Point[] sorted = points.clone();
        Arrays.sort(sorted); // Arrays.sort is stable
        checkRepeatedPoints(sorted);

        int n = sorted.length;

        for (int i = 0; i < n; ++i) {
            Point origin = sorted[i];
            Arrays.sort(sorted, origin.slopeOrder());
            // 1. Origin will be at sorted[0]
            // 2. In sorted[1..n-1],
            //     collinear parts will group together and remain natural order (in group)

            int first = 1;
            while (first < n) {
                int last = first + 1;
                while (last < n
                        && Double.compare(origin.slopeTo(sorted[first]), origin.slopeTo(sorted[last])) == 0) {
                    ++last;
                }
                if (last - first >= 3 && origin.compareTo(sorted[first]) < 0) {
                    lineSegments.add(new LineSegment(origin, sorted[last - 1]));
                }
                first = last;
            }

            Arrays.sort(sorted); // restore natural order (in total array)
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
        FastCollinearPoints collinear = new FastCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            StdOut.println(segment);
            segment.draw();
        }
        StdDraw.show();
    }
}
