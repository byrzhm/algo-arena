import edu.princeton.cs.algs4.StdOut;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {
    private Node first;
    private Node last;
    private int size;

    private class Node {
        Item item;
        Node prev;
        Node next;
    }

    // construct an empty deque
    public Deque() {
        first = null;
        last = null;
        size = 0;
    }

    // is the deque empty?
    public boolean isEmpty() {
        return size == 0;
    }

    // return the number of items on the deque
    public int size() {
        return size;
    }

    // add the item to the front
    public void addFirst(Item item) {
        if (item == null) {
            throw new IllegalArgumentException("addFirst with null argument");
        }

        Node newNode = new Node();
        newNode.item = item;

        if (isEmpty()) {
            first = newNode;
            last = newNode;
        } else {
            newNode.next = first;
            first.prev = newNode;
            first = newNode;
        }

        size = size + 1;
    }

    // add the item to the back
    public void addLast(Item item) {
        if (item == null) {
            throw new IllegalArgumentException("addLast with null argument");
        }
        
        Node newNode = new Node();
        newNode.item = item;

        if (isEmpty()) {
            first = newNode;
            last = newNode;
        } else {
            newNode.prev = last;
            last.next = newNode;
            last = newNode;
        }

        size = size + 1;
    }

    // remove and return the item from the front
    public Item removeFirst() {
        if (isEmpty()) {
            throw new NoSuchElementException("removeFirst when deque is empty");
        }

        Item item = first.item;
        if (size == 1) {
            first = null;
            last = null;
        } else {
            first = first.next;
            first.prev = null;
        }

        size = size - 1;

        return item;
    }

    // remove and return the item from the back
    public Item removeLast() {
        if (isEmpty()) {
            throw new NoSuchElementException("removeLast when deque is empty");
        }

        Item item = last.item;
        if (size == 1) {
            first = null;
            last = null;
        } else {
            last = last.prev;
            last.next = null;
        }

        size = size - 1;
        
        return item;
    }


    private class DequeIterator implements Iterator<Item> {

        private Node current = first;

        @Override
        public boolean hasNext() {
            return current != null;
        }

        @Override
        public Item next() {
            if (!hasNext()) {
                throw new NoSuchElementException("No more elements to iterate");
            }

            Item item = current.item;
            current = current.next;
            return item;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException("Unimplemented");
        }
    }

    // return an iterator over items in order from front to back
    public Iterator<Item> iterator() {
        return new DequeIterator();
    }

    // unit testing (required)
    public static void main(String[] args) {
        Deque<Integer> deque = new Deque<>();
        for (int i = 0; i < 10; ++i) {
            deque.addFirst(i);
        }

        Iterator<Integer> iterator = deque.iterator();
        while (iterator.hasNext()) {
            StdOut.println(iterator.next());
        }
    }
}

/**
 * memory test will fail, if use circular buffer
 */

// public class Deque<Item> implements Iterable<Item> {

//     private static final int DEFAULT_CAPACITY = 10;
//     private static final int GROW_FACTOR = 2;
//     private static final double SHRINK_THRESHOLD = 0.25;

//     private Item[] arrayItems_;
//     private int front_;
//     private int rear_;
//     private int size_;


//     // construct an empty deque
//     public Deque() {
//         this.arrayItems_ = (Item[]) new Object[DEFAULT_CAPACITY];
//         this.front_ = 0;
//         this.rear_ = 0;
//         this.size_ = 0;
//     }

//     // is the deque empty?
//     public boolean isEmpty() {
//         return size_ == 0;
//     }

//     // return the number of items on the deque
//     public int size() {
//         return size_;
//     }

//     // add the item to the front
//     public void addFirst(Item item) {
//         if (item == null) {
//             throw new IllegalArgumentException("addFirst with null argument");
//         }

//         front_ = (front_ - 1 + arrayItems_.length) % arrayItems_.length;
//         arrayItems_[front_] = item;
//         size_ = size_ + 1;

//         ensureCapacity();
//     }

//     // add the item to the back
//     public void addLast(Item item) {
//         if (item == null) {
//             throw new IllegalArgumentException("addLast with null argument");
//         }

//         arrayItems_[rear_] = item;
//         rear_ = (rear_ + 1) % arrayItems_.length;
//         size_ = size_ + 1;

//         ensureCapacity();
//     }

//     // remove and return the item from the front
//     public Item removeFirst() {
//         if (isEmpty()) {
//             throw new NoSuchElementException("removeFirst when deque is empty");
//         }

//         Item item = arrayItems_[front_];
//         arrayItems_[front_] = null;
//         front_ = (front_ + 1) % arrayItems_.length;
//         size_ = size_ - 1;

//         shrinkIfNeeded();

//         return item;
//     }

//     // remove and return the item from the back
//     public Item removeLast() {
//         if (isEmpty()) {
//             throw new NoSuchElementException("removeLast when deque is empty");
//         }

//         rear_ = (rear_ - 1 + arrayItems_.length) % arrayItems_.length;
//         Item item = arrayItems_[rear_];
//         arrayItems_[rear_] = null;
//         size_ = size_ - 1;

//         shrinkIfNeeded();

//         return item;
//     }

//     private void ensureCapacity() {
//         if (size_ == arrayItems_.length) {
//             int newCapacity = arrayItems_.length * GROW_FACTOR;
//             resizeArray(newCapacity);
//         }
//     }

//     private void shrinkIfNeeded() {
//         if (size_ > 0 && size_ <= arrayItems_.length * SHRINK_THRESHOLD) {
//             int newCapacity = Math.max(DEFAULT_CAPACITY, arrayItems_.length / GROW_FACTOR);
//             resizeArray(newCapacity);
//         }
//     }

//     private void resizeArray(int newCapacity) {
//         Item[] newArray = (Item[]) new Object[newCapacity];
//         for (int i = 0; i < size_; ++i) {
//             newArray[i] = arrayItems_[(front_ + i) % arrayItems_.length];
//         }
//         front_ = 0;
//         rear_ = size_;
//         arrayItems_ = newArray;
//     }

//     private class DequeIterator implements Iterator<Item> {

//         private int current_ = front_;

//         @Override
//         public boolean hasNext() {
//             return current_ != rear_;
//         }

//         @Override
//         public Item next() {
//             if (!hasNext()) {
//                 throw new NoSuchElementException("There are no more items to return");
//             }
//             Item item = arrayItems_[current_];
//             current_ = (current_ + 1) % arrayItems_.length;
//             return item;
//         }

//         @Override
//         public void remove() {
//             throw new UnsupportedOperationException("Unimplemented");
//         }
//     }

//     // return an iterator over items in order from front to back
//     public Iterator<Item> iterator() {
//         return new DequeIterator();
//     }

//     // unit testing (required)
//     public static void main(String[] args) {
//         Deque<Integer> deque = new Deque<>();
//         for (int i = 0; i < 10; ++i) {
//             deque.addFirst(i);
//         }

//         Iterator<Integer> iterator = deque.iterator();
//         while (iterator.hasNext()) {
//             StdOut.println(iterator.next());
//         }
//     }

// }