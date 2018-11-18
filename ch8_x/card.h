#ifndef CARD_H
#define CARD_H

class Card
{
public:
  enum CardSuit
  {
    SUIT_CLUB,
    SUIT_DIAMOND,
    SUIT_HEART,
    SUIT_SPADE,
    MAX_SUITS
  };

  enum CardRank
  {
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,
    MAX_RANKS
  };

private:
  Card::CardRank m_rank;
  Card::CardSuit m_suit;

public:
  Card(Card::CardRank rank = RANK_2, Card::CardSuit suit = SUIT_CLUB) : m_rank(rank), m_suit(suit)
  {
  }

  void printCard() const;
  int getCardValue() const;
};

#endif