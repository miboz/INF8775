Required attributes of class node
- Neighbors
- Degree
- Label
- Map of neighbor colors -> number of adjacent nodes of that color

Important to use map and not set to be able to backtrack with the branch and bound algorithm

Another alternative is to use Complete state save instead of actual backtracking,
but may use a lot of process time due to copying the entire state
Will use sorted queue for the processing order of the greedy search

Min req:
- Greedy search: set of nodes with the same color
- Branch and bound: map of color -> number of nodes with that color
- Tabu search: map of color -> number of nodes with that color

But Tabu search data structure could be (maybe) optimized by avoiding using
brute force to get the best neighbor. A map of color -> number of nodes
with that color seems to require using brute force to get the best neighbor