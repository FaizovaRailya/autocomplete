#pragma once
#ifndef TRIE_H
#define TRIE_H

#include <string>
#define ALPHABET_SIZE 26

struct TrieNode         // Структура узла дерева 
{
    TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
};

TrieNode* getNewNode();
void insert(TrieNode*, std::string);
bool search(TrieNode*, std::string);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, std::string, int depth = 0);
void findEnd(TrieNode* root, char buf[], int ind, std::string& res, std::string key);
void find_words(TrieNode* root, std::string key);
void Menu(TrieNode* root);


#endif
