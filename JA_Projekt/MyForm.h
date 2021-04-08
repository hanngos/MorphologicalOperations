#pragma once
#include "LibraryHandler.h"
#include "BMP.h"
#include <chrono>

extern "C" void asmbinarization(BYTE * binary, int width, int height, BYTE * BMPData);

namespace JAProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Threading;
	using namespace std;
	using namespace std::chrono;

	/// <summary>
	/// Podsumowanie informacji o MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

	public:

	public:

	private: System::Windows::Forms::GroupBox^ runGroup;


	public:
	BMP^ bmp;
	LibraryHandler^ libHandler;

		MyForm(void)
		{
			InitializeComponent();
			threadsNumericUpDown->Value = Environment::ProcessorCount;
			noOfThreadsLabel->Text = L"Recommended no. of threads: " + Environment::ProcessorCount.ToString();
			//klasy lib handler i bmp
			bmp = gcnew BMP();
			libHandler = gcnew LibraryHandler();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~MyForm()
		{
			//usunacie bmp
			if (components)
			{
				delete components;
				bmp->clear();
			}
		}

	private: System::Windows::Forms::TextBox^ filenameTextBox;
	private: System::Windows::Forms::Button^ runButton;


	private: System::Windows::Forms::RadioButton^ cppRadioButton;
	private: System::Windows::Forms::RadioButton^ asmRadioButton;
	private: System::Windows::Forms::GroupBox^ threadsGroup;
	private: System::Windows::Forms::GroupBox^ libGroup;
	private: System::Windows::Forms::GroupBox^ imageGroup;
	private: System::Windows::Forms::GroupBox^ moGroup;

	private: System::Windows::Forms::NumericUpDown^ threadsNumericUpDown;





	private: System::Windows::Forms::Label^ timeLabel;
	private: System::Windows::Forms::Label^ noOfThreads;
	private: System::Windows::Forms::Button^ Browse;
	private: System::Windows::Forms::Label^ noOfThreadsLabel;
	private: System::Windows::Forms::RadioButton^ closingRadioButton;
	private: System::Windows::Forms::RadioButton^ openingRadioButton;
	private: System::Windows::Forms::RadioButton^ dilationRadioButton;
	private: System::Windows::Forms::RadioButton^ erosionRadioButton;


	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->filenameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->runButton = (gcnew System::Windows::Forms::Button());
			this->cppRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->asmRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->threadsGroup = (gcnew System::Windows::Forms::GroupBox());
			this->noOfThreadsLabel = (gcnew System::Windows::Forms::Label());
			this->threadsNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->noOfThreads = (gcnew System::Windows::Forms::Label());
			this->libGroup = (gcnew System::Windows::Forms::GroupBox());
			this->imageGroup = (gcnew System::Windows::Forms::GroupBox());
			this->Browse = (gcnew System::Windows::Forms::Button());
			this->moGroup = (gcnew System::Windows::Forms::GroupBox());
			this->closingRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->openingRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->dilationRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->erosionRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->timeLabel = (gcnew System::Windows::Forms::Label());
			this->runGroup = (gcnew System::Windows::Forms::GroupBox());
			this->threadsGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadsNumericUpDown))->BeginInit();
			this->libGroup->SuspendLayout();
			this->imageGroup->SuspendLayout();
			this->moGroup->SuspendLayout();
			this->runGroup->SuspendLayout();
			this->SuspendLayout();
			// 
			// filenameTextBox
			// 
			this->filenameTextBox->Location = System::Drawing::Point(8, 32);
			this->filenameTextBox->Margin = System::Windows::Forms::Padding(4);
			this->filenameTextBox->Name = L"filenameTextBox";
			this->filenameTextBox->Size = System::Drawing::Size(135, 22);
			this->filenameTextBox->TabIndex = 1;
			this->filenameTextBox->Text = L"image.bmp";
			// 
			// runButton
			// 
			this->runButton->Location = System::Drawing::Point(68, 22);
			this->runButton->Margin = System::Windows::Forms::Padding(4);
			this->runButton->Name = L"runButton";
			this->runButton->Size = System::Drawing::Size(116, 30);
			this->runButton->TabIndex = 2;
			this->runButton->Text = L"Run";
			this->runButton->UseVisualStyleBackColor = true;
			this->runButton->Click += gcnew System::EventHandler(this, &MyForm::runButton_Click);
			// 
			// cppRadioButton
			// 
			this->cppRadioButton->AutoSize = true;
			this->cppRadioButton->Checked = true;
			this->cppRadioButton->Location = System::Drawing::Point(19, 23);
			this->cppRadioButton->Margin = System::Windows::Forms::Padding(4);
			this->cppRadioButton->Name = L"cppRadioButton";
			this->cppRadioButton->Size = System::Drawing::Size(54, 21);
			this->cppRadioButton->TabIndex = 7;
			this->cppRadioButton->TabStop = true;
			this->cppRadioButton->Text = L"C++";
			this->cppRadioButton->UseVisualStyleBackColor = true;
			// 
			// asmRadioButton
			// 
			this->asmRadioButton->AutoSize = true;
			this->asmRadioButton->Location = System::Drawing::Point(19, 52);
			this->asmRadioButton->Margin = System::Windows::Forms::Padding(4);
			this->asmRadioButton->Name = L"asmRadioButton";
			this->asmRadioButton->Size = System::Drawing::Size(56, 21);
			this->asmRadioButton->TabIndex = 8;
			this->asmRadioButton->TabStop = true;
			this->asmRadioButton->Text = L"Asm";
			this->asmRadioButton->UseVisualStyleBackColor = true;
			// 
			// threadsGroup
			// 
			this->threadsGroup->Controls->Add(this->noOfThreadsLabel);
			this->threadsGroup->Controls->Add(this->threadsNumericUpDown);
			this->threadsGroup->Location = System::Drawing::Point(16, 97);
			this->threadsGroup->Margin = System::Windows::Forms::Padding(4);
			this->threadsGroup->Name = L"threadsGroup";
			this->threadsGroup->Padding = System::Windows::Forms::Padding(4);
			this->threadsGroup->Size = System::Drawing::Size(241, 87);
			this->threadsGroup->TabIndex = 9;
			this->threadsGroup->TabStop = false;
			this->threadsGroup->Text = L"Threads";
			// 
			// noOfThreadsLabel
			// 
			this->noOfThreadsLabel->AutoSize = true;
			this->noOfThreadsLabel->Location = System::Drawing::Point(7, 60);
			this->noOfThreadsLabel->Name = L"noOfThreadsLabel";
			this->noOfThreadsLabel->Size = System::Drawing::Size(203, 17);
			this->noOfThreadsLabel->TabIndex = 9;
			this->noOfThreadsLabel->Text = L"Recommended no. of threads: ";
			// 
			// threadsNumericUpDown
			// 
			this->threadsNumericUpDown->Location = System::Drawing::Point(76, 23);
			this->threadsNumericUpDown->Margin = System::Windows::Forms::Padding(4);
			this->threadsNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 64, 0, 0, 0 });
			this->threadsNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->threadsNumericUpDown->Name = L"threadsNumericUpDown";
			this->threadsNumericUpDown->ReadOnly = true;
			this->threadsNumericUpDown->Size = System::Drawing::Size(69, 22);
			this->threadsNumericUpDown->TabIndex = 8;
			this->threadsNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// noOfThreads
			// 
			this->noOfThreads->Location = System::Drawing::Point(0, 0);
			this->noOfThreads->Name = L"noOfThreads";
			this->noOfThreads->Size = System::Drawing::Size(100, 23);
			this->noOfThreads->TabIndex = 0;
			// 
			// libGroup
			// 
			this->libGroup->Controls->Add(this->asmRadioButton);
			this->libGroup->Controls->Add(this->cppRadioButton);
			this->libGroup->Location = System::Drawing::Point(16, 192);
			this->libGroup->Margin = System::Windows::Forms::Padding(4);
			this->libGroup->Name = L"libGroup";
			this->libGroup->Padding = System::Windows::Forms::Padding(4);
			this->libGroup->Size = System::Drawing::Size(241, 82);
			this->libGroup->TabIndex = 10;
			this->libGroup->TabStop = false;
			this->libGroup->Text = L"Library";
			// 
			// imageGroup
			// 
			this->imageGroup->Controls->Add(this->Browse);
			this->imageGroup->Controls->Add(this->filenameTextBox);
			this->imageGroup->Location = System::Drawing::Point(16, 16);
			this->imageGroup->Margin = System::Windows::Forms::Padding(4);
			this->imageGroup->Name = L"imageGroup";
			this->imageGroup->Padding = System::Windows::Forms::Padding(4);
			this->imageGroup->Size = System::Drawing::Size(241, 73);
			this->imageGroup->TabIndex = 11;
			this->imageGroup->TabStop = false;
			this->imageGroup->Text = L"Image";
			// 
			// Browse
			// 
			this->Browse->Location = System::Drawing::Point(150, 28);
			this->Browse->Name = L"Browse";
			this->Browse->Size = System::Drawing::Size(84, 30);
			this->Browse->TabIndex = 2;
			this->Browse->Text = L"Browse...";
			this->Browse->UseVisualStyleBackColor = true;
			this->Browse->Click += gcnew System::EventHandler(this, &MyForm::Browse_Click);
			// 
			// moGroup
			// 
			this->moGroup->Controls->Add(this->closingRadioButton);
			this->moGroup->Controls->Add(this->openingRadioButton);
			this->moGroup->Controls->Add(this->dilationRadioButton);
			this->moGroup->Controls->Add(this->erosionRadioButton);
			this->moGroup->Location = System::Drawing::Point(267, 16);
			this->moGroup->Margin = System::Windows::Forms::Padding(4);
			this->moGroup->Name = L"moGroup";
			this->moGroup->Padding = System::Windows::Forms::Padding(4);
			this->moGroup->Size = System::Drawing::Size(241, 149);
			this->moGroup->TabIndex = 12;
			this->moGroup->TabStop = false;
			this->moGroup->Text = L"Morphological Operation";
			// 
			// closingRadioButton
			// 
			this->closingRadioButton->AutoSize = true;
			this->closingRadioButton->Location = System::Drawing::Point(19, 106);
			this->closingRadioButton->Name = L"closingRadioButton";
			this->closingRadioButton->Size = System::Drawing::Size(75, 21);
			this->closingRadioButton->TabIndex = 3;
			this->closingRadioButton->TabStop = true;
			this->closingRadioButton->Text = L"Closing";
			this->closingRadioButton->UseVisualStyleBackColor = true;
			// 
			// openingRadioButton
			// 
			this->openingRadioButton->AutoSize = true;
			this->openingRadioButton->Location = System::Drawing::Point(19, 79);
			this->openingRadioButton->Name = L"openingRadioButton";
			this->openingRadioButton->Size = System::Drawing::Size(83, 21);
			this->openingRadioButton->TabIndex = 2;
			this->openingRadioButton->TabStop = true;
			this->openingRadioButton->Text = L"Opening";
			this->openingRadioButton->UseVisualStyleBackColor = true;
			// 
			// dilationRadioButton
			// 
			this->dilationRadioButton->AutoSize = true;
			this->dilationRadioButton->Location = System::Drawing::Point(19, 51);
			this->dilationRadioButton->Name = L"dilationRadioButton";
			this->dilationRadioButton->Size = System::Drawing::Size(76, 21);
			this->dilationRadioButton->TabIndex = 1;
			this->dilationRadioButton->TabStop = true;
			this->dilationRadioButton->Text = L"Dilation";
			this->dilationRadioButton->UseVisualStyleBackColor = true;
			// 
			// erosionRadioButton
			// 
			this->erosionRadioButton->AutoSize = true;
			this->erosionRadioButton->Checked = true;
			this->erosionRadioButton->Location = System::Drawing::Point(19, 23);
			this->erosionRadioButton->Name = L"erosionRadioButton";
			this->erosionRadioButton->Size = System::Drawing::Size(77, 21);
			this->erosionRadioButton->TabIndex = 0;
			this->erosionRadioButton->TabStop = true;
			this->erosionRadioButton->Text = L"Erosion";
			this->erosionRadioButton->UseVisualStyleBackColor = true;
			// 
			// timeLabel
			// 
			this->timeLabel->AutoSize = true;
			this->timeLabel->Location = System::Drawing::Point(38, 56);
			this->timeLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->timeLabel->Name = L"timeLabel";
			this->timeLabel->Size = System::Drawing::Size(47, 17);
			this->timeLabel->TabIndex = 3;
			this->timeLabel->Text = L"Time: ";
			// 
			// runGroup
			// 
			this->runGroup->Controls->Add(this->runButton);
			this->runGroup->Controls->Add(this->timeLabel);
			this->runGroup->Location = System::Drawing::Point(267, 172);
			this->runGroup->Name = L"runGroup";
			this->runGroup->Size = System::Drawing::Size(241, 102);
			this->runGroup->TabIndex = 17;
			this->runGroup->TabStop = false;
			this->runGroup->Text = L"Run";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(520, 290);
			this->Controls->Add(this->runGroup);
			this->Controls->Add(this->moGroup);
			this->Controls->Add(this->imageGroup);
			this->Controls->Add(this->libGroup);
			this->Controls->Add(this->threadsGroup);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"Morphological Operations Program";
			this->threadsGroup->ResumeLayout(false);
			this->threadsGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadsNumericUpDown))->EndInit();
			this->libGroup->ResumeLayout(false);
			this->libGroup->PerformLayout();
			this->imageGroup->ResumeLayout(false);
			this->imageGroup->PerformLayout();
			this->moGroup->ResumeLayout(false);
			this->moGroup->PerformLayout();
			this->runGroup->ResumeLayout(false);
			this->runGroup->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void runButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (filenameTextBox->Text == "") { MessageBox::Show("There is no Filename!"); }
		else {
			
			if (bmp->readBMP(msclr::interop::marshal_as<string>(filenameTextBox->Text).c_str()) == "ok") {

				auto start = high_resolution_clock::now();

				bmp->binary = new BYTE[bmp->height * bmp->width];

				if (cppRadioButton->Checked)
					cppbinarization(bmp->binary, bmp->width, bmp->height, bmp->BMPData);
				else
					asmbinarization(bmp->binary, bmp->width, bmp->height, bmp->BMPData);

				int numberOfThreads = Decimal::ToInt32(threadsNumericUpDown->Value);
				bmp->result = new BYTE[bmp->height * bmp->width];

				if (erosionRadioButton->Checked == true) {
					libHandler->erosion(bmp, cppRadioButton->Checked, numberOfThreads);
					bmp->writeBMP(filenameTextBox->Text, "-Erosion.bmp");
				}
				else if (dilationRadioButton->Checked == true) {
					libHandler->dilation(bmp, cppRadioButton->Checked, numberOfThreads);
					bmp->writeBMP(filenameTextBox->Text, "-Dilation.bmp");
				}
				else if (openingRadioButton->Checked == true) {
					libHandler->opening(bmp, cppRadioButton->Checked, numberOfThreads);
					bmp->writeBMP(filenameTextBox->Text, "-Opening.bmp");
				}
				else if (closingRadioButton->Checked == true) {
					libHandler->closing(bmp, cppRadioButton->Checked, numberOfThreads);
					bmp->writeBMP(filenameTextBox->Text, "-Closing.bmp");
				}

				auto stop = high_resolution_clock::now();
				duration<double, milli> duration = stop - start;
				timeLabel->Text = gcnew String(("Time: " + to_string(duration.count()) + " ms").c_str());
				/*ofstream file;
				file.open("riverO.txt", std::ios::app);
				file << numberOfThreads;
				file << "\n	" + to_string(duration.count()) + "\n";
				file.close();*/

			}
			else MessageBox::Show("Cannot open image: " + filenameTextBox->Text);

		}
	}

	private: System::Void Browse_Click(System::Object^ sender, System::EventArgs^ e) {
		//Stream^ myStream;
		OpenFileDialog^ fileDialog = gcnew OpenFileDialog();
		fileDialog->Filter = "bmp files(*.bmp)|*.bmp";

		if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
				filenameTextBox->Text = fileDialog->FileName;
		}
		else MessageBox::Show("Dialog window was cancelled or sth went wrong!");
	}
};
}

