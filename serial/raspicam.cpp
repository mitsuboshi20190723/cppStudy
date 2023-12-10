/*
 *  2023.12.10
 *  raspicam.cpp
 *  ver.1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

/*
 * for raspicam
 * echo "bcm2835-v4l2" >> /etc/modules
 * reboot
 * ls /dev/video*
 *
 */


#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>


#define PATH4CAPTURE "/dev/video0"
#define PATH4MP4FILE "./video.mp4"


int main(int argc, char **argv)
{
	char *dev, default_dev[] = "/dev/video0";
	int t;
	double w, h, f;
	std::string file_name;
	cv::VideoCapture cap;
	cv::Mat img;


	if(argc == 1) dev = default_dev;
	else dev = argv[1];


	cap = cv::VideoCapture(dev);
	if(!cap.isOpened())
	{
		std::cout << "Do not open " << dev << std::endl;
		return -1;
	}

	w = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	h = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	f = cap.get(cv::CAP_PROP_FPS);
	t = cap.get(cv::CAP_PROP_FORMAT);
	std::cout << "w=" << w << ", h=" << h << ", fps=" << f << ", FORMAT=" << t << std::endl;

	cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
	cap.set(cv::CAP_PROP_FPS, 30);
	cap.set(cv::CAP_PROP_FORMAT, 16);


	for(;;)
	{
		cap >> img;

		cv::imshow("camera  ( q : quit,  s : shutter )", img);

		int key = cv::waitKey(1);
		if(key == 'q') break;
		else if(key == 's')
		{
			std::cout << "What your name ? > "; std::cin >> file_name;
			file_name += ".png";
			cv::imwrite(file_name, img);
		}
	}
	
	cv::destroyAllWindows();
	cap.release();

	return 0;
}
