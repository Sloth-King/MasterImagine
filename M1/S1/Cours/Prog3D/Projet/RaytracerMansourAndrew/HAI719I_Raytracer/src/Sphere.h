#ifndef Sphere_H
#define Sphere_H
#include "Vec3.h"
#include <vector>
#include "Mesh.h"
#include <cmath>

struct RaySphereIntersection{
    bool intersectionExists;
    float t;
    float theta,phi;
    Vec3 intersection;
    Vec3 secondintersection;
    Vec3 normal;
};

static
Vec3 SphericalCoordinatesToEuclidean( Vec3 ThetaPhiR ) {
    return ThetaPhiR[2] * Vec3( cos(ThetaPhiR[0]) * cos(ThetaPhiR[1]) , sin(ThetaPhiR[0]) * cos(ThetaPhiR[1]) , sin(ThetaPhiR[1]) );
}
static
Vec3 SphericalCoordinatesToEuclidean( float theta , float phi ) {
    return Vec3( cos(theta) * cos(phi) , sin(theta) * cos(phi) , sin(phi) );
}

static
Vec3 EuclideanCoordinatesToSpherical( Vec3 xyz ) {
    float R = xyz.length();
    float phi = asin( xyz[2] / R );
    float theta = atan2( xyz[1] , xyz[0] );
    return Vec3( theta , phi , R );
}



class Sphere : public Mesh {
public:
    Vec3 m_center;
    Vec3 start_center;
    Vec3 end_center;
    float m_radius;
    bool inMotion = false;

    Sphere() : Mesh() {}
    Sphere(Vec3 c , float r) : Mesh() , m_center(c) , m_radius(r) {}
    Sphere(Vec3 c1 , Vec3 c2 , float r) : Mesh() , m_center(c1), start_center(c1) , end_center(c2) , m_radius(r) {
        inMotion = true;
    }

    void build_arrays(){
        unsigned int nTheta = 20 , nPhi = 20;
        positions_array.resize(3 * nTheta * nPhi );
        normalsArray.resize(3 * nTheta * nPhi );
        uvs_array.resize(2 * nTheta * nPhi );
        for( unsigned int thetaIt = 0 ; thetaIt < nTheta ; ++thetaIt ) {
            float u = (float)(thetaIt) / (float)(nTheta-1);
            float theta = u * 2 * M_PI;
            for( unsigned int phiIt = 0 ; phiIt < nPhi ; ++phiIt ) {
                unsigned int vertexIndex = thetaIt + phiIt * nTheta;
                float v = (float)(phiIt) / (float)(nPhi-1);
                float phi = - M_PI/2.0 + v * M_PI;
                Vec3 xyz = SphericalCoordinatesToEuclidean( theta , phi );
                positions_array[ 3 * vertexIndex + 0 ] = m_center[0] + m_radius * xyz[0];
                positions_array[ 3 * vertexIndex + 1 ] = m_center[1] + m_radius * xyz[1];
                positions_array[ 3 * vertexIndex + 2 ] = m_center[2] + m_radius * xyz[2];
                normalsArray[ 3 * vertexIndex + 0 ] = xyz[0];
                normalsArray[ 3 * vertexIndex + 1 ] = xyz[1];
                normalsArray[ 3 * vertexIndex + 2 ] = xyz[2];
                uvs_array[ 2 * vertexIndex + 0 ] = u;
                uvs_array[ 2 * vertexIndex + 1 ] = v;
            }
        }
        triangles_array.clear();
        for( unsigned int thetaIt = 0 ; thetaIt < nTheta - 1 ; ++thetaIt ) {
            for( unsigned int phiIt = 0 ; phiIt < nPhi - 1 ; ++phiIt ) {
                unsigned int vertexuv = thetaIt + phiIt * nTheta;
                unsigned int vertexUv = thetaIt + 1 + phiIt * nTheta;
                unsigned int vertexuV = thetaIt + (phiIt+1) * nTheta;
                unsigned int vertexUV = thetaIt + 1 + (phiIt+1) * nTheta;
                triangles_array.push_back( vertexuv );
                triangles_array.push_back( vertexUv );
                triangles_array.push_back( vertexUV );
                triangles_array.push_back( vertexuv );
                triangles_array.push_back( vertexUV );
                triangles_array.push_back( vertexuV );
            }
        }
    }


    RaySphereIntersection intersect(const Ray &ray) const {
        RaySphereIntersection intersection;
        intersection.intersectionExists = false;
        Vec3 o = ray.origin();
        Vec3 d = ray.direction();
        float a = Vec3::dot(d,d);
        float b = Vec3::dot(d , (o - m_center)) * 2;
        float c = Vec3::dot((o-m_center),(o-m_center)) - pow(m_radius , 2);
        float determinant = pow(b,2) - (4 * a * c); 
        if(determinant < 0){
            intersection.intersectionExists = false;
            return intersection;
        }
        if(determinant > 0){
            intersection.intersectionExists = true;
            float x1 = (-b - sqrt(determinant))/ (2*a);
            float x2 = (-b + sqrt(determinant))/ (2*a);
        if (x1 > 0 && x2 > 0) {
            intersection.t = std::min(x1, x2);  
        } else if (x1 < 0 && x2 > 0) {
            intersection.t = x2;  
        } else if (x1 > 0 && x2 < 0) {
            intersection.t = x1;  
        } else {
            intersection.intersectionExists = false; 
            return intersection;
        }
  
        }
        intersection.intersection = o + d * intersection.t;
        Vec3 normals = (intersection.intersection - m_center);
        normals.normalize();
        intersection.normal = normals;


        return intersection;
    }    
    //TODO : code motion blur option
    //TODO TUAH : when done merge with the other one to make it optional
    RaySphereIntersection intersect2(const Ray &ray) const {
        RaySphereIntersection intersection;
        intersection.intersectionExists = false;
        Vec3 o = ray.origin();
        Vec3 d = ray.direction();

        //get current time and position
        float t = ray.time();
        Vec3 current_center = start_center + t * (end_center-start_center);

        //use the current center to check 
        float a = Vec3::dot(d,d);
        float b = Vec3::dot(d , (o - current_center)) * 2;
        float c = Vec3::dot((o-current_center),(o-current_center)) - pow(m_radius , 2);
        float determinant = pow(b,2) - (4 * a * c); 
        if(determinant < 0){
            intersection.intersectionExists = false;
            return intersection;
        }
        if(determinant > 0){
            intersection.intersectionExists = true;
            float x1 = (-b - sqrt(determinant))/ (2*a);
            float x2 = (-b + sqrt(determinant))/ (2*a);
        if (x1 > 0 && x2 > 0) {
            intersection.t = std::min(x1, x2);  
        } else if (x1 < 0 && x2 > 0) {
            intersection.t = x2;  
        } else if (x1 > 0 && x2 < 0) {
            intersection.t = x1;  
        } else {
            intersection.intersectionExists = false; 
            return intersection;
        }
  
        }
        intersection.intersection = o + d * intersection.t;
        Vec3 normals = (intersection.intersection - current_center);
        normals.normalize();
        intersection.normal = normals;


        return intersection;
    }
};
#endif

// struct RaySphereIntersection{
//     bool intersectionExists;
//     float t;
//     float theta,phi;
//     Vec3 intersection;
//     Vec3 secondintersection;
//     Vec3 normal;
// };