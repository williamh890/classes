// counthsr.cpp
// William Horn
// Oct 11, 2017
// cs311 assignment 4 source file
#include<iostream>
#include<utility>
using std::pair;
using std::move;
#include<vector>
using std::vector;
#include<numeric>
using std::accumulate;
#include<cstddef>
using std::size_t;
#include<stdexcept>
using std::out_of_range;
#include<thread>
using std::thread;
#include<mutex>
using std::lock_guard;
using std::mutex;


using Vec2I = pair<int, int>;
using BoardType = vector<int>;
using ChangePairType = pair<Vec2I, int>; // Position and value changed to

const size_t THREAD_RUN_DIM = 15;


class ThreadedHoleySpiderRun;


class HoleySpiderRun {
    public:
        friend class ThreadedHoleySpiderRun;
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
        int _run(BoardType & board, Vec2I pos, size_t squaresLeft) {

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


class ThreadedHoleySpiderRun {
public:

    ThreadedHoleySpiderRun(
                const Vec2I & dim,
                const Vec2I & hole,
                const Vec2I & start,
                const Vec2I & finish
            ) : _run(HoleySpiderRun(dim, hole, start, finish)),
                _threadsAvailable(thread::hardware_concurrency()),
                _isThreadPass(true){
        }

        // op()
        // call the object as a functition
        // pre: none
        int operator()() {
            // only run threading on larger problems
            if (_run._initLeft > THREAD_RUN_DIM && _run._dim.first > 3 && _run._dim.second > 3 && _threadsAvailable > 1) {
                std::cout << "Availble Threads: " << _threadsAvailable << std::endl;

                _thread_run(_run, _run._initBoard, _run._start, _run._initLeft);

                return (int)accumulate(_returnVals.begin(), _returnVals.end(), 0);

            }
            else {
                return _run();
            }




        }


private:
    void _thread_run(HoleySpiderRun run, BoardType board, Vec2I pos, size_t squaresLeft) {
        // Base case (probably wont happen, but just to be safe)
        if (squaresLeft == 0 && pos == run._finish) {
            {
                lock_guard<mutex> lock(_threadLock);
                _returnVals.push_back(1);
            }
        }

        // Recursive Case
        else {
            vector<Vec2I> toRecurse;
            run._validMoves(board, toRecurse, pos);

            // Recuse on all possible moves
            for(auto & pos : toRecurse) {
                // scope for lock_guard
                {
                    lock_guard<mutex> lock(_threadLock);

                    if (_isThreadPass && _threadsAvailable > 1 ) {
                        _threadsAvailable -= 1;

                        _threads.push_back(
                            move(thread(&ThreadedHoleySpiderRun::_thread_run_main, this, _run, pos, squaresLeft - 1 ))
                        );
                    }
                }
            }

            for(auto & t : _threads) {
                t.join();
            }
        }
    }

    void _thread_run_main(HoleySpiderRun run, Vec2I pos, size_t squaresLeft) {
            run._get2D(run._initBoard, pos) = 0;
            run._initLeft -= 1;
            run._start = pos;
            auto to_add = run();

            {
                std::cout << "to_add" << std::endl;
                lock_guard<mutex> lock(_threadLock);
                _returnVals.push_back(to_add);
            }

        }


    HoleySpiderRun _run;
    vector<HoleySpiderRun> _run_objects;

    size_t _threadsAvailable;
    vector<thread> _threads;
    mutex _threadLock;
    vector<int> _returnVals;
    bool _isThreadPass;

};



// (see header for docs)
int countHSR(int dim_x, int dim_y,
             int hole_x, int hole_y,
             int start_x, int start_y,
             int finish_x, int finish_y) {

    ThreadedHoleySpiderRun run{
        Vec2I{dim_x, dim_y},
        Vec2I{hole_x, hole_y},
        Vec2I{start_x, start_y},
        Vec2I{finish_x, finish_y}
    };

    return run();
}


