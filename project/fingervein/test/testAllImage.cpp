//
// Created by user on 2020/6/24.
//

#include "testAllImage.h"

void testAllImage::run() {
    DetectFeature *detectFeature = new DetectFeature();

    for (int i = 0; i < dataBase.size(); ++i) {
        for (int j = 0; j < input.size(); ++j) {
            detectFeature->compare(input[j], dataBase[i], "surf");
            if (detectFeature->good_matches.size() > 15) {
                cout << detectFeature->good_matches.size() << "  ";
                cout << input[j] << " " << dataBase[i] << endl;
            }
//            detectFeature->showResult();
            detectFeature->clear();
        }
        cout << endl;
    }
}

void testAllImage::setDataBase(const String &path) {
    IO *io = new IO();
    io->getFiles(path, this->dataBase, 1, 0, y1);
    delete io;
}

void testAllImage::setInput(const String &inputPath) {
    IO *io = new IO();
    io->getFiles(inputPath, this->input, 1, 0, y2);
    delete io;
}

float testAllImage::getPassPrecent() {
    return this->result;
}

testAllImage::testAllImage() {}

testAllImage::~testAllImage() {

}

void testAllImage::getROC() {
    DetectFeature *detectFeature = new DetectFeature();
    vector<int> intraclass;
    vector<int> interclass;

    int total_complete = 0;
    for (int i = 0; i < dataBase.size(); ++i) {
        cout << "test " << i << " :" << total_complete << endl;
        for (int j = i + 1; j < input.size(); ++j) {
            detectFeature->compare(input[j], dataBase[i], "surf");
////            if (detectFeature->good_matches.size()>3) {
//            cout << detectFeature->good_matches.size() << "  ";
//            cout << input[j] << " " << dataBase[i] << endl;
////            }

            if (y1[i] == y2[j]) {
                intraclass.push_back(detectFeature->good_matches.size());
            } else {
                interclass.push_back(detectFeature->good_matches.size());
            }
            total_complete++;
//            detectFeature->showResult();
            detectFeature->clear();
        }
        cout << endl;
    }
    for (int thre = 1; thre < 100; thre++) {
        int fr = 0, fa = 0;
        float frr, far;
        cout << intraclass.size() << "\n";
        cout << interclass.size() << endl;
        for (int i = 0; i < intraclass.size(); i++) {
            if (intraclass[i] < thre) {
                fr++;
            }
        }
        for (int i = 0; i < interclass.size(); i++) {
            if (interclass[i] > thre) {
                fa++;
            }
        }
        frr = (float) fr / (float) intraclass.size();
        far = (float) fa / (float) interclass.size();
        cout << "threshold:" << thre << "\n";
        cout << "frr:" << frr << "," << "far:" << far << "\n" << endl;
    }
}
