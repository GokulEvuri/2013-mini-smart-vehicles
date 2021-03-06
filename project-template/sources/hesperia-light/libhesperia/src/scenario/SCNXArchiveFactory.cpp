/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include <fstream>
#include <sstream>

#include "core/macros.h"
#include "core/base/Lock.h"
#include "core/wrapper/CompressionFactory.h"
#include "core/wrapper/DecompressedData.h"
#include "core/wrapper/DisposalService.h"
#include "core/exceptions/Exceptions.h"
#include "hesperia/scenario/SCNXArchiveFactory.h"
#include "hesperia/scenario/ScenarioFactory.h"
#include "hesperia/data/scenario/Scenario.h"

namespace hesperia {
    namespace scenario {

        using namespace std;
        using namespace core::base;
        using namespace core::exceptions;
        using namespace core::io;

        using namespace data::scenario;

        // Initialize singleton instance.
        Mutex SCNXArchiveFactory::m_singletonMutex;
        SCNXArchiveFactory* SCNXArchiveFactory::m_singleton = NULL;

        SCNXArchiveFactory::SCNXArchiveFactory() :
                m_mapOfSCNXArchives() {}

        SCNXArchiveFactory::~SCNXArchiveFactory() {
            map<string, SCNXArchive*, core::wrapper::StringComparator>::iterator it = m_mapOfSCNXArchives.begin();
            while (it != m_mapOfSCNXArchives.end()) {
                SCNXArchive *s = it->second;
                HESPERIA_CORE_DELETE_POINTER(s);
            }
            m_mapOfSCNXArchives.clear();

            clog << "SCNXArchiveFactory destroyed." << endl;
        }

        SCNXArchiveFactory& SCNXArchiveFactory::getInstance() {
            {
                Lock l(SCNXArchiveFactory::m_singletonMutex);
                if (SCNXArchiveFactory::m_singleton == NULL) {
                    SCNXArchiveFactory::m_singleton = new SCNXArchiveFactory();
                }
            }

            return (*SCNXArchiveFactory::m_singleton);
        }

        SCNXArchive& SCNXArchiveFactory::getSCNXArchive(const URL &url) throw (InvalidArgumentException) {
            if (!(url.isValid())) {
                HESPERIA_CORE_THROW_EXCEPTION(InvalidArgumentException, "URL is invalid.");
            }

            SCNXArchive *scnxArchive = NULL;

            // Try to find an existing SCNXArchive in the map using the URL as key.
            map<string, SCNXArchive*, core::wrapper::StringComparator>::iterator it = m_mapOfSCNXArchives.find(url.toString());
            if (it != m_mapOfSCNXArchives.end()) {
            	clog << "Found already constructed data structure." << endl;
                scnxArchive = it->second;
            }

            if (scnxArchive == NULL) {
                clog << "Creating new SCNXArchive from " << url.toString() << endl;

                string fileName = url.getResource();
                fstream fin(fileName.c_str(), ios::binary | ios::in);
                core::wrapper::DecompressedData *data = core::wrapper::CompressionFactory::getInstance().getContents(fin);
                fin.close();

                if (data != NULL) {
                    Scenario scenario;
                    istream *stream = data->getInputStreamFor("./scenario.scn");
                    if (stream != NULL) {
                        stringstream s;
                        char c;
                        while (stream->good()) {
                            stream->get(c);
                            s << c;
                        }

                        // Trying to parse the input.
                        scenario = ScenarioFactory::getInstance().getScenario(s.str());
                    } else {
                        HESPERIA_CORE_THROW_EXCEPTION(InvalidArgumentException, "Archive from the given URL does not contain a valid SCN file.");
                    }

                    // Create SCNXArchive.
                    scnxArchive = new SCNXArchive(scenario, data);

                    // Store SCNXArchive for further usage.
                    // Somehow, there seems to be a bug because the data structure got corrupt...
//                    m_mapOfSCNXArchives[url.toString()] = scnxArchive;
                }
                else {
                    HESPERIA_CORE_THROW_EXCEPTION(InvalidArgumentException, "URL could not be used to read input data.");
                }
            }

            return *scnxArchive;
        }

    }
} // hesperia::scenario
