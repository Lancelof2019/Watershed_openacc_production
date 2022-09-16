#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
using namespace cv;
#define ZERO 0
 void WatershedAlg::removeholesopt(Mat& src,int pnumThrshold, int handlingType, int neighbourType,int pixelThreshold)  {
   
    int RemoveCount=0;       

    Mat Pointlabel(src.rows,src.cols, CV_8UC1,Scalar::all(255) );  
    
 
     auto *srcstart=src.data;
	 auto *plstart=Pointlabel.data;
	 int srcrows=src.rows;
	 int srccols=src.cols;
       // cout<<"removing holes start. "<<endl;  
	    #pragma acc enter data copyin(srcstart[:srcrows*srccols],plstart[:srcrows*srccols],pixelThreshold)
        #pragma acc parallel loop default(present)
		for(int i=0;i<srcrows*srccols;i++){
			
			if(srcstart[i]>pixelThreshold){
				plstart[i]=0;
			}
			
		}
		#pragma acc exit data copyout(srcstart[:srcrows*srccols],plstart[:srcrows*srccols])
		
		/*
        for(int i = 0; i < src.rows; ++i)  {    
           // uchar* iData = src.ptr<uchar>(i);  
           // uchar* iLabel = Pointlabel.ptr<uchar>(i);  
            #pragma acc loop
            for(int j = 0; j < src.cols; ++j) {    
                 if(src.at<uchar>(i,j)>pixelThreshold){
                 Pointlabel.at<uchar>(i,j)=0;
                 
               
                 }
               // if (iData[j] > pixelThreshold)    
              //  {    
                   // iLabel[j] = 3;   
              //  }    
            }    
        }  
		*/

//**

 //  imshow("prepration for contours",Pointlabel);
//
  //  cv::waitKey(0);

   // Mat dulpPointlabel;
    //Pointlabel.copyTo(dulpPointlabel);
    vector<vector<Point>> contours;  
    vector<cv::Vec4i> hierarchy; 
    findContours(Pointlabel,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point()); 
    Mat imageContours=Mat::zeros(Pointlabel.size(),CV_8UC1);  
    Mat contouroutput=Mat::zeros(Pointlabel.size(),CV_8UC1);  
    Point p=Point(0,0);



   if (!contours.empty() && !hierarchy.empty()) 
	{
		vector<vector<Point> >::const_iterator itc = contours.begin();
	
		while (itc != contours.end()) 
		{
			
			cv::Rect countourposition = cv::boundingRect(Mat(*itc));//number of countourposition
			
			double area = contourArea(*itc);
			int countoury=countourposition.y;
			int countourx=countourposition.x;
			int countourybd=countourposition.y + countourposition.height;
			int countourxbd=countourposition.x + countourposition.width;
			
			if (area < pnumThrshold) 
			{
				
				//
				
				
				#pragma acc enter data copyin(srcstart[:srcrows*srccols],pixelThreshold,plstart[:srcrows*srccols])
				#pragma acc parallel loop collapse(2) default(present)
				for (int i = countoury; i < countourybd; i++) 
				{
					
                 
					for (int j = countourx; j < countourxbd; j++) {
						if((int)plstart[i*countourxbd+j]==255){
						plstart[i*w+j]=2;
						srcrows[i*w+j]=pixelThreshold;
						
						}
						
					}
				}
				#pragma acc exit data copyout(srcstart[:srcrows*srccols],plstart[:srcrows*srccols])
				
				/*
				#pragma acc parallel loop copy(src[:src.rows][:src.cols],Pointlabel[:src.rows][:src.cols],pixelThreshold)
				for (int i = countourposition.y; i < countourposition.y + countourposition.height; i++) 
				{
					//uchar *output_data = dst.ptr<uchar>(i);
                   #pragma acc loop
					for (int j = countourposition.x; j < countourposition.x + countourposition.width; j++) 
					{
						
						if ((int)Pointlabel.at<uchar>(i,j) == 255) 
						{
							Pointlabel.at<uchar>(i,j) = 2;
                            src.at<uchar>(i,j)=pixelThreshold;

						}
					}
				}
				*/
				//
			}//if
			itc++;
		}//while
	}//if
 }