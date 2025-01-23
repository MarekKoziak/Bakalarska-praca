#ifndef PROJECTIVEPLANE_HPP
#define PROJECTIVEPLANE_HPP

#include "../Model.h"

class ProjectivePlane : public Model {
public:
	glm::vec3 size;
	float alpha;

	ProjectivePlane( glm::vec3 size, float alpha)
		: size(size), alpha(alpha) {}

	void init() {
		int noVertices = 4;

		// vertex array
		float vertices[] = {
			// positions			    colors
			-1.0f,  0.5625f, -1.0f,     1.0f, 1.0f, 1.0f,
			-1.0f, -0.5625f, -1.0f,		1.0f, 1.0f, 1.0f,
			 1.0f,  0.5625f, -1.0f,		1.0f, 1.0f, 1.0f,
			 1.0f, -0.5625f, -1.0f,		1.0f, 1.0f, 1.0f
		};

		std::vector<unsigned int> indicies = {0, 1, 2, 1, 2, 3};		

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices), indicies));
	}

	void render(Shader shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, size);
		shader.setMat4("model", model);
		shader.setFloat("myAlpha", alpha);

		glEnable(GL_BLEND);
		Model::render(shader);
		glDisable(GL_BLEND);
	}
};

#endif 
