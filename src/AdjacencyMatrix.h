//
// Created by Rohaan Mansoor on 8/2/2025.
//

#ifndef MOVIERECOMMENDER_ADJACENCYMATRIX_H
#define MOVIERECOMMENDER_ADJACENCYMATRIX_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iomanip>
#include "Movie.h"

using namespace std;

class AdjacencyMatrix {
    // Nested vector to implement the adjacency matrix
    vector<vector<int>> adjMatrix;

    // Vector to hold outdegrees
    vector<int> outDegrees;

    vector<Movie> movies;
    vector<double> ratings;

    unordered_map<string, int> titleToIndex;
    vector<string> indexToTitle;

public:

    // Default Constructor
    AdjacencyMatrix();

    void loadGraph(const vector<vector<int>>& matrix, const vector<Movie>& movieData);
    void pageRank(int it, double d);
    void printTopK(const string& movieTitle, int k, ostream& output) const;
};

#endif MOVIERECOMMENDER_ADJACENCYMATRIX_H
