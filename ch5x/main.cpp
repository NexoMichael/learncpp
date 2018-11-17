#include <iostream>
#include <random>
#include <ctime>

struct GameSettings
{
    int tries_count;
    int min, max;
};

std::mt19937 mersanne(static_cast<unsigned int>(std::time(nullptr)));

bool game(GameSettings s)
{
    std::cout << "Let's play a game. I'm thinking of a number. You have " << s.tries_count << " tries to guess what it is" << std::endl;

    std::uniform_int_distribution<> die(s.min, s.max);

    int result = die(mersanne);

    for (int i = 0; i < s.tries_count; i++)
    {
        std::cout << "Guess " << (i + 1) << "#: ";
        int x;
        std::cin >> x;

        if (std::cin.fail())
            std::cin.clear();
        std::cin.ignore(32767, '\n');

        if (result == x)
        {
            std::cout << "Correct! You win!";
            return true;
        }
        if (x > result)
            std::cout << "Your guess is too high." << std::endl;
        if (x < result)
            std::cout << "Your guess is too low." << std::endl;
    }

    std::cout << "Sorry you lose. The correct number was " << result << "." << std::endl;
    return false;
}

bool playAgain()
{
    char ans;
    do
    {
        std::cout << "Would you like to play again (y/n): ";
        std::cin >> ans;

    } while (ans != 'y' && ans != 'n');
    return (ans == 'y');
}

int main()
{
    GameSettings settings = {7, 1, 100};
    int score = 0;
    do
    {
        if (game(settings))
            score++;
    } while (playAgain());
    std::cout << "Your score is: " << score << "." << std::endl;

    return 0;
}