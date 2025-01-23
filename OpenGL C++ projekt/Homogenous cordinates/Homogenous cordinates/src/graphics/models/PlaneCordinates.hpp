#ifndef PLANECORDINATES_HPP
#define PLANECORDINATES_HPP

#include "../Model.h"

class PlaneCordinates : public Model {
public:
	glm::vec3 size;


	PlaneCordinates(glm::vec3 size)
		: size(size) {}

	void init() {
		int noVertices = 8;

		// vertex array
		float vertices[] = {
			// positions			     colors
			-1.0f,   0.003f,   -1.0f,	1.0f, 1.0f, 1.0f,
			 1.0f,   0.003f,   -1.0f,	1.0f, 1.0f, 1.0f,
			 1.0f,  -0.003f,   -1.0f,	1.0f, 1.0f, 1.0f,
			-1.0f,  -0.003f,   -1.0f,	1.0f, 1.0f, 1.0f,
										
			-0.003f,  0.5625f, -1.0f,	1.0f, 1.0f, 1.0f,
			 0.003f,  0.5625f, -1.0f,	1.0f, 1.0f, 1.0f,
			 0.003f, -0.5625f, -1.0f,	1.0f, 1.0f, 1.0f,
			-0.003f, -0.5625f, -1.0f,	1.0f, 1.0f, 1.0f
		};

		std::vector<unsigned int> indicies = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices), indicies));
	}

	void render(Shader shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, size);
		shader.setMat4("model", model);

		Model::render(shader);
	}
};

#endif 
