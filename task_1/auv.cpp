#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<stdio.h>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
Mat img,img2;
int i,j,circles[7],a=0,c=0,num;
Mat pic=imread("auv.jpg",1);
cvtColor(pic,img,CV_BGR2GRAY);
Mat img1(pic.rows,pic.cols,CV_8UC1,Scalar(0));
Mat finalimg(pic.rows,pic.cols,CV_8UC1,Scalar(0));

for(i=0;i<img.rows;i++)
    for(j=0;j<img.cols;j++)
 	{
		if(img.at<uchar>(i,j)>190)
			img1.at<uchar>(i,j)=255;
		else
			img1.at<uchar>(i,j)=0;
	}
vector<vector<Point> >contours;
vector<vector<Point> >cont;
vector<Vec4i> hierarchy;

Canny(img1,img2,50,75,5,4);

findContours(img2,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));

 cout<<"Enter the sum of numbers to be shown on dice : ";
 cin>>num;
     
 
  for( int i = 0; i< contours.size(); i++ )
     {
    if((arcLength(contours[i],1)>=200)&&(arcLength(contours[i],1)<=2000))
      {
       cont.push_back(contours[i]);
       if(a>0)
        circles[c++]=a;
       a=0;
           
     drawContours( pic, contours,i,  Scalar(0,0,255), 2, 8, hierarchy, 0, Point() );
      
       i=i+1;
      }
      
    else if(arcLength(contours[i],1)<=200)
       if((contourArea(contours[i],0)>=250||contourArea(contours[i],0)<=-250))
       if(i!=27)
          {
    		a++;
    		Point2f center;
     		float radius;
     		minEnclosingCircle(contours[i],center,radius);
     		circle(pic,center,cvRound(radius),Scalar(0,255,0),2);
   		i++;
          }
       
      }
       
       circles[6]=a;
       
       for(i=0;i<7;i++)
       { 
         int m;
         for(m=0;m<7;m++)
             if(m!=i)
             if(circles[m]==num-circles[i])
              {
                cout<<i+1<<endl;
        	Point2f corner[4];
        	RotatedRect box = minAreaRect(cont[i]);
       		box.points(corner);
        	int j,k;
        	int xl=corner[0].x,xh=corner[0].x,yl=corner[0].y,yh=corner[0].y;
                for( j = 0; j < 4; j++ )
                   {
			if(corner[j].x<xl)
				xl=corner[j].x;
			if(corner[j].x>xh)
				xh=corner[j].x;
			if(corner[j].y<yl)
				yl=corner[j].y;
			if(corner[j].y>yh)
				yh=corner[j].y;
		   }
		for(j=yl;j<yh;j++)
		for(k=xl;k<xh;k++)
			finalimg.at<uchar>(j,k)=img1.at<uchar>(j,k);

          
     	      }
       }
cout<<endl;
cout<<"over";
namedWindow("window",WINDOW_NORMAL);
imshow("window",pic);
namedWindow("window2",WINDOW_NORMAL);
imshow("window2",finalimg);
waitKey(0);

}
