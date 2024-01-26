import edu.princeton.cs.algs4.StdRandom;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item> implements Iterable<Item> {
    private static final int INITIAL_CAPACITY = 8;
    private static final int GROW_FACTOR = 2;
    private static final double SHRINK_THRESHOLD = 0.25;

    private Item[] array;
    private int size;

    // construct an empty randomized queue
    public RandomizedQueue() {
        array = (Item[]) new Object[INITIAL_CAPACITY];
        size = 0;
    }

    // is the randomized queue empty?
    public boolean isEmpty() {
        return size == 0;
    }

    // return the number of items on the randomized queue
    public int size() {
        return size;
    }

    // add the item
    public void enqueue(Item item) {
        if (item == null) {
            throw new IllegalArgumentException("Item cannot be null");
        }

        ensureCapacity();

        array[size] = item;
        size = size + 1;
    }

    // remove and return a random item
    public Item dequeue() {
        if (isEmpty()) {
            throw new NoSuchElementException("Queue is empty");
        }

        int randomIndex = StdRandom.uniformInt(size);
        Item item = array[randomIndex];

        array[randomIndex] = array[size - 1];
        array[size - 1] = null;
        size = size - 1;

        shrinkIfNeeded();
        return item;
    }

    // return a random item (but do not remove it)
    public Item sample() {
        if (isEmpty()) {
            throw new NoSuchElementException("Queue is empty");
        }

        int randomIndex = StdRandom.uniformInt(size);

        return array[randomIndex];
    }

    private class RandomizedQueueIterator implements Iterator<Item> {
        private int current;
        private final int[] shuffledIndices;

        public RandomizedQueueIterator() {
            current = 0;
            shuffledIndices = new int[size];
            for (int i = 0; i < size; ++i) {
                shuffledIndices[i] = i;
            }

            // Shuffle the indices using Fisher-Yates algorithm
            for (int i = size - 1; i > 0; i--) {
                int j = StdRandom.uniformInt(i + 1);
                int temp = shuffledIndices[i];
                shuffledIndices[i] = shuffledIndices[j];
                shuffledIndices[j] = temp;
            }
        }

        @Override
        public boolean hasNext() {
            return current < size;
        }

        @Override
        public Item next() {
            if (!hasNext()) {
                throw new NoSuchElementException("No more elements to iterate");
            }
            return array[shuffledIndices[current++]];
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException("remove() is not supported");
        }
    }

    // return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return new RandomizedQueueIterator();
    }

    private void ensureCapacity() {
        if (array.length == size) {
            resizeArray(array.length * 2);
        }
    }

    private void shrinkIfNeeded() {
        if (size > 0 && size == array.length * SHRINK_THRESHOLD) {
            int newCapacity = Math.max(array.length / GROW_FACTOR, INITIAL_CAPACITY);
            resizeArray(newCapacity);
        }
    }

    private void resizeArray(int newCapacity) {
        Item[] newArray = (Item[]) new Object[newCapacity];
        System.arraycopy(array, 0, newArray, 0, size);
        array = newArray;
    }

    // unit testing (required)
    public static void main(String[] args) {
        RandomizedQueue<String> rq = new RandomizedQueue<>();

        for (int i = 0; i < 100; i++) {
            rq.enqueue("Item" + i);
        }

        System.out.println("Queue size before dequeue: " + rq.size());

        for (int i = 0; i < 90; i++) {
            rq.dequeue();
        }

        System.out.println("Queue size after dequeue: " + rq.size());
    }

}