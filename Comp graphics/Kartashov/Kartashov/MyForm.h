#pragma once

namespace Kartashov {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	float lines1[] = {
		// ������
		0.5f,3.f,1.f,4.5f, // �� ����� ���� ����� �� ���
		1.f,4.5f,0.5f,6.f, // ����� ��� ����� ����� �����
		0.5f,6.f,0.5f, 7.5f, // ����� ��� �����
		0.5f, 7.5f,1.f,8.f, // ����� ��� ���� �����
		1.f,8.f,1.5f,8.f, // ����� ��� ���� ��������
		1.5f,8.f,2.f,7.5f, // ����� ��� ���� ������
		2.f,7.5f,1.5f, 6.f, // ����� ��� ������ ������ ����
		1.5f, 6.f,1.5f,4.5f, // ����� ��� ������ �� �������
		1.5f,4.5f,3.f,4.5f, // �������
		3.f,4.5f,3.f,6.f, // ������ ��� ����� ����� �����
		3.f,6.f,2.5f,7.5f, // ������ ��� �����
		2.5f,7.5f,3.f,8.f, // ������ ��� ���� �����
		3.f,8.f,3.5f,8.f, // ������ ��� ���� ��������
		3.5f,8.f,4.f,7.5f, // ������ ��� ���� ������
		4.f,7.5f,4.f,6.f, // ������ ��� ������ ����
		4.f,6.f,3.5f,4.5f, // ������ ��� ������
		3.5f,4.5f,4.f,3.f, // �� ������� ��� ���� �� ����
		4.f,3.f,3.5f,1.5f, // ������ �����
		3.5f,1.5f,2.5f,1.f, // ���������� ������
		2.5f,1.f,2.f,1.f, // ���������� �����
		2.f,1.f,1.f,1.5f, // ���������� �����
		1.f,1.5f,0.5f,3.f, // ����� �����
						   // ��������
						   4.f,3.f,5.5f,3.5f, // ����� �� ������ ������
						   5.5f,3.5f,7.f,3.5f, // ����� ����
						   7.f,3.5f,7.5f,2.5f, // ����� ������ �� ������
						   7.5f,2.5f,8.f,2.5f, // ����� ������
						   8.f,2.5f,8.f,2.f, // ����� ������
						   8.f,2.f,7.5f,2.f, // ����� ��� ������ ������
						   7.5f,2.f,7.5f,0.5f, // ������ ���� ������ ������ ����
						   7.5f,0.5f,6.5f,0.5f, // ������ ���� ���
						   6.5f,0.5f,6.5f,1.f, // ������ ���� �����
						   6.5f,1.f,6.f,1.f, // ����� ������ ���
						   6.f,1.f,6.f,0.5f, // ����� ������ ���� ������
						   6.f,0.5f,5.f,0.5f, // ����� ������ ���� ���
						   5.f,0.5f,5.f,1.f, // ����� ������ ���� �����
						   5.f,1.f,4.f,1.f, // ����� ������� � ��������� ������
						   4.f,1.f,4.f,0.5f, // ������ �������� ���� ������
						   4.f,0.5f,3.f,0.5f, // ������ �������� ���� ���
						   3.f,0.5f,3.f,1.f, // ������ �������� ���� �����
						   3.f,1.f,2.5f,1.f, // ����� �������� ���
						   2.5f,1.f,2.5f,0.5f, // �������� ���� ������
						   2.5f,0.5f,1.5f,0.5f, // �������� ���� ���
						   1.5f,0.5f,1.5f,1.25f, // �������� ���� �����
												 // ����� ����
												 1.5f,3.5f,1.5f,3.f, // ����� ���� ����� ������ ����
												 1.5f,3.f,2.f,3.f, // ����� ���� ���
												 2.f, 3.f,2.f,3.5f, // ����� ���� ������
												 2.f,3.5f,1.5f,3.5f, // ����� ���� ����
																	 // ������ ����
																	 2.5f,3.5f,2.5f,3.f, // ������ ���� �����
																	 2.5f,3.f,3.f, 3.f, // ������ ���� �����
																	 3.f,3.f,3.f,3.5f, // ������ ���� ������
																	 3.f,3.5f,2.5f,3.5f, // ������ ���� ������
																						 // ����� ��������
																						 1.f,5.5f,1.f,7.f, // ����� ����� ��������
																						 3.5f,5.5f,3.5f,7.f, // ������ ����� ��������
																											 // ���
																											 2.f,2.5f,2.5f,2.5f, // ��� ������
																											 2.5f,2.5f,2.25f,2.f, // ��� ������
																											 2.25f,2.f,2.f,2.5f // ��� �����
	};
	float Vzx = 8.5f;
	float Vzy = 8.5f;


