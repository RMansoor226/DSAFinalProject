//
// Created by Rohaan Mansoor on 8/2/2025.
//

#ifndef MOVIERECOMMENDER_ADJACENCYLIST_H
#define MOVIERECOMMENDER_ADJACENCYLIST_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Movie.h"

using namespace std;

class AdjacencyList {

    // Nested vector to implement the adjacency list
    vector<unordered_set<int>> adjList;

    // Reverse adjacency list to track incoming edges
    vector<unordered_set<int>> revAdjList;

    // Vector to hold outdegrees of each page
    vector<int> outDegrees;

    vector<Movie> movies;
    vector<double> ratings;

    // Maps movie titles to their indices
    unordered_map<string, int> titleToIndex;

    // Vector to hold movie titles for output
    vector<string> indexToTitle;

public:

    // Default constructor
    AdjacencyList();

    void loadGraph(const vector<unordered_set<int>>& list, const vector<Movie>& movies);
    void pageRank(int it, double d);
    void printTopK(const string& movieTitle, int k, ostream& output) const;
};


#endif MOVIERECOMMENDER_ADJACENCYLIST_H
