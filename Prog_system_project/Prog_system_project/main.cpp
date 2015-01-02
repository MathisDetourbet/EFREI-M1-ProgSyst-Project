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
        cout<< "4- Commencer à partir d'une mémoire préconfigurée"<< endl;
        cout<< "5- Quitter le programme"<< endl;
        cin>> choice;
    } while (!is_number(choice) && (atoi(choice.c_str()) < 1 || atoi(choice.c_str()) > 4));
    
    return atoi(choice.c_str());
}

// *** MAIN ***

int main(int argc, const char * argv[]) {
    
    cout<< "**** Programmation Systeme : Gestion de mémoire ****"<< endl<< endl<< endl;
    
    do {
        cout<< "Quelle taille mémoire souhaitez-vous ? (nombre en Mo)"<< endl;
        cin>> choiceMemoryTotaleSize;
    } while ((!is_number(choiceMemoryTotaleSize)));
    
    // Création taille mémoire
    RAM *memory = new RAM(atoi(choiceMemoryTotaleSize.c_str()));
    memory->displayRAM();
    
    string space = " ";
    string addr = " ";
    
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
                } while (!is_number(space) && (atoi(space.c_str()) <= 0));
                
                switch (atoi(choiceAlgo.c_str())) {
                    case 1:
                        // FIRST-FIT
                        if(memory->allocFirstFit(atoi(space.c_str()))) {
                            cout<< space<< " Mo viennent d'être alloués à l'adresse : "<< endl;
                            memory->displayRAM();
                        } else
                            cout<< "### Erreur d'allocation mémoire : espace libre insuffisant ###"<< endl<< endl;
                        break;
                        
                    case 2:
                        // BEST-FIT
                        if(memory->allocBestFit(atoi(space.c_str()))) {
                            cout<< space<< " Mo viennent d'être alloués à l'adresse : "<< endl;
                            memory->displayRAM();
                        } else
                            cout<< "### Erreur d'allocation mémoire : espace libre insuffisant ###"<< endl;
                        break;
                        
                    default:
                        // WORST-FIT
                        if(memory->allocWorstFit(atoi(space.c_str()))) {
                            cout<< space<< " Mo viennent d'être alloués à l'adresse : "<< endl;
                            memory->displayRAM();
                        } else
                            cout<< "### Erreur d'allocation mémoire : espace libre insuffisant ###"<< endl;
                        break;
                }
                break;
                
            case 2: // Libération d'une zone mémoire
                do {
                    cout<< "Combien d'espace mémoire souhaitez-vous libérer ? (valeur > 0)"<< endl;
                    cin>> space;
                    cout<< "A quelle adresse en mémoire ? (valeur >= 0)"<< endl;
                    cin>> addr;
                } while (!is_number(space) && (atoi(space.c_str()) <= 0) && !is_number(addr));
                if(memory->dealloc(atoi(space.c_str()), atoi(addr.c_str())))
                    cout<< space<< " Mo viennent d'être libéré à l'adresse "<< addr<< endl;
                else
                    cout<< "### Erreur de libération mémoire. L'adresse peut être erronée ou la taille trop élevée ###"<< endl;
                break;
                
            case 3: // Visualisation de la mémoire
                memory->displayRAM();
                break;
                
            case 4: // Exemple de mémoire configurée
                memory = new RAM(1000);
                memory->allocFirstFit(250);
                memory->allocFirstFit(400);
                memory->allocFirstFit(100);
                // il reste 250 Mo de libre
                memory->dealloc(300, 650);
                memory->displayRAM();
                break;
                
            case 5: // Quitter le programme
                return 0;
                break;
        }
    } while (atoi(choiceMainMenu.c_str()) != 5);
    
    
    return 0;
}