#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>


class Playerbase {
protected:
    char symbol;
public:
    Playerbase(char s) : symbol(s) {}

    virtual std::pair<int,int> Turn() = 0;
    virtual ~Playerbase() = default;

    char getsymbol() const {
        return symbol;
    }

};


    class MyPlayer : public Playerbase {
    public:
        MyPlayer(char s) : Playerbase(s) {}  

            std::pair<int,int> Turn() override {
                    std::pair<int,int> turn;
                    std::cout << "Player " << symbol << ": Wo setzen? (row and column 0-2): ";
                    std::cin >> turn.first >> turn.second;
                    return turn;
        }
    };


    class KIPlayer : public Playerbase {
    public:
        KIPlayer(char s) : Playerbase(s) {}

            std::pair<int,int> Turn() override {
                    std::pair<int,int> turn;
                    turn.first = std::rand() % 3;
                    turn.second = std::rand() % 3;

                    return turn;
            }

    };


void welcomeScreen() {

    std::cout << "\n _ _ _ _ _ _ " << std::endl;
    std::cout << "|           |" << std::endl;
    std::cout << "| TicTacToe |";
    std::cout << "\n|_ _ _ _ _ _|" << std::endl;
    std::cout << std::endl;
}

    class Game {
    private:
        char table[3][3];
        Playerbase& player1;
        Playerbase& player2;
        int turncount;
    public:
        Game(Playerbase& p1, Playerbase& p2) : player1(p1), player2(p2),turncount(0) {
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j)
                        table[i][j] = ' ';
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
                    else if (table[row][col] == player1.getsymbol()){
                        std::cout << player1.getsymbol() << " ";
                    }
                    else if (table[row][col] == player2.getsymbol()) {
                        std::cout << player2.getsymbol() << " ";
                    }
                }
                std::cout << "\n";
            }
        }

        std::pair <int,int> checkIf(Playerbase& player, char table[3][3]){   
            std::pair<int, int> move;
            while (true) {
                move = player.Turn();
                if (move.first < 0 || move.first > 2 || move.second < 0 || move.second > 2) {
                    continue;
                }

                if (table[move.first][move.second] != ' ') {
                    continue;
                }
                turncount++;
                break;
            }
            return move;
        }

        void run() {
            welcomeScreen();
            printTable();


            while (true) {
                auto move1 = checkIf(player1,table);

                table[move1.first][move1.second] = player1.getsymbol();
                printTable();

                if (isWin(player1.getsymbol())) {
                    std::cout << "Player " << player1.getsymbol() << " wins!\n";
                    break;
                }

                if (turncount == 9){
                    std::cout << "unentschieden!" << std::endl;
                    break;
                }
                std::cout << std::endl;
                auto move2 = checkIf(player2,table);


                table[move2.first][move2.second] = player2.getsymbol();
                std::cout << "\nKI setzt Zug: \n";
                printTable();

                if (isWin(player2.getsymbol())){
                    std::cout << "KI: " << " wins!\n";
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
    MyPlayer player1('X');
    KIPlayer player2('O');
    Game game(player1,player2);

    std::srand(std::time(nullptr));
    game.run();


    return 0;
}
