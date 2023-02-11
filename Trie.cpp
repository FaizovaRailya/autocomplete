#include <iostream>
#include "Trie.h"

// Возвращет новый узел с пустыми детьми
TrieNode* getNewNode() {
    TrieNode* pNode = new TrieNode;             // выделяем память по новый узел
    pNode->isEndOfWord = false;                 // устанавливаем флаг конца слова в false  
    for (size_t i = 0; i < ALPHABET_SIZE; i++)  // инициализируем детей нулевым уазателем
        pNode->children[i] = nullptr;
    return pNode;
}

// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void insert(TrieNode* root, std::string key) {
    TrieNode* node = root;
    for (size_t i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';   // вычисляем индекс в алфавите через смещение отнситьельно первой буквы

        // если указатель пустрой, т.е. детей с таким префиксом нет создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }
    node->isEndOfWord = true;       // помечаем последний узлел как лист, т.е. конец слова
}

// Возврашает true если ключ есть в дереве, иначе false 
bool  search(TrieNode* root, std::string key) {
    TrieNode* node = root;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;
        node = node->children[index];
    }
    return (node != nullptr && node->isEndOfWord);
}

// Возвращает true если root имеет лист, иначе false
bool isEmpty(TrieNode* root) {
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева 
TrieNode* remove(TrieNode* root, std::string key, int depth) {
    if (!root)                              // Если дерево пустое 
        return nullptr;
    if (depth == key.size()) {              // Если дошли до конца ключа 
        if (root->isEndOfWord)              // Этот узел больше не конец слова 
            root->isEndOfWord = false;
        if (isEmpty(root)) {                // Если ключ не евляется префиксом, удаляем его
            delete (root);
            root = nullptr;
        }
        return root;
    }
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    return root;
}

// вывод окончания слов по ключу
void findEnd(TrieNode* root, char buf[], int ind, std::string& res, std::string key) {
    TrieNode* node = root;
    ind++;
    if (node->isEndOfWord == true && isEmpty(node)) {
        std::cout << key;
        for (size_t i = 0; i < ind; i++) {

            std::cout << buf[i];
        }
        std::cout << std::endl;
    }
    if (node->isEndOfWord == true && !isEmpty(node)) {
        {
            std::cout << key;
            for (size_t i = 0; i < ind; i++) {
                std::cout << buf[i];
            }
            std::cout << std::endl;
        }
        for (size_t i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {
                buf[ind] = 'a' + i;
                findEnd(node->children[i], buf, ind, res, key);
                continue;
            }
        }
    }
    if (node->isEndOfWord == false) {
        for (size_t i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {
                buf[ind] = 'a' + i;
                findEnd(node->children[i], buf, ind, res, key);
                continue;
            }
        }
    }
}

//вывод слов из словаря по ключу
void find_words(TrieNode* root, std::string key) {
    if (key == "") {
        std::cout << "Вы не ввели ключ для поиска!\n" << std::endl;
        return;
    }
    TrieNode* node = root;
    int y = 0;
    for (size_t i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (node->children[index] == nullptr) {
            std::cout << "В словаре нет слова с ключом " << key << " !" << std::endl;
            break;
        }
        if (node->children[index]) {
            node = node->children[index];
            y++;
        }
    }
    if (y == key.length()) {
        char buf[10];
        int ind = -1;
        std::string res;
        findEnd(node, buf, ind, res, key);
    }
    std::cout << std::endl;
}

void Menu(TrieNode* root) {
    bool t = true;
    while (t) {
        std::string key;
        int e = 0;
        std::cout << "-----Введите желаемую операцию:----- \n1 - поиск слова\n2 - добавить слово в словарь\n3 - удалить слово из словаря\n0 - выход\n";
        int command = 0;
        std::cin >> command;

        std::string d;
        switch (command) {
        case 1:									//поиск слова в словаре по ключу
            std::cout << "Введите часть слова: ";
            getline(std::cin, d, '\n');
            getline(std::cin, key, '\n');
            find_words(root, key);
            break;
        case 2:									//Добавление слова в словарь
            std::cout << "Введите слово: ";
            getline(std::cin, d, '\n');
            getline(std::cin, d, '\n');
            if (!search(root, d))
            insert(root, d);
            else
                std::cout << "Cлово " << d << " есть в словаре!" << std::endl;
            std::cout << std::endl;
            break;
        case 3:                                 //удаление слова из словаря
            std::cout << "Введите слово: ";
            getline(std::cin, d, '\n');
            getline(std::cin, d, '\n');
            if (search(root, d))
                remove(root, d);
            else
                std::cout << "Cлово " << d << " нет в словаре!" << std::endl;
            std::cout << std::endl;
            break;
        case 0:
            t = false;
            break;

        default:
            std::cout << "Неверный ВВОД!!!" << std::endl;
            break;
        }
    }
    std::cout << "\n------------До свидания!------------" << std::endl;
}