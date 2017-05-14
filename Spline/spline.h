#include "TSpline.h"
#include <omp.h>

#pragma once

namespace Spline {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	std::string SystemToStl(String ^s) // Перевод типа String ^ в тип string
	{
		using namespace Runtime::InteropServices;
		const char* ptr = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		return std::string(ptr);
	};

	/// <summary>
	/// Summary for spline
	/// </summary>
	public ref class spline : public System::Windows::Forms::Form
	{
	public:
		spline(void)
		{
			InitializeComponent();
			graphic = this->CreateGraphics();
			this->funcChart->Visible = false;
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
			 double leftBound;
			 double rightBound;
	private: System::Windows::Forms::TextBox^  change_step;

	private: System::Windows::Forms::Label^  label7;
			 double step_ch;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~spline()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: Graphics ^graphic;
	private: System::Windows::Forms::ToolStripMenuItem^  generalToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  drawToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  funcChart;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::ToolStripMenuItem^  drawSplineToolStripMenuItem;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  rb;
	private: System::Windows::Forms::TextBox^  lb;
	private: System::Windows::Forms::TextBox^  points;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->generalToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawSplineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->funcChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->change_step = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->rb = (gcnew System::Windows::Forms::TextBox());
			this->lb = (gcnew System::Windows::Forms::TextBox());
			this->points = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->funcChart))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->generalToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(844, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// generalToolStripMenuItem
			// 
			this->generalToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->drawToolStripMenuItem,
					this->drawSplineToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->generalToolStripMenuItem->Name = L"generalToolStripMenuItem";
			this->generalToolStripMenuItem->Size = System::Drawing::Size(59, 20);
			this->generalToolStripMenuItem->Text = L"General";
			// 
			// drawToolStripMenuItem
			// 
			this->drawToolStripMenuItem->Name = L"drawToolStripMenuItem";
			this->drawToolStripMenuItem->Size = System::Drawing::Size(187, 22);
			this->drawToolStripMenuItem->Text = L"Draw source function";
			this->drawToolStripMenuItem->Click += gcnew System::EventHandler(this, &spline::drawToolStripMenuItem_Click);
			// 
			// drawSplineToolStripMenuItem
			// 
			this->drawSplineToolStripMenuItem->Name = L"drawSplineToolStripMenuItem";
			this->drawSplineToolStripMenuItem->Size = System::Drawing::Size(187, 22);
			this->drawSplineToolStripMenuItem->Text = L"Draw Spline";
			this->drawSplineToolStripMenuItem->Click += gcnew System::EventHandler(this, &spline::drawSplineToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(187, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &spline::exitToolStripMenuItem_Click);
			// 
			// funcChart
			// 
			chartArea1->Name = L"ChartArea1";
			this->funcChart->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->funcChart->Legends->Add(legend1);
			this->funcChart->Location = System::Drawing::Point(12, 27);
			this->funcChart->Name = L"funcChart";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Legend = L"Legend1";
			series1->Name = L"Source function";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Legend = L"Legend1";
			series2->Name = L"Spline";
			this->funcChart->Series->Add(series1);
			this->funcChart->Series->Add(series2);
			this->funcChart->Size = System::Drawing::Size(521, 387);
			this->funcChart->TabIndex = 1;
			this->funcChart->Text = L"chart1";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->change_step);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->rb);
			this->groupBox1->Controls->Add(this->lb);
			this->groupBox1->Controls->Add(this->points);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(539, 27);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 120);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Params";
			// 
			// change_step
			// 
			this->change_step->Location = System::Drawing::Point(94, 95);
			this->change_step->Name = L"change_step";
			this->change_step->Size = System::Drawing::Size(100, 20);
			this->change_step->TabIndex = 8;
			this->change_step->Text = L"1";
			this->change_step->TextChanged += gcnew System::EventHandler(this, &spline::change_step_TextChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(7, 98);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(80, 13);
			this->label7->TabIndex = 7;
			this->label7->Text = L"Step of change";
			// 
			// rb
			// 
			this->rb->Location = System::Drawing::Point(94, 69);
			this->rb->Name = L"rb";
			this->rb->Size = System::Drawing::Size(100, 20);
			this->rb->TabIndex = 5;
			this->rb->Text = L"1";
			this->rb->TextChanged += gcnew System::EventHandler(this, &spline::rb_TextChanged);
			// 
			// lb
			// 
			this->lb->Location = System::Drawing::Point(94, 43);
			this->lb->Name = L"lb";
			this->lb->Size = System::Drawing::Size(100, 20);
			this->lb->TabIndex = 4;
			this->lb->Text = L"0";
			this->lb->TextChanged += gcnew System::EventHandler(this, &spline::lb_TextChanged);
			// 
			// points
			// 
			this->points->Location = System::Drawing::Point(94, 17);
			this->points->Name = L"points";
			this->points->Size = System::Drawing::Size(100, 20);
			this->points->TabIndex = 3;
			this->points->Text = L"2";
			this->points->TextChanged += gcnew System::EventHandler(this, &spline::points_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 73);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(66, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Right Bound";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 46);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Left Bound";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(89, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Quantity of points";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(539, 150);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(32, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Error:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(574, 150);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(60, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"no function";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(745, 44);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(34, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"+";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &spline::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(785, 44);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(37, 23);
			this->button2->TabIndex = 6;
			this->button2->Text = L"-";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &spline::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(745, 69);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(34, 23);
			this->button3->TabIndex = 7;
			this->button3->Text = L"+";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &spline::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(745, 94);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(34, 23);
			this->button4->TabIndex = 8;
			this->button4->Text = L"+";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &spline::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(785, 68);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(37, 23);
			this->button5->TabIndex = 9;
			this->button5->Text = L"-";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &spline::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(785, 94);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(37, 23);
			this->button6->TabIndex = 10;
			this->button6->Text = L"-";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &spline::button6_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(580, 214);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(226, 137);
			this->button7->TabIndex = 11;
			this->button7->Text = L"Default";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &spline::button7_Click);
			// 
			// spline
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(844, 426);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->funcChart);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"spline";
			this->Text = L"spline";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->funcChart))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		
	private: System::Void drawToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (leftBound >= rightBound) {
			rightBound=leftBound+ step_ch;
		}
		this->funcChart->Series["Source function"]->Points->Clear();
		for (double i = leftBound; i < rightBound; i += 1e-2)
			this->funcChart->Series["Source function"]->Points->AddXY(i, calculateFunction(i));
		this->funcChart->Visible = true;
	}
	
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Close();
	}

	private: System::Void drawSplineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 funcChart->Series["Spline"]->Points->Clear();

				 int pointsCount = atoi(SystemToStl(points->Text).c_str());
				 if (pointsCount == NULL || pointsCount == 0)
					 pointsCount = 2;
				 if (pointsCount < 2)
					 pointsCount = 2;

				 points->Text = pointsCount.ToString();

				 double step = (rightBound - leftBound) / pointsCount;

				 double *xCoords = new double[pointsCount + 1];
				 double *yCoords = new double[pointsCount + 1];
				 for (int i = 0; i < pointsCount; i++)
				 {
					 xCoords[i] = leftBound + (double)i * step;
					 yCoords[i] = calculateFunction(xCoords[i]);
				 }

				 xCoords[pointsCount] = rightBound;
				 yCoords[pointsCount] = calculateFunction(xCoords[pointsCount]);

				 TSpline spline;
				 spline.buildSplines(xCoords, yCoords, pointsCount);

				 for (double x = leftBound; x < rightBound; x += 1e-2)
				 {
					 funcChart->Series["Spline"]->Points->AddXY(x, spline.getInterpolatedFunctionValue(x));
				 }

				 double epsilon = 0.0;
				 int n = 0;
				 for (double x = leftBound; x < rightBound; x += step)
				 {
					 epsilon += abs(calculateFunction(x + step / 2.0) - spline.getInterpolatedFunctionValue(x + step / 2.0));
					 n++;
				 }

				 label5->Text = (epsilon / n).ToString();

				 delete[] xCoords;
				 delete[] yCoords;
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		int pointsCount = atoi(SystemToStl(points->Text).c_str());
		pointsCount++;
		points->Text = pointsCount.ToString();
		drawSplineToolStripMenuItem_Click(sender, e);
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		int pointsCount = atoi(SystemToStl(points->Text).c_str());
		pointsCount>2 ? pointsCount-- : pointsCount=pointsCount;
		points->Text = pointsCount.ToString();
		drawSplineToolStripMenuItem_Click(sender, e);
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		char* endPtr;
		leftBound = strtod(SystemToStl(lb->Text->Replace(',', '.')).c_str(), &endPtr);
		step_ch = abs(strtod(SystemToStl(change_step->Text->Replace(',', '.')).c_str(), &endPtr));
		if (leftBound < rightBound - step_ch)
			leftBound += step_ch;
		else {
			leftBound = rightBound - step_ch;
		}
		lb->Text = leftBound.ToString()->Replace(',', '.');
		drawToolStripMenuItem_Click(sender, e);
		drawSplineToolStripMenuItem_Click(sender, e);
	}
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
		char* endPtr;
		step_ch = abs(strtod(SystemToStl(change_step->Text->Replace(',', '.')).c_str(), &endPtr));
		leftBound = strtod(SystemToStl(lb->Text->Replace(',', '.')).c_str(),&endPtr);
		if (leftBound <= rightBound - step_ch)
			leftBound -= step_ch;
		else
			leftBound = rightBound - step_ch;
		lb->Text = leftBound.ToString()->Replace(',', '.');
		drawToolStripMenuItem_Click(sender, e);
		drawSplineToolStripMenuItem_Click(sender, e);
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		char* endPtr;
		step_ch = abs(strtod(SystemToStl(change_step->Text->Replace(',', '.')).c_str(), &endPtr));
		rightBound = strtod(SystemToStl(rb->Text->Replace(',', '.')).c_str(), &endPtr);
		if (rightBound >= leftBound + step_ch)
			rightBound += step_ch;
		else
			rightBound = leftBound + step_ch;
		rb->Text = rightBound.ToString()->Replace(',', '.');
		drawToolStripMenuItem_Click(sender, e);
		drawSplineToolStripMenuItem_Click(sender, e);
	}
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
		char* endPtr;
		step_ch = abs(strtod(SystemToStl(change_step->Text->Replace(',', '.')).c_str(),&endPtr));
		rightBound = strtod(SystemToStl(rb->Text->Replace(',', '.')).c_str(),&endPtr);
		if (rightBound > leftBound + step_ch)
			rightBound-= step_ch;
		else {
			rightBound = leftBound + step_ch;
		}
		rb->Text = rightBound.ToString()->Replace(',', '.');
		drawToolStripMenuItem_Click(sender, e);
		drawSplineToolStripMenuItem_Click(sender, e);
	}
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
		leftBound = 0;
		rightBound = 1;
		step_ch = 1;
		int pointsCount = 2;
		lb->Text = leftBound.ToString();
		rb->Text = rightBound.ToString();
		points->Text = pointsCount.ToString();
		change_step->Text = step_ch.ToString();
		drawSplineToolStripMenuItem_Click(sender, e);
		drawToolStripMenuItem_Click(sender, e);
	}
	private: System::Void change_step_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		char* endPtr;
		step_ch = abs(strtod(SystemToStl(change_step->Text->Replace(',', '.')).c_str(),& endPtr));
	}
	private: System::Void lb_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		char* endPtr;
		leftBound = strtod(SystemToStl(lb->Text->Replace(',', '.')).c_str(), &endPtr);
		if (leftBound >= rightBound) {
			leftBound = rightBound - step_ch;
			lb->Text = leftBound.ToString()->Replace(',', '.');
		}
		drawToolStripMenuItem_Click(sender, e);
		drawSplineToolStripMenuItem_Click(sender, e);
	}
	private: System::Void rb_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		char* endPtr;
		rightBound = strtod(SystemToStl(rb->Text->Replace(',', '.')).c_str(), &endPtr);
		if (rightBound <= leftBound) {
			rightBound = leftBound + step_ch;
			rb->Text = rightBound.ToString()->Replace(',', '.');
		}
		drawToolStripMenuItem_Click(sender, e);
		drawSplineToolStripMenuItem_Click(sender, e);
	}
	private: System::Void points_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		int pointsCount = atoi(SystemToStl(points->Text).c_str());
		points->Text = pointsCount.ToString();
		drawSplineToolStripMenuItem_Click(sender, e);
	}
};
}
