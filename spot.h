#ifndef SPOT_H_INCLUDED
#define SPOT_H_INCLUDED



//  app

    class Light;
    class PoI;
    class PoiVis;
    class Ray;
    class Scn;

    #include "mat.h"
    #include "vec-3.h"




class Spot
{
        Vec3 Pnt, Nrm, EyeDir;
        Mat MyMat;


        Color Ambi (const Light & lgt) const;
        Color Diff (const Light & lgt, const Vec3 & lgtdir) const;
        Color Spec (const Light & lgt, const Vec3 & lgtdir) const;

        Vec3 calculateInterpolatedNormal(const Vec3 & baseNormal, const Vec3 & otherNormal, double blendFactor) const;


    public:

        Spot (const Ray & ray, const PoiVis & poi);

        Vec3 pnt () const;
        Vec3 nrm () const;
        Color shading (const Light & lgt, const Vec3 & lgtdir, const Scn & scn, PoI & poi) const;
};



#endif
