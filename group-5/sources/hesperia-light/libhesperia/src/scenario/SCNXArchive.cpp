/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include <istream>
#include <sstream>

#include "core/macros.h"
#include "core/wrapper/Image.h"
#include "core/wrapper/ImageFactory.h"

#include "hesperia/scenario/SCNXArchive.h"
#include "hesperia/situation/SituationFactory.h"
#include "hesperia/data/situation/Situation.h"

namespace hesperia {
    namespace scenario {

        using namespace std;


        SCNXArchive::SCNXArchive(const data::scenario::Scenario &scenario, core::wrapper::DecompressedData *dd) :
                m_scenario(scenario),
                m_decompressedData(dd),
                m_aerialImage(NULL),
                m_heightImage(NULL) {

            // Try to read the images from the archive.
            stringstream sstr;
            sstr << "./" << scenario.getGround().getAerialImage().getFileName();
            istream *stream = m_decompressedData->getInputStreamFor(sstr.str());
            if (stream != NULL) {
                m_aerialImage = core::wrapper::ImageFactory::getInstance().getImage(*stream);
            }

            sstr.str("");
            sstr << "./" << scenario.getGround().getHeightImage().getFileName();
            stream = m_decompressedData->getInputStreamFor(sstr.str());
            if (stream != NULL) {
                m_heightImage = core::wrapper::ImageFactory::getInstance().getImage(*stream);
            }
        }

        SCNXArchive::~SCNXArchive() {
            HESPERIA_CORE_DELETE_POINTER(m_decompressedData);
            HESPERIA_CORE_DELETE_POINTER(m_aerialImage);
            HESPERIA_CORE_DELETE_POINTER(m_heightImage);
        }

        data::scenario::Scenario& SCNXArchive::getScenario() {
            return m_scenario;
        }

        core::wrapper::Image* SCNXArchive::getAerialImage() {
            return m_aerialImage;
        }

        core::wrapper::Image* SCNXArchive::getHeightImage() {
            return m_heightImage;
        }

        vector<data::scenario::ComplexModel*> SCNXArchive::getListOfGroundBasedComplexModels() const {
            const vector<data::scenario::Shape*> &listOfShapes = m_scenario.getGround().getSurroundings().getListOfShapes();
            vector<data::scenario::ComplexModel*> listOfComplexModels;

            vector<data::scenario::Shape*>::const_iterator it = listOfShapes.begin();
            while (it != listOfShapes.end()) {
                data::scenario::Shape *s = (*it++);
                if (s != NULL) {
                    data::scenario::ComplexModel *cm = dynamic_cast<data::scenario::ComplexModel*>(s);
                    if (cm != NULL) {
                        listOfComplexModels.push_back(cm);
                    }
                }
            }

            return listOfComplexModels;
        }

        vector<data::situation::Situation> SCNXArchive::getListOfSituations() const {
            vector<data::situation::Situation> listOfSituations;

            vector<string> listOfEntries = m_decompressedData->getListOfEntries();
            vector<string>::iterator it = listOfEntries.begin();
            while (it != listOfEntries.end()) {
                string entry = (*it++);
                if (entry.find("./situations/") != string::npos) {
                    char c = 0;
                    stringstream s;
                    istream* in = m_decompressedData->getInputStreamFor(entry);
                    if ( (in != NULL) && (in->good()) ) {
                        while ( (c = in->get()) != -1 ) {
                            s << c;
                        }
                        hesperia::data::situation::Situation sit = situation::SituationFactory::getInstance().getSituation(s.str());
                        listOfSituations.push_back(sit);
                    }
                }
            }
            return listOfSituations;
        }

        istream* SCNXArchive::getModelData(const string &modelFile) const {
            stringstream sstr;
            sstr << "./" << modelFile;
            return m_decompressedData->getInputStreamFor(sstr.str());
        }
    }
} // hesperia::scenario
