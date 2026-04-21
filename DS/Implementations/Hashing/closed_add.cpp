#include <bits/stdc++.h>

using namespace std;

class stack_Hash
{
private:
    int tableSize;
    vector<list<int>> table;

    int hashFunction(int key)
    {
        return key % tableSize;
    }

public:
    stack_Hash(int tableSize)
    {
        this->tableSize = tableSize;
        table.resize(tableSize);
    }

    void insert(int key)
    {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    bool search(int key)
    {
        int index = hashFunction(key);
        for (int item : table[index])
        {
            if (item == key)
            {
                return true;
            }
            return false;
        }
    }

    void remove(int key)
    {
        int index = hashFunction(key);
        table[index].remove(key);
    }
};