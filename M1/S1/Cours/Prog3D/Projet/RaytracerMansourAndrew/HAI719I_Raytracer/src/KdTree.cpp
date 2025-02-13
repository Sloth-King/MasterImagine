#include "KdTree.h"
#include <iostream>
#include <cfloat>
#include <vector>
#include "Triangle.h"
#include "Vec3.h"
#include "BoundingBox.h"
#include <algorithm>


bool compareTriangles(const Triangle &a, const Triangle &b, int dimensionSplit) {
    return a.centroid()[dimensionSplit] < b.centroid()[dimensionSplit];
}

//merci tom :D
bool intersectAABB(const BoundingBox& boundingBox , const Vec3& rayOrigin, const Vec3& rayDir) {
    Vec3 aa1 = boundingBox.min - rayOrigin;
    Vec3 aa2 = boundingBox.max - rayOrigin;
    Vec3 facs(1.0 / rayDir[0], 1.0 / rayDir[1], 1.0 / rayDir[2]);

    float tx1 = aa1[0] * facs[0];
    float tx2 = aa2[0] * facs[0];
    float tmin = std::min(tx1, tx2);
    float tmax = std::max(tx1, tx2);

    float ty1 = aa1[1] * facs[1];
    float ty2 = aa2[1] * facs[1];
    tmin = std::max(tmin, std::min(ty1, ty2));
    tmax = std::min(tmax, std::max(ty1, ty2));

    float tz1 = aa1[2] * facs[2];
    float tz2 = aa2[2] * facs[2];
    tmin = std::max(tmin, std::min(tz1, tz2));
    tmax = std::min(tmax, std::max(tz1, tz2));

    return tmax >= tmin;
}

void KdTreeNode::build(const std::vector<Triangle> listOfTriangles , int depth){
    //scene bounding box (big box)
    for(const Triangle &t : listOfTriangles){
        boundingBox.expand(t.get_mc(0));
        boundingBox.expand(t.get_mc(1));
        boundingBox.expand(t.get_mc(2));
    }

    //stopping condition (depth or number of triangles)
    if(listOfTriangles.size() <= maxTriangles || boundingBox.size().length() < minSize){
        isLeaf = true;
        triangles = listOfTriangles;
        return;
    }

    //split axis (TODO maybe choose most efficient axis ?) (for now cycle x y z)
    dimensionSplit = depth % 3;

    //split in the middle of the box
    //can remove, maybe fun to compare speeds for report
    // splitPoint = boundingBox.min + (boundingBox.max - boundingBox.min) / 2;
    // Vec3 median = splitPoint;
    // splitDistance = median[dimensionSplit]; 

    //spllit par mediane
    std::vector<Triangle> sortedTriangles = listOfTriangles;
    std::sort(sortedTriangles.begin(), sortedTriangles.end(), [this](const Triangle &a, const Triangle &b) {
        return compareTriangles(a, b, dimensionSplit);
    });

    size_t medianIndex = sortedTriangles.size() / 2;    
    splitDistance = sortedTriangles[medianIndex].centroid()[dimensionSplit];

    //add triangles to l or r
    std::vector<Triangle> leftTriangles;
    std::vector<Triangle> rightTriangles;   

    for (const Triangle& t : listOfTriangles) {
        bool left = false, right = false;
        if (t.centroid()[dimensionSplit] <= splitDistance) left = true;
        else right = true;
        if (left) leftTriangles.push_back(t);
        if (right && !left) rightTriangles.push_back(t); //stop dupes
    }
    if (leftTriangles.size() == listOfTriangles.size() || rightTriangles.size() == listOfTriangles.size() || leftTriangles.size() == 0 || rightTriangles.size() == 0) {
        isLeaf = true;
        triangles = listOfTriangles;
        return;
    }

    //build left and right nodes
    left = new KdTreeNode();
    right = new KdTreeNode();

    //update boxes fire emoji
    left->boundingBox = boundingBox;
    right->boundingBox = boundingBox;

    left->boundingBox.max[dimensionSplit] = splitDistance;
    right->boundingBox.min[dimensionSplit] = splitDistance;

    left->build(leftTriangles, depth + 1);
    right->build(rightTriangles, depth + 1);

    isBuilt = true;
}

RayTriangleIntersection KdTreeNode::traverse(const Ray& ray) const {

    Vec3 rayDir = ray.direction();
    Vec3 origin = ray.origin();

    //stop condition
    if (isLeaf) {
        return intersect(triangles, ray);
    }

    bool leftHit = intersectAABB(left->boundingBox, origin , rayDir);
    bool rightHit = intersectAABB(right->boundingBox, origin , rayDir);

    if (leftHit && rightHit) {
        RayTriangleIntersection leftHitResult = left->traverse(ray);
        RayTriangleIntersection rightHitResult = right->traverse(ray);
        if (leftHitResult.intersectionExists && leftHitResult.t < rightHitResult.t) {
            return leftHitResult;
        }
        return rightHitResult;
    } else if (leftHit) {
        return left->traverse(ray);
    } else if (rightHit) {
        return right->traverse(ray);
    }

    RayTriangleIntersection nuffinInnit;
    nuffinInnit.intersectionExists = false;
    return nuffinInnit;

}

RayTriangleIntersection KdTreeNode::intersect(const std::vector<Triangle>& listOfTriangles , const Ray& ray) const {
    RayTriangleIntersection result;
    result.intersectionExists = false;
    result.t = FLT_MAX;

    for(const Triangle &t : listOfTriangles){
        RayTriangleIntersection hit = t.getIntersection(ray);
        if(hit.intersectionExists && hit.t < result.t){
            result = hit;
        }
    }

    return result;
}