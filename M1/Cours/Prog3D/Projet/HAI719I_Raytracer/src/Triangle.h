#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Vec3.h"
#include "Ray.h"
#include "Plane.h"

struct RayTriangleIntersection{
    bool intersectionExists;
    float t;
    float w0,w1,w2;
    unsigned int tIndex;
    Vec3 intersection;
    Vec3 normal;
};

class Triangle {
private:
    Vec3 m_c[3] , m_normal;
    float area;
public:
    Triangle() {}
    Triangle( Vec3 const & c0 , Vec3 const & c1 , Vec3 const & c2 ) {
        m_c[0] = c0;
        m_c[1] = c1;
        m_c[2] = c2;
        updateAreaAndNormal();
    }
    void updateAreaAndNormal() {
        Vec3 nNotNormalized = Vec3::cross( m_c[1] - m_c[0] , m_c[2] - m_c[0] );
        float norm = nNotNormalized.length();
        m_normal = nNotNormalized / norm;
        area = norm / 2.f;
    }
    void setC0( Vec3 const & c0 ) { m_c[0] = c0; } // remember to update the area and normal afterwards!
    void setC1( Vec3 const & c1 ) { m_c[1] = c1; } // remember to update the area and normal afterwards!
    void setC2( Vec3 const & c2 ) { m_c[2] = c2; } // remember to update the area and normal afterwards!
    Vec3 const & normal() const { return m_normal; }
    Vec3 projectOnSupportPlane( Vec3 const & p ) const {
        Vec3 result;
        //TODO completer
        
        return result;
    }
    float squareDistanceToSupportPlane( Vec3 const & p ) const {
        float result;
        //TODO completer
        return result;
    }
    float distanceToSupportPlane( Vec3 const & p ) const { return sqrt( squareDistanceToSupportPlane(p) ); }
    bool isParallelTo( Line const & L ) const {
        bool result;
        //TODO completer
        return result;
    }
    Vec3 getIntersectionPointWithSupportPlane( Line const & L ) const {
        // you should check first that the line is not parallel to the plane!
        Vec3 result;
        //TODO completer
        return result;
    }

    //https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
    void computeBarycentricCoordinates( Vec3 const & p , float & u0 , float & u1 , float & u2 ) const {
                // 1. Compute vectors from the vertices of the triangle to the point p
                Vec3 v0 = m_c[1] - m_c[0];
                Vec3 v1 = m_c[2] - m_c[0];
                Vec3 v2 = p - m_c[0];

                // 2. Compute dot products
                float dot00 = Vec3::dot(v0, v0);
                float dot01 = Vec3::dot(v0, v1);
                float dot02 = Vec3::dot(v0, v2);
                float dot11 = Vec3::dot(v1, v1);
                float dot12 = Vec3::dot(v1, v2);

                // 3. Compute the barycentric coordinates
                float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
                u1 = (dot11 * dot02 - dot01 * dot12) * invDenom;
                u2 = (dot00 * dot12 - dot01 * dot02) * invDenom;
                u0 = 1.0f - u1 - u2;
    }


    //need for kd
    Vec3 get_mc(int i) const {
        return m_c[i];
    }

    //https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-polygon-mesh/ray-tracing-polygon-mesh-part-1.html

    RayTriangleIntersection getIntersection( Ray const & ray ) const {
        RayTriangleIntersection result;
        // 1) check that the ray is not parallel to the triangle:
        Plane supportPlane(m_c[0],m_normal);
        if( supportPlane.isParallelTo(ray) ) {
            result.intersectionExists = false;
            return result;
        }        
        // 2) check that the triangle is "in front of" the ray:
        Vec3 intersectionPoint = supportPlane.getIntersectionPoint(ray);
        Vec3 originToIntersection = intersectionPoint - ray.origin();
        float t = Vec3::dot(originToIntersection,ray.direction());
        if( t < 0.f ) {
            result.intersectionExists = false;
            return result;
        }
        // 3) check that the intersection point is inside the triangle:
        // CONVENTION: compute u,v such that p = w0*c0 + w1*c1 + w2*c2, check that 0 <= w0,w1,w2 <= 1

        float w0,w1,w2;
        computeBarycentricCoordinates(intersectionPoint,w0,w1,w2);
        if( w0 < 0.f || w0 > 1.f || w1 < 0.f || w1 > 1.f || w2 < 0.f || w2 > 1.f ) {
            result.intersectionExists = false;
            return result;
        }

        //INTERPOLATION
        //http://web.archive.org/web/20090609111431/http://www.crackthecode.us/barycentric/barycentric_coordinates.html
        //https://www.reddit.com/r/gamedev/comments/1bm5y8/vertex_normal_interpolation/?rdt=46710
        Vec3 n3 = Vec3::cross( m_c[1] - m_c[0] , m_c[2] - m_c[0] );
        n3.normalize();
        Vec3 n0 = m_c[0]; 
        Vec3 n1 = m_c[1]; 
        Vec3 n2 = m_c[2]; 

        Vec3 interpolatedNormal = w0*n3 + w1*n3 + w2*n3 ;

        interpolatedNormal.normalize();

        // 4) Finally, if all conditions were met, then there is an intersection! :
        result.intersectionExists = true;
        result.t = t;
        result.w0 = w0;
        result.w1 = w1;
        result.w2 = w2;
        result.intersection = intersectionPoint;
        //result.normal = m_normal; //withoyt interpolation
        result.normal = interpolatedNormal; //with interpolation
        //result.tIndex = 0;

        return result;
    }
};
#endif
