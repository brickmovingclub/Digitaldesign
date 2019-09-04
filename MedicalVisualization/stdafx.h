#include <QtWidgets>
#include "MedicalVisualization.h"
#include <QtWidgets/QApplication>

//容器头文件
#include <map>
#include <list>
#include <vector>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
// 文件操作头文件
	//点，线，面头文件
#include "CTriangles.h"
//读取 保存头文件
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

#include "CEdge.h"
#include "FileOption.h"
#include "CAlgorithm.h"


// 算法头文件
// 空间划分头文件
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
#include "CEdge.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include "Vector3.h"
#include <vtkRenderWindow.h>

