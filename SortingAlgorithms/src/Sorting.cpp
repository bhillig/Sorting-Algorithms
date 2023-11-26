#include "Sorting.h"

void PerformBubbleSort(std::vector<int>& arr, int sortingSpeed, State& currentState)
{
    int i, j;
    int numberOfSwapsDone;

    if (arr.size() <= 1)
    {
        currentState = Idle;
        return;
    }

    for (i = 0; i < arr.size() - 1; ++i)
    {
        numberOfSwapsDone = 0;
        for (j = 0; j < arr.size() - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                numberOfSwapsDone++;
                if (numberOfSwapsDone >= sortingSpeed)
                {
                    break;
                }
            }
        }

        /* Only continue bubble sort if we swapped, else it's sorted */
        if (numberOfSwapsDone == 0)
        {
            currentState = Idle;
        }
        break;
    }
}

void PerformSelectionSort(std::vector<int>& arr, int sortingSpeed, State& currentState)
{
    int i, j, min_idx;

    int maxSwaps = (sortingSpeed / 100) + 1;

    int swapsDone = 0;
    for (i = 0; i < arr.size(); ++i)
    {

        min_idx = i;
        for (j = i + 1; j < arr.size(); j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx != i)
        {
            std::swap(arr[min_idx], arr[i]);
            swapsDone++;
            if (swapsDone >= maxSwaps)
            {
                break;
            }
        }

    }

    if (swapsDone == 0)
    {
        currentState = Idle;
    }
}

void PerformInsertionSort(std::vector<int>& arr, int sortingSpeed, State& currentState)
{
    static int i = 1;
    int j, key;

    int maxSwaps = (sortingSpeed / 100) + 1;

    int swapsDone = 0;
    bool swapped;
    while (i < arr.size())
    {
        key = arr[i];
        j = i - 1;

        swapped = false;

        // Move elements of arr[0..i-1],
        // that are greater than key, 
        // to one position ahead of their
        // current position
        while (j >= 0 && arr[j] > key) 
        {
            swapped = true;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        if (swapped) ++swapsDone;

        arr[j + 1] = key;
        ++i;

        if (swapsDone >= maxSwaps) break;
    }

    if (swapsDone == 0)
    {
        i = 1;
        currentState = State::Idle;
    }
}

// Returns a random integer from [min, max] inclusive
int GetRandomInt(int min, int max)
{
    int diff = max - min + 1;
    return (rand() % diff) + min;
}