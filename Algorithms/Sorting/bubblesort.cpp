#include <bits/stdc++.h>

// expect vector input

void bubblesort(std::vector<int> &vec, std::function<bool(int, int)> comparator)
{
    // we can also use :auto comparator:

    int sizeOfOperation = vec.size() - 1; // on how many we will operate
    // -1 cus we plan to compair 1 more preceding value ig

    bool swapped; // plan to stop if nothing is swapped for 1 run

    while (sizeOfOperation > 0)
    {
        swapped = false;
        for (int i = 0; i < sizeOfOperation; i++)
        {
            if (comparator(vec[i], vec[i + 1]))
            {
                std::swap(vec[i], vec[i + 1]);
                swapped = true;
            }
        }
        sizeOfOperation--;
    }
}

void printVector(std::vector<int> &vec)
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
    bubblesort(v, [](int a, int b)
               { return a > b; });
    printVector(v);

    bubblesort(v, [](int a, int b)
               { return a < b; });
    printVector(v);

    bubblesort(v, [](int a, int b)
               { return abs(a) > abs(b); });
    printVector(v);

    bubblesort(v, [](int a, int b)
               { return abs(a) < abs(b); });
    printVector(v);
}