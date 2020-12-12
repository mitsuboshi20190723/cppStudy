/*
 *  2020.12.12
 *  fd.cpp
 *  ver 0.2
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>
#include <dlib/image_io.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing/frontal_face_detector.h>
//#include <dlib/image_processing/render_face_detections.h>
//#include <dlib/image_processing.h>


using namespace dlib;


int main(int argc, char** argv)
{
	frontal_face_detector detector = get_frontal_face_detector();
	array2d<unsigned char> img;

	load_image(img, argv[1]);
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