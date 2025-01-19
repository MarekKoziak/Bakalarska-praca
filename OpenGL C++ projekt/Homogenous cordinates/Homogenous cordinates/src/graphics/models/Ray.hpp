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

	void transformParameters(glm::vec3 pointPos1, glm::vec3 pointPos2) {
		glm::vec3 Yaxis(0.0f, 0.0f, 1.0f);
		
		// axis and angle calculations
		float triangleHypotenuse = glm::length(pointPos1);
		float triangleOpposite = glm::length(glm::vec3(0.0f, 0.0f, pointPos1.z));

		angle = acos(triangleOpposite / triangleHypotenuse);
		rotationAxis = glm::normalize(glm::cross(pointPos1, Yaxis));
		if (pointPos2.z < -1.0f) {
			lengthMultiplier = glm::length(pointPos2);
		}
		else {
			lengthMultiplier = glm::length(pointPos1);
		}
	}

	void render(Shader shader, glm::vec3 pointPos1, glm::vec3 pointPos2) {
		transformParameters(pointPos1, pointPos2); // calculate parameters for transform matrices

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, angle, rotationAxis); // rotate to cross the point
		model = glm::scale(model, glm::vec3(size.x, size.y, size.z * lengthMultiplier)); // extends the ray length to match point distance
		shader.setMat4("model", model);

		Model::render(shader);
	}
};

#endif 
