#ifndef SQUARE_H
#define SQUARE_H
#include "Vec3.h"
#include <vector>
#include "Mesh.h"
#include <cmath>

struct RaySquareIntersection{
    bool intersectionExists;
    float t;
    float u,v;
    Vec3 intersection;
    Vec3 normal;
};


class Square : public Mesh {
public:
    Vec3 m_normal;
    Vec3 m_bottom_left; 
    Vec3 m_right_vector;
    Vec3 m_up_vector;

    Square() : Mesh() {}
    Square(Vec3 const & bottomLeft , Vec3 const & rightVector , Vec3 const & upVector , float width=1. , float height=1. ,
           float uMin = 0.f , float uMax = 1.f , float vMin = 0.f , float vMax = 1.f) : Mesh() {
        setQuad(bottomLeft, rightVector, upVector, width, height, uMin, uMax, vMin, vMax);
    }

    void setQuad( Vec3 const & bottomLeft , Vec3 const & rightVector , Vec3 const & upVector , float width=1. , float height=1. ,
                  float uMin = 0.f , float uMax = 1.f , float vMin = 0.f , float vMax = 1.f) {
        m_right_vector = rightVector;
        m_up_vector = upVector;
        m_normal = Vec3::cross(rightVector , upVector);
        m_bottom_left = bottomLeft;

        m_normal.normalize();
        m_right_vector.normalize();
        m_up_vector.normalize();

        m_right_vector = m_right_vector*width;
        m_up_vector = m_up_vector*height;

        vertices.clear();
        vertices.resize(4);
        vertices[0].position = bottomLeft;                                      vertices[0].u = uMin; vertices[0].v = vMin;
        vertices[1].position = bottomLeft + m_right_vector;                     vertices[1].u = uMax; vertices[1].v = vMin;
        vertices[2].position = bottomLeft + m_right_vector + m_up_vector;       vertices[2].u = uMax; vertices[2].v = vMax;
        vertices[3].position = bottomLeft + m_up_vector;                        vertices[3].u = uMin; vertices[3].v = vMax;
        vertices[0].normal = vertices[1].normal = vertices[2].normal = vertices[3].normal = m_normal;
        triangles.clear();
        triangles.resize(2);
        triangles[0][0] = 0;
        triangles[0][1] = 1;
        triangles[0][2] = 2;
        triangles[1][0] = 0;
        triangles[1][1] = 2;
        triangles[1][2] = 3;


    }

    RaySquareIntersection intersect(const Ray &ray) const {
        RaySquareIntersection intersection;

        //Solution trouvée par un camarade pour régler les soucis d'affichage de la cornell box
        Vec3 m_bottom_left = vertices[0].position;
        Vec3 m_right_vector = vertices[1].position - vertices[0].position;
        Vec3 m_up_vector = vertices[3].position - vertices[0].position;
        Vec3 m_normal = Vec3::cross(m_right_vector, m_up_vector);
        m_normal.normalize();

        //TODO calculer l'intersection rayon quad
        Vec3 o = ray.origin();
        Vec3 d = ray.direction();
        Vec3 n = m_normal;
        Vec3 pos = m_bottom_left;
        float denom = Vec3::dot(d,n);
        if(denom >= 0){
            intersection.intersectionExists = false;
            return intersection;
        }
        float t = Vec3::dot((pos - o),n) / denom;
        Vec3 intersectPoint = o + t*d;
        Vec3 v = intersectPoint - pos;
        Vec3 e1 = m_right_vector;
        Vec3 e2 = m_up_vector;
        float width = e1.length();
        float height = e2.length();
        float u1 = Vec3::dot(v,e1) / width;
        float u2 = Vec3::dot(v,e2) / height;

        if( (u1 < width && u1 > 0.f) && (u2 < height && u2 > 0.f) && t > 0.f){
            intersection.intersectionExists = true;
            intersection.t = t;
            intersection.u = u1;
            intersection.v = u2;
            intersection.intersection = intersectPoint;
            intersection.normal = m_normal;
            return intersection;
        }
        intersection.intersectionExists = false;
        return intersection;
    }
};;
#endif // SQUARE_H
