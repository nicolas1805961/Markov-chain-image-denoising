#define STB_IMAGE_IMPLEMENTATION
#include "Image.hpp"

Image::Image(std::string const& filename, Rand& random)
{
    int channels;
    unsigned char *image_char = stbi_load(filename.c_str(), &width, &height, &channels, 1);

    image = std::vector<std::vector<float>>(height, std::vector<float>(width));
    //x = std::vector<std::vector<float>>(height, std::vector<float>(width));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = static_cast<float>(image_char[width * i + j]) / 255.0;
            //x[i][j] = random.rand();
            //x[i][j] = random.rand_cluster();
        }
    }

    stbi_image_free(image_char);
}

int Image::get_width() 
{
    return width;
}

int Image::get_height() 
{
    return height;
}

std::vector<std::vector<float>> Image::get_image() 
{
    return image;
}

/*std::vector<std::vector<float>> Image::get_x() 
{
    return x;
}*/

Image::~Image()
{
}