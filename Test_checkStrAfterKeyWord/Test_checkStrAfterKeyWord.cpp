#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestcheckStrAfterKeyWord
{
	TEST_CLASS(TestcheckStrAfterKeyWord)
	{
	public:
		
		TEST_METHOD(emptyValues)
		{
			char inputStr[] = "";
			char keyWord[] = "";
			char starsWithStr[] = "";
			char endsWithStr[] = "";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptyStrAndKeyWord)
		{
			char inputStr[] = "";
			char keyWord[] = "";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptyString)
		{
			char inputStr[] = "";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptyKeyWord)
		{
			char inputStr[] = "int someFunction(bool arg1, float arg2)";
			char keyWord[] = "";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptyStartSubstrAndEndSubstr)
		{
			char inputStr[] = "int someFunction(bool arg1, float arg2)";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "";
			char endsWithStr[] = "";

			bool expRes = true;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptyStartSubstr)
		{
			char inputStr[] = "int someFunction(bool arg1, float arg2)";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "";
			char endsWithStr[] = ")";

			bool expRes = true;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptyEndSubstr)
		{
			char inputStr[] = "int someFunction(bool arg1, float arg2)";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = "";

			bool expRes = true;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(keyWordNotInString)
		{
			char inputStr[] = "int otherFunction(bool arg1, float arg2)";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(keyWordInString)
		{
			char inputStr[] = "int someFunction(bool arg1, float arg2)";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = true;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(doubleKeyWordInString)
		{
			char inputStr[] = "someFunction = someFunction(bool arg1, float arg2)";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(manyKeyWordInString)
		{
			char inputStr[] = "someFunction = someFunction(bool someFunction, float someFunction)";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(keyWordAtStartOfString)
		{
			char inputStr[] = "someFunction(bool arg1, float arg2)";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = true;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(keyWordAtEndOfString)
		{
			char inputStr[] = "other = someFunction";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(manyStartSubstrAndEndSubstrAfterKeyWord)
		{
			char inputStr[] = "int someFunction(bool (arg1), float (arg2))";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = true;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(manyStartSubstrAndEndSubstrBeforeKeyWord)
		{
			char inputStr[] = "int val = (int) a + (int)c + (int)someFunction";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(endSubstrAtMiddleOfString)
		{
			char inputStr[] = "int val = someFunction(1, true) + a";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(startSubstrAtStartOfString)
		{
			char inputStr[] = "(int) someFunction + a";
			char keyWord[] = "someFunction";
			char starsWithStr[] = "(";
			char endsWithStr[] = ")";

			bool expRes = false;
			bool res = checkStrAfterKeyWord(inputStr, keyWord, starsWithStr, endsWithStr);
			Assert::AreEqual(expRes, res);
		}
	};
}
