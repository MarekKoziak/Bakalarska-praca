#ifndef CORDINATES_HPP
#define CORDINATES_HPP

#include "../Model.h"

class Cordinates : public Model {
public:
	glm::vec3 size;


	Cordinates(glm::vec3 size)
		: size(size) {}

	void init() {
		int noVerticesBottom = 24;
		int noVerticesTop = 12;

		int noVertices = noVerticesBottom + noVerticesTop;

		// vertex array
		float vertices[] = {
			// positions			
			 -0.01f,  0.8f,  0.01f,
			 -0.01f, -0.8f,  0.01f,
			  0.01f,  0.8f,  0.01f,
			  0.01f, -0.8f,  0.01f,
			  0.01f,  0.8f, -0.01f,
			  0.01f, -0.8f, -0.01f,
			 -0.01f,  0.8f, -0.01f,
			 -0.01f, -0.8f, -0.01f,
			 
			  0.0f,   0.9f,  0.0f,
			 -0.03f,  0.8f,  0.03f,
			  0.03f,  0.8f,  0.03f,
			  0.03f,  0.8f, -0.03f,
			 -0.03f,  0.8f, -0.03f
		};

		
		std::vector<unsigned int> indicies(noVerticesBottom);
		for (unsigned int i = 0; i < noVerticesBottom / 4; i += 2) {
			indicies.insert(indicies.end(), {i + 0,i + 1,i + 2,i + 2,i + 1,i + 3});
		}
			indicies.insert(indicies.end(), { 6, 7, 0, 0, 7, 1 });
		for (unsigned int i = 0; i < noVerticesTop / 4; i++) {
			indicies.insert(indicies.end(), {8, i + 9, i + 10});
		}
			indicies.insert(indicies.end(), {8, 12, 9});

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(1.0f, 0.0f, 0.0f)), indicies));
		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(0.0f, 1.0f, 0.0f)), indicies));
		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(0.0f, 0.0f, 1.0f)), indicies));
	}

	void render(Shader shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, size);
		shader.setMat4("model", model);

		meshes[0].render(shader);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setMat4("model", model);
		meshes[1].render(shader);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		meshes[2].render(shader);

	}
};

#endif 
