/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef PLUGINS_ABSTRACTGLWIDGET_H_
#define PLUGINS_ABSTRACTGLWIDGET_H_

#include "core/base/Mutex.h"
#include "hesperia/data/environment/Point3.h"

#include "QtIncludes.h"

#include "plugins/PlugIn.h"

namespace plugins {

    using namespace std;

    /**
     * This class is the main class for an OpenGL-based visualization.
     * It provides free camera movements through the scene.
     */
    class AbstractGLWidget: public QGLWidget {

            Q_OBJECT

        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             */
            AbstractGLWidget(const AbstractGLWidget &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             */
            AbstractGLWidget& operator=(const AbstractGLWidget &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param plugIn Reference to the plugin to which this widget belongs.
             * @param prnt Pointer to the parental widget.
             */
            AbstractGLWidget(const PlugIn &plugIn, QWidget *prnt);

            virtual ~AbstractGLWidget();

            /**
             * This method is used to set the color of the background.
             *
             * @param c Color.
             */
            void setBackgroundColor(const hesperia::data::environment::Point3 &c);

            /**
             * This method can be overridden in subclasses to perform a
             * special setup.
             */
            virtual void setupOpenGL();

            /**
             * This method must be overridden in subclasses to setup the scene.
             */
            virtual void initScene() = 0;

            /**
             * This method must be overridden in subclasses to draw the scene.
             */
            virtual void drawScene() = 0;

        signals:
            void translationXChanged(double translationX);
            void translationXChanged(float translationX);
            void translationYChanged(double translationY);
            void translationYChanged(float translationY);
            void translationZChanged(double translationZ);
            void translationZChanged(float translationZ);
            void phiChanged(double phi);
            void phiChanged(float phi);
            void thetaChanged(double theta);
            void thetaChanged(float theta);
            void epsilonChanged(double epsilon);
            void epsilonChanged(float epsilon);


        public slots:

            /**
             * These methods provide signals for changing the translation values.
             */
            void setTranslationX(double translationX);
            void setTranslationY(double translationY);
            void setTranslationZ(double translationZ);

            void setPhi(double phi);
            void setTheta(double theta);
            void setEpsilon(double epsilon);


        protected:
            /**
             * This method returns the plugin to which this widget belongs.
             *
             * @return PlugIn to which this widget belongs.
             */
            const PlugIn& getPlugIn() const;

        private:
            static bool m_isGLUTinitialized;
            const PlugIn &m_plugIn;
            float m_translationX;
            float m_translationY;
            float m_translationZ;
            float m_rotationX;
            float m_rotationY;
            float m_rotationZ;
            float m_pitchX;
            float m_pitchY;
            float m_pitchZ;
            float m_scale;
            float m_phi;
            float m_theta;
            float m_epsilon;
            float m_mouseSensitivity;
            float m_keySensitivity;
            int32_t m_mouseX;
            int32_t m_mouseY;
            int32_t m_mouseButton;

            core::base::Mutex m_backgroundColorMutex;
            hesperia::data::environment::Point3 m_backgroundColor;

            virtual void initializeGL();

            virtual void paintGL();

            virtual void resizeGL(int32_t w, int32_t h);

            virtual void keyPressEvent(QKeyEvent * e);

            virtual void mousePressEvent(QMouseEvent * e);

            virtual void mouseMoveEvent(QMouseEvent * e);
    };

} // plugins

#endif /*PLUGINS_ABSTRACTGLWIDGET_H_*/
