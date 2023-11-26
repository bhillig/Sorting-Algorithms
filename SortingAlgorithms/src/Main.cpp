#include <iostream>
#include <memory>
#include <fstream>

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>


int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Sorting Algorithms");

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;

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
        ImGui::End();

        window.clear(sf::Color::Black);
        
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
	return 0;
}