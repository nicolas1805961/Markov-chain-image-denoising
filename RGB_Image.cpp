#include "RGB_Image.hpp"

RGB_Image::RGB_Image(std::string const& filename, Rand& random)
{
    int channels;
    unsigned char *RGB_Image_char = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    image = std::vector<std::vector<Vector>>(height, std::vector<Vector>(width));
    //x = std::vector<std::vector<Vector>>(height, std::vector<Vector>(width));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float r = static_cast<float>(RGB_Image_char[(width * i + j) * 3]) / 255.0;
            float g = static_cast<float>(RGB_Image_char[(width * i + j) * 3 + 1]) / 255.0;
            float b = static_cast<float>(RGB_Image_char[(width * i + j) * 3 + 2]) / 255.0;
            image[i][j] = Vector(r, g, b);
            //x[i][j] = random.rand();
            //x[i][j] = random.rand_color_cluster();
            //x[i][j] = random.rand_color();
            //x[i][j] = Vector(r, g, b);
        }
    }
    stbi_image_free(RGB_Image_char);
}

int RGB_Image::get_width() 
{
    return width;
}

int RGB_Image::get_height() 
{
    return height;
}

std::vector<std::vector<Vector>> RGB_Image::get_image() 
{
    return image;
}

/*std::vector<std::vector<Vector>> RGB_Image::get_x() 
{
    return x;
}*/

RGB_Image::~RGB_Image()
{
}