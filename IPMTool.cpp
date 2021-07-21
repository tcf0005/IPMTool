#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>

#include <stdio.h>
#include <stdarg.h>



using namespace std;
using namespace cv;
#define PI 3.1415926


int frameWidth = 640;
int frameHeight = 480;



#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;




int main(int argc, char const *argv[]) {

    
    int state=1;


    // Bring in image from file, must be in folder, and displaying the original
        Mat source = imread("markers2.png");
        Mat src=source.clone();
        imshow("Original", source);
  
    // mat container to receive images
        Mat destination;

    //Introducing the Variables which are in the slider box
        int alpha_ =301, beta_ = 90, gamma_ = 90;
        int f_ =331, dist_ = 374;
        namedWindow("Result", 1);

    // //Slider Box Code
        createTrackbar("Alpha", "Result", &alpha_, 360);
        createTrackbar("Beta", "Result", &beta_, 180);
        createTrackbar("Gamma", "Result", &gamma_, 180);
        createTrackbar("f", "Result", &f_, 10000);
        createTrackbar("Distance", "Result", &dist_, 5000);
    //Slider Box for REGION of INTREST for Intensity:
       




    while( true ) {
    //Defining the region of interest:
        Mat dst, cdst;
        cv::Mat og = src.clone();
        
 
  //Revealing the images
        //imshow("Region of intrest", og);
      
        
        //Converting Parameters to Degrees
            double focalLength, dist, alpha, beta, gamma; 
        
            alpha = alpha_ * PI/180;
            beta =((double)beta_ -90) * PI/180;
            gamma =((double)gamma_ -90) * PI/180;
            focalLength = (double)f_;
            dist = (double)dist_;


        //Resizing
            Size image_size = source.size();
            double w = (double)image_size.width, h = (double)image_size.height;


        // Projecion matrix 2D -> 3D
            Mat A1 = (Mat_<float>(4, 3)<< 
                1, 0, -w/2,
                0, 1, -h/2,
                0, 0, 0,
                0, 0, 1 );


        // Rotation matrices Rx, Ry, Rz

            Mat RX = (Mat_<float>(4, 4) << 
                1, 0, 0, 0,
                0, cos(alpha), -sin(alpha), 0,
                0, sin(alpha), -cos(alpha), 0,
                0, 0, 0, 1 );

            Mat RY = (Mat_<float>(4, 4) << 
                cos(beta), 0, -sin(beta), 0,
                0, 1, 0, 0,
                sin(beta), 0, cos(beta), 0,
                0, 0, 0, 1  );

            Mat RZ = (Mat_<float>(4, 4) << 
                cos(gamma), -sin(gamma), 0, 0,
                sin(gamma), cos(gamma), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1  );


        // R - rotation matrix
            Mat R = RX * RY * RZ;

        // T - translation matrix
            Mat T = (Mat_<float>(4, 4) << 
                1, 0, 0, 0,  
                0, 1, 0, 0,  
                0, 0, 1, dist,  
                0, 0, 0, 1); 

        // K - intrinsic matrix 
            Mat K = (Mat_<float>(3, 4) << 
                focalLength, 0, w/2, 0,
                0, focalLength, h/2, 0,
                0, 0, 1, 0
                ); 


        Mat transformationMat = K * (T * (R * A1));

        warpPerspective(source, destination, transformationMat, image_size, INTER_CUBIC | WARP_INVERSE_MAP);

        imshow("output",destination);
        waitKey(25);
    }


    return 0;
}   
