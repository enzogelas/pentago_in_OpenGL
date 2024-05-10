// ----------------------------------------------------------------------------
// main.cpp
//
//  Created on: 10 oct 2023
//      Author: Enzo GELAS
//        Mail: enzo.gelas@telecom-paris.fr
//
// ----------------------------------------------------------------------------

#define _USE_MATH_DEFINES

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const static float pi = std::acos(-1.0);

GLuint woodTexture;
GLuint metalTexture;
GLuint plasticTexture;

float angleTopLeft = 0.0f;
float angleTopRight = 0.0f;
float angleBottomLeft = 0.0f;
float angleBottomRight = 0.0f;

float angleToReach = 0.0f;
bool change = true; // A boolean that prevent changing module when one is turning


/*The code that represents cubes and that rotates them*/
enum Box {E, P1, P2}; // Empty, Player 1, Player 2
Box gameGrid[6][6] = {{E}}; //The grid 6x6 that represent game at every moment
Box turn = P1;

void printGameGrid(){
  for (int i=0; i<6; i++){
    for (int j=0; j<6; j++){
      std::cout << gameGrid[i][j] ;
    }
    std::cout << "\n" ;
  }
}

void printHelp() {
  std::cout << "How to play" << std::endl; 
  std::cout << "Use directional arrows to move" << std::endl;
  std::cout << "Use O and P to rotate areas (O = counter-clockwise; P = clockwise)" << std::endl;
  std::cout << "Use Enter to place a cube" << std::endl;
  std::cout << "Press H to print this help" << std::endl;
  std::cout << "Press Esc to quit the game" << std::endl;
  std::cout << " " << std::endl;
}

void rotate(int i, int j){ // i and j are used to select whose corner rotate
  Box top = gameGrid[0+i][1+j];
  gameGrid[0+i][1+j] = gameGrid[1+i][2+j];
  gameGrid[1+i][2+j] = gameGrid[2+i][1+j];
  gameGrid[2+i][1+j] = gameGrid[1+i][0+j];
  gameGrid[1+i][0+j] = top;

  Box topLeft = gameGrid[0+i][0+j];
  gameGrid[0+i][0+j] = gameGrid[0+i][2+j];
  gameGrid[0+i][2+j] = gameGrid[2+i][2+j];
  gameGrid[2+i][2+j] = gameGrid[2+i][0+j];
  gameGrid[2+i][0+j] = topLeft;
}

void rotateTopLeft(){rotate(0,0);}
void rotateTopRight(){rotate(0,3);}
void rotateBottomLeft(){rotate(3,0);}
void rotateBottomRight(){rotate(3,3);}

void counterRotate(int i, int j){ // i and j are used to select whose corner rotate
  Box top = gameGrid[0+i][1+j];
  gameGrid[0+i][1+j] = gameGrid[1+i][0+j];
  gameGrid[1+i][0+j] = gameGrid[2+i][1+j];
  gameGrid[2+i][1+j] = gameGrid[1+i][2+j];
  gameGrid[1+i][2+j] = top;

  Box topLeft = gameGrid[0+i][0+j];
  gameGrid[0+i][0+j] = gameGrid[2+i][0+j];
  gameGrid[2+i][0+j] = gameGrid[2+i][2+j];
  gameGrid[2+i][2+j] = gameGrid[0+i][2+j];
  gameGrid[0+i][2+j] = topLeft;
}

void counterRotateTopLeft(){counterRotate(0,0);}
void counterRotateTopRight(){counterRotate(0,3);}
void counterRotateBottomLeft(){counterRotate(3,0);}
void counterRotateBottomRight(){counterRotate(3,3);}

/* Function to test if a players won*/
bool playerWin(Box box) {
  for (int i=0; i<6; i++){
    int count = 0;
    for (int j=0; j<6; j++){
      if (gameGrid[i][j] == box){
        count++;
        if (count == 5) return true;
      }
      else count=0;
    }
  }
  for (int i=0; i<6; i++){
    int count = 0;
    for (int j=0; j<6; j++){
      if (gameGrid[j][i] == box){
        count++;
        if (count == 5) return true;
      }
      else count=0;
    }
  }
  return false;
}

bool player1Win(){return playerWin(P1);}
bool player2Win(){return playerWin(P2);}

/* To differentiate adding cubes and rotating game parts*/
enum Mode {AddCube, RotatingGame};
Mode mode = AddCube;
int nextCubeRow = 0;
int nextCubeColumn = 0;

// Falcultative
float translationTopLeft = 0.0f;
float translationTopRight = 0.0f;
float translationBottomLeft = 0.0f;
float translationBottomRight = 0.0f;

bool rotation = false;
bool counterRotation = false;

enum Corner {TL, TR, BL, BR};
Corner selectedCorner;

// Ending of game declaration *********************************************************************************************************************************************************
// Window parameters
GLFWwindow *g_window = nullptr;

// GPU objects
GLuint g_program = 0; // A GPU program contains at least a vertex shader and a fragment shader

