//  self

    #include "03-cylinder-c.h"


//  app

    #include "angle.h"
    #include "light-pnt.h"
    #include "poi-vis.h"
    #include "ray.h"
    #include "spot.h"
    #include "trf-3.h"


//  c++

    using namespace std;



RegisterThrd (CylinderC)



// Luft: 1.000292
// Wasser: 1.333
// Kronglas: 1.46 - 1.65
// Bleikristall: 1.93
// Diamant: 2.42

const double N1 = 1.000292;
const double N2 = 1.333;
// const double N3 = 1.93;
const double N3 = 1.55;



void CylinderC :: Initialize ()
{
    double wd = width();
    double ht = height();
    double dp = fmin (wd, ht);

    Depth = dp;
    Focus = Vec3 (0.5 * wd, 0.1 * ht, - 1.5 * dp);

    Color red     (1.0, 0., 0.);
    Color yellow  (0.996, 0.871, 0.7);
    Color orange (1.0, 0.647, 0);
    Color green   (0.7, 1.0, 0.7);
    Color cyan    (0.7, 1.0, 1.0);
    Color blue    (0.7, 0.7, 1.0);
    Color magenta (1.0, 0.7, 1.0);
    Color white   (1.0, 1.0, 1.0);
    Color black (0, 0, 0);
    // Color gray = 0.7 * white;

    // 1. //////////////////ELLIPSE EXAMPLE///////////////////////////////
    // MyScn.addEllipse(Vec3(0.6*wd, 0.6*wd, 0.6*wd), Vec3(0.2*wd, 0.1*wd, 0.3*wd), white, 0.5, 0.1, 0);

    // 2. /////////////////HARDCODING RUBBERDUCK - WORK IN PROGRESS/////////////////
    // //body center
    // Vec3 p1 (0.6 * wd, 0.6 * wd, 0.6 * Depth);
    // //head center
    // Vec3 p2 (0.75 * wd, 0.6 * ht, 0.75 * Depth);
    // // tail center
    // Vec3 p3 (0.35 * wd, 0.75 * ht, 0.75 * Depth);
    // //wing center
    // Vec3 p4 (0.6 * wd, 0.6 * wd, 0.5 * Depth);
    // //beak center
    // Vec3 p5 (0.85 * wd, 0.6 * ht, 0.6 * Depth);
    // // eyey center
    // Vec3 p6 (0.79 * wd, 0.58 * ht, 0.48 * Depth);

    // // body radiii
    // Vec3 r1 (wd * 0.25, ht * 0.2, Depth * 0.25);
    // // head radii
    // Vec3 r2 (wd * 0.13, wd * 0.1, wd * 0.25);
    // // tail radii
    // Vec3 r3 (wd * 0.09, wd * 0.06, Depth * 0.3);
    // // wing radii
    // Vec3 r4 (wd * 0.15, wd * 0.1, wd * 0.15);
    // //beak radii
    // Vec3 r5 (wd * 0.03, wd * 0.03, wd * 0.35);
    // //eye radii
    // Vec3 r6 (wd * 0.02, wd * 0.04, wd * 0.05);

    // MyScn.addEllipse(p1, r1, yellow, 0.8, 0, 0);
    // MyScn.addEllipse(p2, r2, yellow, 0.8, 0, 0);
    // MyScn.addEllipse(p3, r3, yellow, 0.8, 0, 0);
    // MyScn.addEllipse(p4, r4, yellow, 0.8, 0, 0);
    // MyScn.addEllipse(p5, r5, orange, 0.8, 0, 0);
    // MyScn.addEllipse(p6, r6, black, 0.8, 0, 0);


    //3. ////////////////RUBBERDUCK MEMBER FUNCTION////////////////
    Vec3 dCnt (0.6 * wd, 0.6 * wd, 0.9 * Depth);

    // Vec3 dCnt (0.9 * wd, 0.3 * wd, 0.6 * Depth); // // UPPER LEFT CORNER
    // Vec3 dCnt (0.6 * wd, 0.6 * wd, 0.1 * Depth); // // CROSS SECTION
    // Vec3 dCnt(0.6 * wd, 0.6 * wd, 10 * dp); // // MAKE IT SMALLER

    MyScn.addRubberDuck(dCnt, wd, ht, dp);


    // 4. ///////////////WATER/////////////////////////////////////
    Vec3 surface (0 * wd, 0.84 * ht, 0.9 * dp);
    Vec3 surface2(0, 1, 0);

    MyScn.addPlane(surface, -surface2, cyan, 0.99, 0.3, 0.3, N2);

    // 5. //////////////SUNSET////////////////////////////////////
    // Vec3 surface3 (0, 0 * ht, 0.999 *dp);
    // Vec3 surface4 (0, 0, 1);
    // MyScn.addPlane(surface3, -surface4, orange, 0.9, 0.2, 1.3, N3);

    Lgt1ptr = make_shared <LightPnt> (Vec3 (0.1 * wd, 0.1 * ht,  0.1 * Depth), Color (1, 1, 1));
    Lgt2ptr = make_shared <LightPnt> (Vec3 (0.5 * wd, 0.5 * ht, -1.0 * Depth), Color (1, 1, 1));


}





