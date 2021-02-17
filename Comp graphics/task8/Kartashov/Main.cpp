#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Figure.h"
#include "Shader.h"


//=============================================================================
// ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
//=============================================================================
std::vector<model> models;
glm::mat4 T; // матрица, в которой накапливаются все преобразования
glm::mat4 lightM; // модельная матрица для источника света
glm::mat4 newLightM;
glm::vec3 S, P, u; // координаты точки наблюдения
				   // точки, в которую направлен вектор наблюдения
				   // вектора направления вверх
float dist; // вспомогательная переменная - расстояние между S и P
float fovy, aspect; // угол обзора и соотношение сторон окна наблюдения
float fovy_work, aspect_work; // рабочие переменные для fovy и aspect
float near_view, far_view; // расстояния до окна наблюдения и до горизонта
float n, f; // рабочие переменные для near_view и far_view
float l, r, t, b; // рабочие вспомогательные переменные
				  // для значений координат левой, правой,
				  // нижней и верхней координаты в СКН
enum projType { Ortho, Frustum, Perspective } pType; // тип трехмерной проекции
double lastX, lastY; // последняя позиция курсора
bool press_mouse = false;
bool checkPolMode = true;//счётчик для кнопки 0

glm::vec3 amb = glm::vec3(0.2f, 0.2f, 0.2f);
glm::vec3 dif = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 spec = glm::vec3(1.0f, 1.0f, 1.0f);
//=============================================================================

void initWorkPars() { // инициализация рабочих параметров камеры
	n = near_view;
	f = far_view;
	fovy_work = fovy;
	aspect_work = aspect;
	float Vy = 2 * near_view * glm::tan(fovy / 2);
	float Vx = aspect * Vy;
	l = -Vx / 2;
	r = -l;
	b = -Vy / 2;
	t = -b;
	dist = glm::length(P - S);
	T = glm::lookAt(S, P, u);
}

