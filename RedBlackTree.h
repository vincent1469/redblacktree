//
// Created by Vincent Chu on 4/30/2023.
//

#ifndef ASSIGNMENT_5_REDBLACKTREE_H
#define ASSIGNMENT_5_REDBLACKTREE_H
#include "RedBlackTreeNode.h"
#include <iostream>
#include <array>
#include <iterator>
using namespace std;


class RedBlackTree {
    friend class RedBlackTreeNode;

    public:
        RedBlackTreeNode* node;

        // default constructor
        RedBlackTree() {
            node = new RedBlackTreeNode();
        }

        RedBlackTree(const RedBlackTree& copy) { // copy constructor
            node = new RedBlackTreeNode(*copy.node);
            capybara(node, copy.node);
        }

        RedBlackTree operator=(const RedBlackTree& original) { // = operator to set a RedBlackTree to another RedBlackTree
            if (this != &original) {
                delete node;
                node = new RedBlackTreeNode(*original.node);
                capybara(node, original.node);
            }
            return *this;
        }

        // destructor
        ~RedBlackTree() {
            delete node;
        }

        // copy the branches of the tree until they are null
        void capybara(RedBlackTreeNode* copying, RedBlackTreeNode* og) {
            // if there's a left value copy it
            if (og->left) {
                copying->left = new RedBlackTreeNode(*og->left);
                capybara(copying->left,og->left);
            }
            // if there's a right value copy it
            if (og->right) {
                copying->right = new RedBlackTreeNode(*og->right);
                capybara(copying->right,og->right);
            }
        }

        // define functions used by the RedBlackTree
        void insertion(const int subject); // insert number into the tree
        void fix(); // insert number into RedBlackTree
        bool search(const int subject, RedBlackTreeNode* observatory); // search for a node in the tree
        bool deletion(const int subject); // delete a node from the tree
        void deletionResult(const bool result) {
            if (result) cout << "Deletion successful!" << endl;
            else cout << "Deletion unsuccessful!" << endl;
        }

        // print tree in preorder
        void preorder() {
            RedBlackTree* og(this); // creates copy of the RedBlackTree to print
            prebranching(og->node);
            cout << endl;
        }

        // recursive helper for printing in pre order
        void prebranching(RedBlackTreeNode* printer) {
            /*cout << "     ";
            cout << printer->getLeft() << " ";
            cout << printer->getRight() << " ";
            cout << printer->getParent() << " ";
            cout << printer->Color << " ";*/
            cout << printer->value << " ";
            if (printer->left) prebranching(printer->left);
            if (printer->right) prebranching(printer->right);
        }

        // print tree in postorder
        void postorder() {
            RedBlackTree* og(this); // creates copy of the RedBlackTree to print
            postbranching(og->node);
            cout << endl;
        }

        // recursive helper for printing in pre order
        void postbranching(RedBlackTreeNode* printer) {
            if (printer->left) postbranching(printer->left);
            if (printer->right) postbranching(printer->right);
            cout << printer->value << " ";
        }

        // print RedBlackTree in inorder
        void inOrder() {
            RedBlackTree* og(this); // creates copy of the RedBlackTree to print

            // initializing
            int treegirth = inbranching(0, og->node); // finds amount of nodes in RedBlackTree
            int collection[treegirth]; // creates array of integers of the size that was just found
            for (int i = 0; i < treegirth; i++) collection[i] = 0; // set all values in array to 0

            // storing and sorting
            instoring(collection, treegirth, og->node); // stores everything into the collection
            for (int j = 0; j < treegirth; j++) {
                int small = collection[j]; // intializes variable for the smallest value left in the array
                for (int k = j; k < treegirth; k++) if (collection[k] < small) small = collection[k]; // finds the smallest value in the order of the array

                // finds where that smallest variable is and swaps it
                for (int m = j; m < treegirth; m++) {
                    if (collection[m] == small) {
                        collection[m] = collection[j];
                        collection[j] = small;
                    }
                }
            }

            // prints array after being sorted
            for (int i = 0; i < treegirth; i++) {
                cout << collection[i] << " ";
            }
            cout << endl;
        }

        // recursive helper to find amount of nodes in RedBlackTree
        int inbranching(int count, RedBlackTreeNode* printer) {
            // increments whenever the function is called
            // function is called when a new node is discovered
            count++;
            if (printer->left) count = inbranching(count, printer->left);
            if (printer->right) count = inbranching(count, printer->right);
            return count;
        }

        // recursive helper to store all the nodes into the newly created array
        void instoring(int *items, const int girth, RedBlackTreeNode* printer) {
            // loop until there's an empty spot on the array then store the value of the node
            for (int i = 0; i < girth; i++) {
                if (items[i] == 0) {
                    items[i] = printer->value;
                    break;
                }
            }

            if (printer->left) instoring(items, girth, printer->left);
            if (printer->right) instoring(items, girth, printer->right);
        }
};


#endif //ASSIGNMENT_5_REDBLACKTREE_H
