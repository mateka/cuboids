#include "stdafx.h"
#include "CppUnitTest.h"
#include <glapp/resolution.h>

using namespace glapp;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft {
namespace VisualStudio {
namespace CppUnitTestFramework {

template<> static std::wstring ToString<resolution>(const resolution& r)
{
	std::wostringstream stream;
	stream << "resolution<" << r.width() << "x" << r.height() << ">";
	return stream.str();
}

}
}
}


namespace glapptests
{
TEST_CLASS(ResolutionTest)
{
public:

	TEST_METHOD(constructor_all)
	{
		const resolution r{ 640, 480 };
		Assert::AreEqual(r.width(), std::size_t(640));
		Assert::AreEqual(r.height(), std::size_t(480));
	}

	TEST_METHOD(copy_constructor)
	{
		const resolution r_800x600{ 800, 600 };
		const resolution r = r_800x600;

		Assert::AreEqual(r_800x600, r);
	}

	TEST_METHOD(copy)
	{
		const resolution r_800x600{ 800, 600 };
		resolution r{ 1280, 1789 };
		r = r_800x600;

		Assert::AreEqual(r_800x600, r);
	}

	TEST_METHOD(equality)
	{
		const resolution r{ 640, 480 };
		Assert::AreEqual(r, resolution(640, 480));
		Assert::IsFalse(r == resolution(800, 600));
		Assert::AreNotEqual(r, resolution(800, 600));
	}
};
}