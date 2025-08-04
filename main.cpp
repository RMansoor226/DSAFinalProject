#include <iostream>
#include <chrono>
#include <filesystem>
#include "GraphConstruct.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
using namespace std;

int main() {

    // Construct the graph from CSV file
    GraphConstruct constructor;
    string filename = "data/cleanMovies.csv";

    // Convert CSV data into vector of Movie objects
    vector<Movie> movies = constructor.parseCSV(filename);

    // Maps movies to indices
    constructor.buildIndexMap(movies);

    // Maps movis to genres
    constructor.buildGenreMap(movies);

    // Build Adjacency List
    vector<unordered_set<int>> adjList;
    constructor.buildAdjacencyList(adjList, movies);

    // Record start time for Adjacency List implementation
    auto startList = chrono::high_resolution_clock::now();

    // Run PageRank on Adjacency List
    AdjacencyList list;
    list.loadGraph(adjList, movies);
    list.pageRank(10, 0.85);

    // Record end time for Adjacency List implementation
    auto endList = chrono::high_resolution_clock::now();

    // Build Adjacency Matrix
    vector<vector<int>> adjMatrix;
    constructor.buildAdjacencyMatrix(adjMatrix, movies);

    // Record start time for Adjacency Matrix implementation
    auto startMatrix = chrono::high_resolution_clock::now();

    // Run PageRank on Adjacency Matrix
    AdjacencyMatrix matrix;
    matrix.loadGraph(adjMatrix, movies);
    matrix.pageRank(10, 0.85);

    // Record end time for Adjacency Matrix implementation
    auto endMatrix = chrono::high_resolution_clock::now();

    // Prompt user to enter favorite movie
    string userMovie;
    cout << "What's your favorite movie: ";
    getline(cin, userMovie);

    // Output recommendations
    cout << "Try these ones out (courtesy of Mr.Adjacency List):\n";
    list.printTopK(userMovie, 10, cout);

    cout << "Try these ones out (courtesy of Mr.Adjacency Matrix):\n";
    matrix.printTopK(userMovie, 10, cout); // After adding support

    // Calculate and print performance metrics
    chrono::duration<double> durationList = endList - startList;
    chrono::duration<double> durationMatrix = endMatrix - startMatrix;

    cout << "\nExecution Time (Adjacency List): " << durationList.count() << " seconds\n";
    cout << "Execution Time (Adjacency Matrix): " << durationMatrix.count() << " seconds\n";

    return 0;
}