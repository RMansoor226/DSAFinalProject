//
// Created by Rohaan Mansoor on 8/3/2025.
//

#ifndef MOVIERECOMMENDER_GRAPHCONSTRUCT_H
#define MOVIERECOMMENDER_GRAPHCONSTRUCT_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "Movie.h"
using namespace std;

class GraphConstruct {

    unordered_map<string, int> movieIdToIndex;
    vector<string> indexToMovieId;

    // Map genre as vector of movie indices
    unordered_map<string, vector<int>> genreMap;

    vector<Movie> movies;
    vector<unordered_set<int>> adjList;
    vector<vector<int>> adjMatrix;

public:

    // Getters
    const vector<Movie>& getMovies() const;
    const vector<unordered_set<int>>& getAdjList() const;
    const vector<vector<int>>& getAdjMatrix() const;

    vector<Movie> parseCSV(const string& filename);
    void buildIndexMap(const vector<Movie> &movies);
    void buildGenreMap(const std::vector<Movie>& movies);
    void buildAdjacencyList(std::vector<std::unordered_set<int>>& adjList, const std::vector<Movie>& movies);
    void buildAdjacencyMatrix(std::vector<std::vector<int>>& adjMatrix, const std::vector<Movie>& movies);
};

#endif //MOVIERECOMMENDER_GRAPHCONSTRUCT_H