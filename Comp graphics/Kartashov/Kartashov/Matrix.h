#pragma once
class vec2 {
public:
	float x, y;
	vec2() {}
	vec2(float a, float b) : x(a), y(b) {}	
};

class vec3 {
public:
	float x, y, z;
	vec3() {}
	vec3(float a, float b, float c) : x(a), y(b), z(c) {}
	vec3(vec2 v, float c) : vec3(v.x, v.y, c) {}
	vec3& operator*=(const vec3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	const vec3 operator*(const vec3& v) {
		return vec3(*this) *= v;// делаем временную копию текущего объекта,
								// которую домножаем на данный вектор,
								// и возвращаем ее как результат
	}
	float& operator[](int i) {
		return ((float*)this)[i]; // ссылку на текущий объект рассматриваем как ссылку
								 // на нулевой элемент массива значений типа float,
								// после чего обращаемс€ к его i-му элементу
	}

	
	

};
vec2 normalize(vec3 v) {
		return vec2(v.x / v.z, v.y / v.z);
	}

float dot(vec3 v1, vec3 v2) {
		vec3 tmp = v1 * v2; // вычисл€ем произведени€ соответствующих координат
		return tmp.x + tmp.y + tmp.z; // и возвращаем их сумму
}


class mat3 {
public:
	vec3 row1, row2, row3;
	mat3() {}
	mat3(vec3 r1, vec3 r2, vec3 r3) : row1(r1), row2(r2), row3(r3) {}	mat3(float a) {
		row1 = vec3(a, 0.f, 0.f);
		row2 = vec3(0.f, a, 0.f);
		row3 = vec3(0.f, 0.f, a);
	}	vec3& operator[](int i) {
		return ((vec3*)this)[i]; // массив значений типа vec3
	}	const vec3 operator* (const vec3& v) {
		vec3* res = new(vec3); // создаем новый вектор (дл€ результата)
		for (int i = 0; i < 3; i++) {
			(*res)[i] = dot((*this)[i], v); // i-й элемент вектора - скал€рное произведение
		}
		return *res;
	}
	mat3 transpose() {
		mat3 tmp(*this); // делаем временную копию матрицы
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				(*this)[i][j] = tmp[j][i]; // замен€ем элементы текущего объекта
				// из временной копии
		return *this;
	}

	mat3& operator*= (const mat3& m) {
		mat3 A(*this), B(m); // создаем копии исходных матриц
		B.transpose(); // транспонируем вторую матрицу
		for (int i = 0; i < 3; i++)
			(*this)[i] = A * B[i]; // в i-ю строку текщего объекта записываем
			// результат перемножени€ первой матрицы с i-й строкой
			// транспонированной матрицы,
		return (*this).transpose(); // транспонируем текущий объект, получаем результат
	}
	const mat3 operator* (const mat3& m) {
		return mat3(*this) *= m;
	}


};