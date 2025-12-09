// queue_adt.cpp
#include <bits/stdc++.h>
using namespace std;

struct QNode {
    int data;
    QNode* next;
    QNode(int v): data(v), next(nullptr) {}
};

class QueueADT {
private:
    QNode* frontPtr;
    QNode* rearPtr;
public:
    QueueADT(): frontPtr(nullptr), rearPtr(nullptr) {}
    ~QueueADT() {
        while (frontPtr) {
            QNode* t = frontPtr;
            frontPtr = frontPtr->next;
            delete t;
        }
    }
    bool empty() const { return frontPtr == nullptr; }
    void enqueue(int x) {
        QNode* n = new QNode(x);
        if (!rearPtr) {
            frontPtr = rearPtr = n;
            return;
        }
        rearPtr->next = n;
        rearPtr = n;
    }
    bool dequeue(int &out) {
        if (!frontPtr) return false;
        QNode* t = frontPtr;
        out = t->data;
        frontPtr = frontPtr->next;
        if (!frontPtr) rearPtr = nullptr;
        delete t;
        return true;
    }
    int peek() const {
        if (!frontPtr) throw runtime_error("Queue empty");
        return frontPtr->data;
    }
    void print() const {
        QNode* cur = frontPtr;
        while (cur) {
            cout << cur->data << (cur->next ? " <- " : "");
            cur = cur->next;
        }
        cout << "\n";
    }
};

int main() {
    QueueADT q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    cout << "Queue: ";
    q.print();

    int v;
    q.dequeue(v);
    cout << "Dequeued: " << v << "\n";
    cout << "After dequeue: ";
    q.print();

    cout << "Front element: " << q.peek() << "\n";
    return 0;
}
