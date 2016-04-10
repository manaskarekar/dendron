#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "../include/grid.h"
#include "../include/gui.h"

int main(){
	Grid g{67};
	GridGUI g_gui{ g.get_grid() };

	sf::Color gray = sf::Color(128,128,128);
	sf::RenderWindow window(sf::VideoMode(1072, 1072), "Dendron"); //TODO: Change video mode to be "as big as needed" and also support fullscreen
	window.clear(gray);

	std::vector< std::vector <int> > seed_cells {
		{1,1}, {2,2}, {3,3}, {4,4}
	};

	std::vector< std::vector <int> > seed_block {
		{1,1}, {1,2}, {2,1}, {2,2}
	};

	std::vector< std::vector <int> > seed_pentonimo {
		{20,19}, {21,19}, {21,18}, {20,20}, {22,19}
	};

	g.seed_grid(seed_pentonimo);

	g_gui.update_grid(g.get_grid());
	g_gui.draw(window);

	window.display();

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//window.clear(gray);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		g.update_grid(); //TODO: Pass around functions, like the python version
		g_gui.update_grid(g.get_grid());
		g_gui.draw(window);
		window.display();
	}
	return 0;
}
