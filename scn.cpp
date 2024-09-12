//  self

    #include "scn.h"


//  app

    #include "angle.h"
    #include "cyl.h"
    #include "disc.h"
    #include "plane.h"
    #include "rect.h"
    #include "ring.h"
    #include "sphere.h"
    #include "ellipse.h"
    #include "obj.h"



//  c++

    using namespace std;

// RegisterThrd(Scn)



void Scn :: addSphere (const Vec3 & cnt, double rad,
    const Color & col, double shd, double rfl, double rfr, double n)
{
    ObjPtr objptr = make_shared <Sphere> (cnt, rad, Mat (col, 50, shd, rfl, rfr, n));
    ObjPtrs.push_back (objptr);
}



void Scn :: addPlane (const Vec3 & pnt, const Vec3 & nrm,
    const Color & col, double shd, double rfl, double rfr, double n)
{
    ObjPtr objptr = make_shared <Plane> (pnt, nrm, Mat (col, 50, shd, rfl, rfr, n));
    ObjPtrs.push_back (objptr);
}



void Scn :: addRect (const Vec3 & pnt, const Vec3 & u, const Vec3 & v,
    const Color & col, double shd, double rfl, double rfr, double n)
{
    ObjPtr objptr = make_shared <Rect> (pnt, u, v, Mat (col, 50, shd, rfl, rfr, n));
    ObjPtrs.push_back (objptr);
}



void Scn :: addCyl (const Trf3 & t, double r, double h,
    const Color & col, double shd, double rfl, double rfr, double n)
{
    ObjPtr objptr = make_shared <Cyl> (t, r, h, Mat (col, 50, shd, rfl, rfr, n));
    ObjPtrs.push_back (objptr);
}



void Scn :: addCyl (const Vec3 & p, const Vec3 & q, double r,
    const Color & col, double shd, double rfl, double rfr, double n)
{
    Vec3 pq = q - p;
    double h = norm (pq);
    Vec3 cylax = h == 0 ? Vec3 (0, 0, 0) : pq / h;
    Vec3 e3 (0, 0, 1);
    Vec3 rotax = cross (e3, cylax);
    double c = dot (cylax, e3);
    double s = norm (rotax);
    Angle phi (c, s);
    Trf3 trf = Trf3::T (p) * Trf3::R (rotax / s, phi); // abgeleitet T * R (homogene koordinaten)

    addCyl (trf, r, h, col, shd, rfl, rfr, n);
}



void Scn :: addDisc (const Vec3 & pnt, const Vec3 & nrm, double rad,
    const Color & col, double shd, double rfl, double rfr, double n)
{
    ObjPtr objptr = make_shared <Disc> (pnt, nrm, rad, Mat (col, 50, shd, rfl, rfr, n));
    ObjPtrs.push_back (objptr);
}



void Scn :: addRing (const Vec3 & pnt, const Vec3 & nrm, double rad1, double rad2,
    const Color & col, double shd, double rfl, double rfr, double n)
{
    ObjPtr objptr = make_shared <Ring> (pnt, nrm, rad1, rad2, Mat (col, 50, shd, rfl, rfr, n));
    ObjPtrs.push_back (objptr);
}

void Scn :: addEllipse(const Vec3 & cnt, const Vec3 & rad, const Color & col,  double shd, double rfl, double rfr, double n) {
    ObjPtr objptr = make_shared <Ellipse> (cnt, rad, Mat (col, 50, shd, rfl, rfr, n));
    ObjPtrs.push_back (objptr);
}




//////////////////////////////////////////////////////////////////////////////////////////
void Scn :: addRubberDuck(const Vec3 & dCnt, double w, double h, double d) {

    Color yellow (0.996, 0.871, 0); //eggyolk yellow
    Color orange (1.0, 0.647, 0);
    Color black (0, 0, 0);

    ////////////////ORIGINAL///////////////////
    // body center
    Vec3 p1Original (0.6 * w, 0.6 * w, 0.6 * d);
    // head center
    Vec3 p2Original = Vec3(1.25 * p1Original.x(), 0.75 * p1Original.y(), 1.25 * p1Original.z()); // might be redundant or actually false....
    // tail Center
    Vec3 p3Original = Vec3(0.67 * p1Original.x(), 0.92 * p1Original.y(), 0.92 * p1Original.z());
    // wing Center
    Vec3 p4Original = Vec3(1.0 * p1Original.x(), 1.0 * p1Original.y(), 0.83 * p1Original.z());
    // beak Center
    Vec3 p5Original = Vec3(1.42 * p1Original.x(), 0.75 * p1Original.y(), 1.2 * p1Original.z());
    // eye Center
    Vec3 p6Original = Vec3(1.32 * p1Original.x(), 0.73 * p1Original.y(), 0.80 * p1Original.z());

    ////////////////TRANSLATION///////////////
    // Body
    Vec3 p1 (dCnt.x(), dCnt.y(), dCnt.z()); // passed parameter
    // head
    Vec3 p2 = p1 + p2Original - p1Original; // subtract old original center
    // tail
    Vec3 p3 = p1 + p3Original - p1Original;
    // wing
    Vec3 p4 = p1 + p4Original - p1Original;
    // beak
    Vec3 p5 = p1 + p5Original - p1Original;
    // eye
    Vec3 p6 = p1 + p6Original - p1Original;


    ////////////////RADII//////////////////////
    // body radiii
    Vec3 r1 (w * 0.25, h * 0.2, d * 0.25);
    // head radii
    Vec3 r2(r1.x() * (0.13 / 0.25), r1.x() * (0.1 / 0.25), r1.x() * (0.25 / 0.25));
    // tail radii
    Vec3 r3(r1.x() * (0.1 / 0.25), r1.x() * (0.05 / 0.25), r1.x() * (0.1 / 0.25));
    // wing radii
    Vec3 r4(r1.x() * (0.15 / 0.25), r1.x() * (0.1 / 0.25), r1.x() * (0.15 / 0.25));
    // beak radii
    Vec3 r5(r1.x() * (0.15 / 0.25), r1.x() * (0.03 / 0.25), r1.x() * (0.05 / 0.25));
    // eye radii
    Vec3 r6(r1.x() * (0.02 / 0.25), r1.x() * (0.04 / 0.25), r1.x() * (0.03 / 0.25));

    addEllipse(p1, r1, yellow, 0.91, 0, 0, 1.000292);
    addEllipse(p2, r2, yellow, 0.91, 0, 0, 1.000292);
    addEllipse(p3, r3, yellow, 1, 0, 0, 1.000292);
    addEllipse(p4, r4, yellow, 1, 0, 0, 1.000292);
    addEllipse(p5, r5, orange, 1, 0, 0, 1.000292);
    addEllipse(p6, r6, black, 1, 0, 0, 1.000292);

}




bool Scn :: hit (const Ray & ray, PoI & poi) const
{
    for (const ObjPtr & objptr: ObjPtrs)
        if (objptr->hit (ray, poi))
            return true;
    return false;
}




