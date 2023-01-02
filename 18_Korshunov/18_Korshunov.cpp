#include <iostream>
#include "../18_Korshunov/18_Korshunov.h"
#include <cstring>

#pragma warning(disable : 4996)

char* stripLeft(char* string, const char stripBy[])
{
	// Если пустая строка, то вернуть значение строки из аргумента
	if (string == NULL || strlen(string) == 0) return string;
	// Вернуть указатель на первый символ с начала строки, не входящий в перечисление
	return string + strspn(string, stripBy);
}

char* stripRight(char* string, const char stripBy[])
{
	// Если пустая строка, то вернуть значение строки из аргумента
	if (string == NULL || strlen(string) == 0) return string;

	// Переместить терминальный ноль влево, пока последний смовл строки входит в перечисление
	int i = strlen(string);
	while (i-- > 0 && (strchr(stripBy, *(string + i)) != NULL))
		*(string + i) = '\0';

	// Вернуть указатель на обновленную строку
	return string;
}

char* strip(char* string, const char stripBy[])
{
	return stripLeft(stripRight(string, stripBy), stripBy);
}

char* delOneLineComment(char* string)
{
	// Если пустая строка, то вернуть значение строки из аргумента
	if (string == NULL || strlen(string) == 0) return string;

	// Получить указатель на положение первого символа однострочного комментария в строке
	char* result = strstr(string, "//");

	// Если символ однострочного комментария имеется в строке, то заменить его терминальным нулем.
	if (result != NULL) *result = '\0';

	// Вернуть указатель на обновленную строку
	return string;
}

bool isWordInLine(const char* line, const char* word)
{
	// Вернуть истину или ложь, если слово имеется в строке и наоборот.
	return strstr(line, word) != NULL;
}

bool startsWith(const char* string, const char* startsWithStr)
{
	// Получить N - кол-во символов в подстроке.
	size_t lenOfstartsWithStr = strlen(startsWithStr);
	// Вернуть истину, если все символы подстроки совпали с первыми N символами строки 
	// или ложь, если какой-либо символы подстроки не совпал с первыми N символами строки.
	return strncmp(startsWithStr, string, lenOfstartsWithStr) == 0;
}

bool endsWith(const char* string, const char* endsWithStr)
{
	// Получить N - кол-во символов в подстроке.
	size_t lenOfstartsWithStr = strlen(endsWithStr);
	// Вернуть истину, если все символы подстроки совпали с последними N символами строки 
	// или ложь, если какой-либо символы подстроки не совпал с последними N символами строки.
	return strncmp(endsWithStr, string + (strlen(string) - lenOfstartsWithStr), lenOfstartsWithStr) == 0;
}

int split(const char* string, char subStrings[][MAX_LINE_LENGTH + 1], const char splitBy[])
{
	// Скопировать символы из исходной строки во временуюю строку.
	char copy_str[MAX_LINE_LENGTH + 1] = ""; strcpy(copy_str, string);

	// Выделить первую подстроку из строки
	char* token = strtok(copy_str, splitBy);

	// Считать кол-во подстрок равным нулю
	int count = 0;

	// Пока можно выделить подстроки из строки
	while (token != NULL)
	{
		// Поместить выделенную подстроку в выходной параметр
		strcpy(subStrings[count++], token);

		// Выделить следующую подстроку из строки
		token = strtok(NULL, splitBy); 
	}
	// Вернуть кол-во выделенных подстрок.
	return count;
}

bool checkStrAfterKeyWord(const char* string, const char* keyWord, const char* startsWithStr, const char* endsWithStr)
{
	// Если пустая строка, то вернуть значение строки из аргумента
	if (string == NULL || strlen(string) == 0) return false;

	// Скопировать символы из исходной строки во временуюю строку.
	char tmpStr[MAX_LINE_LENGTH + 1] = ""; strcpy(tmpStr, string);

	// Получить указатель на положение колючевого слова во временной строке
	char* ptrOnKeyWord = strstr(tmpStr, keyWord);

	// Вернуть ложь, если ключевого слова нет в строке
	if (ptrOnKeyWord == NULL) return false;

	// Убрать белые разделители во временной строке после ключевого слова
	char* strAfterKeyWord = strip(ptrOnKeyWord + strlen(keyWord));

	// Вернуть истину, если временная строка после ключевого слова начинается с начальной подстроки и заканчивается конечной подстрокой
	// или вернуть ложь, если временная строка после ключевого слова не начинается с начальной подстроки и не заканчивается конечной построкой.
	return startsWith(strAfterKeyWord, startsWithStr) && endsWith(strAfterKeyWord, endsWithStr);
}

