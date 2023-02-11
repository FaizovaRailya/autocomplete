// main_.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Trie.h"

int main() {
	setlocale(LC_ALL, "Russian");

	TrieNode* root = getNewNode(); // создаем корень дерева словаря

	//добавляем слова в словарь
	insert(root, "call");
	insert(root, "cat");
	insert(root, "calculator");
	insert(root, "cult");
	insert(root, "run");
	insert(root, "ruler");
	insert(root, "rut");
	insert(root, "bear");
	insert(root, "blue");
	insert(root, "black");
	insert(root, "bed");

	Menu(root);

	return 0;
}