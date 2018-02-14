#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

//#include "opencv2/utility.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"


using namespace cv;
using namespace std;


//  Global Variables
int particle_number_1;
int particle_number_2;
string initial_pfile;
string final_pfile;
string output_image;

//  Default values
int gaussian_size = 15;
float gaussian_weight = 2.5;
float gaussian_factor = 6;
int norm_value = 4;
int image_rows = 300;
int image_cols = 300;

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
				cout<< "Check if number is real: " << ipart[i].vz << endl;
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
                cout<< "Check if number is real: "<<ipart[i].vz <<endl;
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
//#include <sstream>

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

	void write(Mat &img, int gsize, float weight, int pin){

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

    }
};

//  Function Prototypes
void readConfig(ifstream& fin);
void readParam(ifstream& fin);
void compare(galaxy &g1, galaxy &g2);
void normalize_image(const Mat &img,Mat &dest, float max, float in);

int main(int argc, char *argv[]){

    int mrow = 300;
    int mcol = 300;
    int gsize = 15;
	float weight=2.5;
	Mat img(mrow,mcol,CV_32F);
	Mat dest(mrow,mcol,CV_32F);

	ifstream configfile(argv[1]);
	readConfig(configfile);
	configfile.close();

	ifstream paramfile(argv[2]);
	readParam(paramfile);
	paramfile.close();


	ifstream ipartfile(initial_pfile.c_str());
	galaxy g1(particle_number_1, ipartfile);
	galaxy g2(particle_number_2, ipartfile);
	ipartfile.close();

	g1.calc_radius();
	g2.calc_radius();
    //delete g1.ipart;
    //delete g2.ipart;


	ifstream fpartfile(final_pfile.c_str());
	g1.read(fpartfile);
	g2.read(fpartfile);
	fpartfile.close();

	compare(g1,g2);

    /*
	cout << mrow << mcol << endl;
	cout << g1.xmax << "  " << g1.xmin << "  " << g1.ymax << "  "<< g1.ymin << endl;
	cout << g2.xmax << " " << g2.xmin << "  " << g2.ymax << "  " << g2.ymin << endl;

    */


    g1.adj_points(img.cols,img.rows,gsize);
    g2.adj_points(img.cols,img.rows,gsize);

	g1.write(img,gsize,weight,6);
	g2.write(img,gsize,weight,6);

    //g1.add_center_circle(img);
    //g2.add_center_circle(img);

    normalize_image(img,dest,g2.maxb,4);

    dest.convertTo(dest,CV_8UC3,255.0);
    imwrite(output_image,dest);

    return 0;
}

void readConfig(ifstream& fin)
{
    string str;

    while( fin >> str ){
        //cout << str << endl;
        if( str.compare("initial_pfile")==0)
            fin >> initial_pfile;
        else if ( str.compare("final_pfile")==0)
            fin >> final_pfile;
        else if ( str.compare("output_image")==0)
            fin >> output_image;
        else if ( str.compare("particle_number_1")==0)
            fin >> particle_number_1;
        else if ( str.compare("particle_number_2")==0)
            fin >> particle_number_2;
    }
}

void readParam(ifstream& fin)
{
    string str;

    while( fin >> str ){
        //cout << str << endl;
        if( str.compare("gaussian_size")==0)
            fin >> gaussian_size;
        else if ( str.compare("gaussian_weight")==0)
            fin >> gaussian_weight;
        else if ( str.compare("gaussian_factor")==0)
            fin >> gaussian_factor;
        else if ( str.compare("norm_value")==0)
            fin >> norm_value;
        else if ( str.compare("image_rows")==0)
            fin >> image_rows;
        else if ( str.compare("image_cols")==0)
            fin >> image_cols;
    }
}


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


void normalize_image(const Mat &img,Mat &dest, float max, float in){
	float vv, vscaled;
	for (int k=0;k<dest.rows;k++){
		for (int l=0;l<dest.cols;l++){
			vv =img.at<float>(k,l)	;
			vscaled = pow(vv/max,1/in);
			dest.at<float>(k,l) = vscaled;
		}
	}
}

