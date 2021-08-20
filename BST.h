#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <list>

template<class Key, class Val>
struct Node {

    Key key_;
    Val val_;
    Node * left_child_;
    Node * right_child_;

    Node(Key key, Val val) {
        key_ = key;
        val_ = val;
        left_child_ = nullptr;
        right_child_ = nullptr;
    }

    Node(Key key, Val val, Node<Key, Val> * left_child, Node<Key, Val> * right_child) {
        key_ = key;
        val_ = val;
        left_child_ = left_child;
        right_child_ = right_child;
    }
};

template<class Key, class Val>
class BST {

    Node<Key, Val> * root_;
    int size_;

    Node<Key, Val> * InOrderSuccessor(Node<Key, Val> * root) {
        Node<Key, Val> * itr = root->right_child_;
        while (itr->left_child_ != nullptr)
        {
            itr = itr->left_child_;
        }
        return itr;
    }

    Node<Key, Val> * FindParent(Key key) {
        Node<Key, Val> * parent = root_;
        Node<Key, Val> * itr = root_;
        while (itr != nullptr && itr->key_ != key)
        {
            parent = itr;
            if (key < itr->key_)
            {
                itr = itr->left_child_;
            }
            else
            {
                itr = itr->right_child_;
            }
        }
        return parent;
    }

    int CountChildren(Node<Key, Val> * node) {
        int count = 0;
        if (node->left_child_) count++;
        if (node->right_child_) count++;
        return count;
    }

    void RemoveNode(Node<Key, Val> * parent, Node<Key, Val> * child_to_remove, Node<Key, Val> * new_child) {

        if (child_to_remove->key_ < parent->key_)
        {
            parent->left_child_ = new_child;
        }
        else
        {
            parent->right_child_ = new_child;
        }

        if (child_to_remove == root_)
        {
            root_ = new_child;
        }

        child_to_remove->left_child_ = nullptr;
        child_to_remove->right_child_ = nullptr;
        delete child_to_remove;
    }

    void RecursivelyDeleteNodes(Node<Key, Val> * root) {

        if (root == nullptr)
        {
            return;
        }

        RecursivelyDeleteNodes(root->left_child_);
        RecursivelyDeleteNodes(root->right_child_);

        delete root;
    }

    void RecursiveInOrder(Node<Key, Val> * root, std::list<Node<Key, Val> *> & traversal) {

        if (root == nullptr)
        {
            return;
        }

        RecursiveInOrder(root->left_child_, traversal);
        traversal.push_back(root);
        RecursiveInOrder(root->right_child_, traversal);
    }

    void RecursivePostOrder(Node<Key, Val> * root, std::list<Node<Key, Val> *> & traversal) {

        if (root == nullptr)
        {
            return;
        }

        RecursivePostOrder(root->left_child_, traversal);
        RecursivePostOrder(root->right_child_, traversal);
        traversal.push_back(root);
    }

    void RecursivePreOrder(Node<Key, Val> * root, std::list<Node<Key, Val> *> & traversal) {

        if (root == nullptr)
        {
            return;
        }

        traversal.push_back(root);
        RecursivePreOrder(root->left_child_, traversal);
        RecursivePreOrder(root->right_child_, traversal);
    }

public:

    BST() {
        root_ = nullptr;
        size_ = 0;
    }

    ~BST() {
        Clear();
    }

    Node<Key, Val> * Find(Key key) {

        Node<Key, Val> * itr = root_;
        while (itr != nullptr && itr->key_ != key)
        {
            if (key < itr->key_)
            {
                itr = itr->left_child_;
            }
            else if (key > itr->key_)
            {
                itr = itr->right_child_;
            }
        }
        return itr;
    }

    void Insert(Key key, Val val) {

        if (Find(key))
        {
            return;
        }
        else if (root_ == nullptr)
        {
            root_ = new Node<Key, Val>(key, val);
        }
        else
        {
            Node<Key, Val> * parent = FindParent(key);

            if (key < parent->key_)
            {
                parent->left_child_ = new Node<Key, Val>(key, val);
            }
            else
            {
                parent->right_child_ = new Node<Key, Val>(key, val);
            }
        }
        size_++;
    }

    void Remove(Key key) {

        Node<Key, Val> * parent = FindParent(key);
        Node<Key, Val> * to_remove = Find(key);

        if (!to_remove)
        {
            return;
        }

        int num_children = CountChildren(to_remove);

        if (num_children == 2)
        {
            Node<Key, Val> * successor = InOrderSuccessor(to_remove);
            Key key_to_swap = successor->key_;
            Val val_to_swap = successor->val_;

            Remove(successor->key_);
            size_++;

            to_remove->key_ = key_to_swap;
            to_remove->val_ = val_to_swap;
        }
        else if (num_children == 1)
        {
            if (to_remove->left_child_)
            {
                RemoveNode(parent, to_remove, to_remove->left_child_);
            }
            else
            {
                RemoveNode(parent, to_remove, to_remove->right_child_);
            }
        }
        else
        {
            RemoveNode(parent, to_remove, nullptr);
        }

        size_--;
    }

    void Clear() {
        RecursivelyDeleteNodes(root_);
        root_ = nullptr;
        size_ = 0;
    }

    int Size() {
        return size_;
    }

    bool Empty() {
        return size_ == 0;
    }

    std::list<Node<Key, Val> *> InOrderTraversal() {
        std::list<Node<Key, Val> *> traversal;
        RecursiveInOrder(root_, traversal);
        return traversal;
    }

    std::list<Node<Key, Val> *> PostOrderTraversal() {
        std::list<Node<Key, Val> *> traversal;
        RecursivePostOrder(root_, traversal);
        return traversal;
    }

    std::list<Node<Key, Val> *> PreOrderTraversal() {
        std::list<Node<Key, Val> *> traversal;
        RecursivePreOrder(root_, traversal);
        return traversal;
    }
};

#endif