//
// Created by divergent / Doğukan ÖKSÜZ (365304) on 07.03.2019.
// root@dogukanoksuz.com.tr
//

#include "../include/Program.h"

Program::Program()
{
    words = nullptr;
}

Program::~Program()
{
    delete words;
}

void Program::fetchWords()
{
    fp->open("files/wordlist");
    std::string word;
    char *cstr;
    while (getline(*fp, word)) {
        cstr = &word[0];
        words->insert(words, cstr);
    }


}