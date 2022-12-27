#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TeststartsWith
{
	TEST_CLASS(TeststartsWith)
	{
	public:
		
		TEST_METHOD(emptyStringAndSubstr)
		{
			char inputStr[] = "";
			char subStr[] = "";

			bool expRes = true;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptyString)
		{
			char inputStr[] = "";
			char subStr[] = "someFunction";

			bool expRes = false;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptySubstr)
		{
			char inputStr[] = "someFunction(int a);";
			char subStr[] = "";

			bool expRes = true;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(substrNotInString)
		{
			char inputStr[] = "otherFunction(int a);";
			char subStr[] = "someFunction";

			bool expRes = false;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(oneSubstrInString)
		{
			char inputStr[] = "someFunction(int a);";
			char subStr[] = "someFunction";

			bool expRes = true;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(twoSubstrInString)
		{
			char inputStr[] = "someFunction_someFunction(int a);";
			char subStr[] = "someFunction";

			bool expRes = true;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(manySubstrInString)
		{
			char inputStr[] = "someFunctionResult = someFunction(someFunction());";
			char subStr[] = "someFunction";

			bool expRes = true;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(substrInMiddleString)
		{
			char inputStr[] = "int result = someFuntion(int arg1, bool arg2);";
			char subStr[] = "someFunction";

			bool expRes = false;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(substrInEndString)
		{
			char inputStr[] = "int result = someFunction";
			char subStr[] = "someFunction";

			bool expRes = false;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(firstHalfOfSubstrInString)
		{
			char inputStr[] = "someFun(int arg1);";
			char subStr[] = "someFunction";

			bool expRes = false;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(secondHalfOfSubstrInString)
		{
			char inputStr[] = "tion(int arg1);";
			char subStr[] = "someFunction";

			bool expRes = false;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(middlefOfSubstrInString)
		{
			char inputStr[] = "omeFunctio(int arg1);";
			char subStr[] = "someFunction";

			bool expRes = false;
			bool res = startsWith(inputStr, subStr);
			Assert::AreEqual(expRes, res);
		}
	};
}