// Basic camera model
class Camera {
public:
  inline float getFov() const { return m_fov; }
  inline void setFoV(const float f) { m_fov = f; }
  inline float getAspectRatio() const { return m_aspectRatio; }
  inline void setAspectRatio(const float a) { m_aspectRatio = a; }
  inline float getNear() const { return m_near; }
  inline void setNear(const float n) { m_near = n; }
  inline float getFar() const { return m_far; }
  inline void setFar(const float n) { m_far = n; }
  inline void setPosition(const glm::vec3 &p) { m_pos = p; }
  inline void move(float deltaX, float deltaY){m_pos.x += deltaX; m_pos += deltaY;}
  inline glm::vec3 getPosition() { return m_pos; }

  inline glm::mat4 computeViewMatrix() const {
    return glm::lookAt(m_pos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  }

  // Returns the projection matrix stemming from the camera intrinsic parameter.
  inline glm::mat4 computeProjectionMatrix() const {
    return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
  }

private:
  glm::vec3 m_pos = glm::vec3(0, 0, 0);
  float m_fov = 45.f;        // Field of view, in degrees
  float m_aspectRatio = 1.f; // Ratio between the width and the height of the image
  float m_near = 0.1f; // Distance before which geometry is excluded from the rasterization process
  float m_far = 10.f; // Distance after which the geometry is excluded from the rasterization process
};
Camera g_camera;

// The Vertex Shader
const GLchar *vshaderSource = R"(
#version 330 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;

out vec3 fPosition;
out vec3 vertexNormal;
out vec2 fragTexCoord;


uniform mat4 viewMat;
uniform mat4 projMat;

uniform mat4 modelMatrix;
uniform mat4 normalsMatrix;

void main() {
    vertexNormal = vec3(normalsMatrix * vec4(inPosition, 1.0));
    fPosition = vec3(modelMatrix * vec4(inPosition, 1.0));
    fragTexCoord = inTexCoord;

    gl_Position = projMat * viewMat * vec4(fPosition, 1.0);
}
)";

// The Fragment Shader
const GLchar *fshaderSource = R"(
#version 330 core
uniform vec3 camPos;

in vec3 fPosition;
in vec3 vertexNormal; 
in vec2 fragTexCoord;
uniform sampler2D textureSampler;
uniform vec3 objectColor;

out vec4 fragColor; // output color of the fragment

void main() {
  vec3 objectTexture = vec3(texture(textureSampler, fragTexCoord));
  fragColor = vec4(objectTexture+0.6*objectColor, 1.0);
}

)";


// The class that will create and render Spheres
class Mesh {
  public:
  void initMesh(); 
  void renderMesh(); 
  static std::shared_ptr<Mesh> genGame(); // Generate a corner of the game
  static std::shared_ptr<Mesh> genSquare(); // Generate a square
  static std::shared_ptr<Mesh> genCube(); // Generate a cube

  private:
  std::vector<float> m_vertexPositions;
  std::vector<float> m_vertexColors;
  std::vector<float> m_vertexNormals;
  std::vector<unsigned int> m_triangleIndices;
  std::vector<float> m_vertexTextureCoords;
  GLuint m_vao = 0;
  GLuint m_posVbo = 0;
  GLuint m_normalVbo = 0;
  GLuint m_colVbo = 0;
  GLuint m_ibo = 0;
  GLuint m_texCoordVbo = 0;
};


// Declaration of the sphere that will represent planets
// And the orbital and rotation angles that will be modified to do the animation
std::shared_ptr<Mesh> gameMesh;
std::shared_ptr<Mesh> squareMesh;
std::shared_ptr<Mesh> cubeMesh;

std::shared_ptr<Mesh> Mesh::genGame(){
  // Generate vertex positions and triangle indices for a sphere
  std::shared_ptr<Mesh> gameMesh = std::make_shared<Mesh>();

  // Generate the vertex positions for the game piece
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
        float x = static_cast<float>(i)/7.0;
        float z = static_cast<float>(j)/7.0;

        gameMesh->m_vertexPositions.push_back(x-0.5);
        gameMesh->m_vertexPositions.push_back(0);
        gameMesh->m_vertexPositions.push_back(z-0.5);

        gameMesh->m_vertexNormals.push_back(0);
        gameMesh->m_vertexNormals.push_back(1);
        gameMesh->m_vertexNormals.push_back(0);

        gameMesh->m_vertexTextureCoords.push_back(x);
        gameMesh->m_vertexTextureCoords.push_back(z);
    }
  }

  // Generate triangle indices to form the piece
  for (size_t i = 0; i < 7; i++) {
    for (size_t j = 0; j < 7; j++) {
      if(i%2==0 || j%2==0){
        size_t p1 = i * (8) + j;
        size_t p2 = p1 + 1;
        size_t p3 = (i + 1) * (8) + j;
        size_t p4 = p3 + 1;

        
        if(i==0 && j==0){
          gameMesh->m_triangleIndices.push_back(p2);
          gameMesh->m_triangleIndices.push_back(p4);
          gameMesh->m_triangleIndices.push_back(p3);
        }else if(i==6 && j==0){
          gameMesh->m_triangleIndices.push_back(p1);
          gameMesh->m_triangleIndices.push_back(p2);
          gameMesh->m_triangleIndices.push_back(p4);
        }else if(i==0 && j==6){
          gameMesh->m_triangleIndices.push_back(p1);
          gameMesh->m_triangleIndices.push_back(p4);
          gameMesh->m_triangleIndices.push_back(p3);
        }else if(i==6 && j==6){
          gameMesh->m_triangleIndices.push_back(p1);
          gameMesh->m_triangleIndices.push_back(p2);
          gameMesh->m_triangleIndices.push_back(p3);
        }else{
          gameMesh->m_triangleIndices.push_back(p1);
          gameMesh->m_triangleIndices.push_back(p2);
          gameMesh->m_triangleIndices.push_back(p3);

          gameMesh->m_triangleIndices.push_back(p2);
          gameMesh->m_triangleIndices.push_back(p4);
          gameMesh->m_triangleIndices.push_back(p3);
        }
      }
    }
  }

  gameMesh -> initMesh();  // Initialize the mesh

  return gameMesh;
}