bool isLineHeadOfDefinition(const char* string, const char* funcName)
{
	// Если пустая строка, то вернуть ложь.
	if (string == NULL) return false;

	// Скопировать символы из исходной строки во временуюю строку.
	char clearedStr[MAX_LINE_LENGTH + 1] = ""; strcpy(clearedStr, string);

	// Очистить копию строки от однострочного комментария и белых символов в начале и в конце
	char* ptrClearedStr = strip(delOneLineComment(clearedStr)); 

	// Определить, что в строке имеется отдельное слово, начинающееся с названия функции
	// ..Разделить строку по белым разделителям
	char splitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {}; 
	int sLength = split(clearedStr, splitted);

	// Найти первое слово, начинабщееся с имени функции
	bool isOk = false;
	for (int i = 0; i < sLength && !isOk; i++) isOk = isOk || startsWith(splitted[i], funcName);
	// Вернуть ложь, если слово, начинающееся с имени функции не обнаружено.
	if (!isOk) return false;

	// Проверить, что строка не начинается с имени функции
	bool isStrNotStartsWithFuncName = !startsWith(ptrClearedStr, funcName);

	// Проверить, что строка оканчивается закрывающей скобкой
	bool isStrEndsWithClosingBracket = endsWith(ptrClearedStr, ")");

	// Проверить, что подстрка после имени функции начинается открывающей скобкой и заканчивается закрывающей скобкой
	bool isStrStartedWOpeningBrAndEndsWClosingBr = checkStrAfterKeyWord(clearedStr, funcName, "(", ")");

	// Проверить, что первая открывюащая скобка в строке стоит после имени функции
	// .. если подстрока после имени функции начинается с открывающей скобки и заканчивается закрывающей скобкой
	if (isStrStartedWOpeningBrAndEndsWClosingBr) // TODO занести в трассировку ошибок
	{
		// вернуть ложь, если имеются другие открывающие скобки перед именем функции
		if (strstr(clearedStr, funcName) > strchr(clearedStr, '(')) return false;
	}
	// Вернуть истину, если строка не начинается с имени функции, строка заканчивается закрывающей скобокй и 
	// подстрока после имени функции начинается с открывающей скобки и заканчивается закрывающей 
	// или ложь, если одно из условий не выполнилось.
	return isStrNotStartsWithFuncName && isStrEndsWithClosingBracket && isStrStartedWOpeningBrAndEndsWClosingBr;
}

int findHeadOfDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH + 1])
{
	//return 0; // для тестирования с заглушками
	// Для каждой строки текста, пока не найдена искомая функция
	for (int i = 0; i < programText.countLines; i++)
	{
		// Вернуть идекс строки, если она является заголовком определения
		if (isLineHeadOfDefinition(programText.ptrOnLines[i], targetFuncName)) return i;
	}
	// Вернуть значение не найдено, если заголовок определения не удалось найти
	return -1;
}

bool findBodyOfDefinition(const Text programText, const int headOfDefinitionIndex, Text* funcBody)
{
	/*if (headOfDefinitionIndex == 0) // для тестирования с заглушками
	{
		funcBody->countLines = 4;
		for (int i = headOfDefinitionIndex + 1; i < 5; i++)
		{
			funcBody->ptrOnLines[i-1] = programText.ptrOnLines[i];
		}
		return true;
	}
	return false;*/

	// Вернуть ложь, если заголовок определения не найден.
	if (headOfDefinitionIndex < 0) return false;

	// Обнулить кол-во линиий в выходном параметре с телом функции.
	funcBody->countLines = 0;

	// Считать, что тело не найдено
	bool isFound = false;

	// Обнулить счетчик пар открывающийх и закрывающих скобок
	int pairBrCount = 0;

	// Считать, что первая открывающая скобка и последняя закрывающая скобка не найдена.
	int firstBrIndex = -1, endBrIndex = -1;

	// Определить пустую временную строку
	char tmpStr[MAX_LINE_LENGTH + 1] = "";
	char* ptrTmpStr = tmpStr;

	// Для каждой строки текста, начиная со строки с заголовком определения и пока тело не найдено.
	for (int i = headOfDefinitionIndex; i < programText.countLines && !isFound; i++)
	{
		// Скопировать строку текста во временную переменную.
		strcpy(tmpStr, programText.ptrOnLines[i]);

		// Очистить временнную строку от однострочного комментария и белых разделителей в начале и в конце строки.
		ptrTmpStr = strip(delOneLineComment(tmpStr));

		// Если временная строка и начинается и заканчивается открывающей скобкой.
		if (startsWith(ptrTmpStr, "{") && endsWith(ptrTmpStr, "{"))
		{
			// Увеличить счетчик пар скобок на 1 элемент.
			pairBrCount++;

			// Если первая открывающая скобка не найдена, то установить индекс первой октрывающей скобки равный индексу обрабатываемой строки
			if (firstBrIndex == -1) firstBrIndex = i;
		}
		// Если временная строка и начинается и заканчивается закрывающей скобкой.
		else if (startsWith(ptrTmpStr, "}") && endsWith(ptrTmpStr, "}"))
		{
			// Уменьшить счетчик пар скобок на 1 элемент
			pairBrCount--;
			
			// Если счетчик пар равен нулю, значит нашли последнюю закрывающюю скобку
			if (pairBrCount == 0)
			{
				// Установить индекс последней закрывающей скобки равный индексу обрабатываемой строки
				endBrIndex = i;
				// Считать, что тело искомой функции найденл
				isFound = true;
			}
		}
		// Записать строку в выходной параметр с телом функции, если первая открывающая скобка тела найдена.
		if (firstBrIndex != -1)
		{
			funcBody->ptrOnLines[funcBody->countLines++] = programText.ptrOnLines[i];
		}
	}
	// Вернуть нашли ли функцию.
	return isFound;
}

