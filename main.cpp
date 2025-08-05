#include <iostream>
#include <utility>

class Player {
private:
    char symbol;
public:
    Player(char s) : symbol(s) {};

    std::pair<int,int> Turn() {
        std::pair<int,int> turn;
        std::cout << "Player X: Wo setzen? (row and column 0-2): ";
        std::cin >> turn.first >> turn.second;
        return turn;
    }

    char getSymbol() const {
        return symbol;
    }

};

/*class Player2 {
private:
    char symbol = '0';
public:
    std::pair<int,int> player2Turn() {
        std::pair<int,int> turn;
        std::cout << "Player 0: Wo setzen? (row and column 0-2): ";
        std::cin >> turn.first >> turn.second;
        return turn;
    }
    char getSymbol() const{
        return symbol;
    }

};*/





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
    Player player1('X');
    Player player2('0');
    char table[3][3];
    int turncount = 0;

    // Initialize table
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            table[i][j] = ' ';

    printTable(table,player1,player2);


    while (true) {
        std::pair<int, int> MyTurn = player1.Turn();

        if (MyTurn.first < 0 || MyTurn.first > 2 || MyTurn.second < 0 || MyTurn.second > 2) {
            std::cout << "Invalid position. Try again.\n";
            continue;
        }

        if (table[MyTurn.first][MyTurn.second] != ' ') {
            std::cout << "Cell already taken. Try again.\n";
            continue;
        }
        turncount++;
        table[MyTurn.first][MyTurn.second] = player1.getSymbol();
        printTable(table, player1, player2);

        if (isWin(table, player1.getSymbol())) {
            std::cout << "Player " << player1.getSymbol() << " wins!\n";
            break;
        }
        if (turncount == 9){
            std::cout << "unentschieden!" << std::endl;
            return 1;
        }

        std::pair<int, int> PlayerTurn = player2.Turn();


        if (PlayerTurn.first < 0 || PlayerTurn.first > 2 || PlayerTurn.second < 0 || PlayerTurn.second > 2) {
            std::cout << "Invalid position. Try again.\n";
            continue;
        }

        if (table[PlayerTurn.first][PlayerTurn.second] != ' ') {
            std::cout << "Cell already taken. Try again.\n";
            continue;
        }
        turncount++;
        table[PlayerTurn.first][PlayerTurn.second] = player2.getSymbol();
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
