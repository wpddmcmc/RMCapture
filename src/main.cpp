#include <thread> 
#include <unistd.h>
#include <iostream>
#include "ImageConsumer.hpp" 

int main(int argc, char * argv[])
{
	char *config_file_name = "../param/param_config.xml";
    FileStorage fs(config_file_name, FileStorage::READ);    //initialization
    if (!fs.isOpened())     //open xml config file
    {
        std::cout << "Could not open the configuration file: param_config.xml " << std::endl;
        return -1;
    }
    Settings setting(config_file_name);

	ImageConsumer image_cons_prod(&setting);
	
	ImageConsumer image_consumer;
	std::thread task0(&ImageConsumer::ImageReader, image_consumer);  	// add image reading thread
	std::thread task1(&ImageConsumer::ImageProcesser, image_consumer);  // add image processing thread

	// thread joined
	task0.join();
    task1.join();
    
	return EXIT_SUCCESS;
}