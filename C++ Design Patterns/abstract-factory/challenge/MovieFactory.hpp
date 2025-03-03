#include <memory>

#include "Movie.hpp"

enum MovieCity
{
    BOLLYWOOD,
    HOLLYWOOD
};

class MovieFactory
{
public:
    virtual std::unique_ptr<IMovie> make(MovieGenre genre) = 0; 
};


class HollyWoodMovieFactory: MovieFactory
{
public:

    HollyWoodMovieFactory() {}

    std::unique_ptr<IMovie> make(MovieGenre genre) override
    {
        return std::make_unique<HollywoodMovie>(genre);
    }
};

class BollyWoodMovieFactory: MovieFactory
{
public:

    BollyWoodMovieFactory() {}

    std::unique_ptr<IMovie> make(MovieGenre genre) override
    {
        return std::make_unique<BollywoodMovie>(genre);
    }
};


class MovieProducer
{
private:
    std::unique_ptr<BollyWoodMovieFactory> bollywood_factory;
    std::unique_ptr<HollyWoodMovieFactory> hollywood_factory;

public:
    MovieProducer() {}

    std::unique_ptr<IMovie> make_movie(MovieCity city, MovieGenre genre) {
        if (city == MovieCity::BOLLYWOOD)
        {
            return bollywood_factory->make(genre);
        } else if (city == MovieCity::HOLLYWOOD)
        {
            return hollywood_factory->make(genre);
        }
    }
};