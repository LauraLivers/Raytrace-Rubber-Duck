#ifndef SCN_H_INCLUDED
#define SCN_H_INCLUDED



//  app

    class Color;
    class PoI;
    class Ray;
    class Trf3;
    class Vec3;

    #include "obj-ptr.h"


//  c++

    #include <vector>



class Scn
{
        std::vector <ObjPtr> ObjPtrs;


    public:

        void addSphere (const Vec3 & cnt, double rad, const Color & col,
            double shd = 1, double rfl = 0, double rfr = 0, double n = 1);

        void addPlane (const Vec3 & pnt, const Vec3 & nrm, const Color & col,
            double shd = 1, double rfl = 0, double rfr = 0, double n = 1);

        void addRect (const Vec3 & pnt, const Vec3 & u, const Vec3 & v, const Color & col,
            double shd = 1, double rfl = 0, double rfr = 0, double n = 1);

        void addCyl (const Trf3 & t, double r, double h, const Color & col,
            double shd = 1, double rfl = 0, double rfr = 0, double n = 1);

        void addCyl (const Vec3 & p, const Vec3 & q, double r, const Color & col,
            double shd = 1, double rfl = 0, double rfr = 0, double n = 1);

        void addDisc (const Vec3 & pnt, const Vec3 & nrm, double rad, const Color & col,
            double shd = 1, double rfl = 0, double rfr = 0, double n = 1);

        void addRing (const Vec3 & pnt, const Vec3 & nrm, double rad1, double rad2, const Color & col,
            double shd = 1, double rfl = 0, double rfr = 0, double n = 1);

        bool hit (const Ray & ray, PoI & poi) const;
/////////////////////////////////////////////////////////////////////////////////////////
        void addEllipse(const Vec3 & cnt, const Vec3 & rad, const Color & col,
             double shd =0, double rfl= 1, double rfr = 0, double n = 1);

        void addRubberDuck(const Vec3 & dCnt, double w, double h, double d);

};



#endif
