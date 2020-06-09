/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup mclib mclib
/// @{
#ifndef MC_TEST_H
#define MC_TEST_H

#include "McWinDLLApi.h"
#include "McTypedObject.h"
#include "McException.h"
#include "McString.h"

class McTestResult;

#undef mctestassert
/// Test CONDITION.  If false, report error and stop test.
#define mctestassert(CONDITION) { \
    if (!(CONDITION)) { \
        throw McTestFailureException(# CONDITION, __FILE__, __LINE__ ); \
    } \
}

/** If CONDITION is false, report error and stop test; include MESSAGE in
    failure report.

    You can use McString to include information at runtime, for example,
    \code
        mctestassert2(a == b, McString(0, "a = %d, b = %d", a, b));
    \endcode
  */
#define mctestassert2(CONDITION, MESSAGE) { \
    if (!(CONDITION)) { \
        throw McTestFailureException( \
                McString(# CONDITION) + " (" + (const char*)(MESSAGE) + ")", __FILE__, __LINE__ \
                ); \
    } \
}

/** A simple test framework that closely follows the xUnit approach.

    To run the unit test, pass '-test' to the product start script.
    You should run the tests after each compile.  Consider using
    test driven development (TDD): write a failing test case, get
    it to compile, make it pass, remove duplication, repeat.

\verbatim
    # write failing test
    make && ./product/bin/<start-script> -test # -> failure
    # write code to make the test pass
    make && ./product/bin/<start-script> -test # -> PASSED
    # repeat
\endverbatim

    To define tests, derive from McTest and provide member
    functions that should be named testX() and are defined using
    the macro MC_TEST().  You can use the script
    hxtest/makeTestClass to create a new test class.  Use
    mctestassert() to test conditions.  If a condition fails, the
    test is immediately stopped.  To manage the test fixture,
    setUp() is run before and tearDown() after each test.
    setUpTestModule() and tearDownTestModule() can be used to set
    up the global state of the test module before the first setUp()
    and clean up after the last tearDown().  See McTestTest.cpp for
    an example.

        - Unit test must be fast.  We want to run all of them after
          each compile.  A test is not a unit test if it touches
          the file system or communicates across a network.
        - Place test classes in the same package with the code to
          be tested.  This helps to keep code and tests in sync.
        - Declare test classes in a separate resource file
          test_hxmypackage.rc, using the 'testClass' command.
        - Postfix the name of test classes by 'Test', so that
          Visual Studio places them right beside the class tested.
          For example, the test class for McSomething is
          McSomethingTest.
        - Prefix all other test helper classes, for example with
          HxFake, HxMock, HxTesting, so that Visual Studio groups
          them separately from production classes.
 */
class MCLIB_API McTest : public McTypedObject {
    MC_HEADER(McTest);

  public:
    McTest();

    /// Called by a HxTestRunner to run the tests.
    void runTests(McTestResult* result);

  private:
    /// Internal use.
    void reportFailure(const char* name, const char* condition, const char* file, int line);

    /// Override in derived class to set up module before first setUp().
    virtual void setUpTestModule();

    /// Override in derived class to clean up after last tearDown().
    virtual void tearDownTestModule();

    /// Override in derived class to set up before each test.
    virtual void setUp();

    /// Override in derived class to clean up after each test.
    virtual void tearDown();

    /// Internal use.
    void reportUnexpectedException(const char* name, const char* what);

    /// Internal use.
    bool safeCallSetUpTestModule();

    /// Internal use.
    void runEachTest();

    /// Internal use.
    void safeCallTearDownTestModule();

    /// Internal use.
    void handleException(const char* testname);

    McTestResult* mResult;
};


/** Internally used by MC_TEST() and McTest.
  */
class MCLIB_API McTestRegistry {
    public:
        typedef void (McTest::*testFunction_t)();

        struct TestInfo {
            TestInfo() : name(0) {}

            TestInfo(const McTypeInfo* t, const char* n, testFunction_t f)
                : typeinfo(t), name(n), function(f)
            {
                McTestRegistry::addTest(this);
            }

            ~TestInfo() {
                McTestRegistry::removeTest(this);
            }

            const McTypeInfo* typeinfo;
            const char* name;
            testFunction_t function;
        };

        static void addTest(const TestInfo* test);

        static void removeTest(const TestInfo* test);

        static McDArray<const TestInfo*> getTests(const McTypeInfo* typeinfo);
};

/// Use to define test functions.
#define MC_TEST(CLASS, FUNCTION) \
McTestRegistry::TestInfo CLASS##__##FUNCTION##_test_info( \
          CLASS::getClassTypeId() \
        , # FUNCTION \
        , static_cast<McTestRegistry::testFunction_t>(&CLASS::FUNCTION)); \
\
void CLASS::FUNCTION


/** Internally used by McTest to report test failures.
  */
class McTestFailureException {
  public:
    McTestFailureException(const char* m, const char* f, int l)
        : message(m), file(f), line(l) {}

    McString message;
    const char* file;
    int line;
};

#endif

/// @}
