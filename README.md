# 8-PuzzleSolver

# Introduction:

A sliding puzzle is a common combinatorial game for children. The game consists of frame with tiles arranged in a square grid and a singular empty slot. The player can then slide adjacent pieces into the empty slot to rearrange the tiles. Each tile is marked with a unique number. The objective is to put the tiles in numerical order and the empty space on the bottom right. Although a 4 by 4 grid with 15 tiles a common version of the game, a simpler version of this game with only 8 tiles on a 3 by 3 grid exists.
The objective of this project is to explore the different algorithms used in solving the 8-puzzle. We will explore A* using 3 different heuristics: Uniform Cost Search, Misplaced Tile and Manhattan Distance. This has been coded in C++.

# Comparison of Algorithms Basic Strategy:
The three heuristics that were used are Uniform Cost Search, the Misplaced Tile heuristic, and the Manhattan Distance heuristic. Algorithms that use heuristics consider the distance each move makes towards the goal state in addition to the cost with an h(n) in addition to the cost g(n). These two scores are totaled as f(n) and then f(n) is used to consider optimal moves.

## Uniform Cost Search:

Uniform Cost Search is a variant of A* where h(n) = 0 in all states. This algorithm will only attempt to expand nodes using the cheapest cost. In this problem, since the cost of moving a tile is in any direction is as the same, the cost of any move will be g(n) = 1.

## A* using the Misplaced Tile heuristic:

In the Misplaced Tile heuristics, the distance from the goal state h(n) is calculated by counting the number of tiles that are in the wrong position. As we choose to expand states, we prioritize the expansion of nodes that have the lowest cost and have the least number of tiles in the wrong positions. 

Ex) 

1 2 4

7 5 6

8 \ 3  

has a h(n) = 4 because the 4, 7, 8, and 3 tiles are in the wrong position. When making a move, the algorithm prioritizes the expansion 

1 2 4

7 5 6

\ 8 3  

with h(n) = 3 over 


1 2 4

7 5 6

8 3 \

with h(n) = 4, assuming the same cost. 

## A* using the Manhattan Distance heuristic:

Like, the Misplaced Tile heuristic, the Manhattan Distance also considers the distance from the goal state as it constructs the tree of moves. The Manhattan distance considers the actual distance each tile is from its goal location.

Ex) 

1 2 4

7 5 6

8 \ 3

would calculate h(n) as 6 because the misplaced tiles 4, 7, 8, and 3 are 3, 1, 1, and 2 positions away from their goal positions, respectively. Again, the algorithm will prioritize paths that have a low cost and a low distance from the goal. 


1 2 4

7 5 6

\ 8 3

with h(n) = 6 would be prioritized over  

1 2 4

7 5 6

8 3 \

with a h(n) = 8.

# Comparison of Algorithms in Solving Puzzles:

Below is are some samples puzzles and the depth and total expanded nodes for each puzzle. With easier problems, it is easy to see that Uniform Cost is less efficient than the other 2 algorithms. As the depth of the puzzles and their difficulty increases, Manhattan Distance marginally outperforms Misplaced Tiles. 

### Puzzle 1:	

1 2 3

4 \ 5

7 8 6

Uniform Cost:	

Depth: 2

Nodes expanded: 12

Misplaced Tile:

Depth: 2

Nodes expanded: 6	

Manhattan Distance:

Depth: 2

Nodes expanded: 6

### Puzzle 2:	

1 2 3

4 8 \

7 6 5

Uniform Cost:	

Depth: 5

Nodes expanded: 64

Misplaced Tile:

Depth: 5

Nodes expanded: 17	

Manhattan Distance:

Depth: 5

Nodes expanded: 11

### Puzzle 3:	

1 3 6

5 2 \

4 7 8

Uniform Cost:	

Depth: 8

Nodes expanded: 274

Misplaced Tile:

Depth: 8

Nodes expanded: 14	

Manhattan Distance:

Depth: 8

Nodes expanded: 14

### Puzzle 4:	

1 3 4

7 5 6

8 \ 3

Uniform Cost:	

Depth: 8

Nodes expanded: 374

Misplaced Tile:

Depth: 8

Nodes expanded: 33	

Manhattan Distance:

Depth: 8

Nodes expanded: 23

