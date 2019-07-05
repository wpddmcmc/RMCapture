#pragma once
#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>
#include "setting.hpp"

using namespace cv;
using namespace std;

class ImageConsumer{
public:
    ImageConsumer(Settings *settings)
    {
        _settings = settings;
    }
    ImageConsumer(){ }
    void ImageReader();
    void ImageProcesser();
    public:
        Settings * _settings;
};