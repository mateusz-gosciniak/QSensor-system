#include "obiekt_loader.h"

obiekt_loader::obiekt_loader(){

}

void obiekt_loader::wczytaj(vector<wierzcholek> vertices, vector<GLuint> indices, vector<tekstura> textures){
    this->_vertices = vertices;
    this->_indices = indices;
    this->_textures = textures;
    this->init();
}

void obiekt_loader::rysuj(shader_loader *shader){
    GLuint diffuse = 1;
    GLuint specular = 1;

    for (GLuint i = 0; i < this->_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        stringstream ss;
        string numer;
        string nazwa = this->_textures[i]._typ;
        if (nazwa == "texture_diffuse") {
            ss << diffuse++;
        }else if (nazwa == "texture_specular") {
            ss << specular++;
        }
        numer == ss.str();

        glUniform1i(glGetUniformLocation(shader->_program, (nazwa + numer).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, this->_textures[i]._id);
    }

    glUniform1f(glGetUniformLocation(shader->_program, "material.shininess"), 16.0f);

    glBindVertexArray(this->_VAO);

    glUniformMatrix4fv( shader->_modelLoc , 1, GL_FALSE, glm::value_ptr( shader->_model ));

    glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    for (GLuint i = 0; i < this->_textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void obiekt_loader::init(){
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &this->_VAO);
    glGenBuffers(1, &this->_VBO);
    glGenBuffers(1, &this->_EBO);

    glBindVertexArray(this->_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
    glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(wierzcholek), &this->_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof(GLuint), &this->_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(wierzcholek), (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(wierzcholek), (GLvoid*)offsetof(wierzcholek, _normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(wierzcholek), (GLvoid*)offsetof(wierzcholek, _tex_coords));

    glBindVertexArray(0);
}
