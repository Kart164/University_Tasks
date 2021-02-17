#pragma once
#include "Matrix.h"
#include <algorithm>
unsigned int codeKS(vec2 P, float minX, float minY, float maxX, float maxY) {
	unsigned int code = 0; // заготовка для кода точки
	// дальнейшие комментарии предполагают, что система координат правая
	if (P.x < minX) { // точка левее области видимости
		code += 1; // получаем единицу в первом разряде
	}
	else if (P.x > maxX) { // точка правее области видимости
		code += 2; // получаем единицу во втором разряде
	}
	if (P.y < minY) { // точка ниже области видимости
		code += 4; // получаем единицу в третьем разряде
	}
	else if (P.y > maxY) { // точка выше области видимости
		code += 8; // получаем единицу в четвертом разряде
	}
	return code;
}bool clip(vec2& A, vec2& B, float minX, float minY, float maxX, float maxY) {
	unsigned int codeA = codeKS(A, minX, minY, maxX, maxY); // код области точки А
	unsigned int codeB = codeKS(B, minX, minY, maxX, maxY); // код области точки B
	while (codeA | codeB) {
		if (codeA & codeB) {
			return false; // отрезок полностью невидим
		}
		if (codeA == 0) { // если A видима, то B невидима
			std::swap(A, B); // меняем местами A и B
			std::swap(codeA, codeB); // меняем местами их коды
		}


		if (codeA & 1) { // точка A левее области видимости
			A.y = A.y + (B.y - A.y) * (minX - A.x) / (B.x - A.x);
			A.x = minX;
		}
		else if (codeA & 2) { // точка A правее области видимости
			A.y = A.y + (B.y - A.y) * (maxX - A.x) / (B.x - A.x);
			A.x = maxX;
		}
		else if (codeA & 4) { // точка A ниже области видимости
			A.x = A.x + (B.x - A.x) * (minY - A.y) / (B.y - A.y);
			A.y = minY;
		}
		else { // точка A выше области видимости
			A.x = A.x + (B.x - A.x) * (maxY - A.y) / (B.y - A.y);
			A.y = maxY;
		}
		codeA = codeKS(A, minX, minY, maxX, maxY);
	}
	return true;
}
