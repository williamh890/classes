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
#include<stdexcept>
using std::out_of_range;

using Vec2I = pair<int, int>;
using BoardType = vector<int>;


class HoleySpiderRun {
    public:
        // ***************** CONSTRUCTORS ******************

        // ctor
        // sets the inital board and makes _adjacentSquares array for use later
        // pre: dim must be positive ints
        //      hole, start, finish must be coordinates in dimension
        //      total dim area must be > 2
        HoleySpiderRun(
                const Vec2I & dim,
                const Vec2I & hole,
                const Vec2I & start,
                const Vec2I & finish
                ) : _dim(dim),
                    _hole(hole),
                    _start(start),
                    _finish(finish),
                    _initLeft((_dim.first * _dim.second) - 2),
                    _initBoard(dim.first * dim.second, 1) {

            _get2D(_initBoard, _hole) = 0;
            _get2D(_initBoard, _start) = 0;

            _adjacentSquares = vector<Vec2I> {
                    {-1,  1}, {0,  1}, {1,  1},
                    {-1,  0}  /*pos*/, {1,  0},
                    {-1, -1}, {0, -1}, {1, -1}};
        }

        // op()
        // call the object as a functition
        // pre: none
        int operator()() {

            return _run(_initBoard, _start, _initLeft);
        }

    private:
        // ************** PRIVATE FUNCTIONS ********************

        // _get2D
        // access a 1D array like a 2D one
        // pre: index is within board
        // throw: will throw std::out_of_range if index is totally out of array
        int& _get2D(BoardType & board, const Vec2I & index) {

            return board.at( index.first * _dim.second + index.second );
        }

        // _isOffBoard
        // checks whether a coordinate is off the board
        // pre: none
        bool _isOffBoard(const Vec2I & pos) {

            return (pos.first > _dim.first - 1 || pos.first < 0 ||
                    pos.second > _dim.second - 1 || pos.second < 0);
        }

        // _validMoves
        // fills toRecurse with all possible valid moves
        // pre: toRecurse is empty
        // post: toRecurse only contains valid moves
        void _validMoves(BoardType & board,
                          vector<Vec2I> & toRecurse,
                          const Vec2I & pos) {

            for(const auto & p : _adjacentSquares) {
                Vec2I checkPos = Vec2I{p.first + pos.first,
                                       p.second + pos.second};

                if(!_isOffBoard(checkPos)) {
                    auto squareVal = _get2D(board, checkPos);

                    if(squareVal == 1) {
                        toRecurse.push_back(checkPos);
                    }
                }
            }
        }

        // _run
        // recursive workhorse function for computations
        // pre: covered by ctor preconditions
        int _run(BoardType board, Vec2I pos, size_t squaresLeft) {

            // Base case
            if (squaresLeft == 0 && pos == _finish) {
                return 1;
            }

            // Recursive Case
            else {
                auto total = 0;

                vector<Vec2I> toRecurse;
                _validMoves(board, toRecurse, pos);

                // Recuse on all possible moves
                for(auto & pos : toRecurse) {
                    _get2D(board, pos) = 0;
                    total += _run(board, pos, squaresLeft - 1);
                    _get2D(board, pos) = 1;
                }

                return total;
            }
        }

        Vec2I _dim;        // dimension of the board
        Vec2I _hole;       // the coordinate of the hole
        Vec2I _start;      // the starting position of the 'spider'
        Vec2I _finish;     // the finishing location

        size_t _initLeft;  // initial amount of squares left

        BoardType _initBoard;              // inital board state
        vector<Vec2I> _adjacentSquares;    // Relative coords of all neighboring squares
};


// (see header for docs)
int countHSR(int dim_x, int dim_y,
             int hole_x, int hole_y,
             int start_x, int start_y,
             int finish_x, int finish_y) {

    HoleySpiderRun run{
        Vec2I{dim_x, dim_y},
        Vec2I{hole_x, hole_y},
        Vec2I{start_x, start_y},
        Vec2I{finish_x, finish_y}
    };

    return run();
}


