enum Color { RED, BLACK };

template <typename K, typename T>
struct Node {
    K key;
    T value;
    Color color;
    Node <K,T>*left;
    Node <K,T>*right;
    Node <K,T>*parent;

    Node(const K &k, const T &val) : key(k), value(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename K, typename T>
class RedBlackTree {
private:
    Node<K,T> *root;
    int size;

    void leftRotate(Node<K,T> *x) {
        if (x == nullptr || x->right == nullptr)
            return;

        Node <K,T>*y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node<K,T> *y) {
        if (y == nullptr || y->left == nullptr)
            return;

        Node <K,T>*x = y->left;
        y->left = x->right;
        if (x->right != nullptr)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }
    
    Node<K,T> *searchTreeHelper(Node<K,T> *node,const K &key) {
        if (node == nullptr || key == node->key)
            return node;

        if (key < node->key)
            return searchTreeHelper(node->left, key);
        return searchTreeHelper(node->right, key);
    }

    void fixInsert(Node<K,T> *z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node<K,T> *y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node <K,T>*y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Node<K,T> *u, Node<K,T> *v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    void deleteNodeHelper(Node<K,T> *z) {
        if (z == nullptr)
            return;

        Node <K,T>*y = z;
        Node <K,T>*x = nullptr;
        Color y_original_color = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x != nullptr)
                    x->parent = y; 
            } else {
                if (x != nullptr)
                    x->parent = y->parent; 
                transplant(y, y->right);
                if (y->right != nullptr)
                    y->right->parent = y; 
                y->right = z->right;
                if (y->right != nullptr)
                    y->right->parent = y; 
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr)
                y->left->parent = y; 
            y->color = z->color;
        }

        if (y_original_color == BLACK && x != nullptr)
            fixDelete(x);

        delete z; 
    }

    void fixDelete(Node<K,T> *x) {
        while (x != root && x != nullptr && x->color == BLACK) {
            if (x == x->parent->left) {
                Node<K,T> *w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == BLACK) {
                        if (w->left != nullptr)
                            w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right != nullptr)
                        w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node<K,T> *w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((w->right == nullptr || w->right->color == BLACK) &&
                    (w->left == nullptr || w->left->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left == nullptr || w->left->color == BLACK) {
                        if (w->right != nullptr)
                            w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left != nullptr)
                        w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr)
            x->color = BLACK;
    }

    Node<K,T>*minimum(Node<K,T>*node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // void printHelper(Node* root, int space) {
    //     constexpr int COUNT = 5;
    //     if (root == nullptr)
    //         return;
    //     space += COUNT;
    //     printHelper(root->right, space);
    //     std::cout << std::endl;
    //     for (int i = COUNT; i < space; i++)
    //         std::cout << " ";
    //     std::cout << root->data << "(" << ((root->color == RED) ? "RED" : "BLACK") << ")" << std::endl;
    //     printHelper(root->left, space);
    // }
     
    void preOrderHelper(Node<K,T>*node) {
        if (node != nullptr) {
            std::cout << node->value << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        } 
    }

    void inOrderHelper(Node<K,T>*node) {
        if (node != nullptr) {
            inOrderHelper(node->left);
            std::cout << node->value << " ";
            inOrderHelper(node->right);
        } 
    }

    void postOrderHelper(Node<K,T>*node) {
        if (node != nullptr) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            std::cout << node->value << " ";
        } 
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(const K &key,const T &val) {
        Node<K,T> *newNode = new Node<K,T> (key, val);
        Node<K,T> *y = nullptr;
        Node<K,T> *x = root;

        while (x != nullptr) {
            y = x;
            if (newNode->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        newNode->parent = y;
        if (y == nullptr)
            root = newNode;
        else if (newNode->key < y->key)
            y->left = newNode;
        else
            y->right = newNode;

        fixInsert(newNode);
        this->size++;
    }

    void deleteNode(const K &val) {
        Node<K,T> *z = root;
        while (z != nullptr) {
            if (val < z->key)
                z = z->left;
            else if (val > z->key)
                z = z->right;
            else {
                deleteNodeHelper(z);
                this->size--; 
                return;
            }
        }
        std::cout << "Node with value " << val << " not found in the tree." << std::endl;
    }
    
    void printPreorder(){
        preOrderHelper(root);
        std::cout << std::endl;
    }

    void printInorder(){
        inOrderHelper(root);
        std::cout << std::endl;
    }

    void printPostorder(){
        postOrderHelper(root);
        std::cout << std::endl;
    }
    
    Node<K,T> *searchTree(const K &key) {
        return searchTreeHelper(root, key);
    }
   
    int getSize() {
        return this->size;
    }
    
    void clear(){
        
    }

    void printTree() {
        //printHelper(root, 0);
        printInorder();
    }
};
