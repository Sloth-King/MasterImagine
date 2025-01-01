#include "KdTree.h"
#include <iostream>
#include <cfloat>
#include <vector>
#include "Triangle.h"
#include "Vec3.h"
#include "BoundingBox.h"

void KdTreeNode::build(const std::vector<Triangle> listOfTriangles , int depth){
    std::cout << "Building tree of depth : "  << depth << std::endl;
    //scene bounding box (big box)
    for(const Triangle &t : listOfTriangles){
        boundingBox.expand(t.get_mc(0));
        boundingBox.expand(t.get_mc(1));
        boundingBox.expand(t.get_mc(2));
    }

    //stopping condition (depth or number of triangles)
    if(depth >= maxDepth || listOfTriangles.size() <= maxTriangles){
        isLeaf = true;
        triangles = listOfTriangles;
        return;
    }

    //split axis (TODO maybe choose most efficient axis ?) (for now cycle x y z)
    dimensionSplit = depth % 3;
    //split in the middle of the box
    splitPoint = boundingBox.min + (boundingBox.max - boundingBox.min) / 2;
    Vec3 median = splitPoint;

    splitDistance = median[dimensionSplit]; 

    //add triangles to l or r
    //FIXME : i think i can do better
    std::vector<Triangle> leftTriangles;
    std::vector<Triangle> rightTriangles;

    // bool left = false, right = false;
    // for (int i = 0; i < 3; ++i) {
    //     if (t.get_mc(i)[dimensionSplit] < splitDistance) left = true;
    //     if (t.get_mc(i)[dimensionSplit] >= splitDistance) right = true;
    // }
    // if (left) leftTriangles.push_back(t);
    // if (right) rightTriangles.push_back(t);

    for(const Triangle &t : listOfTriangles){
        bool left = false, right = false;
        for (int i = 0; i < 3; ++i) {
            if (t.get_mc(i)[dimensionSplit] < splitDistance) left = true;
            if (t.get_mc(i)[dimensionSplit] >= splitDistance) right = true;
        }
        if (left) leftTriangles.push_back(t);
        if (right) rightTriangles.push_back(t);
    }

    //build left and right nodes
    left = new KdTreeNode();
    right = new KdTreeNode();
    left->build(leftTriangles, depth + 1);
    right->build(rightTriangles, depth + 1);
}

RayTriangleIntersection KdTreeNode::traverse(const Ray& ray , float t_start , float t_end) const{
    //ending condition
    Vec3 rayDir = ray.direction();
    Vec3 origin = ray.origin();
    //rayDir.normalize();
    
    if(isLeaf){
        return intersect(triangles, origin, t_start, t_end);
    }
    //traverse left and right
    if(rayDir[dimensionSplit] == 0){
        return left->traverse(ray, t_start, t_end);
    }
    float t = (splitDistance - origin[dimensionSplit]) / rayDir[dimensionSplit];
    if(t <= t_start){
        //std::cout << "word might be bond on the left ?" << std::endl;
        return left->traverse(ray, t_start, t_end);
    }
    else if(t >= t_end){
        //std::cout << "word might be bond on the right ?" << std::endl;
        return right->traverse(ray, t_start, t_end);
    }
    else{
        RayTriangleIntersection hit = left->traverse(ray, t_start, t);
        if(hit.t <= t){
            return hit;
        }
        return right->traverse(ray, t, t_end);
    }
}

RayTriangleIntersection KdTreeNode::intersect(std::vector<Triangle> listOfTriangles , Vec3 origin , float t_start , float t_end) const {
    RayTriangleIntersection result;
    result.intersectionExists = false;
    result.t = FLT_MAX;

    for(const Triangle &t : listOfTriangles){
        RayTriangleIntersection hit = t.getIntersection(Ray(origin, t.get_mc(0) - origin));
        if(hit.intersectionExists && hit.t < result.t){
            result = hit;
        }
    }
    return result;
}