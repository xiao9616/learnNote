#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace std;
using namespace cv;
void fileStorage(){
    FileStorage fs("test.yml", FileStorage::WRITE);
    fs << "frameCount" << 5;
    time_t rawtime;
    time(&rawtime);
    fs << "calibrationDate" << asctime(localtime(&rawtime));
    Mat cameraMatrix=(
            Mat_<double>(3,3)<<100,20,23,56,546,568,56,546,568
            );
    Mat distMatrix=(
            Mat_<double>(3,3)<<100,20,23,56,546,568,56,546,568
            );
    fs<<"cameraMatrix"<<cameraMatrix;
    fs<<"distMatrix"<<distMatrix;
    fs << "features" << "[";
    for (int i = 0; i < 3; ++i) {
        int x = rand() % 640;
        int y = rand() % 480;
        fs << "{:" << "x" << x << "y" << y << "}";

    }
    fs << "]";
    fs.release();
    return;
}
void fileRead(){
    FileStorage fs("test.yml", FileStorage::READ);
    int frameCount=(int)fs["frameCount"];
    std::string date;
    fs["calibrationDate"] >> date;
    cout << frameCount << date;
    Mat data;
    fs["distMatrix"]>>data;
    cout << data << endl;

}
int main() {
    fileStorage();
    fileRead();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}