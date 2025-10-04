#include <iostream>
using namespace std;

struct Node {
    int data;       // value of the node
    Node* next;     // pointer to next node
    Node(int d) : data(d), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;   // start of the list
public:
    LinkedList() : head(nullptr) {} 
    void insertAtBeginning(int value) {
    Node* node = new Node(value);
    node->next = head;   // link new node to current head
    head = node;         // move head to new node
}
void insertAtEnd(int value) {
    Node* node = new Node(value);
    if (head == nullptr) {
        head = node;   // if list empty, new node is head
        return;
    }
    Node* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = node;  // link last node to new node
}
void insertAtPosition(int value, int pos) {
    if (pos == 0) {
        insertAtBeginning(value);
        return;
    }
    Node* cur = head;
    for (int i = 0; cur != nullptr && i < pos - 1; i++) {
        cur = cur->next;
    }
    if (cur == nullptr) {
        insertAtEnd(value);  // if position too big, insert at end
        return;
    }
    Node* node = new Node(value);
    node->next = cur->next;
    cur->next = node;
}
bool deleteFromBeginning(int* removedValue = nullptr) {
    if (head == nullptr) return false;   // empty list
    Node* temp = head;
    if (removedValue) *removedValue = temp->data;
    head = head->next;                   // move head forward
    delete temp;                         // free memory
    return true;
}
void display() const {
    Node* cur = head;
    while (cur) {
        cout << cur->data;
        if (cur->next) cout << " -> ";
        cur = cur->next;
    }
    cout << "\n";
}
~LinkedList() {
    Node* cur = head;
    while (cur) {
        Node* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
}
};
int main()
{
	
    LinkedList list;

    const int ID_NORMAL_1 = 101;
    const int ID_NORMAL_2 = 102;
    const int ID_NORMAL_3 = 103;
    const int ID_EMERGENCY = 999;
    const int ID_SPECIAL_BOOKING = 555;

    cout << "--- Operations on Linked List ---\n\n";

   
    list.insertAtEnd(ID_NORMAL_1);
    list.insertAtEnd(ID_NORMAL_2);
    list.insertAtEnd(ID_NORMAL_3);
    cout << "Initial List after adding Node:\n";
    list.display();
    cout << "\n";

    
    list.insertAtBeginning(ID_EMERGENCY);
    cout << "After adding an Node at beginning:\n";
    list.display();
    cout << "\n";

    
    try {
        list.insertAtPosition(ID_SPECIAL_BOOKING, 2);
        cout << "After inserting Node at some position 2:\n";
        list.display();
    }  
	    catch (const out_of_range& e) {
        cerr << "Error inserting at position: " << e.what() << "\n";
    }
    cout << "\n";

    
    int removed;
    if (list.deleteFromBeginning(&removed)) {
        cout << "After deleting first Node :\n";
        list.display();
    }  
	    else {
        cout << "Queue was empty, no Node added.\n";
    }
    cout << "\n--- Simulation End ---\n";

    return 0;

}