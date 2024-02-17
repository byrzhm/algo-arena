import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

import java.awt.Color;

public class KdTree {
    private static final boolean VERTICAL = true;
//    private static final boolean HORIZONTAL = false;

    private Node root;
    private int size;

    private static class Node {
        private final Point2D point;
        private Node left;
        private Node right;
        private final boolean orient;

        public Node(Point2D p, boolean orient) {
            point = p;
            this.orient = orient;
        }
    }

    // construct an empty set of points
    public KdTree() {
        size = 0;
    }

    // is the set empty?
    public boolean isEmpty() {
        return size == 0;
    }

    // number of points in the set
    public int size() {
        return size;
    }

    // add the point to the set (if it is not already in the set)
    public void insert(Point2D p) {
        if (p == null) throw new IllegalArgumentException("null argument");
        root = insert(root, p, null);
    }

    private Node insert(Node node, Point2D p, Node parent) {
        if (node == null) {
            ++size;
            return new Node(p, nextOrient(parent));
        }

        if (node.point.equals(p)) {
            return node;
        }

        int cmp = node.orient ?
                Double.compare(p.x(), node.point.x())
                : Double.compare(p.y(), node.point.y());

        if (cmp < 0) node.left = insert(node.left, p, node);
        else /* if (cmp > 0) */ node.right = insert(node.right, p, node);

        return node;
    }

    private boolean nextOrient(Node parent) {
        if (parent == null) return VERTICAL;
        return !parent.orient;
    }

    // does the set contain point p?
    public boolean contains(Point2D p) {
        if (p == null) throw new IllegalArgumentException("null argument");
        return contains(root, p);
    }

    private boolean contains(Node node, Point2D p) {
        if (node == null) return false;

        if (node.point.equals(p)) {
            return true;
        }

        int cmp = node.orient ?
                Double.compare(p.x(), node.point.x())
                : Double.compare(p.y(), node.point.y());

        if (cmp < 0) return contains(node.left, p);
        return contains(node.right, p);
    }

    // draw all points to standard draw
    public void draw() {
        draw(root, 0.0, 1.0, 0.0, 1.0);
    }

    private void draw(Node node, double xMin, double xMax, double yMin, double yMax) {
        if (node == null) return;

        Point2D p = node.point;
        StdDraw.setPenRadius(0.01);

//        StdOut.println(p + ": xMin=" + xMin + ", xMax=" + xMax + ", yMin=" + yMin + ", yMax=" + yMax);
        if (node.orient) {
            StdDraw.setPenColor(Color.RED);
            StdDraw.line(p.x(), yMin, p.x(), yMax);
            draw(node.left, xMin, p.x(), yMin, yMax);
            draw(node.right, p.x(), xMax, yMin, yMax);
        } else {
            StdDraw.setPenColor(Color.BLUE);
            StdDraw.line(xMin, p.y(), xMax, p.y());
            draw(node.left, xMin, xMax, yMin, p.y());
            draw(node.right, xMin, xMax, p.y(), yMax);
        }

        StdDraw.setPenColor(Color.BLACK);
        StdDraw.setPenRadius(0.02);
        p.draw();
    }

    // all points that are inside the rectangle (or on the boundary)
    public Iterable<Point2D> range(RectHV rect) {
        if (rect == null) throw new IllegalArgumentException("null argument");
        Queue<Point2D> queue = new Queue<>();
        range(root, rect, queue);
        return queue;
    }

    private void range(Node node, RectHV rect, Queue<Point2D> queue) {
        if (node == null) return;
        Point2D point = node.point;

        if (rect.contains(point)) {
            queue.enqueue(point);
        }

        if (node.orient) { // Vertical
            if (rect.xmin() < point.x()) range(node.left, rect, queue);
            if (rect.xmax() >= point.x()) range(node.right, rect, queue);
        } else { // Horizontal
            if (rect.ymin() < point.y()) range(node.left, rect, queue);
            if (rect.ymax() >= point.y()) range(node.right, rect, queue);
        }
    }

