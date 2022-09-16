#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
using namespace cv;
#define ZERO 0
 void WatershedAlg::removesmallregion(Mat& src,int pnumThrshold, int handlingType, int neighbourType,int pixelThreshold)  {
   

   cv::imshow("distanceTransform before remove holes",src);
   cv::waitKey(0);
    int RemoveCount=0;       
    string filename33="/opt/test33.txt";
    ofstream fout33(filename33);
    string filename34="/opt/test34.txt";
    ofstream fout34(filename34);
     string filename35="/opt/test35.txt";
    ofstream fout35(filename35);
    vector<Point> NeihborPos;
    queue<int> qx, qy;
    vector<Point>pixbuffer;
    Mat Pointlabel(src.rows,src.cols, CV_8UC1,Scalar::all(0) );  


 
        cout<<"removing holes start. "<<endl;  
        for(int i = 0; i < src.rows; ++i)    
        {    
           // uchar* iData = src.ptr<uchar>(i);  
           // uchar* iLabel = Pointlabel.ptr<uchar>(i);  
            for(int j = 0; j < src.cols; ++j)    
            {    
                 if(src.at<uchar>(i,j)>pixelThreshold){
                 Pointlabel.at<uchar>(i,j)=3;
                 }
               // if (iData[j] > pixelThreshold)    
              //  {    
                   // iLabel[j] = 3;   
              //  }    
            }    
        }    
    //}  
/*
    for(int i=0;i<src.rows;i++){
           for(int j=0;j<src.cols;j++){
           fout34<<(int)src.at<uchar>(i,j)<<",";
             

         }
          fout34<<endl;
      }
         fout34.close();
         */
     //vector record the neighbours 
    NeihborPos.push_back(Point(-1, 0));  
    NeihborPos.push_back(Point(1, 0));  
    NeihborPos.push_back(Point(0, -1));  
    NeihborPos.push_back(Point(0, 1));
    NeihborPos.push_back(Point(-1, -1));  
    NeihborPos.push_back(Point(-1, 1));  
    NeihborPos.push_back(Point(1, -1));  
    NeihborPos.push_back(Point(1, 1));  
     

       
    int NeihborCount=4+4*neighbourType;  //4 or 8 (if neighbourType==0 ,NeihborCount 4)(if neighbourType==1,NeihborCount 8)
    int CurrX=0, CurrY=0;  // it is the beginning for local coordinates
   // vector<Point> GrowBuffer;   


//**to abtain the edge around 0 **//
    for(int i = 0; i < Pointlabel.rows; i++) {
            for(int j = 0; j < Pointlabel.cols; j++) {
                
                if((int)Pointlabel.at<uchar>(i, j) != 3) {
               //     cout<<"Pointlabel"<<((int)Pointlabel.at<uchar>(i, j))<<endl;
                    continue;
                }
                //this is the part that sepreated from the edge
                //Pointlabel.at<int>(i,j)=1;
               // qx.push(i);
               // qy.push(j);
               for(int h = 0; h < 4; h++) {
                // cout<<"-----------------------------------------"<<endl;
                    int nextX = i + NeihborPos.at(h).x;
                    int nextY = j + NeihborPos.at(h).y;
                  //  cout<<"nextX:"<<nextX<<endl;
                  //  cout<<"nextY:"<<nextY<<endl;

                    if( nextX < 0 || nextY < 0 || nextX >= Pointlabel.rows || nextY >= Pointlabel.cols ) {
                        continue;
                    } 
                 //   cout<<"approved passed point:"<<(int)Pointlabel.at<uchar>(nextX, nextY)<<endl;

                  //  cout<<"-----------------------------------------"<<endl;
                    if( (int)Pointlabel.at<uchar>(nextX,nextY)==0&&(int)src.at<uchar>(nextX,nextY)==0) {
                        // if(!Pointlabel.at<int>(nextX,nextY) && (int) src.at<uchar>(nextX, nextY) == ZERO )
                        //visited[nextX][nextY] = true;
                        Pointlabel.at<uchar>(nextX,nextY)=1;
                        //image.at<uchar>(nextX, nextY) = pixelThreshold;
                       qx.push(nextX);
                       qy.push(nextY);
                       //the neighuours are all points who have 75 or 0 
                       //they are the points who are edges
                      // checkVisted.push_back(visited[nextX][nextY]);

                    }
                    
              }//
               // if(checkVisted[0]||checkVisted[1]||checkVisted[2]||checkVisted[3]){


                //  zeroEdge.push_back(Point(i,j));
               //   checkVisted.clear();
              //  }          

        }
        
     }
      

       for(int i=0;i<Pointlabel.rows;i++){
           for(int j=0;j<Pointlabel.cols;j++){
              fout34<<(int)Pointlabel.at<uchar>(i,j)<<",";
             

         }
           fout34<<endl;
      }
           fout34.close();


      
      

      int addpixcounter=0;
      int edgepixcounter=0;
      while(!qx.empty()) {

            
            int crtX = qx.front(); qx.pop();
            int crtY = qy.front(); qy.pop();
            edgepixcounter++;
            pixbuffer.push_back(Point(crtX,crtY));
           // bool isBigger = true;//check
            for(int h = 0; h < 8; h++) {
                int nextX = crtX + NeihborPos.at(h).x;
                int nextY = crtY + NeihborPos.at(h).y;

               if( nextX < 0 || nextY < 0 || nextX >= Pointlabel.rows || nextY >= Pointlabel.cols||(int)Pointlabel.at<uchar>(nextX,nextY)==3) {
                        continue;
                    
                }

              //  if( (int) image.at<uchar>(crtX, crtY) <= (int) image.at<uchar>(nextX, nextY)) {
                  //  isBigger = false;
                    
              //  }
          if( abs(crtX - qx.front())==1||abs(crtY-qy.front())==1 ){
               if(Pointlabel.at<uchar>(crtX,crtY)>Pointlabel.at<uchar>(nextX,nextY)){
                    addpixcounter++;//for point(crtX,crtY)
                    
                    Pointlabel.at<uchar>(nextX,nextY)=1;
                     
                    qx.push(nextX);
                    qy.push(nextY);
                    
                    pixbuffer.push_back(Point(nextX,nextY));
                    

               }
          }

           else{
             
             fout35<<"*******************************************************"<<endl;
             fout35<<"The acount of adding point is:"<<addpixcounter<<endl;

             fout35<<"The acount of edge point is:"<<edgepixcounter<<endl;
             
             fout35<<"The size of pixbuffer : "<<pixbuffer.size()<<endl;
             fout35<<"*******************************************************"<<endl;
             fout35<<endl;
             if(edgepixcounter!=0){
               if(pixbuffer.size()<11){

                for(int i=0;i<pixbuffer.size();i++){
                   Pointlabel.at<uchar>(pixbuffer.at(i).x,pixbuffer.at(i).y)=2;

                        
                  }

                }
             }

             addpixcounter=0;
             edgepixcounter=0;
             pixbuffer.clear();

           }
                //pick the max local value of some regions
              /*
                if( (int) image.at<uchar>(crtX, crtY) +1< (int) image.at<uchar>(nextX, nextY) ) {
                    visited[nextX][nextY] = true;
                    image.at<uchar>(nextX, nextY) = (uchar) min((image.at<uchar>(crtX, crtY)+1), 254);
                    
                    //to get max value for difference between max value image and image
                    if(maxVal<=(int)image.at<uchar>(nextX, nextY)){
                       maxVal=(int)image.at<uchar>(nextX, nextY);
                       
                    }
                     //to get max value for difference between max value image and image
                    qx.push(nextX);
                    qy.push(nextY);
                  //  fout4<<"the postion of push point: "<<Point(nextX,nextY)<<"The value of image: "<<((int)image.at<uchar>(nextX,nextY))<<",";
         

                }
                //fout4<<endl;
                */
            }
           //find the max value in local area
           /* if(isBigger) {//
                markers.push_back(Point(crtX, crtY));
               // cout<<"******************Potion and values******************"<<endl;
             //   cout<<Point(crtX, crtY)<<endl;
           
                
               // cout<<(int)image.at<uchar>(crtX,crtY)<<endl;
               // cout<<"The other parts of the value in position ctrx and ctry "<<endl;
                for(int h = 0; h < 8; h++) {
                   int temp_nextX = crtX + dx[h];
                   int temp_nextY = crtY + dy[h];
                   if( temp_nextX < 0 || temp_nextY < 0 || temp_nextX >= image.rows || temp_nextY >= image.cols || (int) image.at<uchar>(temp_nextX, temp_nextY) == ZERO ) {
                   continue;
                }
                //  cout<<"The value of "<<"["<<temp_nextX<<","<<temp_nextY<<"]:"<<(int)image.at<uchar>(temp_nextX,temp_nextY)<<endl;
                }
         
                            

            }//
            */
        
        }
        fout35.close();





/*
     for(int u=0;u<=20;u++){
       cout<<qx.front()<<endl;
       cout<<qy.front()<<endl;
       cout<<"Pointlabel.at:"<<(int)Pointlabel.at<uchar>(qx.front(),qy.front())<<endl;
       qx.pop();
       qy.pop();



     }
     */
         for(int i=0;i<Pointlabel.rows;i++){
           for(int j=0;j<Pointlabel.cols;j++){
           fout33<<(int)Pointlabel.at<uchar>(i,j)<<",";
             

         }
          fout33<<endl;
      }
         fout33.close();

   


  /*****  for(int i = 0; i < src.rows; ++i)    
    {    
        //uchar* iLabel = Pointlabel.ptr<uchar>(i);  // Mat Pointlabel = Mat::zeros( src.size(), CV_8UC1 );  
        for(int j = 0; j < src.cols; ++j)    
        {    
            if (Pointlabel.at<uchar>(i,j) == 0)    
            {    
                
               // vector<Point> GrowBuffer;                               //vector to record the 0 point in the matrix 
              //  GrowBuffer.push_back( Point(i,j) );  //GrowBuffer(z).x=123,GrowBuffer(z)=456,===>(123,456)
             //   Pointlabel.at<uchar>(i, j)=1;  //chnage current label into 1 which means the Pointlabel has been visited
                
             //   int CheckResult=0;                                               //
  
                for ( int z=0; z<GrowBuffer.size(); z++ )  
                {  
  
                    for (int q=0; q<NeihborCount; q++)                                      //monitor the 4 neighbours 
                    {  
                   //     CurrX=GrowBuffer.at(z).x+NeihborPos.at(q).x;  
                    //    CurrY=GrowBuffer.at(z).y+NeihborPos.at(q).y;  
                  //      if (CurrX>=0&&CurrX<src.cols&&CurrY>=0&&CurrY<src.rows)  //control the border  
                        {  
                   //         if ( Pointlabel.at<uchar>(CurrY, CurrX)==0 )  
                            {  
                    //            GrowBuffer.push_back( Point(CurrX, CurrY) );  //the neighbour whose Pointlabel is 0 will be added into vector GrowBuffer
                     //           Pointlabel.at<uchar>(CurrY, CurrX)=1;         //  the neighbour whose Pointlabel is 0 will be changed into 1
                            }  
                        }  
                    }  
  
                }  
                //
               // if (GrowBuffer.size()>pnumThrshold) {
             //      CheckResult=2;   
            //       for (int z=0; z<GrowBuffer.size(); z++)                           
            //     {  

                //   CurrX=GrowBuffer.at(z).x;   
               //    CurrY=GrowBuffer.at(z).y;  
            //       Pointlabel.at<uchar>(CurrY, CurrX) =2;  
          //        } 
         //      }      //if the total number of the neighbours of point including itself is beyond  pnumlThrshold the value is 2,otherwise 1. 
             //  else {
          //         CheckResult=1;   
                    //RemoveCount++;
                 /*        for (int z=0; z<GrowBuffer.size(); z++)                           
                   {  

                    CurrX=GrowBuffer.at(z).x;   
                    CurrY=GrowBuffer.at(z).y;  
                    Pointlabel.at<uchar>(CurrY, CurrX) =1;  
                  }*/ 
           //        }  

                    
            //then we can see the useful point will be 1 ,otherwise the ok sttaus is ok, and some points is beyond thrshhold will be 2
                
    
  
     //       }    
    //    }
/*
       if (GrowBuffer.size()>pnumThrshold) {
                 //CheckResult=2;   
                 for (int z=0; z<GrowBuffer.size(); z++)                           
               {  

               CurrX=GrowBuffer.at(z).x;   
               CurrY=GrowBuffer.at(z).y;  
               Pointlabel.at<uchar>(CurrY, CurrX) =2;  
                } 
                GrowBuffer.clear();
             }      //if the total number of the neighbours of point including itself is beyond  pnumlThrshold the value is 2,otherwise 1. 
               else {
                 //CheckResult=1;   
           
               }  
                


    }  //
*/

/*
    for(int i = 0; i < Pointlabel.rows; i++) {
      for(int j = 0; j < Pointlabel.cols; j++) {

             // fout33<<(int)Pointlabel.at<uchar>(i,j)<<",";
             if((int)Pointlabel.at<uchar>(i,j)==1){
                src.at<uchar>(i,j)=pixelThreshold;
  
             }
             // fout34<<(int) src.at<uchar>(i,j)<<",";
            }
          // fout33<<endl;
          /// fout34<<endl;

       }
         // fout33.close();
         // fout34.close();


*/


  
}