#include "pch.h"
#include "CppUnitTest.h"
#include "..//FloydWarshall/FloydWarshall.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FWTest
{
	TEST_CLASS(FWTest)
	{
	public:
		FWGraph test;
		TEST_METHOD(InputCitiesTest)
		{
			Assert::IsTrue(test.cities.contain("Москва") && test.cities.contain("Санкт-Петербург") && test.cities.contain("Хабаровск") && test.cities.contain("Владивосток"));
		}

		TEST_METHOD(InputAdjMatrixTest)
		{
			Assert::IsTrue(test.adjMatrix[0][0] == 0 && test.adjMatrix[0][1] == 10 && test.adjMatrix[0][2] == 14 && test.adjMatrix[0][3] == 20);
		}

		TEST_METHOD(CreateWFMatrixTest)
		{
			Assert::IsTrue(test.fwMatrix[0][0] == 0 && test.fwMatrix[0][1] == 10 && test.fwMatrix[0][2] == 14 && test.fwMatrix[0][3] == 20);
		}

		TEST_METHOD(FindMinWayTest1)
		{
			Assert::IsTrue(test.findMinWay("Москва", "Хабаровск") == 34);
		}

		TEST_METHOD(FindMinWayTest2)
		{
			Assert::IsTrue(test.findMinWay("Москва", "Москва") == 0);
		}
	};
}
