#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include <string>
#include <chrono>
#include <thread>

char cards[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
std::vector<char> dealer;
std::vector<char> player;

int checkValue(int target)
{
    if (target == 0)
    {
        int dealerValue = 0;
        for (char card : dealer)
        {
            if (card == 'X')
            {
                dealerValue += 0;
            }
            else if (card >= '2' && card <= '9')
            {
                dealerValue += card - '0';
            }
            else if (card == 'T' || card == 'J' || card == 'Q' || card == 'K')
            {
                dealerValue += 10;
            }
            else if (card == 'A' && (dealerValue + 11) <= 21)
            {
                dealerValue += 11;
            }
            else if (card == 'A' && (dealerValue + 11) > 21)
            {
                dealerValue += 1;
            }
        }
        return dealerValue;
    }
    else
    {
        int playerValue = 0;
        for (char card : player)
        {
            if (card >= '2' && card <= '9')
            {
                playerValue += card - '0';
            }
            else if (card == 'T' || card == 'J' || card == 'Q' || card == 'K')
            {
                playerValue += 10;
            }
            else if (card == 'A' && (playerValue + 11) <= 21)
            {
                playerValue += 11;
            }
            else if (card == 'A' && (playerValue + 11) > 21)
            {
                playerValue += 1;
            }
        }
        return playerValue;
    }
}

int main()
{
    srand(time(0));

    dealer.push_back(cards[rand() % 13]);
    dealer.push_back('X');
    player.push_back(cards[rand() % 13]);
    player.push_back(cards[rand() % 13]);

    char key = ' ';
    bool finish = false;
    bool removed = false;
    while (1)
    {
        system("cls");
        int dealer_result = checkValue(0);
        int player_result = checkValue(1);
        std::cout << "Dealer:";
        for (char card : dealer)
        {
            std::cout << " [" << card << "]";
        }
        std::cout << " Score: " << dealer_result;
        std::cout << "\n\nPlayer:";
        for (char card : player)
        {
            std::cout << " [" << card << "]";
        }
        std::cout << " Score: " << player_result;
        if (finish == true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        if (player_result > 21)
        {
            std::cout << "\n\nYou lost!";
            return 0;
        }
        else if (finish == false)
        {
            std::cout << "\n\nH - hit   S - Stand   E - exit";
            key = _getch();
            switch (key)
            {
            case 'h':
                player.push_back(cards[rand() % 13]);
                break;
            case 's':
                finish = true;
                break;
            case 'e':
                return 0;
            default:
                continue;
            }
        }
        else
        {
            if (removed == false)
            {
                dealer.pop_back();
                removed = true;
            }
            if (dealer_result <= 16)
            {
                dealer.push_back(cards[rand() % 13]);
            }
            else if (dealer_result > 16)
            {
                if (dealer_result < player_result || dealer_result > 21)
                {
                    std::cout << "\n\nYou won!";
                    return 0;
                }
                else
                {
                    std::cout << "\n\nYou lost!";
                    return 0;
                }
            }
        }
    }
}