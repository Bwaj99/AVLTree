#include "AVLTree.h"
#include "Node.h"
#include<iostream>
#include<fstream>
#include<ostream>

using namespace std;

AVLTree::AVLTree() {
    root = nullptr;
}

void AVLTree::insert(const string &newData) { //creates a new node with the provided data and handles the case of inserting the first node into an empty AVL tree
    Node* newNode = new Node(newData);
    if (root == nullptr){
        root = newNode;
        root->parent = nullptr;
        return;
    }

    Node* current = root;
    while (current != nullptr){ //traverses the AVL tree to find the appropriate position to insert the newNode while maintaining the binary search tree property
        if (newNode->data == current->data){
            current = nullptr;
        }
        else if (newNode->data < current->data){
            if (current->left == nullptr){
                current->left = newNode;
                newNode->parent = current;
                current = nullptr;
            }
            else{
                current = current->left;
            }
        }
        else{
            if(current->right == nullptr){
                current->right = newNode;
                newNode->parent = current;
                current = nullptr;
            }
            else{
                current = current->right;
            }
        }
    }
    newNode = newNode->parent; //reassigns
    while(newNode != nullptr){ //performs necessary rotations on the AVL tree after inserting a new node
        rotate(newNode);
        newNode = newNode->parent;
    }
}

void AVLTree::visualizeTree(const string &outputFilename){ //given by instructions
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){ //given by instructions
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}

Node* AVLTree::findUnbalancedNode(Node* temp) { //recursively searches for an unbalanced node in the AVL tree and returns a pointer to the first unbalanced node found
    Node* nodeUnbalanced = nullptr;
    if ((balanceFactor(temp) == -2) || (balanceFactor(temp) == 2)){
        nodeUnbalanced = temp;
    }
    else{
        nodeUnbalanced = findUnbalancedNode(temp->left);
        nodeUnbalanced = findUnbalancedNode(temp->right);
    }

    return nodeUnbalanced;
}
void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::rotate(Node* current) { //performs rotation operations on a given node to restore the balance of the AVL tree.
    updateHeight(current);

    if (balanceFactor(current) == -2){
        if (balanceFactor(current->right) == 1){
            rotateRight(current->right);
        }
        rotateLeft(current);
    }
    else if (balanceFactor(current) == 2){
        if (balanceFactor(current->left) == -1){
            rotateLeft(current->left);
        }
        rotateRight(current);
    }
}

void AVLTree::rotateRight(Node* userNode) {
    Node* rightChildofLeft = userNode->left->right;
    if(userNode->parent != nullptr){
        replaceChild(userNode->parent, userNode, userNode->left);
    }
    else{
        root = userNode->left;
        root->parent = nullptr;
    }

    setChild(userNode->left, "right", userNode);
    setChild(userNode, "left", rightChildofLeft);

}

void AVLTree::rotateLeft(Node *userNode) {
    Node* leftChildofRight = userNode->right->left;
    if (userNode->parent != nullptr){
        replaceChild(userNode->parent, userNode, userNode->right);
    }
    else{ // node is root
        root = userNode->right;
        root->parent = nullptr;
    }

    setChild(userNode->right, "left", userNode);
    setChild(userNode, "right", leftChildofRight);
}

void AVLTree::printBalanceFactors(Node* node) { //ecursively prints the balance factor of each node in the AVL tree in an in-order traversal
    if (node != nullptr){
        printBalanceFactors(node->left);
        cout << node->data << "(" << balanceFactor(node) << "), ";
        printBalanceFactors(node->right);
    }
    else{
        return;
    }
}

int AVLTree::balanceFactor(Node* temp) { //calculates and returns the balance factor of a given node in the AVL tree
    int leftHeight = -1;
    if (temp->left != nullptr){
        leftHeight = temp->left->height;
    }

    int rightHeight = -1;
    if (temp->right != nullptr){
        rightHeight = temp->right->height;
    }

    return (leftHeight - rightHeight);
}

void AVLTree::updateHeight(Node* temporaryNode){ //updates the height of a given node based on the heights of its left and right subtrees
    int leftHeight = -1;
    if (temporaryNode->left != nullptr){
        leftHeight = temporaryNode->left->height;
    }

    int rightHeight = -1;
    if (temporaryNode->right != nullptr){
        rightHeight = temporaryNode->right->height;
    }

    temporaryNode->height = (max(leftHeight, rightHeight) + 1);
}

void AVLTree::setChild(Node* newParent, string chooseChild, Node* child) { //sets a child node for a given parent node based on the specified direction 
    if (chooseChild != "left" && chooseChild != "right"){
        return;
    }
    if (chooseChild == "left"){
        newParent->left = child;
    }
    else{
        newParent->right = child;
    }
    if (child != nullptr){
        child->parent = newParent;
    }
    
    updateHeight(newParent);
}

void AVLTree::replaceChild(Node* parent, Node* currentChild, Node* newChild) { //replaces a child node of a given parent node with a new child node
    if (parent->left == currentChild){
        setChild(parent, "left", newChild);
    }
    else if (parent->right == currentChild){
        setChild(parent, "right", newChild);
    }
}