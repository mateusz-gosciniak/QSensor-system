#include "opengl_framework.h"

static const GLchar* vertex_shader_zrodlo = {
    "#version 300 es                                                                      \n"
    "                                                                                     \n"
    "layout (location = 0) in vec3 position;                                              \n"
    "layout (location = 1) in vec3 normal;                                                \n"
    "layout (location = 2) in vec2 texCoord;                                              \n"
    "                                                                                     \n"
    "out vec2 TexCoord;                                                                   \n"
    "                                                                                     \n"
    "uniform mat4 model;                                                                  \n"
    "uniform mat4 widok;                                                                  \n"
    "uniform mat4 rzutowanie;                                                             \n"
    "                                                                                     \n"
    "void main()                                                                          \n"
    "{                                                                                    \n"
    "   gl_Position = rzutowanie * widok * model * vec4(position, 1.0f);                  \n"
    "   TexCoord = texCoord;                                                              \n"
    "}                                                                                    \n\0"
};

static const GLchar* fragment_shader_zrodlo = {
    "#version 300 es                                                                      \n"
    "                                                                                     \n"
    "in vec2 TexCoord;                                                                    \n"
    "                                                                                     \n"
    "out vec4 color;                                                                      \n"
    "                                                                                     \n"
    "uniform sampler2D texture_diffuse1;                                                  \n"
    "                                                                                     \n"
    "void main()                                                                          \n"
    "{                                                                                    \n"
    "   color = vec4(texture(texture_diffuse1, TexCoord));                                \n"
    "}                                                                                    \n\0"
};

opengl_framework::opengl_framework(QWidget *parent) : QOpenGLWidget(parent){
    _kamera = new kamera_loader();
    _shader = new shader_loader();

    _scena_model = new model_loader();
    _dron_model = new model_loader();
    _budynek_model = new model_loader();

    grabKeyboard();
}

void opengl_framework::keyPressEvent(QKeyEvent *key){
    switch(key->key()){
        case Qt::Key_W:{ _kamera->przemiesc(kamera_loader::KAMERA_PRZOD      ); }break;
        case Qt::Key_S:{ _kamera->przemiesc(kamera_loader::KAMERA_TYL        ); }break;
        case Qt::Key_A:{ _kamera->przemiesc(kamera_loader::KAMERA_LEWO       ); }break;
        case Qt::Key_D:{ _kamera->przemiesc(kamera_loader::KAMERA_PRAWO      ); }break;
        case Qt::Key_E:{ _kamera->przemiesc(kamera_loader::KAMERA_GORA       ); }break;
        case Qt::Key_Q:{ _kamera->przemiesc(kamera_loader::KAMERA_DOL        ); }break;
        case Qt::Key_Z:{ _kamera->przemiesc(kamera_loader::KAMERA_ROLL_PLUS  ); }break;
        case Qt::Key_X:{ _kamera->przemiesc(kamera_loader::KAMERA_ROLL_MINUS ); }break;
        case Qt::Key_C:{ _kamera->przemiesc(kamera_loader::KAMERA_PITCH_PLUS ); }break;
        case Qt::Key_V:{ _kamera->przemiesc(kamera_loader::KAMERA_PITCH_MINUS); }break;
        case Qt::Key_R:{ _kamera->przemiesc(kamera_loader::KAMERA_YAW_PLUS   ); }break;
        case Qt::Key_F:{ _kamera->przemiesc(kamera_loader::KAMERA_YAW_MINUS  ); }break;
    }
}

void opengl_framework::initializeGL(){
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    zmien_kolor_tla(0.4f,0.4f,0.4f,1.0f);
    _shader->wczytaj(vertex_shader_zrodlo, fragment_shader_zrodlo);

    /////////////////////////////////////////////////////////////////////////////////////////
    std::string folder = "C:\\Users\\gosci\\Desktop\\AIR VII\\CETA\\QSensor_system";     ///    UZUPEŁNIĆ ODPOWIEDNIO  ! ///
    /////////////////////////////////////////////////////////////////////////////////////////
    _dron_model->wczytaj((folder+"\\QSensor_system\\zasoby\\3D\\dron.obj").c_str());
    _scena_model->wczytaj((folder+"\\QSensor_system\\zasoby\\3D\\scena.obj").c_str());
    _budynek_model->wczytaj((folder+"\\QSensor_system\\zasoby\\3D\\budynek.obj").c_str());

    _aktualna_klatka = 0;
    pozycja polozenie_poczatkowe;
    polozenie_poczatkowe._x = 0.0f;
    polozenie_poczatkowe._y = 0.0f;
    polozenie_poczatkowe._z = 0.0f;
    polozenie_poczatkowe._ya = 0.0f;
    polozenie_poczatkowe._pi = 0.0f;
    polozenie_poczatkowe._ro = 0.0f;
    _wektor_pozycji.push_back(polozenie_poczatkowe);

    inicjalizuj_opengl_framework();
}

void opengl_framework::paintGL(){
    wyczysc_bufory();
    _shader->uzyj_program();

    glm::mat4 widok = _kamera->macierz_lookAt();
    glm::mat4 rzutowanie = glm::perspective(_kamera->_przyblizenie,(GLfloat)(this->width())/(GLfloat)(this->height()),0.1f,100.0f);

    _shader->_modelLoc = glGetUniformLocation(_shader->_program, "model");
    _shader->wczytaj_uniform(widok,"widok");
    _shader->wczytaj_uniform(rzutowanie,"rzutowanie");

    GLfloat x = _wektor_pozycji[_aktualna_klatka]._x;
    GLfloat y = _wektor_pozycji[_aktualna_klatka]._y;
    GLfloat z = _wektor_pozycji[_aktualna_klatka]._z;
    GLfloat ya = _wektor_pozycji[_aktualna_klatka]._ya;
    GLfloat pi = _wektor_pozycji[_aktualna_klatka]._pi;
    GLfloat ro = _wektor_pozycji[_aktualna_klatka]._ro;
    _shader->_model = glm::translate(_shader->_model, glm::vec3( x, y, z));
    _shader->_model = glm::rotate(_shader->_model, glm::radians(ya), glm::vec3(1.0f, 0.0f, 0.0f));
    _shader->_model = glm::rotate(_shader->_model, glm::radians(pi), glm::vec3(0.0f, 1.0f, 0.0f));
    _shader->_model = glm::rotate(_shader->_model, glm::radians(ro), glm::vec3(0.0f, 0.0f, 1.0f));
    _dron_model->rysuj(_shader);
    _shader->_model = glm::mat4();

    _scena_model->rysuj(_shader);
    _budynek_model->rysuj(_shader);

    renderuj();

    update();
}

void opengl_framework::inicjalizuj_opengl_framework(){

}

void opengl_framework::renderuj(){

}

void opengl_framework::wyczysc_bufory(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearBufferfv( GL_COLOR, 0, _kolor_tla);
}

void opengl_framework::zmien_kolor_tla(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    _kolor_tla[0] = r;
    _kolor_tla[1] = g;
    _kolor_tla[2] = b;
    _kolor_tla[3] = a;
}
