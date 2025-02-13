#ifndef PLANE_H
#define PLANE_H
#include "Vec3.h"
#include "Line.h"
class Plane {
private:
    Vec3 m_center , m_normal;
public:
    Plane() {}
    Plane( Vec3 const & c , Vec3 const & n ) {
        m_center = c;
        m_normal = n; m_normal.normalize();
    }
    void setCenter( Vec3 const & c ) { m_center = c; }
    void setNormal( Vec3 const & n ) { m_normal = n; m_normal.normalize(); }
    Vec3 const & center() const { return m_center; }
    Vec3 const & normal() const { return m_normal; }
    Vec3 project( Vec3 const & p ) const {
        Vec3 result;
        //TODO completer
        return result;
    }
    float squareDistance( Vec3 const & p ) const { return (project(p) - p).squareLength(); }
    float distance( Vec3 const & p ) const { return sqrt( squareDistance(p) ); }


    //https://math.stackexchange.com/questions/1368461/how-do-i-verify-that-a-line-is-parallel-to-a-plane
    //Direction is orthogonal to the plane
    bool isParallelTo( Line const & L ) const {
        bool result;
        Vec3 directionVector = L.direction();
        result = Vec3::dot( directionVector , m_normal ) == 0.f;
        return result;
    }

    //https://www.kristakingmath.com/blog/intersection-of-a-line-and-a-plane
    //https://math.libretexts.org/Bookshelves/Calculus/Supplemental_Modules_(Calculus)/Multivariable_Calculus/1%3A_Vectors_in_Space/Intersection_of_a_Line_and_a_Plane
    Vec3 getIntersectionPoint( Line const & L ) const {
        Vec3 result;
        if (isParallelTo(L)) {
            throw std::runtime_error("The line is parallel to the plane and does not intersect.");
        }

        Vec3 linePoint = L.origin();
        Vec3 lineDirection = L.direction();
        float t = Vec3::dot(m_center - linePoint, m_normal) / Vec3::dot(lineDirection, m_normal);
        result = linePoint + t * lineDirection;

        return result;
    }
};
#endif
