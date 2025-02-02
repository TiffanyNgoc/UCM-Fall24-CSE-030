#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <ostream>
#include "ArrayList.h"

struct Edge;

struct Vertex {
    std::string data;
    ArrayList<Edge*> edgeList;

    Vertex(std::string data){
        this->data = data;
    }
};

inline std::ostream& operator<<(std::ostream& os, Vertex* v){
    os << v->data;

    return os;
}

struct Edge{
    Vertex* from;
    Vertex* to;
    int weight;

    Edge(Vertex* from, Vertex* to, int weight){
        this->from = from;
        this->to = to;
        this->weight = weight;
    }
};

inline std::ostream& operator<<(std::ostream& os, Edge* e){
    os << "(" << e->from << ", " << e->to << ") - " << e->weight;

    return os;
}

struct Graph {
    ArrayList<Vertex*> vertices;

    void addVertex(Vertex* v){
        vertices.append(v);
    }

    void addEdge(Vertex* x, Vertex* y, int w){
        x->edgeList.append(new Edge(x, y, w));
        y->edgeList.append(new Edge(y, x, w));
    }

    void addDirectedEdge(Vertex* x, Vertex* y, int w){
        x->edgeList.append(new Edge(x, y, w));
    }

};

inline std::ostream& operator<<(std::ostream& os, const Graph& g){
    for (int i = 0; i < g.vertices.size(); i++){
        os << g.vertices[i]->edgeList << std::endl;
    }

    return os;
}

struct Waypoint{
    Waypoint* parent;
    Vertex* vertex;
    ArrayList<Waypoint*> children;
    int partialCost;
    int weight;

    Waypoint(Vertex* v){
        parent = nullptr;
        vertex = v;
        weight = 0;
        partialCost = 0;
    }


    void expand(){
        for (int i = 0; i < vertex->edgeList.size(); i++){
            Waypoint* temp = new Waypoint(vertex->edgeList[i]->to);
            temp->parent = this;
            temp->weight = vertex->edgeList[i]->weight;
            temp->partialCost = partialCost + vertex->edgeList[i]->weight;
            children.append(temp);
        }
    }
};

inline std::ostream& operator<<(std::ostream& os, Waypoint* wp){
    std::string p = "null";
    if (wp->parent != nullptr){
        p = wp->parent->vertex->data;
    }

    os << p << " -> " << wp->vertex->data;

    return os;
}

#endif