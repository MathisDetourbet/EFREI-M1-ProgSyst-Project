//
//  main.cpp
//  Prog_system_project
//
//  Created by Mathis Detourbet on 26/12/2014.
//  Copyright (c) 2014 Efrei. All rights reserved.
//

#include <iostream>
#include "RAM.h"



using namespace std;

static string choiceMemoryTotaleSize;
static string choiceMainMenu;
static string choiceAlgo;

bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int displayMainMenu(string &choice) {
    do {
        cout<< "Que souhaitez-vous faire ?"<< endl<< endl;
        cout<< "1- Allocation d'une zone mémoire"<< endl;
        cout<< "2- Libération d'une zone mémoire"<< endl;
        cout<< "3- Visualisation de l'occupation en mémoire"<< endl;
        cout<< "4- Quitter le programme"<< endl;
        cin>> choice;
    } while (!is_number(choice) && (atoi(choice.c_str()) < 1 || atoi(choice.c_str()) > 4));
    
    return atoi(choice.c_str());
}

int main(int argc, const char * argv[]) {
    
    cout<< "**** Programmation Systeme : Gestion de mémoire ****"<< endl<< endl<< endl;
    
    do {
        cout<< "Quelle taille mémoire souhaitez-vous ? (nombre en Mo)"<< endl;
        cin>> choiceMemoryTotaleSize;
    } while ((!is_number(choiceMemoryTotaleSize)));
    
    // Création taille mémoire
    RAM *memory = new RAM(atoi(choiceMemoryTotaleSize.c_str()));
    memory->displayRAM();
    
    int space = 0;
    int addr = NULL;
    
    do {
        // Affichage du menu principal
        switch (displayMainMenu(choiceMainMenu)) {
            case 1: // Allocation d'une zone mémoire
                do {
                    cout<< "Veuillez choisir un algorithme parmi les suivants : "<< endl;
                    cout<< "1- FIRST FIT"<< endl;
                    cout<< "2- BEST-FIT"<< endl;
                    cout<< "3- WORST-FIT"<< endl;
                    cin>> choiceAlgo;
                } while (!is_number(choiceAlgo) && (atoi(choiceAlgo.c_str()) < 1 || atoi(choiceAlgo.c_str()) > 3));
                
                do {
                    cout<< "Combien d'espace mémoire souhaitez-vous allouer ?"<< endl;
                    cin>> space;
                } while (space == 0);
                
                switch (atoi(choiceAlgo.c_str())) {
                    case 1:
                        // FIRST-FIT
                        if(memory->allocFirstFit(space)) {
                            cout<< space<< " Mo viennent d'être alloués à l'adresse : "<< endl;
                            memory->displayRAM();
                        } else
                            cout<< "Erreur d'allocation mémoire"<< endl;
                        break;
                        
                    case 2:
                        // BEST-FIT
                        if(memory->allocBestFit(space)) {
                            cout<< space<< " Mo viennent d'être alloués à l'adresse : "<< endl;
                            memory->displayRAM();
                        } else
                            cout<< "Erreur d'allocation mémoire"<< endl;
                        break;
                        
                    default:
                        // WORST-FIT
                        if(memory->allocWorstFit(space)) {
                            cout<< space<< " Mo viennent d'être alloués à l'adresse : "<< endl;
                            memory->displayRAM();
                        } else
                            cout<< "Erreur d'allocation mémoire"<< endl;
                        break;
                }
                break;
                
            case 2: // Libération d'une zone mémoire
                while (space) {
                    cout<< "Combien d'espace mémoire souhaitez-vous libérer ?"<< endl;
                    cin>> space;
                    cout<< "A quelle adresse en mémoire ?"<< endl;
                    cin>> addr;
                }
                break;
                
            case 3: // Visualisation de la mémoire
                memory->displayRAM();
                break;
                
            case 4:
                return 0;
                break;
        }
    } while (atoi(choiceMainMenu.c_str()) != 4);
    
    
    return 0;
}