#include <iostream>
#include <utility>

class Player1 {
private:
    char symbol = 'X';
public:
    static std::pair<int,int> player1Turn() {
        std::pair<int,int> turn;
        std::cout << "Player X: wo das Kreuz (row and column 0-2): ";
        std::cin >> turn.first >> turn.second;
        return turn;
    }

    [[nodiscard]] char getSymbol() const {
        return symbol;
    }


    bool isWin(char table[3][3]) const{
            for (int i = 0; i < 3; ++i) {
                if (table[i][0] == symbol && table[i][1] == symbol && table[i][2] == symbol) return true;
                if (table[0][i] == symbol && table[1][i] == symbol && table[2][i] == symbol) return true;
            }
            if (table[0][0] == symbol && table[1][1] == symbol && table[2][2] == symbol) return true;
            if (table[0][2] == symbol && table[1][1] == symbol && table[2][0] == symbol) return true;

            return false;
        }


};

class Player2 {
private:
    char symbol = '0';
public:
    static std::pair<int,int> player2Turn() {
        std::pair<int,int> turn;
        std::cout << "Player 0: wo das Kreuz (row and column 0-2): ";
        std::cin >> turn.first >> turn.second;
        return turn;
    }
    [[nodiscard]] char getSymbol() const{
        return symbol;
    }

    bool isWin(char table[3][3]) const {
        for (int i = 0; i < 3; ++i) {
            if (table[i][0] == symbol && table[i][1] == symbol && table[i][2] == symbol) return true;
            if (table[0][i] == symbol && table[1][i] == symbol && table[2][i] == symbol) return true;
        }
        if (table[0][0] == symbol && table[1][1] == symbol && table[2][2] == symbol) return true;
        if (table[0][2] == symbol && table[1][1] == symbol && table[2][0] == symbol) return true;

        return false;
    }

};


void printTable(char table[3][3], Player1& p1, Player2& p2) {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (table[i][j] == ' '){
                std::cout << '.';
            }
            else if (table[i][j] == p1.getSymbol()){
                std::cout << p1.getSymbol();
            }
            else if (table[i][j] == p2.getSymbol()) {
                std::cout << p2.getSymbol();
            }
        }
        std::cout << "\n";
    }
}


int main() {
    Player1 p1;
    Player2 p2;
    char table[3][3];
    int turncount = 0;

    // Initialize table
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            table[i][j] = ' ';

    printTable(table,p1,p2);


    while (true) {

        std::pair<int, int> MyTurn = Player1::player1Turn();

        if (MyTurn.first < 0 || MyTurn.first > 2 || MyTurn.second < 0 || MyTurn.second > 2) {
            std::cout << "Invalid position. Try again.\n";
            continue;
        }

        if (table[MyTurn.first][MyTurn.second] != ' ') {
            std::cout << "Cell already taken. Try again.\n";
            continue;
        }
        turncount++;
        table[MyTurn.first][MyTurn.second] = p1.getSymbol();
        printTable(table, p1, p2);

        if (turncount == 9){
            std::cout << "unentschieden!" << std::endl;
            return 1;
        }

        if (p1.isWin(table)) {
            std::cout << "Player " << p1.getSymbol() << " wins!\n";
            break;
        }

        std::pair<int, int> PlayerTurn = Player2::player2Turn();

        if (PlayerTurn.first < 0 || PlayerTurn.first > 2 || PlayerTurn.second < 0 || PlayerTurn.second > 2) {
            std::cout << "Invalid position. Try again.\n";
            continue;
        }

        if (table[PlayerTurn.first][PlayerTurn.second] != ' ') {
            std::cout << "Cell already taken. Try again.\n";
            continue;
        }
        turncount++;
        table[PlayerTurn.first][PlayerTurn.second] = p2.getSymbol();
        printTable(table, p1, p2);

        if (turncount == 9){
            std::cout << "unentschieden!" << std::endl;
            return 1;
        }

            if (p2.isWin(table)){
                std::cout << "Player " << p2.getSymbol() << " wins!\n";
                break;
            }

    }
    return 0;
}