std::shared_ptr<Mesh> Mesh::genSquare(){
  // Generate vertex positions and triangle indices for a sphere
  std::shared_ptr<Mesh> squareMesh = std::make_shared<Mesh>();

  squareMesh->m_vertexPositions.push_back(-0.5);
  squareMesh->m_vertexPositions.push_back(0);
  squareMesh->m_vertexPositions.push_back(-0.5);

  squareMesh->m_vertexPositions.push_back(-0.5);
  squareMesh->m_vertexPositions.push_back(0);
  squareMesh->m_vertexPositions.push_back(0.5);

  squareMesh->m_vertexPositions.push_back(0.5);
  squareMesh->m_vertexPositions.push_back(0);
  squareMesh->m_vertexPositions.push_back(-0.5);

  squareMesh->m_vertexPositions.push_back(0.5);
  squareMesh->m_vertexPositions.push_back(0);
  squareMesh->m_vertexPositions.push_back(0.5);

  squareMesh->m_vertexTextureCoords.push_back(0);
  squareMesh->m_vertexTextureCoords.push_back(0);

  squareMesh->m_vertexTextureCoords.push_back(0);
  squareMesh->m_vertexTextureCoords.push_back(1);

  squareMesh->m_vertexTextureCoords.push_back(1);
  squareMesh->m_vertexTextureCoords.push_back(1);

  squareMesh->m_vertexTextureCoords.push_back(1);
  squareMesh->m_vertexTextureCoords.push_back(0);

  squareMesh->m_triangleIndices.push_back(0);
  squareMesh->m_triangleIndices.push_back(1);
  squareMesh->m_triangleIndices.push_back(2);

  squareMesh->m_triangleIndices.push_back(1);
  squareMesh->m_triangleIndices.push_back(3);
  squareMesh->m_triangleIndices.push_back(2);

  squareMesh -> initMesh();  // Initialize the mesh

  return squareMesh;
}

std::shared_ptr<Mesh> Mesh::genCube(){
  // Generate vertex positions and triangle indices for a sphere
  std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>();


  cubeMesh->m_vertexPositions.push_back(-0.5);
  cubeMesh->m_vertexPositions.push_back(0.5);
  cubeMesh->m_vertexPositions.push_back(-0.5);

  cubeMesh->m_vertexPositions.push_back(-0.5);
  cubeMesh->m_vertexPositions.push_back(0.5);
  cubeMesh->m_vertexPositions.push_back(0.5);

  cubeMesh->m_vertexPositions.push_back(0.5);
  cubeMesh->m_vertexPositions.push_back(0.5);
  cubeMesh->m_vertexPositions.push_back(-0.5);

  cubeMesh->m_vertexPositions.push_back(0.5);
  cubeMesh->m_vertexPositions.push_back(0.5);
  cubeMesh->m_vertexPositions.push_back(0.5);

  cubeMesh->m_vertexPositions.push_back(-0.5);
  cubeMesh->m_vertexPositions.push_back(-0.5);
  cubeMesh->m_vertexPositions.push_back(-0.5);

  cubeMesh->m_vertexPositions.push_back(-0.5);
  cubeMesh->m_vertexPositions.push_back(-0.5);
  cubeMesh->m_vertexPositions.push_back(0.5);

  cubeMesh->m_vertexPositions.push_back(0.5);
  cubeMesh->m_vertexPositions.push_back(-0.5);
  cubeMesh->m_vertexPositions.push_back(-0.5);

  cubeMesh->m_vertexPositions.push_back(0.5);
  cubeMesh->m_vertexPositions.push_back(-0.5);
  cubeMesh->m_vertexPositions.push_back(0.5);

  cubeMesh->m_vertexTextureCoords.push_back(0);
  cubeMesh->m_vertexTextureCoords.push_back(0);

  cubeMesh->m_vertexTextureCoords.push_back(1);
  cubeMesh->m_vertexTextureCoords.push_back(0);

  cubeMesh->m_vertexTextureCoords.push_back(1);
  cubeMesh->m_vertexTextureCoords.push_back(0);

  cubeMesh->m_vertexTextureCoords.push_back(0);
  cubeMesh->m_vertexTextureCoords.push_back(0);

  cubeMesh->m_vertexTextureCoords.push_back(0);
  cubeMesh->m_vertexTextureCoords.push_back(1);

  cubeMesh->m_vertexTextureCoords.push_back(1);
  cubeMesh->m_vertexTextureCoords.push_back(1);

  cubeMesh->m_vertexTextureCoords.push_back(1);
  cubeMesh->m_vertexTextureCoords.push_back(1);

  cubeMesh->m_vertexTextureCoords.push_back(0);
  cubeMesh->m_vertexTextureCoords.push_back(1);

  cubeMesh->m_triangleIndices.push_back(0);
  cubeMesh->m_triangleIndices.push_back(1);
  cubeMesh->m_triangleIndices.push_back(2);

  cubeMesh->m_triangleIndices.push_back(1);
  cubeMesh->m_triangleIndices.push_back(3);
  cubeMesh->m_triangleIndices.push_back(2);

  cubeMesh->m_triangleIndices.push_back(4);
  cubeMesh->m_triangleIndices.push_back(5);
  cubeMesh->m_triangleIndices.push_back(6);

  cubeMesh->m_triangleIndices.push_back(5);
  cubeMesh->m_triangleIndices.push_back(7);
  cubeMesh->m_triangleIndices.push_back(6);
  
  cubeMesh->m_triangleIndices.push_back(0);
  cubeMesh->m_triangleIndices.push_back(4);
  cubeMesh->m_triangleIndices.push_back(1);

  cubeMesh->m_triangleIndices.push_back(1);
  cubeMesh->m_triangleIndices.push_back(4);
  cubeMesh->m_triangleIndices.push_back(5);

  cubeMesh->m_triangleIndices.push_back(1);
  cubeMesh->m_triangleIndices.push_back(5);
  cubeMesh->m_triangleIndices.push_back(3);

  cubeMesh->m_triangleIndices.push_back(3);
  cubeMesh->m_triangleIndices.push_back(5);
  cubeMesh->m_triangleIndices.push_back(7);

  cubeMesh->m_triangleIndices.push_back(3);
  cubeMesh->m_triangleIndices.push_back(7);
  cubeMesh->m_triangleIndices.push_back(2);

  cubeMesh->m_triangleIndices.push_back(2);
  cubeMesh->m_triangleIndices.push_back(7);
  cubeMesh->m_triangleIndices.push_back(6);

  cubeMesh->m_triangleIndices.push_back(0);
  cubeMesh->m_triangleIndices.push_back(2);
  cubeMesh->m_triangleIndices.push_back(4);

  cubeMesh->m_triangleIndices.push_back(2);
  cubeMesh->m_triangleIndices.push_back(6);
  cubeMesh->m_triangleIndices.push_back(4);
  
  cubeMesh -> initMesh();  // Initialize the mesh

  return cubeMesh;
}

