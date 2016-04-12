#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <cstdlib>

class Grid {
	std::vector < std::vector <int> > grid{}, grid_next{};
	int grid_size{};

	const int cell_dead = 0;
	const int cell_alive = 1;
	const int cell_invalid = -1;

	//const char cell_dead = '.';
	//const char cell_alive = '#';
	//const char cell_invalid = 'x';


	void init_grid(std::vector < std::vector <int> >& grid, int value);
	void set_grid(std::vector < std::vector <int> >& grid, int value);
	void set_cell_state(std::vector < std::vector <int> >& grid, int i, int j, int value);
	int get_cell_state(int i, int j);
	int count_neighbors(int i, int j);

public:
	//Grid()=default;
	Grid(const int n) : grid_size(n) {
		init_grid(grid, cell_dead);
		init_grid(grid_next, cell_dead);
	};

	void seed_grid(std::vector< std::vector <int> > alive_cells);
	void update_grid();
	void process_grid();
	void erase_grid();
	void draw_grid();
	std::vector < std::vector <int> > get_grid();
};

void Grid::init_grid(std::vector < std::vector <int> >& grid_, int value){ // underscore after "grid" to avoid any name clashes, shouldn't happen, but I'll remove it once I've confirmed it.
	std::vector <int> row{};
	for(int i=0; i < grid_size; i++){
		row = {};
		for(int j=0; j < grid_size; j++){
			row.push_back(value);
		}
		grid_.push_back(row);
	}
}

void Grid::set_grid(std::vector < std::vector <int> >& grid_, int value){ // underscore after "grid" to avoid any name clashes, shouldn't happen, but I'll remove it once I've confirmed it.
	for(int i=0; i < grid_size; i++){
		for(int j=0; j < grid_size; j++){
			set_cell_state(grid_, i, j, value);
		}
	}
}

void Grid::set_cell_state(std::vector < std::vector <int> >& grid_, int i, int j, int value){
	grid_[i][j] = value;
}

int Grid::get_cell_state(int i, int j){
	if (i < 0 || j < 0 || i >= grid_size || j >= grid_size){
		return cell_invalid; //
	}
	return grid[i][j];
}

std::vector < std::vector <int> > Grid::get_grid(){
	return grid;
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
		set_cell_state(grid, c[0], c[1], cell_alive);
	}
}

void Grid::update_grid(){
	//if (grid == grid_next) { //TODO: Correct comparison
	//	//TODO: Show "No more activity in visible window" or something.
	//	return;
	//}
	set_grid(grid_next, cell_dead); //TODO: Instead of setting the next grid as dead, copy the current grid and modify based on previous states.
	process_grid();
	grid = grid_next; //TODO: check 2 things: assignment and scope of these
}

void Grid::process_grid(){
	for(int i=0; i < grid_size; i++){
		for(int j=0; j < grid_size; j++){
			int count = count_neighbors(i, j);
			if (count != 2 && count != 3) {
				set_cell_state(grid_next, i, j, cell_dead);
			} else if (count == 2) {
				if (get_cell_state(i, j) == cell_alive){
					set_cell_state(grid_next, i, j, cell_alive);
				}
			} else if (count == 3) {
				set_cell_state(grid_next, i, j, cell_alive);
			}
		}
	}
}

void Grid::erase_grid(){
	std::system("clear");
}

void Grid::draw_grid(){
	for(int i=0; i < grid_size; i++){
		for(int j=0; j < grid_size; j++){
			//std::cout << static_cast<char>(get_cell_state(i, j)) << " ";
			std::cout << get_cell_state(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

#endif
