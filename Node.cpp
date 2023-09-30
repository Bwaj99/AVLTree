#include <string>
#include "Node.h"

Node::Node(): data(""), height(0), left(nullptr), right(nullptr), parent(nullptr) {} //initializes a node object without any parameters and sets default values for each object

Node::Node(string userString) : data(userString), height(0), left(nullptr), right(nullptr), parent(nullptr) {} //creates node object with a specific string value while initializing the other member variables to default values