/*
 * Proxy Design Pattern
 *
 * The Proxy pattern provides a surrogate or placeholder for another object to control access to it.
 * It is useful when you want to add a layer of control over the object, such as lazy initialization,
 * access control, logging, or caching.
 * In this example, the LazyBitmap class acts as a proxy for the Bitmap class, loading the image only when it is needed.
 */

#include <iostream>
#include <sstream>

struct Image
{
    virtual void draw() = 0;
};

struct Bitmap: Image
{
    Bitmap(const std::string& filename)
    {
        std::cout << "Loading image from " << filename << std::endl;
    }

    void draw() override
    {
        std::cout << "Drawing bitmap" << std::endl;
    }
};

struct LazyBitmap: Image
{
    LazyBitmap(const std::string& filename): filename{filename} {}

    void draw() override
    {
        if (!bmp)
            bmp = new Bitmap{filename};
        bmp->draw();
    }

private:
    Bitmap* bmp{nullptr};
    std::string filename;
};

int main()
{
    LazyBitmap img{"pokemon.png"};
    img.draw();
    return 0;
}