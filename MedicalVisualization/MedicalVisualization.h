#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MedicalVisualization.h"

class MedicalVisualization : public QMainWindow
{
	Q_OBJECT

public:
	MedicalVisualization(QWidget *parent = Q_NULLPTR);

private:
	Ui::MedicalVisualizationClass ui;
};
