#pragma once
#include <math.h>
#include "Matrix.h"

mat3 translate(float Tx, float Ty) {
	mat3* res = new mat3(1.f); // ������� ��������� �������
	(*res)[0][2] = Tx; // ��������
	(*res)[1][2] = Ty; // �������� � ��������� �������
	return *res;
}
mat3 scale(float Sx, float Sy) {
	mat3* res = new mat3(1.f);
	(*res)[0][0] = Sx;
	(*res)[1][1] = Sy; // �������� �� ������� ���������
	return *res;
}

mat3 scale(float S) {
	return scale(S, S);
}
mat3 mirrorX() {
	return scale(-1.f, 1.f);
}
mat3 mirrorY() {
	return scale(1.f, -1.f);
}
mat3 rotate(float theta) {
	mat3* res = new mat3(1.f); // ������� ��������� �������
	(*res)[0][0] = (*res)[1][1] = (float)cos(theta); // ��������� ������� ���������
	(*res)[0][1] = (float)sin(theta); // ����� � ������ ������ (� ������)
	(*res)[1][0] = -(*res)[0][1]; // ����� �� ������ ������ (� �������)
	return *res;
}