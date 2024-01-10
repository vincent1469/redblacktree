//
// Created by Vincent Chu on 4/30/2023.
//

#include "RedBlackTree.h"
#include "RedBlackTreeNode.h"
#include <iostream>

// insert a node into the tree
void RedBlackTree::insertion(const int subject) {
    // check if node is empty
    if ((node->value == 0) && (node->Color == RED)) {
        node->value = subject;
        node->Color = BLACK;
    }
    else {
        // while the tree looks to insert somewhere it will keep looping
        int ableToInsert = 0;
        while(ableToInsert == 0) {
            // if the subject is larger or equal than the node value check if the right is empty before inserting
            if (subject >= node->value) {
                if (node->right == nullptr) {
                    ableToInsert = 1;
                    RedBlackTreeNode* child = new RedBlackTreeNode();
                    child->parent = node;
                    child->value = subject;
                    node->right = child;
                    node = node->right;
                }
                else node = node->right;
            }
                // if the subject is smaller than the node value check if the left is empty before inserting
            else if (subject < node->value) {
                if (node->left == nullptr) {
                    ableToInsert = 1;
                    RedBlackTreeNode* child = new RedBlackTreeNode();
                    child->parent = node;
                    child->value = subject;
                    node->left = child;
                    node = node->left;
                }
                else node = node->left;
            }
        }
    }

    fix();
    while (node->parent != nullptr) node = node->parent;
}

