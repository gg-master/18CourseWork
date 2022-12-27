#include "pch.h"
#include "CppUnitTest.h"
#include "string"
#include "../18_Korshunov/18_Korshunov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestisLineHeadOfDefinition
{
	TEST_CLASS(TestisLineHeadOfDefinition)
	{
	public:
		
		TEST_METHOD(emptyValues)
		{
			char inputStr[] = "";
			char funcName[] = "";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptyString)
		{
			char inputStr[] = "";
			char funcName[] = "someFunction";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(emptyFuncName)
		{
			char inputStr[] = "int someFunction(bool arg1, float arg2)";
			char funcName[] = "";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(funcNameNotInString)
		{
			char inputStr[] = "int otherFunction(bool arg1, float arg2)";
			char funcName[] = "someFunction";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(oneFuncNameInString)
		{
			char inputStr[] = "int someFunction(bool arg1, float arg2)";
			char funcName[] = "someFunction";

			bool expRes = true;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(twoFuncNameInString)
		{
			char inputStr[] = "int someFunctionsomeFunction(bool arg1, float arg2)";
			char funcName[] = "someFunction";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(manyFuncNameInString)
		{
			char inputStr[] = "int someFunctionsomeFunction(bool someFunction, float arg2)";
			char funcName[] = "someFunction";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(stringWithFuncNameIsPrototype)
		{
			char inputStr[] = "int someFunction(bool, float);";
			char funcName[] = "someFunction";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(stringWithFuncNameIsValName)
		{
			char inputStr[] = "int someFunction = 1;";
			char funcName[] = "someFunction";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(callFuncNameStringWithoutAssig)
		{
			char inputStr[] = "someFunction(1, false);";
			char funcName[] = "someFunction";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(callFuncNameStringWithAssig)
		{
			char inputStr[] = "int c = someFunction(1, false);";
			char funcName[] = "someFunction";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(compositTypeOfReturnValue)
		{
			char inputStr[] = "unsigned short int someFunction(bool arg1, float arg2)";
			char funcName[] = "someFunction";

			bool expRes = true;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(stringWithFuncNameIsCommented)
		{
			char inputStr[] = "// int someFunction(bool arg1, float arg2)";
			char funcName[] = "someFunction";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
		TEST_METHOD(stringWithFuncNameIsPartlyCommented)
		{
			char inputStr[] = "int someFunction;// someFunction(bool arg1, float arg2)";
			char funcName[] = "someFunction";

			bool expRes = false;
			bool res = isLineHeadOfDefinition(inputStr, funcName);
			Assert::AreEqual(expRes, res);
		}
	};
}
