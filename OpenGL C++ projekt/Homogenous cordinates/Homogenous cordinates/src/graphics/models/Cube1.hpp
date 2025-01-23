#ifndef CUBE1_HPP
#define CUBE1_HPP

#include "../Model.h"

class Cube1 : public Model {
public:
	glm::vec3 pos;
	glm::vec3 size;
	float sizeMultiplier = 1.0f;

	Cube1(glm::vec3 pos, glm::vec3 size)
		: pos(pos), size(size) {}

	void init() {
		int noVertices = 24;

		// vertex array
		float vertices[] = {
			// positions			colors
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
									    
			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
									    
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
									    
			 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
									    
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
									    
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		};

		std::vector<unsigned int> indicies(noVertices);
		for (unsigned int i = 0; i < 24; i += 4) {
			indicies.insert(indicies.end(), {i + 0,i + 1,i + 2,i + 2,i + 3,i + 0});
		};

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices), indicies));
	}

	void render(Shader shader) {
		pos.x = MyGui::x / MyGui::w;
		pos.y = MyGui::y / MyGui::w;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::scale(model, size * sizeMultiplier);
		shader.setMat4("model", model);

		Model::render(shader);
	}
};

#endif 