Because Uniformed Cost Search weights each move equally, it only expands based on the number of moves away it is from the start state, it is essentially a breadth first search. It will expand all the nodes of one level at a time, regardless of whether that node moves us toward a solution or not. The total number of directions all the tiles can move is 24 and the total tiles are 9 so the average number of followers per node is 8/3 so this algorithm had a time and space complexity of O((8/3)^d), where d is the depth of a given puzzle. This is this is a huge limitation on uniform cost search. Consider a problem whose solution is more than 10 moves away. In order to search the states 11 moves away we need to expand and store 18,184 nodes.

While the time and space complexity of the other algorithms depend on their heuristics, they both perform a combination of depth and breadth first search by going down some optimal path until the cost becomes too heavy and we then choose another branch to expand. So. depth and breadth first search act as bounds on the time and space complexity of these algorithms. Depth first search has a time complexity of O((8/3)^d) for this tree as well. However, the space complexity of depth first search is O(d), which is a vast improvement over the exponential space complexity of Uniform Cost Search. The additional improvement is that it chooses to expand along branches that bring us closer to a solved state. The heuristic on the Manhattan distance is marginally better because it considers not just the unsolved positions but also the distance that tile must move to get toward its solved position. In the Manhattan distance, a state where the unsolved pieces are immediately next to their solved state is much closer to a solution than one where they are on the opposite sides of the grid, so the choices in the nodes that are expanded will be marginally better. This difference is inconsequential for easier problems, but with more difficult problems, this would be far more significant.

# Conclusion:

Between the three variants on A*, the Manhattan Distance found the solution with the fewest expanded nodes, followed by the Misplace Tiles, and finally the Uniform Cost Search. An approach that applies a uniform cost is simply a BFS. By applying a better heuristic function, we can reduce the time and space needed to find a solution significantly. A good heuristic should not only consider the differences in the states between nodes but should analyze those differences as well. 

# Examples:

Below are two examples of the Manhattan Distance are given on problems of two levels of difficulty: easy and hard. The first one is on a problem of depth 5 and the second is on a problem of depth 16.


 
## Traceback for an easy problem:

Welcome to Samiha Kibria's 8-puzzle solver.

Enter your puzzle, represent blank with a 0

Enter row 1, separate numbers with spaces: 1 2 3

Enter row 2, separate numbers with spaces: 4 8 0

Enter row 3, separate numbers with spaces: 7 6 5

Enter choice of algorithm:

     1. Uniform Cost Search
 
     2. A* with Misplaced Tile heuristic
     
     3. A* with Manhattan distance heuristic

3

Expanding:

1 2 3

4 8 5

7 6 0

…

The best state to expand with g(n) = 4 and h(n) = 1 is...

1 2 3

4 5 0

7 8 6

Goal has been reached!

To solve this problem the search algorithm expanded a total of 11.

The maximum number of nodes in the queue at any one time was 6.

The depth of the goal node was 5.

 
## Traceback for a hard problem:

Welcome to Samiha Kibria's 8-puzzle solver.

Enter your puzzle, represent blank with a 0

Enter row 1, separate numbers with spaces: 1 6 7

Enter row 2, separate numbers with spaces: 5 0 3

Enter row 3, separate numbers with spaces: 4 8 2

Enter choice of algorithm:

     1. Uniform Cost Search
     
     2. A* with Misplaced Tile heuristic
     
     3. A* with Manhattan distance heuristic

3

Expanding:

1 0 7

5 6 3

4 8 2

The best state to expand with g(n) = 2 and h(n) = 10 is...

1 7 0

5 6 3

4 8 2

The best state to expand with g(n) = 3 and h(n) = 9 is...

1 7 3

5 6 0

4 8 2

The best state to expand with g(n) = 4 and h(n) = 8 is...

1 7 3

5 0 6

4 8 2

… 

The best state to expand with g(n) = 14 and h(n) = 4 is...

1 2 3

5 0 6

4 7 8

The best state to expand with g(n) = 15 and h(n) = 3 is...

1 2 3

0 5 6

4 7 8

The best state to expand with g(n) = 16 and h(n) = 2 is...

1 2 3

4 5 6

0 7 8

The best state to expand with g(n) = 17 and h(n) = 1 is...

1 2 3

4 5 6

7 0 8

Goal has been reached!

To solve this problem the search algorithm expanded a total of 387.

The maximum number of nodes in the queue at any one time was 150.

The depth of the goal node was 18.
