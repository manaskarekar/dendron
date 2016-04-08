#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>

class Grid {
	std::vector < std::vector <int> > grid{}, grid_next{};
	int grid_size{};

	const int cell_dead = 0;
	const int cell_alive = 1;
	const int cell_invalid = -1;

	void set_grid(std::vector < std::vector <int> >& grid, int value);
	void set_cell_dead(std::vector < std::vector <int> >& grid, int i, int j);
	void set_cell_alive(std::vector < std::vector <int> >& grid, int i, int j);

	int get_cell_state(int i, int j);
	int count_neighbors(int i, int j);

public:
	//Grid()=default;
	Grid(const int n) : grid_size(n) {
		set_grid(grid, cell_dead);
		set_grid(grid_next, cell_dead);
	};

	void seed_grid(std::vector< std::vector <int> > alive_cells);
	void update_grid();
	void process_grid();
	void erase_grid();
	void draw_grid();
};

void Grid::set_grid(std::vector < std::vector <int> >& grid_, int value){ // underscore after "grid" to avoid any name clashes, shouldn't happen, but I'll remove it once I've confirmed it.
	std::vector <int> row{};
	for (int i=0; i < grid_size; i++){
		for (int j=0; j < grid_size; j++){
			row.push_back(value);
		}
		grid_.push_back(row);
	}
}

void Grid::set_cell_dead(std::vector < std::vector <int> >& grid_, int i, int j){
	grid_[i][j] = cell_dead;
}

void Grid::set_cell_alive(std::vector < std::vector <int> >& grid_, int i, int j){
	grid_[i][j] = cell_alive;
}

int Grid::get_cell_state(int i, int j){
	if (i < 0 || j < 0 || i >= grid_size || j >= grid_size){
		return cell_invalid; //
	}
	return grid[i][j];
}

int Grid::count_neighbors(int i, int j){
	int count = 0;

	//horizontal
	if (get_cell_state(i-1, j) == cell_alive) count++;
	if (get_cell_state(i+1, j) == cell_alive) count++;
	//vertical
	if (get_cell_state(i, j-1) == cell_alive) count++;
	if (get_cell_state(i, j+1) == cell_alive) count++;
	//diagonal
	if (get_cell_state(i-1, j-1) == cell_alive) count++;
	if (get_cell_state(i+1, j-1) == cell_alive) count++;
	if (get_cell_state(i-1, j+1) == cell_alive) count++;
	if (get_cell_state(i+1, j+1) == cell_alive) count++;
	return count;
}


void Grid::seed_grid(std::vector< std::vector <int> > alive_cells){
	for (auto c : alive_cells){
		set_cell_alive(grid, c[0], c[1]);
	}
}

void Grid::update_grid(){}
void Grid::process_grid(){}
void Grid::erase_grid(){}

void Grid::draw_grid(){
	for (int i=0; i < grid_size; i++){
		for (int j=0; j < grid_size; j++){
			std::cout << get_cell_state(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

#endif
