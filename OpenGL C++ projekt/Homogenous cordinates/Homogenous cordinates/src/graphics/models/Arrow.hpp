#ifndef ARROW_HPP
#define ARROW_HPP

#include "../Model.h"

class Arrow : public Model {
public:
	glm::vec3 size;
	glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, -1.0f);


	Arrow(glm::vec3 size)
		: size(size) {init();}

	void init() {
		int noVertices = 9;

		// vertex array
		float vertices[] = {
			// positions			
			 -0.07f, -0.2f, 0.0f,
			 -0.07f, -0.4f, 0.0f,
			  0.07f, -0.4f, 0.0f,
			  0.07f, -0.2f, 0.0f,
					 
			  0.0f,   0.0f, 0.0f,
			 -0.15f, -0.2f, 0.0f,
			  0.15f, -0.2f, 0.0f
		};


		std::vector<unsigned int> indices = { 0, 1, 3, 3, 1, 2, 4, 5, 6};

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(0.9f, 0.9f, 0.9f)), indices));
	}

	float angle(glm::vec3 pointPos) {
		glm::vec2 up = glm::vec2(0.0f, 1.0f);
		glm::vec2 pointPosV2 = glm::vec2(pointPos.x, pointPos.y);

		if (pointPos.x >= 0) {
			return acos(glm::dot(up, pointPosV2) / (glm::length(up) * glm::length(pointPosV2)));
		}
		else{
			return 2 * glm::pi<float>() - acos(glm::dot(up, pointPosV2) / (glm::length(up) * glm::length(pointPosV2)));
		}
	}

	glm::vec3 pos(glm::vec3 pointPos, glm::vec2 posLimit) {
		float posLimiter = abs(posLimit.x / pointPos.x);
		if (-posLimit.y > (posLimiter * pointPos.y) || (posLimiter * pointPos.y) > posLimit.y){
			posLimiter = abs(posLimit.y / pointPos.y);
		}
		glm::vec3 pos = glm::vec3(posLimiter * pointPos.x, posLimiter * pointPos.y, -1.0f);
		return pos;
	}

	void render(Shader shader, glm::vec3 pointPos, glm::vec2 posLimit) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos(pointPos, posLimit));
		model = glm::scale(model, size);
		model = glm::rotate(model, angle(pointPos), rotationAxis);
		shader.setMat4("model", model);

		Model::render(shader);
	}
};

#endif 