Color CylinderC :: Shading (const Spot & spt) const
{
    static const double f = 0.5;
    static const double g = 1 - f;

    Color col1 = Lgt1ptr->shading (MyScn, spt);
    Color col2 = Lgt2ptr->shading (MyScn, spt);
    return f * col1 + g * col2;
}



class ReflRefr
{
        Vec3 B, C;
        bool Refr;


        inline int Sgn (double x)
        {
            return x < 0 ? -1 : 1;
        }


    public:

        ReflRefr (const Vec3 & a, const Vec3 & n, double n1, double n2)
        {
            double f = dot (a, n);
            Vec3 p = f * n;
            Vec3 d = p - a;
            B = p + d;

            double g = n1 / n2;
            double h = (f * f - 1) * g * g + 1;

            if (h < 0)
            {
                C = B;
                Refr = n1 > n2;
            }
            else
            {
                C = g * d - Sgn (f) * sqrt (h) * n;
                Refr = true;
            }
        }


        Vec3 dirRefl () const { return B; }
        Vec3 dirRefr () const { return C; }
        bool refr () const { return Refr; }
};



Color CylinderC :: Follow (const Ray & ray1, const PoiVis & poi1, double n1, int level) const
{
    Color col1 (0, 0, 0);
    Color col2 (0, 0, 0);
    Color col3 (0, 0, 0);

    Mat mat = poi1.material();
    int flag = 0;
    if (mat.shad() != 0) flag |= 1;
    if (mat.refl() != 0) flag |= 2;
    if (mat.refr() != 0) flag |= 4;

    if (flag != 0)
    {
        Spot spt1 (ray1, poi1);

        if ((flag & 1) != 0)
            col1 = mat.shad() * Shading (spt1);

        if ((flag & 6) != 0)
        {
            double n2 = mat.n();
            double n = dot (-ray1.direction(), spt1.nrm()) < 0 ? n1 : n2;
            ReflRefr rr (-ray1.direction(), spt1.nrm(), n1, n);

            if ((flag & 2) != 0)
            {
                Ray ray2 (spt1.pnt(), rr.dirRefl());
                PoiVis poi2;
                MyScn.hit (ray2, poi2);
                if (poi2.exists())
                {
                    Spot spt2 (ray2, poi2);
                    Color col = level <= 0 ? Shading (spt2) : Follow (ray2, poi2, n1, level - 1);
                    col2 = mat.refl() * col;
                }
            }

            if (rr.refr() && (flag & 4) != 0)
            {
                Ray ray3 (spt1.pnt(), rr.dirRefr());
                PoiVis poi3;
                MyScn.hit (ray3, poi3);
                if (poi3.exists())
                {
                    Spot spt3 (ray3, poi3);
                    Color col = level <= 0 ? Shading (spt3) : Follow (ray3, poi3, n, level - 1);
                    col3 = mat.refr() * col;
                }
            }
        }
    }

    return col1 + col2 + col3;
}



RGB CylinderC :: ComputePixel (int x, int y)
{
    Vec3 pix (x, y, 0);

    #if 0
        Ray ray (pix, Vec3 (1.0, 0.1, 1.0));
    #else
        Ray ray (pix, pix - Focus);
    #endif

    PoiVis poi;
    MyScn.hit (ray, poi);
    return poi.exists()
        ? Follow (ray, poi, N1, 5)
        : Color (0, 0, 0); // background();
}








