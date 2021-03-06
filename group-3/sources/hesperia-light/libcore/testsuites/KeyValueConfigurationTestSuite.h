/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef CORE_KEYVALUECONFIGURATIONTESTSUITE_H_
#define CORE_KEYVALUECONFIGURATIONTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <sstream>
#include <string>

#include "core/base/KeyValueConfiguration.h"
#include "core/exceptions/Exceptions.h"

using namespace std;
using namespace core::base;
using namespace core::exceptions;

class ConfigurationTest : public CxxTest::TestSuite {
    public:
        void testReadSimpleData() {
            stringstream s;
            s << "Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415" << endl
            << "Section1.key4=3.1415" << endl;

            KeyValueConfiguration kvc;
            s >> kvc;
            stringstream s2;
            s2 << kvc;

            string key1 = "";
            int32_t key2 = 0;
            float key3 = 0;
            double key4 = 0;

            key1 = kvc.getValue<string>("Section1.key1");
            key2 = kvc.getValue<int>("Section1.key2");
            key3 = kvc.getValue<float>("Section1.key3");
            key4 = kvc.getValue<double>("Section1.key4");

            TS_ASSERT(key1 == "String1");
            TS_ASSERT(key2 == 10);
            TS_ASSERT_DELTA(key3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);

            stringstream s3;
            s3 << "section1.key1=String1" << endl
            << "section1.key2=10" << endl
            << "section1.key3=3.1415" << endl
            << "section1.key4=3.1415" << endl;
            TS_ASSERT(s3.str() == s2.str());
        }

        void testReadSimpleDataCopyConstructor() {
            stringstream s;
            s << "Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415" << endl
            << "Section1.key4=3.1415" << endl;

            KeyValueConfiguration kvcOriginal;
            s >> kvcOriginal;

            KeyValueConfiguration kvc(kvcOriginal);
            stringstream s2;
            s2 << kvc;

            string key1 = "";
            int32_t key2 = 0;
            float key3 = 0;
            double key4 = 0;

            key1 = kvc.getValue<string>("Section1.key1");
            key2 = kvc.getValue<int>("Section1.key2");
            key3 = kvc.getValue<float>("Section1.key3");
            key4 = kvc.getValue<double>("Section1.key4");

            TS_ASSERT(key1 == "String1");
            TS_ASSERT(key2 == 10);
            TS_ASSERT_DELTA(key3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);

            stringstream s3;
            s3 << "section1.key1=String1" << endl
            << "section1.key2=10" << endl
            << "section1.key3=3.1415" << endl
            << "section1.key4=3.1415" << endl;
            TS_ASSERT(s3.str() == s2.str());
        }

        void testReadSimpleDataAssignmentOperator() {
            stringstream s;
            s << "Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415" << endl
            << "Section1.key4=3.1415" << endl;

            KeyValueConfiguration kvcOriginal;
            s >> kvcOriginal;

            KeyValueConfiguration kvc;
            kvc = kvcOriginal;
            stringstream s2;
            s2 << kvc;

            string key1 = "";
            int32_t key2 = 0;
            float key3 = 0;
            double key4 = 0;

            key1 = kvc.getValue<string>("Section1.key1");
            key2 = kvc.getValue<int>("Section1.key2");
            key3 = kvc.getValue<float>("Section1.key3");
            key4 = kvc.getValue<double>("Section1.key4");

            TS_ASSERT(key1 == "String1");
            TS_ASSERT(key2 == 10);
            TS_ASSERT_DELTA(key3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);

            stringstream s3;
            s3 << "section1.key1=String1" << endl
            << "section1.key2=10" << endl
            << "section1.key3=3.1415" << endl
            << "section1.key4=3.1415" << endl;
            TS_ASSERT(s3.str() == s2.str());
        }

        void testReadCommentedData() {
            stringstream s;
            s << "#Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415 # Comment" << endl
            << "Section3.key4=3.1415" << endl;

            KeyValueConfiguration kvc;
            s >> kvc;
            stringstream s2;
            s2 << kvc;

            string key1 = "";
            int32_t key2 = 0;
            float key3 = 0;
            double key4 = 0;

            bool key1NotFound = false;
            try {
                key1 = kvc.getValue<string>("Section1.key1");
            } catch (ValueForKeyNotFoundException &vfknfe) {
                TS_ASSERT(vfknfe.getMessage() == "Value for key 'Section1.key1' not found.");
                key1NotFound = true;
            }
            key2 = kvc.getValue<int>("Section1.key2");
            key3 = kvc.getValue<float>("Section1.key3");
            key4 = kvc.getValue<double>("Section3.key4");

            TS_ASSERT(key1NotFound);
            TS_ASSERT(key2 == 10);
            TS_ASSERT_DELTA(key3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);

            stringstream s3;
            s3 << "section1.key2=10" << endl
            << "section1.key3=3.1415" << endl
            << "section3.key4=3.1415" << endl;
            TS_ASSERT(s3.str() == s2.str());
        }

        void testReadCommentedDataCaseInsensitive() {
            stringstream s;
            s << "#Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415 # Comment" << endl
            << "Section3.key4=3.1415" << endl;

            KeyValueConfiguration kvc;
            s >> kvc;

            string key1 = "";
            int32_t key2 = 0;
            float key3 = 0;
            double key4 = 0;

            bool key1NotFound = false;
            try {
                key1 = kvc.getValue<string>("SeCtIoN1.key1");
            } catch (ValueForKeyNotFoundException &vfknfe) {
                TS_ASSERT(vfknfe.getMessage() == "Value for key 'SeCtIoN1.key1' not found.");
                key1NotFound = true;
            }
            key2 = kvc.getValue<int>("Section1.kEY2");
            key3 = kvc.getValue<float>("SeCtIoN1.key3");
            key4 = kvc.getValue<double>("Section3.KeY4");

            TS_ASSERT(key1NotFound);
            TS_ASSERT(key2 == 10);
            TS_ASSERT_DELTA(key3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);
        }

        void testReadCommentedDataSubset() {
            stringstream s;
            s << "#Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415 # Comment" << endl
            << "Section3.key4=3.1415" << endl;

            KeyValueConfiguration kvcOriginal;
            s >> kvcOriginal;

            KeyValueConfiguration kvc = kvcOriginal.getSubsetForSection("Section3");
            double key4 = 0;

            key4 = kvc.getValue<double>("Section3.KeY4");

            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);
        }

        void testReadCommentedDataSubsetWithRemovingLeadingSection() {
            stringstream s;
            s << "#main.Section1.key1=String1" << endl
            << "main.Section1.key2=10" << endl
            << "main.Section1.key3=3.1415 # Comment" << endl
            << "main.Section3.key4=3.1415" << endl;

            KeyValueConfiguration kvcOriginal;
            s >> kvcOriginal;

            KeyValueConfiguration kvc = kvcOriginal.getSubsetForSection("main.Section3");
            double key4 = 0;

            key4 = kvc.getValue<double>("main.Section3.KeY4");

            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);

            KeyValueConfiguration kvc_2 = kvcOriginal.getSubsetForSectionRemoveLeadingSectionName("main.");

            double key4_2 = 0;

            key4_2 = kvc_2.getValue<double>("Section3.KeY4");

            TS_ASSERT_DELTA(key4_2, 3.1415, 1e-3);
        }
};

#endif /*CORE_KEYVALUECONFIGURATIONTESTSUITE_H_*/
