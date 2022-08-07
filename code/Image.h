#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <vector>

struct Color {
    double r, g, b;

    Color();
    Color(double r, double g, double b);
};

class Image {
private:
    int width;
    int height;
    std::vector<Color> colors;

public:
    Image(int width, int height);

    Color getColor(int x, int y) const;
    void setColor(const Color& color, int x, int y);

    int getWidth() const;
    int getHeight() const;
};

#endif