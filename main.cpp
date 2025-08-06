#include <iostream>
#include <utility>

class Player {
private:
    char symbol;
public:
    Player(char s) : symbol(s) {};

    std::pair<int,int> Turn() {
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


std::pair <int,int> checkIf(Player& player, char table[3][3]){
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
        break;
    }
    return move;
}

bool isWin(char table[3][3], char symbol)  {
    for (int i = 0; i < 3; ++i) {
        if (table[i][0] == symbol && table[i][1] == symbol && table[i][2] == symbol) return true;
        if (table[0][i] == symbol && table[1][i] == symbol && table[2][i] == symbol) return true;
    }
    if (table[0][0] == symbol && table[1][1] == symbol && table[2][2] == symbol) return true;
    if (table[0][2] == symbol && table[1][1] == symbol && table[2][0] == symbol) return true;

    return false;
}


void printTable(char table[3][3], Player& p1, Player& p2) {
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
    for (int i = 0; i < 3; i++){
        std::cout << i << " | ";
        for (int j = 0; j < 3; j++){
            if (table[i][j] == ' '){
                std::cout << '.' << " ";
            }
            else if (table[i][j] == p1.getSymbol()){
                std::cout << p1.getSymbol() << " ";
            }
            else if (table[i][j] == p2.getSymbol()) {
                std::cout << p2.getSymbol() << " ";
            }
        }
        std::cout << "\n";
    }
}


int main() {
    Player player1('X');
    Player player2('0');
    char table[3][3];
    int turncount = 0;

    // Initialize table
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            table[i][j] = ' ';

    welcomeScreen();
    printTable(table,player1,player2);


    while (true) {

        auto move1 = checkIf(player1,table);

        turncount++;
        table[move1.first][move1.second] = player1.getSymbol();
        printTable(table, player1, player2);

        if (isWin(table, player1.getSymbol())) {
            std::cout << "Player " << player1.getSymbol() << " wins!\n";
            break;
        }
        if (turncount == 9){
            std::cout << "unentschieden!" << std::endl;
            return 1;
        }

        auto move2 = checkIf(player2,table);

        turncount++;
        table[move2.first][move2.second] = player2.getSymbol();
        printTable(table, player1, player2);

        if (isWin(table,player2.getSymbol())){
            std::cout << "Player " << player2.getSymbol() << " wins!\n";
            break;
        }

        if (turncount == 9){
            std::cout << "\nunentschieden!" << std::endl;
            return 1;
        }

    }
    return 0;
}