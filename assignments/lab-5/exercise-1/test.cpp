#include <igloo/igloo.h>
#include <stdexcept>
#include <unistd.h>
#include "Queue.h"

using namespace igloo;

Context(TestQueue){
    int oldSTDOUT;
    int oldSTDERR;

    void SetUp() {
        oldSTDOUT = dup( 1 );
        oldSTDERR = dup( 2 );
        freopen( "/dev/null", "w", stdout );
        freopen( "/dev/null", "w", stderr );     
    }

    void TearDown() {
        fflush( stdout );
        fflush( stderr );
        dup2( oldSTDOUT, 1 );
        dup2( oldSTDERR, 2 );
    }

    Spec(TestCreation){
        Queue<int> q_int;
        Assert::That(q_int.length(), Equals(0));
    }

    Spec(TestDequeueFromEmpty){
        Queue<int> q_int;
        AssertThrows(std::logic_error, q_int.dequeue());
    }

    Spec(TestPeekFromEmpty){
        Queue<int> q_int;
        AssertThrows(std::logic_error, q_int.peek());
    }

    Spec(TestEnqueueAndPeek){
        Queue<int> q_int;
        q_int.enqueue(17);
        Assert::That(q_int.peek(), Equals(17));
        Assert::That(q_int.length(), Equals(1));
    }

    Spec(TestEnqueueAndDequeue){
        Queue<int> q_int;
        q_int.enqueue(17);
        Assert::That(q_int.dequeue(), Equals(17));
        Assert::That(q_int.length(), Equals(0));
    }

    Spec(TestMultipleEnqueueAndDequeue){
        Queue<int> q_int;
        Assert::That(q_int.length(), Equals(0));

        q_int.enqueue(17);
        Assert::That(q_int.length(), Equals(1));

        q_int.enqueue(8);
        Assert::That(q_int.length(), Equals(2));

        q_int.enqueue(93);
        Assert::That(q_int.length(), Equals(3));

        Assert::That(q_int.dequeue(), Equals(17));
        Assert::That(q_int.dequeue(), Equals(8));
        Assert::That(q_int.dequeue(), Equals(93));

        Assert::That(q_int.length(), Equals(0));
    }
};

int main(int argc, const char* argv[]){
    TestRunner::RunAllTests(argc, argv);
}