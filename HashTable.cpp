//Caroline Jones

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

#include "HashTable.h"

using namespace std;

//load factor = .75
#define HASHSIZE 412801

//define the HashTable

//constructor
HashTable::HashTable(string filename){
	//open the file
	ifstream dictfile;
	dictfile.open(filename.c_str());
	//check if file was opened correctly
	if (!dictfile.is_open()){
		cout << "Could not open file" << endl;
		return;
	}

	//variable to store current word
	string newword;
	//store the file into the hashtable
	while(getline(dictfile, newword)){
		//new node to store within the table
		Node* newnode = new Node();
		newnode->val = newword;

		//determine index into the table
		unsigned long index = hashFunction(newword);

		//store the word into the hashtable at the beginning of the chain
		newnode->next = table[index];
		table[index] = newnode;
	}

	//close the file
	dictfile.close();
}

//destructor
HashTable::~HashTable(){
	for (int i = 0; i < HASHSIZE; i++){
		delete table[i];
	}
}

//spellchecking function
void HashTable::SpellCheck(string word){
	//check if the word is in the dictionary
	if (findWord(word)){
		cout << word << endl;
		return;
	}
	//because the word is not in the dictionary, we must provide suggestions
	vector<string> suggestions;
	string temp = word;
	string alphabet = "abcdefghijklmnopqrstuvwxyz-";
	//check to see if words with a Levenshtein distance of one are in the dictionary. these are the suggestions.
	for (int i = 0, n = word.size(); i < n + 1; i++){
		//first check for a deletion 
		temp.erase(i, 1);
		if (findWord(temp)){
			suggestions.push_back(temp);
		}
		temp = word;
		//now check for a missing letter or for a wrong letter
		for (int j = 0, m = alphabet.size(); j < m; j++){
			temp.insert(i, 1, alphabet[j]);
			if(findWord(temp)){
				suggestions.push_back(temp);
			}
			temp = word;
			temp[i] = alphabet[j];
			if(findWord(temp)){
				suggestions.push_back(temp);
			}
			//check for incorrect case
			temp[i] = toupper(alphabet[j]);
			if (findWord(temp)){
				suggestions.push_back(temp);
			}
			temp = word;
		}
	}
	//if empty, return
	if (suggestions.empty()){
		cout << "no matches found!" << endl;
		return;
	}
	//put the suggestions into alphabetical order
	sort(suggestions.begin(), suggestions.end());
	//delete duplicates
	suggestions.erase(unique(suggestions.begin(), suggestions.end()), suggestions.end());
	//print the suggestions
	for (int i = 0, n = suggestions.size(); i < n; i++){
		cout << suggestions[i] << endl;
	}

}

//function to determine if a word is in the hashtable
bool HashTable::findWord(string word){
	//first determine the hash of the word
	unsigned long index = hashFunction(word);
	//use linear search to find element in linked list
	Node* curr = table[index];
	while (curr != 0){
		if (curr->val == word){
			return true;
		}
		else{
			curr = curr->next;
		}
	}
	return false;
}

//hashfunction, used to construct the hashtable
//using djb2
unsigned long HashTable::hashFunction(string str){
    unsigned long hash = 5381;
    for (int i = 0, n = str.size(); i < n; i++){
        hash = ((hash << 5) + hash) + str[i]; 
    }
    hash = hash % (HASHSIZE - 1);
    return hash;
}
