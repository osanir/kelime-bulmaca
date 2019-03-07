#ifndef KELIME_BULMACA_WORDMAP_H
#define KELIME_BULMACA_WORDMAP_H

//
// Created by divergent / Doğukan ÖKSÜZ (365304) on 07.03.2019.
// root@dogukanoksuz.com.tr
//

#include <iostream>
#include <unordered_map>

namespace aMap
{
    struct WordMap
    {
        bool isLeaf;
        std::unordered_map<char, WordMap *> map;
    };

    WordMap *getNewWordMapNode()
    {
        WordMap *node = new WordMap;
        node->isLeaf = false;

        return node;
    }

    void insert(WordMap *&head, char *str)
    {
        if (head == nullptr)
            head = getNewWordMapNode();

        WordMap *curr = head;
        while (*str)
        {
            if (curr->map.find(*str) == curr->map.end())
                curr->map[*str] = getNewWordMapNode();

            curr = curr->map[*str];
            str++;
        }
        curr->isLeaf = true;
    }

    bool haveChildren(WordMap const *curr)
    {
        for (auto it : curr->map)
            if (it.second != nullptr)
                return true;

        return false;
    }

    bool deletion(WordMap *&curr, char *str)
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

    bool search(WordMap *head, char *str)
    {
        if (head == nullptr)
            return false;

        WordMap *curr = head;
        while (*str)
        {
            curr = curr->map[*str];

            if (curr == nullptr)
                return false;

            str++;
        }
        return curr->isLeaf;
    }
};

#endif //KELIME_BULMACA_WORDMAP_H
