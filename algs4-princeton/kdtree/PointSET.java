import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.SET;
import edu.princeton.cs.algs4.StdOut;

public class PointSET {
    private final SET<Point2D> pointSet;

    public PointSET() // construct an empty set of points
    {
        pointSet = new SET<>();
    }

    public boolean isEmpty() // is the set empty?
    {
        return pointSet.isEmpty();
    }

    public int size() // number of points in the set
    {
        return pointSet.size();
    }

    public void insert(Point2D p) // add the point to the set (if it is not already in the set)
    {
        if (p == null) throw new IllegalArgumentException("null argument");
        if (!pointSet.contains(p)) pointSet.add(p);
    }

    public boolean contains(Point2D p) // does the set contain point p?
    {
        if (p == null) throw new IllegalArgumentException("null argument");
        return pointSet.contains(p);
    }

    public void draw() // draw all points to standard draw
    {
        for (Point2D point : pointSet) point.draw();
    }

    public Iterable<Point2D> range(RectHV rect) // all points that are inside the rectangle (or on the boundary)
    {
        if (rect == null) throw new IllegalArgumentException("null argument");
        Queue<Point2D> queue = new Queue<>();
        for (Point2D point : pointSet) {
            if (rect.contains(point)) {
                queue.enqueue(point);
            }
        }
        return queue;
    }

    public Point2D nearest(Point2D p) // a nearest neighbor in the set to point p; null if the set is empty
    {
        if (p == null) throw new IllegalArgumentException("null argument");
        Point2D nearest = null;
        double minDistSquare = Double.POSITIVE_INFINITY;
        for (Point2D point : pointSet) {
            double distSquare = p.distanceSquaredTo(point);
            if (distSquare < minDistSquare) {
                nearest = point;
                minDistSquare = distSquare;
            }
        }
        return nearest;
    }

    public static void main(String[] args) // unit testing of the methods (optional)
    {
        PointSET set = new PointSET();
        for (int i = 0; i < 4; ++i) {
            double x = 0.2 * i;
            double y = 0.2 * i;
            Point2D p = new Point2D(x, y);
            set.insert(p);
        }

        Point2D center = new Point2D(0.5, 0.5);
        StdOut.println("nearest: " + set.nearest(center));

        RectHV rectHV = new RectHV(0.25, 0.25, 0.75, 0.75);
        for (Point2D p : set.range(rectHV)) {
            StdOut.println("In range: " + p);
        }
    }
}

