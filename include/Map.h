//
// Created by divergent / Doğukan ÖKSÜZ (365304) on 07.03.2019.
// root@dogukanoksuz.com.tr
//

#ifndef KELIME_BULMACA_MAP_H
#define KELIME_BULMACA_MAP_H

#include <iostream>
#include <unordered_map>

class Map
{
public:
    Map();

    Map *getNewMapNode();
    void insert(Map *&head, char *str);
    bool haveChildren(Map const *curr);
    bool deletion(Map *&curr, char *str);
    bool search(Map *head, char *str);

private:
    bool isLeaf;
    std::unordered_map<char, Map *> map;
};


#endif //KELIME_BULMACA_MAP_H
