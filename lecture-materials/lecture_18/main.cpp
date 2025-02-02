#include <iostream>
#include <climits>
#include "Graph.h"

using namespace std;


int main(){

    Vertex* sfo = new Vertex("San Francisco");
    Vertex* nyc = new Vertex("New York");
    Vertex* rio = new Vertex("Rio De Janeiro");
    Vertex* paris = new Vertex("Paris");
    Vertex* joburg = new Vertex("Johannesburg");
    Vertex* moscow = new Vertex("Moscow");
    Vertex* sydney = new Vertex("Sydney");
    Vertex* tokyo = new Vertex("Tokyo");
    Vertex* beijing = new Vertex("Beijing");

    Graph g;
    g.addVertex(sfo);
    g.addVertex(nyc);
    g.addVertex(rio);
    g.addVertex(paris);
    g.addVertex(joburg);
    g.addVertex(moscow);
    g.addVertex(sydney);
    g.addVertex(tokyo);
    g.addVertex(beijing);

    g.addEdge(sfo, nyc, 6);
    g.addEdge(nyc, rio, 13);
    g.addEdge(nyc, joburg, 14);
    g.addEdge(nyc, paris, 7);
    g.addEdge(nyc, moscow, 15);
    g.addEdge(nyc, sydney, 40);
    g.addEdge(rio, paris, 11);
    g.addEdge(rio, beijing, 18);
    g.addEdge(paris, sydney, 17);
    g.addEdge(joburg, tokyo, 16);
    g.addEdge(joburg, sydney, 11);
    g.addEdge(sydney, tokyo, 10);
    g.addEdge(tokyo, beijing, 3);
    g.addEdge(beijing, moscow, 8);


    ArrayList<Waypoint*> frontier;
    ArrayList<string> seen;

    Waypoint* start = new Waypoint(sfo);

    Vertex* destination = beijing;

    frontier.append(start);
    seen.append(start->vertex->data);

    Waypoint* result = nullptr;
    bool found = false;
    
    while (frontier.size() > 0){
        result = frontier.removeFirst();

        if(result->vertex == destination){
            found = true;
            break;
        }

        result->expand();

        for (int i = 0; i < result->children.size(); i++){
            if (!seen.search(result->children[i]->vertex->data) || true){
                frontier.append(result->children[i]);

                for (int j = frontier.size()-1; j > 0; j--){
                    if (frontier[j]->partialCost < frontier[j-1]->partialCost){
                        Waypoint* temp = frontier[j];
                        frontier[j] = frontier[j-1];
                        frontier[j-1] = temp;
                    }
                }

                seen.append(result->children[i]->vertex->data);
            }
        }
    }

    if (found){
        cout << "We found a path" << endl;
        Waypoint* temp = result;
        while (temp != nullptr){
            cout << temp->vertex->data << " " << temp->partialCost << endl;
            temp = temp->parent;
        }
    }
    else{
        cout << "There is no path" << endl;
    }
    return 0;
}