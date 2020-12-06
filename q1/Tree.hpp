#include <iostream>

class Node{
private:  
    Node* right;
    Node* left;
    Node* father;
   // Node* son;
    std::string data;

public:
    Node();
    Node(std::string data);
    Node* get_right();
    Node* get_left();
    Node* get_father();
    std::string get_data();

    Node* set_right(Node* n);
    Node* set_left(Node* n);
    Node* set_father(Node* n);
    std::string set_data(std::string data);

    ~Node();
};

class Tree{
private:
    Node* head;
    
public:
    int counter;
    Node* get_head();
    int get_counter();

    Node* set_head(Node* n);

    Tree();
    ~Tree();
};