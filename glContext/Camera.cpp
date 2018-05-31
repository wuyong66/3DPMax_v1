#include "stdafx.h"

#include <gl/gl.h>
#include <gl/glu.h>
#include "Camera.h"

//-------------------------------------------------------------
// For Camera class
//-------------------------------------------------------------
//-------------------------------------------------------------
// For Camera class
//-------------------------------------------------------------
GCamera::GCamera(void)
{
}

GCamera::~GCamera()
{
}

void GCamera::projection() 
{
	//switch to projection
   	glMatrixMode(GL_PROJECTION);//投影模式
   	glLoadIdentity();

	glRenderMode(GL_RENDER);
	/*
	函数简介
　　使用glOrtho[1]函数可以将当前的可视空间设置为正投影空间。基参数的意义如图，
如果绘制的图空间本身就是二维的，可以使gluOrtho2D.他的使用类似于glOrtho.
函数用途
　　设置或修改修剪空间的范围
句法
　　void glOrtho(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near,GLdouble far);
描述
　　这个函数描述了一个平行修剪空间。这种投影意味着离观察者较远的对象看上去不会变小（与透视投影相反）。
在3D笛卡尔坐标中想象这个修剪空间，左边和右边是最小和最大的X值，上边和下边是最小和最大的Y值，近处和远处是
最小和最大的Z值。 正射投影，又叫平行投影。这种投影的视景体是一个矩形的平行管道，也就是一个长方体。正射投影的
最大一个特点是无论物体距离相机多远，投影后的物体大小尺寸不变。这种投影通常用在建筑蓝图绘制和计算机辅助设计等
方面，这些行业要求投影后的物体尺寸及相互间的角度不变，以便施工或制造时物体比例大小正确。 　　glOrtho就是一个
正射投影函数。它创建一个平行视景体。实际上这个函数的操作是创建一个正射投影矩阵，并且用这个矩阵乘以当前矩阵。
其中近裁剪平面是一个矩形，矩形左下角点三维空间坐标是（left，bottom，-near），右上角点是（right，top，-near）；
远裁剪平面也是一个矩形，左下角点空间坐标是（left，bottom，-far），右上角点是（right，top，-far）。所有的near
和far值同时为正或同时为负。如果没有其他变换，正射投影的方向平行于Z轴，且视点朝向Z负轴。这意味着物体在视点前面
时far和near都为负值，物体在视点后面时far和near都为正值。
	*/

	//apply projective matrix
	double left		=  - m_width/2.0;
	double right	=  m_width/2.0;
	double bottom	=  - m_height/2.0;
	double top		=  m_height/2.0;

	glOrtho(left,right,bottom,top,m_near,m_far);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	gluLookAt(m_eye.x,m_eye.y,m_eye.z,m_ref.x,m_ref.y,m_ref.z,m_vecUp.dx, m_vecUp.dy, m_vecUp.dz);	
}

void GCamera::selection(int xPos,int yPos)
{
	GLint	vp[4];
	glGetIntegerv(GL_VIEWPORT,vp);

   	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 
	glRenderMode(GL_SELECT);
 	gluPickMatrix(xPos,vp[3]-yPos, 1, 1, vp );

	//apply projective matrix
	double left		=  - m_width/2.0;
	double right	=  m_width/2.0;
	double bottom	=  - m_height/2.0;
	double top		=  m_height/2.0;

	glOrtho(left,right,bottom,top,m_near,m_far);
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	gluLookAt(m_eye.x,m_eye.y,m_eye.z,m_ref.x,m_ref.y,m_ref.z,
		m_vecUp.dx, m_vecUp.dy, m_vecUp.dz);
}

void GCamera::init()
{
	m_eye = CPoint3D(0,0,5000);
	m_ref = CPoint3D(0,0,0);
	m_far = 10000;
	m_near= 1;

	m_width = 2400.0;
	m_height = 2400.0;

	m_vecUp = CVector3D(0,1,0);
	
	m_screen[0] = 400;
	m_screen[1] = 400;
}

void GCamera::set_screen( int x, int y) 
{ 
	glViewport(0,0,x,y);
	if(y==0) y=1;
	double ratio = (double)x/(double)y;
	m_width *= (double)x/m_screen[0];
	m_height *= (double)y/m_screen[1];
	m_width =  m_height*ratio;
	m_screen[0] = x;
	m_screen[1] = y; 
}

void GCamera::set_eye(double eye_x,double eye_y,double eye_z)
{
	m_eye.x = eye_x;
	m_eye.y = eye_y;
	m_eye.z = eye_z;
}

