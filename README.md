# AlgoBrain
A research project in college supervised by Undergraduates Research Forum at Faculty of Engineering, Cairo University.

## Details
Our problem is that how to obtain the attack set of the next move for sliding pieces (queen, bishop and rock) in
computer chess engines. But why sliding pieces? The answer is that sliding pieces have so
many combinations to be considered. In this paper we will make a comparison between the classical
approach to obtain that and the magic bitboard approach and we will provide the reader with C++ implementation for the magic
approach as we aim to provide programmers who write chess engines a discussion of one of the fastest and most versatile movebitboard generators for individual sliding pieces

## Implementation
We found a library already implemented for the magical approach <a href="https://github.com/goutham/magic-bits">here</a> and we added the implementation for the classical approach in our repo to make a comparison between them.

## Future Work
* Providing the assembly code for both classical and magical approach.
* Providing the exact time for both classical and magical approach.
