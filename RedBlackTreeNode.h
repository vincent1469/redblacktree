//
// Created by Vincent Chu on 4/29/2023.
//

#ifndef ASSIGNMENT_5_REDBLACKTREENODE_H
#define ASSIGNMENT_5_REDBLACKTREENODE_H

enum ColorType { RED, BLACK };

class RedBlackTreeNode
{
    friend class RedBlackTree;

    private:
        int value;
        ColorType Color;
        RedBlackTreeNode* parent;
        RedBlackTreeNode* left;
        RedBlackTreeNode* right;

    public:
        //Constructor
        RedBlackTreeNode()
            :value(0), Color(RED), left(nullptr), right(nullptr), parent(nullptr)
        {}

        //Explicit Value Constructor
        RedBlackTreeNode(int inValue, ColorType color, RedBlackTreeNode* inLeft = nullptr, RedBlackTreeNode* inRight = nullptr, RedBlackTreeNode* inParent = nullptr)
            :value(inValue), left(inLeft), right(inRight), parent(inParent), Color(color)
        {}

        //Copy Constructor
        RedBlackTreeNode(const RedBlackTreeNode& copy) { // copy constructor
            value = copy.value;
            Color = copy.Color;
            parent = copy.parent;
            left = copy.left;
            right = copy.right;
        }

        //Getter Function
        inline int getValue() const
        {
            return value;
        }

        //Getter Function
        inline int getLeft() const
        {
            if (left != nullptr) return left->value;
            else return -999;
        }

        //Getter Function
        inline int getRight() const
        {
            if (right != nullptr) return right->value;
            else return -999;
        }

        //Getter Function
        inline int getParent() const
        {
            if (parent != nullptr) return parent->value;
            else return -999;
        }

        inline ColorType getColor() const
        {
            return Color;
        }

        //Setter Function
        inline void setValue(int newVal)
        {
            value = newVal;
        }

        inline void setColor(ColorType color)
        {
            Color = color;
        }

        RedBlackTreeNode operator=(const RedBlackTreeNode& original) { // = operator to set a child RedBlackTreeNode to another RedBlackTreeNode
            RedBlackTreeNode* equal = new RedBlackTreeNode;
            equal->value = original.value;
            equal->Color = original.Color;
            equal->parent = original.parent;
            equal->left = original.left;
            equal->right = original.right;
            return *equal;
        }
};

#endif //ASSIGNMENT_5_REDBLACKTREENODE_H