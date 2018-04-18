#include <iostream>

#include "game_of_life.h"

int main(int argc, char* argv[])
{
    std::cout << "Game of Life!" << std::endl;
    GameOfLife::CellGrid<25, 25> cell_grid;
    cell_grid.seed(1, 1);
    cell_grid.seed(1, 2);
    cell_grid.seed(1, 3);
    cell_grid.seed(2, 3);
    cell_grid.seed(3, 3);
    cell_grid.seed(5, 5);
    cell_grid.seed(10, 10);
    GameOfLife::print_grid(cell_grid);

    for (size_t i = 0; i < 10; ++i)
    {
        cell_grid.calculate_next_gen();
        GameOfLife::print_grid(cell_grid);
        std::cin.get();
    }
    

    return 0;
}