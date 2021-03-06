#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <sstream>
#include "stack.h"

using namespace std;
using namespace cop4530;

//  Contains structure for each space separated
//  variable
struct OP{
    string str;
    int precedence;

    //Constructors
    OP() : str(""), precedence(0){}
    OP(string s): str(s){
        //Set precedence based on operator
        if(str.length() == 1){
            char c = str[0];
            if(c == '+' || c == '-')
                precedence = 2;
            else if(c == '*' || c == '/')
                precedence = 3;
            else if(c == '(' || c == ')')
                precedence = 1;
            else precedence = 0;
        }
        else
            precedence = 0;
    }
};

//Function prototypes
void infix2postfix(std::vector<OP> input);
bool IsOperator(char c);
bool IsOperandNotNumerical(string s);
bool IsOperand(char c);
void EvaluatePostfix(std::vector<OP> exp);
std::string CalcValues(OP operand1, OP operand2, OP oper);

//Converts infix to postfix and evaluates
int main()
{
    //Member variables
    char c; //Read input
    std::vector<OP> input;  //Vector of space separated strings
    string exp; //Expression str
    bool running = true; //Loop var

    while(running){
        std::cout << "Calculating infix expressions: "<<endl;

        //Get character and add to vector
        while(cin.get(c) && running){
            if(exp == "exit"){
                running = false;
                break;
            }
            else{
                if(c == '\n'){
                    //Push back the expression string to vector, clear
                    input.push_back(exp);
                    infix2postfix(input);
                    exp = "";
                    input.clear();
                    
                }
                else if(c == ' '){
                    //Add expressino to vector on space
                    input.push_back(OP(exp));
                    exp = "";
                }
                else if(c == '(' || c == ')'){
                    //SPecial case push parenthesis to vector
                    string x;
                    x+=c;
                    input.push_back(OP(x));
                }
                else if(c == '\0'){
                    running = false;
                }
                else{
                    //Add string together
                    exp+= c;
                }
            }
        }
        running = false;
    }

    return (EXIT_SUCCESS);
}



//Member ISOperator returns whether a string is an operator
bool IsOperator(string s){
    return(s == "+" || s == "-" || s == "/" || s == "*");
}

//Returns whether an operator is a 'true' variable or not
bool IsOperandNotNumerical(string s){
    for(std::string::iterator it = s.begin(); it != s.end(); ++it){
        char c = *it;
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_')){
            return false;
        }
    }
    return true;
}

//Returns whether or not a string is an operand
bool IsOperand(string s){
    //Check for length of 1 against possible operators
    if(s.length() == 1){
        char c = s[0];
        return((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_'));
    }
    else{
        return true;
    }
}

//Converts space separated strings from infix to postfix notation
void infix2postfix(std::vector<OP> input){
    //Member variables
    Stack<OP> operators;
    OP lastInput;
    std::vector<OP> expression;
    std::cout << "\ninfix exp: ";
	// print input
	for(std::vector<OP>::iterator it = input.begin(); it != input.end(); ++it){
		std::cout << (*it).str << " ";
	}
	std::cout << std::endl;


    //Loop through every space separated string
    for(std::vector<OP>::iterator itr = input.begin(); itr != input.end(); ++itr){
        OP op = *itr;   //space separated string

        //Print the string if it is an operand
        if(IsOperand(op.str)){
            if(op.str.length() > 0)
            expression.push_back(op.str);
        }

        //If input is "(" push it into stack
        if(op.str == "("){
            operators.push(op);
        }
        else if(IsOperator(op.str)){
            //If input is an operator, print top of stack to output and pop until
                //empty, a ( is at the top or lower precedence at top of stack
            while(!operators.empty() && operators.top().str != "(" && (operators.top().precedence >= op.precedence)){
                expression.push_back(operators.top().str);
                operators.pop();
            }
            operators.push(op);
        }
        else if(op.str == ")"){
            
                //Print top of stack and output and pop stack until ( is at the top
                //Empty stack
                while(!operators.empty() && operators.top().str != "("){
                    
                    expression.push_back(operators.top().str);
                    operators.pop();
                }
                operators.pop();
            
        }
        lastInput = op;
    }

    
        while(!operators.empty()){
            
            expression.push_back(operators.top().str);
            operators.pop();
        }
        
    
    //Evaulate postfix
    EvaluatePostfix(expression);
}

//Evaulate postfix expression
// IF all the operands are numeric values calc expression
//  Otherwise output is same as input
void EvaluatePostfix(std::vector<OP> exp){
    //Member variables
    Stack<string> operand;
    string sub;
    bool variable = false;

    //Loop through every expression in postfix
    for(std::vector<OP>::iterator itr = exp.begin(); itr != exp.end(); ++itr){
        //Sub member variables given string
        OP input = *itr;
        sub+= input.str + " ";  //Add to output expression

        //If the expression does not contain a numerical value
        if(!variable && IsOperandNotNumerical(input.str)){
            //If operand add to stack
            if(IsOperand(input.str)){
                operand.push(input.str);
            }
            else if(IsOperator(input.str)){
            
                    OP oper1 = operand.top();
                    operand.pop();
                    OP oper2 = operand.top();
                    operand.pop();

                    string result = CalcValues(oper2,oper1,input.str);
                    operand.push(result);
                    //Push result to stack
                // }
            }
        }
        else{
            variable = true;
        }
    }
    //If the expression contains only numerical values, oputput proper string
    if(!variable){
        if(operand.size() == 1){
            std::cout << "Postfix exp: " << sub << "= " << operand.top() << endl;}
        else std::cout << "Postfix exp: 0" << endl;
    }
    else{
        //Output postfix if expression has variable
        std::cout << "Postfix exp: " << sub << "= " << sub << endl;
    }
}

//Calculate values from a string to int
std::string CalcValues(OP operand1, OP operand2, OP oper)
{
    //Variables
    std::stringstream ss;
   int left = 0.0, right = 0.0;

    //Convert strings to int
    left = atof(operand1.str.c_str());
    right = atof(operand2.str.c_str());

    //evaulate expression based on operator
    if(oper.str == "*")
        left *= right;
    else if(oper.str == "/"){
        if(right != 0)
            left /= right;
        
    }
    else if(oper.str == "+")
        left += right;
    else if(oper.str == "-")
        left -= right;

    //Return string
    ss << left;
    return ss.str();
}
// worst-case time complexity of CalcValues is O(n)



