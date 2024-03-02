import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class Outcast {
    private final WordNet wordnet;
    public Outcast(WordNet wordnet) { // constructor takes a WordNet object
        this.wordnet = wordnet;
    }

    public String outcast(String[] nouns) { // given an array of WordNet nouns, return an outcast
        String ans = null;
        int max = Integer.MIN_VALUE;
        
        for (String nounA : nouns) {
            int sum = 0;
            for (String nounB : nouns) {
                sum += wordnet.distance(nounA, nounB);
            }
            if (sum > max) {
                max = sum;
                ans = nounA;
            }
        }
        return ans;
    }

    public static void main(String[] args) { // see test client below
        WordNet wordnet = new WordNet(args[0], args[1]);
        Outcast outcast = new Outcast(wordnet);
        for (int t = 2; t < args.length; t++) {
            In in = new In(args[t]);
            String[] nouns = in.readAllStrings();
            StdOut.println(args[t] + ": " + outcast.outcast(nouns));
        }
    }
}
