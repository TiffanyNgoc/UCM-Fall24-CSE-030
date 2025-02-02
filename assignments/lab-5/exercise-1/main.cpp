#include <iostream>
#include <sstream>
#include <string>
#include "Queue.h"


using namespace std;

struct Message{
    string content;
    int attempts;

    Message (string content = "", int attempts = 0) : content(content), attempts(attempts) {}

    bool send(){
        attempts--;
        return attempts <= 0;
    }
};

struct MessageQueue{
    Queue<Message> q;

    MessageQueue(){

    }

    void add(const Message& m){
        q.enqueue(m);
    }

    void process(){
        while (!q.isEmpty()){
            Message curr = q.dequeue();
            if (curr.send()){
                cout << curr.content << " was sent" << endl;
            }
            else{
                cout << curr.content << " failed" << endl;
                q.enqueue(curr);
            }
        }
    }
};

int main() {

    MessageQueue mq;
    
    string line;
    while (getline(cin, line)){
        stringstream ss(line);

        string text;
        getline(ss, text, ',');
        string attempts;
        getline(ss, attempts);
        mq.add(Message(text, stoi(attempts)));
    }

    mq.process();

    cout << "Done..." << endl;
    
    return 0;
}