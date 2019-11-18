#ifndef KAMERA_LOADER_H
#define KAMERA_LOADER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

class kamera_loader{
  public:
    glm::vec3 _pozycja;
    glm::vec3 _do_przodu;
    glm::vec3 _w_gore;
    glm::vec3 _w_prawo;
    glm::vec3 _celownik;

    glm::float32 _roll;
    glm::float32 _pitch;
    glm::float32 _yaw;

    glm::float32 _przyblizenie;
    glm::float32 _czulosc;

    enum STEROWANIE{
        KAMERA_PRZOD,
        KAMERA_TYL,
        KAMERA_GORA,
        KAMERA_DOL,
        KAMERA_PRAWO,
        KAMERA_LEWO,

        KAMERA_ROLL_MINUS,
        KAMERA_ROLL_PLUS,
        KAMERA_PITCH_MINUS,
        KAMERA_PITCH_PLUS,
        KAMERA_YAW_MINUS,
        KAMERA_YAW_PLUS
    };

    kamera_loader(glm::vec3    pozycja      = glm::vec3( 20.0f,  20.0f, -20.0f),
                  glm::vec3    do_przodu    = glm::vec3( 0.0f,  0.0f,  1.0f),
                  glm::vec3    w_gore       = glm::vec3( 0.0f,  15.0f,  0.0f),
                  glm::float32 roll         =   0.0f,
                  glm::float32 pitch        =   30.0f,
                  glm::float32 yaw          =   -45.0f,
                  glm::float32 przyblizenie =  45.0f,
                  glm::float32 czulosc      =   0.1f);

    glm::mat4 macierz_lookAt();
    void przemiesc(STEROWANIE argument);

  private:
    void aktualizacja_parametrow();
};

#endif // KAMERA_LOADER_H
