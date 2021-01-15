#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Image.hpp"
#include "RGB_Image.hpp"
#include <map>

float get_ratio(float candidate, std::vector<std::vector<float>> const& x, std::vector<std::vector<float>> const& y, unsigned int i, unsigned int j)
{
    float regularizer_denominator = 0;
    float regularizer_numerator = 0;

    if (i > 0)
    {
        regularizer_denominator += fabs(y[i][j] - y[i - 1][j]);
        regularizer_numerator += fabs(candidate - y[i - 1][j]);
    }
    if (i < x.size() - 1)
    {
        regularizer_denominator += fabs(y[i][j] - y[i + 1][j]);
        regularizer_numerator += fabs(candidate - y[i + 1][j]);
    }
    if (j > 0)
    {
        regularizer_denominator += fabs(y[i][j] - y[i][j - 1]);
        regularizer_numerator += fabs(candidate - y[i][j - 1]);
    }
    else if (j < x.size() - 1)
    {
        regularizer_denominator += fabs(y[i][j] - y[i][j + 1]);
        regularizer_numerator += fabs(candidate - y[i][j + 1]);
    }

    float data_consistency_denominator = fabs(x[i][j] - y[i][j]);
    float u_denominator = 1 * data_consistency_denominator + 1 * regularizer_denominator;

    float data_consistency_numerator = fabs(candidate - y[i][j]);
    float u_numerator = 1 * data_consistency_numerator + 1 * regularizer_numerator;

    return u_denominator - u_numerator;
}

float get_ratio_color(Vector const &candidate, std::vector<std::vector<Vector>> const &x, std::vector<std::vector<Vector>> const &y, unsigned int i, unsigned int j)
{
    float regularizer_denominator = 0;
    float regularizer_numerator = 0;

    if (i > 0)
    {
        regularizer_denominator += (y[i][j] - y[i - 1][j]).norm();
        regularizer_numerator += (candidate - y[i - 1][j]).norm();
    }
    if (i < x.size() - 1)
    {
        regularizer_denominator += (y[i][j] - y[i + 1][j]).norm();
        regularizer_numerator += (candidate - y[i + 1][j]).norm();
    }
    if (j > 0)
    {
        regularizer_denominator += (y[i][j] - y[i][j - 1]).norm();
        regularizer_numerator += (candidate - y[i][j - 1]).norm();
    }
    else if (j < x.size() - 1)
    {
        regularizer_denominator += (y[i][j] - y[i][j + 1]).norm();
        regularizer_numerator += (candidate - y[i][j + 1]).norm();
    }

    float data_consistency_denominator = (x[i][j] - y[i][j]).norm();
    float u_denominator = 1 * data_consistency_denominator + 1 * regularizer_denominator;

    float data_consistency_numerator = (candidate - y[i][j]).norm();
    float u_numerator = 1 * data_consistency_numerator + 1 * regularizer_numerator;

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

float get_ratio_potts_color(Vector const &candidate, std::map<Vector, float> myMap, std::vector<std::vector<Vector>> const &x, std::vector<std::vector<Vector>> const &y, unsigned int i, unsigned int j)
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
    float data_consistency_denominator = (x[i][j] - y[i][j]).norm();
    //float class_preference_denominator = -logf(myMap.find(x[i][j])->second);
    float u_denominator = 0 * data_consistency_denominator + 1 * regularizer_denominator; //+ 0 * class_preference_denominator;

    float data_consistency_numerator = (candidate - y[i][j]).norm();
    //float class_preference_numerator = -logf(myMap.find(candidate)->second);
    float u_numerator = 0 * data_consistency_numerator + 1 * regularizer_numerator; //+ 0 * class_preference_numerator;

    return u_denominator - u_numerator;
}

float update_temp(float r)
{
    return pow(0.99, exp(8 * r));
}

std::vector<float> read_distributions(std::string const &filename)
{
    std::ifstream infile(filename.c_str());
    std::string line;
    std::vector<float> clusters(8);
    for (size_t i = 0; i < 8; i++)
    {
        std::getline(infile, line);
        std::stringstream iss(line);
        iss >> clusters[i];
    }
    return clusters;
}

std::vector<Vector> read_colors(std::string const& filename)
{
    std::ifstream infile(filename.c_str());
    std::string line;
    std::vector<Vector> clusters(8, Vector(0));
    for (size_t i = 0; i < 8; i++)
    {
        std::getline(infile, line);
        std::stringstream iss(line);
        iss >> clusters[i][0] >> clusters[i][1] >> clusters[i][2];
    }
    return clusters;
}

std::vector<float> read_clusters(std::string const &filename)
{
    std::ifstream infile(filename.c_str());
    std::string line;
    std::vector<float> clusters(8);
    for (size_t i = 0; i < 8; i++)
    {
        std::getline(infile, line);
        std::istringstream iss(line);
        iss >> clusters[i];
    }
    return clusters;
}

std::map<Vector, float> getMap(std::vector<Vector> const &colors, std::vector<float> const &distributions)
{
    std::map<Vector, float> myMap;
    for (size_t i = 0; i < distributions.size(); i++)
        myMap[colors[i]] = distributions[i];
    return myMap;
}

int main()
{
    //auto clusters = read_clusters("colors.txt");
    //auto clusters = read_colors("colors.txt");
    //auto distributions = read_distributions("distributions.txt");
    //auto random = Rand(clusters);
    Rand random;
    //auto myMap = getMap(clusters, distributions);
    //auto cleanImage = Image("peppers.jpg", random);
    //auto noisyImage = Image("noisy_peppers.jpg", random);
    auto imageY = RGB_Image("quantized_peppers.jpg", random);
    auto imageX = RGB_Image("peppers.jpg", random);
    //auto y = cleanImage.get_image();
    auto y = imageY.get_image();
    //auto x = noisyImage.get_image();
    auto x = imageX.get_image();
    //auto h = cleanImage.get_height();
    auto h = imageY.get_height();
    //auto w = cleanImage.get_width();
    auto w = imageY.get_width();

    float T = 4;
    unsigned int count = 0;
    unsigned int iterations = 10000000;

    for (size_t iter = 0; iter < iterations; iter++)
    {
        unsigned int row = random.randint(0, h - 1);
        unsigned int col = random.randint(0, w - 1);
        //float candidate = random.rand();
        //float candidate = random.rand_cluster();
        //Vector candidate = random.rand_color_cluster();
        Vector candidate = random.rand_color();
        //float value = get_ratio(candidate, x, y, row, col);
        float value = get_ratio_color(candidate, x, y, row, col);
        //float value = get_ratio_potts_color(candidate, myMap, x, y, row, col);
        float p = expf(std::min(0.0f, value) / T);
        if (random.rand() < p)
        {
            count++;
            x[row][col] = candidate;
        }
        T *= update_temp(static_cast<float>(iter) / static_cast<float>(iterations));
    }
    std::cout << count << '\n';
    /*std::ofstream ofs("out.pgm", std::ios::binary);
    ofs << "P5\n" << w << " " << h << "\n255\n";
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
            ofs << (char)(255 * x[i][j]);
    }
    ofs.close();*/

    std::ofstream ofs("out.ppm", std::ios::binary);
    ofs << "P6\n" << w << " " << h << "\n255\n";
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            char r = (char)(255 * x[i][j][0]);
            char g = (char)(255 * x[i][j][1]);
            char b = (char)(255 * x[i][j][2]);
            ofs << r << g << b;
        }
    }
    ofs.close();

    return 0;
}