// fix tree
void RedBlackTree::fix() {
    // makes sure parent exists first
    if (node->parent != nullptr) {
        // if the parent's colour is red then we got a problem
        if (node->parent->Color == RED) {
            // while the tree reaches the top it keeps correcting itself
            while (node->parent != nullptr) {
                // if there's two reds in a row then fix
                if ((node->Color == RED) && (node->parent->Color == RED)) {
                    // checks if the parent's sibling exists
                    if ((node->parent->parent->left) && (node->parent->parent->right)) {
                        // if the parents' sibling is red then set the parent and the parent's sibling to black
                        // as well as flipping the grandparent's colour
                        if ((node->parent->parent->left->Color == RED) && (node->parent->parent->right->Color == RED)) {
                            node->parent->parent->left->Color = BLACK;
                            node->parent->parent->right->Color = BLACK;
                            node->parent->parent->Color = RED;
                        }

                        // if the parent is the right side and the parent's sibling is black then rotate
                        else if ((node->parent->parent->left->Color == BLACK) && (node->parent->parent->right->Color == RED)) {
                            // check where grandparent is if it exists
                            bool isRight = true;
                            if (node->parent->parent->parent != nullptr) {
                                if (node->parent->parent->parent->right == node->parent->parent) isRight = true;
                                else isRight = false;
                            }

                            // check if there is a right sibling that is black
                            if (node->parent->right->Color == BLACK) {
                                node->parent->left = node->right; // set the parent's left to the right branch
                                node->parent->left->parent = node->parent; // set the right branch's parent to the parent
                                // at this point the right branch believes its parent is the parent instead of the node and the parent should now believe that its left branch is the node's left branch

                                node->right = node->parent; // now set the node's right branch to the parent
                                node->parent = node->right->parent; // set the parent to the former parent's parent (they still believe it is their old parent)
                                node->right->parent = node; // set the former parent's parent to this node

                                node = node->right; // sets the node to the former right branch, there is another rotation to do
                                node->parent->parent->right = node->parent; // make sure the grandparent realizes its right is the parent
                            }

                            // the left sibling should be black now
                            node->parent->parent->right = node->parent->left; // set the right branch of the grandparent to the parent's current left branch
                            node->parent->parent->right->parent = node->parent->parent; // set that right branch's parent to the grandparent
                            // at this point the parent's left branch believes its parent is the grandparent and the grandparent should now believe that its right branch is the parent's left branch

                            node->parent->left = node->parent->parent; // now set the parent's left branch to the grandparent
                            node->parent->parent = node->parent->left->parent; // set the new grandparent to the former grandparent's parent (they still believe it is their old parent)
                            node->parent->left->parent = node->parent; // set the former grandparent's parent to this parent
                            if (node->parent->parent != nullptr) { // make sure the grandparent realizes its child is different is the parent (if it exists)
                                if (isRight) node->parent->parent->right = node->parent;
                                else node->parent->parent->left = node->parent;
                            }

                            // adjust the colours after the swap
                            node->parent->left->Color = RED;
                            node->parent->Color = BLACK;
                        }

                        // if the parent is the left side and the parent's sibling is black then rotate
                        else if ((node->parent->parent->right->Color == BLACK) &&(node->parent->parent->left->Color == RED)) {
                            // check where grandparent is if it exists
                            bool isLeft = true;
                            if (node->parent->parent->parent != nullptr) {
                                if (node->parent->parent->parent->left == node->parent->parent) isLeft = true;
                                else isLeft = false;
                            }

                            // check if there is a left sibling that is black
                            if (node->parent->left->Color == BLACK) {
                                node->parent->right = node->left; // set the parent's right to the left branch
                                node->parent->right->parent = node->parent; // set the left branch's parent to the parent
                                // at this point the left branch believes its parent is the parent instead of the node and the parent should now believe that its right branch is the node's right branch

                                node->left = node->parent; // now set the node's left branch to the parent
                                node->parent = node->left->parent; // set the parent to the former parent's parent (they still believe it is their old parent)
                                node->left->parent = node; // set the former parent's parent to this node

                                node = node->left; // sets the node to the former left branch, there is another rotation to do
                                node->parent->parent->left = node->parent; // make sure the grandparent realizes its left is the parent
                            }

                            // the right sibling should be black now
                            node->parent->parent->left = node->parent->right; // set the left branch of the grandparent to the parent's current right branch
                            node->parent->parent->left->parent = node->parent->parent; // set that left branch's parent to the grandparent
                            // at this point the parent's right branch believes its parent is the grandparent and the grandparent should now believe that its left branch is the parent's right branch

                            node->parent->right = node->parent->parent; // now set the parent's right branch to the grandparent
                            node->parent->parent = node->parent->right->parent; // set the new grandparent to the former grandparent's parent (they still believe it is their old parent)
                            node->parent->right->parent = node->parent; // set the former grandparent's parent to this parent
                            if (node->parent->parent != nullptr) { // make sure the grandparent realizes its child is different is the parent (if it exists)
                                if (isLeft) node->parent->parent->left = node->parent;
                                else node->parent->parent->right = node->parent;
                            }

                            // adjust the colours after the swap
                            node->parent->right->Color = RED;
                            node->parent->Color = BLACK;
                        }
                    }

                    // if the parent is the right side and the parent's sibling is null then do a swap
                    else if (node->parent->parent->right) {
                        // check where grandparent is if it exists
                        bool isRight = true;
                        if (node->parent->parent->parent != nullptr) {
                            if (node->parent->parent->parent->right == node->parent->parent) isRight = true;
                            else isRight = false;
                        }

                        // if this is the left node then swap with the parent node
                        if (node->value < node->parent->value) {
                            node->right = node->parent; // set the right to the old parent
                            node->parent = node->right->parent; // set the parent to the right's parent (they still think it is the grandparent)
                            node->right->parent = node; // set the right's parent to this node
                            node->right->left = nullptr; // set the left of the right to null, since it is no longer this node
                            node->parent->right = node; // make sure the parent knows that this node is the right
                            node = node->right; // set this node to the right node (now this node will be the right node for the actual swap)
                        }

                        // actual swap
                        node->parent->left = node->parent->parent; // set the parent's left to the grandparent
                        node->parent->parent = node->parent->left->parent; // set the parent's parent to the left's parent (they still think it is the grandparent)
                        node->parent->left->right = nullptr; // set the parent's left's right to null (where the parent was before the swap)
                        node->parent->left->parent = node->parent; // set the parent's left's parent to the parent (the parent has already swapped the correct parent)
                        if (node->parent->parent != nullptr) { // make sure the grandparent realizes its child is different is the parent (if it exists)
                            if (isRight) node->parent->parent->right = node->parent;
                            else node->parent->parent->left = node->parent;
                        }

                        // adjust colours after the swap
                        node->parent->Color = BLACK;
                        node->parent->left->Color = RED;
                    }

                    // if the parent is the left side and the parent's sibling is null then do a swap
                    else if (node->parent->parent->left) {
                        // check where grandparent is if it exists
                        bool isLeft = true;
                        if (node->parent->parent->parent != nullptr) {
                            if (node->parent->parent->parent->left == node->parent->parent) isLeft = true;
                            else isLeft = false;
                        }

                        // if this is the right node then swap with the parent node
                        if (node->value > node->parent->value) {
                            node->left = node->parent; // set the left to the old parent
                            node->parent = node->left->parent; // set the parent to the left's parent (they still think it is the grandparent)
                            node->left->parent = node; // set the left's parent to this node
                            node->left->right = nullptr; // set the right of the left to null, since it is no longer this node
                            node->parent->left = node; // make sure the parent knows that this node is the left
                            node = node->left; // set this node to the left node (now this node will be the left node for the actual swap)
                        }

                        // actual swap
                        node->parent->right = node->parent->parent; // set the parent's right to the grandparent
                        node->parent->parent = node->parent->right->parent; // set the parent's parent to the right's parent (they still think it is the grandparent)
                        node->parent->right->left = nullptr; // set the parent's right's left to null (where the parent was before the swap)
                        node->parent->right->parent = node->parent; // set the parent's right's parent to the parent (the parent has already swapped the correct parent)
                        if (node->parent->parent != nullptr) { // make sure the grandparent realizes its child is different is the parent (if it exists)
                            if (isLeft) node->parent->parent->left = node->parent;
                            else node->parent->parent->right = node->parent;
                        }

                        // adjust colours after the swap
                        node->parent->Color = BLACK;
                        node->parent->right->Color = RED;
                    }
                }
                if (node->parent != nullptr) node = node->parent; // set the node to the parent if it's not at the top of the tree
            }
            // if the colour is red change it to black (should be the top node by this point)
            if (node->Color == RED) node->Color = BLACK;
        }
    }
}

