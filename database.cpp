#include "database.h"
/*
    Blacklist içinde bulunan harfler ağaçtan silinmeli.
    Silme konusunda sıkıntılar var:
        Bolca Seg Fault hatası
        Silinen node'ların üst node'larında kelime bulunamaması
*/

Database::Database(){
    wchar_t alphabet2[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 
                            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
                            'r', 's', 't', 'u', 'v', 'y', 'z' };
    /*
    wchar_t alphabet2[] = { 'a', 'b', 'c', 'ç', 'd', 'e', 'f', 'g', 'h', 'ı',
                            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'ö', 'p', 'r',
                            's', 'ş', 't', 'u', 'ü', 'v', 'y', 'z' };
    */

    for(int i=0; i<23; i++){
        alphabet[i] = alphabet2[i];
    }

    root = new Node;

    srand(time(NULL));
}

void Database::start(){
    importDatabase();

    while(1){
        cout << endl << endl << endl;
        string oldPick = randomPick;
        pickRandom(root);
        calculateLetterValues();
        if(randomPick == oldPick) continue;

        cout << randomPick << endl;
        cout << randomPickSorted << endl;
        for(auto val : values)
            cout << val;
        cout << endl << "Score : ";
        int score;
        cin >> score;

        int counter = 0;
        for( auto ch : exactLetters ){
            for(auto c : randomPick){
                if( ch == c )
                    counter++;
            }
        }
        score -= counter;

        setPossibleLetters(score, 0, "");
        setBlacklist();
        setExactLetters();
        
        printAllStr();

        // kesin bulunan harfleri bulduktan sonra ihtiyacımız kalmadı
        possibleLetters.clear();


        simplifyTree(root);
    }
}

void Database::importDatabase(){
    ifstream file;
    file.open("wordlist.txt");
    cout << "İçe aktarılıyor..." << endl;
    string str;
    while( !file.eof() ){
        getline(file, str);
        
        string sorted = str;
        sort(sorted.begin(), sorted.end());
        
        //cout << str << " " << sorted << endl; 
        //cout << sorted << " ekleniyor." << endl; 
        addToTree(str, sorted, root, 0);
    }
    cout << "İçe aktarma tamamlandı!" << endl;
    file.close();
}

void Database::addToTree(string str, string sorted, Node* iter, int letterPos){ 
    //cout << "addToTree çalıştı." << endl;
    if( !(iter->children.empty()) ){
        //cout << "iter->children boş değil" << endl;
        for( auto child : iter->children ){
            if( child->ch == sorted[letterPos] ){
                //cout << "child->ch node'u iter'in çocuklarında var" << endl;
                if( letterPos+1 == sorted.size() ){
                    // TODO: üzerine yazma işlemini kontrol et
                    //cout << "kelime eklendi" << endl;
                    iter->word.push_back(str);
                    return;
                }
                iter = child;
                letterPos++;
                addToTree(str, sorted, iter, letterPos);
                return;
            }
        }
    }
    iter->children.push_back(new Node(sorted[letterPos]));
    //cout << "children.pushback çalıştı: " << sorted[letterPos] << endl;

    iter = iter->children.back();
    if( letterPos+1 == sorted.size() ){
        iter->word.push_back(str);
        //cout << "kelime eklendi: " << iter->word << endl << endl;
        return;
    }
    letterPos++;
    addToTree(str, sorted, iter, letterPos);
    return;
}

// Sözlükten rastgele bir kelime seçer
void Database::pickRandom(Node* iter){
/*     if( !iter->word.empty() ){
        randomPick = iter->word.back();
    }else{
        if( !iter->children.empty() ){
            int i;
            for(i=0; iter->children[i]->inBlackList == true; i++);
            iter = iter->children[i];
            pickRandom(iter);
        }else{
            cout << "Herhangi bir eşleşme bulunamadı!" << endl;
            return;
        }
    } */

    if( !iter->children.empty() ){
        int num;
        int i=0;
        bool cf = false;
        do{
            num = rand() % iter->children.size();
            i++;
            if(iter->children[num]->inBlackList == false)
                break;
            if(i>iter->children.size()*2){
                break;
                cf = true;
            }
        }while(1);
        if(!cf){
            iter = iter->children[num];
           // cout << "Şuan ch: " << iter->ch << " bl: " << iter->inBlackList << endl;
            pickRandom(iter);
        }else{
            if(iter->word.empty() ){
                cout << "Buda boş!" << endl;
            } else{
                    
                int num = rand() % iter->word.size();
                randomPick = iter->word[num];
                return;

            }
        }
    }else{
        int num = rand() % iter->word.size();
        randomPick = iter->word[num];
        return;
    }
}

