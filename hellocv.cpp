#include "stdafx.h"
//インクルードファイル指定
#include <opencv2/opencv.hpp>
//静的リンクライブラリの指定
#include <opencv2/opencv_lib.hpp>
//名前空間の指定
#include<stdio.h>

void RecogBingo(int bingoImgx,int bingoImgy,int x,int y,int (*BingocardNumbers)[5]){
	int i,j;

	i = 0;
	j = 0;
	if(bingoImgx/5 > x){
		i = 0;
	}
	else if(bingoImgx/5 < x && bingoImgx*2/5 >x){
		i = 1;
	}
	else if(bingoImgx*2/5 < x && bingoImgy*3/5 > x){
		i = 2;
	}
	else if(bingoImgx*3/5 < x && bingoImgy*4/5 > x){
		i = 3;
	}
	else{
		i = 4;
	}

	if(bingoImgy*2/6 > y){
		j = 0;
	}
	else if(bingoImgy*2/6 < y && bingoImgy*3/6 >y){
		j = 1;
	}
	else if(bingoImgy*3/6 < x && bingoImgy*4/6 > y){
		j = 2;
	}
	else if(bingoImgy*4/6 < x && bingoImgy*5/6 > x){
		j = 3;
	}
	else{
		j = 4;
	}
	
	BingocardNumbers[i][j] = 71;
}

int main (int argc, char **argv)
{
  double min_val, max_val;
  CvPoint min_loc, max_loc;
  CvSize dst_size;
  CvFont font;
  IplImage *src_img, *tmp_img, *dst_img;
  int BingocardNumbers[5][5] = {0};
  int i,j;

  BingocardNumbers[2][2] = 100;

  if ((src_img = cvLoadImage ("BingoCard.jpg", CV_LOAD_IMAGE_COLOR)) == 0 ||
      (tmp_img = cvLoadImage ("BingoCard71.jpg", CV_LOAD_IMAGE_COLOR)) == 0)
    return -1;

  // (1)探索画像全体に対して，テンプレートのマッチング値（指定した手法に依存）を計算
  dst_size = cvSize (src_img->width - tmp_img->width + 1, src_img->height - tmp_img->height + 1);//cvSize(width,height);
  dst_img = cvCreateImage (dst_size, IPL_DEPTH_32F, 1);
  cvMatchTemplate (src_img, tmp_img, dst_img, CV_TM_CCOEFF_NORMED);
  cvMinMaxLoc (dst_img, &min_val, &max_val, &min_loc, &max_loc, NULL);

  printf("%lf %lf\n",min_val,max_val);
  printf("%d %d\n",max_loc.x,max_loc.y);

  if(max_val > 0.9){
	  printf("exist\n");
	  RecogBingo(src_img->height,src_img->width,max_loc.x,max_loc.y,BingocardNumbers);
  }
  for(i=0; i<5; i++){
	  for(j=0; j<5; j++){
		  printf("%d ",BingocardNumbers[i][j]);
	  }
	  printf("\n");
  }
   //(2)テンプレートに対応する位置に矩形を描画
  cvRectangle (src_img, max_loc,
               cvPoint (max_loc.x + tmp_img->width, max_loc.y + tmp_img->height), CV_RGB (255, 0, 0), 3);
  cvNamedWindow ("Image", 1);
  cvShowImage ("Image", src_img);
  cvWaitKey (0);

  cvDestroyWindow ("Image");
  cvReleaseImage (&src_img);
  cvReleaseImage (&tmp_img);
  cvReleaseImage (&dst_img);
 
  return 0;
}