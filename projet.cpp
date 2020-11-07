#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Image.hpp"
#include "Rand.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

float l2norm(float x)
{
    return sqrt(pow(x, 2));
}

float get_ratio(float candidate, std::vector<std::vector<float>> const& x, std::vector<std::vector<float>> const& y, unsigned int i, unsigned int j)
{
    float regularizer_denominator = 0;
    float regularizer_numerator = 0;

    if (i > 0)
    {
        regularizer_denominator += fabs(x[i][j] - x[i - 1][j]);
        regularizer_numerator += fabs(candidate - x[i - 1][j]);
    }
    if (i < x.size() - 1)
    {
        regularizer_denominator += fabs(x[i][j] - x[i + 1][j]);
        regularizer_numerator += fabs(candidate - x[i + 1][j]);
    }
    if (j > 0)
    {
        regularizer_denominator += fabs(x[i][j] - x[i][j - 1]);
        regularizer_numerator += fabs(candidate - x[i][j - 1]);
    }
    else if (j < x.size() - 1)
    {
        regularizer_denominator += fabs(x[i][j] - x[i][j + 1]);
        regularizer_numerator += fabs(candidate - x[i][j + 1]);
    }

    float data_consistency_denominator = fabs(x[i][j] - y[i][j]);
    float u_denominator = 1 * data_consistency_denominator + 0 * regularizer_denominator;

    float data_consistency_numerator = fabs(candidate - y[i][j]);
    float u_numerator = 1 * data_consistency_numerator + 0 * regularizer_numerator;

    return u_denominator - u_numerator;
}

float get_ratio_potts(float candidate, std::vector<std::vector<float>> const& x, std::vector<std::vector<float>> const& y, unsigned int i, unsigned int j)
{
    float regularizer_denominator = 0;
    float regularizer_numerator = 0;
    if (i > 0)
    {
        regularizer_denominator += (x[i][j] != x[i - 1][j]);
        regularizer_numerator += (candidate != x[i - 1][j]);
    }
    if (i < x.size() - 1)
    {
        regularizer_denominator += (x[i][j] != x[i + 1][j]);
        regularizer_numerator += (candidate != x[i + 1][j]);
    }
    if (j > 0)
    {
        regularizer_denominator += (x[i][j] != x[i][j - 1]);
        regularizer_numerator += (candidate != x[i][j - 1]);
    }
    else if (j < x.size() - 1)
    {
        regularizer_denominator += (x[i][j] != x[i][j + 1]);
        regularizer_numerator += (candidate != x[i][j + 1]);
    }
    float data_consistency_denominator = powf(x[i][j] - y[i][j], 2);
    float u_denominator = 1 * data_consistency_denominator + 1 * regularizer_denominator;

    float data_consistency_numerator = powf(candidate - y[i][j], 2);
    float u_numerator = 1 * data_consistency_numerator + 1 * regularizer_numerator;

    return u_denominator - u_numerator;
}

float update_temp(float r)
{
    return pow(0.99, exp(8 * r));
}

std::vector<float> read_clusters(std::string const& filename)
{
    std::ifstream infile(filename.c_str());
    std::vector<float> clusters(8);
    std::string line;
    for (size_t i = 0; i < 8; i++)
    {
        std::getline(infile, line);
        std::istringstream iss(line);
        iss >> clusters[i];
    }
    return clusters;
}

int main()
{
    auto clusters = read_clusters("colors.txt");
    auto random = Rand(clusters);
    auto image = Image("peppers.jpg", random);
    auto y = image.get_y();
    auto x = image.get_x();
    auto h = image.get_height();
    auto w = image.get_width();

    float T = 4;
    unsigned int count = 0;
    unsigned int iterations = 100000000;

    for (size_t iter = 0; iter < iterations; iter++)
    {
        unsigned int row = random.randint(0, h - 1);
        unsigned int col = random.randint(0, w - 1);
        //float candidate = random.rand();
        float candidate = random.rand_cluster();
        //float value = get_ratio(candidate, x, y, row, col);
        float value = get_ratio_potts(candidate, x, y, row, col);
        float p = expf(std::min(0.0f, value) / T);
        if (random.rand() < p)
        {
            count++;
            x[row][col] = candidate;
        }
        T *= update_temp(static_cast<float>(iter) / static_cast<float>(iterations));
    }
    std::cout << count << '\n';
    std::ofstream ofs("out.pgm", std::ios::binary);
    ofs << "P5\n" << w << " " << h << "\n255\n";
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
            ofs << (char)(255 * x[i][j]);
    }
    ofs.close();

    return 0;
}

