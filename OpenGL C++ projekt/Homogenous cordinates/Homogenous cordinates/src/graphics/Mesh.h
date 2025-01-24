#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;

	static std::vector<struct Vertex> genList(float* vertices, int noVertices);
	static std::vector<struct Vertex> genList(float* vertices, int noVertices, glm::vec3 singleColor);
};
typedef struct Vertex Vertex;

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO;

	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	void render(Shader shader);

	void cleanup();

private:
	unsigned int VBO, EBO;

	void setup();
};

#endif 

