#include "stdafx.h"
#include "CppUnitTest.h"
#include <glapp/version.h>
#include <sstream>

using namespace glapp;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
namespace VisualStudio {
namespace CppUnitTestFramework {

template<> static std::wstring ToString<version>(const version& v)
{
	std::wostringstream stream;
	stream << "version<" << v.major() << "." << v.minor() << "." << v.rev() << ">";
	return stream.str();
}

}}}

namespace glapptests
{		
	TEST_CLASS(VersionTest)
	{
	public:
		
		TEST_METHOD(constructor_all)
		{
			const version v{ 1, 5, 17 };
			Assert::AreEqual(v.major(), std::size_t(1));
			Assert::AreEqual(v.minor(), std::size_t(5));
			Assert::AreEqual(v.rev(), std::size_t(17));
		}

		TEST_METHOD(constructor_default_rev)
		{
			version v{ 9, 7 };
			Assert::AreEqual(v.major(), std::size_t(9));
			Assert::AreEqual(v.minor(), std::size_t(7));
			Assert::AreEqual(v.rev(), std::size_t(0));
		}

		TEST_METHOD(copy_constructor)
		{
			const version v_9_7{ 9, 7 };
			const version v = v_9_7;

			Assert::AreEqual(v_9_7, v);
		}

		TEST_METHOD(copy)
		{
			const version v_9_7{ 9, 7 };
			version v{ 0, 1 };
			v = v_9_7;

			Assert::AreEqual(v_9_7, v);
		}

		TEST_METHOD(equality)
		{
			const version v{ 9, 7 };
			Assert::AreEqual(v, version(9, 7));
			Assert::IsFalse(v == version(9, 7, 17));
			Assert::AreNotEqual(v, version(4, 7));
		}

		TEST_METHOD(comparison)
		{
			const version v_9_7{ 9, 7 };
			const version v_8_7{ 8, 7 };
			const version v_8_6{ 8, 6 };

			Assert::IsTrue(v_8_7 < v_9_7);
			Assert::IsTrue(!(v_9_7 < v_8_7));
			Assert::IsTrue(v_8_7 <= v_9_7);
			Assert::IsTrue(v_9_7 >= v_8_7);
			Assert::IsTrue(v_9_7 > v_8_7);
			Assert::IsTrue(v_9_7 <= v_9_7);
			Assert::IsTrue(v_9_7 >= v_9_7);

			Assert::IsTrue(v_8_6 < v_8_7);
			Assert::IsFalse(v_8_7 < v_8_6);
			Assert::IsTrue(v_8_6 <= v_8_7);
			Assert::IsTrue(v_8_7 >= v_8_6);
			Assert::IsTrue(v_8_7 > v_8_6);

			Assert::IsTrue(v_8_6 < version(8, 6, 1));
			Assert::IsFalse(version(8, 6, 1) < v_8_6);
			Assert::IsTrue(v_8_6 <= version(8, 6, 1));
			Assert::IsTrue(v_8_6 >= version(8, 6, 0));
			Assert::IsTrue(version(8, 6, 1) > v_8_6);
		}

	};
}