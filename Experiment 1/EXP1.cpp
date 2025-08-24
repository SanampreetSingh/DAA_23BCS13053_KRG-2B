#include <iostream>
using namespace std;

template <typename T>
class Stack {
    int topIndex;
    int capacity;
    T* arr;

public:
    Stack(int size) {
        capacity = size;
        arr = new T[capacity];
        topIndex = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == capacity - 1;
    }

    void push(const T& data) {
        if (isFull()) {
            cout << "Error: Stack Overflow! Cannot push " << data << endl;
            return;
        }
        arr[++topIndex] = data;
        cout << data << " pushed into stack." << endl;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Error: Stack Underflow! Nothing to pop." << endl;
            return;
        }
        cout << arr[topIndex--] << " popped from stack." << endl;
    }

    T peek() const {
        if (isEmpty()) {
            cout << "Error: Stack is Empty. No top element." << endl;
            return T();
        }
        return arr[topIndex];
    }
};

int main() {
    Stack<int> s(5);

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top element: " << s.peek() << endl;

    s.pop();
    cout << "Top element after pop: " << s.peek() << endl;

    s.pop();
    s.pop();
    s.pop();

    return 0;
}
