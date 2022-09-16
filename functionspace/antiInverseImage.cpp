
#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
using namespace cv;

Mat WatershedAlg::antiInverseImage(Mat image) {
	    auto *startImg=image.data;
		int imgrows=image.rows;
		int imgcols=image.cols;
	    #pragma acc enter copyin(startImg[:imgrows*imgcols])
        #pragma acc parallel loop default(present)
        for(int i = 0; i < imgrows*imgcols; i++) {
                  if((int)startImg[i]==ZERO){
					  startImg[i]=ZERO;
				  }
				  else{
				      startImg[i]=ONE;
				  }
		  }
		#pragma acc exit data copyout(startImg[:imgrows*imgcols])		  
                  

        /*
		   #pragma acc loop
            for(int j = 0; j < imgcols; j++) {
                if( (int) image.at<uchar>(i,j) == ZERO ) {
                    image.at<uchar>(i,j) = ZERO;
                } else {
                    image.at<uchar>(i,j) = ONE;
                }
            }
        }
        */
        return image;
    }
