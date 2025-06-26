#ifndef QUANT_H
#define QUANT_H

#include "mesh.h"
#include "BoundingBox.h"


BoundingBox generateBB(Mesh mesh);
void quantification(Mesh &in_mesh , Mesh &out_mesh , int qp , Eigen::Vector3f &bbmin , float &range);
void dequantification(Mesh &out_mesh , int qp , Eigen::Vector3f bbmin , float range);

#endif
