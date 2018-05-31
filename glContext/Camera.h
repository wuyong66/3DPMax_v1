/*************************************************************************
* This head file is for 3D scene script. We will define a scene class    *
* with some light and camera and models.                                 *
*************************************************************************/
#ifndef _CAMERA_H__
#define _CAMERA_H__

#include "CadBase.h"

#define	VIEW_FRONT		0
#define	VIEW_BACK		1
#define VIEW_TOP		2
#define	VIEW_BOTTOM		3
#define VIEW_RIGHT		4
#define	VIEW_LEFT		5
#define VIEW_SW_ISOMETRIC	6
#define VIEW_SE_ISOMETRIC	7
#define VIEW_NE_ISOMETRIC	8
#define VIEW_NW_ISOMETRIC	9

#define ZOOM_ALL		9
#define ZOOM_IN			10
#define ZOOM_OUT		11

class GCamera
{

protected:
	//eye coordinator
    CPoint3D	m_eye;
	CPoint3D	m_ref;
	CVector3D	m_vecUp;

	//viewing volume
    double		m_far, m_near;
	double	 	m_width,m_height;

	//viewport
	double			m_screen[2];

public:
    GCamera();
	~GCamera();

	//initailizing
	void init();


    void projection();
	void selection(int xPos,int yPos);

	//zooming
    void zoom(double scale); 
	void zoom_all(double x0,double y0,double z0,double x1,double y1,double z1);

	//switch into a classical view
    void set_view_type(int type);

	//move view with precent
	void move_view(double dpx, double dpy);

	//set viewport acoording to window
	void set_screen( int x, int y);

	//set eye coordinate
	void set_eye(double eye_x,double eye_y,double eye_z);
	void set_ref(double ref_x,double ref_y,double ref_z);
	void set_vecUp(double up_dx,double up_dy,double up_dz);

	//set viewing volume
	void set_view_rect(double width,double height);
	void get_view_rect(double& width,double& height);

protected:
    void update_upVec();
};
#endif 

/////////////////
