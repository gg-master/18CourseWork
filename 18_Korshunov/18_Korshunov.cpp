#include <iostream>
#include "../18_Korshunov/18_Korshunov.h"
#include <cstring>

#pragma warning(disable : 4996)

char* stripLeft(char* string, const char stripBy[])
{
	if (string == NULL || strlen(string) == 0) return string;
	return string + strspn(string, stripBy);
}

char* stripRight(char* string, const char stripBy[])
{
	if (string == NULL || strlen(string) == 0) return string;
	int i = strlen(string);
	while (i-- > 0 && (strchr(stripBy, *(string + i)) != NULL))
		*(string + i) = '\0';
	return string;
}

char* strip(char* string, const char stripBy[])
{
	return stripLeft(stripRight(string, stripBy), stripBy);
}

char* delOneLineComment(char* string)
{
	if (string == NULL || strlen(string) == 0) return string;
	char* result = strstr(string, "//");
	if (result != NULL) *result = '\0';
	return string;
}

bool isWordInLine(const char* line, const char* word)
{
	return strstr(line, word) != NULL;
}

bool startsWith(const char* string, const char* startsWithStr)
{
	return strncmp(startsWithStr, string, strlen(startsWithStr)) == 0;
}

bool endsWith(const char* string, const char* endsWithStr)
{
	return strncmp(endsWithStr, string + (strlen(string) - strlen(endsWithStr)), strlen(endsWithStr)) == 0;
}

bool checkStrAfterKeyWord(const char* string, const char* keyWord, const char* startsWithStr, const char* endsWithStr)
{
	if (string == NULL || strlen(string) == 0) return false;

	char tmpStr[MAX_LINE_LENGTH + 1] = ""; strcpy(tmpStr, string);
	char* ptrOnKeyWord = strstr(tmpStr, keyWord);
	// Если ключевого слова нет в строке
	if (ptrOnKeyWord == NULL) return false;

	char* strAfterKeyWord = strip(ptrOnKeyWord + strlen(keyWord));
	return startsWith(strAfterKeyWord, startsWithStr) && endsWith(strAfterKeyWord, endsWithStr);
}

bool isLineHeadOfDefinition(const char* string, const char* funcName)
{
	if (string == NULL) return false;

	// Сохраняем копию строки в отдельный массив
	char clearedStr[MAX_LINE_LENGTH + 1] = ""; strcpy(clearedStr, string);
	char* ptrClearedStr = strip(delOneLineComment(clearedStr)); // Очищаем копию строки от белых символов в начале и в конце

	// Создаем копию названия искомой функции с начальным пробелом
	char fName[MAX_LINE_LENGTH + 1] = " "; strcat(fName, funcName);

	// Проверяем, что название искомой фукнции имеется в строке
	bool isFuncNameInStr = isWordInLine(clearedStr, fName);
	if (!isFuncNameInStr) return false;

	// Проверяем, что строка не начинается с имени функции
	bool isStrStartsWithFuncName = !startsWith(ptrClearedStr, funcName);

	// Проверяем, что строка оканчивается закрывающей скобкой
	bool isStrEndsWithClosingBracket = endsWith(ptrClearedStr, ")");

	// Проверяем, что подстрка после имени функции начинается открывающей скобкой и заканчивается закрывающей скобкой
	bool isStrStartedWOpeningBrAndEndsWClosingBr = checkStrAfterKeyWord(clearedStr, funcName, "(", ")");

	return isFuncNameInStr && isStrStartsWithFuncName &&
		   isStrEndsWithClosingBracket && isStrStartedWOpeningBrAndEndsWClosingBr;
}

int findHeadOfDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH + 1])
{
	// Для каждой строки текста, пока не найдена искомая функция
	for (int i = 0; i < programText.countLines; i++)
	{
		// Вернуть идекс строки, если она является заголовком определения
		if (isLineHeadOfDefinition(programText.ptrOnLines[i], targetFuncName)) return i;
	}
	return -1;
}

