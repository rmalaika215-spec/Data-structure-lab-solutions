#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int ID;
    Student* next;

    Student(string n, int id) {
        name = n;
        ID = id;
        next = nullptr;
    }
};

class Code_of_Thon {
private:
    Student* head;

public:
    Code_of_Thon() : head(nullptr) {}

    void Add_Student(string n, int id) {
        Student* student = new Student(n, id);
        if (head == nullptr) {
            head = student;
            return;
        }
        Student* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = student;
    }

    bool Serve_Student(string* removedName = nullptr, int* removedID = nullptr) {
        if (head == nullptr) return false;
        Student* temp = head;
        if (removedName) *removedName = temp->name;
        if (removedID) *removedID = temp->ID;
        head = head->next;
        delete temp;
        return true;
    }

    bool Student_Leaves(int position, string* removedName = nullptr, int* removedID = nullptr) {
    if (head == nullptr) {
        cout << "Queue is empty, nothing to delete." << endl;
        return false;
    }
    if (position < 0) {
        cout << "Invalid position." << endl;
        return false;
    }
   
    Student* temp = head;
    for (int i = 0; temp != nullptr && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr) {
        cout << "Position is out of bounds." << endl;
        return false;
    }
    Student* nodeToDelete = temp->next;
    if (removedName) *removedName = nodeToDelete->name;
    if (removedID) *removedID = nodeToDelete->ID;
    temp->next = nodeToDelete->next;
    delete nodeToDelete;
    return true;
}


    int Count_Student() {
        int count = 0;
        Student* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void Display_Queue() {
        Student* temp = head;
        while (temp != nullptr) {
            cout << temp->name << "(" << temp->ID << ") -> ";
            temp = temp->next;
        }
        cout << "Null" << endl;
    }
};

int main() {
    Code_of_Thon queue;
    int id;
	int pos;
    string name;
    int choice;

    do {
        cout << "\n===== Code a Thon =====\n";
        cout << "1. Add student to queue\n";
        cout << "2. Serve student from beginning\n";
        cout << "3. A student leaves \n";
        cout << "4. Display queue\n";
        cout << "5. Count students in queue\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Student's name: ";
                cin >> name;
                cout << "Enter Student's ID: ";
                cin >> id;
                queue.Add_Student(name, id);
                cout << name << " has been added to the queue." << endl;
                break;

            case 2: {
                string removedName;
                int removedID;
                if (queue.Serve_Student(&removedName, &removedID)) {
                    cout << removedName << " (ID: " << removedID << ") has been served." << endl;
                } else {
                    cout << "Queue is empty, no student to serve." << endl;
                }
                break;
            }

            case 3: {
                cout << "Enter Student's position to leave (0-based index): ";
                cin >> pos;
                string removedName;
                int removedID;
                if (queue.Student_Leaves(pos, &removedName, &removedID)) {
                    cout << removedName << " (ID: " << removedID << ") has left the queue." << endl;
                }
                break;
}


            case 4:
                cout << "Current queue: ";
                queue.Display_Queue();
                break;

            case 5:
                cout << "Number of students in queue: " << queue.Count_Student() << endl;
                break;

            case 6:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}