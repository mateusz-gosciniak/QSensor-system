#include <model_loader.h>

model_loader::model_loader(){

}

void model_loader::wczytaj(const GLchar* sciezka){
    this->wczytaj_model(sciezka);
}

void model_loader::rysuj(shader_loader *shader){
    for(GLuint i = 0; i < this->_meshes.size(); i++)
        this->_meshes[i].rysuj(shader);
}

void model_loader::wczytaj_model(string sciezka){
    Assimp::Importer importer;
    const aiScene* scena = importer.ReadFile(sciezka, aiProcess_Triangulate | aiProcess_FlipUVs);
    this->_folder = sciezka.substr(0, sciezka.find_last_of('\\'));
    this->przetwarzaj_korzen(scena->mRootNode, scena);
}

void model_loader::przetwarzaj_korzen(aiNode* korzen, const aiScene* scena){
    for(GLuint i = 0; i < korzen->mNumMeshes; i++){
        aiMesh* mesh_obiekt = scena->mMeshes[korzen->mMeshes[i]];
        this->_meshes.push_back(this->przetwarzaj_meshes(mesh_obiekt, scena));
    }

    for(GLuint i = 0; i < korzen->mNumChildren; i++){
        this->przetwarzaj_korzen(korzen->mChildren[i], scena);
    }
}

obiekt_loader model_loader::przetwarzaj_meshes(aiMesh* mesh_obiekt, const aiScene* scena){
    vector<wierzcholek> vertices;
    vector<GLuint> indices;
    vector<tekstura> textures;

    for(GLuint i = 0; i < mesh_obiekt->mNumVertices; i++){
        wierzcholek vertex;
        glm::vec3 vector;

        vector.x = mesh_obiekt->mVertices[i].x;
        vector.y = mesh_obiekt->mVertices[i].y;
        vector.z = mesh_obiekt->mVertices[i].z;
        vertex._position = vector;

        vector.x = mesh_obiekt->mNormals[i].x;
        vector.y = mesh_obiekt->mNormals[i].y;
        vector.z = mesh_obiekt->mNormals[i].z;
        vertex._normal = vector;

        if(mesh_obiekt->mTextureCoords[0]){
            glm::vec2 vec;
            vec.x = mesh_obiekt->mTextureCoords[0][i].x;
            vec.y = mesh_obiekt->mTextureCoords[0][i].y;
            vertex._tex_coords = vec;
        }
        else
            vertex._tex_coords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for(GLuint i = 0; i < mesh_obiekt->mNumFaces; i++){
        aiFace face = mesh_obiekt->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if(mesh_obiekt->mMaterialIndex){
        aiMaterial* material = scena->mMaterials[mesh_obiekt->mMaterialIndex];

        vector<tekstura> diffuseMaps = this->wczytaj_teksture_material(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        vector<tekstura> specularMaps = this->wczytaj_teksture_material(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    obiekt_loader nowy;
    nowy.wczytaj(vertices, indices, textures);
    return nowy;
}

vector<tekstura> model_loader::wczytaj_teksture_material(aiMaterial* mat, aiTextureType typ, string nazwa_typu){
    initializeOpenGLFunctions();

    vector<tekstura> textures;
    for(GLuint i = 0; i < mat->GetTextureCount(typ); i++){
        aiString str;
        mat->GetTexture(typ, i, &str);
        GLboolean pomin = false;
        for(GLuint j = 0; j < _zaladowane_tekstury.size(); j++){
            if(_zaladowane_tekstury[j]._sciezka == str){
                textures.push_back(_zaladowane_tekstury[j]);
                pomin = true;
                break;
            }
        }
        if(!pomin){
            tekstura texture;

            string nazwa_pliku = string(str.C_Str());
            nazwa_pliku = this->_folder + '\\' + nazwa_pliku;
            GLuint id_tekstury;
            glGenTextures(1, &id_tekstury);
            int szerokosc,wysokosc;
            unsigned char* obraz = SOIL_load_image(nazwa_pliku.c_str(), &szerokosc, &wysokosc, 0, SOIL_LOAD_RGB);

            glBindTexture(GL_TEXTURE_2D, id_tekstury);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, szerokosc, wysokosc, 0, GL_RGB, GL_UNSIGNED_BYTE, obraz);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
            SOIL_free_image_data(obraz);

            texture._id = id_tekstury;

            texture._typ = nazwa_typu;
            texture._sciezka = str;
            textures.push_back(texture);
            this->_zaladowane_tekstury.push_back(texture);
        }
    }
    return textures;
}
