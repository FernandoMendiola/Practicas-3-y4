#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Character/Character.h"
int main() {
    Player *player = new Player("Fer", 100, 8, 4, 10);
    Enemy *enemy = new Enemy("Duende", 50, 5, 2, 5, 10);

    cout << player->toString() << endl;
    cout << enemy->toString() << endl;

    cout << "=====================" << endl;
    int i = 1;
    while(player->getHealth() > 0 && enemy->getHealth() > 0) {
        player->doAttack(enemy);
        enemy->doAttack(player);

        cout << "=====================" << endl;
        cout << "Turno " << i << endl;
        cout << player->toString() << endl;
        cout << enemy->toString() << endl;
        i++;
    }
    if(player->getHealth() <= 0) {
        cout << "El jugador ha sido derrotado. Gracias por jugar." << endl;
    }
    else {
        cout << "El enemigo ha sido derrotado" << endl;
    }

    delete player;
    delete enemy;
    return 0;
}
