#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>

#include "convertToBinary.hpp"
#include "Tree.hpp"

Tree tree;
int A,B,C,D,N;

string prefix(string ip){
    string divides_ip = "";
    int counter = 0;
    for(char& c : ip) {
        if (c == '.' || c == '/') {
            stringstream ss(divides_ip);
            switch (counter)
            {
            case 0:
                ss >> A;
                break;

            case 1:
                ss >> B;
                break;

            case 2:
                ss >> C;
                break;

            case 3:
                ss >> D;
                break;
            default:
                break;
            }
            divides_ip = "";
            counter++;
        }
        else divides_ip += c;
    }
    return divides_ip;
}

void ADD(string ip, string result){
    string divides_ip = prefix(ip);
    stringstream ss(divides_ip);
    ss >> N;
    string binary = toBinary(A) + toBinary(B) + toBinary(C) + toBinary(D);
    Node* root = tree.get_head();
    int depth = 1;
    for (size_t i = 0; i < N; i++) {
        depth++;
        if (binary[i] == '0'){
            if (root->get_left() == nullptr){
                root->set_left(new Node());
                root->get_left()->set_father(root);
                tree.counter++;
                root = root->get_left();
            }
            else root = root->get_left();
        }
        else{
            if (root->get_right() == nullptr){
                root->set_right(new Node());
                root->get_right()->set_father(root);
                tree.counter++;
                root = root->get_right();
            }
            else root = root->get_right();
        }
    }
    root->set_data(result);



    cout << "Added " << ip << " A at the depth " << depth << ", total nodes " << tree.get_counter() <<endl;
}

void FIND(string ip){

    string divides_ip = prefix(ip);
    stringstream ss(divides_ip);
    ss >> D;
    string binary = toBinary(A) + toBinary(B) + toBinary(C) + toBinary(D);
    Node* root = tree.get_head();
    Node* ans = nullptr;
    int depth = 0;
    int subnetMask = 0;
    for(size_t i = 0; i < binary.size(); i++){
        depth++;
        if (binary[i] == '0'){
            if (root->get_left() != nullptr){
                if (root->get_left()->get_data() != ""){
                    ans = root->get_left();
                    subnetMask = depth;
                }
                root = root->get_left();
            }
            else break;
        }
        else {
            if (root->get_right() != nullptr){
                if (root->get_right()->get_data() != ""){
                    ans = root->get_right();
                    subnetMask = depth;
                }
                root = root->get_right();
            }
            else break; 
        }
    }
    if (ans == nullptr){
        cout << "ip not exists" << endl;
        return;
    }
    cout << "Found " << ip << " " << ans->get_data() << " at the depth " << depth << endl; 
}

void REMOVE(string ip, string result){

    string divides_ip = "";
    char counter = 0;
    stringstream ss(divides_ip);
    ss >> N;
    string binary = toBinary(A) + toBinary(B) + toBinary(C) + toBinary(D);
    Node* root = tree.get_head();
    int depth = 1;
    for(size_t i = 0; i < N; i++){
        depth++;
        if (binary[i] == '0'){
            if (root->get_left() != nullptr){
                root = root->get_left();
            }
            else break;
        }
        else {
            if (root->get_right() != nullptr){
                root = root->get_right();
            }
            else break; 
        }
    }
    if (root == tree.get_head()){
        cout << "ip not exists" << endl;
        return;
    }

    if (root->get_data() != result){
        cout << result << " "  << root->get_data() <<endl;
        cout << "ip exists but does not match the result" << endl;
        return;
    }
    Node* deletion = nullptr;
    int flag = 1;
    while(flag){
        if(root != nullptr){
            if (root->get_data() == "" || root->get_data() == result){
                deletion = root;
                root = deletion->get_father();
                if (deletion->get_left() != nullptr || deletion->get_right() != nullptr){
                    deletion->get_data() = "";
                    deletion = nullptr;
                }
                else if(deletion->get_father() == nullptr){
                    deletion->get_data() = "";
                    deletion = nullptr;
                }
                else{
                    if(deletion == root->get_left()) root->set_left(nullptr);
                    if(deletion == root->get_right()) root->set_right(nullptr);
                    delete deletion;
                    tree.counter--;
                }
            }
            else flag = 0;
        }
        else flag = 0;
    }
    cout << "Removed " << ip << " at the depth " << depth << " total nodes " << tree.get_counter() << endl;


}