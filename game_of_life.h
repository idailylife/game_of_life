#pragma once

#include <cstdint>
#include <iostream>
#include <cassert>

namespace GameOfLife
{

template <size_t M, size_t N>   // M x N Grid of Cell
class CellGrid
{
public:
    using grid_type_t = uint8_t[M+2][N+2];

private:
    uint8_t cell_state_grid_[2][M+2][N+2] = {{{0}}};    // 1 means alive
    // there are two grids, the primary grid and the second
    // taking account of 'edge' cells for the ease of update -- just assume they are dead
    // can be bitmap if we want to save the space?
    size_t curr_grid_index_ = 0;

private:
    grid_type_t& current_grid()
    {
        return cell_state_grid_[curr_grid_index_];
    }

    grid_type_t& next_grid()
    {
        return cell_state_grid_[1 - curr_grid_index_];
    }

public:
    constexpr static size_t M_()
    {
        return M;
    }

    constexpr static size_t N_()
    {
        return N;
    }

    const grid_type_t& current_grid() const
    {
        return cell_state_grid_[curr_grid_index_];
    }

    void seed(int x, int y)
    {
        if (x <= M && y <= N)
            current_grid()[x][y] = 1;
    }

    void flip_to_next()
    {
        curr_grid_index_ = 1 - curr_grid_index_;
    }

    inline void update_next_state(size_t x, size_t y)
    {
        uint8_t sum_surrund = current_grid()[x-1][y-1]
                            + current_grid()[x-1][y  ]
                            + current_grid()[x-1][y+1]
                            + current_grid()[x  ][y-1]
                            + current_grid()[x  ][y+1]
                            + current_grid()[x+1][y-1]
                            + current_grid()[x+1][y  ]
                            + current_grid()[x+1][y+1];
        if (current_grid()[x][y] == 1)
        {
            if (sum_surrund < 2)
                next_grid()[x][y] = 0;
            else if (sum_surrund <= 3)
                next_grid()[x][y] = 1;
            else
                next_grid()[x][y] = 0;
        }
        else
        {
            assert(current_grid()[x][y] == 0);
            if (sum_surrund == 3)
                next_grid()[x][y] = 1;
            else
                next_grid()[x][y] = 0;
        }
    }

    void calculate_next_gen(size_t x = 1, size_t y = 1, size_t w = M, size_t h = N)
    {
        assert(x >= 1 && x + w <= M + 1);
        assert(y >= 1 && y + h <= N + 1);

        auto curr_grid = current_grid();
        auto next_grid = this->next_grid();

        for (size_t i = x; i < x + w; ++i)
        {
            for (size_t j = y; j < y + h; ++j)
            {
                update_next_state(i, j);
            }
        }

        flip_to_next();
    }
};

// util functions
template <typename CellGrid_t>
void print_grid(const CellGrid_t& grid)
{
    for (size_t i = 1; i <= grid.M_(); ++i)
    {
        for (size_t j = 0; j < grid.N_(); ++j)
        {
            if (grid.current_grid()[i][j] == 1)
                std::cout << "*";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "===================" << std::endl;
}

} //namespace