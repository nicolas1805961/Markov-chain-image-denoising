#pragma once

#include <random>
#include <iostream>
#include "Vector.hpp"

class Rand
{
private:
    std::mt19937 generator;
    std::vector<float> clusters;
    std::vector<Vector> colors;

public :
    Rand();
    Rand(std::vector<float> const& clusters);
    Rand(std::vector<Vector> const& colors);
    float rand();
    int randint(int start, int stop);
    float rand_cluster();
    Vector rand_color_cluster();
    Vector rand_color();
    ~Rand();
};


