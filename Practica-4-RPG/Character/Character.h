//
// Created by Victor Navarro on 15/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include <string>
#include <ctime>

using namespace std;

class Character {
protected:
    string name;
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
public:
    Character(string _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;
    virtual void defend();


    bool flee(Character* target);
    string getName();
    int getHealth();
    int getAttack();
    int getDefense();
    bool getIsPlayer();
    int getSpeed();
    string toString();

    int getRolledDefense(int defense) {
        srand(time(nullptr));
        int randomValue = rand() % 100;
        if (randomValue <= 40) {
            int lowerLimit = defense * 0.80;
            return (rand() % (defense - lowerLimit + 1)) + lowerLimit;
        } else {
            return defense;
        }
    }
};


#endif //RPG_CHARACTER_H
