#include <iostream>

#include "card.h"

void Card::printCard() const
{
    switch (m_rank)
    {
    case Card::RANK_2:
        std::cout << '2';
        break;
    case Card::RANK_3:
        std::cout << '3';
        break;
    case Card::RANK_4:
        std::cout << '4';
        break;
    case Card::RANK_5:
        std::cout << '5';
        break;
    case Card::RANK_6:
        std::cout << '6';
        break;
    case Card::RANK_7:
        std::cout << '7';
        break;
    case Card::RANK_8:
        std::cout << '8';
        break;
    case Card::RANK_9:
        std::cout << '9';
        break;
    case Card::RANK_10:
        std::cout << 'T';
        break;
    case Card::RANK_JACK:
        std::cout << 'J';
        break;
    case Card::RANK_QUEEN:
        std::cout << 'Q';
        break;
    case Card::RANK_KING:
        std::cout << 'K';
        break;
    case Card::RANK_ACE:
        std::cout << 'A';
        break;
    default:
        break;
    }

    switch (m_suit)
    {
    case Card::SUIT_CLUB:
        std::cout << 'C';
        break;
    case Card::SUIT_DIAMOND:
        std::cout << 'D';
        break;
    case Card::SUIT_HEART:
        std::cout << 'H';
        break;
    case Card::SUIT_SPADE:
        std::cout << 'S';
        break;
    default:
        break;
    }
}

int Card::getCardValue() const
{
    switch (m_rank)
    {
    case Card::RANK_2:
        return 2;
    case Card::RANK_3:
        return 3;
    case Card::RANK_4:
        return 4;
    case Card::RANK_5:
        return 5;
    case Card::RANK_6:
        return 6;
    case Card::RANK_7:
        return 7;
    case Card::RANK_8:
        return 8;
    case Card::RANK_9:
        return 9;
    case Card::RANK_10:
        return 10;
    case Card::RANK_JACK:
        return 10;
    case Card::RANK_QUEEN:
        return 10;
    case Card::RANK_KING:
        return 10;
    case Card::RANK_ACE:
        return 11;
    default:
        return 0;
    }
}