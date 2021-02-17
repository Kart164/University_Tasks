#pragma once
#include<vector>

#include <glm\glm.hpp>
#include <glad\glad.h>

class path {
private:
	GLuint vertexBuffer; // вершинный буфер (объект OpenGL)

	void setupPath() {
		glGenVertexArrays(1, &vertexArray); // создаем вершинный массив
		glGenBuffers(1, &vertexBuffer); // создаем вершинный буфер
		glBindVertexArray(vertexArray); // делаем вершинный массив активным
										// св€зываем vertexBuffer c GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		// копируем содержимое vertices в вершинный буфер vertexBuffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
			&vertices[0], GL_STATIC_DRAW);

		// описание расположени€ параметра вершинного шейдера в вершинном буфере
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0); // включение параметра 0 дл€ шейдера
		glBindBuffer(GL_ARRAY_BUFFER, 0); // отв€зка буферного объекта
		glBindVertexArray(0); // отключение вершинного массива
	}

public:
	GLuint vertexArray; // вершинный массив (объект OpenGL)
	std::vector<glm::vec3> vertices; // последовательность точек
	glm::vec3 color; // цвет, разбитый на составл€ющие RGB
	float thickness; // толщина линии
	path(std::vector<glm::vec3> verts, glm::vec3 col, float thickn) {
		vertices = verts;
		color = col;
		thickness = thickn;
		setupPath();
	}
};

class model {
public:
	std::vector<path> figure; // составл€ющие рисунка
	glm::mat4 modelM; // модельна€ матрица
	model(std::vector<path> fig, glm::mat4 mat) {
		figure = fig;
		modelM = mat;
	}
};