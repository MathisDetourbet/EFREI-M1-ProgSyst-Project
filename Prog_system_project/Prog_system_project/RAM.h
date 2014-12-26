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
#include "MemorySpace.h"

class RAM {
private:
    MemorySpace *_memoire;
    
public:
    RAM();
    RAM(int space);
    void displayRAM();
    void alloc(int space);
    void dealloc(int space);
};

#endif /* defined(__Prog_system_project__RAM__) */
