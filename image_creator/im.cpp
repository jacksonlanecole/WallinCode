#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>

//#include "opencv2/utility.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include "Galaxy_Class.hpp"

using namespace cv;
using namespace std;


//  Global Variables
int particle_number_1;
int particle_number_2;
string particle_location;
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


//  Function Prototypes
void readConfig(ifstream& fin);
void readParam(ifstream& fin);
void compare(Galaxy &g1, Galaxy &g2);
void normalize_image(const Mat &img,Mat &dest, float max, float in);

int main(int argc, char *argv[]){

    

    int mrow = 300;
    int mcol = 300;
    int gsize = 15;
	float weight=2.5;
	Mat img(mrow,mcol,CV_32F);
	Mat dest(mrow,mcol,CV_32F);

    point g1c, g2c;

	ifstream configfile(argv[1]);
	readConfig(configfile);
	configfile.close();

	ifstream paramfile(argv[2]);
	readParam(paramfile);
	paramfile.close();


    vector<string> files;
    DIR* dirp = opendir(particle_location.c_str());
    struct dirent * dp;
    while (( dp = readdir(dirp)) != NULL)
    {
        files.push_back(dp->d_name);
        cout << files.back()<<endl;
    }

	//  Read initial particle file.
	ifstream ipartfile(initial_pfile.c_str());

	//galaxy g1(particle_number_1, ipartfile);
	//galaxy g2(particle_number_2, ipartfile);

	Galaxy g1(particle_number_1, ipartfile);
	Galaxy g2(particle_number_2, ipartfile);

	ipartfile.close();

	g1.calc_radius();
	g2.calc_radius();

    //delete g1.ipart;
    //delete g2.ipart;


	ifstream fpartfile(final_pfile.c_str());
	g1.read(fpartfile);
    g1c.x = g1c.y = g1c.z = 0;

	g2.read(fpartfile);
    fpartfile >> g2c.x >> g2c.y >> g2c.z;
	fpartfile.close();

    g1.add_center(g1c);
    g2.add_center(g2c);

	compare(g1,g2);


    g1.adj_points(img.cols,img.rows,gsize);
    g2.adj_points(img.cols,img.rows,gsize);

	g1.write(img,gsize,weight,6);
	g2.write(img,gsize,weight,6);



    normalize_image(img,dest,g2.maxb,4);


    g1.add_center_circle(dest);
    g2.add_center_circle(dest);

    dest.convertTo(dest,CV_8UC3,255.0);
    imwrite(output_image,dest);

    return 0;


}

void readConfig(ifstream& fin)
{
    string str;

    while( fin >> str ){
        //cout << str << endl;
        if (str.compare("particle_location")==0)
            fin >> particle_location;
        else if( str.compare("initial_pfile")==0)
            fin >> initial_pfile;
        else if ( str.compare("final_pfile")==0)
            fin >> final_pfile;
        else if ( str.compare("output_image")==0)
            fin >> output_image;
        else if ( str.compare("particle_number_1")==0)
            fin >> particle_number_1;
        else if ( str.compare("particle_number_2")==0)
            fin >> particle_number_2;
        else
            cout << str << " : " << (fin >> str) << " Not found\n";
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


void compare(Galaxy &g1, Galaxy &g2){

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

