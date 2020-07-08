#include "Common.h"

Mat extractVeinsFromCentres(Mat veinsCenters, Mat fingerRegion) {
    Size imageSize = veinsCenters.size();
    Mat veins = Mat::zeros(imageSize, veinsCenters.type());

    for (auto x = 2; x < imageSize.width - 2; x++) {
        for (auto y = 2; y < imageSize.height - 2; y++) {
            auto c1 = min(max(veinsCenters.at<DATA_TYPE>(y, x+1), veinsCenters.at<DATA_TYPE>(y, x+2)),
                          max(veinsCenters.at<DATA_TYPE>(y, x-1), veinsCenters.at<DATA_TYPE>(y, x-2)));
            auto c2 = min(max(veinsCenters.at<DATA_TYPE>(y+1, x), veinsCenters.at<DATA_TYPE>(y+2, x)),
                          max(veinsCenters.at<DATA_TYPE>(y-1, x), veinsCenters.at<DATA_TYPE>(y-2, x)));
            auto c3 = min(max(veinsCenters.at<DATA_TYPE>(y-1, x-1), veinsCenters.at<DATA_TYPE>(y-2, x-2)),
                          max(veinsCenters.at<DATA_TYPE>(y+1, x+1), veinsCenters.at<DATA_TYPE>(y+2, x+2)));
            auto c4 = min(max(veinsCenters.at<DATA_TYPE>(y+1, x-1), veinsCenters.at<DATA_TYPE>(y+2, x-2)),
                          max(veinsCenters.at<DATA_TYPE>(y-1, x+1), veinsCenters.at<DATA_TYPE>(y-2, x+2)));

            veins.at<DATA_TYPE>(y, x) = max(max(c1, c2), max(c3, c4));
        }
    }

    for (auto x = 0; x < imageSize.width; x++) {
        for (auto y = 0; y < imageSize.height; y++) {
            if (abs(fingerRegion.at<DATA_TYPE>(y, x)) == 0)
                veins.at<DATA_TYPE>(y, x) = DATA_TYPE(0);
        }
    }

    return veins;
}