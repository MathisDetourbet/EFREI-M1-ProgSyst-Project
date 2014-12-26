//
//  MemorySpace.cpp
//  Prog_system_project
//
//  Created by Mathis Detourbet on 26/12/2014.
//  Copyright (c) 2014 Efrei. All rights reserved.
//

#include "MemorySpace.h"


MemorySpace::MemorySpace() {
    this->_nextSpace = NULL;
    this->_space = 0;
}

MemorySpace::MemorySpace(int space) {
    this->_nextSpace = NULL;
    this->_space = space;
}