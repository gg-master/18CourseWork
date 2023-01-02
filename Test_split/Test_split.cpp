#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool compareSplittedString(char first[][MAX_LINE_LENGTH + 1], char second[][MAX_LINE_LENGTH + 1], int length)
{
	for (int i = 0; i < length; i++)
	{
		if (strcmp(first[i], second[i]) != 0) return false;
	}
	return true;
}

namespace Testsplit
{
	TEST_CLASS(Testsplit)
	{
	public:
		
		TEST_METHOD(emptyString)
		{
			char inputStr[] = "";

			int expLength = 0;
			char expSplitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};

			char splitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};
			int sLength = split(inputStr, splitted);

			Assert::AreEqual(expLength, sLength);
			Assert::IsTrue(compareSplittedString(expSplitted, splitted, sLength));
		}
		TEST_METHOD(onlySeparators)
		{
			char inputStr[] = "  \t  \t\t";

			int expLength = 0;
			char expSplitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};

			char splitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};
			int sLength = split(inputStr, splitted);

			Assert::AreEqual(expLength, sLength);
			Assert::IsTrue(compareSplittedString(expSplitted, splitted, sLength));
		}
		TEST_METHOD(oneSubString)
		{
			char inputStr[] = "string";

			int expLength = 1;
			char expSplitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {"string"};

			char splitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};
			int sLength = split(inputStr, splitted);

			Assert::AreEqual(expLength, sLength);
			Assert::IsTrue(compareSplittedString(expSplitted, splitted, sLength));
		}
		TEST_METHOD(twoSubString)
		{
			char inputStr[] = "some string";

			int expLength = 2;
			char expSplitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = { "some", "string" };

			char splitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};
			int sLength = split(inputStr, splitted);

			Assert::AreEqual(expLength, sLength);
			Assert::IsTrue(compareSplittedString(expSplitted, splitted, sLength));
		}
		TEST_METHOD(manySubString)
		{
			char inputStr[] = "some text and words";

			int expLength = 4;
			char expSplitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = { "some", "text", "and", "words"};

			char splitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};
			int sLength = split(inputStr, splitted);

			Assert::AreEqual(expLength, sLength);
			Assert::IsTrue(compareSplittedString(expSplitted, splitted, sLength));
		}
		TEST_METHOD(sepAtStartOfString)
		{
			char inputStr[] = "\tstring";

			int expLength = 1;
			char expSplitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = { "string" };

			char splitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};
			int sLength = split(inputStr, splitted);

			Assert::AreEqual(expLength, sLength);
			Assert::IsTrue(compareSplittedString(expSplitted, splitted, sLength));
		}
		TEST_METHOD(sepAtEndOfString)
		{
			char inputStr[] = "string\t";

			int expLength = 1;
			char expSplitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = { "string" };

			char splitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};
			int sLength = split(inputStr, splitted);

			Assert::AreEqual(expLength, sLength);
			Assert::IsTrue(compareSplittedString(expSplitted, splitted, sLength));
		}
		TEST_METHOD(sepAtStartAndEndOfString)
		{
			char inputStr[] = "\t \t string\t \t";

			int expLength = 1;
			char expSplitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = { "string" };

			char splitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};
			int sLength = split(inputStr, splitted);

			Assert::AreEqual(expLength, sLength);
			Assert::IsTrue(compareSplittedString(expSplitted, splitted, sLength));
		}
		TEST_METHOD(sepAtStartAndMiddleAndEndOfString)
		{
			char inputStr[] = "\t\t some \t string \t";

			int expLength = 2;
			char expSplitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = { "some", "string"};

			char splitted[MAX_LINE_LENGTH][MAX_LINE_LENGTH + 1] = {};
			int sLength = split(inputStr, splitted);

			Assert::AreEqual(expLength, sLength);
			Assert::IsTrue(compareSplittedString(expSplitted, splitted, sLength));
		}
	};
}
