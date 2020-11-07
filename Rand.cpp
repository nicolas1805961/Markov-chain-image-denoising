#include "Rand.hpp"

Rand::Rand(std::vector<float> const &clusters) : generator(std::random_device()()), clusters(clusters)
{}

float Rand::rand() 
{
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    return distribution(generator);
}

int Rand::randint(int start, int stop) 
{
    std::uniform_int_distribution<> distribution(start, stop);
    return distribution(generator);
}

float Rand::rand_cluster() 
{
    std::uniform_int_distribution<> distribution(0, 7);
    auto index = distribution(generator);
    return clusters[index];
}

Rand::~Rand()
{
}