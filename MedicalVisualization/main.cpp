#include "stdafx.h"
#include "FileOption.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MedicalVisualization w;
	w.show();
	//≤‚ ‘
	FileOption ab;
	
	ab.ReadAscllStlFile("bunny.stl");
	
	return a.exec();

}
