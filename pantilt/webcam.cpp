/*
 *  2021.1.30
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


#include <opencv2/highgui.hpp>

using namespace cv;

int main(int argc, char **argv)
{
	VideoCapture cap(0);
	if(!cap.isOpened()) return -1;

	Mat frame;
	namedWindow("camera", WINDOW_AUTOSIZE);
	for(;;)
	{
		cap >> frame;
		imshow("camera", frame);
		if(waitKey(30) >= 0) break;
	}
	return 0;
}
