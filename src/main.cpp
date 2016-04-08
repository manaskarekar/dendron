#include <iostream>
#include "../include/grid.h"

int main(){
	Grid g{10};
	std::vector< std::vector <int> > seed_cells {
	{1,1}, {2,2}, {3,3}, {4,4}
	};

	g.seed_grid(seed_cells);
	g.draw_grid();
	return 0;
}