void readFromFile(const char* fileName) { // чтение сцены из файла fileName
	// объявление и открытие файла
	std::ifstream in;
	in.open(fileName);
	if (in.is_open()) {
		// файл успешно открыт
		models.clear(); // очищаем имеющийся список рисунков
						// временные переменные для чтения из файла
		glm::mat4 M = glm::mat4(1.f); // матрица для получения модельной матрицы
		glm::mat4 initM; // матрица для начального преобразования каждого рисунка
		std::vector<glm::mat4> transforms; // стек матриц преобразований
		std::vector<mesh> figure; // список мешей очередной модели
		float thickness = 2; // толщина со значением по умолчанию 2

		// составляющие цвета модели со значениями по умолчанию
		glm::vec3 ambient = glm::vec3(0, 0, 0);
		glm::vec3 diffuse = glm::vec3(0, 0, 0);
		glm::vec3 specular = glm::vec3(0, 0, 0);
		float shininess = 1;

		std::string cmd; // строка для считывания имени команды
		// непосредственно работа с файлом
		std::string str; // строка, в которую считываем строки файла
		std::getline(in, str); // считываем из входного файла первую строку
		while (in) { // если очередная строка считана успешно
			// обрабатываем строку
			if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
				// прочитанная строка не пуста и не комментарий
				std::stringstream s(str); // строковый поток из строки str
				s >> cmd;
				if (cmd == "camera") { // положение камеры
					float x, y, z;
					s >> x >> y >> z; // координаты точки наблюдения
					S = glm::vec3(x, y, z);
					s >> x >> y >> z; // точка, в которую направлен вектор наблюдения
					P = glm::vec3(x, y, z);
					s >> x >> y >> z; // вектор направления вверх
					u = glm::vec3(x, y, z);
				}
				else if (cmd == "screen") { // положение окна наблюдения
					s >> fovy_work >> aspect >> near_view >> far_view; // параметры команды
					fovy = glm::radians(fovy_work); // перевод угла из градусов в радианты
				}
				else if (cmd == "color") { // цвет линии
					float r, g, b;
					s >> r >> g >> b; // считываем три составляющие цвета
					ambient = glm::vec3(r, g, b) / 255.f;
					diffuse = ambient;
					specular = ambient;
				}
				else if (cmd == "ambient") { // способность излучать окружающий свет
					float r, g, b;
					s >> r >> g >> b; // считываем три составляющие цвета
					ambient = glm::vec3(r, g, b);
				}
				else if (cmd == "diffuse") { // способность излучать рассеянный свет
					float r, g, b;
					s >> r >> g >> b; // считываем три составляющие цвета
					diffuse = glm::vec3(r, g, b);
				}
				else if (cmd == "specular") { // // способность излучать блики
					float r, g, b;
					s >> r >> g >> b; // считываем три составляющие цвета
					specular = glm::vec3(r, g, b);
				}
				else if (cmd == "shininess") { // степень глянцевости
					s >> shininess;
				}
				else if (cmd == "thickness") { // толщина линии
					s >> thickness; // считываем значение толщины
				}
				else if (cmd == "mesh") { // набор точек
					std::vector<vertex> vertices; // список точек
					int N, K; // количество точек и треугольников
					s >> N >> K;
					std::string str1; // дополнительная строка для чтения из файла

					while (N > 0) { // пока не все точки считали
						std::getline(in, str1); // считываем в str1 из входного файла очередную строку
						// так как файл корректный, то на конец файла проверять не нужно

						if ((str1.find_first_not_of(" \t\r\n") != std::string::npos) && (str1[0] != '#'))
						{
							// прочитанная строка не пуста и не комментарий
							// значит в ней пара координат
							float x, y, z; // переменные для считывания
							float nx, ny, nz; // переменные для считывания координат нормали
							std::stringstream s1(str1); // еще один строковый поток из строки str1
							s1 >> x >> y >> z;
							s1 >> nx >> ny >> nz;
							vertices.push_back({ glm::vec3(x, y, z), glm::vec3(nx, ny, nz) });
							N--; // уменьшаем счетчик после успешного считывания точки
						}
					}

					std::vector<GLuint> indices; // список индексов вершин треугольников

					while (K > 0) { // пока не считали все треугольники
						std::getline(in, str1); // считываем в str1 из входного файла очередную строку
						// так как файл корректный, то на конец файла проверять не нужно

						if ((str1.find_first_not_of(" \t\r\n") != std::string::npos) && (str1[0] != '#'))
						{
							// прочитанная строка не пуста и не комментарий
							// значит в ней тройка индексов вершин треугольника

							GLuint x; // переменная для считывания
							std::stringstream s1(str1); // еще один строковый поток из строки str1
							for (int i = 0; i < 3; i++) // три раза
							{
								s1 >> x; // считываем индекс
								indices.push_back(x); // добавляем индекс в список indices
							}
							K--; // уменьшаем счетчик после успешного считывания точки
						}
					}

					// все точки считаны, генерируем ломаную (path) и кладем ее в список figure
					figure.push_back(mesh(vertices, indices, { ambient, diffuse, specular, shininess }));
				}
				else if (cmd == "model") { // начало описания нового рисунка
					float mVcx, mVcy, mVcz, mVx, mVy, mVz; // параметры команды model
					s >> mVcx >> mVcy >> mVcz >> mVx >> mVy >> mVz; // считываем значения переменных
					float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
					// сдвиг точки привязки из начала координат в нужную позицию
					// после которого проводим масштабирование
					initM = glm::scale(glm::vec3(S)) * glm::translate(glm::vec3(-mVcx, -mVcy, -mVcz));
					figure.clear();
				}
				else if (cmd == "figure") { // формирование новой модели
					models.push_back(model(figure, M * initM));
				}
				else if (cmd == "translate") { // перенос
					float Tx, Ty, Tz; // параметры преобразования переноса
					s >> Tx >> Ty >> Tz; // считываем параметры
					M = glm::translate(glm::vec3(Tx, Ty, Tz)) * M; // добавляем перенос к общему преобразованию
				}
				else if (cmd == "scale") { // масштабирование
					float S; // параметр масштабирования
					s >> S; // считываем параметр
					M = glm::scale(glm::vec3(S)) * M; // добавляем масштабирование к общему преобразованию
				}
				else if (cmd == "rotate") { // поворот
					float theta; // угол поворота в градусах
					float nx, ny, nz; // координаты направляющего вектора оси вращения
					s >> theta >> nx >> ny >> nz; // считываем параметры
												  // добавляем вращение к общему преобразованию
					M = glm::rotate(glm::radians(theta), glm::vec3(nx, ny, nz)) * M;
				}
				else if (cmd == "pushTransform") { // сохранение матрицы в стек
					transforms.push_back(M); // сохраняем матрицу в стек
				}
				else if (cmd == "popTransform") { // откат к матрице из стека
					M = transforms.back(); // получаем верхний элемент стека
					transforms.pop_back(); // выкидываем матрицу из стека
				}
			}
			// считываем очередную строку
			std::getline(in, str);
		}
		initWorkPars();
	}
}



