#include <iostream>
#include <string>
#include <climits>
#include "ArrayList.h"

using namespace std;

struct Edge;

struct Vertex {
    string data;
    ArrayList<Edge*> edgeList;

    Vertex(string data){
        this->data = data;
    }
};

ostream& operator<<(ostream& os, Vertex* v){
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

ostream& operator<<(ostream& os, Edge* e){
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

ostream& operator<<(ostream& os, const Graph& g){
    for (int i = 0; i < g.vertices.size(); i++){
        os << g.vertices[i]->edgeList << endl;
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

ostream& operator<<(ostream& os, Waypoint* wp){
    string p = "null";
    if (wp->parent != nullptr){
        p = wp->parent->vertex->data;
    }

    os << p << " -> " << wp->vertex->data;

    return os;
}


int main(){


    Vertex* ssb = new Vertex("SSB");
    Vertex* aoa = new Vertex("AOA");
    Vertex* cob2 = new Vertex("COB2");
    Vertex* kl = new Vertex("KL");
    Vertex* cob1 = new Vertex("COB1");
    Vertex* ssm = new Vertex("SSM");
    Vertex* se1 = new Vertex("SE1");
    Vertex* se2 = new Vertex("SE2");

    Graph g;

    g.addVertex(ssb);
    g.addVertex(aoa);
    g.addVertex(cob2);
    g.addVertex(kl);
    g.addVertex(cob1);
    g.addVertex(ssm);
    g.addVertex(se1);
    g.addVertex(se2);


    g.addEdge(ssb, aoa, 55);
    g.addEdge(ssb, cob2, 115);
    g.addEdge(ssb, kl, 135);
    g.addEdge(ssb, cob1, 85);
    g.addEdge(ssb, ssm, 100);
    g.addEdge(ssb, se1, 125);
    g.addEdge(ssb, se2, 150);

    g.addEdge(aoa, cob2, 65);
    g.addEdge(aoa, kl, 90);
    g.addEdge(aoa, cob1, 55);
    g.addEdge(aoa, ssm, 100);
    g.addEdge(aoa, se1, 130);
    g.addEdge(aoa, se2, 160);

    g.addEdge(cob2, kl, 30);
    g.addEdge(cob2, cob1, 55);
    g.addEdge(cob2, ssm, 150);
    g.addEdge(cob2, se1, 140);
    g.addEdge(cob2, se2, 170);

    g.addEdge(kl, cob1, 55);
    g.addEdge(kl, ssm, 150);
    g.addEdge(kl, se1, 125);
    g.addEdge(kl, se2, 150);

    g.addEdge(cob1, ssm, 100);
    g.addEdge(cob1, se1, 85);
    g.addEdge(cob1, se2, 120);

    g.addEdge(ssm, se1, 50);
    g.addEdge(ssm, se2, 60);

    g.addEdge(se1, se2, 30);

    ArrayList<Waypoint*> frontier;
    Waypoint* start = new Waypoint(ssb);
    start->expand();
    frontier.append(start);
    
    // The frontier should span the graph
    while (frontier.size() < g.vertices.size()){
        int min = INT_MAX;
        Waypoint* winner = nullptr;

        // Find the smallest edge from the frontier leading outside the frontier
        for (int i = 0; i < frontier.size(); i++){
            Waypoint* curr = frontier[i];
            for (int j = 0; j < curr->children.size(); j++){
                if (curr->children[j]->weight < min){
                    // We found an edge smaller than the current minimum
                    // But does it lead inside or outside the frontier
                    bool found = false;
                    for (int k = 0; k < frontier.size(); k++){
                        if (frontier[k]->vertex->data == curr->children[j]->vertex->data){
                            found = true;
                            break;
                        }
                    }
                    // The vertex that the smallest edge leads to is not in the frontier
                    // So we update our current minimum
                    if (!found){
                        winner = curr->children[j];
                        min = curr->children[j]->weight;
                    }
                }
            }
        }
        // We now have the smallest edge originating in the frontier, leading outside the frontier
        winner->expand();
        frontier.append(winner);
        
    }

    cout << frontier << endl;

    int totalCost = 0;
    for (int i = 0; i < frontier.size(); i++){
        totalCost += frontier[i]->weight;
    }

    cout << totalCost << endl;

    return 0;
}