#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include <SOIL.h>

#include <QOpenGLExtraFunctions>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "obiekt_loader.h"

class model_loader : protected QOpenGLExtraFunctions{
  public:
    model_loader();
    void wczytaj(const GLchar* sciezka);
    void rysuj(shader_loader *shader);

  private:
    vector<obiekt_loader> _meshes;
    string _folder;
    vector<tekstura> _zaladowane_tekstury;

    void wczytaj_model(string sciezka);
    void przetwarzaj_korzen(aiNode* korzen, const aiScene* scena);
    obiekt_loader przetwarzaj_meshes(aiMesh* mesh_obiekt, const aiScene* scena);
    vector<tekstura> wczytaj_teksture_material(aiMaterial* mat, aiTextureType typ, string nazwa_typu);
};

#endif // MODEL_LOADER_H
