// Created by Rohaan Mansoor
// Test suite for Movie Graph Recommendation System using Catch2

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "GraphConstruct.h"
#include "AdjacencyList.h"
#include <sstream>

TEST_CASE("CSV parsing handles basic and quoted titles") {
    GraphConstruct constructor;
    std::stringstream mockCSV;
    mockCSV << "movieId,title,year,genres,director\n"
    << "1,\"The Dark Knight\",2008,Action|Crime|Drama,Christopher Nolan\n"
    << "2,\"Inception\",2010,Action|Sci-Fi|Thriller,Christopher Nolan\n";

    std::ofstream out("test_movies.csv");
    out << mockCSV.str();
    out.close();

    auto movies = constructor.parseCSV("test_movies.csv");
    REQUIRE(movies.size() == 2);
    REQUIRE(movies[0].title == "The Dark Knight");
    REQUIRE(movies[1].genres.size() == 3);
    REQUIRE(movies[1].genres[1] == "Sci-Fi");
}

TEST_CASE("Genre map and adjacency list creation") {
    GraphConstruct constructor;
    vector<Movie> movies = {
            {"1", "Movie A", 2000, {"Action"}, "Dir A"},
            {"2", "Movie B", 2001, {"Action", "Thriller"}, "Dir B"},
            {"3", "Movie C", 2002, {"Thriller"}, "Dir C"}
};

constructor.buildGenreMap(movies);

vector<unordered_set<int>> adjList;
constructor.buildAdjacencyList(adjList, movies);

REQUIRE(adjList[0].count(1) == 1);
REQUIRE(adjList[1].count(0) == 1);
REQUIRE(adjList[1].count(2) == 1);
REQUIRE(adjList[2].count(1) == 1);
REQUIRE(adjList[0].count(2) == 0);
}

TEST_CASE("PageRank scores and topK recommendations") {
GraphConstruct constructor;
vector<Movie> movies = {
        {"1", "Movie A", 2000, {"Action"}, "Dir A"},
        {"2", "Movie B", 2001, {"Action", "Thriller"}, "Dir B"},
        {"3", "Movie C", 2002, {"Thriller"}, "Dir C"}
};

constructor.buildIndexMap(movies);
constructor.buildGenreMap(movies);

vector<unordered_set<int>> adjList;
constructor.buildAdjacencyList(adjList, movies);

AdjacencyList graph;
graph.loadGraph(adjList, movies);
graph.pageRank(10, 0.85);

std::ostringstream oss;
graph.printTopK("Movie A", 1, oss);
std::string result = oss.str();

REQUIRE(result.find("Movie B") != std::string::npos);
}

TEST_CASE("Graceful handling of unknown movie titles") {
GraphConstruct constructor;
vector<Movie> movies = {
        {"1", "Movie A", 2000, {"Action"}, "Dir A"},
};

constructor.buildIndexMap(movies);
constructor.buildGenreMap(movies);
vector<unordered_set<int>> adjList;
constructor.buildAdjacencyList(adjList, movies);

AdjacencyList graph;
graph.loadGraph(adjList, movies);
graph.pageRank(10, 0.85);

std::ostringstream oss;
graph.printTopK("Unknown Movie", 1, oss);

REQUIRE(oss.str().find("not found") != std::string::npos);
}

TEST_CASE("Single movie dataset edge case") {
GraphConstruct constructor;
vector<Movie> movies = {
        {"1", "Solo", 2010, {"Drama"}, "Director"}
};

constructor.buildIndexMap(movies);
constructor.buildGenreMap(movies);
vector<unordered_set<int>> adjList;
constructor.buildAdjacencyList(adjList, movies);

AdjacencyList graph;
graph.loadGraph(adjList, movies);
graph.pageRank(10, 0.85);

std::ostringstream oss;
graph.printTopK("Solo", 1, oss);
std::string out = oss.str();

REQUIRE(out.find("No similar movies found for") != std::string::npos);
}
