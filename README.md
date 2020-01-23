# Chess Engine

This is a basic CLI-based chess engine I designed and developed to better familiarize myself with object orientation and pointers in C++. It is not exceptional and rather than acting as a fully fledged chess engine, it was moreso an exercise for myself to learn more about chess and game tree decisions in general.

# Dependencies

- gcc/g++
- C++ (support for C++11 or higher, may need `-std=c++11` flag
- GNU/Linux

# Compilation and Execution

You can clone these files to your computer with the below:

` $ git clone https://github.com/stratzilla/chess-engine`

Compile with the below:

` $ cd chess-engine`  
` $ g++ src/source.cpp src/*/*.cpp -o chess`

Using `-O2` or `-O3` is advised. Execution as below:

` $ ./chess <args>`

Where `<args>` is either no or two arguments:

Using no arguments presents a Human vs. Human game. But, using two arguments will involve the AI as one or more of the players:

```
 <arg1> - Type of Game
  1. Human vs. Computer
  2. Computer vs. Human
  3. Computer vs. Computer
 <arg2> - Depth for Tree Search
  - some integer value >0
```

# How to Play

Upon executing the program with correct arguments, a chessboard will appear. Choose a move in the form of `a1b2` (for `a1` moves to `b2`), or just a single coordinate to display moves (for `a1`, this will display all moves the piece on `a1` could move). You can quit the game using command `quit`. As to how to play chess or play it effectively, I leave it as an exercise to the reader.

# Chess Representation

The engine respects the rule of chess with regards to movement with consideration for castling, piece promotion, capturing pieces, forcing the player to move out of check and inability to move into check. En passant is not implemented. Terminal board states are checkmate, draw, and stalemate although the AI will forfeit the match were it to have no confident moves to make.

# Board Evaluation

The heuristic evaluation function considers three aspects of the chess board:

- material value of all pieces
- mobility value of all pieces (how many moves can pieces make)
- pawn rank value of all pieces (how far are pawns from initial rank)

With the AI being positive and opposing player being negative. A ratio of all three is needed and the heuristic function can be stated as the balance below:

<img src="https://latex.codecogs.com/png.latex?%5Clarge%20h%20%3D%20c_1%20%5Ctimes%20v_%7B%5Ctext%7Bmaterial%7D%7D%20&plus;%20c_2%20%5Ctimes%20v_%7B%5Ctext%7Bmobility%7D%7D%20&plus;%20c_3%20%5Ctimes%20v_%7B%5Ctext%7Bpawn%20rank%7D%7D" />

Choosing effective coefficients can define the AI behavior:

| <img src="https://latex.codecogs.com/png.latex?c_1" /> | <img src="https://latex.codecogs.com/png.latex?c_2" /> | <img src="https://latex.codecogs.com/png.latex?c_3" /> | Behavior |
| --- | --- | --- | --- |
| 1   | 0   | 0   | Captures pieces and tries to keep pieces |
| 0   | 1   | 0   | Makes moves to promote board control |
| 0   | 0   | 1   | Moves pawns without consideration for promotion |
| 1   | 0   | 2   | Moves pawns with consideration for promotion |
| -1  | 0   | 0   | Prioritizes losing pieces (really dumb AI) |
| 0   | -1  | 0   | Makes the smallest moves possible and blocks self |
| 0   | 0   | -1  | Keeps pawns still (game becomes knight centric) |

And so on. Some experimentation is needed to find a good balance between coefficients, although the default configuration uses the below heuristic:

<img src="https://latex.codecogs.com/png.latex?%5Clarge%20h%20%3D%2012%20%5Ctimes%20v_%7B%5Ctext%7Bmaterial%7D%7D%20&plus;%201%20%5Ctimes%20v_%7B%5Ctext%7Bmobility%7D%7D%20&plus;%203%20%5Ctimes%20v_%7B%5Ctext%7Bpawn%20rank%7D%7D" />

This strikes a decent balance between keeping/taking pieces, making room for AI while removing other player opportunity to move, and moving pawns to get promotion. Currently, the defined heuristic may give some peculiar behavior (for example, sacrificing a queen if it encourages multiple pawns to progress ranks) but overall performs well. 

Any heuristic which has some consideration for material value will generally outperform a human opponent, but just barely: the other values are needed to give it more nuance as only considering material value doesn't make a convincing AI. It's useful to experiment because the heuristic can always be improved. Alternatively, you could design a genetic algorithm to find best coefficients. In general, however, I find the below is useful in finding good coefficients:

<img src="https://latex.codecogs.com/png.latex?%5Clarge%20c_1%2C%20c_2%2C%20c_3%20%5Cin%20%5Cleft%5B1%2C%5Cinfty%5Cright%29" />
<img src="https://latex.codecogs.com/png.latex?%5Clarge%20c_1%20%5Cgg%20c_3%20%3E%20c_2" />

That is, <img src="https://latex.codecogs.com/png.latex?c_1" /> should be the largest coefficient by some bigger degree than <img src="https://latex.codecogs.com/png.latex?c_3" /> is to <img src="https://latex.codecogs.com/png.latex?c_2" />.

Other game states are also evaluated: a stalemate/draw has a zero evaluation (as it is neither beneficial nor detrimental to the player), check is double the current board evaluation, and checkmate is double the highest possible board evaluation, plus one. This ensures a checkmate is not arbitrary and instead is the smallest value which is assured to be better than any (legal) board configuration, including board states in check.

Refer to `game/GameParams.hpp` for chess parameters including coefficients for heuristic evaluation.

# NegaMax Tree Search with Alpha-Beta Pruning

The chess engine uses a simple tree search using NegaMax (a variant of MiniMax) with alpha-beta pruning implemented. NegaMax relies on the mathematical maxim <img src="https://latex.codecogs.com/png.latex?Max%28a%2C%20b%29%20%3D%20-Min%28-a%2C%20-b%29" /> to shorten the MiniMax algorithm to roughly half the lines of MiniMax while maintaining identical performance:

```
function negamax(node, depth, α, β, player):
  if depth = 0:
    return player * eval(node)
  v := -inf
  foreach branch of node:
    v := max(v, -negamax(branch, depth-1, -β, -α, -player))
    α := max(α, v)
    if α >= β: break
  return v
```

`negamax` is called by a broader `negamaxHandler` which performs the first level of NegaMax manually so it can investigate the score of first moves (and their effect on the board) and then return an ideal move. In practice, the tree structure of the game is less like a typical tree and rather multiple trees: each first move is a root node in its own tree. This means first moves can be evaluated and compared.

To prevent threefold repetition, a move buffer is implemented for the AI. The AI is unable to make moves which it has previously made in the last three moves (by default). This eliminates infinite move repetition, at least within the scope of the buffer size. However, were a move reduplication be the only valid move, the AI will instead forfeit. This prevents overly lengthy games full of move repetitions which can become evident in the late game.

# Performance

While the performance is system specific, using a depth of `[1, 4]` results in very speedy AI decision and with a depth of `5` having adequate speed. The program can accept any depth greater than `0`, although the depth which NegaMax search uses is one plus this number (eg. using a depth of `1` searches 1 ply beyond available moves). Timing for moves is below:

| Depth | Early Game | Middle Game | Late Game | Average   |
| ----- | ---------- | ----------- | --------- | --------- |
| 1     | 1.8msec    | 1.0msec     | 1.4msec   | 1.3msec   |
| 2     | 3.9msec    | 3.4msec     | 1.9msec   | 3.0msec   |
| 3     | 67.9msec   | 117.9msec   | 111.7msec | 96.7msec  |
| 4     | 396.9msec  | 354.8msec   | 121.1msec | 298.2msec |
| 5     | 5.0sec     | 1.2sec      | 0.4sec    | 1.7sec    |
| 6     | 13.9sec    | 24.5sec     | 10.2sec   | 22.6sec   |
| 7     | 630.4sec   | 112.6sec    | 41.9sec   | 163.4sec  |

This is using a Ryzen 3600 at stock speeds and 3000mhz DDR4 memory. The testing environment is within LXSS (Ubuntu) in Windows 10 x64. Data collected from averaging five AI vs AI games, combining both AI player move times. Early Game means the first 10% of moves, Late Game means the last 10% of moves, and Middle Game is the remainder.

Beyond a depth of `7`, each move takes in excess of ten minutes, thus I did not test these depths. As for how the AI itself performs from a chess strategy standpoint: it relies heavily on appropriate heuristic evaluation coefficient choices. For the defined coefficients above, it is adequate and able to best myself at least.

# Future

On average, a typical player has 35 possible moves to make which means the branching factor of the tree is, on average, 35. This becomes unbelievably complex with a deeper depth hence the exponential growth between depth choices. If paralellism is implemented by way of multithreaded tree searching, a depth of `7` or possibly even `8` may become reasonable, although for the average person, a depth of `5` is generally adequate as a chess AI.

Usually, the early game is the most taxing as there are an abundance of pieces to check moves for. A dictionary of starting moves may make this aspect of the game quicker at least.

There was an attempt to keep board dumps and reference these scores to prune further branches. Dumping board states and score at every node in an `std::vector<std::string>` can let the AI reference these values were it to encounter a previously examined node. The problem is it is usually cheaper to recurse through branches rather than iterate over an `std::vector` which could be millions of elements large. I tried this method of further pruning and it was in fact slower than keeping it vanilla. This is a "poor" version of transposition tables and I may implement proper tables in the future along with Zobrist hashing.

A GUI may be nice, possibly use nodejs to interface with the C++ "backend". This program was never intended for, nor designed with in mind, a GUI, but if I get an off day in the future I might revisit this idea.

# Screenshots

<img src="https://github.com/stratzilla/chess-engine/blob/master/img/instructions.png" width="15%"/> <img src="https://github.com/stratzilla/chess-engine/blob/master/img/initial.png" width="15%"/> <img src="https://github.com/stratzilla/chess-engine/blob/master/img/movepreview.png" width="15%"/> <img src="https://github.com/stratzilla/chess-engine/blob/master/img/aiplaying.png" width="15%"/> <img src="https://github.com/stratzilla/chess-engine/blob/master/img/checkmate.png" width="15%"/>

From L-to-R: instructions for compilation and execution, initial game display, move display (Qa4), two AI players playing a game, one player checkmates another.
