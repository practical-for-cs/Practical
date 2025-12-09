#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

class SinglyLinkedList {
    Node* head;
public:
    SinglyLinkedList() : head(nullptr) {}

    void insertAtBeginning(int x) {
        Node* temp = new Node(x);
        temp->next = head;
        head = temp;
    }

    void insertAtPosition(int x, int pos) {
        Node* temp = new Node(x);
        if (pos == 1) {
            temp->next = head;
            head = temp;
            return;
        }
        Node* curr = head;
        for (int i = 1; i < pos - 1 && curr; ++i) curr = curr->next;
        if (!curr) return;
        temp->next = curr->next;
        curr->next = temp;
    }

    void removeFromBeginning() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void removeFromPosition(int pos) {
        if (!head) return;
        if (pos == 1) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* curr = head;
        for (int i = 1; i < pos - 1 && curr; ++i) curr = curr->next;
        if (!curr || !curr->next) return;
        Node* temp = curr->next;
        curr->next = temp->next;
        delete temp;
    }

    Node* search(int x) {
        Node* curr = head;
        while (curr) {
            if (curr->data == x) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    SinglyLinkedList list;
    list.insertAtBeginning(10);
    list.insertAtBeginning(20);
    list.insertAtPosition(30, 2);
    list.display();
    list.removeFromPosition(2);
    list.display();
    Node* found = list.search(10);
    if (found) cout << "Found: " << found->data << endl;
}
