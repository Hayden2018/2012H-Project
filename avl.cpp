#include "avl.h"
#include <algorithm>

/* File: avl.cpp */

template <typename T>
int AVL<T>::height() const
{
    return is_empty() ? -1 : root->height; // an empty tree has height -1
}

template <typename T>
int AVL<T>::bfactor() const
{
    return is_empty() ? 0 : right_subtree().height() - left_subtree().height();
}

template <typename T>
void AVL<T>::fix_height() const
{
    if (!is_empty())
        root->height = std::max(left_subtree().height(), right_subtree().height()) + 1;
}

template <typename T>
void AVL<T>::rotate_left()
{
    AVLnode* b = right_subtree().root;
    right_subtree() = b->left;
    b->left = *this;
    fix_height();
    root = b;
    fix_height();
}

template <typename T>
void AVL<T>::rotate_right()
{
    AVLnode* b = left_subtree().root;
    left_subtree() = b->right;
    b->right = *this;
    fix_height();
    root = b;
    fix_height();
}

template <typename T>
void AVL<T>::balance()
{
    if (is_empty())
        return;

    fix_height();
    int bFactor = bfactor();

    if (bFactor == 2) // case R{L/R}
    {
        if (right_subtree().bfactor() < 0) // case RL
            right_subtree().rotate_right();

        return rotate_left();
    }
    else if (bFactor == -2) // case L{L/R}
    {
        if (left_subtree().bfactor() > 0) // case LR
            left_subtree().rotate_left();

        return rotate_right();
    }

}

template <typename T>
const T& AVL<T>::find_min() const
{
    const AVLnode* node = root;

    while (!node->left.is_empty())
    {
        node = node->left.root;
    }

    return node->value;
}

template <typename T>
bool AVL<T>::contains(const T& x) const
{
    if (is_empty())
        return false;

    if (root->value > x)
        return left_subtree().contains(x);

    if (root->value < x)
        return right_subtree().contains(x);

    return true;
}

template <typename T>
void AVL<T>::insert(const T& x)
{
    if (is_empty())
        root = new AVLnode(x);
    else if (root->value > x)
        left_subtree().insert(x);
    else if (root->value < x)
        right_subtree().insert(x);

    balance();
}

template <typename T>
void AVL<T>::remove(const T& x)
{
    if (is_empty())
        return;

    if (x < root->value)
        left_subtree().remove(x);

    else if (x > root->value)
        right_subtree().remove(x);

    else
    {
        AVL& left_avl = left_subtree();
        AVL& right_avl = right_subtree();

        // Found node has 2 children
        if (!left_avl.is_empty() && !right_avl.is_empty())
        {
            root->value = right_avl.find_min(); // Copy the minimum value in the right subtree
            right_avl.remove(root->value); // Remove node with the minimum value
        }

        else  // Found node has 0 or 1 child
        {
            AVLnode* node_to_remove = root; // Save the node first
            *this = left_avl.is_empty() ? right_avl : left_avl;

            // Reset the node to be removed with empty children
            right_avl.root = left_avl.root = nullptr;
            delete node_to_remove;
        }
    }

    balance();
}

template <typename T>
template <typename Callable>
void AVL<T>::in_order_action(Callable action)
{
    if (!is_empty())
    {
        left_subtree().in_order_action(action);
        action(root->value);
        right_subtree().in_order_action(action);
    }
}
