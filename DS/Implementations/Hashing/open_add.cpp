#include <bits/stdc++.h>

using namespace std;

class HashTable
{
    int tableSize;
    int R;
    const int EMPTY = -1;
    const int DELETED = -2;
    vector<int> table;

    int hash1(int key)
    {
        return key % tableSize;
    }

    int hash2(int key)
    {
        return R - (key % R);
    }

public:
    HashTable(int tableSize, int R)
    {
        this->tableSize = tableSize;
        this->R = R;
        table.resize(tableSize, EMPTY);
    }

    void insert(int key)
    {
        int originalSkot = hash1(key);
        int i = 0; // number of collisions

        while (i < tableSize)
        {
            int jump = i * hash2(key);
            int currentSpot = (originalSkot + jump) % tableSize;

            if (table[currentSpot] == EMPTY || table[currentSpot] == DELETED)
            {
                table[currentSpot] = key;
                return;
            }

            if (table[currentSpot] == key)
            {
                cout << "Key already exists" << endl;
                return;
            }

            i++;
        }
        cout << "Hash table is full" << endl;
        return;
    }

    bool search(int key)
    {
        int originalSkot = hash1(key);
        int i = 0; // number of collisions

        while (i < tableSize)
        {
            int jump = i * hash2(key);
            int currentSpot = (originalSkot + jump) % tableSize;

            if (table[currentSpot] == EMPTY)
            {
                return false;
            }

            if (table[currentSpot] == key)
            {
                return true;
            }

            i++;
        }
        return false;
    }

    void remove(int key)
    {
        int originalSkot = hash1(key);
        int i = 0; // number of collisions

        while (i < tableSize)
        {
            int jump = i * hash2(key);
            int currentSpot = (originalSkot + jump) % tableSize;

            if (table[currentSpot] == EMPTY)
            {
                return;
            }

            if (table[currentSpot] == key)
            {
                table[currentSpot] = DELETED;
                return;
            }

            i++;
        }
        cout << "Key not found" << endl;
        return;
    }
};