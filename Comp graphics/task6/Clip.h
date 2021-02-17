#pragma once
#include "Matrix.h"
#include <algorithm>
unsigned int codeKS(vec2 P, float minX, float minY, float maxX, float maxY) {
	unsigned int code = 0; // ��������� ��� ���� �����
	// ���������� ����������� ������������, ��� ������� ��������� ������
	if (P.x < minX) { // ����� ����� ������� ���������
		code += 1; // �������� ������� � ������ �������
	}
	else if (P.x > maxX) { // ����� ������ ������� ���������
		code += 2; // �������� ������� �� ������ �������
	}
	if (P.y < minY) { // ����� ���� ������� ���������
		code += 4; // �������� ������� � ������� �������
	}
	else if (P.y > maxY) { // ����� ���� ������� ���������
		code += 8; // �������� ������� � ��������� �������
	}
	return code;
}
	unsigned int codeA = codeKS(A, minX, minY, maxX, maxY); // ��� ������� ����� �
	unsigned int codeB = codeKS(B, minX, minY, maxX, maxY); // ��� ������� ����� B
	while (codeA | codeB) {
		if (codeA & codeB) {
			return false; // ������� ��������� �������
		}
		//9 ������
		if (codeA == 0) { // ���� A ������, �� B ��������
			std::swap(A, B); // ������ ������� A � B
			std::swap(codeA, codeB); // ������ ������� �� ����
		}
		if (codeA & 1) { // ����� A ����� ������� ���������
			A.y = A.y + (B.y - A.y) * (minX - A.x) / (B.x - A.x);
			A.x = minX;
		}
		else if (codeA & 2) { // ����� A ������ ������� ���������
			A.y = A.y + (B.y - A.y) * (maxX - A.x) / (B.x - A.x);
			A.x = maxX;
		}
		else if (codeA & 4) { // ����� A ���� ������� ���������
			A.x = A.x + (B.x - A.x) * (minY - A.y) / (B.y - A.y);
			A.y = minY;
		}
		else { // ����� A ���� ������� ���������
			A.x = A.x + (B.x - A.x) * (maxY - A.y) / (B.y - A.y);
			A.y = maxY;
		}
		codeA = codeKS(A, minX, minY, maxX, maxY);
	}
	return true;
}