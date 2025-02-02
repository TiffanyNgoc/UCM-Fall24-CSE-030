#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"
#include <stdexcept>
template <class T>
class Queue;

template <class T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& q);


template <class T>
class Queue{
private:
    LinkedList<T> list; // Use LinkedList to store elements of the queue

public:
    // Add an element to the end of the queue
    void enqueue(T item) {
        list.append(item);
    }

    // Remove the front element from the queue and return it
    T dequeue() {
        if (list.isEmpty()) {
            throw std::logic_error("Queue is empty. Cannot dequeue");
        }
        return list.removeFirst();
    }

    // Get the front element of the queue without removing it
    T peek() const{
        return list.peek();
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return list.isEmpty();
    }

    // Get the number of elements in the queue
    int length() const {
        return list.size();
    }
    
    // Overload the << operator to print the queue
    friend std::ostream& operator<<<>(std::ostream& os, const Queue& q);
};

// Overload the << operator to print the queue
template <class T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& q){
    os << q.list;
    return os;
}

#endif