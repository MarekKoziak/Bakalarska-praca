#ifndef CUBE1_HPP
#define CUBE1_HPP

#include "../Model.h"

class Cube1 : public Model {
public:
	glm::vec3 pos;
	glm::vec3 size;
	float sizeMultiplier = 1.0f;

	Cube1(glm::vec3 pos, glm::vec3 size)
		: pos(pos), size(size) {init();}

	void init() {
		int noVertices = 24;

		// vertex array
		float vertices[] = {
			// positions		
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
								
			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
								
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
								
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
								
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
								
			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f
		};

		std::vector<unsigned int> indices(noVertices);
		for (unsigned int i = 0; i < 24; i += 4) {
			indices.insert(indices.end(), {i + 0,i + 1,i + 2,i + 2,i + 3,i + 0});
		};

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(0.0f, 1.0f, 0.0f)), indices));
	}

	void updateposition() {
		pos.x = MyGui::x / MyGui::w;
		pos.y = MyGui::y / MyGui::w;
	}

	void render(Shader shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::scale(model, size * sizeMultiplier);
		shader.setMat4("model", model);

		Model::render(shader);
	}
};

#endif 
