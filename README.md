# Travelling-Salesman-Algorithms
Four algorithms used to solve the Travelling Salesman Problem (TSP)

Each algorithm is more advanced than the previous one, starting from:
- Brute Force algorithm
- Held-Karp's algorithm
- Simulated Annealing algorithm
- Ant Colony algorithm

Each program has a few options:
- Loading data from a .txt file
- Printing the graph (matrix representation)
- Single instance of the algorithm, presenting the user with:
  - Minimum cost
  - Optimal tour
  - Time it took to compute the results
- Benchmark based on a .ini file, with results then saved to a .csv file


The structure of the .txt file can be written in up to four ways, depending on the algorithm (Simple Matrix, Matrix, Triangle, Real Coords, Coords):

1. Simple Matrix (without the "Vertex #number" at the leftmost parts of the file):

[Number of vertices]

Vertex #0: [Cost to travel to vertex #0], [Cost to travel to vertex #1], [...]

Vertex #1: [...]

[...]


2. Matrix (without the "Vertex #number" at the leftmost parts of the file):

MATRIX

[Number of vertices]

Vertex #0: [Cost to travel to vertex #0], [Cost to travel to vertex #1], [...]

Vertex #1: [...]

[...]

EOF


4. Triangle - same as the matrix, just without the lower part (below the diagonal). The difference is that the triangle is used for undirected graphs and the matrix for directed graphs

5. Coords:

COORDS

[Number of vertices]

[Vertex number] [Coordinate X] [Coordinate Y]

[...]

EOF


7. Real Coords:

REAL_COORDS

[Number of vertices]

[Vertex number] [Latitude] [Longitude]

[...]

EOF


Algorithms and their supported data types:
- Brute Force:
  - Simple Matrix
  - Matrix
- Held-Karp:
  - Simple Matrix
  - Matrix
- Simulated Annealing:
  - Simple Matrix
  - Matrix
- Ant Colony:
  - ALL OF THEM


The .ini file is used for benchmarking. It's structure is as follows:

[Name of the .txt file] [Number of Repetitions] [Minimum cost of the optimal path] [Optimal path]

[...]

[Name of the .csv file to save it to]
