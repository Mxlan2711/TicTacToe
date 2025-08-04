#include <iostream>
#include <utility>

class Player1 {
private:
    char symbol = 'X';
public:
    static std::pair<int,int> player1Turn() {
        std::pair<int,int> turn;
        std::cout << "wo das Kreuz (row and column 0-2): ";
        std::cin >> turn.first >> turn.second;
        return turn;
    }

    [[nodiscard]] char getSymbol() const{
        return symbol;
    }

};

class Player2 {
private:
    char symbol = '0';
public:
    static std::pair<int,int> player2Turn() {
        std::pair<int,int> turn;
        std::cout << "wo das Kreuz (row and column 0-2): ";
        std::cin >> turn.first >> turn.second;
        return turn;
    }
    [[nodiscard]] char getSymbol() const{
        return symbol;
    }

};


void printTable(char table[3][3], Player1 p1, Player2 p2) {
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

bool isWin(char table[3][3], Player1& p1){
    for (int i = 0; i < 3; ++i) {
        if (table[i][0] == p1.getSymbol() && table[i][1] == p1.getSymbol() && table[i][2] == p1.getSymbol()) return true;
        if (table[0][i] == p1.getSymbol() && table[1][i] == p1.getSymbol() && table[2][i] == p1.getSymbol()) return true;
    }
    if (table[0][0] == p1.getSymbol() && table[1][1] == p1.getSymbol() && table[2][2] == p1.getSymbol()) return true;
    if (table[0][2] == p1.getSymbol() && table[1][1] == p1.getSymbol() && table[2][0] == p1.getSymbol()) return true;

    return false;
}

bool isWin2(char table[3][3], Player2& p2){
    for (int i = 0; i < 3; ++i) {
        if (table[i][0] == p2.getSymbol() && table[i][1] == p2.getSymbol() && table[i][2] == p2.getSymbol()) return true;
        if (table[0][i] == p2.getSymbol() && table[1][i] == p2.getSymbol() && table[2][i] == p2.getSymbol()) return true;
    }
    if (table[0][0] == p2.getSymbol() && table[1][1] == p2.getSymbol() && table[2][2] == p2.getSymbol()) return true;
    if (table[0][2] == p2.getSymbol() && table[1][1] == p2.getSymbol() && table[2][0] == p2.getSymbol()) return true;

    return false;
}

int main() {
    Player1 p1;
    Player2 p2;
    char table[3][3];

    // Initialize table
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            table[i][j] = ' ';

    printTable(table,p1,p2);

    while (true) {
        std::pair<int,int> MyTurn = Player1::player1Turn();

        if (MyTurn.first < 0 || MyTurn.first > 2 || MyTurn.second < 0 || MyTurn.second > 2) {
            std::cout << "Invalid position. Try again.\n";
            continue;
        }

        if (table[MyTurn.first][MyTurn.second]  != ' ') {
            std::cout << "Cell already taken. Try again.\n";
            continue;
        }

        table[MyTurn.first][MyTurn.second] = p1.getSymbol();
        printTable(table,p1,p2);

        std::pair<int, int> PlayerTurn = Player2::player2Turn();

        table[PlayerTurn.first][PlayerTurn.second] = p2.getSymbol();
        printTable(table,p1,p2);

        if (isWin(table, p1)){
            std::cout << "Player with " << p1.getSymbol() << " wins!\n";
            break;
        }
        else if (isWin2(table,p2)){
            std::cout << "Player with " << p2.getSymbol() << " wins!\n";
            break;
        }
    }

    return 0;
}