bool findBodyOfDefinition(const Text programText, const int headOfDefinitionIndex, Text* funcBody)
{
	if (headOfDefinitionIndex < 0) return false;

	funcBody->countLines = 0;
	bool isFound = false;

	int pairBrCount = 0, firstBrIndex = -1, endBrIndex = -1;

	char tmpStr[MAX_LINE_LENGTH + 1] = "";
	char* ptrTmpStr = tmpStr;

	// Начиная со строки с заголовком определения
	for (int i = headOfDefinitionIndex; i < programText.countLines && !isFound; i++)
	{
		strcpy(tmpStr, programText.ptrOnLines[i]);
		ptrTmpStr = strip(delOneLineComment(tmpStr));

		if (startsWith(ptrTmpStr, "{") && endsWith(ptrTmpStr, "{"))
		{
			pairBrCount++;
			if (firstBrIndex == -1) firstBrIndex = i;
		}
		else if (startsWith(ptrTmpStr, "}") && endsWith(ptrTmpStr, "}"))
		{
			pairBrCount--;
			endBrIndex = i;
			if (pairBrCount == 0) isFound = true;
		}
		if (firstBrIndex != -1)
		{
			funcBody->ptrOnLines[funcBody->countLines++] = programText.ptrOnLines[i];
		}
	}
	return isFound;
}

bool findFunctionDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH + 1], Text* funcDefinition)
{
	funcDefinition->countLines = 0; // Обнулить выходной параметр с определением искомой функии
	
	// Найти индекс строки с заголовком искомой фунцкии
	int headOfDefinitionIndex = findHeadOfDefinition(programText, targetFuncName);
	
	// Если не нашли заголовок искомой функции вернуть неуспешное значение
	if (headOfDefinitionIndex == -1) return false;

	// Записать строку с заголовком функции в возвращаемую структуру с определением функции
	funcDefinition->ptrOnLines[0] = programText.ptrOnLines[headOfDefinitionIndex];
	funcDefinition->countLines++; // Увеличить счетчик строк с определением функции на единицу

	Text funcBody = {}; // Считать параметр с телом искомой функции пустым

	// Найти тело искомой функции 
	bool isFound = findBodyOfDefinition(programText, headOfDefinitionIndex, &funcBody);
	// Если не нашли тело искомой функции вернуть неуспешное значение
	if (!isFound) return false;
	
	// Увеличить счетчик строк с определением на количество строк в теле искомой фукнции
	funcDefinition->countLines += funcBody.countLines;
	// Записать строки с телом функции с параметр с определнием функции
	for (int i = 0; i < funcBody.countLines; i++)
		funcDefinition->ptrOnLines[i + 1] = funcBody.ptrOnLines[i];

	return true;
}

int main()
{
	char inputText[][MAX_LINE_LENGTH+1] =
	{
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
	};
	char targetFuncName[81] = "someFunction";

	Text programText = { {}, 16 };
	for (int i = 0; i < programText.countLines; i++)
		programText.ptrOnLines[i] = (char*)inputText[i];

	Text funcDefinition = {};

	bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);
	
	if (!resOfSearch)
	{
		printf("no function define");
		return 0;
	}
	char tmp[MAX_LINE_LENGTH + 1] = ""; char* ptrTmp = tmp;
	for (int i = 2; i < funcDefinition.countLines - 1; i++)
	{
		strcpy(tmp, funcDefinition.ptrOnLines[i]);
		ptrTmp = strip(tmp);
		if (strlen(ptrTmp) == 0)
		{
			printf("no solution");
			return 0;
		}
	}
	if (funcDefinition.countLines == 3)
	{
		printf("no solution");
		return 0;
	}
	for (int i = 1; i < funcDefinition.countLines; i++)
	{
		printf("%s\n", funcDefinition.ptrOnLines[i]);
	}
	return 0;
}
