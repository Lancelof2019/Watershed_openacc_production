#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
#include <cmath> 
#include <stdlib.h>


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

Mat WatershedAlg::thresholdMeasure(Mat image) {



 
    
        // cv::threshold(image,image, ,255,CV_THRESH_BINARY);
       //double catchvalue=cv::threshold(image, image,0,255,CV_THRESH_OTSU|CV_THRESH_BINARY);

       //cout<<"The catchvalue is :"<<catchvalue<<endl;

        cv::adaptiveThreshold(image,image,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,  19,9);


        //if pixel <254 ,then 0 is given 
       
     // double t0=0.0;
     // double sum=0.0;

     /*
      for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {
            sum=sum+(int)image.at<uchar>(i,j);
            }
      }
     t0=sum/(image.rows*image.cols);

     cout<<"t0 is : "<<t0<<endl;


     */

     


      // string filename9="/opt/test9.txt";
      // ofstream fout9(filename9); 


       /* for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {

             fout9<<((int)image.at<uchar>(i,j))<<",";
             

         }
          fout9<<endl;
     }
     fout9.close();
*/
//
/*
        for(int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                if (((int) image.at<cv::Vec3b>(i, j)[0]) != ZERO && (int) image.at<cv::Vec3b>(i, j)[0] != ONE) {
                    int val = image.at<cv::Vec3b>(i, j)[0];
                    if(abs(val - ZERO) <= abs(val - ONE) ) {
                        image.at<cv::Vec3b>(i, j)[0] = ZERO;
                        image.at<cv::Vec3b>(i, j)[1] = ZERO;
                        image.at<cv::Vec3b>(i, j)[2] = ZERO;
                    } else {
                        image.at<cv::Vec3b>(i, j)[0] = ONE;
                        image.at<cv::Vec3b>(i, j)[1] = ONE;
                        image.at<cv::Vec3b>(i, j)[2] = ONE;
                    }
                }
            }
        }
*/
//


  //  vector<vector<Point>> contours;  
  //  vector<cv::Vec4i> hierarchy;  
   // cv::findContours(image,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point());  
   // Mat imageContours=Mat::zeros(image.size(),CV_8UC1);  
  //  Mat Contours=Mat::zeros(image.size(),CV_8UC1);  //
  //  cout<<"The size of contour is :"<<contours.size()<<endl;
 //   for(int i=0;i<contours.size();i++)  
  //  {  
 //       / 
  //      for(int j=0;j<contours[i].size();j++)   
  //      {  
    //        //绘制出contours向量内所有的像素点  
     //       Point P=Point(contours[i][j].x,contours[i][j].y);  
  //          Contours.at<uchar>(P)=255;  
    //        image.at<uchar>(P)=0;
     //       //threshTestImg.at<uchar>(P)={0,0,255};
    //    }  
  
   
    //    drawContours(imageContours,contours,i,Scalar(255),1,8,hierarchy);  
   // }  
  //  imshow("Contours Image",imageContours); //轮廓  
  //  waitKey(0);  
   // imshow("Point of Contours",Contours);   //向量contours内保存的所有轮廓点集  
  //  waitKey(0);
    //imshow("with Contour",threshTestImg);
    //waitKey(0);



        //thresholdMeasure(image);

        return image;
    }
