#pragma once

#include <utility>

class Player {
private:
    char symbol;
public:
    Player(char s);

    std::pair<int,int> Turn() const;
    char getSymbol() const;
};

void welcomeScreen();

class Board {
private:
    char table[3][3]{};
    Player& player1;
    Player& player2;
    int turncount;
public:
    Board(Player& p1, Player &p2);
    std::pair <int,int> makeAMove(const Player& player);
    bool isWin(char symbol) const;
    void printTable() const;
    void run();
};