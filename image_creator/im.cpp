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
bool notParticleFile(string in);

//  In command line.  a.out config.file param.file directory
int main(int argc, char *argv[]){

    //  Read config and parameter file
	ifstream configfile(argv[1]);
	readConfig(configfile);
	configfile.close();

	ifstream paramfile(argv[2]);
	readParam(paramfile);
	paramfile.close();

    ssds_directory = argv[3];
    cout << "ssds directory: " << ssds_directory.c_str() <<endl;


    vector<string> mainDir;
    DIR* dirp = opendir(ssds_directory.c_str());
    struct dirent * dp;
    while (( dp = readdir(dirp)) != NULL)
        mainDir.push_back(dp->d_name);

    //  filters out non run directories
    mainDir.erase(remove_if(mainDir.begin(),mainDir.end(),removeFromDirectory),mainDir.end());

    cout<< "files in main directory\n";
    for (int i=0;i<mainDir.size();i++)
        cout<< mainDir[i]<<endl;

    // creating Parallel processing threads
    cout<< "thread count: " << thread_count <<endl;
    #pragma omp parallel num_threads(thread_count)
    {
        int mynum = omp_get_thread_num();

        // for loop is shared between all threads
        #pragma omp for
        for(int i1=0; i1<mainDir.size();i1++){

            //  Variables
            string myDir = ssds_directory + mainDir[i1] + '/';

            Galaxy g1,g2;

            Mat img(image_rows,image_cols,CV_32F);
	        Mat dest(image_rows,image_cols,CV_32F);
            string fpartFileName, ipartFileName, sdssName, tempStr;
            int npart1, npart2;
            double x,y,z;

            stringstream strm1, strm2;


            //printf("T: %d  dir: %s\n",mynum,myDir.c_str());

            //  Get files in run directory
            vector<string> runFiles;
            DIR* mydirp = opendir(myDir.c_str());
            struct dirent * mydp;
            while (( mydp = readdir(mydirp)) != NULL)
                runFiles.push_back(mydp->d_name);


            // find particle files
            for (int i; i<runFiles.size();i++)
            {
                size_t foundi = runFiles[i].find(".i.");
                size_t foundf = runFiles[i].find(".f.");
                if (foundi != string::npos)
                    ipartFileName = runFiles[i];
                else if ( foundf != string::npos)
                    fpartFileName = runFiles[i];
            }

            //  Parse data from particle file name

            size_t pos[4];
            pos[0] = ipartFileName.find(".");
            pos[1] = ipartFileName.find(".",pos[0]+1);
            pos[2] = ipartFileName.find(".",pos[1]+1);
            pos[3] = ipartFileName.find(".",pos[2]+1);

            sdssName = ipartFileName.substr(0,pos[0]);

            tempStr = ipartFileName.substr(pos[1]+1,pos[2]-pos[1]-1);
            strm1 << tempStr;
            strm1 >> npart1;
            //printf("String 1: %s  int: %d\n", tempStr.c_str(), npart1);

            tempStr = ipartFileName.substr(pos[2]+1,pos[3]-pos[2]-1);
            strm2 << tempStr;
            strm2 >> npart2;
            //printf("String 2: %s  int: %d\n", tempStr.c_str(), npart2);

            //  Read particle files
            ipartFileName = myDir + ipartFileName;
            fpartFileName = myDir + fpartFileName;

            ifstream ipartstream(ipartFileName.c_str());
            g1.read(ipartstream,npart1,'i');
            g2.read(ipartstream,npart2,'i');
            ipartstream >> x >> y >> z;  // Grabbing final center of g2
            g2.add_center(x,y,z,'i');
            //printf("run: %d  x:%f  y:%f  z:%f  \n",i1,x,y,z);
            ipartstream.close();

            ifstream fpartstream(fpartFileName.c_str());
            g1.read(fpartstream,npart1,'f');
            g2.read(fpartstream,npart2,'f');
            fpartstream >> x >> y >> z;
            g2.add_center(x,y,z,'f');
            fpartstream.close();

            g1.calc_values();
            g2.calc_values();
            compare(g1,g2);

            printf("TS: 7 \n");


            //  Adjust point values to fit on image
            g1.adj_points(img.cols,img.rows,gaussian_size, g1.fpart);
            g2.adj_points(img.cols,img.rows,gaussian_size, g2.fpart);

            //  Write points to image
	        g1.write(img,gaussian_size,gaussian_weight,6, g1.fpart);
	        g2.write(img,gaussian_size,gaussian_weight,6, g2.fpart);

            normalize_image(img,dest,g2.maxb,4);


            //  Troubleshooting location for center of galaxy
            //g1.add_center_circle(dest);
            //g2.add_center_circle(dest);

            string picName = myDir + "pic.png";

            dest.convertTo(dest,CV_8UC3,255.0);
            imwrite(picName,dest);




        }
    }

    return 0;

    /*



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

    */


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

bool notParticleFile(string in )
{
    //  Search for flags in name signifying it's a particle file
    size_t foundi = in.find(".i.");
    size_t foundf = in.find(".f.");

    if ( (foundi == string::npos) && (foundf == string::npos)) // string not found
        return true;
    else
        return false;

}
