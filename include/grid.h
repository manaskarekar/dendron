#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <cstdlib>

class Grid {
	std::vector < std::vector <int> > grid{};
	int grid_size{};

	//TODO: Just use 2 bits to store state such that lsb (current state) and lsb + 1 (next state) and then use bit operations

	static constexpr int cell_invalid = -1;
	static constexpr int cell_dead = 0;
	static constexpr int cell_alive = 1;
	static constexpr int cell_toggle_to_dead = 2;
	static constexpr int cell_toggle_to_alive = 3;

	void init_grid(std::vector < std::vector <int> >& grid, int value);
	void set_grid(std::vector < std::vector <int> >& grid);
	void set_cell_state(std::vector < std::vector <int> >& grid, int i, int j, int value);
	int get_cell_state(int i, int j);
	int count_neighbors(int i, int j);
	bool check_alive(int i, int j);
public:
	//Grid()=default;
	Grid(const int n) : grid_size(n) {
		init_grid(grid, cell_dead);
	};

	void seed_grid(std::vector< std::vector <int> > alive_cells);
	void update_grid();
	void process_grid();
	void erase_grid();
	void draw_grid();
	std::vector < std::vector <int> > get_grid();
};

void Grid::init_grid(std::vector < std::vector <int> >& grid_, int value){
	std::vector <int> row{};
	for(int i=0; i < grid_size; i++){
		row = {};
		for(int j=0; j < grid_size; j++){
			row.push_back(value);
		}
		grid_.push_back(row);
	}
}

void Grid::set_grid(std::vector < std::vector <int> >& grid_){
	for(int i=0; i < grid_size; i++){
		for(int j=0; j < grid_size; j++){
			switch (get_cell_state(i, j)) {
			case cell_toggle_to_alive:
				set_cell_state(grid_, i, j, cell_alive);
				break;
			case cell_toggle_to_dead:
				set_cell_state(grid_, i, j, cell_dead);
				break;
			}
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

bool Grid::check_alive(int i, int j) {
	int cell_value = get_cell_state(i, j);
	if (cell_value == cell_alive or cell_value == cell_toggle_to_dead)
		return true;
	return false;
}

int Grid::count_neighbors(int i, int j){
	int count = 0;

	//horizontal
	if (check_alive(i-1, j)) 	count++;
	if (check_alive(i+1, j)) 	count++;
	//vertical
	if (check_alive(i, j-1)) 	count++;
	if (check_alive(i, j+1)) 	count++;
	//diagonal
	if (check_alive(i-1, j-1)) 	count++;
	if (check_alive(i+1, j-1)) 	count++;
	if (check_alive(i-1, j+1)) 	count++;
	if (check_alive(i+1, j+1)) 	count++;
	return count;
}


void Grid::seed_grid(std::vector< std::vector <int> > alive_cells){
	for (auto c : alive_cells){
		set_cell_state(grid, c[0], c[1], cell_alive);
	}
}

void Grid::update_grid(){
	set_grid(grid);
	process_grid();
}

void Grid::process_grid(){
	for(int i=0; i < grid_size; i++){
		for(int j=0; j < grid_size; j++){
			int count = count_neighbors(i, j);
			if (count != 2 && count != 3) {
				if (get_cell_state(i, j) == cell_alive){
					set_cell_state(grid, i, j, cell_toggle_to_dead); //Herein lies the mistake
				}
			//} else if (count == 2) {
				// do nothing
			} else if (count == 3) {
				if (get_cell_state(i, j) == cell_dead){
					set_cell_state(grid, i, j, cell_toggle_to_alive);
				}
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
