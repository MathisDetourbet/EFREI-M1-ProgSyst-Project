//
//  RAM.h
//  Prog_system_project
//
//  Created by Mathis Detourbet on 26/12/2014.
//  Copyright (c) 2014 Efrei. All rights reserved.
//

#ifndef __Prog_system_project__RAM__
#define __Prog_system_project__RAM__

#include <stdio.h>
#include <vector>
#include "MemoryZone.h"
#include <map>

class RAM {
private:
    std::vector <MemoryZone> _memory;
    int freeMemory, allocMemory;
    
    void displayZoneWith(int zoneSpace, int zoneAddr, bool blockState);
    int getIndexBestSpace(std::map<int, int> freeSpaces);
    
public:
    RAM();
    RAM(int space);
    void displayRAM();
    bool allocFirstFit(int zoneSpace);
    bool allocBestFit(int zoneSpace);
    bool allocWorstFit(int zoneSpace);
    bool dealloc(int zoneSpace, int zoneAddr);
};

#endif /* defined(__Prog_system_project__RAM__) */
