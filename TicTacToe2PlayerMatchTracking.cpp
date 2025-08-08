#include <iostream>
#include <utility>

class Player {
private:
    char symbol;
    int roundwin;
public:
    Player(char s) : symbol(s), roundwin(0) {};

    std::pair<int,int> Turn() const {
        std::pair<int,int> turn;
        std::cout << "Player " << symbol << ": Wo setzen? (row and column 0-2): ";
        std::cin >> turn.first >> turn.second;
        return turn;
    }

    char getSymbol() const {
        return symbol;
    }

    int getRoundWin() const {
        return roundwin;
    }

    void SetRoundWinUp() {
        roundwin++;
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
public:
    Game(Player& p1, Player &p2) : player1(p1), player2(p2) {
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

    void clear_vec(){
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                table[i][j] = ' ';
            }
        }
    }

    void currentstate(int f,int g) {
        std::cout << "\nEs steht: " << f << " : " << g << "\n" << std::endl;
    }

    void run(){
        int rounds = 1;
            welcomeScreen();
        do {
            std::cout << "\n" <<  rounds << ": Runde:" << std::endl;
            int turncount = 0;
            printTable();

            while (true) {
                auto move1 = checkIf(player1);
                turncount++;

                table[move1.first][move1.second] = player1.getSymbol();
                printTable();

                if (isWin(player1.getSymbol())) {
                    std::cout << "Player " << player1.getSymbol() << " wins round " << rounds<< "!\n";
                    player1.SetRoundWinUp();
                    rounds++;
                    break;
                }
                if (turncount == 9) {
                    std::cout << "unentschieden!" << std::endl;
                    rounds++;
                    break;
                }

                auto move2 = checkIf(player2);
                turncount++;


                table[move2.first][move2.second] = player2.getSymbol();
                printTable();

                if (isWin(player2.getSymbol())) {
                    std::cout << "Player " << player2.getSymbol() << " wins round " << rounds << "\n";
                    rounds++;
                    player2.SetRoundWinUp();
                    break;
                }

                if (turncount == 9) {
                    std::cout << "\nunentschieden!" << std::endl;
                    rounds++;
                    break;
                }
            }
            currentstate(player1.getRoundWin(),player2.getRoundWin());
            // Leeren des Arrays mit verschachtelten Schleifen
            clear_vec();


        } while (rounds != 4);

        if (player1.getRoundWin() > player2.getRoundWin()) {
            std::cout << player1.getSymbol() << " wins the match!" << std::endl;
        }
        else if (player1.getRoundWin() == player2.getRoundWin()) {
            std::cout << "Das Match geht unentschieden aus!" << std::endl;
        }
        else {
            std::cout << player2.getSymbol() << " wins the match!" << std::endl;
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
