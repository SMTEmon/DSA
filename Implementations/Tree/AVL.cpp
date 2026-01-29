#include <bits/stdc++.h>

class Node
{
public:
    int val;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    int height;
    Node(int val) : val(val), height(0) {}
    Node(int val, Node *parent) : val(val), parent(parent), height(0) {}
    Node(int val, Node *left, Node *right, Node *parent) : val(val), left(left), right(right), parent(parent), height(0) {}
};

class AVL
{
private:
    Node *root = nullptr;

    int getHeight(Node *node)
    {
        if (!node)
            return -1;
        return node->height;
    }

    int getBalance(Node *node)
    {
        if (!node)
            return -1;
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node *current)
    {
        if (!current)
            current->height = 1 + std::max(getHeight(current->left), getHeight(current->right));
    }

    Node *BSTinsertNode(Node *parentNode, Node *currentNode, int val)
    {
        if (currentNode == nullptr)
            return new Node(val, parentNode);

        else if (val < currentNode->val)
            currentNode->left = BSTinsertNode(currentNode, currentNode->left, val);

        else if (val > currentNode->val)
            currentNode->right = BSTinsertNode(currentNode, currentNode->right, val);

        else
            return currentNode;

        updateHeight(currentNode);

        int balance = getBalance(currentNode);

        if (balance > 1 && val < currentNode->left->val)
        {
            rightRotate(currentNode);
            return currentNode->parent;
        }
        if (balance < -1 && val > currentNode->right->val)
        {
            leftRotate(currentNode);
            return currentNode->parent;
        }
        if (balance > 1 && val > currentNode->left->val)
        {
            leftRotate(currentNode->left);
            rightRotate(currentNode);
            return currentNode->parent;
        }
        if (balance < -1 && val < currentNode->right->val)
        {
            rightRotate(currentNode->right);
            leftRotate(currentNode);
            return currentNode->parent;
        }

        return currentNode;
    }

public:
    void leftRotate(Node *node)
    {
        if (node->right == nullptr)
            return;

        Node *rightNow = node->right;
        if (node == root)
            root = rightNow;
        else
        {
            if (node->parent->left == node)
                node->parent->left = rightNow;
            else
                node->parent->right = rightNow;
        }
        rightNow->parent = node->parent;
        node->parent = rightNow;
        node->right = rightNow->left;
        if (rightNow->left)
            rightNow->left->parent = node;
        rightNow->left = node;

        updateHeight(node);
        updateHeight(rightNow);
    }

    void rightRotate(Node *node)
    {
        if (node->left == nullptr)
            return;

        Node *leftNow = node->left;
        if (node == root)
            root = leftNow;
        else
        {
            if (node->parent->right == node)
                node->parent->right = leftNow;
            else
                node->parent->left = leftNow;
        }
        leftNow->parent = node->parent;
        node->parent = leftNow;
        node->left = leftNow->right;
        if (leftNow->right)
            leftNow->right->parent = node;
        leftNow->right = node;

        updateHeight(node);
        updateHeight(leftNow);
    }

    void insert(int val)
    {
        root = BSTinsertNode(nullptr, root, val);
    }

    void print()
    {
        printHelper(root);
        std::cout << std::endl;
    }
    void printHelper(Node *node)
    {
        if (!node)
            return;
        printHelper(node->left);
        std::cout << node->val << " ";
        printHelper(node->right);
    }
};

int main()
{
    AVL tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30); // Triggers Left Rotation
    tree.insert(40);
    tree.insert(50); // Triggers Left Rotation
    tree.insert(25); // Triggers Right-Left Rotation

    tree.print(); // Should be sorted: 10 20 25 30 40 50
    return 0;
}