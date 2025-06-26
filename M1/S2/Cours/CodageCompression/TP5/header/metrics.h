#ifndef METRICS_H
#define METRICS_H

#include "Eigen/Dense"
#include "handleGlut.h"
#include "mesh.h"

float RMSE(Mesh mesh1 , Mesh mesh2);
float hausdorff(Mesh mesh1 , Mesh mesh2);

#endif