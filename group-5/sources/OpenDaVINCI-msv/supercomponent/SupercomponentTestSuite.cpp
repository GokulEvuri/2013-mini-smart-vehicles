/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/XmlFilePrinter.h>

int main() {
 return CxxTest::XmlFilePrinter().run();
}
#include "/home/msv/2013-mini-smart-vehicles/group-5/sources/OpenDaVINCI-msv/supercomponent/testsuites/SupercomponentClientModuleTestSuite.h"

static SupercomponentClientModuleTest suite_SupercomponentClientModuleTest;

static CxxTest::List Tests_SupercomponentClientModuleTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SupercomponentClientModuleTest( "/home/msv/2013-mini-smart-vehicles/group-5/sources/OpenDaVINCI-msv/supercomponent/testsuites/SupercomponentClientModuleTestSuite.h", 101, "SupercomponentClientModuleTest", suite_SupercomponentClientModuleTest, Tests_SupercomponentClientModuleTest );

static class TestDescription_SupercomponentClientModuleTest_testRegularConfiguration : public CxxTest::RealTestDescription {
public:
 TestDescription_SupercomponentClientModuleTest_testRegularConfiguration() : CxxTest::RealTestDescription( Tests_SupercomponentClientModuleTest, suiteDescription_SupercomponentClientModuleTest, 120, "testRegularConfiguration" ) {}
 void runTest() { suite_SupercomponentClientModuleTest.testRegularConfiguration(); }
} testDescription_SupercomponentClientModuleTest_testRegularConfiguration;

static class TestDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithID : public CxxTest::RealTestDescription {
public:
 TestDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithID() : CxxTest::RealTestDescription( Tests_SupercomponentClientModuleTest, suiteDescription_SupercomponentClientModuleTest, 199, "testConfigurationForModuleWithID" ) {}
 void runTest() { suite_SupercomponentClientModuleTest.testConfigurationForModuleWithID(); }
} testDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithID;

static class TestDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithIDEmptyConfiguration : public CxxTest::RealTestDescription {
public:
 TestDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithIDEmptyConfiguration() : CxxTest::RealTestDescription( Tests_SupercomponentClientModuleTest, suiteDescription_SupercomponentClientModuleTest, 274, "testConfigurationForModuleWithIDEmptyConfiguration" ) {}
 void runTest() { suite_SupercomponentClientModuleTest.testConfigurationForModuleWithIDEmptyConfiguration(); }
} testDescription_SupercomponentClientModuleTest_testConfigurationForModuleWithIDEmptyConfiguration;

#include <cxxtest/Root.cpp>
