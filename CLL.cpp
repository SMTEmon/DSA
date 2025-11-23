#include<bits/stdc++.h>

using namespace std;

struct Node{
    int data;
    Node* next = nullptr;
};

Node* head = nullptr;

void insertAtTail(int val){

    Node* newNode = new Node();

    if (head == nullptr){
        head = newNode;
        head ->next = head;
        return;
    }

    Node* cur = head;
    while (cur->next != head){
        cur = cur->next;
    }
    newNode->data = val;
    newNode->next = head;
    cur->next = newNode;
}

void insertAfter(int refval, int val){
    Node* cur = head;
    bool found = false;
    while (cur->next != head && !found){
        cur = cur->next;
        if (cur->data == refval){
            found = true;
        }
    }
    Node* newNode = new Node();
    newNode->data = val;
    newNode->next = cur->next;
    cur->next = newNode;
}

void display(){
    Node* cur = head;
    while (cur->next != head){
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << cur->data;
    cout << "\n";
}

bool search(Node* head, int key){
    Node* cur = head;

    bool found = false;
    while (cur->next != head && !found){
        cur = cur->next;
        if (cur->data == key){
            found = true;
        }
    }

    return found;
}

void update (Node* head, int oldVal, int newVal){
    Node* cur = head;

    bool found = false;
    while (cur->next != head && !found){
        cur = cur->next;
        if (cur->data == oldVal){
            found = true;
        }
    }

    if (found) cur->data = newVal;
    else cout<< "Not found" <<"\n";
}

void deleteVal(Node* head, int val){
    Node* cur = head;

    if (cur == head && cur->data == val){
            Node* temp = head->next;
            while (temp != head){
                temp = temp->next;
            }
            temp->next = cur->next;
            free(cur);
            return;
        }

    bool found = false;
    while (cur->next != head && !found){
        cur = cur->next;
        if (cur->next->data == val){
            found = true;
        }
    }

    if (found) {
        cur->next = cur->next->next;
        free(cur);
    }
    
    else cout<< "Not found" <<"\n";
}




int main(){
    insertAtTail(20);
    insertAtTail(30);

    display();

}