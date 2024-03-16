import edu.princeton.cs.algs4.FlowEdge;
import edu.princeton.cs.algs4.FlowNetwork;
import edu.princeton.cs.algs4.FordFulkerson;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;
import java.util.TreeSet;

public class BaseballElimination {
    private final String[] teams;
    private final int[] wins;
    private final int[] loss;
    private final int[] left;
    private final int[][] game;
    private final HashMap<String, Integer> nameMap = new HashMap<>();
    private final boolean[] eliminated;
    private final ArrayList<TreeSet<Integer>> subsets;

    // create a baseball division from given filename in format specified below
    public BaseballElimination(String filename) {
        In in = new In(filename);
        int teamNum = Integer.parseInt(in.readLine());

        teams = new String[teamNum];
        wins = new int[teamNum];
        loss = new int[teamNum];
        left = new int[teamNum];
        game = new int[teamNum][teamNum];
        eliminated = new boolean[teamNum];
        subsets = new ArrayList<>(teamNum);

        int currMax = Integer.MIN_VALUE;
        int currMaxIdx = -1;

        for (int i = 0; i < teamNum; ++i) {
            String line = in.readLine();
            Scanner scanner = new Scanner(line);
            teams[i] = scanner.next();
            wins[i] = scanner.nextInt();
            loss[i] = scanner.nextInt();
            left[i] = scanner.nextInt();

            for (int j = 0; j < teamNum; ++j)
                game[i][j] = scanner.nextInt();

            nameMap.put(teams[i], i);
            subsets.add(null);
            if (currMax < wins[i]) {
                currMax = wins[i];
                currMaxIdx = i;
            }
        }

        for (int i = 0; i < teamNum; ++i) {
            checkIsEliminated(i, currMax, currMaxIdx);
        }
    }

    private void checkIsEliminated(int idx, int currMax, int currMaxIdx) {
        // trivial
        if (wins[idx] + left[idx] < currMax) {
            eliminated[idx] = true;
            subsets.set(idx, new TreeSet<>());
            subsets.get(idx).add(currMaxIdx);
            return;
        }

        // nontrivial
        int teamNum = numberOfTeams();
        int gameNodeNum = (teamNum - 2) * (teamNum - 1) / 2; // 1 ~ gameNodeNum
        int teamNodeNum = teamNum - 1; // gameNodeNum + 1 ~ gameNodeNum + teamNodeNum
        int verNum = gameNodeNum + teamNodeNum + 2;
        int source = 0;
        int sink = verNum - 1;
        FlowNetwork flowNet = new FlowNetwork(verNum);
        HashMap<Integer, int[]> gameNodeMap = new HashMap<>();

        int totalGames = 0;
        int index = 1;
        // source to game node
        // game node to team node
        for (int i = 0; i < teamNum - 1; ++i) {
            if (i == idx) continue;

            for (int j = i + 1; j < teamNum; ++j) {
                if (j == idx) continue;

                int verIdx = index;
                ++index;
                totalGames = totalGames + game[i][j];
                int teamNode1 = gameNodeNum + 1 + (i > idx ? i - 1 : i);
                int teamNode2 = gameNodeNum + 1 + (j > idx ? j - 1 : j);
                FlowEdge edgeFromSrc = new FlowEdge(source, verIdx, game[i][j]);
                FlowEdge edgeToTeam1 = new FlowEdge(verIdx, teamNode1, Double.POSITIVE_INFINITY);
                FlowEdge edgeToTeam2 = new FlowEdge(verIdx, teamNode2, Double.POSITIVE_INFINITY);
                flowNet.addEdge(edgeFromSrc);
                flowNet.addEdge(edgeToTeam1);
                flowNet.addEdge(edgeToTeam2);
                gameNodeMap.put(verIdx, new int[]{i, j});
            }
        }

        int maxScore = wins[idx] + left[idx];
        // team node to sink node
        for (int i = 0; i < teamNum; ++i) {
            if (i == idx) continue;

            int teamNode = gameNodeNum + 1 + (i > idx ? i - 1 : i);
            FlowEdge edgeToSink = new FlowEdge(teamNode, sink, maxScore - wins[i]);
            flowNet.addEdge(edgeToSink);
        }

        FordFulkerson maxFlow = new FordFulkerson(flowNet, source, sink);
        int flow = (int) maxFlow.value();
        eliminated[idx] = flow < totalGames;

        if (eliminated[idx]) {
            subsets.set(idx, new TreeSet<>());
            for (int i = 1; i <= gameNodeNum; ++i) {
                if (maxFlow.inCut(i)) {
                    int[] pair = gameNodeMap.get(i);
                    subsets.get(idx).add(pair[0]);
                    subsets.get(idx).add(pair[1]);
                }
            }
        }
    }

    // number of teams
    public int numberOfTeams() {
        return teams.length;
    }

    // all teams
    public Iterable<String> teams() {
        return List.of(teams);
    }

    // number of wins for given team
    public int wins(String team) {
        if (team == null) throw new IllegalArgumentException("null arg");
        if (!nameMap.containsKey(team)) throw new IllegalArgumentException("team not exists");
        return wins[nameMap.get(team)];
    }

    // number of losses for given team
    public int losses(String team) {
        if (team == null) throw new IllegalArgumentException("null arg");
        if (!nameMap.containsKey(team)) throw new IllegalArgumentException("team not exists");
        return loss[nameMap.get(team)];
    }

    // number of remaining games for given team
    public int remaining(String team) {
        if (team == null) throw new IllegalArgumentException("null arg");
        if (!nameMap.containsKey(team)) throw new IllegalArgumentException("team not exists");
        return left[nameMap.get(team)];
    }

    // number of remaining games between team1 and team2
    public int against(String team1, String team2) {
        if (team1 == null || team2 == null) throw new IllegalArgumentException("null arg");
        if (!nameMap.containsKey(team1) || !nameMap.containsKey(team2))
            throw new IllegalArgumentException("team not exists");
        return game[nameMap.get(team1)][nameMap.get(team2)];
    }

    // is given team eliminated?
    public boolean isEliminated(String team) {
        if (team == null) throw new IllegalArgumentException("null arg");
        if (!nameMap.containsKey(team)) throw new IllegalArgumentException("team not exists");
        return eliminated[nameMap.get(team)];
    }

    // subset R of teams that eliminates given team; null if not eliminated
    public Iterable<String> certificateOfElimination(String team) {
        if (team == null) throw new IllegalArgumentException("null arg");
        if (!nameMap.containsKey(team)) throw new IllegalArgumentException("team not exists");

        int idx = nameMap.get(team);
        if (!eliminated[idx]) return null;

        ArrayList<String> list = new ArrayList<>();
        for (int i : subsets.get(idx)) {
            list.add(teams[i]);
        }
        return list;
    }

    public static void main(String[] args) {
        BaseballElimination division = new BaseballElimination(args[0]);
        for (String team : division.teams()) {
            if (division.isEliminated(team)) {
                StdOut.print(team + " is eliminated by the subset R = { ");
                for (String t : division.certificateOfElimination(team)) {
                    StdOut.print(t + " ");
                }
                StdOut.println("}");
            } else {
                StdOut.println(team + " is not eliminated");
            }
        }
    }
}
