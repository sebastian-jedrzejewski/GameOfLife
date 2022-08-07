#include "Image.h"

#include <iostream>
#include <fstream>

Color::Color()
    : r{0}, g{0}, b{0} {
}

Color::Color(double r, double g, double b)
    : r{r}, g{g}, b{b} {
}

Image::Image(int width, int height)
    : width{width}, height{height}, colors{std::vector<Color>(width*height)} {
}

Color Image::getColor(int x, int y) const {
    return colors[y * width + x];
}

void Image::setColor(const Color& color, int x, int y) {
    colors[y * width + x].r = color.r;
    colors[y * width + x].g = color.g;
    colors[y * width + x].b = color.b;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}