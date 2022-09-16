#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
#include<vector>
#include<iomanip>
#define NUMSIZE 8
#define NSIZE 4
using namespace cv;

Mat WatershedAlg::watershed(Mat image, vector<Point>  &markers,Mat duplImage) {
 
   
        
        priority_queue<Pixel,vector<Pixel>,Compare> prioq;//compare the value of image.at<uchar>(i,j)
        Mat markerImage(image.rows, image.cols, CV_8UC3, Scalar::all(0));
            vector<cv::Vec3b> colors{ {0, 0, 0} };
            for(int i = 1; i <= markers.size()+1; i++) {
                Vec3b vecColor;
                  
                for(int j=0;j<3;j++){

                 vecColor[j] = rand()%255+j;

               }
            
            
                colors.push_back(vecColor);
         }
  
        
        vector<vector<int>> markerMap(image.rows, vector<int>(image.cols, 0));
        vector<vector<bool>> inprioq(image.rows, vector<bool>(image.cols, false));
        int dx[NUMSIZE]={-1, 1, 0, 0, -1, -1, 1, 1};
        int dy[NUMSIZE]={0, 0, -1, 1, -1,  1, 1, -1};

        // Put markers in priority queue
        int id = 1;
        Mat testDuplicate;
        duplImage.copyTo(testDuplicate);
        Mat dstImage(duplImage.rows,duplImage.cols,CV_8UC3,Scalar::all(0));
  
      /* #pragma omp parallel for
       for(vector<Point>::iterator markit=markers.begin();markit<markers.end();markit++) {
     
            markerMap[(*markit).x][(*markit).y] = id;
           // cout<<"--------------------------------"<<endl;
           // cout<<"markitx:"<<(*markit).x<<endl;

          //  cout<<"markity:"<<(*markit).y<<endl;
            for(int i = 0; i < 4; i++) {

                int newX = (*markit).x + dx[i];
                int newY = (*markit).y + dy[i];
                if(newX < 0 || newY < 0 || newX >= image.rows || newY >= image.cols) {
                    continue;
                }
                //cout<<"The current marker point:"<<marker<<endl;
               // cout<<(int)image.at<uchar>(marker.x, marker.y)<<endl;
               // cout<<"----------------"<<endl;
               // cout<<"next position:"<<"["<<newX<<","<<newY<<"]"<<endl;
               // cout<<(int)image.at<uchar>(newX, newY)<<endl;

                prioq.push( Pixel( (int) image.at<uchar>(newX, newY), newX, newY) );//start from the neighuobors who got bigger value
                
            }

            id++;
        }
        
*/

        for(auto marker: markers) {
     
            markerMap[marker.x][marker.y] = id;
            
            for(int i = 0; i < 4; i++) {

                int newX = marker.x + dx[i];
                int newY = marker.y + dy[i];
                if(newX < 0 || newY < 0 || newX >= image.rows || newY >= image.cols) {
                    continue;
                }
                //cout<<"The current marker point:"<<marker<<endl;
               // cout<<(int)image.at<uchar>(marker.x, marker.y)<<endl;
               // cout<<"----------------"<<endl;
               // cout<<"next position:"<<"["<<newX<<","<<newY<<"]"<<endl;
               // cout<<(int)image.at<uchar>(newX, newY)<<endl;

                prioq.push( Pixel( (int) image.at<uchar>(newX, newY), newX, newY) );//start from the neighuobors who got bigger value
                
            }

            id++;
        }
























             // cout<<"The first time when the next points,the size is: "<<prioq.size()<<endl;

              //priority_queue<Pixel,vector<Pixel>,Compare> tmp_prioq;

              //tmp_prioq=prioq;

     
        // string filename33="/opt/test33.txt";
        // ofstream fout7(filename7);


          //each marker got its position and its neighbour<--> ^ and V
      
/*
        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {

             fout5<<((int)markerMap[i][j])<<",";
             

        }
         fout5<<endl;
     }
     fout5.close();
     */
        while(!prioq.empty()) {
            Pixel curpoint = prioq.top(); prioq.pop();//store the neighbours near ctrx and ctry

            bool canLabel = true;
            int neighboursLabel = 0;
            for(int i = 0; i < NSIZE; i++) {
                int nextX = curpoint.x + dx[i];
                int nextY = curpoint.y + dy[i];
                if(nextX < 0 || nextY < 0 || nextX >= image.rows || nextY >= image.cols) {
                    continue;
                }
                Pixel next = Pixel( (int) image.at<uchar>(nextX, nextY), nextX, nextY);

                // Must check if all surrounding marked have the same color
                if(markerMap[next.x][next.y] != 0 && next.val != 0) {
                    if(neighboursLabel == 0) {
                        neighboursLabel = markerMap[next.x][next.y];
                    } else {
                        if(markerMap[next.x][next.y] != neighboursLabel ) {
                            canLabel = false;
                        }
                    }
                } else {
                    if(inprioq[nextX][nextY] == false) {
                        inprioq[next.x][next.y] = true;//aviod duplicate point is chosen
                        prioq.push(next);
                        //the most important expending step,//only the point whose pixel value is 0 in Markermap
                    }
                }
            }

            if(canLabel&&(int)image.at<uchar>(curpoint.x,curpoint.y)!=0) {
                
                markerMap[curpoint.x][curpoint.y] = neighboursLabel;
               duplImage.at<Vec3b>(curpoint.x,curpoint.y)=colors[ markerMap[curpoint.x][curpoint.y] ];
         
                
            }
         
        }
//check the data


       cv::imshow("testDuplicate",testDuplicate);
       cv::waitKey(0);
       cv::imshow("duplImage",duplImage);
       cv::waitKey(0);

       
       cv::addWeighted(duplImage,0.4,testDuplicate,0.6,0,dstImage);
     

        image.release();
        duplImage.release();
        testDuplicate.release();
        return dstImage;
    }