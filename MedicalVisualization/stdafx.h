#include <QtWidgets>
#include "MedicalVisualization.h"
#include <QtWidgets/QApplication>


//����ͷ�ļ�
#include <map>
#include <list>
#include <vector>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
// �ļ�����ͷ�ļ�
	//�㣬�ߣ���ͷ�ļ�
#include "CTriangles.h"
//��ȡ ����ͷ�ļ�
#include <pcl/octree/octree.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "MyPoint.h"
#include "CTriangles.h"
#include "CEdge.h"

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

#include <vtkRenderWindow.h>