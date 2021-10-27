#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <vector>

namespace cop4530{
	template <typename T>
	class Stack{
	private:
		std::vector<T> v;

	public:
		Stack(); // default constructor		
		~Stack(); // deconstructor
		Stack(const Stack<T> &); // copy constructor
		Stack(Stack<T> &&); // move constructor
		Stack<T> & operator=(const Stack<T> &); //copy assignment operator
		Stack<T> & operator=(Stack<T> &&); // move assignment operator
		bool empty() const;
		void push(const T& x);
		void push(T && x);
		void pop();
		T& top();
		const T& top() const;
		int size() const; // holds size of vector
		
	};
	
#include "stack.hpp"
} // end of cop4530 namespace

#endif