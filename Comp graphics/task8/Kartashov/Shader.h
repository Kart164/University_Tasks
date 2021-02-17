#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad\glad.h>
#include <map>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

class shader 
{

public:
	GLuint shaderID; // идентификатор шейдера

	shader(const char* fileName, GLenum shaderType) {
		std::string fileStd = readTextFile(fileName); // содержимое файла в виде строки
		const char* shaderSource = fileStd.c_str(); // содержимое файла в виде массива символов
		shaderID = glCreateShader(shaderType); // создаем объект
		// прив€зываем исходный код к шейдерному объекту
		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID); // компилируем шейдер
		GLint success; // результат компил€ции
		// запрашиваем статус компил€ции шейдера в переменную success
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success) { // если компил€ци€ прошла с ошибкой
			GLchar infoLog[512]; // объ€вим контейнер дл€ сообщени€ об ошибке
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog); // запрашиваем сообщение
				// выводим сообщение об ошибке на экран
			std::string strShaderType; // тип шейдера в строке

			switch (shaderType) 
			{
			case GL_VERTEX_SHADER: strShaderType = "VERTEX"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "GEOMETRY"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "FRAGMENT"; break;
			}

			std::cout << "ERROR::SHADER::" << strShaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	void clear() 
	{ 
		// очистка шейдера
		// удаление шейдерного объекта
		glDeleteShader(shaderID);
	}


private:
	std::string readTextFile(const char* fileName) 
	{
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			shaderFile.open(fileName); // файл открываетс€ дл€ чтени€
			std::stringstream shaderStream; // строковый поток дл€ вывода содержимого файла
			shaderStream << shaderFile.rdbuf(); // выводим все из файла в строковый поток
			shaderFile.close(); // закрываем файл
			return shaderStream.str(); // возвращаем строку из строкового потока
		}
		catch (std::ifstream::failure e) 
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ:" << fileName << std::endl;
		}
	}
};

class program {
public:
	GLuint programID; // идентификатор шейдерной программы
	std::map<std::string, GLint> uniforms; // uniform-переменные
	program(shader vertexShader, shader fragmentShader) 
	{
		programID = glCreateProgram(); // создаем программный объект
		glAttachShader(programID, vertexShader.shaderID); // присоедин€ем вершинный шейдер
		glAttachShader(programID, fragmentShader.shaderID); // и фрагментный шейдер
		glLinkProgram(programID); // компоновка программы
		GLint success; // результат компил€ции
		// запрашиваем статус компоновки шейдерной программы в переменную success
		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		
		if (!success) 
		{ 
			// если компоновка прошла с ошибкой
			GLchar infoLog[512]; // объ€вим контейнер дл€ сообщени€ об ошибке
			glGetProgramInfoLog(programID, 512, NULL, infoLog); // запрашиваем сообщение
			// выводим сообщение об ошибке на экран
			std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
		}
	}

	void use() // активизаци€ шейдерной программы
	{ 
		glUseProgram(programID);
	}

	void useUniform(std::string uniformName) // регистраци€ переменной
	{
		// им€ представл€ем в виде массива символов, запрашиваем расположение
		// записываем расположение в ассоциированный массив
		uniforms[uniformName] = glGetUniformLocation(programID, uniformName.c_str());
	}

	void setUniform(std::string uniformName, glm::vec3 value)
	{
		glUniform3fv(uniforms[uniformName], 1, glm::value_ptr(value));
	}

	void setUniform(std::string uniformName, glm::mat4 value) 
	{
		glUniformMatrix4fv(uniforms[uniformName], 1, GL_FALSE, glm::value_ptr(value));
	}

	void setUniform(std::string uniformName, float value) {
		// загрузка одного вещественного числа
		glUniform1f(uniforms[uniformName], value);
	}

};