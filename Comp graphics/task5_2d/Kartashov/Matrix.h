#pragma once
#pragma once
class vec2 {
public:
	float x, y;
	vec2() {}
	vec2(float a, float b) : x(a), y(b) {}
	vec2& operator*=(const vec2& v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}
	const vec2 operator*(const vec2& v) {
		return vec2(*this) *= v;
	}
	float& operator[](int i) {
		return ((float*)this)[i];
	}

};
float dot(vec2 v1, vec2 v2) {
	vec2 tmp = v1 * v2;
	return tmp.x + tmp.y;
}


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
		return vec3(*this) *= v;
	}
	float& operator[](int i) {
		return ((float*)this)[i];
	}
};
class vec4 {
public:
	float x, y, z, a;
	vec4() {}
	vec4(float a, float b, float c, float d) : x(a), y(b), z(c), a(d) {}
	vec4(vec3 v, float c) : vec4(v.x, v.y, v.z, c) {}
	vec4& operator*=(const vec4& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		a *= v.a;
		return *this;
	}
	const vec4 operator*(const vec4& v) {
		return vec4(*this) *= v;
	}
	float& operator[](int i) {
		return((float*)this)[i];
	}
};
vec3 normalize(vec4 v) {
	return vec3(v.x / v.a, v.y / v.a, v.z / v.a);
}
float dot(vec4 v1, vec4 v2) {
	vec4 tmp = v1 * v2;
	return tmp.x + tmp.y + tmp.z + tmp.a;
}
float dot(vec3 v1, vec3 v2) {
	vec3 tmp = v1 * v2;
	return tmp.x + tmp.y + tmp.z;
}
class mat4 {
public:
	vec4 row1, row2, row3, row4;

	mat4(vec4 r1, vec4 r2, vec4 r3, vec4 r4) : row1(r1), row2(r2), row3(r3), row4(r4) {}
	mat4(float a) {
		row1 = vec4(a, 0.f, 0.f, 0.f);
		row2 = vec4(0.f, a, 0.f, 0.f);
		row3 = vec4(0.f, 0.f, a, 0.f);
		row4 = vec4(0.f, 0.f, 0.f, a);
	}
	mat4() {}
	vec4& operator[](int i) { return ((vec4*)this)[i]; }
	mat4 transpose() {
		mat4 tmp(*this);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				(*this)[i][j] = tmp[j][i];
		return *this;
	}
	const vec4 operator* (const vec4& v) {
		vec4* res = new(vec4);
		for (int i = 0; i < 4; i++) {
			(*res)[i] = dot((*this)[i], v);
		}
		return *res;
	}
	mat4& operator*= (const mat4& m) {
		mat4 A(*this), B(m);
		B.transpose();
		for (int i = 0; i < 4; i++)
			(*this)[i] = A * B[i];
		return (*this).transpose();
	}
	const mat4 operator* (const mat4& m) {
		return mat4(*this) *= m;
	}
};
class mat3 {
public:
	vec3 row1, row2, row3;
	mat3(mat4 m) {
		row1 = vec3(m.row1.x, m.row1.y, m.row1.z);
		row2 = vec3(m.row2.x, m.row2.y, m.row2.z);
		row3 = vec3(m.row3.x, m.row3.y, m.row3.z);
	}
	mat3() {}
	mat3(vec3 r1, vec3 r2, vec3 r3) : row1(r1), row2(r2), row3(r3) {}
	mat3(float a) {
		row1 = vec3(a, 0.f, 0.f);
		row2 = vec3(0.f, a, 0.f);
		row3 = vec3(0.f, 0.f, a);
	}
	vec3& operator[](int i) {
		return ((vec3*)this)[i];
	}
	mat3 transpose() {
		mat3 tmp(*this);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				(*this)[i][j] = tmp[j][i];
		return *this;
	}
	const vec3 operator* (const vec3& v) {
		vec3* res = new(vec3);
		for (int i = 0; i < 3; i++) {
			(*res)[i] = dot((*this)[i], v);
		}
		return *res;
	}
	mat3& operator*= (const mat3& m) {
		mat3 A(*this), B(m);
		B.transpose();
		for (int i = 0; i < 3; i++)
			(*this)[i] = A * B[i];
		return (*this).transpose();
	}
	const mat3 operator* (const mat3& m) {
		return mat3(*this) *= m;
	}
};

class mat2 {
public:
	vec2 row1, row2;
	mat2() {}
	mat2(vec2 r1, vec2 r2) : row1(r1), row2(r2) {}
	mat2(float a) {
		row1 = vec2(a, 0.f);
		row2 = vec2(0.f, a);
	}
	vec2& operator[](int i) {
		return ((vec2*)this)[i];
	}
	mat2 transpose() {
		mat2 tmp(*this);
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				(*this)[i][j] = tmp[j][i];
		return *this;
	}
	const vec2 operator* (const vec2& v) {
		vec2* res = new(vec2);
		for (int i = 0; i < 2; i++) {
			(*res)[i] = dot((*this)[i], v);
		}
		return *res;
	}
	mat2& operator*= (const mat2& m) {
		mat2 A(*this), B(m);
		B.transpose();
		for (int i = 0; i < 2; i++)
			(*this)[i] = A * B[i];
		return (*this).transpose();
	}
	const mat2 operator* (const mat2& m) {
		return mat2(*this) *= m;
	}
	mat2(mat3 m) {
		row1 = vec2(m[0][0], m[0][1]);
		row2 = vec2(m[1][0], m[1][1]);
	}
};

vec2 normalize(vec3 v) {
	return vec2(v.x / v.z, v.y / v.z);
}