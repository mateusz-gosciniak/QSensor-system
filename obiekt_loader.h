#ifndef OBIEKT_LOADER_H
#define OBIEKT_LOADER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include <QOpenGLExtraFunctions>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/scene.h>

#include "shader_loader.h"

struct wierzcholek{
    glm::vec3 _position;
    glm::vec3 _normal;
    glm::vec2 _tex_coords;
};

struct tekstura{
    GLuint _id;
    string _typ;
    aiString _sciezka;
};

class obiekt_loader : protected QOpenGLExtraFunctions{
  public:
    vector<wierzcholek> _vertices;
    vector<GLuint> _indices;
    vector<tekstura> _textures;

    obiekt_loader();
    void wczytaj(vector<wierzcholek> vertices, vector<GLuint> indices, vector<tekstura> textures);
    void rysuj(shader_loader *shader);

  private:
    GLuint _VAO; // vertex array objects
    GLuint _VBO; // vertex buffer objects
    GLuint _EBO; // element buffer objects

    void init();
};

#endif // OBIEKT_LOADER_H
