#include "shader_loader.h"

shader_loader::shader_loader() : _program(0){

}

void shader_loader::wczytaj(const GLchar* vertex_shader_kod, const GLchar* fragment_shader_kod){
    initializeOpenGLFunctions();
    GLuint shader_wierzcholkow = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader_wierzcholkow, 1, &vertex_shader_kod, NULL);
    glCompileShader(shader_wierzcholkow);

    GLuint shader_fragmentow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_fragmentow, 1, &fragment_shader_kod, NULL);
    glCompileShader(shader_fragmentow);

    this->_program = glCreateProgram();
    glAttachShader(this->_program, shader_wierzcholkow);
    glAttachShader(this->_program, shader_fragmentow);
    glLinkProgram(this->_program);

    glDeleteShader(shader_wierzcholkow);
    glDeleteShader(shader_fragmentow);
}

void shader_loader::uzyj_program(){
    glUseProgram(this->_program);
}

void shader_loader::wczytaj_uniform(glm::mat4 uniform_macierz, const char *uniform_nazwa){
    glUniformMatrix4fv(glGetUniformLocation(this->_program, uniform_nazwa), 1, GL_FALSE, glm::value_ptr(uniform_macierz));
}
