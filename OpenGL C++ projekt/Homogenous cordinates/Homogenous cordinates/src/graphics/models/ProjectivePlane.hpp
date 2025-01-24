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
		int noVertices2 = 8;

		// vertex array
		float vertices[] = {
			// positions			   
			-1.0f,  0.5625f, -1.0f,    
			-1.0f, -0.5625f, -1.0f,		
			 1.0f,  0.5625f, -1.0f,		
			 1.0f, -0.5625f, -1.0f,		
		};
		float vertices2[] = {
			-1.0f,   0.003f,   -1.0f,	
			 1.0f,   0.003f,   -1.0f,	
			 1.0f,  -0.003f,   -1.0f,	
			-1.0f,  -0.003f,   -1.0f,	

			-0.003f,  0.5625f, -1.0f,	
			 0.003f,  0.5625f, -1.0f,	
			 0.003f, -0.5625f, -1.0f,	
			-0.003f, -0.5625f, -1.0f,	

		};

		std::vector<unsigned int> indicies = {0, 1, 2, 1, 2, 3};	
		std::vector<unsigned int> indicies2 = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(1.0f, 1.0f, 1.0f)), indicies));
		meshes.push_back(Mesh(Vertex::genList(vertices2, noVertices2, glm::vec3(1.0f, 1.0f, 1.0f)), indicies2));
	}

	void render(Shader shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, size);
		shader.setMat4("model", model);

		shader.setFloat("myAlpha", 1.0f);
		meshes[1].render(shader);

		shader.setFloat("myAlpha", alpha);
		glEnable(GL_BLEND);
		meshes[0].render(shader);
		glDisable(GL_BLEND);
	}
};

#endif 
