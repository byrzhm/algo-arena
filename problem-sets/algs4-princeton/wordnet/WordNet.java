import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.DirectedCycle;
import edu.princeton.cs.algs4.In;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Performance requirements.
 * Your data type should use space linear in the input size
 * (size of synsets and hypernyms files). The constructor
 * should take time linearithmic (or better) in the input size.
 * The method isNoun() should run in time logarithmic (or better)
 * in the number of nouns. The methods distance() and sap() should
 * run in time linear in the size of the WordNet digraph.
 * For the analysis, assume that the number of nouns per
 * synset is bounded by a constant.
 */
public class WordNet {
    private final SAP sap;
    private final Map<String, List<Integer>> nounMap = new HashMap<>();
    private final Map<Integer, String> synsetMap = new HashMap<>();

    // constructor takes the name of the two input files
    public WordNet(String synsets, String hypernyms) {
        if (synsets == null || hypernyms == null) {
            throw new IllegalArgumentException("null argument");
        }

        In in = new In(synsets);
        while (!in.isEmpty()) {
            String line = in.readLine();
            String[] fields = line.split(",");
            int index = Integer.parseInt(fields[0]);
            synsetMap.put(index, fields[1]);
            String[] nouns = fields[1].split(" ");
            for (String noun : nouns) {
                if (!nounMap.containsKey(noun)) {
                    nounMap.put(noun, new ArrayList<>());
                }
                nounMap.get(noun).add(index);
            }
        }

        in = new In(hypernyms);
        Digraph g = new Digraph(synsetMap.size());
        while (!in.isEmpty()) {
            String line = in.readLine();
            String[] fields = line.split(",");
            int hypo = Integer.parseInt(fields[0]);
            for (int i = 1; i < fields.length; ++i) {
                g.addEdge(hypo, Integer.parseInt(fields[i]));
            }
        }

        DirectedCycle directedCycle = new DirectedCycle(g);
        if (directedCycle.hasCycle()) {
            throw new IllegalArgumentException("Given graph has a circle");
        }

        int rooted = 0;
        for (int i = 0; i < synsetMap.size(); ++i) {
            if (!g.adj(i).iterator().hasNext()) {
                ++rooted;
            }
        }
        if (rooted != 1) {
            throw new IllegalArgumentException("Given graph is not a rooted DAG");
        }

        sap = new SAP(g);
    }

    // returns all WordNet nouns
    public Iterable<String> nouns() {
        return nounMap.keySet();
    }

    // is the word a WordNet noun?
    public boolean isNoun(String word) {
        if (word == null) {
            throw new IllegalArgumentException("null argument");
        }
        return nounMap.containsKey(word);
    }

    // distance between nounA and nounB (defined below)
    public int distance(String nounA, String nounB) {
        if (nounA == null || nounB == null) {
            throw new IllegalArgumentException("null argument");
        }
        if (!(isNoun(nounA) && isNoun(nounB))) {
            throw new IllegalArgumentException("not a WordNetNoun");
        }
        return sap.length(indexOf(nounA), indexOf(nounB));
    }

    // a synset (second field of synsets.txt) that is the common ancestor of nounA and nounB
    // in the shortest ancestral path (defined below)
    public String sap(String nounA, String nounB) {
        if (!isNoun(nounA) || !isNoun(nounB)) {
            throw new IllegalArgumentException("not a WordNetNoun");
        }
        int ancestor = sap.ancestor(indexOf(nounA), indexOf(nounB));
        return synsetMap.get(ancestor);
    }

    private Iterable<Integer> indexOf(String noun) {
        return nounMap.get(noun);
    }

    // do unit testing of this class
    public static void main(String[] args) {
        WordNet w = new WordNet("synsets.txt", "hypernyms.txt");
        System.out.println(w.sap("soda", "bed"));
        System.out.println(w.distance("soda", "bed"));
    }
}