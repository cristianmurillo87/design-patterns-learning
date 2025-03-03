#include <iostream>

enum MovieGenre
{
    ACTION,
    COMEDY
};

class IMovie
{
public:
    virtual void watch() = 0;
};

class HollywoodMovie: public IMovie
{
private:
    MovieGenre genre;
public:
    HollywoodMovie(MovieGenre genre): genre{genre} {}

    void watch() override
    {
        std::cout << "Watching a Hollywood " << genre << std::endl;
    }
};

class BollywoodMovie: public IMovie
{
private:
    MovieGenre genre;
public:
    BollywoodMovie(MovieGenre genre): genre{genre} {}

    void watch() override
    {
        std::cout << "Watching a Bollywood " << genre << std::endl;
    }

};