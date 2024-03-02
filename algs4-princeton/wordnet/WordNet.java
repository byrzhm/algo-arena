import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.DirectedCycle;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

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
    private final Digraph G;
    private final Map<String, List<Integer>> nouns = new HashMap<>();
    private final Map<Integer, String> synsets = new HashMap<>();

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
            this.synsets.put(index, fields[1]);
            String[] nouns = fields[1].split(" ");
            for (String noun : nouns) {
                if (!this.nouns.containsKey(noun)) {
                    this.nouns.put(noun, new ArrayList<>());
                }
                this.nouns.get(noun).add(index);
            }
        }

        in = new In(hypernyms);
        G = new Digraph(this.synsets.size());
        while (!in.isEmpty()) {
            String line = in.readLine();
            String[] fields = line.split(",");
            int hypo = Integer.parseInt(fields[0]);
            for (int i = 1; i < fields.length; ++i) {
                G.addEdge(hypo, Integer.parseInt(fields[i]));
            }
        }

        DirectedCycle directedCycle = new DirectedCycle(G);
        if (directedCycle.hasCycle()) {
            throw new IllegalArgumentException("Given graph is not rooted DAG");
        }
    }

    // returns all WordNet nouns
    public Iterable<String> nouns() {
        return nouns.keySet();
    }

    // is the word a WordNet noun?
    public boolean isNoun(String word) {
        if (word == null) {
            throw new IllegalArgumentException("null argument");
        }
        return nouns.containsKey(word);
    }

    // distance between nounA and nounB (defined below)
    public int distance(String nounA, String nounB) {
        if (nounA == null || nounB == null) {
            throw new IllegalArgumentException("null argument");
        }
        if (!(isNoun(nounA) && isNoun(nounB))) {
            throw new IllegalArgumentException("not a WordNetNoun");
        }
        SAP sap = new SAP(G);
        return sap.length(indexOf(nounA), indexOf(nounB));
    }

    // a synset (second field of synsets.txt) that is the common ancestor of nounA and nounB
    // in the shortest ancestral path (defined below)
    public String sap(String nounA, String nounB) {
        if (!isNoun(nounA) || !isNoun(nounB)) {
            throw new IllegalArgumentException("not a WordNetNoun");
        }
        SAP sap = new SAP(G);
        int ancestor = sap.ancestor(indexOf(nounA), indexOf(nounB));
        return synsets.get(ancestor);
    }

    private Iterable<Integer> indexOf(String noun) {
        return nouns.get(noun);
    }

    // do unit testing of this class
    public static void main(String[] args) {
    }
}