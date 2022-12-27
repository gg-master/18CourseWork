#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TeststripLeft
{
	TEST_CLASS(TeststripLeft)
	{
	public:
		TEST_METHOD(emptyString)
		{
			char inputStr[] = "";
			char* expPtr = "";
			char* resPtr = stripLeft(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(onLeftNoOneSym)
		{
			char inputStr[] = "some text";
			char* expPtr = "some text";
			char* resPtr = stripLeft(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(onLeftOneSym)
		{
			char inputStr[] = " some text";
			char* expPtr = "some text";
			char* resPtr = stripLeft(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(onLeftManySym)
		{
			char inputStr[] = "\t\t  \t\t    some text";
			char* expPtr = "some text";
			char* resPtr = stripLeft(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(allSym)
		{
			char inputStr[] = "\t\t   \t \t";
			char* expPtr = "";
			char* resPtr = stripLeft(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
	};
}
