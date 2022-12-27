#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TeststripRight
{
	TEST_CLASS(TeststripRight)
	{
	public:
		
		TEST_METHOD(emptyString)
		{
			char inputStr[] = "";
			char* expPtr = "";
			char* resPtr = stripRight(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(onRightNoOneSym)
		{
			char inputStr[] = "some text";
			char* expPtr = "some text";
			char* resPtr = stripRight(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(onRightOneSym)
		{
			char inputStr[] = "some text ";
			char* expPtr = "some text";
			char* resPtr = stripRight(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(onRightManySym)
		{
			char inputStr[] = "some text\t\t  \t\t    ";
			char* expPtr = "some text";
			char* resPtr = stripRight(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(allSym)
		{
			char inputStr[] = "\t\t   \t \t";
			char* expPtr = "";
			char* resPtr = stripRight(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
	};
}
