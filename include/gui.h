#ifndef GRID_GUI_H
#define GRID_GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class GridGUI {
	sf::Color dead_color = sf::Color(32,32,32);
	sf::Color alive_color = sf::Color(255,69,0); //orangered
	sf::Vector2f cell_size = sf::Vector2f(16, 16);
	int grid_size{};

	std::vector < std::vector <sf::RectangleShape> > grid_gui{};
	void init(int n);
	void set_position();
public:
	GridGUI()=default;
	GridGUI(std::vector < std::vector <int> > grid) {
		grid_size = grid.size();
		init(grid_size);
		set_position();
		update_grid(grid); //TODO: tweak this later to allow setting a default state.
	}
	void update_grid(std::vector < std::vector <int> > grid_states);
	void draw(sf::RenderWindow& window);

	~GridGUI(){};
};

void GridGUI::init(int n){
	std::vector <sf::RectangleShape> row{};

	for(auto i=0; i < n; i++){
		row = {};
		for(auto j=0; j < n; j++){
			row.push_back(sf::RectangleShape(cell_size));
		}
		grid_gui.push_back(row);
	}
}

void GridGUI::set_position(){
	float x = 0.0, y = 0.0;
	for(auto i=0; i < grid_size; i++){
		for(auto j=0; j < grid_size; j++){
			grid_gui[i][j].setPosition(x, y);
			x += cell_size.x;
		}
		y += cell_size.y;
		x = 0.0;
	}
}

void GridGUI::update_grid(std::vector < std::vector <int> > grid_states){
	for(auto i=0; i < grid_size; i++){
		for(auto j=0; j < grid_size; j++){
			if (grid_states[i][j] == 0){
				grid_gui[i][j].setFillColor(dead_color);
			} else if (grid_states[i][j] == 1){
				grid_gui[i][j].setFillColor(alive_color);
			} //TODO: add support for > 2 states
		}
	}
}

void GridGUI::draw(sf::RenderWindow& window){
	//TODO: Improve iterating through each
	for(auto i=0; i < grid_size; i++){
		for(auto j=0; j < grid_size; j++){
			window.draw(grid_gui[i][j]);
		}
	}
}

#endif
