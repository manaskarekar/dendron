#include <iostream>
#include <chrono>
#include <thread>
#include "../include/grid.h"
#include <SFML/Graphics.hpp>

int main(){
	sf::Color gray(128,128,128);
	sf::RectangleShape dead_cell, live_cell;
	sf::Vector2f cell_size(16,16);

	sf::RenderWindow window(sf::VideoMode(640, 480), "Dendron");
	window.clear(gray);

	dead_cell.setSize(cell_size);
	dead_cell.setFillColor(sf::Color(255, 255, 255));
	window.draw(dead_cell);

	live_cell.setSize(cell_size);
	live_cell.setFillColor(sf::Color(0, 0, 0));
	window.draw(live_cell);

	window.display();

	Grid g{25};
	std::vector< std::vector <int> > seed_cells {
		{1,1}, {2,2}, {3,3}, {4,4}
	};

	std::vector< std::vector <int> > seed_block {
		{1,1}, {1,2}, {2,1}, {2,2}
	};


	std::vector< std::vector <int> > seed_pentonimo {
		{20,19}, {21,19}, {21,18}, {20,20}, {22,19}
	};

	g.erase_grid();
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	g.seed_grid(seed_pentonimo);
	//g.draw_grid();

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(gray);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		g.erase_grid();
		g.update_grid(); //TODO: Pass around functions, like the python version
		g.draw_grid();
		window.display();

	}
	return 0;
}
