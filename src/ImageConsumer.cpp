#include "ImageConsumer.hpp"
#include "RMVideoCapture.hpp"

#define VIDEO_WIDTH  640
#define VIDEO_HEIGHT 480
#define BUFFER_SIZE 1

#define USE_CAMERA

volatile unsigned int prdIdx = 0;		// index of reading image
volatile unsigned int csmIdx = 0;		// index of processing image

int exposure_time = 20;
#define WINDOW_NAME "Exposure Time Setting" 

struct ImageData {
	Mat img;             // data come from camera
	unsigned int frame;  // speed of img
};

ImageData capturedata[BUFFER_SIZE];   // Buffer of capture

void ImageConsumer::ImageReader() 
{ 									
	Settings & setting = *_settings;
	string video_name = "../video/";

	#ifndef USE_CAMERA
	//read video file
	video_name+=setting.video_name;
	VideoCapture cap(video_name);
	if (!cap.isOpened())
   	{
        cout<<"Can't Open video chassis"<<endl;
        return;
	}
	#else
	RMVideoCapture cap("/dev/video0", 3); 
	cap.setVideoFormat(VIDEO_WIDTH, VIDEO_HEIGHT, 1);
	cap.startStream();
	cap.setVideoFPS(60);
	cap.info();
	#endif

	while (true) {
		#ifdef USE_CAMERA
		cap.setExposureTime(false,exposure_time*25);
		while (prdIdx - csmIdx >= BUFFER_SIZE);
		cap >> capturedata[prdIdx % BUFFER_SIZE].img;
		capturedata[prdIdx % BUFFER_SIZE].frame = cap.getFrameCount();
		#else
		 while(prdIdx - csmIdx >= BUFFER_SIZE);
		cap >> capturedata[prdIdx % BUFFER_SIZE].img;
		capturedata[prdIdx % BUFFER_SIZE].frame++;
		#endif
		++prdIdx;
	}
}

void ImageConsumer::ImageProcesser() {

	Mat frame;
	double t=0, fps;
	char fps_display[10];

    while(true){
		t = (double) getTickCount();
		
		namedWindow(WINDOW_NAME);
		createTrackbar("Exposure Time", WINDOW_NAME, &exposure_time, 50);

		while (prdIdx - csmIdx == 0);
		capturedata[csmIdx % BUFFER_SIZE].img.copyTo(frame);
		++csmIdx;

		try {
			t = ((double)getTickCount() - t) / getTickFrequency();
			fps = 1.0 / t;
			sprintf(fps_display,"FPS:%.2f",fps);
			putText(frame,fps_display,Point(15,25),CV_FONT_HERSHEY_SIMPLEX , 1, Scalar(128, 255, 128), 1);
			imshow("frame", frame);
            waitKey(30);
		}
		catch (cv::Exception e) {
			std::cout<<"error"<<std::endl;
		}			
    }
}


