#include "Direction.h"

// Masks all the bits from the given index, and along the given direction to 1,
// excluding the square given by the index and the edge of the board along
// given direction.
U64 MaskBits(const Direction& direction, const int index) {                  // obtain the attack in this direction 
	U64 bitboard = 0ULL;
	int next_index = index;
	while (direction.NextIndex(next_index) >= 0) {
		next_index = direction.NextIndex(next_index);
		bitboard |= (1ULL << next_index);
	}
	return bitboard;
}
void PrintBitBoard(const U64 bitboard) {
	
	for (int row = 7; row >= 0; --row) {
		for (int col = 0; col <= 7; ++col) {
			if (bitboard & (1ULL << ((row * 8) + col))) {
				std::cout << "1 ";
			}
			else {
				std::cout << ". ";
			}
		}
		std::cout << std::endl;
	}
}

void initialize_rays()
{
	
	for (int i = 0; i < Direcitions; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			Direction D = Direction::NORTH;
			
			     if (i == 0) D = Direction::NORTH;
			else if (i == 1) D = Direction::SOUTH;
			else if (i == 2) D = Direction::EAST;
			else if (i == 3) D = Direction::WEST;
			else if (i == 4) D = Direction::NORTH_EAST;
			else if (i == 5) D = Direction::NORTH_WEST;
			else if (i == 6) D = Direction::SOUTH_EAST;
			else if (i == 7) D = Direction::SOUTH_WEST;

			RAYS[i][j] = MaskBits(D, j);

		}
	}
}
const int index64[64] = {
	0,  1, 48,  2, 57, 49, 28,  3,
   61, 58, 50, 42, 38, 29, 17,  4,
   62, 55, 59, 36, 53, 51, 43, 22,
   45, 39, 33, 30, 24, 18, 12,  5,
   63, 47, 56, 27, 60, 41, 37, 16,
   54, 35, 52, 21, 44, 32, 23, 11,
   46, 26, 40, 15, 34, 20, 31, 10,
   25, 14, 19,  9, 13,  8,  7,  6
};

U64 Bishop_classical(int indx, U64 blocker)
{
	U64 attacks = 0ULL;

	// North West
	attacks |= RAYS[Direction::NORTH_WEST][indx];
	if (RAYS[Direction::NORTH_WEST][indx] & blocker) {
		unsigned long blockerIndex;
		unsigned char valid = _BitScanForward64(&blockerIndex, 
			RAYS[Direction::NORTH_WEST][indx] & blocker);
		if (valid) {
			attacks &= ~RAYS[Direction::NORTH_WEST][blockerIndex];
		}
	}

	// North East
	attacks |= RAYS[Direction::NORTH_EAST][indx];
	if (RAYS[Direction::NORTH_EAST][indx] & blocker) {
		unsigned long blockerIndex;
		unsigned char valid = _BitScanForward64(&blockerIndex, 
			RAYS[Direction::NORTH_EAST][indx] & blocker);
		if (valid) {
			attacks &= ~RAYS[Direction::NORTH_EAST][blockerIndex];
		}
	}

	// South East
	attacks |= RAYS[Direction::SOUTH_EAST][indx];
	if (RAYS[Direction::SOUTH_EAST][indx] & blocker) {
		unsigned long blockerIndex;
		unsigned char valid = _BitScanReverse64(&blockerIndex, 
			RAYS[Direction::SOUTH_EAST][indx] & blocker);
		if (valid) {
			attacks &= ~RAYS[Direction::SOUTH_EAST][blockerIndex];
		}
	}

	// South West
	attacks |= RAYS[Direction::SOUTH_WEST][indx];
	if (RAYS[Direction::SOUTH_WEST][indx] & blocker) {
		unsigned long blockerIndex;
		unsigned char valid = _BitScanReverse64(&blockerIndex, 
			RAYS[Direction::SOUTH_WEST][indx] & blocker);
		if (valid) {
			attacks &= ~RAYS[Direction::SOUTH_WEST][blockerIndex];
		}
	}
	return attacks;
}


U64 Rook_classical(int indx, U64 blocker)
{
	U64 attacks = 0ULL;

	// North
	attacks |= RAYS[Direction::NORTH][indx];
	if (RAYS[Direction::NORTH][indx] & blocker) {
		unsigned long blockerIndex;
		unsigned char valid = _BitScanForward64(&blockerIndex, RAYS[Direction::NORTH][indx] & blocker);
		if (valid) {
			attacks &= ~RAYS[Direction::NORTH][blockerIndex];
		}
	}

	// East
	attacks |= RAYS[Direction::EAST][indx];
	if (RAYS[Direction::EAST][indx] & blocker) {
		unsigned long blockerIndex;
		unsigned char valid = _BitScanForward64(&blockerIndex, RAYS[Direction::EAST][indx] & blocker);
		if (valid) {
			attacks &= ~RAYS[Direction::EAST][blockerIndex];
		}
	}

	// South
	attacks |= RAYS[Direction::SOUTH][indx];
	if (RAYS[Direction::SOUTH][indx] & blocker) {
		unsigned long blockerIndex;
		unsigned char valid = _BitScanReverse64(&blockerIndex, RAYS[Direction::SOUTH][indx] & blocker);
		if (valid) {
			attacks &= ~RAYS[Direction::SOUTH][blockerIndex];
		}
	}

	//West
	attacks |= RAYS[Direction::WEST][indx];
	if (RAYS[Direction::WEST][indx] & blocker) {
		unsigned long blockerIndex;
		unsigned char valid = _BitScanReverse64(&blockerIndex, RAYS[Direction::WEST][indx] & blocker);
		if (valid) {
			attacks &= ~RAYS[Direction::WEST][blockerIndex];
		}
	}
	return attacks;
}



U64 Queen_classical(int indx, U64 blocker)
{
	return Bishop_classical(indx, blocker) | Rook_classical(indx, blocker);
}


int main()
{
	initialize_rays();
	Direction D = Direction::NORTH_EAST;
	const U64 board = 0xF7F6F3748CA5B610ULL;
	PrintBitBoard(board);

	std::cout << std::endl;
	std::cout << "Bishpop" << std::endl;
	U64 attacks = Bishop_classical(36, board);
	PrintBitBoard(attacks);

	std::cout << std::endl;
	std::cout << "Rook" << std::endl;
	attacks = Rook_classical(36, board);
	PrintBitBoard(attacks);

	std::cout << std::endl;
	std::cout << "Queen" << std::endl;
	attacks = Queen_classical(36, board);
	PrintBitBoard(attacks);

}
