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

namespace TestfindFunctionDefinition 
{
	TEST_CLASS(TestfindFunctionDefinition)
	{
	public:
		TEST_METHOD(targetFunctionIsMissing)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
				{
					"int main()",
					"{",
					"}"
				};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**) inputText, 3};
			Text funcDefinition = {};
			
			Text exp_funcDefinition = {};
			bool exp_resOfSearch = false;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
 		}
		TEST_METHOD(oneTargetFunctionInText)
		{
			char inputText[][MAX_LINE_LENGTH+1] =
			{
				"int someFunction(int arg1, double arg2)",
				"{",
				"    int c = arg1 + arg2;",
				"    return c",
				"}",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = {(char **) inputText, 8};
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**)inputText, 5 };
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(manySameTargetFunctionInText)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int a)",
				"{",
				"}",
				"int someFunction1(int a)",
				"{",
				"}",
				"int someFunctionOne(int a)",
				"{",
				"}",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 12};
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**) inputText, 3};
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionIsPrototype)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int);",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			struct Text programText = { (char**)inputText, 4 };
			Text funcDefinition = {};

			Text exp_funcDefinition = {};
			bool exp_resOfSearch = false;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionIsPrototypeAndDefinition)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int);",
				"int main()",
				"{",
				"}",
				"int someFunction(int a)",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 7 };
			Text funcDefinition = {};

			Text exp_funcDefinition = {(char**) inputText + 4, 3};
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(oneCallTargetFunctionWhithoutDefinition)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int main()",
				"{",
				"    int a = 0;",
				"    int b = someFunction(a);",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			struct Text programText = { (char**)inputText, 5 };
			struct Text funcDefinition = {};

			Text exp_funcDefinition = {};
			bool exp_resOfSearch = false;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionDefinitionBeforeCall)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int a)",
				"{",
				"}",
				"int main()",
				"{",
				"   int a = 0;",
				"   int b = someFunction(a);",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 8 };
			Text funcDefinition= {};

			Text exp_funcDefinition = {};
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionDefinitionAfterCall)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int main()",
				"{",
				"   int a = 0;",
				"   int b = someFunction(a);",
				"}",
				"int someFunction(int a)",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 8 };
			Text funcDefinition = {};

			Text exp_funcDefinition = {(char**) inputText + 5, 3};
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(manyCallTargetFunctionWhithoutDefinition)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int main()",
				"{",
				"   int a = count(\"some string\");",
				"   int b = someFunction(a);",
				"}",
				"int count(char str[])",
				"{",
				"   return someFunction(someFunction(0));",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 9 };
			Text funcDefinition = {};

			Text exp_funcDefinition = {};
			bool exp_resOfSearch = false;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionDefinitionBeforeManyCall)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int a)",
				"{",
				"}",
				"int main()",
				"{",
				"   int a = count(\"some string\");",
				"   int b = someFunction(a);",
				"}",
				"int count(char str[])",
				"{",
				"   return someFunction(someFunction(0));",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 12 };
			Text funcDefinition = {};

			Text exp_funcDefinition = {(char**) inputText, 3};
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionDefinitionAfterManyCall)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int main()",
				"{",
				"   int a = count(\"some string\");",
				"   int b = someFunction(a);",
				"}",
				"int count(char str[])",
				"{",
				"   return someFunction(someFunction(0));",
				"}",
				"int someFunction(int a)",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 12 };
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**)inputText+9, 3 };
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionIsCommented)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"// int someFuntion(int a)",
				"// {",
				"// }",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 6 };
			Text funcDefinition = {};

			Text exp_funcDefinition = {};
			bool exp_resOfSearch = false;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionPartIsCommented)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int a)",
				"{",
				"// int c;",
				"// doSmth();",
				"//}",
				"}",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 9 };
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**)inputText, 6 };
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionNameAsVariable)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int main()",
				"{",
				"   int someFunction = 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 4 };
			Text funcDefinition = {};

			Text exp_funcDefinition = {};
			bool exp_resOfSearch = false;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionBodyIsEmpty)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int a)",
				"{",
				"",
				"",
				"",
				"}",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 9 };
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**)inputText, 6 };
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionBodyIsNotEmpty)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int a)",
				"{",
				"    int c = 0;",
				"    doSmth(c);",
				"    return c;",
				"}",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 9 };
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**)inputText, 6 };
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(emptyLinesInTargetFuncBodyInStartMidEnd)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int a)",
				"{",
				"",
				"//  doSmth(c);",
				"    int c = 0;",
				"",
				"//  doSmth(c);",
				"",
				"// ������ �����������",
				"",
				"}",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 14 };
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**)inputText, 11 };
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(notEmptyLinesInTargetFuncBodyInStartMidEnd)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int a)",
				"{",
				"    int c = 0;",
				"//  doSmth(c);",
				"",
				"// ������ �����������",
				"",
				"    c = 1 + 3;",
				"// ��� �����������",
				"    return c;",
				"}",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 14 };
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**)inputText, 11 };
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(operatorsInTargetFunctionBody)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int c)",
				"{",
				"    for(int i = 0; i < 10; i++)",
				"    {",
				"    }",
				"    if (c > i)",
				"    {",
				"        return 1;",
				"    }",
				"    else",
				"    {",
				"        return c;",
				"    }",
				"}",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 17 };
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**)inputText, 14 };
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(nestedOperatorsInTargetFunctionBody)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int c)",
				"{",
				"    for(int i = 0; i < 10; i++)",
				"    {",
				"        if (c > i)",
				"        {",
				"            while(i < c)",
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
			Text programText = { (char**)inputText, 16 };
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**)inputText, 13 };
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}	
		TEST_METHOD(compositTypeOfReturnValue)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"unsigned short int someFunction(int arg1, double arg2)",
				"{",
				"    unsigned short int c = arg1 + arg2;",
				"    return c",
				"}",
				"int main()",
				"{",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { (char**)inputText, 8 };
			Text funcDefinition = {};

			Text exp_funcDefinition = { (char**)inputText, 5 };
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
	};
}