// обработчик события Resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// матрица вращения относительно оси, заданной вектором n,
// проходящей через точку P
glm::mat4 rotateP(float theta, glm::vec3 n, glm::vec3 P) {
	return glm::translate(P) * glm::rotate(theta, n) * glm::translate(-P);
}

// обработчик положения курсора
void cursorPos_callback(GLFWwindow* window, double xpos, double ypos) {
	// вычисляем вектор, задающий ось вращения
	glm::vec3 n = glm::vec3(lastY - ypos, lastX - xpos, 0);
	// создаем матрицу вращения
	glm::mat4 M = glm::rotate(glm::length(n) * 0.002f, n);
	// вращаем току (0, 0, -1), на которую смотрит наблюдатель
	glm::vec3 P = glm::vec3(M * glm::vec4(0, 0, -1, 1));
	// добавляем к преобразованиям переход к новой системе координат наблюдателя
	T = glm::lookAt(glm::vec3(0), P, u) * T;
	lastX = xpos;
	lastY = ypos;
}

// обработчик позиции курсора при включенном курсоре
void cursorPosSave_callback(GLFWwindow* window, double xpos, double ypos) {
	if (press_mouse) {
		glm::mat4 M = rotateP(0.1, glm::vec3(lastX, lastY, 0), glm::vec3(0, 0, -dist)); // матрица вращения относительно точки P
		glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0);
		glm::vec3 S_new = glm::normalize(M * glm::vec4(0, 0, 0, 1)); // вращение начала координат
		// переход к СКН в которой начало координат в новой точке, а направление
		// наблюдения - в точку P
		T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
	}
	lastX = xpos;
	lastY = ypos;
}

// обработчик панелей прокрутки
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	dist += yoffset;
}

// обработчик нажатия кнопки мыши
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) press_mouse = true;
	else if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT) press_mouse = false;
}


