#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include "Galaxy_Class.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

using namespace std;
using namespace cv;


Galaxy::Galaxy(){
	maxr=maxb=bx=by=bz=fx=fy=fz=0;
    xmin = ymin = -2.5;  // fixed max and min
    xmax = ymax = 2.5;
}

void Galaxy::read(ifstream& infile, int part, char state){
    npart = part;
    if ( state == 'i' )
    {
        ipart = (point *) malloc(npart*sizeof(point));

       for (int i=0;i<npart;i++)
       {
        infile>>ipart[i].x>>ipart[i].y>>ipart[i].z>>ipart[i].vx>>ipart[i].vy>>ipart[i].vz;
       }
    }
    else if ( state == 'f' )
    {
	    fpart = (point *) malloc(npart*sizeof(point));
    	for (int i=0;i<npart;i++){
		    infile>>fpart[i].x>>fpart[i].y>>fpart[i].z>>fpart[i].vx>>fpart[i].vy>>fpart[i].vz;
        }
    }
    else
        printf("Galaxy read particle state unidetnified\n");
}



void Galaxy::write(Mat &img, int gsize, float weight, int pin, point *pts){

	maxb=0;
	for (int i=0;i<npart;i++){
		int row = int(pts[i].y);
		int col = int(pts[i].x);
		for (int k=0;k<gsize;k++){
			for (int l=0;l<gsize;l++){
				float pbright = exp( - pin* ipart[i].r / maxr);
				float val = pbright*1.0/(2*3.14*weight*weight)*exp( -1.0*((k-1.0*gsize/2)*(k-1.0*gsize/2) +  (l-1.0*gsize/2)*(l-1.0*gsize/2))/(2*weight*weight));

				img.at<float>(row +k-gsize/2, col+l-gsize/2)+=val;
				if (maxb < img.at<float>(row+k-gsize/2,col+l-gsize/2))
					maxb = img.at<float>(row+k-gsize/2,col+l-gsize/2);
			}
		}
	}
}



void Galaxy::simple_write(Mat &img, point *pts){

	for (int i=0;i<npart;i++){
		img.at<float>(pts[i].y, pts[i].x)+=1;
	}
}


void Galaxy::calc_radius(){

    //  centers now obtained, calculation no longer needed.
         // Calculate center of galaxies originally by averaging points
	/*
    for (int i=0;i<npart;i++){
		x += ipart[i].x;
		y += ipart[i].y;
		z += ipart[i].z;
	}
	x /= npart;
	y /= npart;
	z /= npart;

    */



        //  calculate initial distance from center for each point
	for (int i=0;i<npart;i++){
		ipart[i].calc_radius(bx,by,bz);
		if (ipart[i].r > maxr)
			maxr = ipart[i].r;
	}
}


void Galaxy::adj_points(int xsize, int ysize, int gsize, point *pts){

        int scale_factor;

        xmax-=xmin;
        ymax-=ymin;

        if( (1.0*(xsize-gsize)/xmax) > (1.0*(ysize-gsize)/ymax))
            scale_factor = 1.0*(ysize-gsize)/ymax;
        else
            scale_factor = 1.0*(xsize-gsize)/xmax;

        fx = (fx-xmin)*scale_factor + gsize/2.0;
        fy = ysize - ( ( fy-ymin)*scale_factor + gsize/2.0);

        for (int i=0; i<npart; i++)
        {
            pts[i].x= (pts[i].x-xmin)*scale_factor + gsize/2.0;
            pts[i].y= ysize-((pts[i].y-ymin)*scale_factor + gsize/2.0);
        }

}



void Galaxy::add_center(float x, float y, float z, char state){
    //  State is beginning or final state of galaxy;
    if (state == 'b'){
        bx = x;
        by = y;
        bz = z;
    }
    else if (state == 'f'){
        fx = x;
        fy = y;
        fz = z;
    }
    else
        printf("Add_center: state not recognized");
}

void Galaxy::add_center_circle(Mat &img){

            circle( img,Point2f(int(fx),int(fy)),10,Scalar(255,255,255),2,8);

}
