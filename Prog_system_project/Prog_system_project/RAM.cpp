//
//  RAM.cpp
//  Prog_system_project
//
//  Created by Mathis Detourbet on 26/12/2014.
//  Copyright (c) 2014 Efrei. All rights reserved.
//

#include "RAM.h"

//using namespace std;

RAM::RAM() {
    // Constructeur par défaut
    this->_memoire = new MemorySpace();
    
}

RAM::RAM(int space) {
    // Constructeur avec spécification de la mémoire
    this->_memoire = new MemorySpace(space);
}

void RAM::displayRAM() {
    // Affichage de la RAM dans la console à l'instant t
}

void RAM::alloc(int space) {
    // Allocation de mémoire
}

void RAM::dealloc(int space) {
    // Libération de mémoire
}