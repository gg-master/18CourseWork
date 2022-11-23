#pragma once

//! Максимальная длина строки в вводимом тексте программы
const int MAX_LINE_LENGTH = 80;


struct Text {
	//! Массив указателей на каждую строку в тексте.
	char **ptrOnLines;

	//! Количество строк в тексте.
	int countLines;
};
 
/*! Найти определение искомой функции в тексте программы.
	\param[in] programText текст, в котором идет поиск тела функции.
	\param[in] targetFuncName название искомой функции.
	\param[out] funcDefinition указатель на структуру, в которой отобразится определение искомой функции.
	\return 1 - успешное завершение поиска. 0 - неуспешное.
*/
bool findFunctionDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH+1], Text*  funcDefinition);
