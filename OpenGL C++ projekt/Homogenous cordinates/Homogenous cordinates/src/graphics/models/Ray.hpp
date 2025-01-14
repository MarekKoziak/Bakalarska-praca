#ifndef RAY_HPP
#define RAY_HPP

#include "../Model.h"

class Ray : public Model {
public:
	glm::vec3 size;
	glm::vec3 rotationAxis;
	float lengthMultiplier;
	float angle;


	Ray(glm::vec3 size)
		: size(size) {}

	void init() {
		int noVertices = 12;

		// vertex array
		float vertices[] = {
			// positions			colors
			 0.0f,  0.01f,  0.0f,	0.0f, 0.0f, 1.0f,
			 0.0f, -0.01f, -1.0f,	0.0f, 0.0f,	1.0f,
			 0.0f,  0.01f, -1.0f,	0.0f, 0.0f,	1.0f,
							
			 0.0f, -0.01f,  0.0f,	0.0f, 0.0f,	1.0f,
			 0.0f, -0.01f, -1.0f,	0.0f, 0.0f,	1.0f,
			 0.0f,  0.01f,  0.0f,	0.0f, 0.0f,	1.0f,
							
			 0.01f, 0.0f,   0.0f,	0.0f, 0.0f, 1.0f,
			-0.01f, 0.0f,   0.0f,	0.0f, 0.0f,	1.0f,
			-0.01f, 0.0f,  -1.0f,	0.0f, 0.0f,	1.0f,
							
			 0.01f, 0.0f,   0.0f,	0.0f, 0.0f,	1.0f,
			-0.01f, 0.0f,  -1.0f,	0.0f, 0.0f,	1.0f,
			 0.01f, 0.0f,  -1.0f,	0.0f, 0.0f,	1.0f,
		};

		// Could create more efficient indicies array
		std::vector<unsigned int> indicies(noVertices);
		for (unsigned int i = 0; i < noVertices; i++) {
			indicies[i] = i;
		}

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices), indicies));
	}

	void transformParameters(glm::vec3 pointPos) {
		glm::vec3 Yaxis(0.0f, 0.0f, 1.0f);
		
		// axis and angle calculations
		float triangleHypotenuse = glm::length(pointPos);
		float triangleOpposite = glm::length(glm::vec3(0.0f, 0.0f, pointPos.z));

		angle = acos(triangleOpposite / triangleHypotenuse);
		rotationAxis = glm::normalize(glm::cross(pointPos, Yaxis));
		lengthMultiplier = triangleHypotenuse;
	}

	void render(Shader shader, glm::vec3 pointPos) {
		transformParameters(pointPos); // calculate parameters for transform matrices

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, angle, rotationAxis); // rotate to cross the point
		model = glm::scale(model, glm::vec3(size.x, size.y, size.z * lengthMultiplier)); // extends the ray length to match point distance
		shader.setMat4("model", model);

		Model::render(shader);
	}
};

#endif 
