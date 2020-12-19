/*
 *  2020.12.12
 *  fd.cpp
 *  ver 0.4
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <dlib/image_io.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing/frontal_face_detector.h>
//#include <dlib/image_processing/render_face_detections.h>
//#include <dlib/image_processing.h>

char photo[] = "img.png";

using namespace dlib;


int main(int argc, char** argv)
{
	frontal_face_detector detector = get_frontal_face_detector();
	array2d<unsigned char> img;
	char *imgfile;

	if(argv[1] == NULL)
	{
		cv::VideoCapture capture(0);
		if(!capture.isOpened())
		{
			printf("do not open camera\n");
			return -1;
		}
		cv::Mat frame;
		while(capture.read(frame))
		{
			cv::imshow("win", frame);
			const int key = cv::waitKey(1);
			if(key == 'q') break;
			else if(key == 's') cv::imwrite(photo, frame);
		}
		cv::destroyAllWindows();
		/*cv::VideoCapture::release();*/
		imgfile = photo;
	}
	else if(strcmp(argv[1], "realsense") == 0)
	{
		cv::VideoCapture capture(cv::VideoCaptureAPIs::CAP_INTELPERC);
		if(!capture.isOpened())
		{
			printf("do not open realsense\n");
			return -1;
		}
printf("open realsense\n");
		while(true)
		{
			capture.grab();
			cv::Mat color_frame;
			capture.retrieve(color_frame, cv::CAP_INTELPERC_IMAGE);
			cv::imshow("Color", color_frame);
			const int32_t key = cv::waitKey(33);
			if(key == 'q') break;
		}
printf("close realsense\n");
		cv::destroyAllWindows();
		return 0;
	}
	else
	{
		imgfile = argv[1];
	}

	load_image(img, imgfile);
	pyramid_up(img);

	std::vector<rectangle> dets = detector(img);
	std::vector<rectangle>::iterator it;
	for(it = dets.begin(); it != dets.end(); it++) std::cout << *it << std::endl;

	image_window win;
	win.clear_overlay();
	win.set_image(img);
	win.add_overlay(dets, rgb_pixel(255,0,0));
	std::cin.get();

}