    // a nearest neighbor in the set to point p; null if the set is empty
    public Point2D nearest(Point2D p) {
        if (p == null) throw new IllegalArgumentException("null argument");
        if (root == null) return null;
        return nearest(root, p);
    }

    private Point2D nearest(Node node, Point2D p) {
        Point2D point = node.point;
        if (node.left == null && node.right == null) {
            return point;
        }

        if (node.left == null || node.right == null) {
            Node n1 = node.left == null ? node.right : node.left;
            Point2D p1 = nearest(n1, p);
            int cmp = p.distanceToOrder().compare(point, p1);
            if (cmp < 0) return point;
            return p1;
        }

        Point2D leftPoint = node.left.point;
        Point2D rightPoint = node.right.point;

        double dist = p.distanceSquaredTo(point);
        double leftDist = p.distanceSquaredTo(leftPoint);
        double rightDist = p.distanceSquaredTo(rightPoint);

        if (node.orient) {
            double distToSplitLine = p.distanceSquaredTo(new Point2D(point.x(), p.y()));
            if (leftDist < dist && leftDist < distToSplitLine) { // left
                return nearest(node.left, p);
            }

            if (rightDist < dist && rightDist < distToSplitLine) { // right
                return nearest(node.right, p);
            }
        }

        if (!node.orient) {
            double distToSplitLine = p.distanceSquaredTo(new Point2D(p.x(), point.y()));
            if (leftDist < dist && leftDist < distToSplitLine) { // bottom
                return nearest(node.left, p);
            }

            if (rightDist < dist && rightDist < distToSplitLine) { // up
                return nearest(node.right, p);
            }
        }

        Point2D leftNearest = nearest(node.left, p);
        Point2D rightNearest = nearest(node.right, p);
        Point2D leftRightNearest = nearest(p, leftNearest, rightNearest);
        return nearest(p, leftRightNearest, point);
    }

    private Point2D nearest(Point2D origin, Point2D p1, Point2D p2) {
        int cmp = origin.distanceToOrder().compare(p1, p2);
        if (cmp < 0) return p1;
        return p2;
    }

    // unit testing of the methods (optional)
    public static void main(String[] args) {
        KdTree kdtree = new KdTree();
//        kdtree.insert(new Point2D(0.7, 0.2));
//        kdtree.insert(new Point2D(0.5, 0.4));
//        kdtree.insert(new Point2D(0.2, 0.3));
//        kdtree.insert(new Point2D(0.4, 0.7));
//        kdtree.insert(new Point2D(0.9, 0.6));

        kdtree.insert(new Point2D(0.29, 0.17));
        kdtree.insert(new Point2D(0.6, 0.87));
        kdtree.insert(new Point2D(0.37, 0.01));
        kdtree.insert(new Point2D(0.9, 0.61));
        kdtree.insert(new Point2D(0.75, 0.23));
        kdtree.insert(new Point2D(0.58, 0.31));
        kdtree.insert(new Point2D(0.69, 0.43));
        kdtree.insert(new Point2D(0.57, 0.69));
        kdtree.insert(new Point2D(0.69, 0.85));
        kdtree.insert(new Point2D(0.88, 0.9));
        kdtree.insert(new Point2D(0.04, 0.09));
        kdtree.insert(new Point2D(0.29, 0.23));

        StdOut.println(kdtree.size);

//        StdOut.println(kdtree.nearest(new Point2D(0.2, 0.7)));

        // process nearest neighbor queries
        StdDraw.enableDoubleBuffering();

        while (true) {
            // the location (x, y) of the mouse
            double x = StdDraw.mouseX();
            double y = StdDraw.mouseY();
            Point2D query = new Point2D(x, y);
//            StdOut.println(query);

            // draw all the points
            StdDraw.clear();
            kdtree.draw();

            StdDraw.setPenColor(StdDraw.GREEN);
            StdDraw.setPenRadius(0.03);
            kdtree.nearest(query).draw();
            StdDraw.show();

            StdDraw.pause(40);
        }
    }
}
