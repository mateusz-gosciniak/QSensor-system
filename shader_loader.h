#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <QString>
#include <QOpenGLExtraFunctions>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class shader_loader : private QOpenGLExtraFunctions{
  public:
    GLuint _program;

    glm::mat4 _model;
    GLint _modelLoc;

    shader_loader();
    void wczytaj(const GLchar* vertex_shader_kod, const GLchar* fragment_shader_kod);
    void uzyj_program();
    void wczytaj_uniform(glm::mat4 uniform_macierz, const char *uniform_nazwa);
};

#endif // SHADER_LOADER_H
