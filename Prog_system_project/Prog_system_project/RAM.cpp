//
//  RAM.cpp
//  Prog_system_project
//
//  Created by Mathis Detourbet on 26/12/2014.
//  Copyright (c) 2014 Efrei. All rights reserved.
//

#include "RAM.h"
#include <iostream>

using namespace std;

RAM::RAM() {
    // Constructeur par défaut (10Go par défaut)
    this->_memory.push_back(* new MemoryZone(1000, 0, 0));
    this->freeMemory = 1000;
    this->allocMemory = 0;
}

RAM::RAM(int space) {
    // Constructeur avec spécification de la mémoire
    this->_memory.push_back(* new MemoryZone(space, 0, 0));
    this->freeMemory = space;
    this->allocMemory = 0;
}

// ** FIRST-FIT ALGORITHM **
bool RAM::allocFirstFit(int zoneSpace) {
    for (unsigned i = 0; i < this->_memory.size(); i++) {
        
        if ((this->_memory[i]._space >= zoneSpace) && (this->_memory[i]._state == 0)) {
            
            // Si la taille demandée est égale à celle disponible
            if (this->_memory[i]._space == zoneSpace) {
                this->_memory[i]._state = 1;
                return true;
            }
            // Sinon création d'une nouvelle zone mémoire
            MemoryZone *newZone = new MemoryZone(zoneSpace, this->_memory[i]._addr, 1);
            this->_memory[i]._space -= zoneSpace;
            this->_memory[i]._addr += zoneSpace;
            
            // Insertion de la nouvelle zone mémoire
            this->_memory.insert(this->_memory.begin() + i, *newZone);
            
            return true;
        }
    }
    return false;
}

// ** BEST-FIT ALGORITHM **
bool RAM::allocBestFit(int zoneSpace) {
    map <int, int> freeSpaces;
    
    for (unsigned i = 0; i < this->_memory.size(); i++) {
        if (this->_memory[i]._state == 0 && this->_memory[i]._space >= zoneSpace)
            freeSpaces[i] = this->_memory[i]._space;
    }
    int bestIndex = this->getIndexBestSpace(freeSpaces, zoneSpace);
    if (bestIndex >= 0) {
        MemoryZone *newZone = new MemoryZone(zoneSpace, this->_memory[bestIndex]._addr, 1);
        this->_memory[bestIndex]._space -= zoneSpace;
        this->_memory[bestIndex]._addr += zoneSpace;
        
        // Insertion de la nouvelle zone mémoire
        this->_memory.insert(this->_memory.begin() + bestIndex, *newZone);

        return true;
    }
    
    return false;
}

// Retourne l'index de la zone libre qui possède la capacité la plus proche de celle demandée
int RAM::getIndexBestSpace(map<int, int> freeSpaces, int spaceNedded) {
    int bestdX = INT16_MAX;
    int bestIndex = -1;
    
    for (unsigned i = 0; i < freeSpaces.size(); i++) {
        if ((freeSpaces[i] - spaceNedded) < bestdX) {
            bestdX = freeSpaces[i] - spaceNedded;
            bestIndex = i;
        }
    }
    return bestIndex;
}

// ** WORST-FIT ALGORITHM **
bool RAM::allocWorstFit(int zoneSpace) {
    map<int, int> freeSpaces;
    
    for (unsigned i = 0; i < this->_memory.size(); i++) {
        if (this->_memory[i]._state == 0 && this->_memory[i]._space >= zoneSpace)
            freeSpaces[i] = this->_memory[i]._space;
    }
    int worstIndex = this->getIndexWorstSpace(freeSpaces, zoneSpace);
    if (worstIndex >= 0) {
        MemoryZone *newZone = new MemoryZone(zoneSpace, this->_memory[worstIndex]._addr, 1);
        this->_memory[worstIndex]._space -= zoneSpace;
        this->_memory[worstIndex]._addr += zoneSpace;
        
        // Insertion de la nouvelle zone mémoire
        this->_memory.insert(this->_memory.begin() + worstIndex, *newZone);
        
        return true;
    }
    
    return false;
}

int RAM::getIndexWorstSpace(map <int, int> freeSpaces, int spaceNeeded) {
    int worstIndex = -1;
    int spaceMax = 0;
    
    for (unsigned i = 0; i < freeSpaces.size(); i++) {
        if (freeSpaces[i] > spaceMax) {
            worstIndex = i;
            spaceMax = freeSpaces[i];
        }
    }
    return worstIndex;
}


// Libération d'une zone mémoire
bool RAM::dealloc(int zoneSpace, int zoneAddr) {
    
    return false;
}

// Affichage de la RAM dans la console à l'instant t
void RAM::displayRAM() {
    cout<< endl<< endl<< "* Affichage de la mémoire actuelle *"<< endl<< endl;
    cout<< "-----------------------"<< endl;
    
    for (unsigned i = 0; i < this->_memory.size(); i++) {
        cout<< "||-------------------||\t"<< this->_memory[i]._addr<< endl;
        displayZoneWith(this->_memory[i]._space, this->_memory[i]._addr, this->_memory[i]._state);
    }
    cout<< "||-------------------||"<< endl;
    cout<< "-----------------------"<< endl;
}

void RAM::displayZoneWith(int zoneSpace, int zoneAddr, bool zoneState) {
    string state = zoneState ? "Busy" : "Free";
    
    for (unsigned i = 0; i <= (zoneSpace / 100); i++) {
        if (i == ((int)((zoneSpace/100) / 2))) {
            if (zoneSpace >= 1000 && zoneSpace < 10000) {
                cout<< "|| \t"<< state<< " : "<< zoneSpace<< " Mo   ||"<< endl;
            } else if (zoneSpace < 1000 && zoneSpace >= 100) {
                cout<< "|| \t"<< state<< " : "<< zoneSpace<< " Mo    ||"<< endl;
            } else if (zoneSpace < 100 && zoneSpace >= 10) {
                cout<< "|| \t"<< state<< " : "<< zoneSpace<< " Mo     ||"<< endl;
            }
        }
        else
            cout<< "|| \t\t\t\t\t ||"<< endl;
    }
}