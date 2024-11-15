#ifndef CUBE_HPP
#define CUBE_HPP

#include "../Model.h"

class Cube : public Model {
public:
	glm::vec3 pos;
	glm::vec3 size;

	Cube(glm::vec3 pos, glm::vec3 size)
		: pos(pos), size(size) {}

	void init() {
		int noVertices = 36;

		// vertex array
		float vertices[] = {
			// positions			colors
			-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

			-0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
			-0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
			-0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,

			-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 1.0f
		};

		std::vector<unsigned int> indicies(noVertices);
		for (unsigned int i = 0; i < noVertices; i++) {
			indicies[i] = i;
		}

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices), indicies));
	}

	void render(Shader shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, size);
		model = glm::translate(model, pos);
		shader.setMat4("model", model);

		Model::render(shader);
	}
};

#endif 
