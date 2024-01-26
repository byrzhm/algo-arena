import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

import java.util.Iterator;

public class Permutation {
    public static void main(String[] args) {
        try {
            int k = Integer.parseInt(args[0]);
            if (k <= 0) {
                return;
            }

            RandomizedQueue<String> rq = new RandomizedQueue<>();

            /**
             * reservoir sampling algorithm
             * See https://en.wikipedia.org/wiki/Reservoir_sampling
             */
            int count = 0;
            while (!StdIn.isEmpty()) {
                String string = StdIn.readString();
                ++count;
                if (rq.size() == k) {
                    int rand = StdRandom.uniformInt(count);
                    if (rand < k) {
                        rq.dequeue();
                    } else {
                        continue;
                    }
                }
                rq.enqueue(string);
            }

            Iterator<String> iterator = rq.iterator();
            for (int i = 0; i < k && iterator.hasNext(); ++i) {
                StdOut.println(iterator.next());
            }

        } catch (NumberFormatException e) {
            System.err.println("Error parsing the string to int: " + e.getMessage());
        }
    }
}