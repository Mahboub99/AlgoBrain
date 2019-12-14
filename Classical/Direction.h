#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

static const int kSquares = 64;
static const int Direcitions = 8;
typedef uint64_t U64;

U64 RAYS[Direcitions][kSquares];


inline unsigned Indx(unsigned row, unsigned col) { return row * 8 + col; }
inline unsigned Row(unsigned index) { return index / 8; }
inline unsigned Col(unsigned index) { return index % 8; }



class Direction {
public:
	enum D {
		NORTH,
		SOUTH,
		EAST,
		WEST,
		NORTH_EAST,
		NORTH_WEST,
		SOUTH_EAST,
		SOUTH_WEST
	};

	Direction(D direction)
		: direction_(direction) {}

	// Index of the next square along this direction. Returns -1 if 
	// next index is outside the board.
	int NextIndex(int index) const {
		int row = Row(index);
		int col = Col(index);

		switch (direction_) {
		case NORTH:      ++row;        break;
		case SOUTH:      --row;        break;
		case EAST:       ++col;        break;
		case WEST:       --col;        break;
		case NORTH_EAST: ++row; ++col; break;
		case NORTH_WEST: ++row; --col; break;
		case SOUTH_EAST: --row; ++col; break;
		case SOUTH_WEST: --row; --col; break;
		}
		return (row > 7 || col > 7 || row < 0 || col < 0) ? -1 : Indx(row, col);
	}

	// Number of squares from given square to the edge of the board
	// along this direction.
	int EdgeDistance(int index) const {
		using std::min;
		int row = Row(index);
		int col = Col(index);

		auto inv = [](int x)->int { return 7 - x; };

		int d = -1;
		switch (direction_) {
		case NORTH:      d = inv(row);                break;
		case SOUTH:      d = row;                     break;
		case EAST:       d = inv(col);                break;
		case WEST:       d = col;                     break;
		case NORTH_EAST: d = min(inv(row), inv(col)); break;
		case NORTH_WEST: d = min(inv(row), col);      break;
		case SOUTH_EAST: d = min(row, inv(col));      break;
		case SOUTH_WEST: d = min(row, col);           break;
		}
		//assert(d >= 0 && d <= 7);
		return d;
	}

private:
	D direction_;
};