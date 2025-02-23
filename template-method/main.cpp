/*
 * Template Method Design Pattern
 *
 * The Template Method pattern defines the skeleton of an algorithm in a method,
 * deferring some steps to subclasses. It allows subclasses to redefine certain steps of an algorithm
 * without changing the algorithm's structure.
 * In this example, the Game class provides a template method (run) that defines the steps of the game,
 * while the Chess class implements the specific steps (start, take_turn, have_winner, get_winner).
 */

#include <iostream>

class Game
{
public:
    explicit Game(int number_ofplayers): number_of_players(number_ofplayers) 
    {}

    void run()
    {
        start();
        while(!have_winner())
        {
            take_turn();
            std::cout << "Player " << get_winner() << " wins.\n";
        }
    }

protected:
    int number_of_players;
    int current_player{0};

    virtual void start() = 0;
    virtual void take_turn() = 0;
    virtual int get_winner() = 0;
    virtual bool have_winner() = 0;
};

class Chess: public Game
{
public:
    explicit Chess(): Game{2}
    {}

protected:
    void start() override
    {
        std::cout << "Starting a game of chess with " << number_of_players << " players.\n";
    }

    bool have_winner() override
    {
        return turn == max_turns;
    }

    void take_turn() override
    {
        std::cout << "Turn " << turn  << " taken by plazer " << current_player << std::endl;
        ++turn;
        current_player = (current_player + 1) % number_of_players;
    }

    int get_winner() override
    {
        return current_player;
    }

private:
    int turn{0}, max_turns{10};
};

int main()
{
    Chess chess;
    chess.run();
    
    return 0;
}