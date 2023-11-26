#pragma once
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Sorting.h"

struct WindowProps { int Width; int Height; };
struct FontProps { std::string path; int size; };

class App
{
public:
	App(const std::string& path);

	void Run();

private:

	/* Called from constructor to init config */
	void Init(const std::string& path);

	void GUI();

	void Render();

	bool m_running;

	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;
	WindowProps m_windowProps;
	FontProps m_fontProps;
	State m_currentState;
	int m_sortingSpeed;

	std::vector<int> m_values;
	int m_arraySize;

	/* The visual representation of m_values */
	std::vector<std::shared_ptr<sf::RectangleShape>> m_barValues;

	sf::Font m_font;
	bool m_experimental;

	/* Top left corner text */
	sf::Text m_sortingText;
};