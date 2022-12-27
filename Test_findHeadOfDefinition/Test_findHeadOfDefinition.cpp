#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void fillText(Text* destination, char source[][MAX_LINE_LENGTH + 1])
{
	for (int i = 0; i < destination->countLines; i++)
		destination->ptrOnLines[i] = (char*)source[i];
}

namespace TestfindHeadOfDefinition
{
	TEST_CLASS(TestfindHeadOfDefinition)
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

			int exp_resOfSearch = -1;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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

			Text programText = { {}, 9 };
			fillText(&programText, inputText);

			int exp_resOfSearch = 0;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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

			int exp_resOfSearch = 4;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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

			int exp_resOfSearch = -1;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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
			Text programText = { {}, 11 }; fillText(&programText, inputText);

			int exp_resOfSearch = 5;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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

			int exp_resOfSearch = -1;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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
			Text programText = { {}, 12 }; fillText(&programText, inputText);

			int exp_resOfSearch = 0;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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
			Text programText = { {}, 12 };
			fillText(&programText, inputText);

			int exp_resOfSearch = 6;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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

			int exp_resOfSearch = -1;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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

			int exp_resOfSearch = 0;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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

			int exp_resOfSearch = 10;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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

			int exp_resOfSearch = -1;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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

			int exp_resOfSearch = 0;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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
			Text programText = { {}, 5 }; fillText(&programText, inputText);

			int exp_resOfSearch = -1;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
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

			int exp_resOfSearch = 0;
			int resOfSearch = findHeadOfDefinition(programText, targetFuncName);

			Assert::AreEqual(exp_resOfSearch, resOfSearch);
		}
	};
}
