#include <iostream>
#include "../18_Korshunov/18_Korshunov.h"
#include <cstring>

#pragma warning(disable : 4996)


/*! Удалить перечисленные символы слева от строки
*/
char* stripLeft(char* string, const char stripBy[]="\\t\\n\\v\\f\\r ")
{
	return string + strspn(string, stripBy) - 1;
}

/*! Удалить перечисленные символы справа от строки
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
*/
char* strip(char* string, const char stripBy[]="\\t\\n\\v\\f\\r ")
{
	return stripLeft(stripRight(string, stripBy), stripBy);
}

/* Удалить однострочный комментарий из строки
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

bool isLineHeadOfDefinition(const char* string, const char* funcName)
{
	char tmp[MAX_LINE_LENGTH + 1] = ""; 
	strcpy(tmp, string);
	char* tmp_cleared = strip(delOneLineComment(tmp));
	//if (isCompareLineWithPattern(tmp_cleared, )
	char* ptrOnFuncNameInStr = strstr(tmp_cleared, funcName);
	if (*(tmp_cleared + strlen(tmp_cleared) -1) == ')' && *(ptrOnFuncNameInStr + strlen(funcName)) == '(' && tmp_cleared != ptrOnFuncNameInStr)
	{
		// логика определения 
		return true;
	}
	return false;
}

int findHeadOfDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH + 1])
{
	// Для каждой строки текста, пока не найдена искомая функция
	for (int i = 0; i < programText.countLines; i++)
	{
		//
		if (isWordInLine(programText.ptrOnLines[i], targetFuncName) && 
			isLineHeadOfDefinition(programText.ptrOnLines[i], targetFuncName))
		{
			return i;
		}
	}
}

bool isLineEndOfDefinition(const char line[])
{
	return strstr(line, "}") != NULL;
}

bool findFunctionDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH + 1], Text* funcDefinition)
{
	bool isFound = false; // Считать, что искомая функция не найдена
	funcDefinition->countLines = 0; // Обнулить выходной параметр с определением искомой функии
	// Для каждой строки текста, пока не найдена искомая функция
	for (int i = 0; i < programText.countLines && !isFound; i++)
	{
		// Если отсутсвуют строки в выходном параметре с определением искомой функции
		if (funcDefinition->countLines == 0)
		{
			//isWordInLine(programText.ptrOnLines[i], targetFuncName)
			if (isLineHeadOfDefinition((char*)programText.ptrOnLines[i], targetFuncName))
			{
				funcDefinition->ptrOnLines[i] = programText.ptrOnLines[i];
				funcDefinition->countLines++;
			}
		}
		else
		{
			funcDefinition->ptrOnLines[i] = programText.ptrOnLines[i];
			funcDefinition->countLines++;
			// Если строка содержит конец определения функции
			if (isLineEndOfDefinition((char*)programText.ptrOnLines[i]))
			{
				isFound = true;
			}
		}
	}
	return isFound;
}


int main()
{
	char s[] = "void name((), , ()=)";
	//bool p = isCompareLineWithPattern(s, "name(,)#");
	bool p = isLineHeadOfDefinition(s, "name");
	printf("%d\n", p);
	/*char inputText[][MAX_LINE_LENGTH+1] =
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
	}*/
}
