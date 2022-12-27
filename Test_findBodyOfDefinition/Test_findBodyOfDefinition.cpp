#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool compareStructText(Text firstText, Text secondText)
{
	if (firstText.countLines != secondText.countLines) return false;
	for (int i = 0; i < firstText.countLines; i++)
	{
		if (firstText.ptrOnLines[i] != secondText.ptrOnLines[i]) return false;
	}
	return true;
}

void fillText(Text* destination, char source[][MAX_LINE_LENGTH + 1])
{
	for (int i = 0; i < destination->countLines; i++)
		destination->ptrOnLines[i] = (char*)source[i];
}
namespace TestfindBodyOfDefinition
{
	TEST_CLASS(TestfindBodyOfDefinition)
	{
	public:
		
		TEST_METHOD(targetFunctionIsMissing)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int main()",
				"{",
				"	return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";

			Text programText = { {}, 4 }; fillText(&programText, inputText);

			Text funcBody = {};

			Text exp_funcBody = {};
			bool exp_resOfSearch = false;

			bool resOfSearch = findBodyOfDefinition(programText, -1, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
		TEST_METHOD(oneTargetFunctionInText)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int arg1, double arg2)",
				"{",
				"    int c = arg1 + arg2;",
				"    return c",
				"}",
				"int main()",
				"{",
				"	return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";

			Text programText = { {}, 9 }; fillText(&programText, inputText);

			Text funcBody = {};

			Text exp_funcBody = { {}, 4 }; fillText(&exp_funcBody, inputText + 1);
			bool exp_resOfSearch = true;

			bool resOfSearch = findBodyOfDefinition(programText, 0, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
		TEST_METHOD(manySameTargetFunctionInText)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunctionsomeFunctionOne(int arg1, double arg2)",
				"{",
				"	return 0;",
				"}",
				"int someFunction(int arg1, double arg2)",
				"{",
				"	return 0;",
				"}",
				"int someFunction1(int arg1, double arg2)",
				"{",
				"	return 0;",
				"}",
				"int main()",
				"{",
				"	return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 16 }; fillText(&programText, inputText);

			Text funcBody = {};

			Text exp_funcBody = { {}, 3 }; fillText(&exp_funcBody, inputText + 5);
			bool exp_resOfSearch = true;

			bool resOfSearch = findBodyOfDefinition(programText, 4, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
		TEST_METHOD(targetFunctionIsCommented)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"// int someFunction(int arg1, double arg2)",
				"// {",
				"//    int c = arg1 + arg2;",
				"// Комментарий",
				"//    return c;",
				"// }",
				"int main()",
				"{",
				"return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 10 }; fillText(&programText, inputText);

			Text funcBody = {};

			Text exp_funcBody = {};
			bool exp_resOfSearch = false;

			bool resOfSearch = findBodyOfDefinition(programText, -1, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
		TEST_METHOD(targetFunctionPartIsCommented)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int arg1, double arg2)",
				"{",
				"//    int c = arg1 + arg2;",
				"// Комментарий",
				"//    return c;",
				"//}",
				"}",
				"int main()",
				"{",
				"return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 11 }; fillText(&programText, inputText);
			
			Text funcBody = {};

			Text exp_funcBody = { {}, 6 }; fillText(&exp_funcBody, inputText + 1);
			bool exp_resOfSearch = true;

			bool resOfSearch = findBodyOfDefinition(programText, 0, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
		TEST_METHOD(targetFunctionBodyIsEmpty)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int arg1, double arg2)",
				"{",
				"",
				"",
				"",
				"}",
				"int main()",
				"{",
				"return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {} , 10 }; fillText(&programText, inputText);

			Text funcBody = {};

			Text exp_funcBody = { {}, 5 }; fillText(&exp_funcBody, inputText + 1);
			bool exp_resOfSearch = true;

			bool resOfSearch = findBodyOfDefinition(programText, 0, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
		TEST_METHOD(targetFunctionBodyIsNotEmpty)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int arg1, double arg2)",
				"{",
				"    int c = 0;",
				"    doSmth(c);",
				"    return c;",
				"}",
				"int main()",
				"{",
				"return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 10 }; fillText(&programText, inputText);
			
			Text funcBody = {};

			Text exp_funcBody = { {}, 5 }; fillText(&exp_funcBody, inputText + 1);
			bool exp_resOfSearch = true;

			bool resOfSearch = findBodyOfDefinition(programText, 0, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
		TEST_METHOD(emptyLinesInTargetFuncBodyInStartMidEnd)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int arg1, double arg2)",
				"{",
				"",
				"//  doSmth(c);",
				"    int c = 0;",
				"",
				"//  doSmth(c);",
				"",
				"// просто комментарий",
				"",
				"}",
				"int main()",
				"{",
				"return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 15 }; fillText(&programText, inputText);
			
			Text funcBody = {};

			Text exp_funcBody = { {}, 10 }; fillText(&exp_funcBody, inputText + 1);
			bool exp_resOfSearch = true;

			bool resOfSearch = findBodyOfDefinition(programText, 0, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
		TEST_METHOD(notEmptyLinesInTargetFuncBodyInStartMidEnd)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int arg1, double arg2)",
				"{",
				"    int c = 0;",
				"//  doSmth(c);",
				"",
				"// просто комментарий",
				"",
				"    c = 1 + 3;",
				"// еще комментарий",
				"    return c;",
				"}",
				"int main()",
				"{",
				"return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 15 }; fillText(&programText, inputText);
			
			Text funcBody = {};

			Text exp_funcBody = { {}, 10 }; fillText(&exp_funcBody, inputText + 1);
			bool exp_resOfSearch = true;

			bool resOfSearch = findBodyOfDefinition(programText, 0, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
		TEST_METHOD(operatorsInTargetFunctionBody)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int arg1, double arg2)",
				"{",
				"    for(int i = 0; i < 10; i++)",
				"    {",
				"    }",
				"    if (arg1 > i)",
				"    {",
				"        return 1;",
				"    }",
				"    else",
				"    {",
				"        return arg1;",
				"    }",
				"}",
				"int main()",
				"{",
				"return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 18 }; fillText(&programText, inputText);
			
			Text funcBody = {};

			Text exp_funcBody = { {}, 13 }; fillText(&exp_funcBody, inputText + 1);
			bool exp_resOfSearch = true;

			bool resOfSearch = findBodyOfDefinition(programText, 0, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
		TEST_METHOD(nestedOperatorsInTargetFunctionBody)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
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
				"return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 17 }; fillText(&programText, inputText);
			
			Text funcBody = {};

			Text exp_funcBody = { {}, 12 }; fillText(&exp_funcBody, inputText + 1);
			bool exp_resOfSearch = true;

			bool resOfSearch = findBodyOfDefinition(programText, 0, &funcBody);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcBody, funcBody));
		}
	};
}
