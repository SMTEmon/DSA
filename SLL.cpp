#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    Node *next = nullptr;
};

Node *head = nullptr;

void insertAtHead(int val)
{
    Node *newNode = new Node();
    newNode->data = val;
    newNode->next = head;
    head = newNode;
}

void insertAtTail(int val)
{
    Node *cur = head;
    while (cur->next != nullptr)
    {
        cur = cur->next;
    }
    Node *newNode = new Node();
    newNode->data = val;
    cur->next = newNode;
}

void insertAfter(int refval, int val)
{
    Node *cur = head;
    bool found = false;
    while (cur->next != nullptr && !found)
    {
        cur = cur->next;
        if (cur->data == refval)
        {
            found = true;
        }
    }
    Node *newNode = new Node();
    newNode->data = val;
    newNode->next = cur->next;
    cur->next = newNode;
}

void display()
{
    Node *cur = head;
    while (cur->next != nullptr)
    {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << cur->data;
    cout << "\n";
}

bool search(int key)
{
    Node *cur = head;

    bool found = false;
    while (cur->next != nullptr && !found)
    {
        cur = cur->next;
        if (cur->data == key)
        {
            found = true;
        }
    }

    return found;
}

void update(int oldVal, int newVal)
{
    Node *cur = head;

    bool found = false;
    while (cur->next != nullptr && !found)
    {
        cur = cur->next;
        if (cur->data == oldVal)
        {
            found = true;
        }
    }

    if (found)
        cur->data = newVal;
    else
        cout << "Not found" << "\n";
}

void deleteVal(int val)
{
    Node *cur = head;

    bool found = false;
    while (cur->next != nullptr && !found)
    {
        cur = cur->next;
        if (cur->next->data == val)
        {
            found = true;
        }
    }

    if (found)
    {
        cur->next = cur->next->next;
        free(cur);
    }
    else
        cout << "Not found" << "\n";
}

int main()
{
    insertAtHead(10);
    insertAtTail(20);
    insertAtTail(30);

    display();
}