/*
 *  2023.12.10
 *  webcam.cpp
 *  ver.2.5
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

// g++ -o WEBCAM webcam.cpp `pkg-config --cflags --libs opencv4`
// WEBCAM /dev/video0 /usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml ./video.mp4

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


#define PATH4CAPTURE "/dev/video0"
#define PATH4CASCADE "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml"
#define PATH4MP4FILE "./video.mp4"


int main(int argc, char **argv)
{
	char stat, default_dev[] = "/dev/video0";
	int d, cnt;
	std::chrono::system_clock::time_point s, e;

	char *path4capture;
	int t;
	double w, h, f;
	cv::VideoCapture cap;
	cv::Mat img;

	char *path4cascade;
	cv::CascadeClassifier cascade;
	std::vector<cv::Rect> faces;
	cv::Point left_up, right_down;
	std::string str;

	char *path4mp4file;
	int fourcc;
	cv::VideoWriter writer;
	cv::Size wh;


	if(argc == 1)
	{
		std::cout << "For example command." << std::endl;
		std::cout << argv[0] << " " << PATH4CAPTURE
		       	             << " " << PATH4CASCADE
				     << " " << PATH4MP4FILE << std::endl;
		return 0;
	}
	stat = 0;
	for(cnt=1; cnt < argc; cnt++)
	{
		if(std::string(argv[cnt]).find("/dev") != std::string::npos)
		{
			stat += 1;
			path4capture = argv[cnt];
		}
		else if(std::string(argv[cnt]).find(".xml") != std::string::npos)
		{
			stat += 2;
			path4cascade = argv[cnt];
		}
		else if(std::string(argv[cnt]).find(".mp4") != std::string::npos)
		{
			stat += 4;
			path4mp4file = argv[cnt];
		}
	}


	if(!(stat & 1)) path4capture = default_dev;
	cap = cv::VideoCapture(path4capture);
	if(!cap.isOpened()) return -1;
	std::cout << "Camera device : " << path4capture << std::endl;

	w = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	h = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	f = cap.get(cv::CAP_PROP_FPS);
	t = cap.get(cv::CAP_PROP_FORMAT);
	std::cout << "w=" << w << ", h=" << h << ", fps=" << f << ", FORMAT=" << t << std::endl;

	cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
	cap.set(cv::CAP_PROP_FPS, 30);
	cap.set(cv::CAP_PROP_FORMAT, 16);


	if(stat & 2) if(!cascade.load(path4cascade)) return -1;
	std::cout << "Found Cascade : " << path4cascade << std::endl;


	if(stat & 4)
	{
		fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
		wh = cv::Size((int)w, (int)h);
		writer.open(PATH4MP4FILE, fourcc, f, wh);
		if(!writer.isOpened()) return -1;
	}
	std::cout << "Open REC file : " << path4mp4file << std::endl;


	cv::namedWindow("webcamera  ( q : quit )", cv::WINDOW_AUTOSIZE);

	s = std::chrono::system_clock::now();
	cnt = 0;
	for(;;)
	{
		cap >> img;

		if(!(stat & 1))
		{
			e = std::chrono::system_clock::now();
			d = std::chrono::duration_cast<std::chrono::microseconds>(e-s).count();
			str = "passed " + std::to_string((float)d/1000000) + " seconds";
			cv::putText(img, str, cv::Point(330,22), 1, 1.0, cv::Scalar(255,255,255));
			str = "frame counter : " + std::to_string(cnt);
			cv::putText(img, str, cv::Point(10,22), 1, 1.0, cv::Scalar(0,255,0));
			cnt++;
		}


		if(stat & 2)
		{
			cascade.detectMultiScale(img, faces, 1.1, 3, 0, cv::Size(50, 50));
			for(int i=0; i<faces.size(); i++)
			{
				left_up = cv::Point(faces[i].x, faces[i].y);
				right_down = cv::Point(faces[i].x+faces[i].width, faces[i].y+faces[i].height);
				cv::rectangle(img, left_up, right_down, cv::Scalar(0,0,255), 3);
			}
		}


		if(stat & 4)
		{
			writer << img;
			if(stat == 4) std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000/f)));
		}


		cv::imshow("webcamera  ( q : quit )", img);
		if(cv::waitKey(1) == 'q') break; // 113(0x71)  if any key  (cv::waitKey(1) >= 0)
	}
	
	cv::destroyAllWindows();
	if(stat && 4) writer.release();
	cap.release();

	return 0;
}
