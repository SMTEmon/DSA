#include <bits/stdc++.h>

void merge(std::vector<int> &vec, size_t lo, size_t mid, size_t hi, std::function<bool(int, int)> comparator)
{
    size_t vec1Size = mid - lo + 1;
    size_t vec2Size = hi - mid;
    std::vector<int> vec1(vec1Size);
    std::vector<int> vec2(vec2Size);

    // Copy all the values on their vectors
    for (size_t i = 0; i < vec1Size; i++)
    {
        vec1[i] = vec[lo + i];
    }
    for (size_t i = 0; i < vec2Size; i++)
    {
        vec2[i] = vec[mid + 1 + i];
    }

    // merge into the real vector now

    // idx for both vec and the real vec
    size_t idx1 = 0, idx2 = 0, idx = lo;
    // merging
    while ((idx1 < vec1Size) && (idx2 < vec2Size))
    {
        if (comparator(vec1[idx1], vec2[idx2]))
        {
            vec[idx] = vec1[idx1];
            idx1++;
        }
        else
        {
            vec[idx] = vec2[idx2];
            idx2++;
        }
        idx++;
    }

    // deal with the rest that was missed

    while (idx1 < vec1Size)
    {
        vec[idx] = vec1[idx1];
        idx1++;
        idx++;
    }

    while (idx2 < vec2Size)
    {
        vec[idx] = vec2[idx2];
        idx2++;
        idx++;
    }
}

void mergeSort(std::vector<int> &vec, size_t lo, size_t hi, std::function<bool(int, int)> comparator)
{

    if (lo >= hi)
        return;
    size_t mid = lo + (hi - lo) / 2;
    mergeSort(vec, lo, mid, comparator);
    mergeSort(vec, mid + 1, hi, comparator);
    merge(vec, lo, mid, hi, comparator);
}

void mergeSort(std::vector<int> &vec, std::function<bool(int, int)> comparator)
{
    mergeSort(vec, 0, vec.size() - 1, comparator);
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
    mergeSort(v, [](int a, int b)
              { return a < b; });
    printVector(v);
    mergeSort(v, [](int a, int b)
              { return a > b; });
    printVector(v);
    mergeSort(v, [](int a, int b)
              { return abs(a) < abs(b); });
    printVector(v);
    mergeSort(v, [](int a, int b)
              { return abs(a) > abs(b); });
    printVector(v);
}