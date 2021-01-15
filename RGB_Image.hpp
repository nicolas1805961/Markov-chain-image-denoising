#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Rand.hpp"
#include "stb_image.h"

class RGB_Image
{
private:
    int width;
    int height;
    std::vector<std::vector<Vector>> image;
    //std::vector<std::vector<Vector>> x;

public:
    RGB_Image(std::string const &filename, Rand &random);
    int get_width();
    int get_height();
    std::vector<std::vector<Vector>> get_image();
    //std::vector<std::vector<Vector>> get_x();
    ~RGB_Image();
};