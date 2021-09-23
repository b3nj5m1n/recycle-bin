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
    BinarySearchTree<T>* parent;
    T* content;

    public:
    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(T content);
    bool is_empty();
    bool is_leaf();
    bool has_only_one_child();
    void set_content(T* content);
    T* get_content();
    void set_parent(BinarySearchTree<T>* parent);
    void overwrite_self_parent(BinarySearchTree<T>* new_subtree);
    void insert(T* content);
    void insert(T* content, BinarySearchTree<T>* caller);
    BinarySearchTree<T>* search(T* content);
    T* remove();
    void print();
    void print_pre_order();
    void print_in_order();
    void print_post_order();
    void print_dot(int* count, int parent_id);
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

// Will return true if the subtree only has one other subtree
template <class T>
bool BinarySearchTree<T>::has_only_one_child() {
    if (this->is_empty()) { return false; }
    if (!this->subtree_left->is_empty() && this->subtree_right->is_empty()) { return true; }
    if (this->subtree_left->is_empty() && !this->subtree_right->is_empty()) { return true; }
    return false;
}

// Sets content, creates emtpy subtrees if subtrees don't exist yet
template <class T>
void BinarySearchTree<T>::set_content(T* content) {
    this->content = content;
    if (this->subtree_left == nullptr) { this->subtree_left = new BinarySearchTree<T>; }
    if (this->subtree_right == nullptr) { this->subtree_right = new BinarySearchTree<T>; }
}

// Return pointer to content
template <class T>
T* BinarySearchTree<T>::get_content() {
    return this->content;
}

// Return pointer to content
template <class T>
void BinarySearchTree<T>::set_parent(BinarySearchTree<T>* parent) {
    this->parent = parent;
}

// Find itself in the parent, then overwrite that subtree
template <class T>
void BinarySearchTree<T>::overwrite_self_parent(BinarySearchTree<T>* new_subtree) {
    if (this->parent->subtree_left == this) {
        this->parent->subtree_left = new_subtree;
    }
    if (this->parent->subtree_right == this) {
        this->parent->subtree_right = new_subtree;
    }
}

template <class T>
void BinarySearchTree<T>::insert(T* content) {
    this->insert(content, nullptr);
}
// Inserts content at appropriate position, if content already exists, nothing happens
template <class T>
void BinarySearchTree<T>::insert(T* content, BinarySearchTree<T>* caller) {
    if (this->is_empty()) { this->set_content(content); this->set_parent(caller); }
    if (this->content == content) { }
    else if (*(this->content) > *content) { this->subtree_left->insert(content, this); }
    else if (*(this->content) < *content) { this->subtree_right->insert(content, this); }
}

// Returns null if the content doesn't exist, otherwise returns the subtree containing the content
template <class T>
BinarySearchTree<T>* BinarySearchTree<T>::search(T* content) {
    if (this->is_empty()) { return nullptr; }
    if (*(this->content) == *(content)) { return this; }
    if (*(this->content) > *(content)) { return this->subtree_left->search(content); }
    if (*(this->content) < *(content)) { return this->subtree_right->search(content); }
}

// Removes the subtree, returns the value
template <class T>
T* BinarySearchTree<T>::remove() {
    T* content = this->get_content();
    // There are three cases that need to be handled differently:
    // The subtree is a leaf (no subtrees are attached to it) - We can just delete it
    if (this->is_leaf()) {
        this->overwrite_self_parent(new BinarySearchTree<T>);
    }
    // The subtree only has one subtree attached to it - We can simply move the
    // pointer of the parent to this child
    else if (this->has_only_one_child()) {
        if (!this->subtree_left->is_empty()) {
            this->overwrite_self_parent(this->subtree_left);
            this->subtree_left->set_parent(this->parent);
        }
        if (!this->subtree_right->is_empty()) {
            this->overwrite_self_parent(this->subtree_right);
            this->subtree_right->set_parent(this->parent);
        }
    }
    // The subtree has two subtrees attached to it - Move to the right subtree,
    // go left as many times as possible, copy this subtree to the position where
    // we want to remove our subtree, then call delete on the replacement
    else {
        // Find the leftmost subtree of the right subtree
        BinarySearchTree<T>* current = this->subtree_right;
        while (!current->subtree_left->is_empty()) {
            current = current->subtree_left;
        }
        // Replace the value of the subtree we're trying to remove with the value of
        // the subtree we just found
        this->set_content(current->get_content());
        // Remove the subtree from the tree
        current->remove();
    }
    return content;
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
    std::cout << "Parent: " << *(this->parent->content) << ", ";
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

template <class T>
void BinarySearchTree<T>::print_dot(int* counter, int parent_id) {
    if (this->is_empty()) { return; }
    (*counter)++;
    int id = *counter;
    if (parent_id == 0) {
        std::cout << "digraph BST {" << std::endl;
    }
    std::cout << "\t" << "node" << *counter << "[label=\"" << *(this->content) << "\"];" << std::endl;
    if (parent_id != 0) {
        std::cout << "\t" << "node" << parent_id << " -> " << "node" << id << ";" << std::endl;
    }
    if (!this->subtree_left->is_empty()) {
        this->subtree_left->print_dot(counter, id);
    }
    if (!this->subtree_right->is_empty()) {
        this->subtree_right->print_dot(counter, id);
    }
    if (parent_id == 0) {
        std::cout << "}" << std::endl;
    }
}

#endif
