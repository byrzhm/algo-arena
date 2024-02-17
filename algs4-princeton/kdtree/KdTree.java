import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

import java.awt.Color;

public class KdTree {
    private Node root;
    private int size;

    private static class Node {
        private final Point2D p;
        private final RectHV r;
        private Node left;
        private Node right;

        public Node(Point2D p, RectHV r) {
            this.p = p;
            this.r = r;
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
        root = insert(root, p, 0.0, 0.0, 1.0, 1.0, true);
    }

    private Node insert(Node node, Point2D p, double x0, double y0, double x1, double y1, boolean vertical) {
        if (node == null) {
            ++size;
            return new Node(p, new RectHV(x0, y0, x1, y1));
        }

        if (node.p.equals(p)) return node;

        if (vertical) {
            int cmp = Double.compare(p.x(), node.p.x());
            if (cmp < 0) node.left = insert(node.left, p, x0, y0, node.p.x(), y1, false);
            else /* if (cmp > 0) */ node.right = insert(node.right, p, node.p.x(), y0, x1, y1, false);
        } else {
            int cmp = Double.compare(p.y(), node.p.y());
            if (cmp < 0) node.left = insert(node.left, p, x0, y0, x1, node.p.y(), true);
            else /* if (cmp > 0) */ node.right = insert(node.right, p, x0, node.p.y(), x1, y1, true);
        }

        return node;
    }

    // does the set contain point p?
    public boolean contains(Point2D p) {
        if (p == null) throw new IllegalArgumentException("null argument");
        return contains(root, p, true);
    }

    private boolean contains(Node node, Point2D p, boolean vertical) {
        if (node == null) return false;

        if (node.p.equals(p)) {
            return true;
        }

        int cmp = vertical ?
                Double.compare(p.x(), node.p.x())
                : Double.compare(p.y(), node.p.y());

        if (cmp < 0) return contains(node.left, p, !vertical);
        return contains(node.right, p, !vertical);
    }

    // draw all points to standard draw
    public void draw() {
        draw(root, true);
    }

    private void draw(Node node, boolean vertical) {
        if (node == null) return;


//        StdOut.println(p + ": xMin=" + xMin + ", xMax=" + xMax + ", yMin=" + yMin + ", yMax=" + yMax);
        if (vertical) {
            StdDraw.setPenColor(Color.RED);
            StdDraw.setPenRadius();
            StdDraw.line(node.p.x(), node.r.ymin(), node.p.x(), node.r.ymax());
            draw(node.left, false);
            draw(node.right, false);
        } else {
            StdDraw.setPenColor(Color.BLUE);
            StdDraw.setPenRadius();
            StdDraw.line(node.r.xmin(), node.p.y(), node.r.xmax(), node.p.y());
            draw(node.left, true);
            draw(node.right, true);
        }

        StdDraw.setPenColor(Color.BLACK);
        StdDraw.setPenRadius(0.02);
        node.p.draw();
    }

    // all points that are inside the rectangle (or on the boundary)
    public Iterable<Point2D> range(RectHV rect) {
        if (rect == null) throw new IllegalArgumentException("null argument");
        Queue<Point2D> queue = new Queue<>();
        range(root, rect, queue, true);
        return queue;
    }

    /**
     * Range search. To find all points contained in a given query rectangle, start at the root
     * and recursively search for points in both subtrees using the following pruning rule:
     *      if the query rectangle does not intersect the rectangle corresponding to a node,
     *      there is no need to explore that node (or its subtrees). A subtree is searched only
     *      if it might contain a point contained in the query rectangle.
     */
    private void range(Node node, RectHV rect, Queue<Point2D> queue, boolean vertical) {
        if (node == null) return;
        Point2D point = node.p;

        if (rect.contains(point)) {
            queue.enqueue(point);
        }

        if (vertical) { // Vertical
            if (rect.xmin() < point.x()) range(node.left, rect, queue, false);
            if (rect.xmax() >= point.x()) range(node.right, rect, queue, false);
        } else { // Horizontal
            if (rect.ymin() < point.y()) range(node.left, rect, queue, true);
            if (rect.ymax() >= point.y()) range(node.right, rect, queue, true);
        }
    }

    // a nearest neighbor in the set to point p; null if the set is empty
    public Point2D nearest(Point2D p) {
        if (p == null) throw new IllegalArgumentException("null argument");
        if (root == null) return null;
        return nearest(root, p, root.p, true);
    }

    /**
     * Nearest-neighbor search.
     *   To find the closest point to a given query point, start at the root and recursively
     *   search in both subtrees using the following pruning rule:
     *      if the closest point discovered so far is closer than the distance between the
     *      query point and the rectangle corresponding to a node, there is no need to explore
     *      that node (or its subtrees). That is, search a node only if it might contain a
     *      point that is closer than the best one found so far.
     *   The effectiveness of the pruning rule depend on quickly finding a nearby point. To do this,
     *   organize the recursive method so that when there are two possible subtrees to go down,
     *   you always choose the subtree that is on the same side of the splitting line as the query
     *   point as the first subtree to explore—the closest point found while exploring the first
     *   subtree may enable pruning of the second subtree.
     */
    private Point2D nearest(Node node, Point2D p, Point2D c, boolean vertical) {
        Point2D closest = c;
        if (node == null) return closest;

        if (node.p.distanceSquaredTo(p) < closest.distanceSquaredTo(p))
            closest = node.p;

        /*
         *  if the closest point discovered so far is closer than the distance between the query
         *  point and the rectangle corresponding to a node, there is no need to explore that node.
         *
         *  That is, search a node only if it might contain a point that is closer than the best
         *  one found so far.
         */
        if (node.r.distanceSquaredTo(p) < closest.distanceSquaredTo(p)) {
            Node near;
            Node far;
            if ((vertical && (p.x() < node.p.x())) || (!vertical && (p.y() < node.p.y()))) {
                near = node.left;
                far = node.right;
            }
            else {
                near = node.right;
                far = node.left;
            }

            closest = nearest(near, p, closest, !vertical); // same side first
            closest = nearest(far, p, closest, !vertical);
        }

        return closest;
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
