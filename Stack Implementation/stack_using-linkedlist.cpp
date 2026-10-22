// Stack implementation using linked list (struct-class)
// created: 22 oct 2026
#include <iostream>
#include <stdexcept>

using namespace std;

// Define the Node structure
struct Node {
    int data;
    Node* next;
    
    Node(int value) : data(value), next(nullptr) {}
};

// Stack Class
class Stack {
private:
    Node* top; // Pointer to the top node of the stack
    int stackSize;

public:
    // Constructor
    Stack() : top(nullptr), stackSize(0) {}

    // Destructor to prevent memory leaks
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Push: Add an element to the top of the stack
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top; // Link the new node to the current top
        top = newNode;       // Update top pointer to the new node
        stackSize++;
    }

    // Pop: Remove and return the top element
    int pop() {
        if (isEmpty()) {
            throw underflow_error("Stack Underflow: Cannot pop from an empty stack.");
        }
        
        Node* temp = top;        // Temporarily store the current top node
        int poppedValue = top->data;
        top = top->next;         // Move top to the next node
        delete temp;             // Deallocate the old top node memory
        stackSize--;
        
        return poppedValue;
    }

    // Peek/Top: Return the top element without removing it
    int peek() const {
        if (isEmpty()) {
            throw underflow_error("Stack is empty: Cannot peek.");
        }
        return top->data;
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return top == nullptr;
    }

    // Return the current size of the stack
    int size() const {
        return stackSize;
    }
};

// Main function to demonstrate the Stack
int main() {
    Stack myStack;

    cout << "Pushing elements: 10, 20, 30\n";
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    cout << "Current Stack Size: " << myStack.size() << "\n";
    cout << "Top element (Peek): " << myStack.peek() << "\n\n";

    cout << "Popping elements:\n";
    while (!myStack.isEmpty()) {
        cout << "Popped: " << myStack.pop() << "\n";
    }

    // Attempting to pop from an empty stack to test exception handling
    try {
        myStack.pop();
    } catch (const std::underflow_error& e) {
        cout << "\nCaught expected exception: " << e.what() << "\n";
    }

    return 0;
}
