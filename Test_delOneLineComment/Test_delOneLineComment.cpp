#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestdelOneLineComment
{
	TEST_CLASS(TestdelOneLineComment)
	{
	public:
		
		TEST_METHOD(emptyString)
		{
			char inputStr[] = "";
			char* expPtr = "";
			char* resPtr = delOneLineComment(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(noCommentInString)
		{
			char inputStr[] = "int a = 0;";
			char* expPtr = "int a = 0;";
			char* resPtr = delOneLineComment(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(oneCommentInEndOfString)
		{
			char inputStr[] = "int a = 0;//";
			char* expPtr = "int a = 0;";
			char* resPtr = delOneLineComment(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(oneCommentInMiddleOfString)
		{
			char inputStr[] = "int a;// = 0; комментарий";
			char* expPtr = "int a;";
			char* resPtr = delOneLineComment(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(oneCommentInStartOfString)
		{
			char inputStr[] = "// int a = 0; комментарий";
			char* expPtr = "";
			char* resPtr = delOneLineComment(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(doubleCommentInEndOfString)
		{
			char inputStr[] = "int a;////";
			char* expPtr = "int a;";
			char* resPtr = delOneLineComment(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(doubleCommentInMiddleOfString)
		{
			char inputStr[] = "int a;// = 0; // комментарий";
			char* expPtr = "int a;";
			char* resPtr = delOneLineComment(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(doubleCommentInStartOfString)
		{
			char inputStr[] = "//// int a = 0; комментарий";
			char* expPtr = "";
			char* resPtr = delOneLineComment(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
		TEST_METHOD(manyCommentInString)
		{
			char inputStr[] = "// //int a; // = 0; // комментарий //";
			char* expPtr = "";
			char* resPtr = delOneLineComment(inputStr);
			Assert::IsTrue(strcmp(resPtr, expPtr) == 0);
		}
	};
}
