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

const bool USER_THREADS = true;
const size_t THREAD_RUN_DIM = 15;
const size_t MIN_DIM = 2;

// Forward declaration for friend class
class ThreadedHoleySpiderRun;

// HoleySpiderRun
// Worker class to recusively calculate number of 'holey spider runs'
// invarients: dim, hole, start are constant
class HoleySpiderRun {
public:

    // Make life easier
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
                _board(dim.first * dim.second, 1) {

        _get2D(_board, _hole) = 0;
        _get2D(_board, _start) = 0;

        _adjacentSquares = vector<Vec2I> {
                {-1,  1}, {0,  1}, {1,  1},
                {-1,  0}  /*pos*/, {1,  0},
                {-1, -1}, {0, -1}, {1, -1}};
    }

    // *************** OPERATORS ********************

    // op()
    // call the object as a functition
    // pre: none
    int operator()() {
        return _run(_board, _start, _initLeft);
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
    // *********************** MEMBER VARIABLES **************************

    Vec2I _dim;        // dimension of the board
    Vec2I _hole;       // the coordinate of the hole
    Vec2I _start;      // the starting position of the 'spider'
    Vec2I _finish;     // the finishing location

    size_t _initLeft;  // initial amount of squares left

    BoardType _board;              // inital board state
    vector<Vec2I> _adjacentSquares;    // Relative coords of all neighboring squares
};


// ThreadedHolySpiderRun
// Wrapper for hsr class to add threading
// invarients: same as HSR
class ThreadedHoleySpiderRun {
public:
    // ************************ CONSTRUTOR ****************************

    // ctor
    // make a holey spider run to spawn threaded runs off of
    // pre: same as HSR ctor
    ThreadedHoleySpiderRun(
                const Vec2I & dim,
                const Vec2I & hole,
                const Vec2I & start,
                const Vec2I & finish
            ) : _run(HoleySpiderRun(dim, hole, start, finish)),
                _threadsAvailable(thread::hardware_concurrency()) {
        }
    // **************************** OPERATORS ************************

    // op()
    // start HSR with or without threads
    // pre: none
    int operator()() {
        if (_shouldUseThreads()) {
            _thread_run(_run, _run._board, _run._start, _run._initLeft);

            return (int)accumulate(_returnVals.begin(), _returnVals.end(), 0);
        }
        else {
            return _run();
        }
    }

private:

    // _shouldUseThreads
    // pre: none
    bool _shouldUseThreads() {
        return _run._initLeft > THREAD_RUN_DIM &&
               _run._dim.first > 3 && _run._dim.second > 3 &&
               _threadsAvailable > 1;
    }

    // _thread_run
    // find all valid first moves then spawn threads off for each move
    // pre: none
    // post: will only spawn at most 8 threads (this is inefficent, but it just makes life simpler)
    void _thread_run(HoleySpiderRun run, BoardType board, Vec2I pos, size_t squaresLeft) {
        // Base case (probably wont happen, but just to be safe)
        if (squaresLeft == 0 && pos == run._finish) {
            _returnVals.push_back(1);
            return;
        }

        vector<Vec2I> toRecurse;
        run._validMoves(board, toRecurse, pos);

        // Recuse on all possible moves
        for(auto & pos : toRecurse) {
            lock_guard<mutex> lock(_threadLock);

            _threads.push_back(
                move(thread(&ThreadedHoleySpiderRun::_thread_run_main,
                     this,
                     _run,
                     pos))
            );
        }
        _joinThreads();

    }

    // _joinThreads
    // join all threads in _thread array
    // pre: none
    // post: all threads in _thread will be joined
    void _joinThreads () {
        for(auto & t : _threads) {
                t.join();
        }
    }

    // _thread_run_main
    // recusive worker function for threads
    // pre: none
    // post: all possible answer from that branch will be found
    void _thread_run_main(HoleySpiderRun run, Vec2I pos) {

        // Setup the run at first step
        run._get2D(run._board, pos) = 0;
        run._initLeft -= 1;
        run._start = pos;

        // compute recursively
        auto to_add = run();

        // Add output to return vals
        lock_guard<mutex> lock(_threadLock);
        _returnVals.push_back(to_add);
    }

    // ****************** MEMBER VARIABLES *************************

    HoleySpiderRun _run;          // Template HSR obj to make other off of

    size_t _threadsAvailable;     // Available threads on system
    vector<thread> _threads;      // All running threads
    mutex _threadLock;            // To guard the returnVals array
    vector<int> _returnVals;      // Where the output of all the threads go
};



// (see header for docs)
int countHSR(int dim_x, int dim_y,
             int hole_x, int hole_y,
             int start_x, int start_y,
             int finish_x, int finish_y) {

    if (USER_THREADS) {
        ThreadedHoleySpiderRun run{
            Vec2I{dim_x, dim_y},
            Vec2I{hole_x, hole_y},
            Vec2I{start_x, start_y},
            Vec2I{finish_x, finish_y}
        };
        return run();
    }

    else {
        HoleySpiderRun run{
            Vec2I{dim_x, dim_y},
            Vec2I{hole_x, hole_y},
            Vec2I{start_x, start_y},
            Vec2I{finish_x, finish_y}
        };
        return run();
    }
}


