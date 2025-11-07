#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node* prev;
};

class DoublyLL {
    Node* head;
public:
    DoublyLL() {
        head = NULL;
    }

    void insertAtBeg(int val) {
        Node* newNode = new Node{val, head, NULL};
        if (head)
            head->prev = newNode;
        head = newNode;
    }

    void insertAtEnd(int val) {
        Node* newNode = new Node{val, NULL, NULL};
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }

    void DelAtBeg() {
        if (!head) {
            cout << "List is Empty\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head)
            head->prev = NULL;
        delete temp;
    }

    void DelAtEnd() {
        if (!head) {
            cout << "List is Empty\n";
            return;
        }
        if (!head->next) {
            delete head;
            head = NULL;
            return;
        }
        Node* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->prev->next = NULL;
        delete temp;
    }

    void Display() {
        Node* temp = head;
        while (temp) {
            cout << temp->val << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
};

struct CNode {
    int val;
    CNode* next;
};

class CircularLL {
    CNode* last;
public:
    CircularLL() {
        last = NULL;
    }

    void InsertAtBeg(int val) {
        CNode* newNode = new CNode{val, NULL};
        if (!last) {
            last = newNode;
            last->next = last;
        } else {
            newNode->next = last->next;
            last->next = newNode;
        }
    }

    void InsertAtEnd(int val) {
        CNode* newNode = new CNode{val, NULL};
        if (!last) {
            last = newNode;
            last->next = last;
        } else {
            newNode->next = last->next;
            last->next = newNode;
            last = newNode;
        }
    }

    void DelAtBeg() {
        if (!last) {
            cout << "List is Empty\n";
            return;
        }
        CNode* temp = last->next;
        if (last == temp) {
            delete last;
            last = NULL;
        } else {
            last->next = temp->next;
            delete temp;
        }
    }

    void DelAtEnd() {
        if (!last) {
            cout << "List is Empty\n";
            return;
        }
        CNode* temp = last->next;
        if (last == temp) {
            delete last;
            last = NULL;
        } else {
            while (temp->next != last)
                temp = temp->next;
            temp->next = last->next;
            delete last;
            last = temp;
        }
    }

    void Display() {
        if (!last) {
            cout << "List is Empty\n";
            return;
        }
        CNode* temp = last->next;
        do {
            cout << temp->val << " ";
            temp = temp->next;
        } while (temp != last->next);
        cout << "\n";
    }
};

int main() {
    DoublyLL dll;
    dll.insertAtBeg(37);
    dll.insertAtEnd(28);
    dll.insertAtEnd(58);
    dll.insertAtEnd(62);
    dll.insertAtEnd(89);
    dll.insertAtEnd(43);

    cout << "Doubly Linked List: ";
    dll.Display();

    dll.DelAtBeg();
    cout << "After Deletion at Beginning: ";
    dll.Display();

    dll.DelAtEnd();
    cout << "After Deletion at End: ";
    dll.Display();

    CircularLL cll;
    cll.InsertAtBeg(37);
    cll.InsertAtEnd(28);
    cll.InsertAtEnd(58);
    cll.InsertAtEnd(62);
    cll.InsertAtEnd(89);
    cll.InsertAtEnd(43);

    cout << "Circular Linked List: ";
    cll.Display();

    cll.DelAtBeg();
    cout << "After Deletion at Beginning: ";
    cll.Display();

    cll.DelAtEnd();
    cout << "After Deletion at End: ";
    cll.Display();
    
    return 0;
}