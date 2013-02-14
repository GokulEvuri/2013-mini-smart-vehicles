/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef CAMGEN_H_
#define CAMGEN_H_

#include <opencv/cv.h>

#include "core/SharedPointer.h"
#include "core/wrapper/Image.h"

#include "hesperia/base/ConferenceClientModule.h"
#include "hesperia/data/environment/EgoState.h"
#include "hesperia/io/camera/ImageGrabber.h"

#include "OpenGLGrabber.h"

namespace camgen {

    using namespace std;

    /**
     * This class is the camera server providing new camera images.
     */
    class CamGen : public hesperia::base::ConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            CamGen(const CamGen &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            CamGen& operator=(const CamGen &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            CamGen(const int32_t &argc, char **argv);

            virtual ~CamGen();

            virtual void setUp();

            virtual void tearDown();

            core::base::ModuleState::MODULE_EXITCODE body();

            /**
             * This method returns the singleton instance.
             *
             * @return The singleton pointer.
             */
            static CamGen& getInstance();

            /**
             * This method is called by OpenGL to draw the scene.
             */
            void display();

            /**
             * This method is called by OpenGL for resizing
             * the window.
             *
             * @param w new width.
             * @param h new height.
             */
            void resize(int32_t w, int32_t h);

            /**
             * This method processes any key event.
             *
             * @param key The pressed key.
             * @param x
             * @param y
             */
            void processKey(unsigned char key, int32_t x, int32_t y);

            /**
             * This method processes any mouse motion event.
             *
             * @param x Mouse's X position.
             * @param y Mouse's Y position.
             */
            void processMouseMotion(int32_t x, int32_t y);

            /**
             * This method processes any mouse event.
             *
             * @param button The pressed mouse button.
             * @param state GLUT_DOWN or GLUT_UP.
             * @param x Mouse's X position.
             * @param y Mouse's Y position.
             */
            void processMouseEvent(int32_t button, int32_t state, int32_t x, int32_t y);

        private:
            static CamGen* m_singleton;
            hesperia::data::environment::EgoState m_egoState;
            OpenGLGrabber *m_grabber;
            core::SharedPointer<core::wrapper::Image> m_image;

            float m_translationX;
            float m_translationY;
            float m_scale;
            float m_phi;
            float m_theta;
            float m_height;

            int32_t m_mouseX;
            int32_t m_mouseY;
            int32_t m_mouseButton;

            /**
             * This method initializes the GLUT subsystem.
             */
            void initGlut();

            /**
             * This method initializes the GL subsystem.
             */
            void initGL();

            /**
             * This method draws the three dimensional scene.
             */
            void drawScene();
    };

} // camgen

#endif /*CAMGEN_H_*/