// Обработчик нажатия клавиш
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action != GLFW_RELEASE) { // если клавиша нажата
		switch (key) { // анализируем обрабатываемую клавишу
		case GLFW_KEY_ESCAPE: // если клавиша - Escape
		{
			initWorkPars();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		}
		case GLFW_KEY_W:
			if (mode == GLFW_MOD_SHIFT)
			{
				T = glm::lookAt(glm::vec3(0, 0, -0.1), glm::vec3(0, 0, -0.2), glm::vec3(0, 0.1, 0)) * T;
			}
			else
			{
				T = glm::lookAt(glm::vec3(0, 0, -1), glm::vec3(0, 0, -2), glm::vec3(0, 1, 0)) * T;
			}
			break;
		case GLFW_KEY_S:
			if (mode == GLFW_MOD_SHIFT)
			{
				T = glm::lookAt(glm::vec3(0, 0, 0.1), glm::vec3(0, 0, 0), glm::vec3(0, 0.1, 0)) * T;
			}
			else
			{
				T = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * T;
			}
			break;
		case GLFW_KEY_Y:
		{
			glm::vec3 u_new = glm::mat3(glm::rotate(0.1f, glm::vec3(0, 0, -1))) * glm::vec3(0, 1, 0);
			T = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), u_new) * T;
			break;
		}
		case GLFW_KEY_F5:
			if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
				// включается курсор
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				// отключается обработчик положения курсора
				glfwSetCursorPosCallback(window, cursorPosSave_callback);
			}
			else {
				// отключается курсор
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				// включается обработчик положения курсора
				glfwSetCursorPosCallback(window, cursorPos_callback);
			}
			break;
		case GLFW_KEY_F3: {
			OPENFILENAME openFileDialog; // диалог открытия файла
			char fileName[260]; // буфер для имени файла
								// Инициализация файлового диалога
			ZeroMemory(&openFileDialog, sizeof(openFileDialog));
			openFileDialog.lStructSize = sizeof(openFileDialog);
			openFileDialog.hwndOwner = NULL;
			openFileDialog.lpstrFile = fileName;
			openFileDialog.lpstrFile[0] = '\0';
			openFileDialog.nMaxFile = sizeof(fileName);
			openFileDialog.lpstrFilter = "Text files (*.txt)\0*.txt\0All files 2007\0*.*\0";
			openFileDialog.nFilterIndex = 1;
			openFileDialog.lpstrFileTitle = NULL;
			openFileDialog.nMaxFileTitle = 0;
			openFileDialog.lpstrInitialDir = NULL;
			openFileDialog.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			// Ввывод файлового диалога и получение результата
			if (GetOpenFileName(&openFileDialog)) {
				// если файл выбран успешно
				readFromFile(fileName);
			}
			break;
		}
		case GLFW_KEY_A:
			if (mode == GLFW_MOD_SHIFT)
			{
				T = glm::lookAt(glm::vec3(-0.1, 0, 0), glm::vec3(-0.1, 0, -0.1), glm::vec3(0, 0.1, 0)) * T;
			}
			else
			{
				T = glm::lookAt(glm::vec3(-1, 0, 0), glm::vec3(-1, 0, -1), glm::vec3(0, 1, 0)) * T;
			}
			break;
		case GLFW_KEY_D:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				T = glm::lookAt(glm::vec3(0.1, 0, 0), glm::vec3(0.1, 0, -0.1), glm::vec3(0, 0.1, 0)) * T;
			}
			else
			{
				T = glm::lookAt(glm::vec3(1, 0, 0), glm::vec3(1, 0, -1), glm::vec3(0, 1, 0)) * T;
			}
			break;
		}
		case GLFW_KEY_R: {
			glm::vec3 u_new = glm::mat3(glm::rotate(0.1f, glm::vec3(0, 0, 1))) * glm::vec3(0, 1, 0);
			T = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), u_new) * T;
			break;
		}
		case GLFW_KEY_T: {
			if (mode == GLFW_MOD_SHIFT) {
				// матрица вращения относительно точки P
				glm::mat4 M = rotateP(0.1, glm::vec3(1, 0, 0), glm::vec3(0, 0, -dist));
				glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
				glm::vec3 S_new = glm::vec3(M * glm::vec4(0, 0, 0, 1)); // вращение начала координат
																		   // переход к СКН в которой начало координат в новой точке, а направление
																		   // наблюдения - в точку P
				T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
			}
			else {
				glm::mat4 M = glm::rotate(0.1f, glm::vec3(1, 0, 0)); // матрица вращения относительно Ox
				glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
																		// вращение точки, в которую смотрит наблюдатель
				glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1));
				T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
			}
			break;
		}
		case GLFW_KEY_G:
		{
			if (mode == GLFW_MOD_SHIFT) {
				glm::mat4 M = rotateP(0.1, glm::vec3(-1, 0, 0), glm::vec3(0, 0, -dist)); // матрица вращения относительно точки P
				glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
				glm::vec3 S_new = glm::vec3(M * glm::vec4(0, 0, 0, -1)); // вращение начала координат
															   // переход к СКН в которой начало координат в новой точке, а направление
															   // наблюдения - в точку P
				T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
			}
			else {
				glm::mat4 M = glm::rotate(0.1f, glm::vec3(-1, 0, 0)); // матрица вращения относительно Ox
				glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
				glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1)); // вращение точки, в которую смотрит наблюдатель
				T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
			}
			break;
		}

		case GLFW_KEY_F: //вращение против часовой стрелки
		{
			if (mode == GLFW_MOD_SHIFT) {
				glm::mat4 M = rotateP(0.1, glm::vec3(0, 1, 0), glm::vec3(0, 0, -dist)); // матрица вращения относительно точки P
				glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
				glm::vec3 S_new = glm::vec3(M * glm::vec4(0, 0, 0, 1)); // вращение начала координат
															  // переход к СКН в которой начало координат в новой точке, а направление
															  // наблюдения - в точку P
				T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
			}
			else {
				glm::mat4 M = glm::rotate(0.1f, glm::vec3(0, 1, 0)); // матрица вращения относительно Oy
				glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
				glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1)); // вращение точки, в которую смотрит наблюдатель
				T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
			}
			break;
		}
		case GLFW_KEY_H: //вращение по часовой стрелке
		{
			if (mode == GLFW_MOD_SHIFT) {
				glm::mat4 M = rotateP(-0.1, glm::vec3(0, 1, 0), glm::vec3(0, 0, -dist)); // матрица вращения относительно точки P
				glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
				glm::vec3 S_new = glm::vec3(M * glm::vec4(0, 0, 0, 1)); // вращение начала координат
															  // переход к СКН в которой начало координат в новой точке, а направление
															  // наблюдения - в точку P
				T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
			}
			else {
				glm::mat4 M = glm::rotate(-0.1f, glm::vec3(0, 1, 0)); // матрица вращения относительно Oy
				glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
				glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1)); // вращение точки, в которую смотрит наблюдатель
				T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
			}
			break;
		}
		case GLFW_KEY_K:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				b--;
			}
			else
			{
				b++;
			}
			break;
		}
		case GLFW_KEY_L:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				r--;
			}
			else
			{
				r++;
			}
			break;
		}
		case GLFW_KEY_U:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				if (n > 0.1)
				{
					n -= 0.2;
				}
			}
			else
			{
				if (n < (f - 0.1))
				{
					n += 0.2;
				}
			}
			break;
		}
		case GLFW_KEY_O:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				if (f >= (n + 0.1))
				{
					f -= 0.2;
				}
			}
			else
			{
				f += 0.2;
			}
			break;
		}
		case GLFW_KEY_B:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				if (dist >= 0.1)
				{
					dist -= 0.2;
				}
			}
			else
			{
				dist += 0.2;
			}
			break;
		}
		case GLFW_KEY_Z:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				if (fovy_work >= 0.3)
				{
					fovy_work -= 0.05;
				}
			}
			else
			{
				if (fovy_work <= 3)
					fovy_work += 0.05;
			}
			break;
		}
		case GLFW_KEY_X:
		{
			if (mode == GLFW_MOD_SHIFT)	//уменьшение aspect_work на 0.05
			{
				if (aspect_work >= 0.01)
				{
					aspect_work -= 0.05;
				}
			}
			else
			{
				aspect_work += 0.05;
			}
			break;
		}
		case GLFW_KEY_I:
			if (mode == GLFW_MOD_SHIFT) {
				t--;
			}
			else {
				t++;
			}
			break;
		case GLFW_KEY_J:
			if (mode == GLFW_MOD_SHIFT) {
				l--;
			}
			else {
				l++;
			}
			break;
		case GLFW_KEY_1:
			pType = Ortho;
			break;
		case GLFW_KEY_2:
			pType = Frustum;
			break;
		case GLFW_KEY_7:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				amb = amb * glm::vec3(1 / 1.1, 1 / 1.1, 1 / 1.1);
				spec = spec * glm::vec3(1 / 1.1, 1 / 1.1, 1 / 1.1);
			}

			else
			{
				amb = amb * glm::vec3(1.1, 1.1, 1.1);
				spec = spec * glm::vec3(1.1, 1.1, 1.1);
			}

			break;
		}
		case GLFW_KEY_0:
		{
			if (checkPolMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				checkPolMode = false;
			}

			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				checkPolMode = true;
			}

			break;
		}
		case GLFW_KEY_4:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				newLightM = glm::inverse(T) * glm::translate(glm::vec3(0.0f, 0.0f, -0.3f)) * T * newLightM;
			}

			else
			{
				newLightM = glm::inverse(T) * glm::translate(glm::vec3(0.0f, 0.0f, 0.3f)) * T * newLightM;
			}

			break;
		}
		case GLFW_KEY_5:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				newLightM = glm::inverse(T) * glm::translate(glm::vec3(-0.3f, 0.0f, 0.0f)) * T * newLightM;
			}

			else
			{
				newLightM = glm::inverse(T) * glm::translate(glm::vec3(0.3f, 0.0f, 0.0f)) * T * newLightM;
			}
			break;
		}

		case GLFW_KEY_6:
		{
			if (mode == GLFW_MOD_SHIFT)
			{
				newLightM = glm::inverse(T) * glm::translate(glm::vec3(0.0f, -0.3f, 0.0f)) * T * newLightM;
			}

			else
			{
				newLightM = glm::inverse(T) * glm::translate(glm::vec3(0.0f, 0.3f, 0.0f)) * T * newLightM;
			}
			break;
		}
		case GLFW_KEY_3:
			pType = Perspective;
			break;
		default:
			break;
		}
	}
}


