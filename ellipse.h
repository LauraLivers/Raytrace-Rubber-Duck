#ifndef ELLIPSE_H
#define ELLIPSE_H

class PoI;
class Ray;

#include "obj.h"
#include "vec-3.h"



class Ellipse
    : public Obj
{
    // Centerpoint
    Vec3 Cnt;
    // (a, b, c) Radii for Ellipse
    Vec3 Rad;

public:
    Ellipse();
    Ellipse(const Vec3 & cnt, const Vec3 & rad, const Mat & mat);

    Vec3 center() const;
    Vec3 radii() const;

    bool hit(const Ray & ray, PoI & poi) override;
    Vec3 normal(const Vec3 & pnt) const override;

};


#endif // ELLIPSE_H
