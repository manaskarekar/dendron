#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>

class Grid {
	std::vector < std::vector <int> > grid{}, grid_next{};
	size_t grid_size{};

	const int dead = 0;
	const int alive = 1;

	void set_grid(std::vector < std::vector <int> > grid, int value);
	void set_cell_dead(std::vector < std::vector <int> > grid, int i, int j);
	void set_cell_alive(std::vector < std::vector <int> > grid, int i, int j);

public:
	Grid()=default;
	Grid(const int n) : grid_size(n) {
		set_grid(grid, dead);
		set_grid(grid_next, dead);
	};

};

void Grid::set_grid(std::vector < std::vector <int> > grid_, int value){ // underscore after "grid" to avoid any name clashes, shouldn't happen, but I'll remove it once I've confirmed it.
	for (auto i=0; i < grid_size; i++){
		for (auto j=0; j < grid_size; j++){
			grid_[i][j] = value;
		}
	}
}

void Grid::set_cell_dead(std::vector < std::vector <int> > grid_, int i, int j){
	grid_[i][j] = dead;
}

void Grid::set_cell_alive(std::vector < std::vector <int> > grid_, int i, int j){
	grid_[i][j] = alive;
}

