#include <iostream>
#include <chrono>
#include <thread>
#include "../include/grid.h"

int main(){
	Grid g{45};
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
	g.draw_grid();

	while(1){
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		g.erase_grid();
		g.update_grid(); //TODO: Pass around functions, like the python version
		g.draw_grid();
	}
	return 0;
}