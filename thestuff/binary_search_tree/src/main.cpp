#include <iostream>
#include "BinarySearchTree.h"

int main(int argc, char** argv) {
    // int values[] = {44,17,32,78,88,50,48,62};
    int values[] = {31, 6, 2, 19, 7, 11, 45, 28, 25, 41, 9, 4, 43, 10, 23, 34, 18, 42, 47, 38, 12, 35, 29, 16, 39, 30, 37, 50, 46, 33, 48, 40, 1, 15, 3, 5, 27, 22, 8, 20, 44, 13, 49, 21, 26, 24, 14, 32, 17, 36};
    BinarySearchTree<int>* tree = new BinarySearchTree<int>;
    for (int i = 0; i < (sizeof(values)/sizeof(*values)); i++) {
        tree->insert(&values[i]);
    }
    // tree->print();
    // tree->print_post_order();

    /* std::cout << tree->is_empty() << std::endl;
    tree->insert(&content);
    std::cout << tree->is_empty() << std::endl; */

    int content = 50;
    BinarySearchTree<int>* result = tree->search(&content);
    // std::cout << *(result->get_content()) << std::endl;

    int values_to_remove[] = {14,35,19};
    for (int i = 0; i < (sizeof(values_to_remove)/sizeof(*values_to_remove)); i++) {
        BinarySearchTree<int>* subtree = tree->search(&values_to_remove[i]);
        subtree->remove();
        // subtree->print();
        // std::cout << subtree->is_leaf() << std::endl;
    }

    int counter = 0;
    tree->print_dot(&counter, 0);

    return 0;
}
