/*! \file  Interface_Tests.cpp
 *  \brief Tests for working with generic object interfaces.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   17.11.2021
 *
 */

#include "gtest/gtest.h"

#include "../InterfaceUtils.h"

namespace Symplektis::UnitTests
{
    using namespace Util;

	//
	// interface class for test class implementations
	//
	class ITestClass : public ISymplektBaseObject
	{
	public:
        ITestClass() : ISymplektBaseObject() {}
		ITestClass(const double& val)
		   : ISymplektBaseObject(), m_Value(val) { }

		ITestClass(const ITestClass& other)
			: m_Value(other.m_Value) { }

        void SetValue(const double& val)
        {
            m_Value = val;
        }

        [[nodiscard]] double GetValue() const
        {
            return m_Value;
        }

        [[nodiscard]] virtual double ProcessValue() const = 0;
	
	protected:
        double m_Value = 0.0;
	};

    //
    // test class implementation returning m_Value^2 with ProcessValue
    //
    class TestClassSquareImpl : public ITestClass
    {
    public:    	
        TestClassSquareImpl(const double& val)
    		: ITestClass(val) {}
    	
    	[[nodiscard]] double ProcessValue() const override
    	{
            return m_Value * m_Value;
    	}

        [[nodiscard]] ISymplektBaseObject* Clone() const override
        {
            return (new TestClassSquareImpl(*this));
        }
    };

    //
    // test class implementation returning sqrt(m_Value) with ProcessValue
    //
    class TestClassSqrtImpl : public ITestClass
    {
    public:
        TestClassSqrtImpl(const double& val)
            : ITestClass(val)
        {
        }

        [[nodiscard]] double ProcessValue() const override
        {
            return sqrt(m_Value);
        }

        [[nodiscard]] ISymplektBaseObject* Clone() const override
        {
            return (new TestClassSqrtImpl(*this));
        }
    };

    //
	// ===================================================================
    //

    TEST(Interface_TestSuite, CreateClassInterfaceFromData)
    {
        // Arrange
        const double dataValue = 3.0;
        const auto testObjSqr = TestClassSquareImpl(dataValue);

        // Act
        const auto iTestObjSqr = SymplektObjectInterface<ITestClass>(testObjSqr);

        // Assert
        EXPECT_DOUBLE_EQ(iTestObjSqr->GetValue(), dataValue);
        EXPECT_DOUBLE_EQ(iTestObjSqr->ProcessValue(), dataValue * dataValue);
    }

    TEST(Interface_TestSuite, CreateInterfacesFromTwoDifferentImplementations)
    {
        // Arrange
        const double dataValue = 3.0;
        const auto testObjSqr = TestClassSquareImpl(dataValue);
    	const auto testObjSqrt = TestClassSqrtImpl(dataValue);

    	// Act
        const auto iTestObjSqr = SymplektObjectInterface<ITestClass>(testObjSqr);
        const auto iTestObjSqrt = SymplektObjectInterface<ITestClass>(testObjSqrt);

    	// Assert
        EXPECT_DOUBLE_EQ(iTestObjSqr->GetValue(), dataValue);
        EXPECT_DOUBLE_EQ(iTestObjSqrt->GetValue(), dataValue);
        EXPECT_DOUBLE_EQ(iTestObjSqr->ProcessValue(), dataValue * dataValue);
        EXPECT_DOUBLE_EQ(iTestObjSqrt->ProcessValue(), sqrt(dataValue));
    }

    TEST(Interface_TestSuite, RetrieveInterface)
    {
        // Arrange
        const double dataValue = 3.0;
        const auto testObjSqrt = TestClassSqrtImpl(dataValue);
        const auto iTestObjSqrt = SymplektObjectInterface<ITestClass>(testObjSqrt);

        // Act
        const auto testObjSqrtIntf = iTestObjSqrt.RetrieveInterface<TestClassSqrtImpl>();

        // Assert
        EXPECT_DOUBLE_EQ(testObjSqrtIntf->GetValue(), dataValue);
        EXPECT_DOUBLE_EQ(testObjSqrtIntf->ProcessValue(), sqrt(dataValue));
    }

    TEST(Interface_TestSuite, DirectConstructInterface)
    {
        // Arrange
        const double dataValue = 3.0;

        // Act
        const auto iTestObjSqrt = SymplektObjectInterface<ITestClass>(TestClassSqrtImpl(dataValue));

        // Assert
        EXPECT_DOUBLE_EQ(iTestObjSqrt->GetValue(), dataValue);
        EXPECT_DOUBLE_EQ(iTestObjSqrt->ProcessValue(), sqrt(dataValue));
    }

    TEST(Interface_TestSuite, DirectNewConstructInterface)
    {
        // Arrange
        const double dataValue = 3.0;

        // Act
        const auto iTestObjSqrt = SymplektObjectInterface<ITestClass>(new TestClassSqrtImpl(dataValue));

        // Assert
        EXPECT_DOUBLE_EQ(iTestObjSqrt->GetValue(), dataValue);
        EXPECT_DOUBLE_EQ(iTestObjSqrt->ProcessValue(), sqrt(dataValue));
    }

} // Symplektis::UnitTests