bool findFunctionDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH + 1], Text* funcDefinition)
{
	// Обнулить выходной параметр с определением искомой функии
	funcDefinition->countLines = 0;
	
	// Найти индекс строки с заголовком искомой фунцкии
	int headOfDefinitionIndex = findHeadOfDefinition(programText, targetFuncName);
	
	// Если не нашли заголовок искомой функции вернуть неуспешное значение
	if (headOfDefinitionIndex == -1) return false;

	// Записать строку с заголовком функции в возвращаемую структуру с определением функции
	funcDefinition->ptrOnLines[0] = programText.ptrOnLines[headOfDefinitionIndex];

	// Увеличить счетчик строк с определением функции на единицу
	funcDefinition->countLines++; 

	// Считать параметр с телом искомой функции пустым
	Text funcBody = {};

	// Найти тело искомой функции 
	bool isFound = findBodyOfDefinition(programText, headOfDefinitionIndex, &funcBody);

	// Если не нашли тело искомой функции вернуть неуспешное значение
	if (!isFound) return false;
	
	// Увеличить счетчик строк с определением на количество строк в теле искомой фукнции
	funcDefinition->countLines += funcBody.countLines;

	// Записать строки с телом функции с параметр с определнием функции
	for (int i = 0; i < funcBody.countLines; i++)
		funcDefinition->ptrOnLines[i + 1] = funcBody.ptrOnLines[i];

	// Вернуть успешное значение поиска.
	return true;
}

int main()
{
	printf("Enter the function name: ");
	char targetFuncName[MAX_LINE_LENGTH + 1] = "";
	gets_s(targetFuncName, MAX_LINE_LENGTH);

	printf("Enter the number of lines of program text: ");

	int countLines = 0;
	scanf("%d", &countLines);

	if (countLines < 1 || countLines > 20) {
		printf("invalid input data");
		return 0;
	}

	printf("Enter the program text:\n");
	char inputText[20][MAX_LINE_LENGTH + 1] = {};
	/*{
		"int someFunction(int arg1, double arg2)",
		"{",
		"    for(int i = 0; i < 10; i++)",
		"    {",
		"        if (arg1 > i)",
		"        {",
		"            while(i < arg1)",
		"            {",
		"                i++;",
		"            }",
		"         }",
		"    }",
		"}",
		"int main()",
		"{",
		"}",
	};*/
	char emptyStr[MAX_LINE_LENGTH + 1];
	gets_s(emptyStr);
	for (int i = 0; i < countLines; i++)
	{
		gets_s(inputText[i]);
	}
	Text programText = { {}, countLines };
	for (int i = 0; i < programText.countLines; i++)
	{
		programText.ptrOnLines[i] = (char*)inputText[i];
	}

	Text funcDefinition = {};

	bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);
	
	if (!resOfSearch)
	{
		printf("no function define");
		return 0;
	}
	char tmp[MAX_LINE_LENGTH + 1] = ""; char* ptrTmp = tmp;
	bool isOk = 0;
	for (int i = 2; i < funcDefinition.countLines - 1; i++)
	{
		strcpy(tmp, funcDefinition.ptrOnLines[i]);
		ptrTmp = strip(tmp);
		isOk = isOk || strlen(ptrTmp) != 0; // TODO добавить в трассировку
	}
	if (!isOk)
	{
		printf("no solution");
		return 0;
	}
	// Выввод тела определния искомой функции без начальной и конечной скобок
	for (int i = 2; i < funcDefinition.countLines - 1; i++)
	{
		printf("%s\n", funcDefinition.ptrOnLines[i]);
	}
	return 0;
}
