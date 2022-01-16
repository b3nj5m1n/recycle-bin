# binary_search_tree

A complete implementation of a binary search tree in c++.

Probably not safe to use because I don't know c++.

## Methods

### `is_empty`

Returns true if there are no subtrees associated with the current subtree and the content field is empty.

### `is_leaf`

Returns true if both subtrees are empty.

### `has_only_one_child`

Returns true if there is only one non-empty subtree.

### `set_content`

Sets the content field for the current subtree.

### `get_content`

Returns the content field of the current subtree.

### `set_parent`

Sets the parent property to a new subtree.

### `overwrite_self_parent`

Convenience method to ascend to the parent, find the subtree which currently contains the subtree on which the `overwrite_self_parent` method is being called, and overwrite that with a new subtree.

### `insert`

Inserts content into the tree.

### `search`

Searches for content, if it exists returns the subtree containing the element, if it doesn't exist, returns a nullpointer.

### `remove`

Removes the subtree on which the method is called from the parent,  returns the value it holds.

### `print`

Prints general information about the current subtree.

### `print_pre_order`

Traverses the subtree in pre-order and prints the values.

### `print_post_order`

Traverses the subtree in post-order and prints the values.

### `print_in_order`

Traverses the subtree in-order and prints the values.

### `print_dot`

Prints the subtree structure in the dot format. Currently you can't tell if a subtree is attached at the left or right side of its parent if it's the only subtree of that parent.

For example:
```sh
./bin/main > /tmp/test.dot
dot -Tpng /tmp/test.dot -o /tmp/test.png
```
Will generate a png file visualising the tree.
