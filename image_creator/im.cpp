#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <omp.h>

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
int thread_count;
string particle_location;
string initial_pfile;
string final_pfile;
string output_image;
string directory;
string ssds_directory;

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
bool removeFromDirectory(string in);
bool not_particleFile(string in);

//  In command line.  a.out config.file param.file directory
int main(int argc, char *argv[]){


	ifstream configfile(argv[1]);
	readConfig(configfile);
	configfile.close();

	ifstream paramfile(argv[2]);
	readParam(paramfile);
	paramfile.close();

    ssds_directory = argv[3];
    cout << "ssds directory: " << ssds_directory.c_str() <<endl;


    vector<string> files;
    DIR* dirp = opendir(ssds_directory.c_str());
    struct dirent * dp;
    while (( dp = readdir(dirp)) != NULL)
    {
        files.push_back(dp->d_name);
        //cout << files.back()<<endl;
    }

    //  filters out non run directories
    files.erase(remove_if(files.begin(),files.end(),removeFromDirectory),files.end());

    cout<< "files in main directory\n";
    for (int i=0;i<files.size();i++)
        cout<< files[i]<<endl;

    // creating Parallel processing threads
    cout<< "thread count: " << thread_count <<endl;
    #pragma omp parallel num_threads(thread_count)
    {
        int mynum = omp_get_thread_num();
        //printf("I am in thread: %d\n",mynum);
        //cout<< "I am in thread: "<< mynum <<endl;

        // for loop is shared between all threads
        #pragma omp for
        for(int i=0; i<files.size();i++){

            string myDir = ssds_directory + files[i] + '/';
            printf("T: %d  dir: %s\n",mynum,myDir.c_str());

            //  Look at particle title and sort accordingly
            vector<string> mydir;
            DIR* mydirp = opendir(myDir.c_str());
            struct dirent * mydp;
            while (( mydp = readdir(mydirp)) != NULL)
            {
                string temp = mydp->d_name;
                printf("-step: %d -file name: %s",i,temp.c_str());
                //files.push_back(mydp->d_name);
                //cout << files.back()<<endl;
            }

    //  filters out non run directories


            Mat img(image_rows,image_cols,CV_32F);
	        Mat dest(image_rows,image_cols,CV_32F);


        }
    }

    return 0;


    Mat img(image_rows,image_cols,CV_32F);
    Mat dest(image_rows,image_cols,CV_32F);



	//  Read initial particle file.
	ifstream ipartfile(initial_pfile.c_str());
	Galaxy g1(particle_number_1, ipartfile);
	Galaxy g2(particle_number_2, ipartfile);
	ipartfile.close();

	g1.calc_radius();
	g2.calc_radius();

    //  Read final particle file.
	ifstream fpartfile(final_pfile.c_str());
	g1.read(fpartfile);
    g2.read(fpartfile);


    //  Read center of 2nd galaxy
    point g1c, g2c;
    g1c.x = g1c.y = g1c.z = 0;
    fpartfile >> g2c.x >> g2c.y >> g2c.z;
    g1.add_center(g1c);
    g2.add_center(g2c);

	fpartfile.close();

    //  Adjust point so they fit in an image
	compare(g1,g2);
    g1.adj_points(img.cols,img.rows,gaussian_size, g1.fpart);
    g2.adj_points(img.cols,img.rows,gaussian_size, g2.fpart);

    //  Write points to image
	g1.write(img,gaussian_size,gaussian_weight,6, g1.fpart);
	g2.write(img,gaussian_size,gaussian_weight,6, g2.fpart);

    normalize_image(img,dest,g2.maxb,4);


    //  Troubleshooting location for center of galaxy
    //g1.add_center_circle(dest);
    //g2.add_center_circle(dest);

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
        else if( str.compare("thread_count")==0)
            fin >> thread_count;
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


// Accompaning function for clearnDirectory
bool removeFromDirectory(string in ){
    return in.compare(0,3,"run")!=0;
}

bool is_particleFile(string in )
{
    return true;

}
