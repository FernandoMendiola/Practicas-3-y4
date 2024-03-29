//
// Created by Victor Navarro on 15/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H

#pragma once
#include "../Character/Character.h"
#include "../Player/Player.h"
#include <vector>
class Player;

class Enemy: public Character{
private:
    int experience;
public:
    Enemy(string _name, int _health, int _attack, int _defense, int _speed, int _experience);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* selectTarget(vector<Player*> possibleTargets);

    int getExperience();

    void defend();
};


#endif //RPG_ENEMY_H
