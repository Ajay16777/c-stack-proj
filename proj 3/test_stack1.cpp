#include <iostream>
#include <cstdlib>
#include "Stack.h"

using namespace std;
using namespace cop4530;

int main() {
    Stack<int> intsta;

    cout << "inserting 10 elements" << endl;
    for (unsigned int i = 0; i < 10; ++i) 
	intsta.push(i);

    cout << "Size: " << intsta.size() << endl;

    cout << "emptying the stack" << endl;
    while (!intsta.empty()) {
	cout << intsta.top() << " ";
	intsta.pop();
    }
    cout << endl;

    cout << "Size: " << intsta.size() << endl;

    cout << "inserting 10 elements" << endl;

    for (unsigned int i = 0; i < 10; ++i) 
	intsta.push(i);

    Stack<int> intsta1(intsta);
    Stack<int> intsta2;
    intsta2 = intsta;

	if (intsta1.size() != intsta2.size()) {
		cout << "wrong" << endl;
	} else {
		while (!intsta1.empty()) {
			if (intsta1.top() != intsta2.top()) {
				cout << "wrong" << endl;
				break;
			}
			intsta1.pop();
			intsta2.pop();
		}
		if (intsta1.empty()) {
			cout << "copy constructor and assignment operator are OK" << endl;
		}
	}
    // if (intsta1 == intsta2)
    // 	cout << "Copy constructor and assignment operators are OK" << endl;
    // else
    // 	cout << "ERROR: copy constructor or assignment operator is wrong" << endl;

    return(EXIT_SUCCESS);
}
