//
// Created by Rohaan Mansoor on 8/3/2025.
//

#include "GraphConstruct.h"

const vector<Movie>& GraphConstruct::getMovies() const {
    return movies;
}

const vector<unordered_set<int>>& GraphConstruct::getAdjList() const {
    return adjList;
}

const vector<vector<int>>& GraphConstruct::getAdjMatrix() const {
    return adjMatrix;
}

vector<Movie> GraphConstruct::parseCSV(const string& filename) {
    vector<Movie> movies;
    ifstream file(filename);
    string line;

    // Skip header
    getline(file, line);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return {};
    }

    while (getline(file, line)) {
        stringstream ss(line);
        Movie m;
        string col, genresStr;

        // ID
        if (!getline(ss, m.movieId, ',')) continue;

        // Title
        if (ss.peek() == '"') {
            getline(ss, col, '"'); // skip leading quote
            getline(ss, m.title, '"'); // read until ending quote
            ss.ignore(1); // skip comma
        } else {
            getline(ss, m.title, ',');
        }

        // Year
        if (!getline(ss, col, ',')) continue;
        try {
            m.year = stoi(col);
        } catch (...) {
            m.year = 0;
        }

        // Genres
        if (!getline(ss, genresStr, ',')) continue;

        // Director
        if (!getline(ss, m.director)) continue;

        // Parse genres
        stringstream gs(genresStr);
        string genre;
        while (getline(gs, genre, '|')) {
            if (!genre.empty()) m.genres.push_back(genre);
        }

        movies.push_back(m);
    }

    return movies;
}


void GraphConstruct::buildIndexMap(const vector<Movie> &movies) {
    for (size_t i = 0; i < movies.size(); ++i) {
        movieIdToIndex[movies[i].movieId] = i;
        indexToMovieId.push_back(movies[i].movieId);
    }
}

void GraphConstruct::buildGenreMap(const vector<Movie>& movies) {
    for (size_t i = 0; i < movies.size(); ++i) {
        for (const auto& genre : movies[i].genres) {
            genreMap[genre].push_back(i);
        }
    }
}

void GraphConstruct::buildAdjacencyList(vector<unordered_set<int>>& adjList, const vector<Movie>& movies) {
    adjList.resize(movies.size());

    // Iterate over each genre
    for (const auto& [genre, movieIndices] : genreMap) {
        // Connect every pair of movies in this genre
        for (size_t i = 0; i < movieIndices.size(); ++i) {
            for (size_t j = i + 1; j < movieIndices.size(); ++j) {
                int idx1 = movieIndices[i];
                int idx2 = movieIndices[j];

                adjList[idx1].insert(idx2);
                adjList[idx2].insert(idx1);
            }
        }
    }
}

void GraphConstruct::buildAdjacencyMatrix(vector<vector<int>>& adjMatrix, const vector<Movie>& movies) {
    size_t n = movies.size();

    // Initialize empty adjacency matrix
    adjMatrix.clear();
    adjMatrix.resize(n);
    for (auto& row : adjMatrix) {
        row.resize(n, 0);
    }

    // Build connections genre-by-genre
    for (const auto& [genre, indices] : genreMap) {
        for (size_t i = 0; i < indices.size(); ++i) {
            int u = indices[i];
            for (size_t j = i + 1; j < indices.size(); ++j) {
                int v = indices[j];
                adjMatrix[u][v] = 1;
                adjMatrix[v][u] = 1;
            }
        }
    }
}