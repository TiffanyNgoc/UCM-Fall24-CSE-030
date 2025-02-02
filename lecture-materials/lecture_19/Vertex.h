#ifndef VERTEX_H
#define VERTEX_H

#include <ostream>
#include "ArrayList.h"

template <class T>
struct Vertex;

template <class T>
struct Neighbor {
    int weight;
    Vertex<T>* location;

    Neighbor(Vertex<T>* vertex, int label) {
        location = vertex;
        weight = label;
    }
};

template <class T>
struct Vertex {
    T data;
    int degree;
    ArrayList<Vertex<T>*> adjList;
    ArrayList<Neighbor<T>> neighbors;

    Vertex() {
        adjList = nullptr;
    }

    Vertex(T value) {
        data = value;
        adjList = new ArrayList<Vertex<T>*>();
        degree = 0;
    }

    void addNeighbor(Vertex<T>* vertex, int weight) {
        degree++;
        neighbors.append(Neighbor<T>(vertex, weight));
    }

    ~Vertex() {
        delete adjList;  // Proper deletion
    }
};

template <class T>
std::ostream& operator<<(std::ostream& os, Vertex<T>& v) {
    os << "Vertex:" << std::endl;
    os << v.data << std::endl;
    os << "Neighbors:" << std::endl;
    for (int i = 0; i < v.degree; i++) {
        os << v.neighbors[i]->location->data << std::endl;
    }
    return os;
}

#endif
