#include <bits/stdc++.h>

void selectionSort(std::vector<int> &vec, std::function<bool(int, int)> comparator)
{
    size_t sizee = vec.size();
    for (size_t i = 0; i < sizee; i++)
    {
        size_t idx = i;
        for (size_t j = i + 1; j < sizee; j++)
        {
            if (comparator(vec[idx], vec[j]))
                idx = j;
        }

        if (idx != i)
            std::swap(vec[i], vec[idx]);
    }
}

void printVector(std::vector<int> &vec)
{
    size_t sizeOfVector = vec.size();
    for (size_t i = 0; i < sizeOfVector; i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
}

int main()
{
    std::vector<int> v = {6, 3, -3, 5, 9, 2};
    selectionSort(v, [](int a, int b)
                  { return a > b; });
    printVector(v);

    selectionSort(v, [](int a, int b)
                  { return a < b; });
    printVector(v);

    selectionSort(v, [](int a, int b)
                  { return abs(a) > abs(b); });
    printVector(v);

    selectionSort(v, [](int a, int b)
                  { return abs(a) < abs(b); });
    printVector(v);
}