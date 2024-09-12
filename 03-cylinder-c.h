#ifndef APP_03_CYLINDER_c_H_INCLUDED
#define APP_03_CYLINDER_c_H_INCLUDED



//  app

    class Color;
    class PoiVis;
    class Spot;

    #include "light-ptr.h"
    #include "scn.h"
    #include "thrd.h"
    #include "vec-3.h"



class CylinderC
    : public Thrd
{
    double Depth;
    Vec3 Focus;
    Scn MyScn;
    LightPtr Lgt1ptr;
    LightPtr Lgt2ptr;

    Color Shading (const Spot & spt) const;
    Color Follow (const Ray & ray, const PoiVis & poi, double n1, int level) const;

    virtual void Initialize () override;
    virtual RGB ComputePixel (int x, int y) override;
};



#endif
