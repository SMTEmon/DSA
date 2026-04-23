#include <bits/stdc++.h>

// Can't pass function as args since we are not directly comparing anything, skill issue

void countSort(std::vector<int> &vec)
{

    // min max
    int min = INT32_MAX, max = INT32_MIN;
    size_t sizee = vec.size();
    for (size_t i = 0; i < sizee; i++)
    {
        if (min > vec[i])
            min = vec[i];
        if (max < vec[i])
            max = vec[i];
    }

    int sizeOfCount = max - min + 1;

    std::vector<int> count(sizeOfCount);

    int offset = 0;

    // if (min < 0) // we actually don't need to check this, don't touch if it works (mathematically)
    offset = -min; // incase we have negative

    // count up

    for (size_t i = 0; i < sizee; i++)
    {
        count[(vec[i] + offset)]++;
    }

    for (int i = 1; i < sizeOfCount; i++)
    {
        count[i] += count[i - 1]; // change to prefix sum
    }

    std::vector<int> result_vec(sizee);

    for (int i = sizee - 1; i >= 0; i--) // Don't use size_t here, size_t i = 0; i--; don't ask me wtf will happen next
    {
        result_vec[--count[vec[i] + offset]] = vec[i];
    }

    vec = result_vec;
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
    countSort(v);
    printVector(v);
}