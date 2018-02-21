#ifndef GALAXY_H
#define GALAXY_H

#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>


#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

using namespace std;
using namespace cv;


struct point{
	float r,x,y,z,vx,vy,vz;
	int npart;

	void calc_radius(float cx,float cy,float cz){
		r = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz));
	}

};


class Galaxy
{
public:
	float x,y,z, maxr, xmin, xmax, ymin, ymax,maxb;
	int npart;
	point *ipart, *fpart;

	Galaxy(int part, ifstream& initpart);

	void read(ifstream& infile);
	void write(Mat &img, int gsize, float weight, int pin);
	void calc_radius();
	void adj_points(int xsize, int ysize, int gsize);
	void add_center(point center);
	void add_center_circle(Mat &img);

};
 
#endif