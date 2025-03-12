#ifndef CORDINATES_HPP
#define CORDINATES_HPP

#include "../Model.h"

class Cordinates : public Model {
public:
	glm::vec3 size;


	Cordinates(glm::vec3 size)
		: size(size) {init();}

	void init() {
		int noVerticesBottom = 24;
		int noVerticesTop = 12;
		int noVertices = noVerticesBottom + noVerticesTop;

		int noVertices_x = 30;
		int noVertices_y = 132;
		int noVertices_w = 33;

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

		float vertices_x[]{
			-0.423f,  0.509f, 0.0f,
			-0.237f,  0.509f, 0.0f,
			 0.252f,  0.509f, 0.0f,
			 0.429f,  0.509f, 0.0f,
			-0.437f, -0.490f, 0.0f,
			-0.253f, -0.490f, 0.0f,
			 0.236f, -0.490f, 0.0f,
			 0.423f, -0.490f, 0.0f,
			-0.097f,  0.000f, 0.0f,
			 0.000f,  0.089f, 0.0f,
			 0.092f,  0.000f, 0.0f,
			 0.000f, -0.089f, 0.0f

		};

		float vertices_y[]{
			-0.460f,  0.734f, 0.0f,  
			-0.285f,  0.734f, 0.0f,
			-0.072f, -0.263f, 0.0f,
			 0.009f, -0.111f, 0.0f,
			 0.316f,  0.734f, 0.0f,
			 0.480f,  0.734f, 0.0f,
			-0.146f, -0.439f, 0.0f,
			 0.030f, -0.402f, 0.0f,
			-0.162f, -0.475f, 0.0f,
			 0.014f, -0.441f, 0.0f,
			-0.178f, -0.504f, 0.0f,
			-0.002f, -0.478f, 0.0f,
			-0.194f, -0.527f, 0.0f,
			-0.018f, -0.510f, 0.0f,
			-0.210f, -0.545f, 0.0f,
			-0.034f, -0.539f, 0.0f,
			-0.226f, -0.560f, 0.0f,
			-0.050f, -0.565f, 0.0f,
			-0.242f, -0.571f, 0.0f,
			-0.066f, -0.588f, 0.0f,
			-0.258f, -0.580f, 0.0f,
			-0.082f, -0.609f, 0.0f,
			-0.274f, -0.587f, 0.0f,
			-0.098f, -0.628f, 0.0f,
			-0.300f, -0.594f, 0.0f,
			-0.116f, -0.647f, 0.0f,
			-0.316f, -0.597f, 0.0f,
			-0.132f, -0.661f, 0.0f,
			-0.332f, -0.597f, 0.0f,
			-0.148f, -0.674f, 0.0f,
			-0.348f, -0.597f, 0.0f,
			-0.164f, -0.686f, 0.0f,
			-0.364f, -0.595f, 0.0f,
			-0.180f, -0.696f, 0.0f,
			-0.377f, -0.593f, 0.0f,
			-0.196f, -0.705f, 0.0f,
			-0.396f, -0.589f, 0.0f,
			-0.212f, -0.712f, 0.0f,
			-0.411f, -0.585f, 0.0f,
			-0.228f, -0.718f, 0.0f,
			-0.428f, -0.580f, 0.0f,
			-0.244f, -0.723f, 0.0f,
			-0.274f, -0.730f, 0.0f,
			-0.304f, -0.734f, 0.0f,
			-0.352f, -0.734f, 0.0f,
			-0.377f, -0.732f, 0.0f,
			-0.403f, -0.728f, 0.0f,
			-0.428f, -0.722f, 0.0f
		};

		float vertices_w[]{
			-0.698f,  0.499f, 0.0f,
			-0.396f, -0.499f, 0.0f,
			-0.531f,  0.499f, 0.0f,
			-0.306f, -0.311f, 0.0f,
			-0.054f,  0.499f, 0.0f,
			-0.237f, -0.499f, 0.0f,
			 0.010f,  0.279f, 0.0f,
			 0.234f, -0.499f, 0.0f,
			 0.092f,  0.499f, 0.0f,
			 0.318f, -0.311f, 0.0f,
			 0.542f,  0.499f, 0.0f,
			 0.399f, -0.499f, 0.0f,
			 0.698f,  0.499f, 0.0f
		};

		
		std::vector<unsigned int> indices(noVertices);
		for (unsigned int i = 0; i < noVerticesBottom / 4; i += 2) {
			indices.insert(indices.end(), {i + 0,i + 1,i + 2,i + 2,i + 1,i + 3});
		}
			indices.insert(indices.end(), { 6, 7, 0, 0, 7, 1 });
		for (unsigned int i = 0; i < noVerticesTop / 4; i++) {
			indices.insert(indices.end(), {8, i + 9, i + 10});
		}
			indices.insert(indices.end(), {8, 12, 9});


		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(1.0f, 0.0f, 0.0f)), indices));
		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(0.0f, 1.0f, 0.0f)), indices));
		meshes.push_back(Mesh(Vertex::genList(vertices, noVertices, glm::vec3(0.0f, 0.0f, 1.0f)), indices));

		std::vector<unsigned int> indices_x(noVertices_x);
		indices_x.insert(indices_x.end(), { 0, 8, 1, 1, 8, 9, 2, 9, 3, 3, 9, 10, 8, 4, 11, 11, 4, 5, 11, 6, 10, 10, 6, 7, 8, 10, 9, 8, 11, 10});
		std::vector<unsigned int> indices_y(noVertices_y);
		indices_y.insert(indices_y.end(), { 0, 2, 1, 1, 2, 3, 4, 6, 5, 5, 6, 7 });
		for (unsigned int i = 0; i < 34; i++) {
			indices_y.insert(indices_y.end(), { 6 + i, 7 + i, 8 + i });
		}
		for (unsigned int i = 0; i < 6; i++) {
			indices_y.insert(indices_y.end(), { 40, 41 + i, 42 + i });
		}
		std::vector<unsigned int> indices_w(noVertices_w);
		indices_w.insert(indices_w.end(), { 1, 3, 5, 4, 6, 8, 7, 9, 11 });
		for (unsigned int i = 0; i < 8; i++) {
			indices_w.insert(indices_w.end(), { i + i/2 + 0, i + i/2 + 1, i + i/2 + 2});
		}

		meshes.push_back(Mesh(Vertex::genList(vertices_x, noVertices_x, glm::vec3(0.0f, 1.0f, 0.0f)), indices_x));
		meshes.push_back(Mesh(Vertex::genList(vertices_y, noVertices_y, glm::vec3(1.0f, 0.0f, 0.0f)), indices_y));
		meshes.push_back(Mesh(Vertex::genList(vertices_w, noVertices_w, glm::vec3(0.0f, 0.0f, 1.0f)), indices_w));
	}

	void render(Shader shader) {
		glm::mat4 model = glm::mat4(1.0f);

			// Arrows
		model = glm::scale(model, size);
		shader.setMat4("model", model);
		meshes[0].render(shader);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setMat4("model", model);
		meshes[1].render(shader);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		meshes[2].render(shader);
			
			// Letters
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.76f * size.x, 0.05f * size.y, 0.0f * size.z));
		model = glm::scale(model, glm::vec3(0.1));
		shader.setMat4("model", model);
		meshes[3].render(shader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.05f * size.x, 0.74f * size.y, 0.0f * size.z));
		model = glm::scale(model, glm::vec3(0.1));
		shader.setMat4("model", model);
		meshes[4].render(shader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.00f * size.x, 0.05f * size.y, -0.75f * size.z));
		model = glm::scale(model, glm::vec3(0.1));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		meshes[5].render(shader);
	}
};

#endif 
