#ifndef AVL_H
#define AVL_H
/* File: avl.h */

/* 
 * This is an implementation of the AVL tree
 * Supports O(logn) time insertion, deletion and searching
 * Primarily used to store the whitelist, 
 * can also be used by other program components
 */

template <typename T>
class AVL
{
  private:
    struct AVLnode
    {
        T value;
        int height;
        AVL left;            // Left subtree is also an AVL object
        AVL right;           // Right subtree is also an AVL object
        AVLnode(const T& x) : value(x), height(0), left(), right() { }
    };

    AVLnode* root = nullptr;

    AVL& right_subtree() { return root->right; }
    AVL& left_subtree() { return root->left; }
    const AVL& right_subtree() const { return root->right; }
    const AVL& left_subtree() const { return root->left; }

    int height() const;      // Find the height of tree
    int bfactor() const;     // Find the balance factor of tree
    void fix_height() const; // Rectify the height of each node in tree
    void rotate_left();      // Single left or anti-clockwise rotation
    void rotate_right();     // Single right or clockwise rotation
    void balance();          // AVL tree balancing

  public:
    AVL() = default;         // Build an empty AVL tree by default
    ~AVL() { delete root; }

    bool is_empty() const { return root == nullptr; }
    const T& find_min() const;       // Find the minimum value in an AVL, used in deletion
    bool contains(const T& x) const; // Search an item

    void insert(const T& x); // Insert an item
    void remove(const T& x); // Remove an item

    template <typename Callable>
    void in_order_action(Callable action); // Perform action to each of the data stored in the tree
                                           // in in-order
};

#include "avl.cpp"

#endif // AVL_H
