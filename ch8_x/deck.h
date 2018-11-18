#ifndef DECK_H
#define DECK_H
#pragma once

#include <iostream>
#include <array>
#include <random>
#include <ctime>

#include "card.h"
#include "player.h"

class Deck
{
  private:
    std::array<Card, 52> m_deck;
    size_t m_deal;

  public:
    Deck() : m_deal(0)
    {
        for (size_t i = 0; i < static_cast<size_t>(Card::MAX_SUITS); i++)
            for (size_t j = 0; j < static_cast<size_t>(Card::MAX_RANKS); j++)
            {
                m_deck[static_cast<size_t>(Card::MAX_RANKS) * i + j] =
                    {static_cast<Card::CardRank>(j), static_cast<Card::CardSuit>(i)};
            }
    }

    void printDeck()
    {
        for (auto &card : m_deck)
        {
            card.printCard();
            std::cout << " ";
        }
        std::cout << std::endl;
    }

    void swapCard(Card &a, Card &b)
    {
        Card t = a;
        a = b;
        b = t;
    }

    void shuffleDeck()
    {
        static std::mt19937 mersanne(static_cast<unsigned int>(std::time(nullptr)));
        static std::uniform_int_distribution die(0, static_cast<int>(m_deck.size() - 1));

        for (size_t i = 0; i < m_deck.size(); i++)
        {
            size_t j = static_cast<size_t>(die(mersanne));
            swapCard(m_deck[i], m_deck[j]);
        }
    }

    const Card &dealCard()
    {
        return m_deck[m_deal++];
    }

    void giveCard(Player &player)
    {
        Card card = dealCard();
        if (player.m_type == Player::PLAYER)
        {
            std::cout << "You given: ";
            card.printCard();
            std::cout << "\n";
        }
        player.score += card.getCardValue();
    }
};

#endif // !DECK_H
