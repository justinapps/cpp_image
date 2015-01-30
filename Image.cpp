#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]){

	//the first three lines of each ppm file
	string ppmFormat;
	string size;
	string numOfColours;

	//vectors for RGB values of each pixel of every image
	vector<int> red_vector;
	vector<int> green_vector;
	vector<int> blue_vector;

	//strings and ints for r, g, b
	string red_string, blue_string, green_string; //to store string values
	int Red, Green, Blue; //to store converted values (initially in string form)
	int red_median, green_median, blue_median; //to store median values for each pixel

	//height & width of images = number of pixels in image
	int height;
	int width;
        ifstream ppm;
	//getting each file
        ppm.open(argv[1]);
        cout<<argc<<endl;
        ifstream myFiles[argc-1];
        int j=1;
        int i=0;
        string skipLine = "";

        while(i<argc-1){
            cout<<argv[j]<< "     ";
            myFiles[i].open(argv[j]);
            getline( myFiles[i],skipLine);
            getline( myFiles[i],skipLine);
            getline( myFiles[i],skipLine);

	        cout<<i<<" ";
	        cout<<myFiles[i]<<endl;

	        i++;
	        j++;
        }

	//get first 3 lines for new_img
	ppm >> ppmFormat; //p3
	ppm >> height >> width;
	ppm >> numOfColours; //255
	ofstream outfile("new_img.ppm"); //create new_img file of ppm format
	outfile << ppmFormat << "\n" << height << " " << width << "\n" << numOfColours << endl; //write the lines to new_img.ppm

	int counter = 0;
	while(counter < height * width){ //loops through each pixel
			
        	for(int i=0; i<argc-1; i++){
	
			myFiles[i]>> red_string >> green_string >> blue_string;
			istringstream n1 (red_string);
			n1 >> Red;
			red_vector.push_back(Red);
	
			istringstream n2 (green_string);
			n2 >> Green;
			green_vector.push_back(Green);
	
			istringstream n3 (blue_string);
			n3 >> Blue;
			blue_vector.push_back(Blue);

            }

		sort(red_vector.begin(), red_vector.end());
		sort(green_vector.begin(), green_vector.end());
		sort(blue_vector.begin(), blue_vector.end());

		outfile << red_vector[argc/2] << " " << green_vector[argc/2] << " " << blue_vector[argc/2] << endl; //write to new_img file

		red_vector.clear(); //clear vectors
		green_vector.clear();
		blue_vector.clear();

		counter++; //incrementor to go to new pixel
	}

	cout << "Finished image cleanup!" << endl;
}//end of main
