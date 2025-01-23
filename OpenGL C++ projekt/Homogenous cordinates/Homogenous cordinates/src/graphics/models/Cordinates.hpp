#ifndef CORDINATES_HPP
#define CORDINATES_HPP

#include "../Model.h"

class Cordinates : public Model {
public:
	glm::vec3 size;


	Cordinates(glm::vec3 size)
		: size(size) {}

	void init() {
		int noVertices = 54;

		// vertex array
		float vertices[] = {
			// positions			colors
			// X arrow
			 0.8f,   0.01f, 0.0f,	1.0f, 0.0f, 0.0f,
			 0.8f,  -0.01f, 0.0f,	1.0f, 0.0f, 0.0f,
			-0.8f,  -0.01f, 0.0f,	1.0f, 0.0f, 0.0f,
												  
			 0.8f,   0.01f, 0.0f,	1.0f, 0.0f, 0.0f,
			-0.8f,  -0.01f, 0.0f,	1.0f, 0.0f, 0.0f,
			-0.8f,   0.01f, 0.0f,	1.0f, 0.0f, 0.0f,

			 0.8f,   0.05f, 0.0f,	1.0f, 0.0f, 0.0f,
			 0.8f,  -0.05f, 0.0f,	1.0f, 0.0f, 0.0f,
			 0.9f,   0.0f,  0.0f,	1.0f, 0.0f, 0.0f,

			 0.8f,   0.0f,  0.01f,	1.0f, 0.0f, 0.0f,
			 0.8f,   0.0f, -0.01f,	1.0f, 0.0f, 0.0f,
			-0.8f,   0.0f, -0.01f,	1.0f, 0.0f, 0.0f,
					   						
			 0.8f,   0.0f,  0.01f,	1.0f, 0.0f, 0.0f,
			-0.8f,   0.0f, -0.01f,	1.0f, 0.0f, 0.0f,
			-0.8f,   0.0f,  0.01f,	1.0f, 0.0f, 0.0f,
					   						
			 0.8f,   0.0f,  0.05f,	1.0f, 0.0f, 0.0f,
			 0.8f,   0.0f, -0.05f,	1.0f, 0.0f, 0.0f,
			 0.9f,   0.0f,   0.0f, 	1.0f, 0.0f, 0.0f,

			 // Y arrow
			 0.01f,  0.8f,  0.0f,	0.0f, 1.0f, -0.0f,
			-0.01f,  0.8f,  0.0f,	0.0f, 1.0f, -0.0f,
			-0.01f, -0.8f,  0.0f,	0.0f, 1.0f, -0.0f,
							 					
			 0.01f,  0.8f,  0.0f,	0.0f, 1.0f, -0.0f,
			-0.01f, -0.8f,  0.0f,	0.0f, 1.0f, -0.0f,
			 0.01f, -0.8f,  0.0f,	0.0f, 1.0f, -0.0f,
							 					
			 0.05f,  0.8f,  0.0f,	0.0f, 1.0f, -0.0f,
			-0.05f,	 0.8f,  0.0f,	0.0f, 1.0f, -0.0f,
			 0.0f,	 0.9f,  0.0f,	0.0f, 1.0f, -0.0f,

			 0.0f,  0.8f,  0.01f, 	0.0f, 1.0f, -0.0f,
			 0.0f,  0.8f, -0.01f, 	0.0f, 1.0f, -0.0f,
			 0.0f, -0.8f, -0.01f, 	0.0f, 1.0f, -0.0f,
			
			 0.0f,  0.8f,  0.01f, 	0.0f, 1.0f, -0.0f,
			 0.0f, -0.8f, -0.01f, 	0.0f, 1.0f, -0.0f,
			 0.0f, -0.8f,  0.01f, 	0.0f, 1.0f, -0.0f,

			 0.0f,  0.8f,  0.05f, 	0.0f, 1.0f, -0.0f,
			 0.0f,	0.8f, -0.05f,	0.0f, 1.0f, -0.0f,
			 0.0f,	0.9f,  0.0f,	0.0f, 1.0f, -0.0f,

			 // Z arrow
			 0.0f,  0.01f,  0.8f,	0.0f, 0.0f, 1.0f,
			 0.0f, -0.01f,  0.8f,	0.0f, 0.0f,	1.0f,
			 0.0f, -0.01f, -0.8f,	0.0f, 0.0f,	1.0f,

			 0.0f,  0.01f,  0.8f,	0.0f, 0.0f,	1.0f,
			 0.0f, -0.01f, -0.8f,	0.0f, 0.0f,	1.0f,
			 0.0f,  0.01f, -0.8f,	0.0f, 0.0f,	1.0f,

			 0.0f,  0.05f, -0.8f,	0.0f, 0.0f,	1.0f,
			 0.0f, -0.05f, -0.8f,	0.0f, 0.0f,	1.0f,
			 0.0f,  0.0f,  -0.9f,	0.0f, 0.0f,	1.0f,

			 0.01f, 0.0f,   0.8f,	0.0f, 0.0f, 1.0f,
			-0.01f, 0.0f,   0.8f,	0.0f, 0.0f,	1.0f,
			-0.01f, 0.0f,  -0.8f,	0.0f, 0.0f,	1.0f,
						   
			 0.01f, 0.0f,   0.8f,	0.0f, 0.0f,	1.0f,
			-0.01f, 0.0f,  -0.8f,	0.0f, 0.0f,	1.0f,
			 0.01f, 0.0f,  -0.8f,	0.0f, 0.0f,	1.0f,
						   
			 0.05f, 0.0f,  -0.8f,	0.0f, 0.0f,	1.0f,
			-0.05f, 0.0f,  -0.8f,	0.0f, 0.0f,	1.0f,
			 0.0f,  0.0f,  -0.9f,	0.0f, 0.0f,	1.0f,
		}; // FLICKERING ISSUE AT AXES CROSS OVER

		// Could create more efficient indicies array
		std::vector<unsigned int> indicies(noVertices);
		for (unsigned int i = 0; i < noVertices; i++) {
			indicies[i] = i;
		}

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices), indicies));
	}

	void render(Shader shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, size * MyGui::size);
		shader.setMat4("model", model);

		Model::render(shader);
	}
};

#endif 
