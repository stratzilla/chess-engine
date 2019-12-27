# Chess Engine

This is a basic CLI-based chess engine I designed and developed to better familiarize myself with object orientation and pointers in C++. I marathoned it out in the matter of five days and while it's not perfect, perhaps resembles the largest achievement in programming I've done as of writing this readme.

# Compilation and Execution

You can clone these files to your computer with the below:

` $ git clone https://github.com/stratzilla/chess-engine`

Compile with the below:

` $ cd chess-engine`  
` $ g++ src/source.cpp src/*/*.cpp -o chess`

Using `-O2` or `-O3` is advised. Execution as below:

` $ ./chess <args>`

Where `<args>` is either two or three arguments:

Using two arguments:

```
 <arg1> - Type of Game
  1. Human vs. Human
  2. Human vs. Computer
  3. Computer vs. Computer
 <arg2> - Depth for Tree Search
  - some integer value >0
```

Using three arguments:

```
 <arg1> - Type of Game
 <arg2> - Depth for Tree Search
 <arg3> - Relative Path to Save File
```

Save files are stored as text files in `saves` directory. This will load a custom board state as that file describes. To test specific functionality, tests exist in `tests` and can showcase piece movement, castling, check, etc.

Execute with no arguments to be reminded of compilation and argument requirements.

# Dependencies

