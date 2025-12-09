#include <iostream>
using namespace std;

struct CNode {
    int data;
    CNode* next;
    CNode(int v): data(v), next(nullptr) {}
};

class CircularLinkedList {
private:
    CNode* tail;
public:
    CircularLinkedList(): tail(nullptr) {}
    ~CircularLinkedList() {
        if (!tail) return;
        CNode* cur = tail->next;
        tail->next = nullptr;
        while (cur) {
            CNode* t = cur;
            cur = cur->next;
            delete t;
        }
    }

    void insert(int x) {
        CNode* n = new CNode(x);
        if (!tail) {
            tail = n;
            tail->next = tail;
        } else {
            n->next = tail->next;
            tail->next = n;
            tail = n;
        }
    }

    bool remove(int x) {
        if (!tail) return false;
        CNode* cur = tail->next;
        CNode* prev = tail;
        do {
            if (cur->data == x) {
                if (cur == prev) {
                    delete cur;
                    tail = nullptr;
                } else {
                    prev->next = cur->next;
                    if (cur == tail) tail = prev;
                    delete cur;
                }
                return true;
            }
            prev = cur;
            cur = cur->next;
        } while (cur != tail->next);
        return false;
    }

    CNode* search(int x) {
        if (!tail) return nullptr;
        CNode* cur = tail->next;
        do {
            if (cur->data == x) return cur;
            cur = cur->next;
        } while (cur != tail->next);
        return nullptr;
    }

    void print() {
        if (!tail) { cout << "Empty\n"; return; }
        CNode* cur = tail->next;
        do {
            cout << cur->data;
            cur = cur->next;
            if (cur != tail->next) cout << " -> ";
        } while (cur != tail->next);
        cout << "\n";
    }
};

int main() {
    CircularLinkedList cl;
    cl.insert(10);
    cl.insert(20);
    cl.insert(30);
    cout << "Circular List: ";
    cl.print();

    cl.remove(20);
    cout << "After removing 20: ";
    cl.print();
    return 0;
}
