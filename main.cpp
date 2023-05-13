#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Node {
    std::vector<int> keys;
    std::vector<Node*> children;
    bool isLeaf;
};

class XTree {
public:
    XTree(int _M) : M(_M) {
        root = new Node();
        root->isLeaf = true;
    }
public:
    // ...

    Node* search(int key) {
        return searchNode(root, key);
    }

    void insert(int key) {
        if (root->keys.size() == M - 1) {
            Node* newRoot = new Node();
            newRoot->isLeaf = false;
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
        }
        insertNonFull(root, key);
    }

    void print() {
        printNode(root, 0);
    }
    
    
    
private:
    // ...

    Node* searchNode(Node* node, int key) {
        int i = std::lower_bound(node->keys.begin(), node->keys.end(), key) - node->keys.begin();
        if (i < node->keys.size() && node->keys[i] == key) {
            return node;
        }
        if (node->isLeaf) {
            return nullptr;
        }
        return searchNode(node->children[i], key);
    }

private:
    int M;
    Node* root;

    void splitChild(Node* x, int i) {
        Node* z = new Node();
        Node* y = x->children[i];
        z->isLeaf = y->isLeaf;
        for (int j = 0; j < M / 2 - 1; j++) {
            z->keys.push_back(y->keys[M / 2 + j]);
        }
        if (!y->isLeaf) {
            for (int j = 0; j < M / 2; j++) {
                z->children.push_back(y->children[M / 2 + j]);
            }
        }
        y->keys.resize(M / 2 - 1);
        y->children.resize(M / 2);
        x->children.insert(x->children.begin() + i + 1, z);
        x->keys.insert(x->keys.begin() + i, y->keys[M / 2 - 1]);
    }

    void insertNonFull(Node* x, int key) {
        if (x->isLeaf) {
            x->keys.insert(std::upper_bound(x->keys.begin(), x->keys.end(), key), key);
        } else {
            int i = x->keys.size() - 1;
            while (i >= 0 && key < x->keys[i]) i--;
            i++;
            if (x->children[i]->keys.size() == M - 1) {
                splitChild(x, i);
                if (key > x->keys[i]) i++;
            }
            insertNonFull(x->children[i], key);
        }
    }

    void printNode(Node* node, int depth) {
        std::string indent(depth * 2, ' ');
        std::cout << indent << "[";
        for (int i = 0; i < node->keys.size(); i++) {
            std::cout << node->keys[i];
            if (i != node->keys.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
        if (!node->isLeaf) {
            for (int i = 0; i < node->children.size(); i++) {
                printNode(node->children[i], depth + 1);
            }
        }
    }
};

int main() {
    XTree tree(5);

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);

    tree.print();

    int clave = 15;
    Node* nodo = tree.search(clave);
    if (nodo) {
        std::cout << "¡Se encontró la clave " << clave << " en el árbol!" << std::endl;
    } else {
        std::cout << "La clave " << clave << " no se encontró en el árbol." << std::endl;
    }

    clave = 20;
    nodo = tree.search(clave);
    if (nodo) {
        std::cout << "¡Se encontró la clave " << clave << " en el árbol!" << std::endl;
    } else {
        std::cout << "La clave " << clave << " no se encontró en el árbol." << std::endl;
    }

    return 0;
}
