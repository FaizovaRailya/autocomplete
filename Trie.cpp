#include <iostream>
#include "Trie.h"

// ��������� ����� ���� � ������� ������
TrieNode* getNewNode() {
    TrieNode* pNode = new TrieNode;             // �������� ������ �� ����� ����
    pNode->isEndOfWord = false;                 // ������������� ���� ����� ����� � false  
    for (size_t i = 0; i < ALPHABET_SIZE; i++)  // �������������� ����� ������� ���������
        pNode->children[i] = nullptr;
    return pNode;
}

// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
void insert(TrieNode* root, std::string key) {
    TrieNode* node = root;
    for (size_t i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';   // ��������� ������ � �������� ����� �������� ������������ ������ �����

        // ���� ��������� �������, �.�. ����� � ����� ��������� ��� ������� ����� ����
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }
    node->isEndOfWord = true;       // �������� ��������� ����� ��� ����, �.�. ����� �����
}

// ���������� true ���� ���� ���� � ������, ����� false 
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

// ���������� true ���� root ����� ����, ����� false
bool isEmpty(TrieNode* root) {
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// ����������� ������� �������� ����� �� ������ 
TrieNode* remove(TrieNode* root, std::string key, int depth) {
    if (!root)                              // ���� ������ ������ 
        return nullptr;
    if (depth == key.size()) {              // ���� ����� �� ����� ����� 
        if (root->isEndOfWord)              // ���� ���� ������ �� ����� ����� 
            root->isEndOfWord = false;
        if (isEmpty(root)) {                // ���� ���� �� �������� ���������, ������� ���
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

// ����� ��������� ���� �� �����
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

//����� ���� �� ������� �� �����
void find_words(TrieNode* root, std::string key) {
    if (key == "") {
        std::cout << "�� �� ����� ���� ��� ������!\n" << std::endl;
        return;
    }
    TrieNode* node = root;
    int y = 0;
    for (size_t i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (node->children[index] == nullptr) {
            std::cout << "� ������� ��� ����� � ������ " << key << " !" << std::endl;
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
        std::cout << "-----������� �������� ��������:----- \n1 - ����� �����\n2 - �������� ����� � �������\n3 - ������� ����� �� �������\n0 - �����\n";
        int command = 0;
        std::cin >> command;

        std::string d;
        switch (command) {
        case 1:									//����� ����� � ������� �� �����
            std::cout << "������� ����� �����: ";
            getline(std::cin, d, '\n');
            getline(std::cin, key, '\n');
            find_words(root, key);
            break;
        case 2:									//���������� ����� � �������
            std::cout << "������� �����: ";
            getline(std::cin, d, '\n');
            getline(std::cin, d, '\n');
            if (!search(root, d))
            insert(root, d);
            else
                std::cout << "C���� " << d << " ���� � �������!" << std::endl;
            std::cout << std::endl;
            break;
        case 3:                                 //�������� ����� �� �������
            std::cout << "������� �����: ";
            getline(std::cin, d, '\n');
            getline(std::cin, d, '\n');
            if (search(root, d))
                remove(root, d);
            else
                std::cout << "C���� " << d << " ��� � �������!" << std::endl;
            std::cout << std::endl;
            break;
        case 0:
            t = false;
            break;

        default:
            std::cout << "�������� ����!!!" << std::endl;
            break;
        }
    }
    std::cout << "\n------------�� ��������!------------" << std::endl;
}