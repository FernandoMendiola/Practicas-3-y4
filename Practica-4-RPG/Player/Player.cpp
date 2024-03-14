//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
    originalDefense = _defense; // Inicializar la defensa original
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;
    health -= trueDamage;
    cout << name << " took " << trueDamage << " damage!" << endl;
}

void Player::defend() {
    defense += defense * 0.2;
    cout << "The player " << name << " defended himself, new defense: " << defense << endl;
}

void Player::restoreDefense() {
    defense = originalDefense;
}

void Player::levelUp() {
    level++;
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100 - experience;
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

void Player::selectAction(Character* target) {
    cout << "It's your turn, " << name << ". What will you do?" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Defend" << endl;

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        doAttack(target);
    } else if (choice == 2) {
        defend();
    } else {
        cout << "Invalid option. Performing attack by default." << endl;
        doAttack(target);
    }
}