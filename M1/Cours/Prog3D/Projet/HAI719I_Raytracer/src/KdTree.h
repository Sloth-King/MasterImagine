#ifndef KDTREENODE_H
#define KDTREENODE_H

#include <iostream>
#include <cfloat>
#include <vector>
#include "Triangle.h"
#include "Vec3.h"
#include "BoundingBox.h"

class KdTreeNode{
    private:
        KdTreeNode *left; //child1
        KdTreeNode *right; //child2
        int dimensionSplit; //0 for x, 1 for y, 2 for z
        float splitDistance; //distance from origin point along split axis (idk what origin point is yet oops)
        Vec3 splitPoint; //point where the split axis intersects the plane
        bool isLeaf = false; //leaf = no boxes inside
        std::vector<Triangle> triangles; //triangles in the leaf
        BoundingBox boundingBox = BoundingBox(); //bounding box of the leaf

    public:
        //public in case i wanna change it later easily
        int maxTriangles = 10;
        int maxDepth = 15;

        void build(std::vector<Triangle> listOfTriangles , int depth);
        RayTriangleIntersection intersect(std::vector<Triangle> listOfTriangles , Vec3 origin , float t_start , float t_end) const;
        RayTriangleIntersection traverse(const Ray& ray , float t_start , float t_end) const;
};

#endif