/*
 *  2023.5.28
 *  webcam.cpp
 *  ver 1.8
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

/*
 * for raspicam
 * echo "bcm2835-v4l2" >> /etc/modules
 * reboot
 * ls /dev/video*
 *
 * for openCV 4.5
 */

// g++ -o webcam webcam.cpp `pkg-config --cflags --libs opencv4 `

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

//using namespace cv;

int main(int argc, char **argv)
{
	int t, fourcc;
	double w, h, f;
	cv::CascadeClassifier cascade;
	cv::Mat img;
	cv::Size wh;
	std::vector<cv::Rect> faces;
	cv::Rect face;
	cv::VideoWriter writer;
	std::string filepath = "video.mp4";

	cv::VideoCapture cap(0);
	if(!cap.isOpened()) return -1;

	w = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	h = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	f = cap.get(cv::CAP_PROP_FPS);
	t = cap.get(cv::CAP_PROP_FORMAT);
	std::cout << "w=" << w << ",h=" << h << ",fps=" << f << std::endl;
	std::cout << "FORMAT=" << t << std::endl;
/*
	cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
	cap.set(cv::CAP_PROP_FPS, 30);
	cap.set(cv::CAP_PROP_FORMAT, 2);
*/

	cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml");
//	cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");

	fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
	wh = cv::Size((int)w, (int)h);
	writer.open(filepath, fourcc, f, wh);
	if(!writer.isOpened()) return -1;


//	cv::namedWindow("camera", cv::WINDOW_AUTOSIZE);
	for(;;)
	{
		cap >> img;

		cascade.detectMultiScale(img, faces, 1.1, 3, 0, cv::Size(50, 50));
		for(int i=0; i<faces.size(); i++) cv::rectangle(img, cv::Point(faces[i].x, faces[i].y), cv::Point(faces[i].x+faces[i].width, faces[i].y+faces[i].height), cv::Scalar(0,0,255), 3);

		cv::imshow("camera", img);
		
		writer << img;

//		if(cv::waitKey(30) >= 0) break;
		const int key = cv::waitKey(1);
		if(key == 'q') break; // 113
	}
	cv::destroyAllWindows();

	return 0;
}
