#include <bits/stdc++.h>

// Same issue with counting sort, we are just using counting sort on this, with diff config
// Can't implement function passes in any way I know for now

int getMax(std::vector<int> vec)
{
    int maxNow = INT32_MIN;
    size_t sizeOfVector = vec.size();

    for (size_t i = 0; i < sizeOfVector; i++)
    {
        if (maxNow < vec[i])
            maxNow = vec[i];
    }

    return maxNow;
}

int getMaxDigitCount(int val)
{
    int count = 0;

    while (val > 1)
    {
        count++;
        val /= 10;
    }
    return count;
}

int getIthDigit(int val, int idx)
{
    if (val == 0 && idx == 1)
        return 0;
    while (idx > 1)
    {
        val /= 10;
        idx--;
    }

    if (val >= 1)
        return val % 10;
    else
        return -1;
}

void countSort(std::vector<int> &vec, int idx)
{
    size_t sizee = vec.size();

    int sizeOfCount = 11;
    int offset = 1;

    // we count -1 -> 0 ig
    // if that idx is not present in a number, they should be put first ig

    std::vector<int> count(sizeOfCount);

    // count up

    for (size_t i = 0; i < sizee; i++)
    {
        count[getIthDigit(vec[i], idx) + offset]++;
    }

    for (int i = 1; i < sizeOfCount; i++)
    {
        count[i] += count[i - 1]; // change to prefix sum
    }

    std::vector<int> result_vec(sizee);

    for (int i = sizee - 1; i >= 0; i--) // Don't use size_t here, size_t i = 0; i--; don't ask me wtf will happen next
    {
        result_vec[--count[getIthDigit(vec[i], idx) + offset]] = vec[i];
    }

    vec = result_vec;
}

void radixSort(std::vector<int> &vec)
{
    int maxDigitCount = getMaxDigitCount(getMax(vec));
    size_t sizeOfVector = vec.size();

    for (int i = 1; i <= maxDigitCount; i++)
    {
        countSort(vec, i);
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
    std::vector<int> v = {12, 322, 4, 0, 654, 213};

    radixSort(v);
    printVector(v);

    // Tester
    // std::cout << getMaxDigitCount(getMax(v)) << "\n";
}