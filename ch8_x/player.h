#ifndef PLAYER_H
#define PLAYER_H
#pragma once

class Deck;

class Player
{
  public:
    enum PlayerClass
    {
        DEALER,
        PLAYER,
    };
    enum Answer
    {
        HIT,
        STAND,
    };

  private:
    PlayerClass m_type;
    int score;

  public:
    Player(PlayerClass type) : m_type(type)
    {
    }

    int Score() const
    {
        return score;
    }

    Answer getAnswer() const
    {
        // dealer logic
        if (m_type == Player::DEALER)
        {
            if (score < 17)
                return Answer::HIT;
            return Answer::STAND;
        }
        // player logic
        char ans;
        do
        {
            std::cout << "Hit or stand? (h/s)";
            std::cin >> ans;
            std::cin.ignore(32767, '\n');
        } while (ans != 'h' && ans != 's');
        if (ans == 'h')
            return Answer::HIT;
        return Answer::STAND;
    }

    friend class Deck;
};

#endif // !PLAYER_H
