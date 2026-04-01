
#ifndef STACK_H
#define STACK_H


#include <iostream>
using namespace std;
//Author: Zeynep Taskin 33851
//Date: 28.10.2024 
//Header file of the stack class with the implementations of the member functions.

template <class Atype> // stack class template
class Stack {
private:
	struct StackNode { // node structure for the stack
	Atype value;
	StackNode* next;
	StackNode(Atype v) { // constructor for the structure
		next = nullptr;
		value = v;
	}
	};
	StackNode* top; // pointer to the top of the stack
public:
    Atype pop(); // member function to pop out the top of the stack
	void push(Atype val); // member function to add to the stack
	Stack(); // constructor
	~Stack(); // destructor
	bool isEmpty(); // member function to check if the stack is empty
};

template <class Atype> Stack<Atype>::Stack() :top(nullptr) {} // constructor implementation

template<class Atype> Stack<Atype>::~Stack() { // destructor implementation
	while (top != nullptr) { // until stack is empty
		StackNode* temp = top; // get the top node
		top = top->next; // go to the next node
		delete temp; // delete the previous top node
	}
}

template <class Atype> Atype Stack<Atype>::pop() { // implementation of the pop member function
	StackNode* popTop = top; // get the top node
	top = top->next; // set the top node to the next node
	Atype value = popTop->value; // get the value of the previous top node
	delete popTop; // delete the previous top node
	return value; // return the value

}
template <class Atype> void Stack<Atype>::push(Atype val) { // implementation of the push member function
	StackNode* newTop = new StackNode(val); // create a new top node with the given value
	// set the new top
	newTop->next = top;
	top = newTop;
}
template <class Atype>bool Stack<Atype>::isEmpty() { // implementation of the isempty member function
	if (top == nullptr) { // check if the top is nullptr
		return true;
	}
	return false;
}
#endif