	float lines[] = {
		//left left leg
		0.5f,0.5f,2.f,0.5f,
		0.5f,0.5f,1.5f,1.5f,
		2.f,0.5f,2.f,1.5f,
		1.5f,1.5f,1.5f,5.5f,
		2.f,1.5f,2.5f,5.5f,

		//left leg
		2.f,0.5f,3.5f,0.5f,
		2.f,0.5f,2.5f,1.5f,
		3.5f,0.5f,3.f,1.5f,
		2.5f,1.5f,2.5f,5.5f,
		3.f,1.5f,3.5f,5.f,
		
		//right legs
		5.f,0.5f,7.5f,0.5f,
		5.f,0.5f,5.5f,1.5f,
		5.5f,0.5f,6.f,1.5f,
		5.5f,1.5f,6.5f,1.5f,
		6.f,1.5f,6.5f,2.f,
		6.5f,1.5f,7.f,2.f,
		6.5f,2.f,5.5f,4.25f,
		7.f,2.f,6.f,4.f,
		6.f,4.f,6.5f,5.5f,
		6.5f,5.5f,6.5f,6.5f,
		6.5f,6.5f,7.f,6.f,
		7.f,6.f,7.5f,5.f,
		7.5f,5.f,7.5f,4.5f,

		7.5f,0.5f,7.f,1.f,
		7.f,1.f,7.5f,2.f,
		7.5f,2.f,7.f,3.f,
		7.f,3.f,7.5f,4.5f,

		//tail
		7.5f,4.5f,8.5f,5.f,
		8.5f,5.f,8.f,7.f,
		8.f,7.f,8.5f,7.5f,
		8.5f,7.5f,9.f,7.5f,
		9.f,7.5f,9.5f,8.5f,
		9.5f,8.5f,8.5f,8.f,
		8.5f,8.f,8.5f,7.5f,

		8.f,7.f,8.f,5.5f,
		8.f,5.5f,7.5f,5.f,

		//body
		1.5f,5.5f,1.f,6.5f,
		1.f,6.5f,1.5f,7.5f,
		1.5f,7.5f,2.f,8.f,

		4.f,8.f,5.5f,7.f,
		5.5f,7.f,6.5f,6.5f,

		2.f,6.f,2.5f,5.5f,
		2.5f,5.5f,3.f,5.5f,
		3.f,5.5f,3.5f,5.f,
		3.5f,5.f,6.f,4.f,

		//neck
		2.f,8.f,2.5f,10.5f,
		4.f,8.f,4.f,12.f,
		2.5f,10.5f,2.5f,12.23f,

		//head
		3.5f,12.5f,2.f,12.f,
		2.f,12.f,1.f,12.5f,
		1.f,12.5f,1.f,13.f,
		1.f,13.f,2.f,13.5f,
		2.f,13.5f,2.f,14.f,//(ear start)
		2.f,14.f,2.5f,14.5f,
		2.5f,14.5f,3.5f,14.5f,
		3.5f,14.5f,4.f,14.f,
		4.f,14.f,4.5f,14.5f,
		4.5f,14.5f,5.5f,14.5f,
		5.5f,14.5f,5.5f,14.f,
		5.5f,14.f,4.5f,13.5f,
		4.5f,13.5f,5.f,13.f,
		5.f,13.f,4.f,12.f,

		//left ear
		2.f,14.f,1.5f,14.5f,
		1.5f,14.5f,0.5f,14.5f,
		0.5f,14.5f,1.f,13.5f,
		1.f,13.5f,2.f,14.f,

		//eyes
		2.f,13.5f,2.5f,13.5f,
		2.5f,13.5f,2.5f,14.f,
		2.5f,14.f,2.f,13.5f,

		3.f,13.5f,3.5f,13.5f,
		3.5f,13.5f,3.5f,14.f,
		3.5f,14.f,3.f,13.5f,

		
		7.5f,4.5f,7.f,4.5f,
		7.f,4.5f,7.f,5.f,
		7.f,5.f,7.5f,5.f,

		6.5f,5.5f,6.f,5.5f,
		6.f,5.5f,6.f,6.5f,
		6.f, 6.5f,6.5f,6.5f,

		5.5f,5.5f,5.f,5.5f,
		5.f,5.5f,5.f,5.f,
		5.f,5.f,5.5f,5.5f,

		5.5f,6.f,5.f,6.f,
		5.f,6.f,5.f,6.5f,
		5.f,6.5f,4.5f,6.5f,
		4.5f,6.5f,4.5f,7.f,
		4.5f,7.f,5.5f,7.f,
		5.5f,7.f,5.5f,6.f,

		4.5f,6.f,4.f,6.5f,
		4.f,6.5f,3.5f,6.f,
		3.5f,6.f,4.f,5.5f,
		4.f,5.5f,4.5f,6.f,

		4.f,7.f,4.f,7.5f,
		4.f,7.5f,3.5f,7.5f,
		3.5f,7.5f,3.5f,7.f,
		3.5f,7.f,4.f,7.f,

		3.f,7.5f,2.5f,7.f,
		2.5f,7.f,3.f,7.f,
		3.f,7.f,3.f,7.5f,

		2.5f,7.5f,2.f,7.5f,
		2.f,7.5f,2.f,8.f,
		2.f,8.f,2.5f,8.f,
		2.5f,8.f,2.5f,7.5f,

		4.f,8.f,3.f,8.f,
		3.f,8.f,4.f,9.f,

		3.f,8.5f,2.5f,9.f,
		2.5f,9.f,2.5f,8.5f,
		2.5f,8.5f,3.f,8.5f,

		4.f,9.5f,3.5f,10.f,
		3.5f,10.f,3.f,9.5f,
		3.f,9.5f,4.f,9.5f,

		4.f,10.f,3.5f,10.5f,
		3.5f,10.5f,3.5f,11.f,
		3.5f,11.f,4.f,11.5f,

		3.f,10.5f,2.5f,10.5f,
		3.f,10.5f,2.5f,11.f,

		2.5f,11.5f,3.f,12.f,
		3.f,12.f,3.5f,11.5f,
		3.5f,11.5f,3.f,11.f,
		3.f,11.f,2.5f,11.5f

	};

