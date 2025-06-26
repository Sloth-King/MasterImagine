#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

#include <GL/glut.h>

#include "Eigen/Dense"
#include "happly.h"

class Mesh
{
private:
    // Local
    std::vector<Eigen::Vector3f> vertices_;
    std::vector<Eigen::Vector3f> normals_;
    std::vector<std::array<unsigned int, 3>> triangles_;

    // Global
    Eigen::Affine3f transform_;
    std::vector<Eigen::Vector3f> global_vertices_;
    std::vector<Eigen::Vector3f> global_normals_;

    // Draw
    bool canDraw_;
    Eigen::Vector3f meshColor_ = Eigen::Vector3f(0.8f, 0.8f, 1.0f);

public:
    // Constructor / Clone
    Mesh();
    Mesh clone() const;

    // Imports / Exports
    void loadFromPLY(const char *filename);
    void saveToPLY(const char *filename);

    // Draw
    void setMeshColor(const Eigen::Vector3f &color);
    void draw(bool displayNormals) const;

    // Transformations
    void setPosition(const Eigen::Vector3f &position);
    void setRotation(float angle, const Eigen::Vector3f &axis);
    void setScale(const Eigen::Vector3f &scale);
    void setTransform(const Eigen::Affine3f &transform);
    void translate(const Eigen::Vector3f &translation);
    void rotate(float angle, const Eigen::Vector3f &axis);

    void computeGlobalMeshTransform();
    void computeNormals();

    //getters
    int getVertexSize(){
        return vertices_.size();
    }

    std::vector<Eigen::Vector3f> getVertices(){
        return vertices_;
    }

    //setters
    void setVertices(std::vector<Eigen::Vector3f> &new_vertices){
        vertices_ = new_vertices;
    }
};



#endif // MESH_H