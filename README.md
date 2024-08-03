# DFS Recursive Pathfinding
DFS Recursive algorithm for determining all paths and their corresponding costs from a user-provided starting index to a user-provided destination index, given an input file containing mappings of Nodes and their associated costs to construct the graph.
|                       |                                                                                                                               |
|----------------------:|-------------------------------------------------------------------------------------------------------------------------------|
|**Last Modified Date:**| 2/19/20                                                                                                                       |
|**Last Modifications:**| Fine-tuning project output and finalizing tests                                                                               |
|     **Documentation:**| [Doc Site](https://codedocs.xyz/GriffinNye22/DFS-Recursive-Pathfinding/)                                                      |  
|          **Platform:**| UNIX                                                                                                                          |
|          **Language:**| C++                                                                                                                           |

## Adjacency List Design
For my adjacency list, I utilized a vector of vectors of type Node, with Node being a custom-defined struct containing two data members: val and cost.

In order to maintain encapsulation, I set both of Node's data members to private and implemented member functions to set and retrieve these data members. 

I decided to utilize vectors for my adjacency list due to their dynamic nature, as a vertex could hypothetically have an exponentially large number of neighbors.

Each element in the outer vector corresponds to a vertex in the graph, with the inner vector being its list of adjacent vertices.

Each element in the inner vector is an instance of type Node, where val corresponds to the vertex number and cost corresponds to the weight of the edge directed from the outer element to val.

 A vertex with no adjacent vertices contains an empty inner vector, but still exists as an element in the outer vector.
*Ex. For a graph containing a single edge of weight 2 traversing from vertex 0 to vertex 1:
```cpp
adjacencyList[0][0].val = 1;
adjacencyList[0][0].cost = 2;
adjacencyList.size() = 2;
adjacencyList[1].size() = 0;
```
					
## Major Design Decisions
I decided to utilize the Node type, as it seemed to be more organized than utilizing a map within the inner vector. Seeing as though map is of type pair, which is just a standard template class implementation of a struct containing 2 data members, Node provides similar functionality while maintaining simplicity.

fillAdjList() assumes input text file provides vertices in chronological order starting from vertex 0 up to vertex n.  
(In other words, the vertex number = line number - 1).

Vector of integers was chosen as the STL sequential container for holding currently traversed path.

Algorithm for finding paths utilizes recursive DFS-like algorithm with a boolean array for marking vertices, an index for keeping track of path length, a vector of integers for holding the currently traversed path, and tracks the cost of the current path contained in said vector of integers.

Algorithm for finding all paths broken into two functions: one preparing the additional data structures required for the recursive algorithm (findPaths) and one performing the recursion (recursiveFind).

Map with key of type integer and a value with type vector of strings was chosen as the associative container for holding and ordering the set of all paths from starting vertex to destination vertex.

Successful paths are converted from a vector of integers to a space delimited string of the path before being inserted into map of successful paths.

Paths with same totalCost are stored in the vector accessible by the key equal to their cost.
		
## Info to Run Program
compile: g++ paths.cpp  
execute: ./a.out  

