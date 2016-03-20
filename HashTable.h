//Caroline Jones

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

#define HASHSIZE 412801

using namespace std;

//define a node class
class Node{
public:
    string val;
    Node* next;
    Node(){
    	next = 0;
    }
    Node(string initval){
    	val = initval;
		next = 0;
    }
};

class HashTable{
public:
	HashTable(string filename);
	void SpellCheck(string word);
	~HashTable();
private:
	unsigned long hashFunction(string str);
	bool findWord(string word);
	Node* table[HASHSIZE] = {0};
};

#endif