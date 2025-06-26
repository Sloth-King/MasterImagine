#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Eigen/Dense"
#include <iostream>
#include <fstream>
#include <cfloat>
#include "BoundingBox.h"

class BoundingBox{
    public : 
        Eigen::Vector3f min;
        Eigen::Vector3f max;

        BoundingBox() : min(Eigen::Vector3f(FLT_MAX, FLT_MAX, FLT_MAX)), max(Eigen::Vector3f(-FLT_MAX, -FLT_MAX, -FLT_MAX)) {}

        void expand(const Eigen::Vector3f &point){
            min[0] = std::min(min[0], point[0]);
            min[1] = std::min(min[1], point[1]);
            min[2] = std::min(min[2], point[2]);
            max[0] = std::max(max[0], point[0]);
            max[1] = std::max(max[1], point[1]);
            max[2] = std::max(max[2], point[2]);   
        }

        void expand(const BoundingBox& box) {
            expand(box.min);
            expand(box.max);
        }

        Eigen::Vector3f size() const {
            return max - min;
        }
};

#endif