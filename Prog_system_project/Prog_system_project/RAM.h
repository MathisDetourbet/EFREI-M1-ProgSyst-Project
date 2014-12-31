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
    
    void displayZoneWith(int, int, bool);
    int getIndexBestSpace(std::map<int, int>, int);
    int getIndexWorstSpace(std::map<int, int>, int);
    
public:
    RAM();
    RAM(int);
    void displayRAM();
    bool allocFirstFit(int);
    bool allocBestFit(int);
    bool allocWorstFit(int);
    bool dealloc(int, int);
};

#endif /* defined(__Prog_system_project__RAM__) */
