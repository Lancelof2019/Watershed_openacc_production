 #include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
 #include<iostream>
 using namespace std;
 using namespace cv;
 #include <time.h>
 int main(){

     /////////////////string filename30="/opt/test30.txt";
     //ofstream fout30(filename30);
    // cout<<"---Image will be read into memory-----"<<endl;
    clock_t start,end;
    start=clock();
    //cv::Mat srcImg=cv::imread("/opt/testimages/landscape.jpg");
     

     //cv::Mat srcImg=cv::imread("/opt/project_space/test_mnist/HPC_comb_code/Pictures_source/Dog/9d97ca8c85b481e7b1245cd65ec8bd5f.jpg");
   // cv::imshow("original image",orgImg); 
   // cv::waitKey(0);
   // Mat srcImg;
  //  resize(orgImg,   srcImg, Size(orgImg.rows*0.6,orgImg.cols*0.5));

     // cv::Mat srcImg=cv::imread("/opt/project_space/test_mnist/HPC_comb_code/Pictures_source/Dog/9d97ca8c85b481e7b1245cd65ec8bd5f.jpg");
    // cv::Mat srcImg=cv::imread("/opt/project_space/test_mnist/HPC_comb_code/Pictures_source/Dog/9d97ca8c85b481e7b1245cd65ec8bd5f.jpg");
    // cv::imshow("test1",srcImg);
   
    // cv::Mat srcImg=cv::imread("/opt/testimages/istockphoto-1150481340-612x612.jpg");

    // cv::Mat srcImg=cv::imread("/opt/PicturesOvergementation/beach.jpg");
     cv::Mat srcImg=cv::imread("/opt/testimages/matterhorn-1313x875.jpg");
      cv::imshow("orginal",srcImg);
      //cv::Mat srcImg=cv::imread("/opt/testimages/SHX8-038_1568286487.jpg");
     // cv::Mat srcImg=cv::imread("/opt/prroject_space/test_mnist/HPC_comb_code/Pictures_source/Dog/7fb67f13a3cd5be143710404fcd42661.jpg");
     //cv::imshow("Test image",srcImg);
     //cv::waitKey(0);
    // Mat dstImg = Mat::zeros(256,256 , CV_8UC3); 
	  // resize(srcImg,   dstImg, dstImg.size());

	  // imshow("resize", dstImg);
     
     //opt/project_space/test_mnist/HPC_comb_code/watershed_demo/energy/12_energy_map.png");
     
     //cv::Mat srcImg=cv::imread("/opt/Herd/234996-14022PQ02888.jpg");
     ///opt/project_space/test_mnist/HPC_comb_code/watershed_demo/energy/32_energy_map.png");
  
	   //imshow("resize", dstImg);
    // cv::Mat duplImage=dstImg;
     ///opt/project_space/test_mnist/HPC_comb_code/watershed_demo/energy/12_energy_map.png");

         
         //"Copyright-Norfolk-Castle-Museum.jpg");   
     
     //opt/project_space/te st_mnist/HPC_comb_code/watershed_demo/energy/2_energy_map.png");
     
    // cv::waitKey();
     cv::Mat duplImage(srcImg.rows,srcImg.cols,CV_8UC3,Scalar::all(0));
     srcImg.copyTo(duplImage);
    /*
        for(int i = 0; i < srcImg.rows; i++) {
          for(int j = 0; j < srcImg.cols; j++) {

          fout30<<((int)srcImg.at<uchar>(i,j))<<",";
             

        }
         fout30<<endl;
     }
       fout30.close();
       */
     //double ratio=0.09;
     WatershedAlg *walg=new WatershedAlg();
     walg->processImage(srcImg,duplImage);
     end=clock();
     cout<<"CLOCKS_PER_SEC :"<<CLOCKS_PER_SEC<<endl;
     cout<<"The total time the algorithm used is :"<<(double)(end - start)/CLOCKS_PER_SEC<<"s"<<endl;
     return 0;
   } 