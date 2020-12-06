#include"Tree.hpp"

Node::Node(){
    right = NULL;
    left = NULL;
    father = NULL;
    data = "";
}
Node::Node(std::string data){
    right = NULL;
    left = NULL;
    father = NULL;
    this->data = data;
}

Node* Node::get_right(){
    return this->right;
}

Node* Node::get_left(){
        return this->left;
}

Node* Node::get_father(){
        return this->father;
}

std::string Node::get_data(){
        return this->data;
}

Node* Node::set_right(Node* n){
    this->right = n;
}

Node* Node::set_left(Node* n){
    this->left = n;
}

Node* Node::set_father(Node* n){
    this->father = n;
}

std::string Node::set_data(std::string data){
    this->data = data;
}


Node::~Node(){}

Tree::Tree(){
    Node *newNode = new Node();
    this->head = newNode;
    this->counter = 1;
}

Node* Tree::get_head(){
    return this->head;
}
int Tree::get_counter(){
    return this->counter;
}

Node* Tree::set_head(Node* n){
    this->head = n;
}

Tree::~Tree(){}