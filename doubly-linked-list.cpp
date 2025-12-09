#include <iostream>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int v): data(v), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail;
public:
    DoublyLinkedList(): head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList() {
        DNode* cur = head;
        while (cur) {
            DNode* t = cur;
            cur = cur->next;
            delete t;
        }
    }

    void insertBegin(int x) {
        DNode* n = new DNode(x);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = head;
    }

    void insertEnd(int x) {
        DNode* n = new DNode(x);
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = tail;
    }

    bool removeBegin() {
        if (!head) return false;
        DNode* t = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete t;
        return true;
    }

    bool removeEnd() {
        if (!tail) return false;
        DNode* t = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete t;
        return true;
    }

    void printForward() {
        DNode* cur = head;
        while (cur) {
            cout << cur->data << (cur->next ? " <-> " : "");
            cur = cur->next;
        }
        cout << "\n";
    }
};

int main() {
    DoublyLinkedList d;
    d.insertBegin(30);
    d.insertBegin(20);
    d.insertEnd(40);
    cout << "List: ";
    d.printForward();

    d.removeBegin();
    d.removeEnd();
    cout << "After removals: ";
    d.printForward();
    return 0;
}
