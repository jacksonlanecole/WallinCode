#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

//#include "opencv2/utility.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"


using namespace cv;
using namespace std;


struct point{
	float r,x,y,z,vx,vy,vz;

	void calc_radius(float cx,float cy,float cz){
		r = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz));
	}

};


struct galaxy{

	float x,y,z, maxr, xmin, xmax, ymin, ymax,maxb;
	int npart;
	point *ipart, *fpart;


	galaxy(int part, ifstream& initpart){
		npart = part;
		maxr =maxb= x = y = z =0;
		ipart=(point *) malloc(npart*sizeof(point));
		fpart=(point *) malloc(npart*sizeof(point));
		for (int i=0;i<npart;i++){
			initpart>>ipart[i].x>>ipart[i].y>>ipart[i].z>>ipart[i].vx>>ipart[i].vy>>ipart[i].vz;
			if ( i == npart-1){
				cout<< "Check this number is real: " << ipart[i].vz << endl;
            }
		}
	}

	void read(ifstream& infile){
		for (int i=0;i<npart;i++){
			infile>>fpart[i].x>>fpart[i].y>>fpart[i].z>>fpart[i].vx>>fpart[i].vy>>fpart[i].vz;
			if ( i == npart-1){
                x=fpart[i].x;
                y=fpart[i].y;
                z=fpart[i].z;
            }
			if(xmin > fpart[i].x)
				xmin = fpart[i].x;
			if(xmax < fpart[i].x)
				xmax = fpart[i].x;
			if(ymin > fpart[i].y)
				ymin = fpart[i].y;
			if(ymax < fpart[i].y)
				ymax = fpart[i].y;
		}
	}

	void calc_radius(){

        // Calculate center of galaxies originally by averaging points
		for (int i=0;i<npart;i++){
			x += ipart[i].x;
			y += ipart[i].y;
			z += ipart[i].z;
		}
		x /= npart;
		y /= npart;
		z /= npart;

        //  calculate initial distance from center for each point
		for (int i=0;i<npart;i++){
			ipart[i].calc_radius(x,y,z);
			if (ipart[i].r > maxr)
				maxr = ipart[i].r;
		}
	}

    void adj_points(int xsize, int ysize, int gsize){

        int scale_factor;

        xmax-=xmin;
        ymax-=ymin;

        if(1.0*(xsize-gsize)/xmax>1.0*(ysize-gsize)/ymax)
            scale_factor = 1.0*(ysize-gsize)/ymax;
        else
            scale_factor = 1.0*(xsize-gsize)/xmax;

        for (int i=0; i<npart; i++)
        {
            fpart[i].x= (fpart[i].x-xmin)*scale_factor + gsize/2.0;
            fpart[i].y= ysize-((fpart[i].y-ymin)*scale_factor + gsize/2.0);
        }
        x = fpart[0].x;
        y = fpart[0].y;

    }

	void write(Mat &img, int mrow, int mcol, int gsize, float weight, int pin){

		maxb=0;

		for (int i=0;i<npart;i++){
			int row = int(fpart[i].y);
			int col = int(fpart[i].x);
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

    void add_center_circle(Mat &img){

            circle( img,Point2f(int(x),int(y)),10,Scalar(255,255,255),2,8);
/*
	rc[1] = Point2f(178,250);
		//~ circle( real,rc[i],10, Scalar( 255, 255, 255 ), thickness, lineType );

*/

    }
};

void compare(galaxy &g1, galaxy &g2){

	if (g1.xmin > g2.xmin)
		g1.xmin = g2.xmin;
	else
		g2.xmin = g1.xmin;

	if (g1.xmax < g2.xmax)
		g1.xmax = g2.xmax;
	else
		g2.xmax = g1.xmax;

	if (g1.ymin > g2.ymin)
		g1.ymin = g2.ymin;
	else
		g2.ymin = g1.ymin;

	if (g1.ymax < g2.ymax)
		g1.ymax = g2.ymax;
	else
		g2.ymax = g1.ymax;

	if (g1.maxb>g2.maxb)
		g2.maxb=g1.maxb;
	else
		g1.maxb=g2.maxb;
}


void normalize_image(const Mat &img,Mat &dest, int mrow, int mcol, float max, float in){
	float vv, vscaled;
	for (int k=0;k<mrow;k++){
		for (int l=0;l<mcol;l++){
			vv =img.at<float>(k,l)	;
			vscaled = pow(vv/max,1/in);
			dest.at<float>(k,l) = vscaled;
		}
	}
}



int main(int argc, char *argv[]){

	ifstream ipartfile(argv[1]);
	ifstream fpartfile(argv[2]);
	ifstream infofile(argv[3]);

    int mrow = 300;
	int mcol = 300;
	int npart1, npart2;

	int gsize = 15;
	float weight=2.5;

	Mat img(mrow,mcol,CV_32F);
	Mat dest(mrow,mcol,CV_32F);


    int tr_index = 0;   // Simple variable to help me troubleshoot where the program goes wrong

    infofile >> npart1 >> npart2;

	galaxy g1(npart1, ipartfile);
	galaxy g2(npart2, ipartfile);

	g1.calc_radius();
	g2.calc_radius();

	g1.read(fpartfile);
	g2.read(fpartfile);

	compare(g1,g2);

    g1.adj_points(img.cols,img.rows,gsize);
    g2.adj_points(img.cols,img.rows,gsize);

	g1.write(img,mrow,mcol,gsize,weight,6);
	g2.write(img,mrow,mcol,gsize,weight,6);

    g1.add_center_circle(img);
    g2.add_center_circle(img);

	normalize_image(img,dest,mrow,mcol,g2.maxb,4);

    dest.convertTo(dest,CV_8UC3,255.0);
	imwrite("sim_img.png",dest);

    return 0;
}

/*
	rc[1] = Point2f(178,250);
		//~ circle( real,rc[i],10, Scalar( 255, 255, 255 ), thickness, lineType );
	

*/
