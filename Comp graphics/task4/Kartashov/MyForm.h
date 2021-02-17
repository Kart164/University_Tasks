#pragma once
#include "Matrix.h"
#include "Transform.h"
#include "Figure.h"
#include "Clip.h"
#include <fstream>
#include <sstream>
namespace Kartashov {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	vector<model> models;

	float Vx;
	float Vy;
	float aspectFig;
	mat3 T;// матрица, в которой накапливаются все преобразования
						// первоначально - единичная матрица
	mat3 initT; // матрица начального преобразования

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	protected:
	private: System::Windows::Forms::Button^ btn_Open;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btn_Open = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_Open
			// 
			this->btn_Open->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btn_Open->Location = System::Drawing::Point(200, 9);
			this->btn_Open->Margin = System::Windows::Forms::Padding(0, 0, 0, 0);
			this->btn_Open->Name = L"btn_Open";
			this->btn_Open->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->btn_Open->Size = System::Drawing::Size(75, 23);
			this->btn_Open->TabIndex = 0;
			this->btn_Open->Text = L"Open";
			this->btn_Open->UseVisualStyleBackColor = true;
			this->btn_Open->Click += gcnew System::EventHandler(this, &MyForm::Btn_Open_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->btn_Open);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(155, 120);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: float left = 30, right = 100, top = 20, bottom = 50; // расстояния до границ окна
			 float minX = left, maxX; // диапазон изменения координат x
			 float minY = top, maxY; // диапазон изменения координат y
			 float Wcx = left, Wcy; // координаты левого нижнего угла прямоугольника
			 float Wx, Wy; // ширина и высота прямоугольника
	private: System::Void rectCalc() {
		maxX = ClientRectangle.Width - right; // диапазон изменения координат x
		maxY = ClientRectangle.Height - bottom; // диапазон изменения координат y
		Wcy = maxY; // координаты левого нижнего угла прямоугольника
		Wx = maxX - left; // ширина прямоугольника
		Wy = maxY - top; // ширина и высота прямоугольника
	}
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;

		g->Clear(Color::Aquamarine);
		Pen^ rectPen = gcnew Pen(Color::Black, 2);
		g->DrawRectangle(rectPen,ClientRectangle.Width - 101.f, ClientRectangle.Height - 101.f, 100.f, 100.f);		for (int k = 0; k < models.size(); k++) { // цикл по рисункам
			vector<path> figure = models[k].figure; // список ломаных очередного рису
			mat3 TM = T * models[k].modelM;
			for (int i = 0; i < figure.size(); i++) {
				path lines = figure[i]; // lines - очередная ломаная линия
				Pen^ pen = gcnew Pen(Color::FromArgb(lines.color.x, lines.color.y, lines.color.z));
				pen->Width = lines.thickness;

				vec2 start = normalize(TM * vec3(lines.vertices[0], 1.0)); // первая начальная точка
				for (int j = 1; j < lines.vertices.size(); j++) { // цикл по конечным точкам (от единицы)
					vec2 end = normalize(TM * vec3(lines.vertices[j], 1.0)); // конечная точка
					vec2 tmpEnd = end; // продублировали координаты точки для будущего использования
					if (clip(start, end, minX, minY, maxX, maxY)) { // если отрезок видим
									// после отсечения, start и end - концы видимой части отрезка
						g->DrawLine(pen, start.x, start.y, end.x, end.y); // отрисовка видимой части
					}
					start = tmpEnd; // конечная точка текущего отрезка становится начальной точкой следующего
				}
			}
		}
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		rectCalc();
		Refresh();
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		rectCalc();
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		float Wcx = (ClientRectangle.Width - right - left) / 2.f + left; // координаты центра
		float Wcy = (ClientRectangle.Height - top - bottom) / 2.f + top; // текущего окна
		switch (e->KeyCode) {
		case Keys::Q:
			T = translate(-Wcx, -Wcy) * T; // перенос начала координат в (Wcx, Wcy)
			T = rotate(0.01f) * T; // поворот на 0.01 радиан относительно
									// нового центра
			T = translate(Wcx, Wcy) * T; // перенос начала координат обратно
			break;
		case Keys::E:
			T = translate(-Wcx, -Wcy) * T;
			T = rotate(-0.01f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
		case Keys::Y:
			T = translate(-Wcx, -Wcy) * T;
			T = rotate(-0.05f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
		case Keys::R:
			T = translate(-Wcx, -Wcy) * T;
			T = rotate(0.05f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
		case Keys::W:
			T = translate(0.f, -1.f) * T;
			break;
		case Keys::S:
			T = translate(0.f, 1.f) * T;
			break;
		case Keys::A:
			T = translate(-1.f, 0.f) * T;
			break;
		case Keys::D:
			T = translate(1.f, 0.f) * T;
			break;

		case Keys::T:
			T = translate(0.f, -10.f) * T;
			break;
		case Keys::G:
			T = translate(0.f, 10.f) * T;
			break;
		case Keys::F:
			T = translate(-10.f, 0.f) * T;
			break;
		case Keys::H:
			T = translate(10.f, 0.f) * T;
			break;

		case Keys::X:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1.1f) * T;
			T = translate(Wcx, Wcy) * T;
			break; 
		case Keys::Z:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1/1.1f) * T;
			T = translate(Wcx, Wcy) * T;
			break;

		case Keys::I:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1.1f,1.f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
		case Keys::K:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1/1.1f, 1.f) * T;
			T = translate(Wcx, Wcy) * T;
			break;

		case Keys::O:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1.f, 1.1f) * T;
			T = translate(Wcx, Wcy) * T;
			break;
		case Keys::L:
			T = translate(-Wcx, -Wcy) * T;
			T = scale(1.f, 1/1.1f) * T;
			T = translate(Wcx, Wcy) * T;
			break;

