#include "stdafx.h"
//インクルードファイル指定
#include <opencv2/opencv.hpp>
//静的リンクライブラリの指定
#include <opencv2/opencv_lib.hpp>
//名前空間の指定
#include<stdio.h>

int main (int argc, char **argv)
{
  IplImage *src_img = 0, *dst_img;
  IplImage *src_img_gray = 0;
  IplImage *tmp_img1, *tmp_img2, *tmp_img3;

  // (1)画像を読み込む
  //if (argc >= 2)
    src_img = cvLoadImage ("BingoCard.jpg", CV_LOAD_IMAGE_COLOR);
  if (src_img == 0)
    return -1;

  tmp_img1 = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  tmp_img2 = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  tmp_img3 = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  src_img_gray = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  cvCvtColor (src_img, src_img_gray, CV_BGR2GRAY);
  dst_img = cvCloneImage (src_img);

  // (2)ガウシアンフィルタで平滑化を行う
  cvSmooth (src_img_gray, src_img_gray, CV_GAUSSIAN, 5);

  // (3)二値化:cvThreshold
  cvThreshold (src_img_gray, tmp_img1, 50, 255, CV_THRESH_BINARY);

  // (4)二値化:cvAdaptiveThreshold
  //cvAdaptiveThreshold (src_img_gray, tmp_img2, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 11, 10);

  // (5)二つの二値化画像の論理積
  //cvAnd (tmp_img1, tmp_img2, tmp_img3);
  //cvCvtColor (tmp_img3, dst_img, CV_GRAY2BGR);

  // (6)元画像と二値画像の論理積
  //cvSmooth (src_img, src_img, CV_GAUSSIAN, 11);
  //cvAnd (dst_img, src_img, dst_img);
  cvSaveImage("Binary.jpg",tmp_img1);  
	  // (7)画像を表示する
  cvNamedWindow ("Threshold", CV_WINDOW_AUTOSIZE);
  cvShowImage ("Threshold", tmp_img1);
  //cvNamedWindow ("AdaptiveThreshold", CV_WINDOW_AUTOSIZE);
  //cvShowImage ("AdaptiveThreshold", tmp_img2);
  //cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
  //cvShowImage ("Image", dst_img);
  cvWaitKey (0);

  cvDestroyWindow ("Threshold");
  //cvDestroyWindow ("AdaptiveThreshold");
  //cvDestroyWindow ("Image");
  cvReleaseImage (&src_img);
  cvReleaseImage (&dst_img);
  cvReleaseImage (&src_img_gray);
  cvReleaseImage (&tmp_img1);
  cvReleaseImage (&tmp_img2);
  cvReleaseImage (&tmp_img3);

  return 0;
}
