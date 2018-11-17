#include <iostream>
#include <array>
#include <random>
#include <ctime>

enum class CardRank
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

    MAX_RANKS,
};

enum class CardSuite
{
    SUIT_CLUB,
    SUIT_DIAMOND,
    SUIT_HEART,
    SUIT_SPADE,

    MAX_SUITS,
};

struct Card
{
    CardRank rank;
    CardSuite suite;
};

typedef std::array<Card, 52> Deck;

void printCard(const Card &card)
{
    switch (card.rank)
    {
    case CardRank::RANK_2:
        std::cout << "2";
        break;
    case CardRank::RANK_3:
        std::cout << "3";
        break;
    case CardRank::RANK_4:
        std::cout << "4";
        break;
    case CardRank::RANK_5:
        std::cout << "5";
        break;
    case CardRank::RANK_6:
        std::cout << "6";
        break;
    case CardRank::RANK_7:
        std::cout << "7";
        break;
    case CardRank::RANK_8:
        std::cout << "8";
        break;
    case CardRank::RANK_9:
        std::cout << "9";
        break;
    case CardRank::RANK_10:
        std::cout << "T";
        break;
    case CardRank::RANK_JACK:
        std::cout << "J";
        break;
    case CardRank::RANK_QUEEN:
        std::cout << "Q";
        break;
    case CardRank::RANK_KING:
        std::cout << "K";
        break;
    case CardRank::RANK_ACE:
        std::cout << "A";
        break;
    default:
        std::cout << "Invalid card rate!" << std::endl;
    }

    switch (card.suite)
    {
    case CardSuite::SUIT_CLUB:
        std::cout << "C";
        break;
    case CardSuite::SUIT_DIAMOND:
        std::cout << "D";
        break;
    case CardSuite::SUIT_HEART:
        std::cout << "H";
        break;
    case CardSuite::SUIT_SPADE:
        std::cout << "S";
        break;
    default:
        std::cout << "Invalid card suite!" << std::endl;
    }
}

void printDeck(const Deck &deck)
{
    for (auto &card : deck)
    {
        printCard(card);
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

void shuffleDeck(Deck &deck)
{
    std::mt19937 mersanne(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution die(0, static_cast<int>(deck.size() - 1));

    for (size_t i = 0; i < deck.size(); i++)
    {
        size_t j = static_cast<size_t>(die(mersanne));
        swapCard(deck[i], deck[j]);
    }
}

void fillDeck(Deck &deck)
{
    for (size_t i = 0; i < static_cast<size_t>(CardSuite::MAX_SUITS); i++)
        for (size_t j = 0; j < static_cast<size_t>(CardRank::MAX_RANKS); j++)
        {
            deck[static_cast<size_t>(CardRank::MAX_RANKS) * i + j] =
                {static_cast<CardRank>(j), static_cast<CardSuite>(i)};
        }
}

int getCardValue(Card &card)
{
    switch (card.rank)
    {
    case CardRank::RANK_JACK:
        return 2;
    case CardRank::RANK_QUEEN:
        return 3;
    case CardRank::RANK_KING:
        return 4;
    case CardRank::RANK_ACE:
        return 11;
    default:
        return static_cast<int>(card.rank) + 2;
    }
}

enum class Answer
{
    HIT,
    STAND,
};

Answer getAnswer()
{
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

enum class PlayerClass
{
    DEALER,
    PLAYER,
};

struct Player
{
    PlayerClass type;
    int score;
};

void giveCard(Player &player, Deck &deck, Card **cardPtr)
{
    if (*cardPtr == nullptr || *cardPtr == std::end(deck))
    {
        shuffleDeck(deck);
        printDeck(deck);
        *cardPtr = std::begin(deck);
    }

    if (player.type == PlayerClass::PLAYER)
    {
        std::cout << "You given: ";
        printCard(**cardPtr);
        std::cout << "\n";
    }
    player.score += getCardValue(**cardPtr);
    (*cardPtr)++;
}

bool blackjack(Deck deck, Player &player, Player &dealer)
{
    Card *cardPtr = nullptr;

    giveCard(dealer, deck, &cardPtr);
    giveCard(player, deck, &cardPtr);
    giveCard(player, deck, &cardPtr);
    std::cout << "Your score: " << player.score << ". Dealer score: " << dealer.score << std::endl;

    while (1)
    {
        if (getAnswer() == Answer::STAND)
            break;
        giveCard(player, deck, &cardPtr);
        if (player.score > 21)
            return false;
        std::cout << "Your score: " << player.score << std::endl;
    }

    while (dealer.score < 17)
    {
        giveCard(dealer, deck, &cardPtr);
        if (dealer.score > 21)
            return true;
        std::cout << "Dealer score: " << dealer.score << std::endl;
    }

    return player.score > dealer.score;
}

int main()
{
    Deck deck;
    fillDeck(deck);

    Player dealer = {PlayerClass::DEALER, 0};
    Player player = {PlayerClass::PLAYER, 0};

    if (blackjack(deck, player, dealer))
        std::cout << "You win! Your score: " << player.score << ". Dealer score: " << dealer.score << std::endl;
    else
        std::cout << "Dealer win! Your score: " << player.score << ". Dealer score: " << dealer.score << std::endl;
    return 0;
}