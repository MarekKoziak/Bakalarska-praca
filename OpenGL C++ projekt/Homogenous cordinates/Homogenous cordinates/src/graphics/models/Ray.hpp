#ifndef RAY_HPP
#define RAY_HPP

#include "../Model.h"

class Ray : public Model {
public:
	glm::vec3 size;
	glm::vec3 pointPozition;
	glm::vec3 rotationAxis;
	float lengthMultiplayer = 3.0f;
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

	void crossPoint() {
		glm::vec3 Yaxis(0.0f, 0.0f, 1.0f);
		float pointDistance;

		rotationAxis = glm::normalize(glm::cross(pointPozition, Yaxis));
		pointDistance = glm::length(glm::vec2(pointPozition.x, pointPozition.z));

		if (pointDistance == 0.0f) {
			angle = 0.0f;
		}
		else {
			angle = asin(pointPozition.y / pointDistance);
		}
	}

	void render(Shader shader) {
		// axis and angle calculations
		glm::vec3 rotationAxis = glm::normalize(glm::cross(pointPozition, glm::vec3(0.0f, 0.0f, 1.0f)));
		float triangleHypotenuse = glm::length(pointPozition);
		float triangleOpposite = glm::length(glm::vec3(0.0f, 0.0f, -1.0f) - pointPozition);
		float angle = asin(triangleOpposite / triangleHypotenuse);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, angle, rotationAxis); // rotate to cross the point
		model = glm::scale(model, glm::vec3(size.x, size.y, size.z * lengthMultiplayer));
		shader.setMat4("model", model);

		Model::render(shader);
	}
};

#endif 
