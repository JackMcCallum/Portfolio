/* Just a bunch of useful macros for various things, not gonna go into detail.  */

#pragma once

// Smooth step
#define Smootherstep(x) (x*x*x*(x*(x*6-15)+10))
#define Smoothstep(x) (x*x*(3-2*x))

// Linear Interpolation functions
#define Lerp(a, b, t) (a+t*(b-a))
#define Bilinear(v00, v01, v10, v11, lx, ly) (Lerp(Lerp(v00, v01, lx), Lerp(v10, v11, lx), ly))
#define Trilinear(v000, v010, v100, v110, v001, v011, v101, v111, lx, ly, lz) Lerp(Bilinear(v000, v010, v100, v110, lx, ly), Bilinear(v001, v011, v101, v111, lx, ly), lz);

// Dimension space (for converting arrays from eg: 1D to 2D)
#define Dim1Dto2D(x, y, width) (y*width + x)
#define Dim1Dto3D(x, y, z, width, height) (z*width*height + y*width + x)

// After some testing these macros are like 20x faster than the normal ones >_>
// Though be careful doing maths inside them might be a big funky results
#define Abs(x) (x > 0 ? x : -x)
#define Floor(x) (float((int)x))
#define Ceil(x) (float((int)x+1))
#define Round(x) (float(int(x+0.5)))
#define Sqr(x) ((x)*(x))
#define Power3(x) ((x)*(x)*(x))
#define Power4(x) ((x)*(x)*(x)*(x))
#define Power5(x) ((x)*(x)*(x)*(x)*(x))
#define Dot(x1,y1,x2,y2) ((x1)*(x2)+(y1)*(y2))

#define PI 3.14159265359f;
#define RadToDeg 57.2957795f
#define DegToRad 0.0174532925f

// Trig in degrees, radians are icky!
#define SinD(x) sin(x*DegToRad);
#define CosD(x) cos(x*DegToRad);
#define TanD(x) tan(x*DegToRad);
#define ATanD2(y, x) (atan2(y, x)*RadToDeg);


// Hot digity! just found this on the web
// Okay so when running debug mode, things get super slow, making debug most almost useless
// So this assembler runs just as fast as sqrt in release mode as it does in debug mode
double inline __declspec (naked) __fastcall SqrtAsm(double n)
{
	_asm fld qword ptr [esp+4]
	_asm fsqrt
	_asm ret 8
}

#define Sqrt(x) sqrt(x)