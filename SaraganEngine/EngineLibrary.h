#ifndef _ENGINE_LIBRARY_H_
#define _ENGINE_LIBRARY_H_


#ifndef CLASSNAME
#define CLASSNAME   L"Saragan"
#endif

#ifndef WNDNAME
#define WNDNAME     L"Saragan"
#endif

#define PI  3.141592654
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.01745329251994329576923690768489

#define DEG2RAD(a)	(PI/180*(a))
#define RAD2DEG(a)	(180/PI*(a))


extern HWND hWnd;
extern HINSTANCE hInst;

#endif