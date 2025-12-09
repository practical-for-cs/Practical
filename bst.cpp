#include <iostream>
using namespace std;

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int k): key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;
    BSTNode* insertRec(BSTNode* node, int key) {
        if (!node) return new BSTNode(key);
        if (key < node->key) node->left = insertRec(node->left, key);
        else if (key > node->key) node->right = insertRec(node->right, key);
        // duplicates ignored
        return node;
    }
    BSTNode* searchRec(BSTNode* node, int key) {
        if (!node || node->key == key) return node;
        if (key < node->key) return searchRec(node->left, key);
        return searchRec(node->right, key);
    }
    BSTNode* findMin(BSTNode* node) {
        while (node && node->left) node = node->left;
        return node;
    }
    BSTNode* deleteRec(BSTNode* node, int key) {
        if (!node) return nullptr;
        if (key < node->key) node->left = deleteRec(node->left, key);
        else if (key > node->key) node->right = deleteRec(node->right, key);
        else {
            
            if (!node->left) {
                BSTNode* r = node->right;
                delete node;
                return r;
            } else if (!node->right) {
                BSTNode* l = node->left;
                delete node;
                return l;
            } else {
                BSTNode* succ = findMin(node->right);
                node->key = succ->key;
                node->right = deleteRec(node->right, succ->key);
            }
        }
        return node;
    }
    void preorderRec(BSTNode* node) {
        if (!node) return;
        cout << node->key << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }
    void inorderRec(BSTNode* node) {
        if (!node) return;
        inorderRec(node->left);
        cout << node->key << " ";
        inorderRec(node->right);
    }
    void postorderRec(BSTNode* node) {
        if (!node) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->key << " ";
    }
    void freeRec(BSTNode* node) {
        if (!node) return;
        freeRec(node->left);
        freeRec(node->right);
        delete node;
    }
public:
    BST(): root(nullptr) {}
    ~BST(){ freeRec(root); }
    void insert(int key){ root = insertRec(root, key); }
    bool remove(int key){
        if (!searchRec(root, key)) return false;
        root = deleteRec(root, key);
        return true;
    }
    BSTNode* search(int key){ return searchRec(root, key); }
    void preorder(){ preorderRec(root); cout << "\n"; }
    void inorder(){ inorderRec(root); cout << "\n"; }
    void postorder(){ postorderRec(root); cout << "\n"; }
};

int main() {
    BST tree;
    vector<int> keys = {50, 30, 20, 40, 70, 60, 80};
    for (int k : keys) tree.insert(k);
    cout << "Inorder (sorted): "; tree.inorder();
    cout << "Preorder: "; tree.preorder();
    cout << "Postorder: "; tree.postorder();

    cout << "Searching 40: ";
    auto p = tree.search(40);
    if (p) cout << "Found " << p->key << " at " << p << "\n"; else cout << "Not found\n";

    tree.remove(50);
    cout << "Inorder after deleting 50: "; tree.inorder();
    return 0;
}