int main() {
	glfwInit(); // Инициализация GLFW
	// Задается минимальная требуемая версия OpenGL.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Номер до десятичной точки
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Номер после десятичной точки
	// Используем только средства указанной версии без совместимости с более ранними
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Создаем окно
	GLFWwindow* window = glfwCreateWindow(800, 600, "Kartashov", NULL, NULL);
	if (window == NULL) { // если ссылка на окно не создана
		std::cout << "Вызов glfwCreateWindow закончился неудачей." << std::endl;
		glfwTerminate(); // завершить работу GLFW
		return -1; // завершить программу
	}
	glfwMakeContextCurrent(window); // делаем окно window активным (текущим)
	// Назначение обработчика события Resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// Назначение обработчика нажатия клавиш
	glfwSetKeyCallback(window, key_callback);
	// назначение обработчика положения курсора
	glfwSetCursorPosCallback(window, cursorPosSave_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Инициализация GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Не удалось загрузить GLAD" << std::endl;
		glfwTerminate(); // завершить работу GLFW
		return -1; // завершить программу
	}

	// сообщаем диапазон координат в окне
	// (0, 0) - координаты левого нижнего угла, 800x600 - размеры окна в пикселах
	glViewport(0, 0, 800, 600);

	/*
	//======================================================
	// ВЕРШИННЫЙ ШЕЙДЕР
	//======================================================
		const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"uniform mat4 clipView;\n"
		"void main() {\n"
		" gl_Position = clipView * vec4(position, 1.0);\n"
		"}\0";
	//======================================================

	GLuint vertexShader; // шейдерный объект - вершинный шейдер
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // создаем объект
	// привязываем исходный код к шейдерному объекту
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader); // компилируем шейдер*/
	GLint success; // результат компиляции
	shader vertexShader("Vertex.glsl", GL_VERTEX_SHADER); // вершинный шейдер
	shader fragmentShader("Fragment.glsl", GL_FRAGMENT_SHADER); // фрагментный шейдер

	/* // запрашиваем статус компиляции шейдера в переменную success
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) { // если компиляция прошла с ошибкой
		GLchar infoLog[512]; // объявим контейнер для сообщения об ошибке
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // запрашиваем сообщение
		// выводим сообщение об ошибке на экран
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//======================================================
	// ФРАГМЕНТНЫЙ ШЕЙДЕР
	//======================================================
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 color;\n"
		"uniform vec3 pathColor;\n"
		"void main() {\n"
		" color = vec4(pathColor, 1.0f);\n"
		"}\n\0";
	//=======================================================

	GLuint fragmentShader; // шейдерный объект - фрагментный шейдер
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // создаем объект
	// привязываем исходный код к шейдерному объекту
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader); // компилируем шейдер
	// запрашиваем статус компиляции шейдера в описанную ранее переменную success
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) { // если компиляция прошла с ошибкой
		GLchar infoLog[512]; // объявим контейнер для сообщения об ошибке
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); // запрашиваем сообщение
		// выводим сообщение об ошибке на экран
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}*/

	// Шейдерная программа
	program shaderProgram(vertexShader, fragmentShader);
	/*
	GLuint shaderProgram; // идентификатор шейдерной программы
	shaderProgram = glCreateProgram(); // создаем программный объект
	glAttachShader(shaderProgram, vertexShader.shaderID); // присоединяем вершинный шейдер
	glAttachShader(shaderProgram, fragmentShader.shaderID); // фрагментный шейдер
	glLinkProgram(shaderProgram); // компоновка программы
	// запрашиваем статус компоновки шейдерной программы в переменную success
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) { // если компоновка прошла с ошибкой
		GLchar infoLog[512]; // объявим контейнер для сообщения об ошибке
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog); // запрашиваем сообщение
		// выводим сообщение об ошибке на экран
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
	*/

	// удаление шейдерных объектов
	vertexShader.clear();
	fragmentShader.clear();

	// вершинный шейдер для источника света
	fragmentShader = shader("LightVertex.glsl", GL_VERTEX_SHADER);
	// фрагментный шейдер для источника света
	fragmentShader = shader("LightFragment.glsl", GL_FRAGMENT_SHADER);
	// шейдерная программа для источника света
	program lightShaderProgram(vertexShader, fragmentShader);
	// удаление шейдерных объектов
	vertexShader.clear();
	fragmentShader.clear();

	//второй источник света
	vertexShader = shader("NewLightVertex.glsl", GL_VERTEX_SHADER);
	fragmentShader = shader("NewLightFragment.glsl", GL_FRAGMENT_SHADER);
	program newLightShaderProgram(vertexShader, fragmentShader);
	vertexShader.clear();
	fragmentShader.clear();


	/*
		// запрашиваем у программы shaderProgram расположение переменной pathColor
		GLint pathColorLocation = glGetUniformLocation(shaderProgram, "pathColor");
		// запрашиваем у программы shaderProgram расположение переменной clipView
		GLint clipViewLocation = glGetUniformLocation(shaderProgram, "clipView");
	*/
	// декларируем использование uniform-переменных
	shaderProgram.useUniform("pathColor");
	shaderProgram.useUniform("clipView");
	shaderProgram.useUniform("modelView");
	shaderProgram.useUniform("modelInv");
	shaderProgram.useUniform("viewPos");

	shaderProgram.useUniform("lightPos");
	shaderProgram.useUniform("light.ambient");
	shaderProgram.useUniform("light.diffuse");
	shaderProgram.useUniform("light.specular");

	shaderProgram.useUniform("newLightPos");
	shaderProgram.useUniform("newLight.ambient");
	shaderProgram.useUniform("newLight.diffuse");
	shaderProgram.useUniform("newLight.specular");

	shaderProgram.useUniform("material.ambient");
	shaderProgram.useUniform("material.diffuse");
	shaderProgram.useUniform("material.specular");
	shaderProgram.useUniform("material.shininess");

	lightShaderProgram.useUniform("clipView");
	lightShaderProgram.useUniform("pathColor");

	newLightShaderProgram.useUniform("pathColor");
	newLightShaderProgram.useUniform("clipView");

	//==========================================================
	// НАБОР ИСХОДНЫХ ДАННЫХ ДЛЯ ОТРИСОВКИ ИСТОЧНИКА СВЕТА
	//==========================================================
	GLfloat lightVertices[] = {
	-0.1f, 0.f, 0.f,
	0.1f, 0.f, 0.f,
	0.f, 0.1f, 0.f,
	0.f, -0.1f, 0.f,
	0.f, 0.f, 0.1f,
	0.f, 0.f, -0.1f,
	0.07071f, 0.07071f, 0.f,
	-0.07071f, -0.07071f, 0.f,
	-0.07071f, 0.07071f, 0.f,
	0.07071f, -0.07071f, 0.f,
	0.07071f, 0.f, 0.07071f,
	-0.07071f, 0.f, -0.07071f,
	-0.07071f, 0.f, 0.07071f,
	0.07071f, 0.f, -0.07071f,
	0.f, 0.07071f, 0.07071f,
	0.f, -0.07071f, -0.07071f,
	0.f, -0.07071f, 0.07071f,
	0.f, 0.07071f, -0.07071f,
	0.05774f, 0.05774f, 0.05774f,
	-0.05774f, -0.05774f, -0.05774f,
	-0.05774f, -0.05774f, 0.05774f,
	0.05774f, 0.05774f, -0.05774f,
	-0.05774f, 0.05774f, 0.05774f,
	0.05774f, -0.05774f, -0.05774f,
	0.05774f, -0.05774f, 0.05774f,
	-0.05774f, 0.05774f, -0.05774f
	};

	GLuint lightVertexArray; // объект вершинного массива
							 // создаем вершинный массив, идентификатор которого присваиваем vertexArray
	glGenVertexArrays(1, &lightVertexArray);
	glBindVertexArray(lightVertexArray); // делаем активным вершинный массив

	GLuint lightVertexBuffer; // идентификатор буферного объекта
// создаем буферный объект, идентификатор которого присваиваем vertexBuffer
	glGenBuffers(1, &lightVertexBuffer);
	// привязка vertexBuffer к GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, lightVertexBuffer);
	// в буфер, привязанный к GL_ARRAY_BUFFER копируем содержимое vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
	// описание расположения параметра вершинного шейдера в вершинном буфере
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0); // включение параметра 0 для шейдера
	glBindBuffer(GL_ARRAY_BUFFER, 0); // отвязка буферного объекта
	glBindVertexArray(0); // отключение вершинного массива

	// перемещение источника света из начала координат в точку (0, 0, 5)
	lightM = glm::translate(glm::vec3(0, 0, 5));

	newLightM = glm::translate(glm::vec3(7, 5, -4));


	/*	//==============================================
		// НАБОР ИСХОДНЫХ ДАННЫХ ДЛЯ ОТРИСОВКИ
		//==============================================
		GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
		};

		GLuint vertexArray; // объект вершинного массива
							// создаем вершинный массив, идентификатор которого присваиваем vertexArray
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray); // делаем активным вершинный массив

		GLuint vertexBuffer; // идентификатор буферного объекта
							 // создаем буферный объект, идентификатор которого присваиваем vertexBuffer
		glGenBuffers(1, &vertexBuffer);
		// привязка vertexBuffer к GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		// в буфер, привязанный к GL_ARRAY_BUFFER копируем содержимое vertices
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// описание расположения параметра вершинного шейдера в вершинном буфере
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0); // включение параметра 0 для шейдера
		glBindBuffer(GL_ARRAY_BUFFER, 0); // отвязка буферного объекта

		glBindVertexArray(0); // отключение вершинного массива


		*/

	readFromFile("triangle.txt");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) { // пока окно window не должно закрыться
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // назначаем цвет заливки
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 move = glm::rotate((float)glfwGetTime() * glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 1.0f));
		glm::mat4 lightM1 = move * lightM;

		shaderProgram.use(); // шейдерную программу shaderProgram делаем активной

		/*glBindVertexArray(vertexArray); // делаем активным вершинный массив
		glLineWidth(6); // устанавливаем толщину линии - 6
		glDrawArrays(GL_LINE_STRIP, 0, 3); // отрисовка одного треугольника
		glBindVertexArray(0); // отключаем вершинный массив*/

		glm::mat4 proj; // матрица перехода в пространство отсечения
		switch (pType) {
		case Ortho: // прямоугольная проекция
			proj = glm::ortho(l, r, b, t, n, f);
			break;
		case Frustum: // перспективная проекция с Frustum
			proj = glm::frustum(l, r, b, t, n, f);
			break;
		case Perspective: // перспективная проекция с Perspective
			proj = glm::perspective(fovy_work, aspect_work, n, f);
			break;
		}

		glm::mat4 C = proj * T; // матрица перехода от мировых координат в пространство отсечения

		shaderProgram.setUniform("light.ambient", amb);
		shaderProgram.setUniform("light.diffuse", dif);
		shaderProgram.setUniform("light.specular", spec);

		shaderProgram.setUniform("newLight.ambient", amb);
		shaderProgram.setUniform("newLight.diffuse", dif);
		shaderProgram.setUniform("newLight.specular", spec);

		shaderProgram.setUniform("lightPos", glm::vec3(lightM1 * glm::vec4(0, 0, 0, 1)));
		shaderProgram.setUniform("newLightPos", glm::vec3(newLightM * glm::vec4(0, 0, 0, 1)));
		shaderProgram.setUniform("viewPos", glm::vec3(glm::inverse(T) * glm::vec4(0, 0, 0, 1)));

		for (int k = 0; k < models.size(); k++) { // цикл по моделям
			std::vector<mesh> figure = models[k].figure; // список ломаных очередной модели
			glm::mat4 TM = C * models[k].modelM; // матрица общего преобразования модели
			// пересылка пересылка матрицы TM в переменную clipView шейдерной программы

			shaderProgram.setUniform("clipView", TM);
			shaderProgram.setUniform("modelView", models[k].modelM);
			shaderProgram.setUniform("modelInv", glm::transpose(glm::inverse(models[k].modelM)));

			for (int i = 0; i < figure.size(); i++) {

				// пересылка цвета линии в переменную pathColor шейдерной программы
				shaderProgram.setUniform("material.ambient", figure[i].material.ambient);
				shaderProgram.setUniform("material.diffuse", figure[i].material.diffuse);
				shaderProgram.setUniform("material.specular", figure[i].material.specular);
				shaderProgram.setUniform("material.shininess", figure[i].material.shininess);

				glBindVertexArray(figure[i].vertexArray); // делаем активным вершинный массив i-й ломаной
				// отрисовка набора треугольников по буферу индексов
				glDrawElements(GL_TRIANGLES, figure[i].indices.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0); // отключаем вершинный массив
			}
		}

		lightShaderProgram.use(); // делаем активной программу для источника света
		// матрица перехода в пространство отсечения
		lightShaderProgram.setUniform("clipView", C * lightM1);
		// белый цвет
		lightShaderProgram.setUniform("pathColor", amb + dif + spec);
		glBindVertexArray(lightVertexArray); // делаем активным вершинный массив
		glDrawArrays(GL_LINES, 0, 26); // рисуем 13 отрезков (в массиве 26 точек)
		glBindVertexArray(0); // отключаем вершинный массив

		newLightShaderProgram.use();
		newLightShaderProgram.setUniform("clipView", C * newLightM);
		newLightShaderProgram.setUniform("pathColor", amb + dif + spec);
		glBindVertexArray(lightVertexArray);
		glDrawArrays(GL_LINES, 0, 26);
		glBindVertexArray(0);
		glfwSwapBuffers(window); // поменять местами буферы изображения
		glfwPollEvents(); // проверить, произошли ли какие-то события
	}

	glfwTerminate(); // завершить работу GLFW
	return 0;
}