#include <QtWidgets>

#include "MedicalVisualization.h"
#include <QtWidgets/QApplication>



#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
// �㷨ͷ�ļ�
// �ռ仮��ͷ�ļ�
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <vtkRenderWindow.h>

