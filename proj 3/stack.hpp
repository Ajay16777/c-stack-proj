template <typename T>
Stack<T>::Stack(){ // default constructor	
}

template <typename T>
Stack<T>::~Stack(){ // deconstructor
	v.clear(); // clear everything out of vector. no need to use delete statement becasue did not create using new
}

template <typename T>
Stack<T>::Stack(const Stack<T> & x){ // copy constructor
	*this = x;
}
	
template <typename T>
Stack<T>::Stack(Stack<T> && x){ // move constructor
	*this = x;
}

template <typename T>
Stack<T> & Stack<T>::operator=(const Stack<T> & b){ // copy assignment operator=
	v = b.v;
	return *this;
}

template <typename T>
Stack<T> & Stack<T>::operator=(Stack<T> && b){ // move assignment operator=
	v = b.v;
	return *this;
}

template <typename T>
bool Stack<T>::empty() const{ // returns true if the Stack contains no elements, and false otherwise
	return v.empty();
}


template <typename T>
void Stack<T>::push(const T& x){ // push(add) x to vector
	v.push_back(x);
}

template <typename T>
void Stack<T>::push(T&& x){ // push(add) x to vector
	v.push_back(x);
}

template <typename T>
void Stack<T>::pop(){ // pop(remove) most recent element
	v.pop_back();
}

template <typename T>
T& Stack<T>::top(){ // return element on top
	return v.back();
}

template <typename T>
const T& Stack<T>::top() const{ // return element on top
	return v.back();
}
	
template <typename T>
int Stack<T>::size() const{ // return size of vector
	return v.size();
}

