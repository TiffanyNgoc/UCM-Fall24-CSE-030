#include <iostream>
#include "Stack.h"

using namespace std;

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int eval(int x, int y, char op){
    if (op == '+'){
        return x + y;
    }
    else if (op == '-'){
        return x - y;
    }
    else if (op == '*'){
        return x * y;
    }
    else{
        return x / y;
    }
}

int evaluateRPN(std::string expression){
    Stack<int> s;
    std::string curr = "";
    for (int i = 0; i < expression.length(); i++){
        if (expression[i] == ' '){
            if (curr != ""){
                s.push(stoi(curr)); 
                curr = "";
            }
        }
        else{
            if (!isOperator(expression[i])){
                curr += expression[i];
            }
            else{
                int rhs = s.pop();
                int lhs = s.pop();
                s.push(eval(lhs, rhs, expression[i]));
            }
        }
    }

    return s.pop();
}


int main(int argc, char* argv[]){
    
    //string expression = "12 7 2 + -"; // This is 12 - (7 + 2) = 3
    string expression = "1 2 3 + 4 5 * + 6 7 - 8 9 * + 10 11 / * 12 13 14 + 15 16 * + 17 18 - 19 20 * + 21 22 / * 23 24 25 + 26 27 * + 28 29 - 30 31 * + 32 33 / * 34 35 36 + 37 38 * + 39 40 - 41 42 * +";

    int answer = evaluateRPN(expression);

    cout << answer << endl;

    return 0;

    return 0;
}