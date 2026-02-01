//
// Created by milan on 01.02.26.
//

#include "TicTacToe2Player.h"

int main() {
    Player player1('X');
    Player player2('0');
    Board game(player1,player2);

    game.run();


    return 0;
}

