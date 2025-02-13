#ifndef RAY_H
#define RAY_H
#include "Line.h"
class Ray : public Line {
private: 
    double tm;
public:
    Ray() : Line() {}
    Ray( Vec3 const & o , Vec3 const & d ) : Line(o,d) {}
    Ray(Vec3 const & o , Vec3 const & d  , double tmps) : Line(o,d), tm(tmps) {}

    double time() const { return tm; }
};
#endif
