// ====== STACK IMPLEMENTATION IN C++ ==========
// created: 7 oct 2026
#include <iostream>
#include <cctype>
#include <string>
using namespace std;

//Define stack class
class Stack {
private:
	// top element of the stack
	int top;
	int arr[100];
public:
	//constructor to init an empty stack
	Stack() { top = -1; }

	void push(int x) {
		if (top >= 99) {
			cout << "stack overflow!" << endl;
			return;
		}

		arr[++top] = x;
		cout << "Pushed " << x << " to stack\n";
	}

	int pop() {
		if (top < 0) {
			cout << "stack underflow!" << endl;
			return 0;
		}
		return arr[top--];
	}

	int peek() {
		if (top < 0) {
			cout << "stack is empty!" << endl;
			return 0;
		}
		return arr[top];
	}

	bool isEmpty() {
		return (top < 0);
	}

};

string evalPostfix(string exp) {
	Stack s;
	string text = "The final value is ";

	for (int i = 0; i < exp.length(); i++) {
		// ignore space
		if (exp[i] == ' ') continue;

		if (isdigit(exp[i])) {
			s.push(exp[i] - '0'); //convert char to int
		}
		else {
			int val1 = s.pop(); //hold right operand (-X)
			int val2 = s.pop(); //hold left operand  (X-)

			switch (exp[i]){
			case '+': cout << "'+' "; s.push(val2 + val1); break;
			case '-': cout << "'-' ";s.push(val2 - val1);  break;
			case '*': cout << "'*' ";s.push(val2 * val1);  break;
			case '/':
				if (val1 != 0) {
					cout << "'/' ";
					s.push(val2 / val1);
				}
				else {
					return "Error: division by zero!\n";
				}
				break;
			}
		}
	}
	return text + to_string(s.pop());
}

int main() {
	/*
	// Stack push-pop only, no operators
	Stack s;
	s.push(10);
	s.push(20);
	s.push(30);
	cout << "top element is: " << s.peek() << endl;
	cout << "elements present in stack: ";
	while (!s.isEmpty()) {
		cout << s.pop() << " ";
	} */

	// Stack with operators
	string expr = "12+3*4-34+-";
	cout << evalPostfix(expr) << endl;

	return 0;
}