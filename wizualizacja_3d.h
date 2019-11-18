#ifndef WIZUALIZACJA_3D_H
#define WIZUALIZACJA_3D_H

#include "opengl_framework.h"

class wizualizacja_3d : public opengl_framework{
  public:
    wizualizacja_3d(QWidget* parent);

  protected:
    void inicjalizuj_opengl_framework();
    void renderuj();
};

#endif // WIZUALIZACJA_3D_H
