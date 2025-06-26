#include "Eigen/Dense"
#include "handleGlut.h"
#include "mesh.h"
#include "metrics.h"

float RMSE(Mesh mesh1 , Mesh mesh2){
    float sum = 0.0;
    int n = mesh1.getVertexSize();
    std::vector<Eigen::Vector3f> vertices1 = mesh1.getVertices();
    std::vector<Eigen::Vector3f> vertices2 = mesh2.getVertices();

    for (int i = 0; i < n; i++) {
        Eigen::Vector3f diff = vertices1[i] - vertices2[i];
        sum += diff.squaredNorm();
    }

    float rmse = std::sqrt(sum / vertices1.size());
    return rmse;
}

float hausdorff(Mesh mesh1 , Mesh mesh2){

    int n = mesh1.getVertexSize();
    std::vector<Eigen::Vector3f> vertices1 = mesh1.getVertices();
    std::vector<Eigen::Vector3f> vertices2 = mesh2.getVertices(); 

    float sid1 = 0.0;
    float sid2 = 0.0;

    for (int i = 0; i < n; i++) {
        float minDist1 = std::numeric_limits<float>::max();
        for (int j = 0; j < n; j++) {
            float dist = (vertices1[i] - vertices2[j]).norm();
            if (dist < minDist1) {
                minDist1 = dist;
            }
        }
        if (minDist1 > sid1) {
            sid1 = minDist1;
        }
    }

    for (int i = 0; i < n; i++) {
        float minDist2 = std::numeric_limits<float>::max();
        for (int j = 0; j < n; j++) {
            float dist = (vertices2[i] - vertices1[j]).norm();
            if (dist < minDist2) {
                minDist2 = dist;
            }
        }
        if (minDist2 > sid2) {
            sid2 = minDist2;
        }
    }

    float dh = std::max(sid1 , sid2);
    return dh;

}
