//
//  MemoryZone.h
//  Prog_system_project
//
//  Created by Mathis Detourbet on 29/12/2014.
//  Copyright (c) 2014 Efrei. All rights reserved.
//

#ifndef __Prog_system_project__MemoryZone__
#define __Prog_system_project__MemoryZone__

#include <stdio.h>

class MemoryZone {
public:
    int _space;  // en Méga octet
    int _addr;
    bool _state; // libre = 0, allouée = 1

    MemoryZone();
    MemoryZone(int space, int addr, int state);
};

#endif /* defined(__Prog_system_project__MemoryZone__) */
