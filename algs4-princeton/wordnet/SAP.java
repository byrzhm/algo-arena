import edu.princeton.cs.algs4.BreadthFirstDirectedPaths;
import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

/**
 * Performance requirements.
 * All methods (and the constructor) should take time
 * at most proportional to E + V in the worst case,
 * where E and V are the number of edges and vertices
 * in the digraph, respectively. Your data type should
 * use space proportional to E + V.
 */

public class SAP {
    private final Digraph G;

    // constructor takes a digraph (not necessarily a DAG)
    public SAP(Digraph G) {
        if (G == null) {
            throw new IllegalArgumentException("G is null");
        }
        this.G = new Digraph(G);
    }

    // length of shortest ancestral path between v and w; -1 if no such path
    public int length(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        return breadthFirstSearch(v, w)[1];
    }

    // a common ancestor of v and w that participates in the shortest ancestral path; -1 if no such path
    public int ancestor(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        return breadthFirstSearch(v, w)[0];
    }

    // length of shortest ancestral path between any vertex in v and any vertex in w; -1 if no such path
    public int length(Iterable<Integer> v, Iterable<Integer> w) {
        validateVertices(v);
        validateVertices(w);
        return breadthFirstSearch(v, w)[1];
    }

    // a common ancestor that participates in the shortest ancestral path; -1 if no such path
    public int ancestor(Iterable<Integer> v, Iterable<Integer> w) {
        validateVertices(v);
        validateVertices(w);
        return breadthFirstSearch(v, w)[0];
    }

    private int[] breadthFirstSearch(int v, int w) {
        return breadthFirstSearch(new BreadthFirstDirectedPaths(G, v), new BreadthFirstDirectedPaths(G, w));
    }

    private int[] breadthFirstSearch(Iterable<Integer> v, Iterable<Integer> w) {
        return breadthFirstSearch(new BreadthFirstDirectedPaths(G, v), new BreadthFirstDirectedPaths(G, w));
    }

    private int[] breadthFirstSearch(BreadthFirstDirectedPaths bfs1, BreadthFirstDirectedPaths bfs2) {
        int minDistance = Integer.MAX_VALUE;
        int ancestor = 0;

        for (int i = 0; i < G.V(); ++i) {
            if (bfs1.hasPathTo(i) && bfs2.hasPathTo(i)) {
                int distance = bfs1.distTo(i) + bfs2.distTo(i);
                if (distance < minDistance) {
                    minDistance = distance;
                    ancestor = i;
                }
            }
        }

        if (minDistance == Integer.MAX_VALUE) {
            return new int[]{-1, -1};
        }

        return new int[]{ancestor, minDistance};

    }

    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    private void validateVertex(int v) {
        int V = G.V();
        if (v < 0 || v >= V)
            throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V - 1));
    }

    // throw an IllegalArgumentException if vertices is null, has zero vertices,
    // or has a vertex not between 0 and V-1
    private void validateVertices(Iterable<Integer> vertices) {
        if (vertices == null) {
            throw new IllegalArgumentException("argument is null");
        }
        int vertexCount = 0;
        for (Integer v : vertices) {
            vertexCount++;
            if (v == null) {
                throw new IllegalArgumentException("vertex is null");
            }
            validateVertex(v);
        }
        if (vertexCount == 0) {
            throw new IllegalArgumentException("zero vertices");
        }
    }


    // do unit testing of this class
    public static void main(String[] args) {
        In in = new In(args[0]);
        Digraph G = new Digraph(in);
        SAP sap = new SAP(G);
        while (!StdIn.isEmpty()) {
            int v = StdIn.readInt();
            int w = StdIn.readInt();
            int length = sap.length(v, w);
            int ancestor = sap.ancestor(v, w);
            StdOut.printf("length = %d, ancestor = %d\n", length, ancestor);
        }
    }
}
