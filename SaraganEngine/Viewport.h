#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

struct viewPos
{
	float x;
	float y;
	float width;
	float height;
};

typedef enum {
	fullwindow = 0,
	halfwindowLeft,
	halfwindowRight,
	qwTopLeft,
	qwTopRight,
	qwBottomLeft,
	qwBottomRight
} positionType;

class Viewport
{
public:
	Viewport() {};
	Viewport(HDC& DC, viewPos pos);
	~Viewport();

	PIXELFORMATDESCRIPTOR pfd;
	GLuint PixelFormat;

	std::string CameraName;

	bool isActive;
	bool isCurrent;
	bool isLoaded;


	HDC   hDC;

	// reference to attached camera
	bool isAttached = true;
	positionType layoutPos = fullwindow;

	bool ResizeWindow(viewPos pos);

	void ChangeCamera(std::string camName);

	bool Render();
	void CleanUp();
	void check_gl_error();
};

#endif