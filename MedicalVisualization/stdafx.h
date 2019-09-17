#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QVTKWidget.h>
#include <QtGui/QWheelEvent>


#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
// �ļ�����ͷ�ļ�
	//�㣬�ߣ���ͷ�ļ�
//��ȡ ����ͷ�ļ�
#include <pcl/octree/octree.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/visualization/pcl_visualizer.h>



#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

#include <vtkVersion.h>
#include <vtkPlaneSource.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkPLYReader.h>
#include <vtkPLYWriter.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLookupTable.h>

#include "CStackWidget.h"
#include "MedicalVisualization.h"
#include "vtkRenderer.h"
#include "vtkDICOMImageReader.h"
#include "vtkPolyDataWriter.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataReader.h"
#include "vtkPolyDataMapper.h"

#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkPLYReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLookupTable.h>


// �㷨ͷ�ļ�
// �ռ仮��ͷ�ļ�


#include <vtkRenderWindow.h>

//��ʾҶ�ӽڵ�
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPoints.h>
#include <vtkLine.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkProperty.h>
#include <vtkPolyLine.h>



#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <vector>
//����ͷ�ļ�
#include <map>
#include <list>
#include <vector>
#include <boost/thread/thread.hpp>



#include "CEdge.h"
#include "Vector3.h"
#include "MyPoint.h"
#include "CTriangles.h"

#include "CEdge.h"
#include "FileOption.h"
#include "CAlgorithm.h"