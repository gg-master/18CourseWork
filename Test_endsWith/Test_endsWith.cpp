#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestendsWith
{
	TEST_CLASS(TestendsWith)
	{
	public:
		
		TEST_METHOD(emptyStringAndSubstr)
		{
			char inputStr[] = "";
			char subStr[] = "";

			bool expRes = true;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptyString)
		{
			char inputStr[] = "";
			char subStr[] = "someText";

			bool expRes = false;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptySubstr)
		{
			char inputStr[] = "someText";
			char subStr[] = "";

			bool expRes = true;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(subStrNotInString)
		{
			char inputStr[] = "other words";
			char subStr[] = "someText";

			bool expRes = false;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(oneSubstrInString)
		{
			char inputStr[] = "other text. someText";
			char subStr[] = "someText";

			bool expRes = true;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(twoSubstrInString)
		{
			char inputStr[] = "other text. someText. someText";
			char subStr[] = "someText";

			bool expRes = true;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(manySubstrInString)
		{
			char inputStr[] = "someText = someText(someText()) = someText";
			char subStr[] = "someText";

			bool expRes = true;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(substrInStartString)
		{
			char inputStr[] = "someText(otherFunction());";
			char subStr[] = "someText";

			bool expRes = false;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(substrInMiddleString)
		{
			char inputStr[] = "otherText = someText(int arg1, bool arg2);";
			char subStr[] = "someText";

			bool expRes = false;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(firstHalfOfSubstrInString)
		{
			char inputStr[] = "otherText, some";
			char subStr[] = "someText";

			bool expRes = false;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(secondHalfOfSubstrInString)
		{
			char inputStr[] = "otherText Text";
			char subStr[] = "someText";

			bool expRes = false;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(middlefOfSubstrInString)
		{
			char inputStr[] = "otherText. omeTex";
			char subStr[] = "someText";

			bool expRes = false;
			bool res = endsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
	};
}
