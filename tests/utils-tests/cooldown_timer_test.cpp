#include "stdafx.h"
#include "CppUnitTest.h"
#include <utils/cooldown_timer.h>

using namespace utils;
using namespace std::chrono;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
namespace VisualStudio {
namespace CppUnitTestFramework {

template<> static std::wstring ToString<cooldown_timer>(const cooldown_timer& t)
{
	std::wostringstream stream;
	stream << "cooldown_timer<" << t.remaining().count() << "/" << t.cooldown().count() << ">";
	return stream.str();
}

}}}

namespace utilstests
{		
	TEST_CLASS(CooldownTimerTest1)
	{
	public:

		TEST_METHOD(constructor)
		{
			cooldown_timer timer(1s);
			const auto remaining_is_0_s = timer.remaining() == 0s;
			const auto cooldown_is_1_s = timer.cooldown() == 1s;
			Assert::IsTrue(remaining_is_0_s);
			Assert::IsTrue(cooldown_is_1_s);
			Assert::IsTrue(static_cast<bool>(timer));
		}

		TEST_METHOD(execute)
		{
			cooldown_timer timer(1s);
			Assert::IsTrue(timer.execute([]() { std::cout << "Executed" << std::endl; }));
			const auto remaining_is_1_s = timer.remaining() == 1s;
			Assert::IsTrue(remaining_is_1_s);
			Assert::IsFalse(timer.execute([]() { std::cout << "Not executed" << std::endl; }));
		}

		TEST_METHOD(execute_update)
		{
			cooldown_timer timer(1s);
			Assert::IsTrue(timer.execute([]() { std::cout << "Executed" << std::endl; }));

			timer.update(500ms);
			const auto remaining_is_500_ms = timer.remaining() == 500ms;
			Assert::IsTrue(remaining_is_500_ms);
			Assert::IsFalse(timer.execute([]() { std::cout << "Not executed" << std::endl; }));

			timer.update(500ms);
			const auto remaining_is_0_s = timer.remaining() == 0s;
			Assert::IsTrue(remaining_is_0_s);
			Assert::IsTrue(timer.execute([]() { std::cout << "Executed" << std::endl; }));
		}

	};
}