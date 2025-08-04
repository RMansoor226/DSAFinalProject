//
// Created by Rohaan Mansoor on 8/2/2025.
//

#include "AdjacencyMatrix.h"
#include <algorithm>
#include <cmath>
#include <functional>

AdjacencyMatrix::AdjacencyMatrix() {
    this->adjMatrix = {};
    this->outDegrees = {};
    this->movies = {};
    this->ratings = {};
    this->titleToIndex.clear();
    this->indexToTitle.clear();
}

void AdjacencyMatrix::loadGraph(const vector<vector<int>>& matrix, const vector<Movie>& movieData) {
    adjMatrix = matrix;
    movies = movieData;
    int n = matrix.size();

    // Clear all class data members
    outDegrees.resize(n, 0);
    ratings.assign(n, 1.0 / n);
    titleToIndex.clear();
    indexToTitle.clear();

    // Build outdegrees and title-index mappings
    for (int i = 0; i < n; ++i) {
        outDegrees[i] = 0;
        titleToIndex[movies[i].title] = i;
        indexToTitle.push_back(movies[i].title);

        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j])
                outDegrees[i]++;
        }
    }
}

void AdjacencyMatrix::pageRank(int it, double d) {
    int n = adjMatrix.size();
    vector<double> newRanks(n, 0.0);

    for (int iter = 0; iter < it; ++iter) {
        fill(newRanks.begin(), newRanks.end(), 0.0);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adjMatrix[j][i] == 1 && outDegrees[j] > 0)
                    newRanks[i] += ratings[j] / outDegrees[j];
            }
            // Apply the PageRank formula with damping factor
            newRanks[i] = (1 - d) / n + d * newRanks[i];
        }

        ratings = newRanks;
    }
}

void AdjacencyMatrix::printTopK(const string& movieTitle, int k, ostream& output) const {

    // Check if movie title doesn't exist
    auto it = titleToIndex.find(movieTitle);
    if (it == titleToIndex.end()) {
        output << "Movie \"" << movieTitle << "\" not found.\n";
        return;
    }

    int movieIdx = it->second;
    int n = adjMatrix.size();

    vector<pair<string, double>> neighbors;

    for (int i = 0; i < n; ++i) {
        if (adjMatrix[movieIdx][i]) {
            neighbors.emplace_back(indexToTitle[i], ratings[i]);
        }
    }

    if (neighbors.empty()) {
        output << "No similar movies found for \"" << movieTitle << "\".\n";
        return;
    }

    // Sort neighbors by score in descending order
    sort(neighbors.begin(), neighbors.end(),
         [](const auto& a, const auto& b) { return a.second > b.second; });

    // Print results
    for (int i = 0; i < k && i < neighbors.size(); ++i) {
        output << neighbors[i].first << " (" << fixed << setprecision(2)
               << neighbors[i].second << ")\n";
    }
}