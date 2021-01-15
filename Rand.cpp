#include "Rand.hpp"

Rand::Rand() : generator(std::random_device()()), clusters(std::vector<float>()), colors(std::vector<Vector>())
{}

Rand::Rand(std::vector<float> const &clusters) : generator(std::random_device()()), clusters(clusters), colors(std::vector<Vector>())
{}

Rand::Rand(std::vector<Vector> const &colors) : generator(std::random_device()()), clusters(std::vector<float>()), colors(colors)
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

Vector Rand::rand_color_cluster() 
{
    std::uniform_int_distribution<> distribution(0, 7);
    auto index = distribution(generator);
    return colors[index];
}

Vector Rand::rand_color() 
{
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    auto r = distribution(generator);
    auto g = distribution(generator);
    auto b = distribution(generator);
    return Vector(r, g, b);
}

Rand::~Rand()
{
}