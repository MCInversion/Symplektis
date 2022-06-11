//#include "Symplekt_GeometryBase/Matrix4.h"
//#include "Symplekt_GeometryBase/Vector3.h"

//#include "Symplekt_UtilityGeneral/Assert.h"

#include "Symplekt_UtilityGeneral/InterfaceUtils.h"

#include <iostream>

// TODO:
// 
// DONE:
// - do something about asserts crashing the whole app
// - what to return and what to throw when calling Normalize ?

using namespace Symplektis::Util;

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

int main()
{
    const double dataValue = 3.0;
    const auto testObjSqr = TestClassSquareImpl(dataValue);
    const auto testObjSqrt = TestClassSqrtImpl(dataValue);

    const auto iTestObjSqr = SymplektObjectInterface<ITestClass>(testObjSqr);
    const auto iTestObjSqrt = SymplektObjectInterface<ITestClass>(testObjSqrt);

    std::cout << "testObjSqr->ProcessValue() = " << iTestObjSqr->ProcessValue() << "\n";    // out: 9.0
    std::cout << "testObjSqrt->ProcessValue() = " << iTestObjSqrt->ProcessValue() << "\n";   //  out: 1.73205080...

	return 0;
}