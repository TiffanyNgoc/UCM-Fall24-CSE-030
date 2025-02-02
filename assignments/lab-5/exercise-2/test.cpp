#include <igloo/igloo.h>
#include <stdexcept>
#include <unistd.h>
#include "Stack.h"

using namespace igloo;

Context(TestStack){
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
        Stack<int> s_int;
        Assert::That(s_int.length(), Equals(0));
    }

    Spec(TestPopFromEmpty){
        Stack<int> s_int;
        AssertThrows(std::logic_error, s_int.pop());
    }

    Spec(TestPeekFromEmpty){
        Stack<int> s_int;
        AssertThrows(std::logic_error, s_int.peek());
    }

    Spec(TestPushAndPeek){
        Stack<int> s_int;
        s_int.push(17);
        Assert::That(s_int.peek(), Equals(17));
        Assert::That(s_int.length(), Equals(1));
    }

    Spec(TestPushAndPop){
        Stack<int> s_int;
        s_int.push(17);
        Assert::That(s_int.pop(), Equals(17));
        Assert::That(s_int.length(), Equals(0));
    }

    Spec(TestMultiplePushAndPop){
        Stack<int> s_int;
        Assert::That(s_int.length(), Equals(0));

        s_int.push(17);
        Assert::That(s_int.length(), Equals(1));

        s_int.push(8);
        Assert::That(s_int.length(), Equals(2));

        s_int.push(93);
        Assert::That(s_int.length(), Equals(3));

        Assert::That(s_int.pop(), Equals(93));
        Assert::That(s_int.pop(), Equals(8));
        Assert::That(s_int.pop(), Equals(17));

        Assert::That(s_int.length(), Equals(0));
    }
};

int main(int argc, const char* argv[]){
    TestRunner::RunAllTests(argc, argv);
}