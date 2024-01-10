//
// Created by Vincent Chu on 4/30/2023.
//

#include "RedBlackTree.h"
#include <iostream>
using namespace std;

int main() {
    RedBlackTree* test = new RedBlackTree();
    test->insertion(78);
    test->insertion(56);
    test->insertion(97);
    test->insertion(80);
    test->insertion(190);
    test->insertion(33);
    test->insertion(60);
    test->insertion(400);
    test->insertion(500);
    test->insertion(777);
    test->insertion(20);
    test->insertion(23);
    test->insertion(14);
    cout << "Adding these numbers to the Red Black Tree: ";
    test->inOrder();
    cout << endl;

    cout << "Our Red Black Tree in PreOrder: ";
    test->preorder();
    cout << "Our Red Black Tree in PostOrder: ";
    test->postorder();
    cout << "Our Red Black Tree in InOrder: ";
    test->inOrder();
    cout << endl;

    cout << "Deleting numbers 97, 78, 3, 60, 44 from our Red Black Tree and printing it" << endl;
    test->deletionResult(test->deletion(97));
    test->deletionResult(test->deletion(78));
    test->deletionResult(test->deletion(3));
    test->deletionResult(test->deletion(60));
    test->deletionResult(test->deletion(44));
    test->preorder();
    cout << endl;

    cout << "Inserting numbers 40, 67, 75, 77 into our Red Black Tree and printing it" << endl;
    test->insertion(40);
    test->insertion(67);
    test->insertion(75);
    test->insertion(77);
    test->preorder();
    cout << endl;

    cout << "Deleting numbers 56, 23 from our Red Black Tree and printing it" << endl;
    test->deletionResult(test->deletion(56));
    test->deletionResult(test->deletion(23));
    test->preorder();
    cout << endl;

    return 0;
}