#include <bits/stdc++.h>

void insertionSort(std::vector<int> &vec, std::function<bool(int, int)> comparator)
{
    size_t sizeOfVector = vec.size();
    for (int i = 1; i < sizeOfVector; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (comparator(vec[j - 1], vec[j]))
            {
                std::swap(vec[j - 1], vec[j]);
            }
        }
    }
}

void printVector(std::vector<int> vec)
{
    int sizeOfVector = vec.size();
    for (int i = 0; i < sizeOfVector; i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
}

int main()
{
    std::vector<int> v = {6, 3, -3, 5, 9, 2};
    insertionSort(v, [](int a, int b)
                  { return a > b; });
    printVector(v);

    insertionSort(v, [](int a, int b)
                  { return a < b; });
    printVector(v);

    insertionSort(v, [](int a, int b)
                  { return abs(a) > abs(b); });
    printVector(v);

    insertionSort(v, [](int a, int b)
                  { return abs(a) > abs(b); });
    printVector(v);
}