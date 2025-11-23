#include<bits/stdc++.h>

using namespace std;

struct Node{
    int data;
    Node* next = nullptr;
    Node* prev = nullptr;
};

Node* head = nullptr;

void insertAtHead(int val){
    Node* newNode = new Node();
    newNode->data = val;
    newNode->next = head;
    cout << newNode->data << "\n";
    if (head->next != nullptr){
        head->next->prev = newNode;
    }
    head = newNode;
}

void insertAtTail(int val){
    Node* cur = head;
    while (cur->next != nullptr){
        cout << cur-> data << endl;
        cur = cur->next;
    
    }
    Node* newNode = new Node();
    newNode->data = val;
    newNode->prev = cur;
    cur->next = newNode;
    
}

void insertAfter(int refval, int val){
    Node* cur = head;
    bool found = false;
    while (cur->next != nullptr && !found){
        cur = cur->next;
        if (cur->data == refval){
            found = true;
        }
    }
    Node* newNode = new Node();
    newNode->data = val;
    newNode->prev = cur;
    newNode->next = cur->next;
    newNode->next->prev = newNode;
    cur->next = newNode;
}

void displayForward(){
    Node* cur = head;
    while (cur->next != nullptr){
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << "\n";
}

void displayBackward(){
    Node* cur = head;
    while (cur->next != nullptr){
        cur = cur->next;
    }
    while (cur != head){
        cout << cur->data << " ";
        cur = cur->prev;
    }
    cout << cur->data << "\n";
}

bool search(int key){
    Node* cur = head;

    bool found = false;
    while (cur->next != nullptr && !found){
        cur = cur->next;
        if (cur->data == key){
            found = true;
        }
    }

    return found;
}


void deleteVal(int val){
    Node* cur = head;

    bool found = false;
    while (cur->next != nullptr && !found){
        cur = cur->next;
        if (cur->next->data == val){
            found = true;
        }
    }

    if (found) {
        cur->next = cur->next->next;
        cur->next->prev = cur;
        free(cur);
    }
    else cout<< "Not found" <<"\n";
}




int main(){
    insertAtHead(10);
    insertAtTail(20);
    insertAtTail(30);

    displayBackward();
}