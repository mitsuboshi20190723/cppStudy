/*
 *  2021.2.2
 *  webcam.cpp
 *  ver 0.5
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

/*
 * for picam
 * echo "bcm2835-v4l2" >> /etc/modules
 * ls /dev/video*
 *
 * for openCV 4.5
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

//using namespace cv;

int main(int argc, char **argv)
{
	cv::VideoCapture cap(0);
	if(!cap.isOpened()) return -1;

	int t;
	double w, h, f;
	w = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	h = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	f = cap.get(cv::CAP_PROP_FPS);
	t = cap.get(cv::CAP_PROP_FORMAT); //2:RGB24
	std::cout << "w=" << w << ",h=" << h << ",fps=" << f << std::endl;
	std::cout << "FORMAT=" << t << std::endl;

	cap.set(cv::CAP_PROP_FRAME_WIDTH, w);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, h);
	cap.set(cv::CAP_PROP_FPS, f);

	cv::Mat img;
	cv::namedWindow("camera", cv::WINDOW_AUTOSIZE);
	for(;;)
	{
		cap >> img;
		cv::imshow("camera", img);
		if(cv::waitKey(30) >= 0) break;
	}
	return 0;
}
