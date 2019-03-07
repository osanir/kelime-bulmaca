//
// Created by divergent / Doğukan ÖKSÜZ (365304) on 07.03.2019.
// root@dogukanoksuz.com.tr
//

#include "../include/Map.h"

Map::Map()
{

}

Map *Map::getNewMapNode()
{
    Map *node = new Map;
    node->isLeaf = false;

    return node;
}

void Map::insert(Map *&head, char *str)
{
    if (head == nullptr)
        head = getNewMapNode();

    Map *curr = head;
    while (*str)
    {
        if (curr->map.find(*str) == curr->map.end())
            curr->map[*str] = getNewMapNode();

        curr = curr->map[*str];
        str++;
    }
    curr->isLeaf = true;
}


bool Map::haveChildren(Map const *curr)
{
    for (auto it : curr->map)
        if (it.second != nullptr)
            return true;

    return false;
}

bool Map::deletion(Map *&curr, char *str)
{
    if (curr == nullptr)
        return false;

    if (*str)
    {
        if (curr != nullptr && curr->map.find(*str) != curr->map.end() &&
            deletion(curr->map[*str], str + 1) && curr->isLeaf == false)
        {
            if (!haveChildren(curr))
            {
                delete curr;;
                curr = nullptr;
                return true;
            } else
            {
                return false;
            }
        }
    }

    if (*str == '\0' && curr->isLeaf)
    {
        if (!haveChildren(curr))
        {
            delete curr;
            curr = nullptr;
            return true;
        } else
        {
            curr->isLeaf = false;
            return false;
        }
    }

    return false;
}

bool Map::search(Map *head, char *str)
{
    if (head == nullptr)
        return false;

    Map *curr = head;
    while (*str)
    {
        curr = curr->map[*str];

        if (curr == nullptr)
            return false;

        str++;
    }
    return curr->isLeaf;
}