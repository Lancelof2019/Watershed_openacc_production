#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
#define TESTTHR  1
using namespace cv;
void WatershedAlg::processImage(Mat image,Mat duplImage)  {
        // Make image grayscale




       //lapseedFunc(image);



       image = makeImageGrayScale(image);
       //Mat tempImage;

      // cv::imshow("Gray image",image);
      // cv::waitKey(0);
      // duplImage.copyTo(tempImage);

      // Mat threshTestImg;

     // duplImage.copyTo(threshTestImg);


        //cv::imshow("makeImageGrayScale",image);
       // cv::waitKey(0);

        // Erode foreground
        vector< vector<int> > erosionTargetThree{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, };
        image = erosion(image, erosionTargetThree);
       // cv::imshow("erosion",image);
      //  cv::waitKey(0);
         // Apply threshold
        
        for(int i=0;i<TESTTHR;i++){
        image = thresholdMeasure(image);
        }

      //  cv::imshow("thresholdMeasure",image);
       // cv::waitKey(0);
       
     
        // Inverse pixels
    
       // image = inverseImage(image);
        //cv::imshow("inverseImage",image);
       // cv::waitKey(0);

       image=antiInverseImage(image);
     //  cv::imshow("antiInverseImage",image);
      // cv::waitKey(0);
       
    
        // Apply distance transform
        vector<Point> markers;
        image = distanceTransform(image,markers);
       // cv::imshow("distancetrans-image",image);
      //  cv::waitKey(0);
        //image=testDistanceTransform(image, markers);
        Mat distanceImage = image;
       // cv::imshow("distance transformation",distanceImage);
       // cv::waitKey(0);
        //cout << "Detected " << markers.size() << " markers \n";
         
        // Watershed
	  // #pragma acc enter data copyin()
	   auto *diststart=distanceImage.data;
	   int distrows=distanceImage.rows;
	   int distcols=distanceImage.cols;
	  
       if(markers.size() == 0) {
		 //   #pragma acc enter data copyin(diststart[:distrows*distcols])
            for(int i = 0; i < distrows; i++) {
                for(int j = 0; j < distcols; j++) {
                    if((int) diststart[i*distrows+j] != 0) {
                        markers.push_back(Point(i, j));//
                        image.at<uchar>(i, j) = 25;
                        cv::imshow("watershed result",image);
                        cv::waitKey(0);
                        //return watershed(image, markers);
                    }
                }
            }
        }


        image = watershed(image, markers,duplImage);
        cv::imshow("watershed result",image);
        cv::waitKey(0);

    }