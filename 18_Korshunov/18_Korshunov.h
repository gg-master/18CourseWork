#pragma once

// Максимальная длина строки в вводимом тексте программы
const int MAX_LINE_LENGTH = 80;

// Максимальгное количество строк в тексте
const int MAX_LINES = 20;

struct Text {
	// Массив указателей на каждую строку в тексте.
	char* ptrOnLines[MAX_LINES];

	// Количество строк в тексте.
	int countLines;
};
 
/*! Найти определение искомой функции в тексте программы.
	\param[in] programText текст, в котором идет поиск тела функции.
	\param[in] targetFuncName название искомой функции.
	\param[out] funcDefinition указатель на структуру, в которой отобразится определение искомой функции.
	\return 1 - успешное завершение поиска. 0 - неуспешное.
*/
bool findFunctionDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH+1], Text*  funcDefinition);
