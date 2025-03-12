#ifndef PROJECTIVEPLANE_HPP
#define PROJECTIVEPLANE_HPP

#include "../Model.h"

class ProjectivePlane : public Model {
public:
	glm::vec3 size;
	glm::vec2 border = glm::vec2(1.0f * size.x, 0.5625f * size.y);
	float alpha;

	ProjectivePlane( glm::vec3 size, float alpha)
		: size(size), alpha(alpha) {init();}

	void init() {
		int noVertices = 4;
		int noVertices2 = 8;
		int noVertices_u = 114;
		int noVertices_v = 21;

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
		float vertices_u[] = {
			-0.412f,  0.510f, 0.0f,
			-0.258f,  0.510f, 0.0f,
			-0.412f, -0.173f, 0.0f,
			-0.258f, -0.100f, 0.0f,
			 0.254f,  0.510f, 0.0f,
			 0.412f,  0.510f, 0.0f,
			 0.254f, -0.487f, 0.0f,
			 0.412f, -0.487f, 0.0f,
			-0.399f, -0.252f, 0.0f,
			-0.246f, -0.186f, 0.0f,
			-0.380f, -0.313f, 0.0f,
			-0.225f, -0.251f, 0.0f,
			-0.349f, -0.374f, 0.0f,
			-0.195f, -0.301f, 0.0f,
			-0.322f, -0.410f, 0.0f,
			-0.160f, -0.335f, 0.0f,
			-0.293f, -0.438f, 0.0f,
			-0.124f, -0.356f, 0.0f,
			-0.247f, -0.469f, 0.0f,
			-0.076f, -0.371f, 0.0f,
			-0.201f, -0.489f, 0.0f,
			-0.033f, -0.377f, 0.0f,
			-0.152f, -0.502f, 0.0f,
			 0.001f, -0.377f, 0.0f,
			-0.083f, -0.510f, 0.0f,
			 0.058f, -0.367f, 0.0f,
			-0.039f, -0.510f, 0.0f,
			 0.104f, -0.349f, 0.0f,
			 0.026f, -0.502f, 0.0f,
			 0.145f, -0.322f, 0.0f,
			 0.071f, -0.489f, 0.0f,
			 0.185f, -0.282f, 0.0f,
			 0.115f, -0.469f, 0.0f,
			 0.216f, -0.234f, 0.0f,
			 0.157f, -0.441f, 0.0f,
			 0.235f, -0.189f, 0.0f,
			 0.195f, -0.405f, 0.0f,
			 0.246f, -0.146f, 0.0f,
			 0.226f, -0.366f, 0.0f,
			 0.251f, -0.113f, 0.0f,
			 0.254f, -0.323f, 0.0f,
			 0.254f, -0.083f, 0.0f
		};

		float vertices_v[]{
			-0.466f,  0.499f, 0.0f,
			-0.291f,  0.499f, 0.0f,
			-0.088f, -0.499f, 0.0f,
			-0.026f, -0.261f, 0.0f,
			 0.000f, -0.366f, 0.0f,
			 0.024f, -0.260f, 0.0f,
			 0.069f, -0.499f, 0.0f,
			 0.299f,  0.499f, 0.0f,
			 0.467f,  0.499f, 0.0f
		};


		std::vector<unsigned int> indices = {0, 1, 2, 1, 2, 3};	
		std::vector<unsigned int> indices2 = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(1.0f)), indices));
		meshes.push_back(Mesh(Vertex::genList(vertices2, noVertices2, glm::vec3(1.0f)), indices2));

		std::vector<unsigned int> indices_u(noVertices_u);
		indices_u.insert(indices_u.end(), {0, 2, 1, 1, 2, 3, 4, 6, 5, 5, 6, 7, 2, 8, 3, 3, 8, 9});
		for (unsigned int i = 0; i < 32; i += 2) {
			indices_u.insert(indices_u.end(), { i + 11, i + 9, i + 8, i + 11, i + 8, i + 10});
		}
		std::vector<unsigned int> indices_v = {0, 2, 1, 1, 2, 3, 2, 4, 3, 2, 6, 4, 4, 6, 5, 5, 8, 7, 5, 6, 8};

		meshes.push_back(Mesh(Vertex::genList(vertices_u, noVertices_u, glm::vec3(1.0f)), indices_u));
		meshes.push_back(Mesh(Vertex::genList(vertices_v, noVertices_v, glm::vec3(1.0f)), indices_v));

	}

	void render(Shader shaderTransparent) {
		glm::mat4 model = glm::mat4(1.0f);

			// Letters
		shaderTransparent.setFloat("myAlpha", 1.0f);	// set level of transparency
		model = glm::translate(model, glm::vec3(0.04f * size.x, 0.52f * size.y, -1.0f * size.z));
		model = glm::scale(model, glm::vec3(0.08f));
		shaderTransparent.setMat4("model", model);
		meshes[3].render(shaderTransparent);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.96f * size.x, -0.04f * size.y, -1.0f * size.z));
		model = glm::scale(model, glm::vec3(0.08f));
		shaderTransparent.setMat4("model", model);
		meshes[2].render(shaderTransparent);

			// Cross
		model = glm::mat4(1.0f);
		model = glm::scale(model, size);
		shaderTransparent.setMat4("model", model);
		meshes[1].render(shaderTransparent);

			// Plane
		shaderTransparent.setFloat("myAlpha", alpha);
		glEnable(GL_BLEND);
		meshes[0].render(shaderTransparent);
		glDisable(GL_BLEND);
	}
};

#endif 
