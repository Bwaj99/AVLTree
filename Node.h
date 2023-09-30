#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node {
    public:
        Node(string); //initialize node with a specific string value
        Node();
        string data = ""; //initialized with an empty string by default
        int height = 0;
        Node* left = nullptr; //pointer to the left child node
        Node* right; //pointer to the right child node, value is undefined
        Node* parent; //pointer to the parent node, value is undefined
}; 

#endif