	unsigned int arrayLength = sizeof(lines) / sizeof(float);
	float Vx = 10.f;
	float Vy = 15.f;
	float aspectFig = Vx / Vy;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->DoubleBuffered = true;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: bool keepAspectRatio; //����� ����������� ������
	private: bool switchPic; //����� �������
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		System::Drawing::Graphics^ g = e->Graphics;

		g->Clear(Color::Aquamarine);
		Pen^ blackPen = gcnew Pen(Color::Black, 2);
		float Wx = ClientRectangle.Width;
		float Wy = ClientRectangle.Height;
		
		float VRx, VRy;
		float* LINE;
		unsigned int arrayLength;

		if (switchPic) {
			VRx = Vx;
			VRy = Vy;

			arrayLength = sizeof(lines) / sizeof(float);
			LINE = lines;
		}
		else {
			VRx = Vzx;
			VRy = Vzy;
			arrayLength = sizeof(lines1) / sizeof(float);
			LINE = lines1;
		}
		float aspectFig = VRx / VRy;
		float aspectForm = Wx / Wy; // ����������� ������ ���� ���������
		float Sx, Sy;
		if (keepAspectRatio) {
			// �����������s ���������� ��� ���������� ��������� ����������� ������
			Sx = Sy = aspectFig < aspectForm ? Wy / Vy : Wx / Vx;
		}
		else {
			Sx = Wx / Vx; // ����������� ���������� �� ��� Ox
			Sy = Wy / Vy;
		}
		float Ty = Sy * Vy; // �������� � ������������� ������� �� ��� Oy ����� ����� �����
		for (int i = 0; i < arrayLength; i += 4) {
			g->DrawLine(blackPen, Sx * LINE[i], Ty - Sy * LINE[i + 1],
				Sx * LINE[i + 2], Ty - Sy * LINE[i + 3]);
		}
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		Refresh();
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		keepAspectRatio = true;
		switchPic = true;
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::M:
			keepAspectRatio = !keepAspectRatio;
			break;
		case Keys::N:
			switchPic = !switchPic;
			break;
		default:
			break;
		}		Refresh();
	}
	};
}