void Mesh::initMesh(){
  // Create and initialize the GPU buffers for the mesh
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // Generate a GPU buffer to store the positions, the normals and the U,V coordinates of the vertices
  glGenBuffers(1, &m_posVbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_posVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertexPositions.size(), m_vertexPositions.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  glGenBuffers(1, &m_normalVbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_normalVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertexNormals.size(), m_vertexNormals.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  glEnableVertexAttribArray(1);

  glGenBuffers(1, &m_texCoordVbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_texCoordVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertexTextureCoords.size(), m_vertexTextureCoords.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
  glEnableVertexAttribArray(3);

  // Create an index buffer object (IBO) if you have triangle indices
  if (!m_triangleIndices.empty()) {
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_triangleIndices.size(), m_triangleIndices.data(), GL_STATIC_DRAW);
  }

  // Unbind the VAO
  glBindVertexArray(0);
}

void Mesh::renderMesh() {
  // Bind the VAO and draw the mesh
  glBindVertexArray(m_vao);

  if (m_ibo != 0) {
    // If you have an index buffer (IBO), use glDrawElements
    glDrawElements(GL_TRIANGLES, m_triangleIndices.size(), GL_UNSIGNED_INT, 0);
  } else {
    // If you're using just vertex data (no IBO), use glDrawArrays
    glDrawArrays(GL_TRIANGLES, 0, m_vertexPositions.size() / 3);
  }

  // Unbind the VAO
  glBindVertexArray(0);
}

void addCubeForPlayer1(int i, int j){
  gameGrid[i][j] = P1;
}

void addCubeForPlayer2(int i, int j){
  gameGrid[i][j] = P2;
}

GLuint loadTextureFromFileToGPU(const std::string &filename) {
  int width, height, numComponents;
  // Loading the image in CPU memory using stb_image
  unsigned char *data = stbi_load(
    filename.c_str(),
    &width, &height,
    &numComponents, // 1 for a 8 bit grey-scale image, 3 for 24bits RGB image, 4 for 32bits RGBA image
    0);

  GLuint texID;
  if (data) {
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (numComponents == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else if (numComponents == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else if (numComponents == 1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    }

    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cerr << "Failed to load texture: " << filename << std::endl;
  }
  // Free useless CPU memory
  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D, 0); // unbind the texture

  return texID;
}

// Executed each time the window is resized. Adjust the aspect ratio and the rendering viewport to the current window.
void windowSizeCallback(GLFWwindow* window, int width, int height) {
  g_camera.setAspectRatio(static_cast<float>(width)/static_cast<float>(height));
  glViewport(0, 0, (GLint)width, (GLint)height); // Dimension of the rendering region in the window
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    if (key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, true); // Closes the application if the escape key is pressed
    } else if (key == GLFW_KEY_O) {
      if(mode == RotatingGame){
        if(selectedCorner == TL) rotateTopLeft();
        if(selectedCorner == TR) rotateTopRight();
        if(selectedCorner == BL) rotateBottomLeft();
        if(selectedCorner == BR) rotateBottomRight();
        angleToReach = pi/2;
        rotation = true;
        change = false;
        mode = AddCube;
        
        nextCubeRow = 0;
        nextCubeColumn = 0;
      } else std::cout << "Please place your cube before" << std::endl;
    } else if (key == GLFW_KEY_P) {
      if(mode == RotatingGame){
        if(selectedCorner == TL) counterRotateTopLeft();
        if(selectedCorner == TR) counterRotateTopRight();
        if(selectedCorner == BL) counterRotateBottomLeft();
        if(selectedCorner == BR) counterRotateBottomRight();
        angleToReach = -pi/2;
        counterRotation = true;
        change = false;
        mode = AddCube;
        
        nextCubeRow = 0;
        nextCubeColumn = 0;
      } else std::cout << "Please place your cube before" << std::endl;
    } else if (key == GLFW_KEY_UP){
      if (mode == AddCube) nextCubeRow = std::max(0,nextCubeRow-1);
      
      if(change){
        if(selectedCorner == BL) selectedCorner = TL;
        if(selectedCorner == BR) selectedCorner = TR;
      }
    } else if (key == GLFW_KEY_RIGHT){
      if (mode == AddCube) nextCubeColumn = std::min(5,nextCubeColumn+1);

      if(change){
        if(selectedCorner == TL) selectedCorner = TR;
        if(selectedCorner == BL) selectedCorner = BR;
      }
    } else if (key == GLFW_KEY_LEFT){
      if (mode == AddCube) nextCubeColumn = std::max(0,nextCubeColumn-1);

      if(change){
        if(selectedCorner == TR) selectedCorner = TL;
        if(selectedCorner == BR) selectedCorner = BL;
      }
    } else if (key == GLFW_KEY_DOWN){
      if (mode == AddCube) nextCubeRow = std::min(5,nextCubeRow+1);

      if(change){
        if(selectedCorner == TL) selectedCorner = BL;
        if(selectedCorner == TR) selectedCorner = BR;
      }
    } else if (key == GLFW_KEY_V){
      if(player1Win()) std::cout << "Player 1 wins" << std::endl;
      if(player2Win()) std::cout << "Player 2 wins" << std::endl;
      if(!player1Win() && !player2Win()) std::cout << "No one win" << std::endl;
      
    } else if (key == GLFW_KEY_ENTER) { 
      if(mode == AddCube) {
        if (turn == P1 && gameGrid[nextCubeRow][nextCubeColumn] != P2){
          gameGrid[nextCubeRow][nextCubeColumn] = P1;
          turn = P2;
          mode = RotatingGame;
          
          nextCubeRow = -1;
          nextCubeColumn = -1;
        } else if (turn == P2 && gameGrid[nextCubeRow][nextCubeColumn] != P1){
          gameGrid[nextCubeRow][nextCubeColumn] = P2;
          turn = P1;
          mode = RotatingGame;
          
          nextCubeRow = -1;
          nextCubeColumn = -1;
        }
      }
    } else if (key == GLFW_KEY_H) {
      printHelp();
    }
  }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
}

void errorCallback(int error, const char *desc) {
  std::cout <<  "Error " << error << ": " << desc << std::endl;
}

void initGLFW() {
  glfwSetErrorCallback(errorCallback);

  // Initialize GLFW, the library responsible for window management
  if(!glfwInit()) {
    std::cerr << "ERROR: Failed to init GLFW" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // Before creating the window, set some option flags
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // Create the window
  g_window = glfwCreateWindow(
    1024, 768,
    "Pentago",
    nullptr, nullptr);
  if(!g_window) {
    std::cerr << "ERROR: Failed to open window" << std::endl;
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  // Load the OpenGL context in the GLFW window using GLAD OpenGL wrangler
  glfwMakeContextCurrent(g_window);
  glfwSetWindowSizeCallback(g_window, windowSizeCallback);
  glfwSetKeyCallback(g_window, keyCallback);
  glfwSetCursorPosCallback(g_window, cursorPosCallback);
}

void initOpenGL() {
  // Load extensions for modern OpenGL
  if(!gladLoadGL()) {
    std::cerr << "ERROR: Failed to initialize OpenGL context" << std::endl;
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  glCullFace(GL_BACK); // Specifies the faces to cull (here the ones pointing away from the camera)
  glEnable(GL_CULL_FACE); // Enables face culling (based on the orientation defined by the CW/CCW enumeration).
  glDepthFunc(GL_LESS);   // Specify the depth test for the z-buffer
  glEnable(GL_DEPTH_TEST);      // Enable the z-buffer test in the rasterization
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // specify the background color, used any time the framebuffer is cleared
}

// Loads the content of an ASCII file in a standard C++ string
std::string file2String(const std::string &filename) {
  std::ifstream t(filename.c_str());
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

// Loads and compile a shader, before attaching it to a program
void loadShader(GLuint program, GLenum type, const std::string &shaderFilename) {
  GLuint shader = glCreateShader(type); // Create the shader, e.g., a vertex shader to be applied to every single vertex of a mesh
  std::string shaderSourceString = file2String(shaderFilename); // Loads the shader source from a file to a C++ string
  const GLchar *shaderSource = (const GLchar *)shaderSourceString.c_str(); // Interface the C++ string through a C pointer
  glShaderSource(shader, 1, &shaderSource, NULL); // load the vertex shader code
  glCompileShader(shader);
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR in compiling " << shaderFilename << "\n\t" << infoLog << std::endl;
  }
  glAttachShader(program, shader);
  glDeleteShader(shader);
}

void initGPUprogram() {
  // TODO: set shader variables, textures, etc.
  g_program = glCreateProgram(); // create a GPU program object
  GLuint vshader = glCreateShader(GL_VERTEX_SHADER); // create a vertex shader object
  GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER); // create a fragment shader object

  glShaderSource(vshader, 1, &vshaderSource, NULL); // load the vertex shader source codes
  glShaderSource(fshader, 1, &fshaderSource, NULL); // load the fragment shader

  glCompileShader(vshader); // compile the vertex shader
  glCompileShader(fshader); // compile the fragment shader

  glAttachShader(g_program, vshader); // attach the vertex shader
  glAttachShader(g_program, fshader); // attach the fragment shader
  // ... load/compile/attach other shaders, e.g., GL_FRAGMENT_SHADER

  glLinkProgram(g_program);
  glUseProgram(g_program);

  glDeleteShader(vshader); // delete the shader object; once linked, no lorger need
  glDeleteShader(fshader);
  // the GPU program is ready to handle your data ...
}

// Define your mesh(es) in the CPU memory
void initCPUgeometry() {

}

void initGPUgeometry() {

}

void initCamera() {
  int width, height;
  glfwGetWindowSize(g_window, &width, &height);
  g_camera.setAspectRatio(static_cast<float>(width)/static_cast<float>(height));

  g_camera.setPosition(glm::vec3(0.0, 1.0, 1.0));
  g_camera.setNear(0.1);
  g_camera.setFar(100.0f);
}

void init() {
  initGLFW();
  initOpenGL();
  initCPUgeometry();
  initGPUprogram();
  initGPUgeometry();
  initCamera();
}

void clear() {
  glDeleteProgram(g_program);

  glfwDestroyWindow(g_window);
  glfwTerminate();
}


void rotate(float & angle){
  if(angle < pi/2){
    angle += pi/1000;
  }else{
    rotation = false;
    change = true;
    angle = 0.0;
    angleToReach = 0.0;
  }
}

void counterRotate(float & angle){
  if(angle > -pi/2){
    angle -= pi/1000;
  }else{
    counterRotation = false;
    change = true;
    angle = 0.0;
    angleToReach = 0.0;
  }
}


float rotateToTranslate(float x){
  float y = fabs(fabs(x) - pi/4);
  return 0.1*(1-4/pi*y);
}


float cubeAngle(float pieceAngle){
  if (pieceAngle == 0.0) return 0.0;
  else if (pieceAngle > 0) return pieceAngle-pi/2;
  else return pieceAngle+pi/2;
}

// The main rendering call
void render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Erase the color and z buffers.

  const glm::mat4 viewMatrix = g_camera.computeViewMatrix();
  const glm::mat4 projMatrix = g_camera.computeProjectionMatrix();

  glUniformMatrix4fv(glGetUniformLocation(g_program, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMatrix)); // compute the view matrix of the camera and pass it to the GPU program
  glUniformMatrix4fv(glGetUniformLocation(g_program, "projMat"), 1, GL_FALSE, glm::value_ptr(projMatrix)); // compute the projection matrix of the camera and pass it to the GPU program

  const glm::vec3 camPosition = g_camera.getPosition();
  glUniform3f(glGetUniformLocation(g_program, "camPos"), camPosition[0], camPosition[1], camPosition[2]);

  if(rotation){
    if (selectedCorner == TL) rotate(angleTopLeft);
    if (selectedCorner == TR) rotate(angleTopRight);
    if (selectedCorner == BL) rotate(angleBottomLeft);
    if (selectedCorner == BR) rotate(angleBottomRight);
  }

  if(counterRotation){
    if (selectedCorner == TL) counterRotate(angleTopLeft);
    if (selectedCorner == TR) counterRotate(angleTopRight);
    if (selectedCorner == BL) counterRotate(angleBottomLeft);
    if (selectedCorner == BR) counterRotate(angleBottomRight);
  }

  
  translationTopLeft = rotateToTranslate(angleTopLeft);
  translationTopRight = rotateToTranslate(angleTopRight);
  translationBottomLeft = rotateToTranslate(angleBottomLeft);
  translationBottomRight = rotateToTranslate(angleBottomRight);
  

  glm::mat4 identity = glm::scale(glm::mat4(1.0f), glm::vec3(1.0,1.0,1.0));

  glm::mat4 topLeft = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25,1.0/28,-0.25)) 
                  * glm::translate(glm::mat4(1.0f), glm::vec3(-translationTopLeft,0.0,-translationTopLeft))
                  * glm::rotate(glm::mat4(1.0f), angleTopLeft, glm::vec3(0.0,1.0,0.0))
                  * glm::scale(glm::mat4(1.0f), glm::vec3(0.5,0.5,0.5));
  
  glm::mat4 topRight = glm::translate(glm::mat4(1.0f), glm::vec3(0.25,1.0/28,-0.25)) 
                  * glm::translate(glm::mat4(1.0f), glm::vec3(translationTopRight,0.0,-translationTopRight))
                  * glm::rotate(glm::mat4(1.0f), angleTopRight, glm::vec3(0.0,1.0,0.0))
                  * glm::scale(glm::mat4(1.0f), glm::vec3(0.5,0.5,0.5));

  glm::mat4 bottomLeft = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25,1.0/28,0.25)) 
                  * glm::translate(glm::mat4(1.0f), glm::vec3(-translationBottomLeft,0.0,translationBottomLeft))
                  * glm::rotate(glm::mat4(1.0f), angleBottomLeft, glm::vec3(0.0,1.0,0.0))
                  * glm::scale(glm::mat4(1.0f), glm::vec3(0.5,0.5,0.5));
  
  glm::mat4 bottomRight = glm::translate(glm::mat4(1.0f), glm::vec3(0.25,1.0/28,0.25)) 
                  * glm::translate(glm::mat4(1.0f), glm::vec3(translationBottomRight,0.0,translationBottomRight))
                  * glm::rotate(glm::mat4(1.0f), angleBottomRight, glm::vec3(0.0,1.0,0.0))
                  * glm::scale(glm::mat4(1.0f), glm::vec3(0.5,0.5,0.5));


  // Render the first Square (top left)
  glBindTexture(GL_TEXTURE_2D, woodTexture); // Bind a wood texture
  glUniform1i(glGetUniformLocation(g_program, "textureSampler"), 0);

  glm::vec3 colorTopLeft = glm::vec3(0.0,0.0,0.0);
  if(selectedCorner == TL && mode==RotatingGame) colorTopLeft = glm::vec3(0.0, 1.0, 1.0);
  glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(colorTopLeft));
  glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(topLeft));

  gameMesh -> renderMesh();

  // Render the second Square (top right)
  glm::vec3 colorTopRight = glm::vec3(0.0,0.0,0.0);
  if(selectedCorner == TR && mode==RotatingGame) colorTopRight = glm::vec3(0.0, 1.0, 1.0);
  glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(colorTopRight));
  glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(topRight));

  gameMesh -> renderMesh();

  // Render the third Square (bottom left)
  glm::vec3 colorBottomLeft = glm::vec3(0.0,0.0,0.0);
  if(selectedCorner == BL && mode==RotatingGame) colorBottomLeft = glm::vec3(0.0, 1.0, 1.0);
  glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(colorBottomLeft));
  glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(bottomLeft));

  gameMesh -> renderMesh();

  // Render the fourth Square (bottom right)
  glm::vec3 colorBottomRight = glm::vec3(0.0,0.0,0.0);
  if(selectedCorner == BR && mode==RotatingGame) colorBottomRight = glm::vec3(0.0, 1.0, 1.0);
  glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(colorBottomRight));
  glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(bottomRight));
  gameMesh -> renderMesh();

  glBindTexture(GL_TEXTURE_2D, plasticTexture); // Bind a wood texture
  glUniform1i(glGetUniformLocation(g_program, "textureSampler"), 0);

  // Top Left
  for (int i=0; i<3; i++){
    for (int j=0; j<3; j++){ // j is the x coordinate ; i is the z coordinate
      glm::mat4 cubeMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25, 0, -0.25))
                          * glm::translate(glm::mat4(1.0f), glm::vec3(-translationTopLeft,0.0,-translationTopLeft))
                          * glm::rotate(glm::mat4(1.0f), cubeAngle(angleTopLeft), glm::vec3(0.0,1.0,0.0))
                          * glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(4*j - 4)/28, 1.0/28, static_cast<float>(4*i -4)/28))
                          * glm::scale(glm::mat4(1.0f), glm::vec3(1.0/14, 1.0/14, 1.0/14));
    
      if(gameGrid[i][j] == P1){
        glm::vec3 cubeColor = glm::vec3(0.0,0.5,1.0);
        glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
        glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
        cubeMesh -> renderMesh();
      } else if (gameGrid[i][j] == P2) {
        glm::vec3 cubeColor = glm::vec3(1.0,0.5,0.0);
        glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
        glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
        cubeMesh -> renderMesh();
      }
    }
  }

  //Bottom Left
  for (int i=3; i<6; i++){
    for (int j=0; j<3; j++){ // j is the x coordinate ; i is the z coordinate
      glm::mat4 cubeMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25, 0, 0.25))
                          * glm::translate(glm::mat4(1.0f), glm::vec3(-translationBottomLeft,0.0,translationBottomLeft))
                          * glm::rotate(glm::mat4(1.0f), cubeAngle(angleBottomLeft), glm::vec3(0.0,1.0,0.0))
                          * glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(4*j - 4)/28, 1.0/28, static_cast<float>(4*(i-3) -4)/28))
                          * glm::scale(glm::mat4(1.0f), glm::vec3(1.0/14, 1.0/14, 1.0/14));
    
      if(gameGrid[i][j] == P1){
        glm::vec3 cubeColor = glm::vec3(0.0,0.5,1.0);
        glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
        glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
        cubeMesh -> renderMesh();
      } else if (gameGrid[i][j] == P2) {
        glm::vec3 cubeColor = glm::vec3(1.0,0.5,0.0);
        glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
        glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
        cubeMesh -> renderMesh();
      }
    }
  }

  //Top Right
  for (int i=0; i<3; i++){
    for (int j=3; j<6; j++){ // j is the x coordinate ; i is the z coordinate
      glm::mat4 cubeMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.25, 0, -0.25))
                          * glm::translate(glm::mat4(1.0f), glm::vec3(translationTopRight,0.0,-translationTopRight))
                          * glm::rotate(glm::mat4(1.0f), cubeAngle(angleTopRight), glm::vec3(0.0,1.0,0.0))
                          * glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(4*(j-3) - 4)/28, 1.0/28, static_cast<float>(4*i -4)/28))
                          * glm::scale(glm::mat4(1.0f), glm::vec3(1.0/14, 1.0/14, 1.0/14));
    
      if(gameGrid[i][j] == P1){
        glm::vec3 cubeColor = glm::vec3(0.0,0.5,1.0);
        glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
        glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
        cubeMesh -> renderMesh();
      } else if (gameGrid[i][j] == P2) {
        glm::vec3 cubeColor = glm::vec3(1.0,0.5,0.0);
        glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
        glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
        cubeMesh -> renderMesh();
      }
    }
  }

  // Bottom Right
  for (int i=3; i<6; i++){
    for (int j=3; j<6; j++){ // j is the x coordinate ; i is the z coordinate
      glm::mat4 cubeMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.25, 0, 0.25))
                          * glm::translate(glm::mat4(1.0f), glm::vec3(translationBottomRight,0.0,translationBottomRight))
                          * glm::rotate(glm::mat4(1.0f), cubeAngle(angleBottomRight), glm::vec3(0.0,1.0,0.0))
                          * glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(4*(j-3) - 4)/28, 1.0/28, static_cast<float>(4*(i-3) -4)/28))
                          * glm::scale(glm::mat4(1.0f), glm::vec3(1.0/14, 1.0/14, 1.0/14));
    
      if(gameGrid[i][j] == P1){
        glm::vec3 cubeColor = glm::vec3(0.0,0.5,1.0);
        glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
        glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
        cubeMesh -> renderMesh();
      } else if (gameGrid[i][j] == P2) {
        glm::vec3 cubeColor = glm::vec3(1.0,0.5,0.0);
        glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
        glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
        cubeMesh -> renderMesh();
      }
    }
  }
  if(nextCubeRow != -1){
    if(nextCubeRow<3 && nextCubeColumn<3){
      glm::mat4 cubeMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25, 0, -0.25))
                            * glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(4*nextCubeColumn - 4)/28, 1.0/28, static_cast<float>(4*nextCubeRow -4)/28))
                            * glm::scale(glm::mat4(1.0f), glm::vec3(1.0/14, 1.0/14, 1.0/14));
      glm::vec3 cubeColor = glm::vec3(0.0,1.0,1.0);
          glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
          glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
          cubeMesh -> renderMesh();
    }

    if(nextCubeRow>=3 && nextCubeColumn<3){
      glm::mat4 cubeMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25, 0, 0.25))
                            * glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(4*nextCubeColumn - 4)/28, 1.0/28, static_cast<float>(4*(nextCubeRow-3) -4)/28))
                            * glm::scale(glm::mat4(1.0f), glm::vec3(1.0/14, 1.0/14, 1.0/14));
      glm::vec3 cubeColor = glm::vec3(0.0,1.0,1.0);
          glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
          glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
          cubeMesh -> renderMesh();
    }

    if(nextCubeRow<3 && nextCubeColumn>=3){
      glm::mat4 cubeMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.25, 0, -0.25))
                            * glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(4*(nextCubeColumn-3) - 4)/28, 1.0/28, static_cast<float>(4*nextCubeRow -4)/28))
                            * glm::scale(glm::mat4(1.0f), glm::vec3(1.0/14, 1.0/14, 1.0/14));
      glm::vec3 cubeColor = glm::vec3(0.0,1.0,1.0);
          glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
          glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
          cubeMesh -> renderMesh();
    }

    if(nextCubeRow>=3 && nextCubeColumn>=3){
      glm::mat4 cubeMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.25, 0, 0.25))
                            * glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(4*(nextCubeColumn-3) - 4)/28, 1.0/28, static_cast<float>(4*(nextCubeRow-3) -4)/28))
                            * glm::scale(glm::mat4(1.0f), glm::vec3(1.0/14, 1.0/14, 1.0/14));
      glm::vec3 cubeColor = glm::vec3(0.0,1.0,1.0);
          glUniform3fv(glGetUniformLocation(g_program, "objectColor"), 1, glm::value_ptr(cubeColor));
          glUniformMatrix4fv(glGetUniformLocation(g_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeMatrix));
          cubeMesh -> renderMesh();
    }
  }
}

int main(int argc, char ** argv) {
  init(); // Your initialization code (user interface, OpenGL states, scene with geometry, material, lights, etc)
  woodTexture = loadTextureFromFileToGPU("C:/pentago_OpenGL/tex/wood.png");
  metalTexture = loadTextureFromFileToGPU("C:/pentago_OpenGL/tex/metal.jpg");
  plasticTexture = loadTextureFromFileToGPU("C:/pentago_OpenGL/tex/wood2.jpg");

  squareMesh = Mesh::genSquare();
  cubeMesh = Mesh::genCube();
  gameMesh = Mesh::genGame(); 

  printHelp();

  while(!glfwWindowShouldClose(g_window)) {
    render();
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f); 
    glfwSwapBuffers(g_window);
    glfwPollEvents();
  }
  clear();
  return EXIT_SUCCESS;
}
