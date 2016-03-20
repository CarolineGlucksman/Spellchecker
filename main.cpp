#include "HashTable.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc <= 1)
    {
        cout << "Please supply a file name for the dictionary as input" << endl;
        return 1;
    }
    
    HashTable* hashTable = new HashTable(argv[1]);
    
    cout << "Spell checking...\n";
    
    cout << "--spelling--" << endl;
    hashTable->SpellCheck("spelling");
    cout << endl;
    cout << "--spel--" << endl;
    hashTable->SpellCheck("spel");
    cout << endl;
    cout << "--goiing--" << endl;
    hashTable->SpellCheck("goiing");
    cout << endl;
    cout << "--abcdefghijklmnop--" << endl;
    hashTable->SpellCheck("abcdefghijklmnop");

    return 0;
}
