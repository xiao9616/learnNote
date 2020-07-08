//
// Created by user on 2020/6/24.
//
#include "IO.h"

void IO::getFiles(std::string path, std::vector<std::string> &files, int recursive, int includeDir) {
    DIR *dir;
    struct dirent *ptr;

    if ((dir = opendir(path.c_str())) == NULL) {
        perror("Open dir error...");
        exit(1);
    }

    /*
     * 文件(8)、目录(4)、链接文件(10)
     */

    while ((ptr = readdir(dir)) != NULL) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;
        else if (ptr->d_type == 8)
            files.push_back(path + ptr->d_name);
        else if (ptr->d_type == 10)
            continue;
        else if (ptr->d_type == 4) {
            if (includeDir) {
                files.push_back(path + ptr->d_name);
            }
            if (recursive) {
                getFiles(path + ptr->d_name + "/", files, recursive, includeDir);
            }

        }
    }
    closedir(dir);
}

void IO::getFiles(std::string path, std::vector<std::string> &files, int recursive, int includeDir,std::vector<int> &label) {
    DIR *dir;
    struct dirent *ptr;


    if ((dir = opendir(path.c_str())) == NULL) {
        perror("Open dir error...");
        exit(1);
    }

    /*
     * 文件(8)、目录(4)、链接文件(10)
     */

    while ((ptr = readdir(dir)) != NULL) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;
        else if (ptr->d_type == 8) {
            files.push_back(path + ptr->d_name);
            label.push_back(this->y);
        }
        else if (ptr->d_type == 10)
            continue;
        else if (ptr->d_type == 4) {
            this->y++;
            if (includeDir) {
                files.push_back(path + ptr->d_name);

            }
            if (recursive) {
                getFiles(path + ptr->d_name + "/", files, recursive, includeDir, label);
            }

        }

    }
    closedir(dir);

}

IO::IO() {}

IO::~IO() {

}
