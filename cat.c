#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
};

GLuint catVAO, catVBO, catEBO;
std::vector<Vertex> catVertices;
std::vector<GLuint> catIndices;
GLuint catTexture;

void loadCatModel() {
    // Load vertex positions and texture coordinates from file
    std::ifstream infile("cat_model.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        glm::vec3 pos;
        glm::vec2 texCoord;
        iss >> pos.x >> pos.y >> pos.z >> texCoord.x >> texCoord.y;
        catVertices.push_back({ pos, texCoord });
    }

    // Load indices from file
    infile.close();
    infile.open("cat_indices.txt");
    while (std::getline(infile, line)) {
        GLuint index;
        std::istringstream iss(line);
        iss >> index;
        catIndices.push_back(index);
    }

    // Create OpenGL buffers and upload data
    glGenVertexArrays(1, &catVAO);
    glBindVertexArray(catVAO);

    glGenBuffers(1, &catVBO);
    glBindBuffer(GL_ARRAY_BUFFER, catVBO);
    glBufferData(GL_ARRAY_BUFFER, catVertices.size() * sizeof(Vertex), &catVertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &catEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, catEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, catIndices.size() * sizeof(GLuint), &catIndices[0], GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    // Load texture
    glGenTextures(1, &catTexture);
    glBindTexture(GL_TEXTURE_2D, catTexture);

    int width, height;
    unsigned char* image = SOIL_load_image("cat_texture.png", &width, &height, 0, SOIL_LOAD_RGB);
    if (image == NULL) {
        std::cout << "Failed to load cat texture" << std::endl;
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawCat() {
    glBindVertexArray(catVAO);
    glBindTexture(GL_TEXTURE_2D, catTexture);
    glDrawElements(GL_TRIANGLES, catIndices.size(), GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

int main() {