void Database::calculateLetterValues(){
    randomPickSorted.clear();
    string tempStr = randomPick;
    sort(tempStr.begin(), tempStr.end());
    for( auto ch1 : tempStr ){
        // kelimedeki aynı harflerin eklenmemesi için kontrol
        bool check = true;  
        for( auto ch2 : randomPickSorted ){
            if( ch1 == ch2 )
                check = false;
        }
        // kesin varolan kelimelerin kontrolü
        for( auto ch2 : exactLetters ){
            if( ch1 == ch2)
                check = false;
        }
        // kara listedeki kelimelerin puan kazandırmadığını bildiğimiz için eklemiyoruz
        for( auto ch2 : blackListLetters ){
            if( ch1 == ch2 )
                check = false;
        }

        if( check )
            randomPickSorted.push_back(ch1);
    }
    // Seçilen kelimenin harf ağırlıkları hesaplanır.
    values.resize(randomPickSorted.size());
    int i=0;
    int counter = 0;
    for( auto ch1 : randomPickSorted ){
        for( auto ch2 : tempStr ){
            if( ch1 == ch2 ){
                counter++;
            }
        }
        values[i] = counter;
        counter = 0;
        i++;
    }
}

void Database::simplifyTree(Node *iter){
    if( !iter->children.empty() ){
        for(int i=0; i<iter->children.size(); i++){
            if(iter->children[i]->inBlackList)
                continue;
            for(auto bl : blackListLetters){
                if(iter->children[i]->ch == bl ){
                    iter->children[i]->inBlackList = true;
                }
            }
            simplifyTree(iter->children[i]);
        } 
    }
/*         for(auto node : iter->children){
            if(node->inBlackList)   
                continue;
            for(auto bl : blackListLetters){
                if(node->ch == bl){
                    node->inBlackList = true;
                    cout << node->ch << " elendi" << endl;
                }
            }
            simplifyTree(node);
        }
    }
 */   /*  for(auto node : iter->children){
        for(auto bl : blackListLetters){
            if( node->ch == bl){
                node->inBlackList = true;
            }
        }
        if(!node->children.empty())
            simplifyTree(node);
    } */
}

void Database::setPossibleLetters( int score, int pos = 0, string newStr = "" ){
    for(int i=pos; i<randomPickSorted.size(); i++){
        setPossibleLetters(score, ++pos, newStr);
        if( score - values[i] >= 0 ){
            newStr.push_back(randomPickSorted[i]);
            score -= values[i];
        }
        if( score == 0){
            for(auto str : possibleLetters) if( str == newStr ) return;
            for(auto bl : blackListLetters) if( isContain(newStr, bl)) return;
            possibleLetters.push_back(newStr);
        }
    }
}

void Database::setBlacklist(){
    for( auto c : randomPickSorted){
        //cout << "Karakter: " << c << endl;
        bool found = false;
        for( auto str : possibleLetters){
            //cout << "Karşılaştırma : " << c << " : " << str << " : " << isContain(str, c) <<endl;
            found = isContain(str, c);
            if( found ) break;
        }
        if( found == false ){
            bool isAlreadyAdded = false;
            for(auto bl : blackListLetters)
                if(bl == c )
                    isAlreadyAdded = true;
            if(isAlreadyAdded == false)
                blackListLetters.push_back(c);
        }
    }
}

void Database::setExactLetters(){
    // intersections
    for(auto str1 : possibleLetters){
        for(auto ch : str1){
            bool isFound;
            for(auto str2 : possibleLetters){
                isFound = false;
                for(auto c : str2){
                    if( c == ch ) 
                        isFound = true;
                }
                if(!isFound)
                    break;
            }
            if(isFound){
                bool itContain = false;
                for(auto c : exactLetters)
                    if(ch == c)
                        itContain = true;
                if( itContain == false)
                    exactLetters.push_back(ch);
            }
        }
    }

}

void Database::printAllStr(){
    cout << endl << "Possible Letters: " << endl;
    for(auto str : possibleLetters)
        cout << str << " ";

    cout << endl << "BlackList Letters: " << endl;
    for(auto c : blackListLetters)
        cout << c << " ";
    
    cout << endl << "Exact Letters: " << endl;
    for(auto c : exactLetters)
        cout << c << " ";
}

bool Database::isContain(string str, char ch){
    for( auto c : str ){
        if( ch == c )
            return true;
    }
    return false;
}