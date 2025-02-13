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
        float splitDistance; //distance from origin point along split axis
        Vec3 splitPoint; //point where the split axis intersects the plane
        bool isLeaf = false; //leaf = no boxes inside
        std::vector<Triangle> triangles; //triangles in the leaf
        BoundingBox boundingBox = BoundingBox(); //bounding box of the leaf

    public:
        int maxTriangles = 3; //supposed to be the most optimal
        float minSize = 0.001;
        bool isBuilt = false;

        void build(std::vector<Triangle> listOfTriangles , int depth);
        RayTriangleIntersection intersect(const std::vector<Triangle>& listOfTriangles , const Ray& ray) const;
        RayTriangleIntersection traverse(const Ray& ray) const;
};

#endif