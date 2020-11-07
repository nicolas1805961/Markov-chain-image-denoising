#pragma once

#include <random>
#include <iostream>

class Rand
{
private:
    std::mt19937 generator;
    std::vector<float> clusters;

public :
    Rand(std::vector<float> const& clusters = std::vector<float>());
    float rand();
    int randint(int start, int stop);
    float rand_cluster();
    ~Rand();
};


