#include <iostream>
#include <utility>
#include <cstdlib>  // für rand() und srand()
#include <ctime>    // für time()


class Playerbase {
protected:
    char symbol;
public:
    Playerbase(char s) : symbol(s) {}

    virtual std::pair<int,int> Turn() const = 0;
    virtual ~Playerbase() = default;

    char getSymbol() const {
        return symbol;
    }
};


    class MyPlayer : public Playerbase {
    public:
        MyPlayer(char s) : Playerbase(s) {}  // Konstruktor der Basisklasse wird aufgerufen

            std::pair<int,int> Turn() const override {
                    std::pair<int,int> turn;
                    std::cout << "Player " << symbol << ": Wo setzen? (row and column 0-2): ";
                    std::cin >> turn.first >> turn.second;
                    return turn;
        }
    };


    class KIPlayer : public Playerbase {
    public:
        KIPlayer(char s) : Playerbase(s) {}            // Konstruktor der Basisklasse wird aufgerufen

            std::pair<int,int> Turn() const override {
                    std::pair<int,int> turn;
                    turn.first = std::rand() % 3;
                    turn.second = std::rand() % 3;

                    return turn;
            }

    };

void welcomeScreen(){

    std::cout << "\n _ _ _ _ _ _ " << std::endl;
    std::cout << "|           |" << std::endl;
    std::cout << "| TicTacToe |";
    std::cout << "\n|_ _ _ _ _ _|" << std::endl;
    std::cout << std::endl;


}

std::pair <int,int> checkIfForPlayer(MyPlayer& player, char table[3][3]){   // Funktion eventuell bündeln mit checkIfForKI(Playerbase& player). Durch die Übergabe von Playerbase kann man beide Player verwenden
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


std::pair <int,int> checkIfForKI(KIPlayer& player, char table[3][3]) {
        std::pair<int,int> move;
        while (true) {
        move = player.Turn();
         if (move.first < 0 || move.first > 2 || move.second < 0 || move.second > 2) {
            continue;
        }

        if (table[move.first][move.second] != ' ') {
            continue;
        }
        std::cout << "KI setzt Zug: " << std::endl;
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

void printTable(char table[3][3], Playerbase& p1, Playerbase& p2) {
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
    MyPlayer player1('X');
    KIPlayer player2('O');

    char table[3][3];
    int turncount = 0;
    std::srand(std::time(nullptr)); // Initialisierung mit aktuellem Zeitstempel

    // Initialize table
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            table[i][j] = ' ';
}
}
    welcomeScreen();
    printTable(table,player1,player2);


    while (true) {
        auto move1 = checkIfForPlayer(player1,table);

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
        std::cout << std::endl;
        auto move2 = checkIfForKI(player2,table);

        turncount++;
        table[move2.first][move2.second] = player2.getSymbol();
        printTable(table, player1, player2);

        if (isWin(table,player2.getSymbol())){
             std::cout << "KI: " << " wins!\n";
              break;
            }

        if (turncount == 9){
             std::cout << "\nunentschieden!" << std::endl;
             return 1;
            }
    }
    return 0;
}
