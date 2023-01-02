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

/* Определить, имеется ли слово в строке.
	\param[in] line - строка в которой ведется поиск слова.
	\param[in] word - слово, которое ищется в строке.
	\return флаг, имеется ли слово в строке.
*/
bool isWordInLine(const char* line, const char* word);

/* Определить, начинается ли строка с указаной подстроки.
	\param[in] string - анализируемая строка.
	\param[in] startsWithStr - подстрока, с которой должная начинаться строка.
	\return флаг, начинается ли анализируемая строка с подстроки.
*/
bool startsWith(const char* string, const char* startsWithStr);

/* Определить, заканчивается ли строка с указаной подстроки.
	\param[in] string - анализируемая строка.
	\param[in] endsWithStr - подстрока, которой должная заканчиваться строка.
	\return флаг, заканчивается ли анализируемая строка подстрокой.
*/
bool endsWith(const char* string, const char* endsWithStr);

/*
* Разделяет строку на подстроки по указанным разделителям.
* \param [in] string - строка, разбиваемая на подстроки.
* \param [out] subStrings - массив, в который будут скопированы выделенные подстроки.
* \param[in] splitBy спсок символов, выступающих в качетсве разделителей между подстроками.
* \return количество выделенных подстрок из строки.
*/
int split(const char* string, char subStrings[][MAX_LINE_LENGTH + 1], const char splitBy[] = " \t\n\v\f\r");

/* Проверить, начинается ли подстрока после ключевого слова с указанных начальных и конечных подстрок.
	\param[in] string - анализируемая строка с ключевым словом.
	\param[in] keyWord - ключевое слово, после которого будет происходить анализ строки.
	\param[in] startsWithStr - подстрока, с которой должная начинаться строка после ключевого слова. 
	Не учитываются белые разделители.
	\param[in] endsWithStr - подстрока, которой должная заканчиваться строка после ключевого слова.
	Не учитываются белые разделители.
	\return флаг, начинается ли с подстроки и заканчивается ли подстрокой анализируемая строка после ключевого слова.
*/
bool checkStrAfterKeyWord(const char* string, const char* keyWord, const char* startsWithStr, const char* endsWithStr);

/* Определить, является ли строка заголовком в определении функции.
	\param[in] string анализируемая строка
	\param[in] funcName имя искомой функции.
	\return флаг, является ли строка заголовком в определении функции.
*/
bool isLineHeadOfDefinition(const char* string, const char* funcName);

/* Найти заголовок определния искомой функции.
	\param[in] programText текст, в котором ведется поиск заголовка.
	\param[in] targetFuncName имя искомой функции.
	\return индекс строки с заголовком искомой функции. -1 если не найдено.
*/
int findHeadOfDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH + 1]);

/* Найти тело определения искомой функции.
	\param[in] programText анализируемая строка
	\param[in] headOfDefinitionIndex - индекс строки с заголовком определения функции.
	\param[out] funcBody структура, в которой сохранится тело определния искомой функции.
	\return удалось ли найти тело определения функции.
*/
bool findBodyOfDefinition(const Text programText, int headOfDefinitionIndex, Text* funcBody);