		case Keys::U:
			T = translate(-Wcx, -Wcy) * T;
			T = mirrorX() * T;
			T = translate(Wcx, Wcy) * T;
			break;
		case Keys::J:
			T = translate(-Wcx, -Wcy) * T;
			T = mirrorY() * T;
			T = translate(Wcx, Wcy) * T;
			break;

		case Keys::Escape:
			T = initT; // присвоили T единичную матрицу
			break;

		default:
			break;
		}
		Refresh();
	}
	private: System::Void Btn_Open_Click(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// в файловом диалоге нажата кновка OK
				 // перезапись имени файла из openFileDialog->FileName в fileName
			wchar_t fileName[1024]; // переменная, в которой посимвольно сохраним имя файла
			for (int i = 0; i < openFileDialog->FileName->Length; i++)
				fileName[i] = openFileDialog->FileName[i];
			fileName[openFileDialog->FileName->Length] = '\0';

			// объявление и открытие файла
			ifstream in;
			in.open(fileName);
			if (in.is_open()) 
			{
				// файл успешно открыт
				models.clear(); // очищаем имеющийся список рисунков
			// временные переменные для чтения из файла
				mat3 M = mat3(1.f); // матрица для получения модельной матрицы
				mat3 initM; // матрица для начального преобразования каждого рисунка
				vector<mat3> transforms; // стек матриц преобразований
				vector<path> figure; // список ломаных очередного рисунка
				float thickness = 2; // толщина со значением по умолчанию 2
				float r, g, b; // составляющие цвета
				r = g = b = 0; // значение составляющих цвета по умолчанию (черный)
				string cmd; // строка для считывания имени команды
				// непосредственно работа с файлом
				string str; // строка, в которую считываем строки файла
				getline(in, str); // считываем из входного файла первую строку
				while (in) 
				{ // если очередная строка считана успешно
					 // обрабатываем строку
					if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) 
					{
						// прочитанная строка не пуста и не комментарий
						stringstream s(str); // строковый поток из строки str
						s >> cmd;
						if (cmd == "frame") 
						{ // размеры изображения
							s >> Vx >> Vy; // считываем глобальные значение Vx и Vy
							aspectFig = Vx / Vy; // обновление соотношения сторон
							float Wx = ClientRectangle.Width - left - right; // ширина прямоугольника
							float Wy = ClientRectangle.Height - top - bottom; // высота прямоугольника
							float aspectRect = Wx / Wy; // соотношение сторон окна рисования
							// смещение центра рисунка с началом координат
							mat3 T1 = translate(-Vx / 2, -Vy / 2);
							// масштабирование остается прежним, меняется только привязка
							// коэффициент увеличения при сохранении исходного соотношения сторон
							float S = aspectFig < aspectRect ? Wy / Vy : Wx / Vx;
							mat3 S1 = scale(S, -S);
							// сдвиг точки привязки из начала координат в нужную позицию
							mat3 T2 = translate(Wx / 2 + Wcx, Wcy - Wy / 2);
							// В initT совмещаем эти три преобразования (справа налево)
							initT = T2 * (S1 * T1);
								T = initT;
						}
						else if (cmd == "color") 
						{
							s >> r >> g >> b;
						}
						else if (cmd == "thickness") 
						{
							s >> thickness;
						}
						else if (cmd == "path") 
						{ // набор точек
							vector<vec2> vertices; // список точек ломаной
							int N; // количество точек
							s >> N;
							string str1;
							while (N > 0) 
							{
								getline(in, str1);
								if ((str1.find_first_not_of(" \t\r\n") != string::npos) && (str1[0] != '#')) 
								{
									float x, y;
									stringstream s1(str1);
									s1 >> x >> y;
									vertices.push_back(vec2(x, y));
									N--;
								}
							}
							figure.push_back(path(vertices, vec3(r, g, b), thickness));
						}
						else if (cmd == "model") { // начало описания нового рисунка
							float mVcx, mVcy, mVx, mVy; // параметры команды model
							s >> mVcx >> mVcy >> mVx >> mVy; // считываем значения переменных
							float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
							// сдвиг точки привязки из начала координат в нужную позицию
							// после которого проводим масштабирование
							initM = scale(S) * translate(-mVcx, -mVcy);
							figure.clear();
						}
						else if (cmd == "figure") { // формирование новой модели
							models.push_back(model(figure, M * initM));
						}
						else if (cmd == "translate") { // перенос
							float Tx, Ty; // параметры преобразования переноса
							s >> Tx >> Ty; // считываем параметры
							M = translate(Tx, Ty) * M; // добавляем перенос к общему преобразованию
						}
						else if (cmd == "scale") { // масштабирование
							float S; // параметр масштабирования
							s >> S; // считываем параметр
							M = scale(S) * M; // добавляем масштабирование к общему преобразованию
						}
						else if (cmd == "rotate") { // поворот
							float theta; // угол поворота в градусах
							s >> theta; // считываем параметр
							M = rotate(-theta / 180.f * Math::PI) * M; // добавляем поворот к общему преобразованию
						}
						else if (cmd == "pushTransform") { // сохранение матрицы в стек
							transforms.push_back(M); // сохраняем матрицу в стек
						}
						else if (cmd == "popTransform") { // откат к матрице из стека
							M = transforms.back(); // получаем верхний элемент стека
							transforms.pop_back(); // выкидываем матрицу из стека
						}
					}
					getline(in, str);
				}
				Refresh();
			}
		}
	}

	};
};
