#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
#include <queue>
#include <cstdlib> 
#include <vector>
#define NUMSIZE 8
#define NSIZE 4
//#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/functionspace/removesmallregion.cpp"
using namespace cv;

/*bool comp(Point a,Point b){
      if(a.x!=b.x){
         return a.x<b.x;
     // else if(a.x==b.x)
      }
      return a.y<b.y;

}
*/
Mat WatershedAlg::distanceTransform(Mat image, vector<Point> &markers) {
        vector< vector<double> > distanceMap(image.rows, vector<double>(image.cols, 0));
        Mat markerImage(image.rows, image.cols, CV_8UC3, Scalar::all(0));

    /**************************/
       //cv::Mat dsrcImg=cv::imread("/opt/project_space/test_mnist/HPC_comb_code/watershed_demo/energy/12_energy_map.png");
       // Mat testImg=image;
	    
        queue<int> qx, qy;
        int dx[NUMSIZE]={-1, 1, 0, 0, -1, -1, 1, 1};
        int dy[NUMSIZE]={0, 0, -1, 1, -1,  1, 1, -1};
        //int numthresh=25;
        int pixelThreshold=45;
        //new added part:
        vector<bool>checkVisted;
        vector<Point>zeroEdge;
        vector< vector<bool> > visited(image.rows, vector<bool>(image.cols, false));
     

//******It makes the nearest piexel along 0 point sohow up and become the edge pixel
        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {
                
                if(image.at<uchar>(i, j) != ZERO) {
                    continue;
                }
                //this is the part that sepreated from the edge
                
                for(int h = 0; h < NSIZE; h++) {
                    int nextX = i + dx[h];
                    int nextY = j + dy[h];

                    if( nextX < 0 || nextY < 0 || nextX >= image.rows || nextY >= image.cols ) {
                        continue;
                    }

                    if( !visited[nextX][nextY] && (int) image.at<uchar>(nextX, nextY) == ONE ) {
                        visited[nextX][nextY] = true;
                        image.at<uchar>(nextX, nextY) = pixelThreshold;
                        qx.push(nextX);
                        qy.push(nextY);
                       //the neighuours are all points who have 75 or 0 
                       //they are the points who are edges
                       checkVisted.push_back(visited[nextX][nextY]);

                    }
                }
                if(checkVisted[0]||checkVisted[1]||checkVisted[2]||checkVisted[3]){


                  zeroEdge.push_back(Point(i,j));
                  checkVisted.clear();
                }

         
             

        }
        
     }
    //******It makes the nearest piexel along 0 point sohow up and become the edge pixel
    
//edge is equal to 50
        int maxVal=0;
        //**Magic part**//
        while(!qx.empty()) {
            int crtX = qx.front(); qx.pop();
            int crtY = qy.front(); qy.pop();

            bool isBigger = true;//check
            //#pragma omp parallel for
            for(int h = 0; h < 8; h++) {
                int nextX = crtX + dx[h];
                int nextY = crtY + dy[h];

                if( nextX < 0 || nextY < 0 || nextX >= image.rows || nextY >= image.cols || (int) image.at<uchar>(nextX, nextY) == ZERO ) {
                    continue;
                }

                if( (int) image.at<uchar>(crtX, crtY) <= (int) image.at<uchar>(nextX, nextY)) {
                    isBigger = false;
                    
                }
                //pick the max local value of some regions

                if( (int) image.at<uchar>(crtX, crtY) +1< (int) image.at<uchar>(nextX, nextY) ) {
                    visited[nextX][nextY] = true;
                    image.at<uchar>(nextX, nextY) = (uchar) min((image.at<uchar>(crtX, crtY)+1), 254);
                    
                    //to get max value for difference between max value image and image
                    if(maxVal<=(int)image.at<uchar>(nextX, nextY)){
                       maxVal=(int)image.at<uchar>(nextX, nextY);
                       
                    }
                     //to get max value for difference between max value image and image
                    qx.push(nextX);//qx is not determinabale
                    qy.push(nextY);
       
         

                }
             }
           //find the max value in local area
            if(isBigger) {
                markers.push_back(Point(crtX, crtY));
        
                #pragma acc parallel loop copy(crtX,crtY,dx[:NUMSIZE],dy[:NUMSIZE])
                for(int h = 0; h < NUMSIZE; h++) {
                 //  int temp_nextX = crtX + dx[h];
                   //int temp_nextY = crtY + dy[h];
                   if( crtX + dx[h] < 0 || crtY + dy[h] < 0 || crtX + dx[h]>= image.rows || crtY + dy[h] >= image.cols || (int) image.at<uchar>(crtX + dx[h],crtY + dy[h]) == ZERO ) {
                   continue;
                }
                
                }
         
                            

            }
        
        }


   pixelThreshold=pixelThreshold-1;

   int pnumThrshold=30;
   int handlingType=0;
   int neighbourType=0;

   removeholesopt(image,pnumThrshold,  handlingType, neighbourType, pixelThreshold);


/*

        Mat vlogImg;
        image.copyTo(vlogImg);
        int x_coordi=0;
        int y_coordi=0;
        #pragma acc parallel loop copy(markers[:markers.size()],vlogImg[:vlogImg.rows][:vlogImg.cols])
        for(vector<Point>::iterator it=markers.begin();it<markers.end();it++){
         //x_coordi=(*it).x;
        // y_coordi=(*it).y;
         vlogImg.at<uchar>((*it).x,(*it).y)=255;
        }

       imshow("With seeds",vlogImg);
       cv::waitKey(0);
 
*/


       return image;
    }