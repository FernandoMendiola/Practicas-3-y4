//
// Created by Victor Navarro on 19/02/24.
//

#include "Combat.h"
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant : participants) {
        if (participant->getIsPlayer()) {
            partyMembers.push_back((Player *) participant);
        } else {
            enemies.push_back((Enemy *) participant);
        }
    }
}

Combat::Combat(vector<Player*> _partyMembers, vector<Enemy*> _enemies) {
    partyMembers = std::move(_partyMembers);
    enemies = std::move(_enemies);
    participants = vector<Character*>();
    participants.insert(participants.end(), partyMembers.begin(), partyMembers.end());
    participants.insert(participants.end(), enemies.begin(), enemies.end());
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()){
        partyMembers.push_back((Player*) participant);
    } else {
        enemies.push_back((Enemy*) participant);
    }
}

void Combat::combatPrep() {
    // Sort participants by speed
    sort(participants.begin(),participants.end(), compareSpeed);
}

string Combat::toString() {
    string result = "";
    vector<Character*>::iterator it;
    for(it = participants.begin(); it != participants.end(); it++){
        result += (*it)->toString() + "\n";
    }
    cout<<"===================="<<endl;
    return result;
}

Character* Combat::getTarget(Character* attacker) {
    vector<Character*>::iterator it;
    for(it = participants.begin(); it != participants.end(); it++){
        if((*it)->getIsPlayer() != attacker->getIsPlayer()){
            return *it;
        }
    }

    return nullptr;
}
void Combat::doCombat() {
    cout << "Inicio del combate" << endl;
    combatPrep();
    int turn = 1;
    while (participants.size() > 1) {
        cout << "Turno " << turn << endl;
        ++turn;
        auto it = participants.begin();
        while (it != participants.end()) {
            Character* target = nullptr;
            if ((*it)->getIsPlayer()) {
                Player* currentPlayer = static_cast<Player*>(*it);
                int action;
                cout << "Turno de " << currentPlayer->getName() << endl;
                cout << "Selecciona tu acción:\n";
                cout << "1. Atacar\n";
                cout << "2. Defensa\n";
                cin >> action;
                if (action == 1) {
                    target = currentPlayer->selectTarget(enemies);
                    currentPlayer->doAttack(target);
                } else if (action == 2) {
                    currentPlayer->defend();
                    ++it;
                    currentPlayer->restoreDefense();
                    continue;
                } else {
                    cout << "Opción inválida. Se realizará un ataque por defecto.\n";
                    target = currentPlayer->selectTarget(enemies);
                    currentPlayer->doAttack(target);
                }
            } else {
                target = static_cast<Enemy*>(*it)->selectTarget(partyMembers);
                (*it)->doAttack(target);
            }

            if (target->getHealth() <= 0) {
                it = participants.erase(remove(participants.begin(), participants.end(), target), participants.end());
                if (target->getIsPlayer()) {
                    partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), target), partyMembers.end());
                    if (partyMembers.empty()) {
                        cout << "Game Over" << endl;
                        return;
                    }
                } else {
                    cout << "Has derrotado al enemigo " << target->getName() << endl;
                    enemies.erase(remove(enemies.begin(), enemies.end(), target), enemies.end());
                    if (enemies.empty()) {
                        cout << "¡Victoria!" << endl;
                        return;
                    }
                }
            } else {
                ++it; // Avanzar al siguiente participante
            }
        }
    }
}