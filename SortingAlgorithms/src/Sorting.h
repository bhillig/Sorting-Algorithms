#pragma once
#include <vector>

enum State { Idle, BubbleSort, SelectionSort, InsertionSort };

void PerformBubbleSort(std::vector<int>& arr, int sortingSpeed, State& currentState);

void PerformSelectionSort(std::vector<int>& arr, int sortingSpeed, State& currentState);

void PerformInsertionSort(std::vector<int>& arr, int sortingSpeed, State& currentState);

int GetRandomInt(int min, int max);