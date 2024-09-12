#include "ellipse.h"

#include "poi.h"
#include "ray.h"
#include <cmath>

//default constructor
Ellipse :: Ellipse()
    : Ellipse(Vec3(0, 0, 0), Vec3(1, 2, 3), Mat(Color(1, 0, 0)))
{
}
//param constructor
Ellipse ::Ellipse (const Vec3 & cnt, const Vec3 & rad, const Mat & mat)
    : Obj(mat)
    , Cnt(cnt)
    , Rad(rad)
{
}
//getter
Vec3 Ellipse::center() const {
    return Cnt;
}
Vec3 Ellipse::radii() const {
    return Rad;
}
bool Ellipse::hit(const Ray & ray, PoI & poi) {
    //pixel to center
    Vec3 v = ray.point() - Cnt;
    // w = p + lambda * u
    Vec3 u = ray.direction();
    //Ellipse
    // u.x^2/a^2 + u.y^2/b^2 + u.z^2/c^2
    double A = (u.x() * u.x()) / (Rad.x() * Rad.x()) +
               (u.y() * u.y()) / (Rad.y() * Rad.y()) +
               (u.z() * u.z()) / (Rad.z() * Rad.z());
    // (2 * u.x * v.x )/ a^2 + (2 * u.y * v.y )/ b^2 + (2 * u.z * v.z )/ c^2
    double B = 2 * ((u.x() * v.x()) / (Rad.x() * Rad.x()) +
                    (u.y() * v.y()) / (Rad.y() * Rad.y()) +
                    (u.z() * v.z()) / (Rad.z() * Rad.z()));
    //v.x^2/ a^2 + v.y^2/ b^2 + v.z^2/ c^2 -1
    double C = (v.x() * v.x()) / (Rad.x() * Rad.x()) +
               (v.y() * v.y()) / (Rad.y() * Rad.y()) +
               (v.z() * v.z()) / (Rad.z() * Rad.z()) -1; //do not forget the 1!

    double D = B * B - 4 * A * C;
    if (D < 0)
        return false;

    return poi.process((-B - sqrt(D)) / (2 * A), shared_from_this())
        || poi.process((-B + sqrt(D)) / (2 * A), shared_from_this());


}

Vec3 Ellipse :: normal(const Vec3 & pnt) const {
    return normalized(pnt - Cnt);
}
