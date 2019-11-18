#include "wizualizacja_3d.h"

/// w zamyśle tutaj powinny być wczytywane modele wyświetlane na scenie

wizualizacja_3d::wizualizacja_3d(QWidget* parent) : opengl_framework(parent) {

}

void wizualizacja_3d::inicjalizuj_opengl_framework(){

}

void wizualizacja_3d::renderuj(){
    for(float i = -10; i <= 10; i += 5)
    {
     glBegin(GL_LINES);
        glColor3ub(150, 190, 150);
        glVertex3f(-10, 0, i);
        glVertex3f(10, 0, i);
        glVertex3f(i, 0,-10);
        glVertex3f(i, 0, 10);
     glEnd();
    }
}