// search for a node in the tree
bool RedBlackTree::search(const int subject, RedBlackTreeNode* observatory) {
    RedBlackTreeNode* copier(observatory); // creates copy of the node to search through

    if (subject == copier->value) return true; // return true if the value is found
    // if the subject is less than the current value then check if the left exists before entering
    else if (subject < copier->value) {
        if (copier->left) {
            return search(subject, copier->left);
        }
        else return false;
    }
    // if the subject is more or equal to the current value then check if the right exists before entering
    else if (subject >= copier->value) {
        if (copier->right) {
            return search(subject, copier->right);
        }
        else return false;
    }
}

// delete a node from the tree
bool RedBlackTree::deletion(const int fired) {
    bool deleted = false;
    // make sure the number is actually in the tree
    if (search(fired, node)) {
        // loop through the tree until you delete the node
        while (!deleted) {
            // delete the value when you find it
            if (fired == node->value) {
                RedBlackTreeNode* dummy(node); // create dummy node to process deletion

                // if the node to delete has two children then swap with largest node in left
                if ((node->left) && (node->right)) {
                    // set the dummy to the largest node in the left
                    dummy = node -> left;
                    while (dummy->right) {
                        dummy = dummy -> right;
                    }

                    node -> value = dummy -> value; // set the node's value to the dummy's value

                    // checks if the dummy is on the right side before nullifying itself from the parent
                    if (dummy->parent->right) {
                        // checks if the dummy had a left child
                        if (dummy->left) {
                            dummy->left->Color = BLACK;
                            dummy->parent->left = dummy->left;
                            dummy->left->parent = dummy->parent;
                        }
                        else dummy->parent->right = nullptr;
                    }
                    else if (dummy->parent->left) {
                        // checks if the dummy had a left child
                        if (dummy->left) {
                            dummy->left->Color = BLACK;
                            dummy->parent->right = dummy->left;
                            dummy->left->parent = dummy->parent;
                        }
                        dummy->parent->left = nullptr;
                    }

                    delete dummy; // free memory
                    while (node->parent) node = node->parent; // rotate back to top
                    deleted = true;
                }

                // if the node to delete has one child then swap with parent
                if (((node->left) && !(node->right)) || ((node->right) && !(node->left))) {
                    // check which child exists before deleting
                    if (node->left) {
                        dummy = node->left;

                        node->value = dummy->value;
                        node->left = nullptr;
                    }
                    else if (node->right) {
                        dummy = node->right;

                        node->value = dummy->value;
                        node->right = nullptr;
                    }

                    node->Color = BLACK;
                    delete dummy; // free memory
                    while (node->parent) node = node->parent; // rotate back to top
                    deleted = true;
                }

                // if the node has no children then delete
                if (!(node->left) && !(node->right)) {
                    // if the node has a parent make its child null
                    if (node->parent) {
                        // check which side the node is on before deleting
                        if (node->parent->left) {
                            if (node->parent->left == node) {
                                // check where parent is
                                bool isLeft = true;
                                if (node->parent->parent != nullptr) {
                                    if (node->parent->parent->left == node->parent->parent) isLeft = true;
                                    else isLeft = false;
                                }

                                node = node->parent;
                                dummy = node->left;
                                node->left = nullptr;
                                delete dummy; // free memory
                                deleted = true;

                                // check if the other side exists to fix
                                if (node->right) {
                                    // take the left kid of the other side as your right
                                    if (node->right->left) {
                                        node->right = node->right->left;
                                        node->right->parent->parent = node->parent;
                                        node->right->parent->left = node;
                                        node->parent->right = node->right->parent;
                                        node->parent = node->right->parent;
                                        node->right->parent = node;
                                        node->parent->Color = BLACK;
                                        node->right->Color = RED;
                                    }
                                    else if (node->right->right) { // check again if the right kid exists, since we already know the left kid doesn't
                                        node->right->left = node;
                                        node->right->parent = node->parent;
                                        node->parent = node->right;
                                        node->right = nullptr;
                                        if (node->parent->parent) {
                                            if (isLeft) node->parent->parent->left = node->parent;
                                            else node->parent->parent->right = node->parent;
                                        }

                                        // mess with the colours
                                        if ((node->parent->left->Color == RED) && (node->parent->left->Color == RED)) {
                                            node->parent->left->Color = BLACK;
                                            node->parent->right->Color = BLACK;
                                            node->parent->Color = RED;
                                        }
                                        else {
                                            node->parent->left->Color = BLACK;
                                            node->parent->right->Color = BLACK;
                                            node->parent->Color = BLACK;
                                        }
                                    }
                                    else {
                                        node->Color = BLACK;
                                        node->right->Color = RED;
                                    }
                                }
                            }
                        }
                        if (!deleted) { // only check right side if not already deleted
                            // check where parent is
                            bool isRight = true;
                            if (node->parent->parent != nullptr) {
                                if (node->parent->parent->right == node->parent->parent) isRight = true;
                                else isRight = false;
                            }

                            node = node->parent;
                            dummy = node->right;
                            node->right = nullptr;
                            delete dummy; // free memory
                            deleted = true;

                            // check if the other side exists to fix
                            if (node->left) {
                                // take the right kid of the other side as your left if it exists
                                if (node->left->right) {
                                    node->left = node->left->right;
                                    node->left->parent->parent = node->parent;
                                    node->left->parent->right = node;
                                    node->parent->left = node->left->parent;
                                    node->parent = node->left->parent;
                                    node->left->parent = node;
                                    node->parent->Color = BLACK;
                                    node->left->Color = RED;
                                }
                                else if (node->left->left) { // check again if the left kid exists, since we already know the right kid doesn't
                                    node->left->right = node;
                                    node->left->parent = node->parent;
                                    node->parent = node->left;
                                    node->left = nullptr;
                                    if (node->parent->parent) {
                                        if (isRight) node->parent->parent->right = node->parent;
                                        else node->parent->parent->left = node->parent;
                                    }

                                    // mess with the colours
                                    if ((node->parent->right->Color == RED) && (node->parent->right->Color == RED)) {
                                        node->parent->right->Color = BLACK;
                                        node->parent->right->Color = BLACK;
                                        node->parent->Color = RED;
                                    }
                                    else {
                                        node->parent->right->Color = BLACK;
                                        node->parent->left->Color = BLACK;
                                        node->parent->Color = BLACK;
                                    }
                                }
                                else {
                                    node->Color = BLACK;
                                    node->left->Color = RED;
                                }
                            }
                        }
                        while (node->parent) node = node->parent; // rotate back to top
                    }
                    else node = new RedBlackTreeNode(); // if no kids and no parent then this is the first child
                }
            }
            // look in the left or right for the value (we know it's in here so no need to check if it exists)
            else if (fired < node->value) node = node->left;
            else if (fired >= node->value) node = node->right;
        }
        return deleted;
    }
    else return deleted; // there was not a successful deletion
}