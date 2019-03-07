//
// Created by divergent / Doğukan ÖKSÜZ (365304) on 07.03.2019.
// root@dogukanoksuz.com.tr
//

#ifndef KELIME_BULMACA_PROGRAM_H
#define KELIME_BULMACA_PROGRAM_H

#include <iostream>
#include <fstream>
#include "Map.h"

using namespace std;

class Program
{
public:
    Program();
    ~Program();

    void fetchWords();

private:
    Map *words;
    std::ifstream *fp;
};


#endif //KELIME_BULMACA_PROGRAM_H
