//
//  MemoryZone.cpp
//  Prog_system_project
//
//  Created by Mathis Detourbet on 29/12/2014.
//  Copyright (c) 2014 Efrei. All rights reserved.
//

#include "MemoryZone.h"

MemoryZone::MemoryZone() {
    this->_space = 0;
    this->_addr = NULL;
    this->_state = 0;
}

MemoryZone::MemoryZone(int space, int addr, int state) {
    this->_space = space;
    this->_addr = addr;
    this->_state = state;
}