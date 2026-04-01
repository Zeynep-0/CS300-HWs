/*
#include "stack.h"

template <class Atype> Stack<Atype>::Stack() :top(nullptr){}

template<class Atype> Stack<Atype>::~Stack() {
	while (top != nullptr) {
		StackNode* temp = top;
		top = top->next;
		delete temp;
	}
}

template <class Atype> Atype Stack<Atype>::pop() {
	StackNode* popTop = top;
	top = top->next;
	Atype value = popTop->value;
	delete popTop;
	return value;
	
}
template <class Atype> void Stack<Atype>::push(Atype val) {
	StackNode* newTop = new StackNode(val);
	newTop->next = top;
	top = newTop;
}
template <class Atype>bool Stack<Atype>::isEmpty() {
	if (top == nullptr) {
		return true;
	}
	return false;
}
template class Stack<BoardNodes>;
*/
