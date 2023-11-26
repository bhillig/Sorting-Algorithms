#include "App.h"
#include "Sorting.h"
#include <time.h>   
#include <fstream>
#include "imgui.h"
#include "imgui-SFML.h"

App::App(const std::string& path)
    : m_running(true)
    , m_currentState(State::Idle)
    , m_sortingSpeed(5)
    , m_arraySize(1000)
    , m_experimental(false)
{
    Init(path);
}

void App::Init(const std::string& path)
{
    /* Initialize random seed: */
    srand(time(NULL));

    /* Set default values for window dimensions */
    m_windowProps.Width = 1920;
    m_windowProps.Height = 1080;

    std::fstream fin(path);

    std::string category;
    while (fin >> category)
    {
        if (category == "Window")
        {
            fin >> m_windowProps.Width >> m_windowProps.Height;
        }
        else if (category == "Font")
        {
            fin >> m_fontProps.path >> m_fontProps.size;
        }
    }

    m_values.resize(m_arraySize);

    /* Initialize array with random values from (1 - window height) */
    for (int i = 0; i < m_values.size(); ++i)
    {
        m_values[i] = GetRandomInt(1, m_windowProps.Height);
    }

    /* Initialize window */
    m_window.create(sf::VideoMode(m_windowProps.Width, m_windowProps.Height), "Sorting Algorithms");

    /* Intialize ImGui */
    ImGui::SFML::Init(m_window);

    float ELEMENT_WIDTH = (float)m_windowProps.Width / m_values.size();

    for (int i = 0; i < m_values.size(); ++i)
    {
        std::shared_ptr<sf::RectangleShape> shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(ELEMENT_WIDTH, m_values[i]));
        int r = GetRandomInt(0, 255);
        int g = GetRandomInt(0, 255);
        int b = GetRandomInt(0, 255);
        shape->setFillColor(sf::Color(r, g, b));
        shape->setPosition(sf::Vector2f(ELEMENT_WIDTH * i, m_windowProps.Height - m_values[i]));
        m_barValues.emplace_back(shape);
    }

    if (!m_font.loadFromFile(m_fontProps.path))
    {
        exit(-1);
    }

    m_sortingText = sf::Text("", m_font, m_fontProps.size);
    m_sortingText.setPosition(20, 20);
}

void App::Run()
{
    // Run the program as long as the window is open
    while (m_running)
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                m_running = false;
                
            }
        }

        ImGui::SFML::Update(m_window, m_deltaClock.restart());

        GUI();

        m_sortingText.setString("");
        if (m_currentState == State::BubbleSort)
        {
            PerformBubbleSort(m_values, m_sortingSpeed, m_currentState);
            m_sortingText.setString("Bubble Sorting...");
        }
        else if (m_currentState == State::SelectionSort)
        {
            PerformSelectionSort(m_values, m_sortingSpeed, m_currentState);
            m_sortingText.setString("Selection Sorting...");
        }
        else if (m_currentState == State::InsertionSort)
        {
            PerformInsertionSort(m_values, m_sortingSpeed, m_currentState);
            m_sortingText.setString("Insertion Sorting...");
        }

        if (m_currentState != State::Idle)
        {
            float ELEMENT_WIDTH = (float)m_windowProps.Width / m_arraySize;

            /* Update positions and sizes */
            for (int i = 0; i < m_values.size(); ++i)
            {
                m_barValues[i]->setSize(sf::Vector2f(ELEMENT_WIDTH, m_values[i]));
                m_barValues[i]->setPosition(sf::Vector2f(ELEMENT_WIDTH * i, m_windowProps.Height - m_values[i]));
            }
        }

        Render();
    }

    m_window.close();
    ImGui::SFML::Shutdown();
}

void App::GUI()
{
    ImGui::Begin("Sorting Algorithms");
    std::string elementsText = "Elements: " + std::to_string(m_values.size());
    ImGui::Text(elementsText.c_str());
    ImGui::SliderInt("Array Size", &m_arraySize, 1, 2000);
    if (ImGui::Button("Regenerate Data"))
    {
        m_values.resize(m_arraySize);
        m_barValues.resize(m_arraySize);
        float ELEMENT_WIDTH = (float)m_windowProps.Width / m_values.size();
        for (int i = 0; i < m_values.size(); ++i)
        {
            m_values[i] = GetRandomInt(1, m_windowProps.Height);
            if (!m_barValues[i])
            {
                m_barValues[i] = std::make_shared<sf::RectangleShape>(sf::Vector2f(ELEMENT_WIDTH, m_values[i]));
            }

            int r = GetRandomInt(0, 255);
            int g = GetRandomInt(0, 255);
            int b = GetRandomInt(0, 255);
            m_barValues[i]->setFillColor(sf::Color(r, g, b));

            m_barValues[i]->setSize(sf::Vector2f(ELEMENT_WIDTH, m_values[i]));
            m_barValues[i]->setPosition(sf::Vector2f(ELEMENT_WIDTH * i, m_windowProps.Height - m_values[i]));
        }
    }

    ImGui::NewLine();
    ImGui::NewLine();

    ImGui::Text("Sorting");
    ImGui::SliderInt("Speed", &m_sortingSpeed, 1, 1000);

    ImGui::NewLine();
    ImGui::NewLine();

    ImGui::Text("Sorting Algorithms");

    if (ImGui::Button("Bubble Sort"))
    {
        m_currentState = State::BubbleSort;
    }
    if (ImGui::Button("Selection Sort"))
    {
        m_currentState = State::SelectionSort;
    }
    if (ImGui::Button("Insertion Sort"))
    {
        m_currentState = State::InsertionSort;
    }

    ImGui::NewLine();
    ImGui::NewLine();

    ImGui::Text("Apply Color");

    if (ImGui::Button("White"))
    {
        for (auto& rect : m_barValues)
        {
            rect->setFillColor(sf::Color::White);
        }
    }

    if (ImGui::Button("Green"))
    {
        for (auto& rect : m_barValues)
        {
            rect->setFillColor(sf::Color::Green);
        }
    }

    if (ImGui::Button("Random Color"))
    {
        for (auto& rect : m_barValues)
        {
            int r = GetRandomInt(0, 255);
            int g = GetRandomInt(0, 255);
            int b = GetRandomInt(0, 255);
            rect->setFillColor(sf::Color(r, g, b));
        }
    }

    ImGui::End();
}

void App::Render()
{
    m_window.clear(sf::Color::Black);

    for (auto& rect : m_barValues)
    {
        m_window.draw(*rect);
    }

    m_window.draw(m_sortingText);

    ImGui::SFML::Render(m_window);
    m_window.display();
}