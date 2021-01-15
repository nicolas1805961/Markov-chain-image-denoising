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
    std::vector<std::vector<float>> image;
    //std::vector<std::vector<float>> x;


public:
    Image(std::string const &clearedImage, Rand &random);
    int get_width();
    int get_height();
    std::vector<std::vector<float>> get_image();
    //std::vector<std::vector<float>> get_x();
    ~Image();
};