- gcc/g++
- C++ (support for C++11 or higher, may need `-std=c++11` flag
- GNU/Linux

# How to Play

Upon executing the program with correct arguments, a chessboard will appear. Choose a move in the form of `a1b2` (for `a1` moves to `b2`), or just a single coordinate to display moves (for `a1`, this will display all moves the piece on `a1` could move). You can save the game or quit the game using commands `save` and `quit` respectively. As to how to play chess or play it effectively, I leave it as an exercise to the reader.

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

This strikes a decent balance between keeping/taking pieces, making room for AI while removing other player opportunity to move, and moving pawns to get promotion. In general, I find the below is useful in finding good coefficients:

<img src="https://latex.codecogs.com/png.latex?%5Clarge%20c_1%2C%20c_2%2C%20c_3%20%5Cin%20%5Cleft%5B1%2C%5Cinfty%5Cright%29" />
<img src="https://latex.codecogs.com/png.latex?%5Clarge%20c_1%20%5Cgg%20c_3%20%3E%20c_2" />
<img src="https://latex.codecogs.com/png.latex?%5Clarge%20103c_1%20&plus;%2064c_2%20&plus;%2048c_3%20%3C%205%5Ctimes10%5E7" />

That is, <img src="https://latex.codecogs.com/png.latex?c_1" /> should be the largest coefficient by some bigger degree than <img src="https://latex.codecogs.com/png.latex?c_3" /> is to <img src="https://latex.codecogs.com/png.latex?c_2" />. As for the last condition: this is to confirm that the heuristic score does not exceed the value for checkmate. This is easy to abide by as the heuristic equation is reducible:

<img src="https://latex.codecogs.com/png.latex?%5Csmall%205c_1%20&plus;%205c_2%20&plus;%205c_3%20%5Cequiv%204c_1%20&plus;%204c_2%20&plus;%204c_3%20%5Cequiv%20%5Cdots%20%5Cequiv%20c_1%20&plus;%20c_2%20&plus;%20c_3" \>

Any coefficient choice where there is a common factor between them has an impact equivalent to the reduced form of the heuristic equation. In other words, since the heuristic is a balance between values, an equal ratio between values, irrespective of the ratio, has identical heuristic performance.

It's useful to experiment because the heuristic can always be improved. Alternatively, you could design a genetic algorithm to find best coefficients. 

Currently, the defined heuristic may give some peculiar behavior (for example, sacrificing a queen if it encourages multiple pawns to progress ranks) but overall performs well. Any heuristic which has some consideration for material value will generally outperform a human opponent, but just barely: the other values are needed to give it more nuance as only considering material value doesn't make a convincing AI.

# NegaMax/MiniMax Tree Search with Alpha-Beta Pruning

The chess engine uses a simple tree search using NegaMax (a variant of MiniMax) with alpha-beta pruning implemented. Recall MiniMax as below:

```
function minimax(node, depth, α, β, player):
  if depth = 0:
    return eval(node)
  if player = minimizingplayer:
    v := -inf
    foreach branch of node:
      v := max(v, minimax(branch, depth-1, α, β, minimizingplayer)
      α := max(α, v)
      if α >= β: break
  if player = minimizingplayer:
    v := +inf
    foreach branch of node:
      v := min(v, minimax(branch, depth-1, α, β, maximizingplayer)
      β := min(β, v)
      if α >= β: break
  return v
```

NegaMax relies on the mathematical maxim <img src="https://latex.codecogs.com/png.latex?Max%28a%2C%20b%29%20%3D%20-Min%28-a%2C%20-b%29" /> to optimize the algorithm to roughly half the lines of MiniMax while maintaining identical performance and result:

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

Some minor alterations to fit a chess engine are added to this, for example considering moves which bring the AI or the player into check, stalemate, or checkmate, etc.

`negamax` is called by a broader `negamaxHandler` which performs the first level of NegaMax manually so it can investigate the score of first moves (and their effect on the board) and then return an ideal move. In practice, the tree structure of the game is less like a typical tree and rather multiple trees: each first move is a root node in its own tree. This means first moves can be evaluated and compared. This lends itself well to parallelization which I may implement in the future, potentially making the tree search 35x faster at best cases.

# Pruning beyond Alpha-Beta

Besides alpha-beta pruning, the tree search is otherwise exhaustive but it doesn't need to be. Consider a branch node where the current board state is checkmate: this is a terminal case and there should be no future moves in branch nodes. The search algorithm evaluates branch nodes like this as a fixed value rather than recursing further to see more moves. Secondly, threefold repetition needs to be addressed with a move buffer: if the AI sees a branch node of a move which it has made within the last three moves, it needs to ignore this. Not only to prevent move reduplication but also to prune those branches.

There was an attempt to keep board dumps and reference these scores to prune further branches. Dumping board states and score at every node in an `std::vector<std::string>` can let the AI reference these values were it to encounter a previously examined node. The problem is it is usually cheaper to recurse through branches rather than iterate over an `std::vector` which could be millions of elements large. I tried this method of further pruning and it was in fact slower than keeping it vanilla.

# Performance

While the performance is system specific, using a depth of `[1, 4]` results in fairly speedy AI decision with a depth of `5` having adequate speed. The program can accept any depth greater than `0`, although the depth which NegaMax search uses is one plus this number (eg. using a depth of `1` searches 1 ply beyond available moves). Timing for moves is below:

| Depth | Early Game | Middle Game | Late Game | Average |
| ----- | ---------- | ----------- | --------- | ------- |
| 1     | <0.001s    | <0.001s     | <0.001s   | <0.001s |
| 2     | <0.005s    | <0.008s     | <0.001s   | <0.002s |
| 3     | <0.01s     | <0.03s      | <0.01s    | <0.01s  |
| 4     | <0.4s      | <0.5s       | <0.1s     | <0.4s   |
| 5     | <1.4s      | <6.2s       | <0.9s     | <3.2s   |
| 6     | <38s       | <58s        | <21s      | <45s    |

Beyond a depth of `6`, each move takes over a minute so I did not test. As for how the AI itself performs from a chess strategy standpoint: it relies heavily on appropriate heuristic evaluation coefficient choices. For the defined coefficients above, it is adequate and able to best myself at least.

On average, a typical player has 35 possible moves to make which means the branching factor of the tree is, on average, 35. This becomes unbelievably complex with a deeper depth hence the exponential growth between depth choices. If paralellism is implemented by way of multithreaded tree searching, a depth of `7` may become reasonable, although for most people, a depth of `5` is generally adequate as a chess AI.
