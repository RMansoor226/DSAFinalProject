//
// Created by apaxm on 8/3/2025.
//


#ifndef MOVIERECOMMENDER_MOVIE_H
#define MOVIERECOMMENDER_MOVIE_H

#include <iostream>
#include <vector>
using namespace std;

struct Movie {
    string movieId;
    string title;
    int year;
    vector<string> genres;
    string director;
};

#endif //MOVIERECOMMENDER_MOVIE_H
