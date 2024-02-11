import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.List;

public class Solver {
    private List<Board> solution = new ArrayList<>();
    private final boolean solvable;

    // find a solution to the initial board (using the A* algorithm)
    public Solver(Board initial) {
        if (initial == null) {
            throw new IllegalArgumentException("Argument 'initial' is null");
        }

        // To detect such situations, use the fact that boards are divided
        // into two equivalence classes with respect to reachability:
        //
        // 1. Those that can lead to the goal board
        // 2. Those that can lead to the goal board if we modify the initial
        //      board by swapping any pair of tiles (the blank square is
        //      not a tile).
        MinPQ<SearchNode> nodes = new MinPQ<>();
        MinPQ<SearchNode> twinNodes = new MinPQ<>();

        nodes.insert(new SearchNode(initial, 0, null));
        twinNodes.insert(new SearchNode(initial.twin(), 0, null));

        boolean solved = false;
        boolean twinSolved = false;
        SearchNode lastNode = null;

        while (!solved && !twinSolved) {
            SearchNode currNode = nodes.delMin();
            SearchNode predecessor = currNode.getPredecessor();
            Board temp = currNode.getBoard();
            solved = temp.isGoal();

            SearchNode twinCurrent = twinNodes.delMin();
            SearchNode twinPredecessor = twinCurrent.getPredecessor();
            Board twinTemp = twinCurrent.getBoard();
            twinSolved = twinTemp.isGoal();

            // To reduce unnecessary exploration of useless search nodes,
            // when considering the neighbors of a search node, don’t
            // enqueue a neighbor if its board is the same as the board
            // of the previous search node in the game tree.
            for (Board b : temp.neighbors()) {
                if (predecessor == null || !predecessor.getBoard().equals(b)) {
                    SearchNode neighborNode = new SearchNode(b, currNode.getMoves() + 1, currNode);
                    nodes.insert(neighborNode);
                }
            }

            for (Board b : twinTemp.neighbors()) {
                if (twinPredecessor == null || !twinPredecessor.getBoard().equals(b)) {
                    SearchNode neighborNode = new SearchNode(b, currNode.getMoves() + 1, twinCurrent);
                    twinNodes.insert(neighborNode);
                }
            }

            lastNode = currNode;
        }

        solvable = !twinSolved;

        if (solvable) {
            while (lastNode != null) {
                solution.add(0, lastNode.board);
                lastNode = lastNode.predecessor;
            }
        }
    }

    // is the initial board solvable? (see below)
    public boolean isSolvable() {
        return solvable;
    }

    // min number of moves to solve initial board; -1 if unsolvable
    public int moves() {
        return solution.size() - 1;
    }

    // sequence of boards in a shortest solution; null if unsolvable
    public Iterable<Board> solution() {
        return isSolvable() ? solution : null;
    }

    private static class SearchNode implements Comparable<SearchNode> {
        private final SearchNode predecessor;
        private final Board board;
        private final int moves;
        private final int priority; // avoid recomputing the Manhattan priority of a search node

        SearchNode(Board brd, int mov, SearchNode pred) {
            predecessor = pred;
            board = brd;
            moves = mov;

            priority = moves + board.manhattan();
        }

        public SearchNode getPredecessor() {
            return predecessor;
        }

        public Board getBoard() {
            return board;
        }

        public int getMoves() {
            return moves;
        }

        public int getPriority() {
            return priority;
        }

        @Override
        public int compareTo(SearchNode other) {
            return Integer.compare(priority, other.getPriority());
        }
    }

    // test client (see below)
    public static void main(String[] args) {
        // create initial board from file
        In in = new In(args[0]);
        int n = in.readInt();
        int[][] tiles = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                tiles[i][j] = in.readInt();
        Board initial = new Board(tiles);

        // solve the puzzle
        Solver solver = new Solver(initial);

        // print solution to standard output
        if (!solver.isSolvable())
            StdOut.println("No solution possible");
        else {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board board : solver.solution())
                StdOut.println(board);
        }
    }

}