void GCamera::set_ref(double ref_x,double ref_y,double ref_z)
{
	m_ref.x = ref_x;
	m_ref.y = ref_y;
	m_ref.z = ref_z;
}

void GCamera::set_vecUp(double up_dx,double up_dy,double up_dz)
{
	m_vecUp.dx = up_dx;
	m_vecUp.dy = up_dy;
	m_vecUp.dz = up_dz;
}

void GCamera::set_view_rect(double width,double height)
{
	m_width = width;
	m_height = height;
	double aspect = m_screen[0]/m_screen[1];
	m_width =  m_height*aspect;
}

void GCamera::get_view_rect(double& width,double& height)
{
	width = m_width;
	height = m_height;
}

void GCamera::zoom(double scale)
{
	ASSERT(scale > 0.0);
    m_width *= scale;
    m_height *= scale;
}

void GCamera::zoom_all(double x0,double y0,double z0,double x1,double y1,double z1)
{
	

	double width,height;
	double	xl, yl, zl;
	xl = x1-x0;
	yl = y1-y0;
	zl = z1-z0;

	width = max(max(xl,yl),zl);
	height= max(max(xl,yl),zl);

	set_view_rect(width,height);

	//init();//本来想把坐标回归屏幕中央，但是不知道怎么弄
	//m_ref = CPoint3D(0,0,0);

//以下代码是改变视图方向，并保持图像不变形的

//	CVector3D vec = m_eye - m_ref;
//	m_ref.x = (x0+x1)/2;
//	m_ref.y = (y0+y1)/2;
//	m_ref.z = (z0+z1)/2;
//	m_eye = m_ref + vec;




	//glLoadIdentity(); // 不起任何效果
}

void GCamera::set_view_type( int type )
{
	double r;
	CVector3D vec;

	vec = m_ref - m_eye;
	r = vec.GetLength();

	if(IS_ZERO(r)) r = 50.0;
	if( r > 10000)  r = 10000;

	switch(type){
	case VIEW_FRONT:
	//	m_eye = CPoint3D(0,0,1000);		
	//	m_ref = CPoint3D(0,0,0);
	//AfxMessageBox("2222");
		m_eye = m_ref + CVector3D(0,-r,0);

		m_vecUp = CVector3D(0,0,1);
		break;
	case VIEW_BACK:
		m_eye = m_ref + CVector3D(0,r,0);
		m_vecUp = CVector3D(0,0,1);
		break;
	case VIEW_TOP:
		m_eye = m_ref + CVector3D(0,0,r);
		m_vecUp = CVector3D(0,1,0);
		break;
	case VIEW_BOTTOM:
		m_eye = m_ref + CVector3D(0,0,-r);
		m_vecUp = CVector3D(0,1,0);
		break;
	case VIEW_RIGHT:
		m_eye = m_ref + CVector3D(r,0,0);
		m_vecUp = CVector3D(0,0,1);
		break;
	case VIEW_LEFT:
		m_eye = m_ref + CVector3D(-r,0,0);
		m_vecUp = CVector3D(0,0,1);
		break;
	case VIEW_SW_ISOMETRIC:
		m_eye = m_ref + CVector3D(-1,-1,1).GetNormal()*r;
		update_upVec();		
		break;
	case VIEW_SE_ISOMETRIC:
		m_eye = m_ref + CVector3D(1,-1,1).GetNormal()*r;
		update_upVec();		
		break;
	case VIEW_NE_ISOMETRIC:
		m_eye = m_ref + CVector3D(1,1,1).GetNormal()*r;
		update_upVec();
		break;
	case VIEW_NW_ISOMETRIC:
		m_eye = m_ref + CVector3D(-1,1,1).GetNormal()*r;
		update_upVec();
		break;
	}
}

void GCamera::move_view(double dpx, double dpy)
{
	CVector3D vec;
	CVector3D xUp, yUp;

	vec = m_ref - m_eye;
	vec.Normalize();
	xUp = vec*m_vecUp;
	yUp = xUp*vec;

	m_eye -= xUp*m_width*dpx + yUp*m_height*dpy;
	m_ref -= xUp*m_width*dpx + yUp*m_height*dpy;
}

void GCamera::update_upVec()
{
	CVector3D vec = m_ref - m_eye;
	CVector3D zVec(0,0,1);
	CVector3D vec0;

	vec.Normalize();
	vec0 = vec*zVec; 
	m_vecUp = vec0*vec;
}
