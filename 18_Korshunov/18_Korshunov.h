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

/*! Удалить перечисленные символы слева от строки
	\param[in, out] string строка из которой удаляют крайние левые символы
	\param[in] stripBy спсок удаляемых символов слева от строки
	\return указатель на обновленную строку.
*/
char* stripLeft(char* string, const char stripBy[] = " \t\n\v\f\r");

/*! Удалить перечисленные символы справа от строки
	\param[in, out] string строка из которой удаляют крайние правые символы
	\param[in] stripBy спсок удаляемых символов справа от строки
	\return указатель на обновленную строку.
*/
char* stripRight(char* string, const char stripBy[] = " \t\n\v\f\r");

/* Удалить перечисленные символы и слева и справа
	\param[in] string строка из которой удаляют крайние правые и левые символы
	\param[in] stripBy спсок удаляемых символов справа от строки
	\return указатель на обновленную строку.
*/
char* strip(char* string, const char stripBy[] = " \t\n\v\f\r");

/* Удалить однострочный комментарий из строки
	\param[in, out] string строка, из которой удаляется однострочный комментарий
	\return указатель на обновленную строку.
*/
char* delOneLineComment(char* string);


bool isWordInLine(const char* line, const char* word);

/* Определить, является ли строка заголовком в определении функции.
	\param[in] string анализируемая строка
	\param[in] funcName имя искомой функции.
	\return флаг, является ли строка заголовком в определении функции.
*/
bool isLineHeadOfDefinition(const char* string, const char* funcName);

/* Найти заголовок определния искомой функции.
	\param[in] programText анализируемая строка
	\param[in] funcName имя искомой функции.
	\return флаг, является ли строка заголовком в определении функции.
*/
int findHeadOfDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH + 1]);

bool findBodyOfDefinition(const Text programText, const int headOfDefinitionIndex, Text* funcBody);
