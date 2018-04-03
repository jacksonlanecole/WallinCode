#include "imgCreator.hpp"

using namespace cv;
using namespace std;

//  Function Prototypes
void getDir(vector<string> &myVec, string dirPath);   
bool removeFromDirectory(string in);

//  In command line.
//  ./image_creator.exe    sdss_directory    param_file
int main(int argc, char *argv[]){

	bool overWriteImages = true;
	bool printStdWarnings = true;
	string sdss_directory;


    cout << endl;
    //  Get main Directory
    string mainPath = argv[1];

    // Open parameter file and save name
    string tempParam = argv[2];
	ifstream paramfile(tempParam.c_str());
    if (paramfile.fail())
        printf("Parameter file not found.  Using default param0001\n");

	paramStruct param;
	param.loadParam(paramfile);
	paramfile.close();
	
	if (false){
		cout << "Param Name is " << param.name << endl;
		cout << param.gaussian_weight<<endl;
		cout << param.image_cols<<endl;
	}

    //  Add '/' to directory string if not already present
    string temp = mainPath.substr(mainPath.size()-1,1);
    if (temp != "/")
        mainPath = mainPath + '/';

	
    vector<string> runNames;
    getDir(runNames,mainPath);
    runNames.erase(remove_if(runNames.begin(),runNames.end(),removeFromDirectory),runNames.end());
	sort(runNames.begin(), runNames.end()); 
	
    if (runNames.size()==0){
        printf("No run directories found in %s\nExiting...\n",mainPath.c_str());
		return 0;
    }


    //  Parallization implementation
    int numThreads = omp_get_num_threads();
    numThreads /= 2;
    #pragma omp parallel num_threads(numThreads)    
	{
		#pragma omp for
		for (int unsigned iRun=0; iRun < 10 /*runNames.size()*/; iRun++)
		{
			string tempStr = mainPath + runNames[iRun]+'/';
			ImgCreator myCreator( tempStr, overWriteImages, printStdWarnings, param, 1);			
			if(myCreator.prepare()){
				myCreator.makeImage();
				myCreator.delMem();
			}	
		}
    }

    cout<<endl;
    return 0;

}

void getDir(vector<string> &myVec, string dirPath){
     // Search Directory for files
    DIR* dirp = opendir(dirPath.c_str());
    struct dirent * dp;
    while (( dp = readdir(dirp)) != NULL)
        myVec.push_back(dp->d_name);
}

// Accompaning function for clearnDirectory
bool removeFromDirectory(string in ){
    return in.compare(0,3,"run")!=0;
}



