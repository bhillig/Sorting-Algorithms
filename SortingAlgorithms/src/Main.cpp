#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <stdlib.h>  
#include <time.h>       

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>

enum State {Idle, BubbleSort, SelectionSort};

// Returns a random integer from [min, max] inclusive
int GetRandomInt(int min, int max)
{
    int diff = max - min + 1;
    return (rand() % diff) + min;
}

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

int main(int argc, char* argv[])
{
    /* Initialize state */
    State currentState = State::Idle;

    /* Initialize random seed: */
    srand(time(NULL));

    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    int sortingSpeed = 20;

    bool bDoingBubbleSort = false;
    bool bDoingSelecitonSort = false;

    int ARRAY_SIZE = 200;

    std::vector<int> values(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        values[i] = GetRandomInt(1, WINDOW_HEIGHT);
    }
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorting Algorithms");

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    
    float ELEMENT_WIDTH = (float)WINDOW_WIDTH / ARRAY_SIZE;

    std::vector<std::shared_ptr<sf::RectangleShape>> shapes;

    int index = 0;
    for (int val : values)
    {
        std::shared_ptr<sf::RectangleShape> shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(ELEMENT_WIDTH, val));
        int r = GetRandomInt(0, 255);
        int g = GetRandomInt(0, 255);
        int b = GetRandomInt(0, 255);
        shape->setFillColor(sf::Color(r, g, b));
        shape->setPosition(sf::Vector2f(ELEMENT_WIDTH * index, WINDOW_HEIGHT - val));
        shapes.emplace_back(shape);
        index++;
    }

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Sorting Algorithms");
        std::string elementsText = "Elements: " + std::to_string(values.size());
        ImGui::Text(elementsText.c_str());
        ImGui::SliderInt("Array Size", &ARRAY_SIZE, 1, 2000);
        if (ImGui::Button("Regenerate Data"))
        {
            values.resize(ARRAY_SIZE);
            shapes.resize(ARRAY_SIZE);
            ELEMENT_WIDTH = (float)WINDOW_WIDTH / ARRAY_SIZE;
            for (int i = 0; i < values.size(); ++i)
            {
                values[i] = GetRandomInt(1, WINDOW_HEIGHT);
                if (!shapes[i])
                {
                    shapes[i] = std::make_shared<sf::RectangleShape>(sf::Vector2f(ELEMENT_WIDTH, values[i]));
                }

                int r = GetRandomInt(0, 255);
                int g = GetRandomInt(0, 255);
                int b = GetRandomInt(0, 255);
                shapes[i]->setFillColor(sf::Color(r, g, b));

                shapes[i]->setSize(sf::Vector2f(ELEMENT_WIDTH, values[i]));
                shapes[i]->setPosition(sf::Vector2f(ELEMENT_WIDTH * i, WINDOW_HEIGHT - values[i]));
            }
        }

        ImGui::NewLine();
        ImGui::NewLine();

        ImGui::Text("Apply Color");
        if (ImGui::Button("White"))
        {
        
            for (auto& shape : shapes)
            {
                shape->setFillColor(sf::Color::White);
            }
        }
        if (ImGui::Button("Green"))
        {

            for (auto& shape : shapes)
            {
                shape->setFillColor(sf::Color::Green);
            }
        }
        if (ImGui::Button("Random Color"))
        {
            for (auto& shape : shapes)
            {
                int r = GetRandomInt(0, 255);
                int g = GetRandomInt(0, 255);
                int b = GetRandomInt(0, 255);
                shape->setFillColor(sf::Color(r, g, b));
            }
        }

        ImGui::NewLine();
        ImGui::NewLine();

        ImGui::Text("Sorting");
        ImGui::SliderInt("Speed", &sortingSpeed, 1, 2000);

        ImGui::NewLine();
        ImGui::NewLine();
        if (currentState == State::Idle)
        {
            ImGui::Text("Sorting Algorithms");
            
            if (ImGui::Button("Bubble Sort"))
            {
                currentState = State::BubbleSort;
            }
            if (ImGui::Button("Selection Sort"))
            {
                currentState = State::SelectionSort;
            }
        }
        
        ImGui::End();

        if (currentState == State::BubbleSort)
        {
            PerformBubbleSort(values, sortingSpeed, currentState);
        }
        else if (currentState == State::SelectionSort)
        {
            PerformSelectionSort(values, sortingSpeed, currentState);
        }

        if (currentState != State::Idle)
        {
            /* Update positions and sizes */
            for (int i = 0; i < values.size(); ++i)
            {
                shapes[i]->setSize(sf::Vector2f(ELEMENT_WIDTH, values[i]));
                shapes[i]->setPosition(sf::Vector2f(ELEMENT_WIDTH * i, WINDOW_HEIGHT - values[i]));
            }
        }

        window.clear(sf::Color::Black);
        
        for (auto& shape : shapes)
        {
            window.draw(*shape);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
	return 0;
}