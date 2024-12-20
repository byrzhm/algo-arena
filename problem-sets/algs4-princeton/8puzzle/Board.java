import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.List;

public class Board {

    private final int[][] tiles;

    // create a board from an n-by-n array of tiles,
    // where tiles[row][col] = tile at (row, col)
    public Board(int[][] tiles) {
        if (tiles == null) {
            throw new IllegalArgumentException("Argument 'tiles' is null");
        }

        int r = tiles.length;
        int c = tiles[0].length;
        if (r != c) {
            throw new IllegalArgumentException("Argument 'tiles': r != c");
        }

        this.tiles = new int[r][r];
        for (int i = 0; i < r; ++i) {
            System.arraycopy(tiles[i], 0, this.tiles[i], 0, r);
        }
    }

    // string representation of this board
    public String toString() {
        StringBuilder sb = new StringBuilder();
        int n = dimension();
        sb.append(n).append('\n');
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                sb.append(' ').append(tiles[i][j]);
            }
            sb.append('\n');
        }
        return sb.toString();
    }

    // board dimension n
    public int dimension() {
        return tiles.length;
    }

    private int goalAtIdx(int i, int j) {
        int n = dimension();
        if (i == n - 1 && j == n - 1) return 0;
        return i * n + j + 1;
    }

    // number of tiles out of place
    public int hamming() {
        int hammingDist = 0;
        int n = dimension();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (tiles[i][j] != 0 && tiles[i][j] != goalAtIdx(i, j))
                    ++hammingDist;
            }
        }
        return hammingDist;
    }

    private int[] idxOfGoal(int goal) {
        if (goal == 0)
            return new int[0];

        int[] indexes = new int[2];
        int n = dimension();
        --goal;
        indexes[0] = goal / n;
        indexes[1] = goal % n;
        return indexes;
    }

    // sum of Manhattan distances between tiles and goal
    public int manhattan() {
        int manhattanDist = 0;
        int n = dimension();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int[] indexes = idxOfGoal(tiles[i][j]);
                if (indexes.length == 2) { // blank is excluded
                    manhattanDist += Math.abs(indexes[0] - i) + Math.abs(indexes[1] - j);
                }
            }
        }
        return manhattanDist;
    }

    // is this board the goal board?
    public boolean isGoal() {
        return hamming() == 0;
    }

    // does this board equal y?
    public boolean equals(Object y) {
        if (y == null) return false;
        if (y == this) return true;
        if (this.getClass() != y.getClass()) return false;

        Board other = (Board) y;
        if (dimension() != other.dimension()) return false;

        int n = dimension();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (tiles[i][j] != other.tiles[i][j])
                    return false;
            }
        }
        return true;
    }

    // all neighboring boards
    public Iterable<Board> neighbors() {
        List<Board> neighborBoards = new ArrayList<>();
        int n = dimension();
        int i = 0, j = 0;

        for (; i < n; ++i) {
            j = 0;
            while (j < n && tiles[i][j] != 0) ++j;
            if (j < n && tiles[i][j] == 0) break;
        }

        if (i + 1 < n) {
            swap(i + 1, j, i, j);
            neighborBoards.add(new Board(tiles));
            swap(i + 1, j, i, j);
        }

        if (i - 1 >= 0) {
            swap(i - 1, j, i, j);
            neighborBoards.add(new Board(tiles));
            swap(i - 1, j, i, j);
        }

        if (j + 1 < n) {
            swap(i, j + 1, i, j);
            neighborBoards.add(new Board(tiles));
            swap(i, j + 1, i, j);
        }

        if (j - 1 >= 0) {
            swap(i, j - 1, i, j);
            neighborBoards.add(new Board(tiles));
            swap(i, j - 1, i, j);
        }

        return neighborBoards;
    }

    // a board that is obtained by exchanging any pair of tiles
    public Board twin() {
        int n = dimension();
        Board twinBoard = null;

        // the blank square is not a tile
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (tiles[i][j] != 0) {
                    if (i + 1 < n && tiles[i + 1][j] != 0) {
                        swap(i + 1, j, i, j);
                        twinBoard = new Board(tiles);
                        swap(i + 1, j, i, j);
                        break;
                    }

                    if (i - 1 >= 0 && tiles[i - 1][j] != 0) {
                        swap(i - 1, j, i, j);
                        twinBoard = new Board(tiles);
                        swap(i - 1, j, i, j);
                        break;
                    }

                    if (j + 1 < n && tiles[i][j + 1] != 0) {
                        swap(i, j + 1, i, j);
                        twinBoard = new Board(tiles);
                        swap(i, j + 1, i, j);
                        break;
                    }

                    if (j - 1 >= 0 && tiles[i][j - 1] != 0) {
                        swap(i, j - 1, i, j);
                        twinBoard = new Board(tiles);
                        swap(i, j - 1, i, j);
                        break;
                    }
                }
            }
        }

        return twinBoard;
    }

    // swap tiles[i1][j1] and tiles[i2][j2]
    private void swap(int i1, int j1, int i2, int j2) {
        int temp = tiles[i1][j1];
        tiles[i1][j1] = tiles[i2][j2];
        tiles[i2][j2] = temp;
    }

    // unit testing (not graded)
    public static void main(String[] args) {
        int[][] tiles = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 0}
        };

        Board board = new Board(tiles);
        StdOut.println(board);

        for (Board b : board.neighbors()) {
            StdOut.println(b);
        }
    }

}