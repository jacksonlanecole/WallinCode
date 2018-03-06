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
	float bx,by,bz,fx,fy,fz;  // beginning and final x,y,z coordinates;
    float maxr, xmin, xmax, ymin, ymax,maxb;
	int npart;
	point *ipart, *fpart;

    Galaxy();

	void read(ifstream& infile,int part, char state);
	void write(Mat &img, int gsize, float weight, int pin, point *pts);
    void simple_write( Mat &img, point *pts);
	void calc_radius();
	void adj_points(int xsize, int ysize, int gsize, point *pts);
	void add_center(float x, float y, float z, char state);
	void add_center_circle(Mat &img);

};

#endif
