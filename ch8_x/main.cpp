#include "card.h"
#include "deck.h"
#include "player.h"

bool blackjack(Deck deck, Player &player, Player &dealer)
{
    deck.giveCard(dealer);
    deck.giveCard(player);
    deck.giveCard(player);
    std::cout << "Your score: " << player.Score() << ". Dealer score: " << dealer.Score() << std::endl;

    while (player.getAnswer() == Player::HIT)
    {
        deck.giveCard(player);
        if (player.Score() > 21)
            return false;
        std::cout << "Your score: " << player.Score() << std::endl;
    }

    while (player.getAnswer() == Player::HIT)
    {
        deck.giveCard(dealer);
        if (dealer.Score() > 21)
            return false;
        std::cout << "Dealer score: " << dealer.Score() << std::endl;
    }

    return player.Score() > dealer.Score();
}

int main()
{
    Player dealer = Player(Player::DEALER);
    Player player = Player(Player::PLAYER);

    Deck deck;
    deck.shuffleDeck();
    deck.printDeck();

    if (blackjack(deck, player, dealer))
        std::cout << "You win! Your score: " << player.Score() << ". Dealer score: " << dealer.Score() << std::endl;
    else
        std::cout << "Dealer win! Your score: " << player.Score() << ". Dealer score: " << dealer.Score() << std::endl;

    return 0;
}