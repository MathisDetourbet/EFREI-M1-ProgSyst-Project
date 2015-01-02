//
//  RAM.cpp
//  Prog_system_project
//
//  Created by Mathis Detourbet on 26/12/2014.
//  Copyright (c) 2014 Efrei. All rights reserved.
//

#include "RAM.h"
#include <iostream>
#include <math.h>

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
        if (_memory[i]._state == 0 && _memory[i]._space >= zoneSpace)
            freeSpaces[i] = _memory[i]._space;
    }
    int bestIndex = this->getIndexBestSpace(freeSpaces, zoneSpace);
    if (bestIndex >= 0) {
        // Si la taille demandée est égale à celle disponible
        if (this->_memory[bestIndex]._space == zoneSpace) {
            this->_memory[bestIndex]._state = 1;
            return true;
        }
        
        _memory[bestIndex]._space -= zoneSpace;
        _memory[bestIndex]._addr += zoneSpace;
        
        // Insertion de la nouvelle zone mémoire
        MemoryZone *newZone = new MemoryZone(zoneSpace, _memory[bestIndex]._addr, 1);
        this->_memory.insert(this->_memory.begin() + bestIndex, *newZone);

        return true;
    }
    
    return false;
}

// Retourne l'index de la zone libre qui possède la capacité la plus proche de celle demandée
int RAM::getIndexBestSpace(map <int, int> freeSpaces, int spaceNedded) {
    int bestdX = INT16_MAX;
    int bestIndex = -1;
    
    for (unsigned i = 0; i < freeSpaces.size(); i++) {
        if ((freeSpaces[i] - spaceNedded) < bestdX) {
            bestdX = abs(freeSpaces[i] - spaceNedded);
            bestIndex = i;
        }
    }
    return bestIndex;
}

// ** WORST-FIT ALGORITHM **
bool RAM::allocWorstFit(int zoneSpace) {
    map <int, int> freeSpaces;
    
    for (unsigned i = 0; i < _memory.size(); i++) {
        if (_memory[i]._state == 0 && _memory[i]._space >= zoneSpace)
            freeSpaces[i] = _memory[i]._space;
    }
    int worstIndex = this->getIndexWorstSpace(freeSpaces, zoneSpace);
    if (worstIndex >= 0) {
        // Si la taille demandée est égale à celle disponible
        if (_memory[worstIndex]._space == zoneSpace) {
            _memory[worstIndex]._state = 1;
            return true;
        }
        MemoryZone *newZone = new MemoryZone(zoneSpace, _memory[worstIndex]._addr, 1);
        _memory[worstIndex]._space -= zoneSpace;
        _memory[worstIndex]._addr += zoneSpace;
        
        // Insertion de la nouvelle zone mémoire
        _memory.insert(_memory.begin() + worstIndex, *newZone);
        
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
    int indexZoneAsk = -1;
    
    for (unsigned i = 0; i < _memory.size(); i++) {
        if (_memory[i]._addr == zoneAddr) {
            indexZoneAsk = i;
        }
    }
    if (indexZoneAsk == -1) {
        return false;
    }
    if (_memory[indexZoneAsk]._space < zoneSpace) {
        return false;
    }
    // Libération de la zone mémoire : création d'une zone libre
    MemoryZone *newFreeZone = new MemoryZone(zoneSpace, zoneAddr, 0);
    _memory[indexZoneAsk]._space -= zoneSpace;
    _memory[indexZoneAsk]._addr += zoneSpace;
    
    // Insertion de la nouvelle zone mémoire
    _memory.insert(_memory.begin() + indexZoneAsk, *newFreeZone);
    return true;
}

// Défragmentation de la mémoire
/*void RAM::defrag() {
    
    for (unsigned i = 0; ; <#increment#>) {
        <#statements#>
    }
}*/

// Affichage de la RAM dans la console à l'instant t
void RAM::displayRAM() {
    cout<< endl<< endl<< "* Affichage de la mémoire actuelle *"<< endl<< endl;
    cout<< "-----------------------"<< endl;
    
    for (unsigned i = 0; i < this->_memory.size(); i++) {
        cout<< "||-------------------||\t"<< _memory[i]._addr<< endl;
        displayZoneWith(_memory[i]._space, _memory[i]._addr, _memory[i]._state);
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