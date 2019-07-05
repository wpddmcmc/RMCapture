#pragma once
#include "opencv2/core/core.hpp"
#include <string>

using namespace cv;

class Settings{
public:
    Settings(const std::string & filename)
	{
        FileStorage setting_fs(filename, FileStorage::READ);
        read(setting_fs);
        setting_fs.release();
    }
    void read(const FileStorage& fs) {
        fs["debug_mode"] >> debug_mode;
        fs["video_name"] >> video_name;
    }
public:
    int debug_mode;
    std::string video_name;
};