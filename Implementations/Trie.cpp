#include <bits/stdc++.h>

using namespace std;

class Trie
{
private:
    Trie *children[26];
    bool isLeaf;
    int count;

public:
    Trie() : isLeaf(false), count(0)
    {
        memset(this->children, 0, sizeof(this->children));
    }

    void insert(const string &key)
    {

        Trie *curr = this;

        for (char c : key)
        {
            if (curr->children[c - 'a'] == nullptr)
            {
                curr->children[c - 'a'] = new Trie();
            }
            curr->count++;
            curr = curr->children[c - 'a'];
        }

        curr->isLeaf = true;
    }

    bool search(const string &key)
    {
        Trie *curr = this;

        for (char c : key)
        {
            if (curr->children[c - 'a'] == nullptr)
                return false;
            curr = curr->children[c - 'a'];
        }

        return curr->isLeaf;
    }

    bool isEmpty(Trie *curr = nullptr)
    {
        if (curr == nullptr)
            curr = this;
        for (int i = 0; i < 26; i++)
        {
            if (curr->children[i])
                return false;
        }
        return true;
    }

    int prefixCount(const string &key)
    {
        if (search(key))
        {
            int cnt = 0; // pref count
            // if (this = nullptr)
            //     return 0;

            Trie *curr = this;

            for (char c : key)
            {
                // if (curr->children[c - 'a'] == nullptr)
                //     return false;
                curr = curr->children[c - 'a'];
                if (curr->isLeaf)
                    cnt++;
            }

            return cnt;
        }
        return 0;
    }

    Trie *remove(Trie *curr, const string &key, int depth = 0)
    {
        if (!curr)
            return nullptr;
        if (depth == key.size()) // last char being processed
        {
            if (curr->isLeaf)
                curr->isLeaf = false;
            if (isEmpty(curr) && curr != this)
            {
                delete (curr);
                curr = nullptr;
            }
            return curr;
        }

        // not the last char
        int idx = key[depth] - 'a';
        curr->children[idx] = remove(curr->children[idx], key, depth + 1);

        curr->count--;

        // if theres no other branch on this node after the deletion
        if (isEmpty(curr) && !curr->isLeaf && curr != this)
        {
            delete (curr);
            curr = nullptr;
        }
        return curr;
    }

    Trie *remove(const string &key)
    {
        if (search(key))
        {
            return remove(this, key, 0);
        }
        return this;
    }

    void deleteIt(const string &key)
    {
        if (search(key))
        {
            Trie *curr = this;

            for (char c : key)
            {
                if (!curr->children[c - 'a'])
                    return;
                curr->count--;
                curr = curr->children[c - 'a'];
            }

            curr->isLeaf = false;
        }
    }
};

int main()
{
    Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");

    cout << trie.search("apple") << endl;
    cout << trie.search("app") << endl;
    cout << trie.prefixCount("app") << endl;

    trie.remove("app");

    cout << trie.search("app") << endl;
    cout << trie.search("apple") << endl;
    cout << trie.prefixCount("app") << endl;

    return 0;
}