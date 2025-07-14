# Graphs Implementation

This program aims to implement, in C, some of the core concepts and algorithms from Graph Theory — a well-known data structure in computer science.

## Representation

Graphs can be represented in several ways, such as matrices and linked lists. In this case, we use the **Adjacency Matrix** representation.

<img src="./assets/adjacency-matrix.png" width="600" height="280">

The adjacency matrix is built from either a text file or manual user input, containing the following information:

**First line:**

    [num_vertices]  [num_edges]  [type]  [weighted]


**Subsequent lines:**

For each edge or arc **{vi, vj}**, add a line in the format:

    [vi]  [vj]  [weight]

#### Notes:

- **[type]**: Indicates the graph type. Use `G` for undirected graphs and `D` for directed graphs.
- **[weighted]**: Use `1` for weighted graphs and `0` for unweighted graphs.
- **[weight]**: This field is optional and only included for weighted graphs.
- Parallel edges or arcs may appear multiple times in the file.

## Implemented Algorithms

- Vertex degree calculation  
- Minimum Spanning Tree – Prim’s Algorithm  
- Shortest Path – Dijkstra’s Algorithm  
- Breadth-First Search (BFS)  
- Depth-First Search (DFS)  

## Tests

### Test 1

<img src="./assets/teste1-grafos.png" width="570" height="380">

### Test 2

<img src="./assets/teste2-grafos.png" width="570" height="380">

### Test 3

<img src="./assets/teste3-grafos.png" width="570" height="380">

### Test 4

<img src="./assets/teste4-grafos.png" width="570" height="380">

### Test 5

<img src="./assets/teste5-grafos.png" width="570" height="380">