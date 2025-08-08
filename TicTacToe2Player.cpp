#include <iostream>

class Player {
private:
    char symbol;
public:
    Player(char s) : symbol(s) {};

    std::pair<int,int> Turn() const {
        std::pair<int,int> turn;
        std::cout << "Player " << symbol << ": Wo setzen? (row and column 0-2): ";
        std::cin >> turn.first >> turn.second;
        return turn;
    }

    char getSymbol() const {
        return symbol;
    }
};


void welcomeScreen(){
    std::cout << "\n _ _ _ _ _ _ " << std::endl;
    std::cout << "|           |" << std::endl;
    std::cout << "| TicTacToe |";
    std::cout << "\n|_ _ _ _ _ _|" << std::endl;
    std::cout << std::endl;

}

class Game {
private:
    char table[3][3];
    Player& player1;
    Player& player2;
    int turncount;
public:
    Game(Player& p1, Player &p2) : player1(p1), player2(p2), turncount(0) {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                table[row][col] = ' ';
            }
        }
    }

    std::pair <int,int> checkIf(Player& player){
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

    bool isWin(char symbol)  {
        for (int row = 0; row < 3; ++row) {
            if (table[row][0] == symbol && table[row][1] == symbol && table[row][2] == symbol) return true;
            if (table[0][row] == symbol && table[1][row] == symbol && table[2][row] == symbol) return true;
        }
        if (table[0][0] == symbol && table[1][1] == symbol && table[2][2] == symbol) return true;
        if (table[0][2] == symbol && table[1][1] == symbol && table[2][0] == symbol) return true;

        return false;
    }

    void printTable() {
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

    void run(){
        welcomeScreen();
        printTable();

        while (true) {
            auto move1 = checkIf(player1);

            table[move1.first][move1.second] = player1.getSymbol();
            printTable();

            if (isWin(player1.getSymbol())) {
                std::cout << "Player " << player1.getSymbol() << " wins!\n";
                break;
            }
            if (turncount == 9){
                std::cout << "unentschieden!" << std::endl;
                break;
            }

            auto move2 = checkIf(player2);


            table[move2.first][move2.second] = player2.getSymbol();
            printTable();

            if (isWin(player2.getSymbol())){
                std::cout << "Player " << player2.getSymbol() << " wins!\n";
                break;
            }

            if (turncount == 9){
                std::cout << "\nunentschieden!" << std::endl;
                break;
            }
        }

    }

};





int main() {
    Player player1('X');
    Player player2('0');
    Game game(player1,player2);

    game.run();


    return 0;
  }
