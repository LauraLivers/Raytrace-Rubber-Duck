# Raytrace-Rubber-Duck
Simplistic implementation of Ellipses in a C++ raytracing environment

author: Laura Livers
date: April 25th 2024

This project was done in the context of the module _Raytracing von Grund auf_ at the University of Applied Sciences Lucern (CH) 
and resulted in Grade A.

_This code can be used, but remember: credit, where credit's due!_

## Formula
Ray      : $w = p + \lambda u$ <br>
Ellipse  : $\frac{x^2}{a^2}+\frac{y^2}{b^2}+\frac{z^2}{c^2}=1$<br>
rewrite  : $\frac{(w_x-q_x)^2}{a^2}+\frac{(w_y-q_y)^2}{b^2}+\frac{(w_z-q_z)^2}{c^2}=1$<br>
Intersect: $\frac{((p_x + \lambda u_x) -q_x)^2}{a^2}+\frac{((p_y + \lambda u_y)-q_y)^2}{b^2}+\frac{((p_z + \lambda u_z)-q_z)^2}{c^2}=1$<br>
rewrite  : $\frac{(\lambda u_x + v_x)^2}{a^2}+\frac{(\lambda u_y + v_y)^2}{b^2}+\frac{(\lambda u_z + v_z)^2}{c^2}=1$<br>
expand   : $\frac{\lambda^2u_x^2}{a^2}+\frac{\lambda 2u_x v_x}{a^2}+\frac{v_x^2}{a^2}+\frac{\lambda^2u_y^2}{b^2}+\frac{\lambda 2u_y v_y}{b^2}+\frac{v_y^2}{b^2}+\frac{\lambda^2u_z^2}{c^2}+\frac{\lambda 2u_z v_z}{c^2}+\frac{v_z^2}{c^2} - 1 = 0$<br>
<br>
In order to "plot" the Elipse we're using the discriminant: <br>
$D = B^2 - 4 * A * C$<br>
and the midnight formula:<br>
$\frac{-B - sqrt{D}}{2 * A}$ <br> 
$\frac{B - sqrt{D}}{2 * A}$ <br>
<br>
redefine:<br>
$A = \frac{u_x^2}{a^2}+\frac{u_y^2}{b^2}+\frac{u_z^2}{c^2}$<br>
$B = 2 * \bigrr[\frac{u_xv_x}{a^2}+\frac{u_xv_y}{b^2}+\frac{u_xv_z}{c^2}\biggr]$<br>
$C = \frac{v_x^2}{a^2}+\frac{v_y^2}{b^2}+\frac{v_z^2}{c^2}$<br>

