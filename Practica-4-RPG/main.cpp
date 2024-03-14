#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"

int main() {
    Player *player = new Player("Victor", 40, 10, 5, 4);
    Enemy *enemy = new Enemy("Goblin", 20, 10, 2, 5, 10);
    Enemy *enemy2 = new Enemy("Orc", 20, 10, 2, 5, 10);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;
    return 0;
}
