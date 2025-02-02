#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"
#include <stdexcept>
template <class T>
class Stack;

template <class T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& q);


template <class T>
class Stack{
private:
    LinkedList<T> list; // Use LinkedList to store elements of the stack

public:
    // Push an element onto the stack
    void push(T item) {
        list.prepend(item);
    }

    // Pop the top element from the stack and return it
    T pop() {
        if (list.isEmpty()) {
            throw std::logic_error("Stack is empty. Cannot pop.");
        }
        return list.removeFirst();
    }

    // Get the top element of the stack without removing it
    T peek() const {
        return list.peek();
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return list.isEmpty();
    }

    // Get the number of elements in the stack
    int length() const {
        return list.size();
    }

    // Overload the << operator to print the stack
    friend std::ostream& operator<<<>(std::ostream& os, const Stack& s);
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& s){
    os << s.list;
    return os;
}

#endif