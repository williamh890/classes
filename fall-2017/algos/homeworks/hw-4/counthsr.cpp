// counthsr.cpp
// William Horn
// Oct 11, 2017
// cs311 assignment 4 source file

#include<utility>
using std::pair;
#include<vector>
using std::vector;
#include<cstddef>
using std::size_t;
#include<iostream>
using std::cout;
using std::endl;

using Vec2I = pair<int, int>;


class HoleySpiderRun {
public:
    HoleySpiderRun(
        const Vec2I & dim,
        const Vec2I & hole,
        const Vec2I & start,
        const Vec2I & finish
    ) : _dim(dim),
        _hole(hole),
        _start(start),
        _finish(finish),
        _board(dim.first * dim.second, 1) {

        get2D(_hole) = 0;
        get2D(_start) = 0;
        printBoard();
    }

    void printBoard() {
        for (auto x = 0; x < _dim.first + 2; ++x) {
            for (auto y = 0; y < _dim.second + 2; ++y) {
                cout << get2D(x, y) << " ";
            }
            cout << endl;
        }
    }

    int& get2D(size_t x, size_t y) {
        return _board[x * _dim.second + y];
    }

    int& get2D(const Vec2I & index) {
        auto x = index.first;
        auto y = index.second;
        return get2D(x, y);
    }


    int operator()() {
        return _run();
    }

private:

    int _run() {
        return 0;
    }

    Vec2I _dim;
    Vec2I _hole;
    Vec2I _start;
    Vec2I _finish;

    vector<int> _board;
};


int countHSR(int dim_x, int dim_y,
             int hole_x, int hole_y,
             int start_x, int start_y,
             int finish_x, int finish_y) {

    Vec2I dim{dim_x, dim_y};
    Vec2I hole{hole_x, hole_y};
    Vec2I start{start_x, start_y};
    Vec2I finish{finish_x, finish_y};

    HoleySpiderRun run{dim, hole, start, finish};

    return run();
}
