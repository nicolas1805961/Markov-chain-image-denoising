#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Rand.hpp"
#include "stb_image.h"

class Image
{
private:
    int width;
    int height;
    std::vector<std::vector<float>> y;
    std::vector<std::vector<float>> x;


public:
    Image(std::string const &filename, Rand &random);
    int get_width();
    int get_height();
    std::vector<std::vector<float>> get_y();
    std::vector<std::vector<float>> get_x();
    ~Image();
};


