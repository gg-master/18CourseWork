#include <iostream>
#include "../18_Korshunov/18_Korshunov.h"
#include <cstring>

#pragma warning(disable : 4996)


/*! Удалить перечисленные символы слева от строки
	\param[in, out] string строка из которой удаляют крайние левые символы
	\param[in] stripBy спсок удаляемых символов слева от строки
	\return указатель на обновленную строку.
*/
char* stripLeft(char* string, const char stripBy[]="\\t\\n\\v\\f\\r ")
{
	return string + strspn(string, stripBy) - 1;
}

/*! Удалить перечисленные символы справа от строки
	\param[in, out] string строка из которой удаляют крайние правые символы
	\param[in] stripBy спсок удаляемых символов справа от строки
	\return указатель на обновленную строку.
*/
char* stripRight(char* string, const char stripBy[]="\\t\\n\\v\\f\\r ")
{
	int i = 0;
	while (*(string + i) != '\0') i++;
	if (i > 0)
		while (i-- > 0 && (strchr(stripBy, (*(string + i))) != NULL))
			*(string + i) = '\0';
	return string;
}

/* Удалить перечисленные символы и слева и справа
	\param[in] string строка из которой удаляют крайние правые и левые символы
	\param[in] stripBy спсок удаляемых символов справа от строки
	\return указатель на обновленную строку.
*/
char* strip(char* string, const char stripBy[]="\\t\\n\\v\\f\\r ")
{
	return stripLeft(stripRight(string, stripBy), stripBy);
}

/* Удалить однострочный комментарий из строки
	\param[in, out] string строка, из которой удаляется однострочный комментарий
	\return указатель на обновленную строку.
*/
char* delOneLineComment(char* string)
{
	char* result = strstr(string, "//");
	if (result != NULL) *result = '\0';
	return string;
}


bool isWordInLine(const char* line, const char* word)
{
	return strstr(line, word) != NULL;
}

//bool isCompareLineWithPattern(const char* string, const char* pattern)
//{
//	char tmp_s[MAX_LINE_LENGTH+1] = "", tmp_p[MAX_LINE_LENGTH + 1] = "";
//	char* ptr_s = strcpy(tmp_s, string);
//	char* ptr_p = strcpy(tmp_p, pattern);
//	
//	char prev_p = NULL;
//	while (ptr_s != NULL && *ptr_p != '\0')
//	{
//		if (*ptr_p == '#')
//		{
//			if (prev_p == NULL && (*tmp_s != *(ptr_p + 1))) return false;
//			if (prev_p != NULL && *(ptr_s - 1) != prev_p && *ptr_s != *(ptr_p + 1)) return false;
//			ptr_p++;
//		}
//		ptr_s = strchr(ptr_s, *ptr_p); 
//		if (ptr_s != NULL) ptr_s++;
//		prev_p = *ptr_p; ptr_p++;
//		
//	}
//	return (ptr_s == NULL) ? false : true;
//}
/* Определить, является ли строка заголовком в определении функции.
	\param[in] string анализируемая строка
	\param[in] funcName имя искомой функции.
	\return указатель на обновленную строку.
*/
bool isLineHeadOfDefinition(const char* string, const char* funcName)
{
	char clearedStr[MAX_LINE_LENGTH + 1] = ""; strcpy(clearedStr, string);
	char fName[MAX_LINE_LENGTH + 1] = " "; strcat(fName, funcName); 

	char* tmp_cleared = strip(delOneLineComment(clearedStr));

	char* ptrOnFuncNameInStr = strstr(tmp_cleared, fName);
	if (ptrOnFuncNameInStr++ == NULL) return false;

	char tmp_s[MAX_LINE_LENGTH + 1] = ""; strcpy(tmp_s, ptrOnFuncNameInStr);
	char* ptrOnOpenBr = strchr(tmp_s, '(');
	*ptrOnOpenBr = '\0';
	ptrOnOpenBr = stripRight(tmp_s);
	
	if (*(tmp_cleared + strlen(tmp_cleared) -1) == ')' && strcmp(tmp_s, funcName) == 0 && tmp_cleared != ptrOnFuncNameInStr)
		return true;
	return false;
}

int findHeadOfDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH + 1])
{
	char fName[MAX_LINE_LENGTH + 1] = " "; strcat(fName, targetFuncName);
	// Для каждой строки текста, пока не найдена искомая функция
	for (int i = 0; i < programText.countLines; i++)
	{
		//
		if (isWordInLine(programText.ptrOnLines[i], fName) &&
			isLineHeadOfDefinition(programText.ptrOnLines[i], targetFuncName))
		{
			return i;
		}
	}
}

bool findBodyOfDefinition(const Text programText, const int headOfDefinitionIndex, Text* funcBody)
{
	return true;
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
	// Если не нашли тело искомой функции вернуть неиспешное значение
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
	//char s[] = "name((), , ()=)";
	////bool p = isCompareLineWithPattern(s, "name(,)#");
	//bool p = isLineHeadOfDefinition(s, "name");
	//printf("%d\n", p);
	char inputText[][MAX_LINE_LENGTH+1] =
	{
		"int main(a)",
		"{",
		"}",
	};
	char targetFuncName[81] = "main";

	Text programText = { {}, 3 };
	for (int i = 0; i < programText.countLines; i++)
		programText.ptrOnLines[i] = (char*)inputText[i];

	Text funcDefinition = {};

	bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);
	printf("%d\n", resOfSearch);
	for (int i = 0; i < funcDefinition.countLines; i++)
	{
		printf("%s\n", funcDefinition.ptrOnLines[i]);
	}
}
