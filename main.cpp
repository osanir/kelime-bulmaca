#include <iostream>
#include "include/Program.h"

using namespace std;

int main()
{
    /*
     * Notlar:
     * https://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/
     *
     * Class yapısına çevirmeye çalıştım niye yaptım bilmiyorum olmadı. Bugünlük bu kadar, Trie işimize yarayacak
     * veri yapısı diye düşünüyorum. Bir sen de bak istersen.
     */

    auto * a = new Program();
    a->fetchWords();
}