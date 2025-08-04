//
// Created by Rohaan Mansoor on 8/2/2025.
//

#include "AdjacencyList.h"

#include <utility>
#include <algorithm>
#include <iomanip>
#include <functional>
#include <cmath>

AdjacencyList::AdjacencyList() {
    this->adjList = {};
    this->revAdjList = {};
    this->outDegrees = {};
    this->movies = {};
    this->ratings = {};
    this->titleToIndex.clear();
    this->indexToTitle.clear();
}

void AdjacencyList::loadGraph(const vector<unordered_set<int>>& list, const vector<Movie>& movieData) {
    adjList = list;
    movies = movieData;
    int n = adjList.size();

    // Clear all class data members
    revAdjList.resize(n);
    outDegrees.resize(n);
    ratings.assign(n, 1.0 / n);

    titleToIndex.clear();
    indexToTitle.clear();

    // Build reverse adjacency list and outdegrees
    for (int i = 0; i < n; ++i) {
        outDegrees[i] = adjList[i].size();
        titleToIndex[movies[i].title] = i;
        indexToTitle.push_back(movies[i].title);

        for (int j : adjList[i]) {
            revAdjList[j].insert(i);
        }
    }
}

void AdjacencyList::pageRank(int it, double d) {

    int n = adjList.size();
    vector<double> newRanks(n);

    for (int iter = 0; iter < it; ++iter) {
        fill(newRanks.begin(), newRanks.end(), 0.0);

        for (int i = 0; i < n; ++i) {
            for (int src : revAdjList[i]) {
                if (outDegrees[src] > 0)
                    newRanks[i] += ratings[src] / outDegrees[src];
            }
            // Apply the PageRank formula with damping factor
            newRanks[i] = (1 - d) / n + d * newRanks[i];
        }

        ratings = newRanks;
    }
}

void AdjacencyList::printTopK(const string& movieTitle, int k, ostream& output) const {

    // Check if movie title doesn't exist
    auto it = titleToIndex.find(movieTitle);
    if (it == titleToIndex.end()) {
        output << "Movie \"" << movieTitle << "\" not found.\n";
        return;
    }

    int movieIdx = it->second;
    const auto& neighbors = adjList[movieIdx];

    if (neighbors.empty()) {
        output << "No similar movies found for \"" << movieTitle << "\".\n";
        return;
    }

    // Gather neighbor titles and scores
    vector<pair<string, double>> rankedNeighbors;
    rankedNeighbors.reserve(neighbors.size());

    for (int neighborIdx : neighbors) {
        rankedNeighbors.emplace_back(indexToTitle[neighborIdx], ratings[neighborIdx]);
    }

    // Sort neighbors by score in descending order
    sort(rankedNeighbors.begin(), rankedNeighbors.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    // Print results
    int count = 0;
    for (const auto& [title, score] : rankedNeighbors) {
        output << title << " (" << fixed << setprecision(2) << score << ")\n";
        if (++count >= k) break;
    }
}

