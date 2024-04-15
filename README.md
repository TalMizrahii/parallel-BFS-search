<h1 align="center">
  <br>
  <a href="https://github.com/TalMizrahii/parallel-BFS-search"><img src="https://img.icons8.com/color/344/c-plus-plus-logo.png" alt="C++" width="200"></a>
  <br>
  Parallel BFS search
  <br>
</h1>

<h4 align="center"> </h4>

<p align="center">
  <a href="#description">Description</a> •
  <a href="#implementation">Implementation</a> •
  <a href="#dependencies">Dependencies</a> •
  <a href="#installing-and-executing">Installing And Executing</a> •
  <a href="#author">Author</a> 
</p>

## Description

### About The Program

The Parallel BFS Search program implements a parallel Breadth-First Search algorithm for undirected graphs, aimed at calculating the shortest path matrix for the given graph. The shortest path matrix is updated with distances between each pair of vertices, where -1 represents infinity if no path exists between the vertices. 

The algorithm utilizes a thread pool and parallelization techniques to efficiently explore the graph in a breadth-first manner, discovering shortest paths in parallel. 


![download](https://github.com/TalMizrahii/parallel-BFS-search/assets/103560553/07369659-a288-431e-904f-f8cf97221c3a)

## Implementation

The program's implementation revolves around the following key aspects:

- **Parallel Breadth-First Search**: The core algorithm employs parallelization techniques, leveraging either `<pthread.h>` or `<thread>` as the thread library for concurrent exploration of the graph. A thread pool is utilized to manage and distribute tasks among available threads, enhancing efficiency and scalability.

- **Shortest Path Matrix Update**: The program updates the provided shortest path matrix with the distances between each pair of vertices discovered during the BFS traversal. It utilizes a suitable representation for infinity (such as -1) to denote unreachable vertices.

- **Graph Input**: The graph is inputted similarly to the DFS algorithm from the practical session, facilitating ease of testing using input redirection from a file. This ensures that graph input is streamlined and doesn't require manual entry during testing.

  
![download](https://github.com/TalMizrahii/parallel-BFS-search/assets/103560553/c804452c-9757-4f63-a7ae-9acb12cf2baf)

## Dependencies

This program has the following dependencies:

- **Thread Library**: The program requires `<thread>` as the thread library for managing parallelism. Ensure that the chosen library is supported and properly configured in the compilation environment.

## Installing And Executing

To install and run the program you use [Git](https://git-scm.com). From your command line:

```bash
# Clone this repository.
$ git clone https://github.com/TalMizrahii/parallel-BFS-search

# Navigate to the repository directory:
$ cd parallel-BFS-search

# Compile the program
$ make

# run the program
$ make run
```
## Author

* [@Tal Mizrahi](https://github.com/TalMizrahii)
* Taltalon1927@gmail.com
