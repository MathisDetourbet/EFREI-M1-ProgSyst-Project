//
//  MemorySpace.h
//  Prog_system_project
//
//  Created by Mathis Detourbet on 26/12/2014.
//  Copyright (c) 2014 Efrei. All rights reserved.
//

#ifndef __Prog_system_project__MemorySpace__
#define __Prog_system_project__MemorySpace__

#include <stdio.h>

class MemorySpace {
private:
    int _space;  // en giga octet
    MemorySpace *_nextSpace;
    
public:
    MemorySpace();
    MemorySpace(int space);
};

#endif /* defined(__Prog_system_project__MemorySpace__) */
