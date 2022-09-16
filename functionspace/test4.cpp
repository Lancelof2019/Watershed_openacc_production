#include <opencv2/opencv.hpp>
#include<queue>
#include <vector>
#include<random>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include<openacc.h>

using namespace std;
using namespace cv;


int main(){

     cv::Mat srcImg=cv::imread("/home/rzlin/vo79tedi/testSpace/images/blue-mountains.jpg");



      Mat grayScale(srcImg.rows, srcImg.cols, CV_8UC1, Scalar::all(0));
      Mat duplicate(srcImg.rows,srcImg.cols, CV_8UC1,Scalar::all(255) );

    if(!srcImg.data){

     cout<<"The file is not loaded or does not exist"<<endl;
     return -1;

     }

         
     
       for(int i = 0; i < srcImg.rows; i++) {
          for(int j = 0; j < srcImg.cols; j++) {
             double gray = 0.21 * srcImg.at<cv::Vec3b>(i,j)[0] +
                           0.72 * srcImg.at<cv::Vec3b>(i,j)[1] +
                           0.07 * srcImg.at<cv::Vec3b>(i,j)[2];
             grayScale.at<uchar>(i,j) = (uchar) gray;
            }
       
        }




     cout<<"Matrix grayScale :"<<grayScale.rows<<" "<<grayScale.cols<<endl;


/*     cout<<(int)grayScale.data[0]<<endl;
cout<<(int)grayScale.data[1]<<endl;
cout<<(int)grayScale.data[2]<<endl;



      cout<<(int)grayScale.data[3]<<endl;
cout<<"########################"<<endl;
      cout<<(int)grayScale.at<uchar>(0,0)<<endl;


cout<<(int)grayScale.at<uchar>(0,1)<<endl;

cout<<(int)grayScale.at<uchar>(0,2)<<endl;

cout<<(int)grayScale.at<uchar>(0,3)<<endl;
cout<<(int)grayScale.at<uchar>(0,4)<<endl;



*/

int vrows=srcImg.rows;
int vcols=srcImg.cols;
//int i,j=0;


   // #pragma acc data copy(grayScale.data[:grayScale.rows*][:grayScale.cols],duplicate[:duplicate.rows][:duplicate.cols])
  // {
        
/*        #pragma acc parallel //copy(grayScale.data[:vrows*vcols],duplicate.data[:vrows*vcols])
         for(int i=0;i<vrows*vcols;i++){

              duplicate.data[i]=grayScale.data[i];


	 }	 
*/


       /* #pragma acc parallel loop
	for(int i=0;i<vrows;i++){
        #pragma acc loop
        for(int j=0;j<vcols;j++){

	  duplicate.at<uchar>(i,j)=10;//grayScale.at<uchar>(i,j);

       }

      }
*/


    // #pragma acc parallel loop collapse(2) copy()

cout<<"Step"<<grayScale.step<<endl;
//cout<<"ch"<<grayScale.ch<<endl;

int b[3][5];

#pragma acc parallel loop copy(b[:3][:5])
for(int i=0;i<3;i++){
  #pragma acc loop	
  for(int j=0;j<5;j++){
    b[i][j]=i+j;


   }
}



cout<<"b[N-1][M-2] :"<<b[1][1]<<endl;
cout<<"b[N][M] :"<<b[2][4]<<endl;

//#pragma acc parallel loop copy(grayScale)
  
auto *startaddress=grayScale.data;


cout<<(int)*(startaddress+1)<<endl;
cout<<(int)*(startaddress+2)<<endl;






//        #pragma acc parallel //copy(grayScale.data[:vrows*vcols],duplicate.data[:vrows*vcols])
  //       for(int i=0;i<vrows*vcols;i++){

    //          duplicate.data[i]=grayScale.data[i];


      //   }



        #pragma acc parallel loop collapse(2)
        for(int i=0;i<vrows;i++){
        //#pragma acc loop
        for(int j=0;j<vcols;j++){

          duplicate.at<uchar>(i,j)=10;//grayScale.at<uchar>(i,j);

       }

      }


    cout<<"duplicate"<<": "<<(int)grayScale.at<uchar>(23,45)<<endl;
    cout<<"duplicate"<<": "<<(int)duplicate.at<uchar>(23,45)<<endl;

}
