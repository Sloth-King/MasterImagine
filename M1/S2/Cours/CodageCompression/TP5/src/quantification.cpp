#include "Eigen/Dense"
#include "handleGlut.h"
#include "mesh.h"
#include "metrics.h"
#include "quantification.h"
#include <iostream>
#include "BoundingBox.h"

BoundingBox generateBB(Mesh mesh) {
    BoundingBox bb;
    std::vector<Eigen::Vector3f> vertices = mesh.getVertices();
    for (const auto& vertex : vertices) {
        bb.expand(vertex);
    }
    
    return bb;
}

void quantification(Mesh &in_mesh , Mesh &out_mesh , int qp , Eigen::Vector3f &bbmin , float &range){
    BoundingBox bb = generateBB(in_mesh);

    int n = in_mesh.getVertexSize();

    std::vector<Eigen::Vector3f> v = in_mesh.getVertices();
    std::vector<Eigen::Vector3f> vp = out_mesh.getVertices();


    range = std::max(std::max(bb.max[0] - bb.min[0], bb.max[1] - bb.min[1]), bb.max[2] - bb.min[2]);
    bbmin = bb.min;

    for(int i = 0 ; i < n ; i++){
        vp[i] = (v[i] - bbmin) * (pow(2,qp) - 1)/range;
        vp[i][0] = (int)vp[i][0];
        vp[i][1] = (int)vp[i][1];
        vp[i][2] = (int)vp[i][2];
    } 

    out_mesh.setVertices(vp);
    out_mesh.computeNormals();
    out_mesh.computeGlobalMeshTransform();

}

void dequantification(Mesh &out_mesh , int qp , Eigen::Vector3f bbmin , float range){

    Mesh in_mesh = out_mesh.clone();
    int n = in_mesh.getVertexSize();

    std::vector<Eigen::Vector3f> v = in_mesh.getVertices();
    std::vector<Eigen::Vector3f> vp = out_mesh.getVertices();

    for(int i = 0 ; i < n ; i++){
        vp[i] = v[i]*(range/(pow(2,qp)-1)) + bbmin;
    } 

    out_mesh.setVertices(vp);
    out_mesh.computeNormals();
    out_mesh.computeGlobalMeshTransform();
}

