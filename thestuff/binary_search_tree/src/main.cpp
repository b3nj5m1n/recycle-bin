#include <iostream>
#include "BinarySearchTree.h"

int main(int argc, char** argv) {
    char content = 'A';
    int values[] = {44,17,32,78,88,50,48,62};
    BinarySearchTree<int>* tree = new BinarySearchTree<int>;
    for (int i = 0; i < (sizeof(values)/sizeof(*values)); i++) {
        tree->insert(&values[i]);
    }
    // tree->print();
    tree->print_post_order();
    /* std::cout << tree->is_empty() << std::endl;
    tree->insert(&content);
    std::cout << tree->is_empty() << std::endl; */
    return 0;
}
