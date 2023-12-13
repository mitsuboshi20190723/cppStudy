/*
 *  2023.12.14
 *  face_detect.cpp
 *  ver.0.9
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


// g++ -o FACE_DETECT face_detect.cpp `pkg-config --cflags --libs opencv4`  -ldlib -llapack -lblas  -lpthread -lwebp  -lX11 -ljpeg -lpng -lgif


#include <iostream>
#include <opencv2/opencv.hpp>
#include <dlib/image_io.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing/frontal_face_detector.h>
//#include <dlib/image_processing/render_face_detections.h>
//#include <dlib/image_processing.h>




int main(int argc, char** argv)
{

	cv::VideoCapture capture(0);
	if(!capture.isOpened())
	{
		printf("Do not open camera.\n");
		return -1;
	}



	if(argv[1] == NULL)
	{
		cv::Mat frame;
		char photo[] = "img.png";
	
		while(capture.read(frame))
		{
			cv::imshow("camera  ( q : quit,  s : shutter )", frame);
			const int key = cv::waitKey(1);
			if(key == 'q') break;
			else if(key == 's') cv::imwrite(photo, frame);
		}

		cv::destroyAllWindows();
	}
	else
	{
		char *imgfile;
		imgfile = argv[1];

		dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
		dlib::array2d<unsigned char> img;

		dlib::load_image(img, imgfile);
		dlib::pyramid_up(img);

		std::vector<dlib::rectangle> dets = detector(img);
		std::vector<dlib::rectangle>::iterator it;

		for(it = dets.begin(); it != dets.end(); it++) std::cout << *it << std::endl;

		dlib::image_window win;
		win.clear_overlay();
		win.set_image(img);
		win.add_overlay(dets, dlib::rgb_pixel(255,0,0));
		std::cin.get();
// win close

	}

	capture.release();

	return 0;
}
