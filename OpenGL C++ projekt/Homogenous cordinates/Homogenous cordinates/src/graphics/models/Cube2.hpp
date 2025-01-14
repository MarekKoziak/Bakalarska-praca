#ifndef CUBE2_HPP
#define CUBE2_HPP

#include "../Model.h"

class Cube2 : public Model {
public:
	glm::vec3 pos;
	glm::vec3 size;
	float sizeMultiplier = 1.0f;

	Cube2(glm::vec3 pos, glm::vec3 size)
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

			-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

			-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f
		};

		std::vector<unsigned int> indicies(noVertices);
		for (unsigned int i = 0; i < noVertices; i++) {
			indicies[i] = i;
		}

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices), indicies));
	}

	void render(Shader shader) {
		pos.x = MyGui::x;
		pos.y = MyGui::y;
		pos.z = -MyGui::w;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::scale(model, size * sizeMultiplier);
		shader.setMat4("model", model);

		Model::render(shader);
	}
};

#endif 
