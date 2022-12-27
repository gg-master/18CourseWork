#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestisWordInLine
{
	TEST_CLASS(TestisWordInLine)
	{
	public:
		
		TEST_METHOD(wordNotInLine)
		{
			char inputStr[] = "int otherFunction(int a);";
			char word[] = "someFunction";

			bool expRes = false;
			bool res = isWordInLine(inputStr, word);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(oneWordInLine)
		{
			char inputStr[] = "int someFunction(int a);";
			char word[] = "someFunction";

			bool expRes = true;
			bool res = isWordInLine(inputStr, word);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(twoWordInLine)
		{
			char inputStr[] = "int someFunction_someFunction(int a);";
			char word[] = "someFunction";

			bool expRes = true;
			bool res = isWordInLine(inputStr, word);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(manyWordInLine)
		{
			char inputStr[] = "someFunctionResult = someFunction(someFunction());";
			char word[] = "someFunction";

			bool expRes = true;
			bool res = isWordInLine(inputStr, word);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(wordInStartOfLine)
		{
			char inputStr[] = "someFunction(otherFunction());";
			char word[] = "someFunction";

			bool expRes = true;
			bool res = isWordInLine(inputStr, word);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(wordInMiddleOfLine)
		{
			char inputStr[] = "int result = someFunction(int arg1, bool arg2);";
			char word[] = "someFunction";

			bool expRes = true;
			bool res = isWordInLine(inputStr, word);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(wordInEndOfLine)
		{
			char inputStr[] = "int result = someFunction;";
			char word[] = "someFunction";

			bool expRes = true;
			bool res = isWordInLine(inputStr, word);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(firstHalfOfWordInLine)
		{
			char inputStr[] = "int someFun(int arg1);";
			char word[] = "someFunction";

			bool expRes = false;
			bool res = isWordInLine(inputStr, word);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(secondHalfOfWordInLine)
		{
			char inputStr[] = "int tion(int arg1);";
			char word[] = "someFunction";

			bool expRes = false;
			bool res = isWordInLine(inputStr, word);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(middleOfWordInLine)
		{
			char inputStr[] = "int omeFunctio(int arg1);";
			char word[] = "someFunction";

			bool expRes = false;
			bool res = isWordInLine(inputStr, word);
			Assert::AreEqual(expRes, res);
		}
	};
}
