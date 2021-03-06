/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include <algorithm>

// The following include is necessary on Win32 platforms to set up necessary macro definitions.
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

#include "core/macros.h"
#include "core/base/Lock.h"
#include "core/base/Thread.h"
#include "core/wrapper/DisposalService.h"
#include "hesperia/data/Constants.h"
#include "hesperia/threeD/TransformGroup.h"

namespace hesperia {
    namespace threeD {

        using namespace core::base;
        using namespace data::environment;

        TransformGroup::TransformGroup() :
                Node(NodeDescriptor()),
                m_translation(),
                m_rotation(),
                m_scaling(Point3(1, 1, 1)),
                m_listOfChildrenMutex(),
                m_listOfChildren() {}

        TransformGroup::TransformGroup(const NodeDescriptor &nodeDescriptor) :
                Node(nodeDescriptor),
                m_translation(),
                m_rotation(),
                m_scaling(Point3(1, 1, 1)),
                m_listOfChildrenMutex(),
                m_listOfChildren() {}

        TransformGroup::~TransformGroup() {
            deleteAllChildren();
        }

        void TransformGroup::render(const RenderingConfiguration &renderingConfiguration) const {
            Lock l(m_listOfChildrenMutex);

            // Render if unnamed or not disabled.
            if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                glPushMatrix();
                {
                    // Translate the model.
                    glTranslated(m_translation.getX(), m_translation.getY(), m_translation.getZ());

                    // Rotate the model using DEG (m_rotation is in RAD!).
                    glRotated(m_rotation.getX()*180.0 / data::Constants::PI, 1, 0, 0);
                    glRotated(m_rotation.getY()*180.0 / data::Constants::PI, 0, 1, 0);
                    glRotated(m_rotation.getZ()*180.0 / data::Constants::PI, 0, 0, 1);

                    // Scale the model.
                    glScaled(m_scaling.getX(), m_scaling.getY(), m_scaling.getZ());

                    // Draw all existing children.
                    vector<Node*>::const_iterator it = m_listOfChildren.begin();
                    while (it != m_listOfChildren.end()) {
                        const Node *n = (*it++);
                        if (n != NULL) {
                            n->render(renderingConfiguration);
                        }
                    }
                }
                glPopMatrix();
            }
        }

        void TransformGroup::setTranslation(const Point3 &t) {
            m_translation = t;
        }

        Point3 TransformGroup::getTranslation() const {
            return m_translation;
        }

        void TransformGroup::setRotation(const Point3 &r) {
            m_rotation = r;
        }

        Point3 TransformGroup::getRotation() const {
            return m_rotation;
        }

        void TransformGroup::setScaling(const Point3 &s) {
            m_scaling = s;
        }

        Point3 TransformGroup::getScaling() const {
            return m_scaling;
        }

        void TransformGroup::accept(TransformGroupVisitor &visitor) {
            visitor.visit(this);

            // Traverse all children.
            vector<Node*>::iterator it = m_listOfChildren.begin();
            while (it != m_listOfChildren.end()) {
                Node *n = (*it++);
                TransformGroup *tg = dynamic_cast<TransformGroup*>(n);
                if (tg != NULL) {
                    tg->accept(visitor);
                }
                else {
                    // Child is not a TransformGroup.
                    visitor.visit(n);
                }
            }
        }

        void TransformGroup::addChild(Node *c) {
            Lock l(m_listOfChildrenMutex);

            m_listOfChildren.push_back(c);
        }

        void TransformGroup::removeChild(Node *c) {
            Lock l(m_listOfChildrenMutex);

            if (c != NULL) {
                vector<Node*>::iterator result = find(m_listOfChildren.begin(), m_listOfChildren.end(), c);
                if (result != m_listOfChildren.end()) {
                    core::wrapper::DisposalService::getInstance().addDisposableForRegularRemoval(*result);
                    m_listOfChildren.erase(result);
                }
            }
        }

        void TransformGroup::deleteAllChildren() {
            Lock lc(m_listOfChildrenMutex);

            vector<Node*>::iterator it = m_listOfChildren.begin();
            while (it != m_listOfChildren.end()) {
                Node *n = (*it++);

                TransformGroup *tg = dynamic_cast<TransformGroup*>(n);
                if (tg != NULL) {
                    tg->deleteAllChildren();
                }
                else {
                    // Child is not a TransformGroup.

                    // Use disposal service for cleaning up.
                    core::wrapper::DisposalService::getInstance().addDisposableForRegularRemoval(n);
                }
            }

            // Clear regular node list.
            m_listOfChildren.clear();
        }

    }
} // hesperia::threeD
