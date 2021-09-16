#ifndef NODE
#define NODE

class Node {
    private:
    int s;
    public:
    void set_content(int p) { this->s = p; }
    int get_content() { return this->s; }
    bool operator==(const Node& rhs) const { return (this->s == rhs.s); }
    bool operator!=(const Node& rhs) const { return !operator==(rhs); }
    bool operator<(const Node& rhs) const { return (this->s < rhs.s); }
    bool operator>(const Node& rhs) const { return !operator<(rhs); }
    bool operator<=(const Node& rhs) const { return !operator>(rhs); }
    bool operator>=(const Node& rhs) const { return !operator<(rhs); }
};

#endif

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <concepts>

template <class T>
requires std::totally_ordered<T>
class BinarySearchTree {
    private:
    BinarySearchTree<T>* subtree_left;
    BinarySearchTree<T>* subtree_right;
    T* content;

    public:
    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(T content);
    bool is_empty();
    bool is_leaf();
    void set_content(T* content);
    void insert(T* content);
    void print();
    void print_pre_order();
    void print_in_order();
    void print_post_order();
};

template <class T>
BinarySearchTree<T>::BinarySearchTree() {
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
    delete this->subtree_left;
    delete this->subtree_right;
}

// Construtor when content is already known, will create two empty subtrees
template <class T>
BinarySearchTree<T>::BinarySearchTree(T content) {
    this->subtree_left = new BinarySearchTree<T>;
    this->subtree_right = new BinarySearchTree<T>;
    this->content = &content;
}

// Will return true if both subtrees and the content are nullpointers
template <class T>
bool BinarySearchTree<T>::is_empty() {
    return ((this->subtree_left == nullptr) and (this->subtree_right == nullptr) and (this->content == nullptr));
}

// Will return true if both subtrees are empty
template <class T>
bool BinarySearchTree<T>::is_leaf() {
    if (this->is_empty()) { return false; }
    if (!this->subtree_left->is_empty()) { return false; }
    if (!this->subtree_right->is_empty()) { return false; }
    return true;
}

// Sets content, creates emtpy subtrees if subtrees don't exist yet
template <class T>
void BinarySearchTree<T>::set_content(T* content) {
    this->content = content;
    if (this->subtree_left == nullptr) { this->subtree_left = new BinarySearchTree<T>; }
    if (this->subtree_right == nullptr) { this->subtree_right = new BinarySearchTree<T>; }
}

// Inserts content at appropriate position, if content already exists, nothing happens
template <class T>
void BinarySearchTree<T>::insert(T* content) {
    if (this->is_empty()) { this->set_content(content); }
    if (this->content == content) { }
    else if (*(this->content) > *content) { this->subtree_left->insert(content); }
    else if (*(this->content) < *content) { this->subtree_right->insert(content); }
}

// Prints general information about current subtree
template <class T>
void BinarySearchTree<T>::print() {
    std::cout << "Content: " << *(this->content) << ", ";
    if (!this->subtree_left->is_empty()) {
        std::cout << "Left: " << *(this->subtree_left->content) << ", ";
    } else {
        std::cout << "Left empty.";
    }
    if (!this->subtree_right->is_empty()) {
        std::cout << "Right: " << *(this->subtree_right->content) << ", ";
    } else {
        std::cout << "Right empty.";
    }
    std::cout << std::endl;
}

template <class T>
void BinarySearchTree<T>::print_pre_order() {
    if (this->is_empty()) { return; }
    std::cout << *(this->content) << std::endl;
    this->subtree_left->print_pre_order();
    this->subtree_right->print_pre_order();
}
template <class T>
void BinarySearchTree<T>::print_post_order() {
    if (this->is_empty()) { return; }
    this->subtree_left->print_post_order();
    this->subtree_right->print_post_order();
    std::cout << *(this->content) << std::endl;
}
template <class T>
void BinarySearchTree<T>::print_in_order() {
    if (this->is_empty()) { return; }
    this->subtree_left->print_in_order();
    std::cout << *(this->content) << std::endl;
    this->subtree_right->print_in_order();
}

#endif
