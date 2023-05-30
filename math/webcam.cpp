/*
 *  2023.5.30
 *  webcam.cpp
 *  ver 2.0
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
#include <string>
#include <thread>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

//using namespace cv;

int main(int argc, char **argv)
{
	int t, fourcc, d;
	double w, h, f;
	std::chrono::system_clock::time_point s, e;
	cv::CascadeClassifier cascade;
	cv::Mat img;
	cv::Size wh;
	std::vector<cv::Rect> faces;
	cv::Rect face;
	cv::VideoWriter writer;
	std::string filepath = "video.mp4", str;

	cv::VideoCapture cap(0);
	if(!cap.isOpened()) return -1;

	w = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	h = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	f = cap.get(cv::CAP_PROP_FPS);
	t = cap.get(cv::CAP_PROP_FORMAT);
	std::cout << "w=" << w << ",h=" << h << ",fps=" << f << std::endl;
	std::cout << "FORMAT=" << t << std::endl;

	cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
	cap.set(cv::CAP_PROP_FPS, 30);
//	cap.set(cv::CAP_PROP_FORMAT, 16);


	cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml");
//	cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");

	fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
	wh = cv::Size((int)w, (int)h);
	writer.open(filepath, fourcc, f, wh);
	if(!writer.isOpened()) return -1;

	s = std::chrono::system_clock::now();

//	cv::namedWindow("camera", cv::WINDOW_AUTOSIZE);
	for(int cnt=0; ; cnt++)
	{
		cap >> img;
		writer << img;

		cascade.detectMultiScale(img, faces, 1.1, 3, 0, cv::Size(50, 50));
		for(int i=0; i<faces.size(); i++) cv::rectangle(img, cv::Point(faces[i].x, faces[i].y), cv::Point(faces[i].x+faces[i].width, faces[i].y+faces[i].height), cv::Scalar(0,0,255), 3);

		str = "frame counter : " + std::to_string(cnt);
		cv::putText(img, str, cv::Point(10,22), 1, 1.0, cv::Scalar(0,255,0));
		e = std::chrono::system_clock::now();
		d = std::chrono::duration_cast<std::chrono::microseconds>(e-s).count();
		str = "passed " + std::to_string((float)d/1000000) + " seconds";
		cv::putText(img, str, cv::Point(330,22), 1, 1.0, cv::Scalar(255,255,255));

		cv::imshow("webcamera (q : quit)", img);

//		if(cv::waitKey(30) >= 0) break;
		const int key = cv::waitKey(1);
		if(key == 'q') break; // 113
		
//		std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000/f)));
	}
	cv::destroyAllWindows();
	writer.release();
	cap.release();

	return 0;
}
