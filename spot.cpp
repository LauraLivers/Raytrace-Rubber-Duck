//  self

    #include "spot.h"


//  app

    #include "light.h"
    #include "poi-vis.h"
    #include "ray.h"
    #include "scn.h"


//  c++

    #include <cmath>



Spot :: Spot (const Ray & ray, const PoiVis & poi)
    : Pnt (ray (poi.lambda()))
    , Nrm (poi.normal (Pnt))
    , EyeDir (- ray.direction())
    , MyMat (poi.material())
{
}

// //////////THIS DOESN'T CREATE THE DESIRED EFFECT////////////////////
// //////////NORMAL INTERPOLATION - MANIPULATE NORM////////////////////
// Spot::Spot(const Ray &ray, const PoiVis &poi)
//     : Pnt(ray(poi.lambda())), EyeDir(-ray.direction()), MyMat(poi.material())
// {
//     Vec3 geoNormal = poi.normal(Pnt);
//     Vec3 otherNormal = Vec3(geoNormal.x(), -geoNormal.y(), geoNormal.z());
//     float hardcodedBlendFactor = 0.9; // 50% blending for testing

//     Nrm = calculateInterpolatedNormal(geoNormal, otherNormal, hardcodedBlendFactor);
// }


// //////////NORMAL INTERPOLATION - HELPER FUNCTION////////////////////
// Vec3 Spot :: calculateInterpolatedNormal(const Vec3 & baseNormal, const Vec3 & otherNormal, double blendFactor)  const{
//     return normalized((1 - blendFactor) * baseNormal + blendFactor * otherNormal);
// }



Color Spot :: Ambi (const Light & lgt) const
{
    return MyMat.ambi() * lgt.ambi();
}



Color Spot :: Diff (const Light & lgt, const Vec3 & lgtdir) const
{
    double s = dot (Nrm, lgtdir);
    return s > 0
        ? s * MyMat.diff() * lgt.diff()
        : Color (0, 0, 0);
        // : MyMat.ambi() * lgt.diff();
}



Color Spot :: Spec (const Light & lgt, const Vec3 & lgtdir) const
{
    Vec3 rfl = reflect (lgtdir, Nrm);
    double s = dot (rfl, EyeDir);
    return s > 0
        ? s * MyMat.spec() * lgt.spec() * pow (s, MyMat.shin())
        : Color (0, 0, 0);
        // : MyMat.ambi() * lgt.spec();
}



Vec3 Spot :: pnt () const
{
    return Pnt;
}



Vec3 Spot :: nrm () const
{
    return Nrm;
}



Color Spot :: shading (const Light & lgt, const Vec3 & lgtdir, const Scn & scn, PoI & poi) const
{
    Color col = Ambi (lgt);

    #if 0
    Ray ray (Pnt, lgtdir);
    if (! scn.hit (ray, poi))
    #endif
    {
        col += Diff (lgt, lgtdir);
        col += Spec (lgt, lgtdir);
    }

    return col;
}
