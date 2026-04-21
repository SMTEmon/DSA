#include <bits/stdc++.h>

// expect vector input

void bubblesortMinToMax(std::vector<int> &vec)
{
    int sizeOfOperation = vec.size() - 1; // on how many we will operate
    // -1 cus we plan to compair 1 more preceding value ig
    while (sizeOfOperation > 0)
    {

        for (int i = 0; i < sizeOfOperation; i++)
        {
            if (vec[i] > vec[i + 1])
                std::swap(vec[i], vec[i + 1]);
        }
        sizeOfOperation--;
    }
}

void bubblesortMaxToMin(std::vector<int> &vec)
{
    int sizeOfOperation = vec.size() - 1; // on how many we will operate
    // -1 cus we plan to compair 1 more preceding value ig
    while (sizeOfOperation > 0)
    {

        for (int i = 0; i < sizeOfOperation; i++)
        {
            if (vec[i] < vec[i + 1])
                std::swap(vec[i], vec[i + 1]);
        }
        sizeOfOperation--;
    }
}

void bubblesortMinToMaxAbs(std::vector<int> &vec)
{
    int sizeOfOperation = vec.size() - 1; // on how many we will operate
    // -1 cus we plan to compair 1 more preceding value ig
    while (sizeOfOperation > 0)
    {

        for (int i = 0; i < sizeOfOperation; i++)
        {
            if (abs(vec[i]) > abs(vec[i + 1]))
                std::swap(vec[i], vec[i + 1]);
        }
        sizeOfOperation--;
    }
}

void bubblesortMaxToMinAbs(std::vector<int> &vec)
{
    int sizeOfOperation = vec.size() - 1; // on how many we will operate
    // -1 cus we plan to compair 1 more preceding value ig
    while (sizeOfOperation > 0)
    {

        for (int i = 0; i < sizeOfOperation; i++)
        {
            if (abs(vec[i]) < abs(vec[i + 1]))
                std::swap(vec[i], vec[i + 1]);
        }
        sizeOfOperation--;
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
    bubblesortMinToMax(v);
    printVector(v);

    bubblesortMaxToMin(v);
    printVector(v);

    bubblesortMinToMaxAbs(v);
    printVector(v);

    bubblesortMaxToMinAbs(v);
    printVector(v);
}