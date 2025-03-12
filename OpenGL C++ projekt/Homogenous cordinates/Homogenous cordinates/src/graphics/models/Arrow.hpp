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
		int noVertices_inf = 63;

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

		float vertices_inf[]{
			0.000f,	0.064f, 0.0f,
			0.080f,	0.145f, 0.0f,
			0.139f,	0.192f, 0.0f,
			0.190f,	0.219f, 0.0f,
			0.242f,	0.234f, 0.0f,
			0.324f,	0.234f, 0.0f,
			0.383f,	0.215f, 0.0f,
			0.430f,	0.181f, 0.0f,
			0.463f,	0.138f, 0.0f,
			0.489f,	0.088f, 0.0f,
			0.500f,	0.034f, 0.0f,
			0.500f,	0.000f, 0.0f,
			0.000f,	0.000f, 0.0f,
			0.062f,	0.000f, 0.0f,
			0.131f,	0.073f, 0.0f,
			0.186f,	0.116f, 0.0f,
			0.226f,	0.135f, 0.0f,
			0.248f,	0.142f, 0.0f,
			0.307f,	0.142f, 0.0f,
			0.344f,	0.127f, 0.0f,
			0.366f,	0.108f, 0.0f,
			0.384f,	0.085f, 0.0f,
			0.399f,	0.058f, 0.0f,
			0.409f,	0.031f, 0.0f,
			0.409f,	0.000f, 0.0f
		};


		std::vector<unsigned int> indices = { 0, 1, 3, 3, 1, 2, 4, 5, 6};

		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(1.0f)), indices));

		std::vector<unsigned int> indices_inf(noVertices_inf);
		for (unsigned int i = 0; i <= 10; i++) {
			indices_inf.insert(indices_inf.end(), { i + 0, i + 13, i + 1 });
			indices_inf.insert(indices_inf.end(), { i + 13, i + 14, i + 1 });
		}
		indices_inf.insert(indices_inf.end(), { 0, 12, 13 });

		meshes.push_back(Mesh(Vertex::genList(vertices_inf, noVertices_inf, glm::vec3(1.0f)), indices_inf));

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
		glm::vec3 pos = Arrow::pos(pointPos, posLimit);
			
			// Arrow
		glm::mat4 translateMatrix = glm::translate(model, pos);
		glm::mat4 rotateMatrix = glm::rotate(model, angle(pointPos), rotationAxis);
		glm::mat4 scaleMatrix = glm::scale(model, size);

		model = translateMatrix * rotateMatrix * scaleMatrix;
		shader.setMat4("model", model);
		meshes[0].render(shader);

			// Inf symbol
		glm::mat4 miror1 = glm::mat4(1.0f);
		glm::mat4 miror2 = glm::mat4(1.0f);
		glm::mat4 miror3 = glm::mat4(1.0f);

		miror1 = glm::rotate(miror1, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		miror2 = glm::rotate(miror2, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		miror3 = glm::rotate(miror3, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		translateMatrix = glm::translate(translateMatrix, 0.17f * -glm::normalize(glm::vec3(pos.x, pos.y, 0.0f)));
		translateMatrix = glm::translate(translateMatrix, 0.1f * glm::normalize(glm::cross(glm::vec3(pos.x, pos.y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))));
		scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.2f));
		
		if (pointPos.z == 0) {
			model = translateMatrix * rotateMatrix * scaleMatrix;
			shader.setMat4("model", model);
			meshes[1].render(shader);
			model = translateMatrix * rotateMatrix * miror1 * scaleMatrix;
			shader.setMat4("model", model);
			meshes[1].render(shader);
			model = translateMatrix * rotateMatrix * miror2 * scaleMatrix;
			shader.setMat4("model", model);
			meshes[1].render(shader);
			model = translateMatrix * rotateMatrix * miror3 * scaleMatrix;
			shader.setMat4("model", model);
			meshes[1].render(shader);
		}
	}
};

#endif 
