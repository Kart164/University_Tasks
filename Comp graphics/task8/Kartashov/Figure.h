#pragma once
#include<vector>

#include <glm\glm.hpp>
#include <glad\glad.h>

struct vertex { // ���� �������
	glm::vec3 position; // ���������� �������
	glm::vec3 normal; // ������� � �������
};

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};


class mesh
{
public:
	std::vector<vertex> vertices; // ������������������ �����
	Material material;
	GLuint vertexArray; // ��������� ������ (������ OpenGL)
	std::vector<GLuint> indices; // ������������������ �������� � ������ �����

	mesh(std::vector<vertex> verts, std::vector<GLuint> inds, Material col)
	{
		vertices = verts;
		material = col;
		indices = inds;
		setupMesh();
	}

private:
	GLuint vertexBuffer; // ��������� ����� (������ OpenGL)
	GLuint elementBuffer; // ����� �������� ������ (������ OpenGL)

	void setupMesh()
	{
		// ������� ��������� ������ � ��������� �����
		glGenVertexArrays(1, &vertexArray); // ������� ��������� ������
		glGenBuffers(1, &vertexBuffer); // ������� ��������� �����
		glGenBuffers(1, &elementBuffer); // ������� ����� ��������

		glBindVertexArray(vertexArray); // ������ ��������� ������ ��������

		// ��������� vertexBuffer c GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		// �������� ���������� vertices � ��������� ����� vertexBuffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
		// �������� ������������ ��������� ���������� ������� � ��������� ������
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);
		glEnableVertexAttribArray(0); // ��������� ��������� 0 ��� �������
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));
		glEnableVertexAttribArray(1); // ��������� ��������� 1 ��� �������

		// ��������� elementBuffer c GL_ELEMENT_ARRAY_BUFFER
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		// �������� ���������� indices � ����� �������� elementBuffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // ������� ��������� �������
		glBindVertexArray(0); // ���������� ���������� �������
	}
};

class model {
public:
	std::vector<mesh> figure; // ������������ �������
	glm::mat4 modelM; // ��������� �������
	model(std::vector<mesh> fig, glm::mat4 mat) {
		figure = fig;
		modelM = mat;
	}
};
