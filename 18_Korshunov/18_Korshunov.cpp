#include <iostream>
#include "../18_Korshunov/18_Korshunov.h"
#include <cstring>



int main()
{
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

bool isWordInLine(const char *line, const char *word)
{
	return strstr(line, word) != NULL;
}

bool isLineHeadOfDefinition(const char line[], const char word[])
{
	if (isWordInLine(line, word))
	{
		// ������ ����������� 
		return true;
	}
	return false;
}

bool isLineEndOfDefinition(const char line[])
{	
	return strstr(line, "}") != NULL;
}

//char* strip(char* string)
//{
//
//}

bool findFunctionDefinition(const Text programText, const char targetFuncName[MAX_LINE_LENGTH + 1], Text* funcDefinition)
{
	bool isFound = false; // �������, ��� ������� ������� �� �������
	funcDefinition->countLines = 0; // �������� �������� �������� � ������������ ������� ������
	// ��� ������ ������ ������, ���� �� ������� ������� �������
	for (int i = 0; i < programText.countLines && !isFound; i++)
	{
		// ���� ���������� ������ � �������� ��������� � ������������ ������� �������
		if(funcDefinition->countLines == 0)
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
			// ���� ������ �������� ����� ����������� �������
			if (isLineEndOfDefinition((char*)programText.ptrOnLines[i]))
			{
				isFound = true;
			}
		}
	}
	return isFound;
}
