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
					"	return 0;",
					"}",
				};
			char targetFuncName[81] = "someFunction";

			Text programText = { {}, 4 };
			fillText(&programText, inputText);

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
				"	return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";

			Text programText = { {}, 9};
			fillText(&programText, inputText);

			Text funcDefinition = {};
			
			Text exp_funcDefinition = { {}, 5 };
			fillText(&exp_funcDefinition, inputText);

			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
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

			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 4}; fillText(&exp_funcDefinition, inputText + 4);

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
				"	return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			struct Text programText = { {}, 5 };
			fillText(&programText, inputText);

			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 0 };
			bool exp_resOfSearch = false;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionIsPrototypeAndDefinition)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int arg1, double arg2);",
				"int main()",
				"{",
				"return 0;",
				"}",
				"int someFunction(int arg1, double arg2)",
				"{",
				"    int c = arg1 + arg2;",
				"// Комментарий",
				"    return c;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 11}; fillText(&programText, inputText);

			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 6}; fillText(&exp_funcDefinition, inputText + 5);

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
				"    int b = someFunction(a, 0.1);",
				"	 return 0;"
				"}",
			};
			char targetFuncName[81] = "someFunction";
			struct Text programText = { {}, 6 }; fillText(&programText, inputText);

			struct Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 0 };
			bool exp_resOfSearch = false;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(targetFunctionDefinitionBeforeCall)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int someFunction(int arg1, double arg2)",
				"{",
				"    int c = arg1 + arg2;",
				"// Комментарий",
				"    return c;",
				"}",
				"int main()",
				"{",
				"   int a = 0;",
				"   int b = someFunction(a, 0.1);",
				"   return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 12}; fillText(&programText, inputText);

			Text funcDefinition= {};

			Text exp_funcDefinition = { {}, 6 }; fillText(&exp_funcDefinition, inputText);
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
				"   int b = someFunction(a, 0.1);",
				"   return 0;",
				"}",
				"int someFunction(int arg1, double arg2)",
				"{",
				"    int c = arg1 + arg2;",
				"// Комментарий",
				"    return c;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 12};
			fillText(&programText, inputText);

			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 6 };
			fillText(&exp_funcDefinition, inputText + 6);

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
				"   int b = someFunction(a, 0.1);",
				"   return 0;",
				"}",
				"int count(char str[])",
				"{",
				"   return someFunction(someFunction(0, 0.0), 1.1);",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 10 }; fillText(&programText, inputText);
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
				"int someFunction(int arg1, double arg2)",
				"{",
				"    int c = arg1 + arg2;",
				"// Комментарий",
				"    return c;",
				"}",
				"int main()",
				"{",
				"   int a = count(\"some string\");",
				"   int b = someFunction(a, 0.1);",
				"   return 0;",
				"}",
				"int count(char str[])",
				"{",
				"   return someFunction(someFunction(0, 0.0), 1.1);",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 16 }; fillText(&programText, inputText);
			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 6 }; fillText(&exp_funcDefinition, inputText);
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
				"   int b = someFunction(a, 1.1);",
				"   return 0;",
				"}",
				"int count(char str[])",
				"{",
				"   return someFunction(someFunction(0, 0.1), 1.1);",
				"}",
				"int someFunction(int arg1, double arg2)",
				"{",
				"    int c = arg1 + arg2;",
				"// Комментарий",
				"    return c;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 16 }; fillText(&programText, inputText);

			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 6 }; fillText(&exp_funcDefinition, inputText + 10);
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
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
			Text programText = { {}, 11}; fillText(&programText, inputText);
			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 7 }; fillText(&exp_funcDefinition, inputText);
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
				"   return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 5}; fillText(&programText, inputText);
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
			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 6 }; fillText(&exp_funcDefinition, inputText);
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
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
			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 6 }; fillText(&exp_funcDefinition, inputText);
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
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
			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 11 }; fillText(&exp_funcDefinition, inputText);
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
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
			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 11 }; fillText(&exp_funcDefinition, inputText);
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
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
			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 14 }; fillText(&exp_funcDefinition, inputText);
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
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
			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 13 }; fillText(&exp_funcDefinition, inputText);
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
				"return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 9 }; fillText(&programText, inputText);
			Text funcDefinition = {};

			Text exp_funcDefinition = { {}, 5 }; fillText(&exp_funcDefinition, inputText);
			bool exp_resOfSearch = true;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
		TEST_METHOD(callOfFunctionSameAsHeadOfDefinition)
		{
			char inputText[][MAX_LINE_LENGTH + 1] =
			{
				"int main()",
				"{",
				"    if(!someFunction()) return 0;",
				"}",
			};
			char targetFuncName[81] = "someFunction";
			Text programText = { {}, 4 }; fillText(&programText, inputText);
			Text funcDefinition = {};

			Text exp_funcDefinition = {}; fillText(&exp_funcDefinition, inputText);
			bool exp_resOfSearch = false;

			bool resOfSearch = findFunctionDefinition(programText, targetFuncName, &funcDefinition);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
			Assert::IsTrue(compareStructText(exp_funcDefinition, funcDefinition));
		}
	};
}
