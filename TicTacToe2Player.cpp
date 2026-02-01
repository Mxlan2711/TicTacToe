#include <iostream>
#include <utility>
#include <vector>
#include "TicTacToe2Player.h"

Player::Player(char s) : symbol(s) {}

    std::pair<int,int> Player::Turn() const {
        std::pair<int,int> turn;
        std::cout << "Player " << symbol << ": Wo setzen? (row and column 0-2): ";
        std::cin >> turn.first >> turn.second;
        return turn;
    }

    char Player::getSymbol() const {
        return symbol;
    }


void welcomeScreen(){
    std::cout << "\n _ _ _ _ _ _ " << std::endl;
    std::cout << "|           |" << std::endl;
    std::cout << "| TicTacToe |";
    std::cout << "\n|_ _ _ _ _ _|" << std::endl;
    std::cout << std::endl;
}



Board::Board(Player& p1, Player &p2) : player1(p1), player2(p2), turncount(0) {
    for (auto & row : table) {
        for (char & col : row) {
            col = ' ';
        }
    }
}



    std::pair <int,int> Board::makeAMove(const Player& player){
        std::pair<int, int> move;
        while (true) {
            move = player.Turn();
            if (move.first < 0 || move.first > 2 || move.second < 0 || move.second > 2) {
                std::cout << "Invalid position. Try again.\n";
                continue;
            }

            if (table[move.first][move.second] != ' ') {
                std::cout << "Cell already taken. Try again.\n";
                continue;
            }
            turncount++;
            break;
        }
        return move;
    }

    bool Board::isWin(const char symbol) const {
        for (int row = 0; row < 3; ++row) {
            if (table[row][0] == symbol && table[row][1] == symbol && table[row][2] == symbol) return true;
            if (table[0][row] == symbol && table[1][row] == symbol && table[2][row] == symbol) return true;
        }
        if (table[0][0] == symbol && table[1][1] == symbol && table[2][2] == symbol) return true;
        if (table[0][2] == symbol && table[1][1] == symbol && table[2][0] == symbol) return true;

        return false;
    }

    void Board::printTable() const {
        std::cout << "\n    ";
        for (int i = 0; i < 3; ++i) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        std::cout << "   ";
        for (int i = 0; i < 3; ++i) {
            std::cout << " _";
        }
        std::cout << std::endl;
        for (int row = 0; row < 3; row++){
            std::cout << row << " | ";
            for (int col = 0; col < 3; col++){
                if (table[row][col] == ' '){
                    std::cout << '.' << " ";
                }
                else if (table[row][col] == player1.getSymbol()){
                    std::cout << player1.getSymbol() << " ";
                }
                else if (table[row][col] == player2.getSymbol()) {
                    std::cout << player2.getSymbol() << " ";
                }
            }
            std::cout << "\n";
        }
    }

    void Board::run(){
        welcomeScreen();
        printTable();

        const std::vector vec = {player1, player2};

        while (true) {
            for (auto& player : vec) {
                auto move = makeAMove(player);

                table[move.first][move.second] = player.getSymbol();
                printTable();

                if (turncount == 9){
                    std::cout << "unentschieden!" << std::endl;
                    break;
                }

                if (isWin(player.getSymbol())){
                    std::cout << "Player " << player.getSymbol() << " wins!\n";
                    return;
                }
            }
        }
    }