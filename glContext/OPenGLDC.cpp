#include "stdafx.h"
#include "OpenGLDC.h"
#include "gl/glut.h"

#define GL_PI 3.1415f
#define MAX_CHAR   128

// OpenGLDC.cpp: implementation of the COpenGLDC class.
//
//////////////////////////////////////////////////////////////////////


COpenGLDC::COpenGLDC(HWND hWnd):m_hWnd(hWnd)
{
	m_bSelectionMode = FALSE;
}

COpenGLDC::~COpenGLDC()
{
}

BOOL COpenGLDC::InitDC()
{
	if (m_hWnd == NULL) return FALSE;
	
	m_Camera.init();

	m_hDC = ::GetDC(m_hWnd);			// Get the Device context

	int pixelformat;
	PIXELFORMATDESCRIPTOR pfdWnd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Structure size.
		1,                             // Structure version number.
		PFD_DRAW_TO_WINDOW |           // Property flags.
		PFD_SUPPORT_OPENGL |
 		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,                            // 24-bit color.
		0, 0, 0, 0, 0, 0,              // Not concerned with these.
		0, 0, 0, 0, 0, 0, 0,           // No alpha or accum buffer.
		32,                            // 32-bit depth buffer.
		0, 0,                          // No stencil or aux buffer.
		PFD_MAIN_PLANE,                // Main layer type.
		0,                             // Reserved.
		0, 0, 0                        // Unsupported.
	};

    if ( (pixelformat = ChoosePixelFormat(m_hDC, &pfdWnd)) == 0 )
	{
		AfxMessageBox("ChoosePixelFormat to wnd failed");
		return FALSE;
	}

    if (SetPixelFormat(m_hDC, pixelformat, &pfdWnd) == FALSE)
        AfxMessageBox("SetPixelFormat failed");

	m_hRC=wglCreateContext(m_hDC);

	VERIFY(wglMakeCurrent(m_hDC,m_hRC));
	GLSetupRC();
	wglMakeCurrent(NULL,NULL);
	return m_hRC!=0;
}


void COpenGLDC::GLResize(int w,int h)
{
	wglMakeCurrent(m_hDC,m_hRC);

	// Prevent a divide by zero
	if(h == 0) h = 1;
	if(w == 0) w = 1;
	m_Camera.set_screen(w,h);
}

void COpenGLDC::GLSetupRC()
{
	//initialize color and rendering
	m_bShading = TRUE;

	//bright white light - full intensity RGB values
	GLfloat lightAmbient[] = {0.75f,0.75f,0.75f,1.0f};
	GLfloat lightDiffuse[] = {1.0f,1.0f,1.0f,1.0f};

	glEnable(GL_DEPTH_TEST);		//Hidden surface removal
	glEnable(GL_CULL_FACE);			//Do not calculate inside of object
	glFrontFace(GL_CCW);			//counter clock-wise polygons face out

	glEnable(GL_LIGHTING);			//enable lighting

	//setup and enable light 0
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmbient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiffuse);
	SetLightDirection(1,1,1);
	glEnable(GL_LIGHT0);

	//Initialize Material Color to Gray
	SetBkColor(RGB(0,0,0));				//black background
	SetMaterialColor(RGB(225,175,22));	//golden material color
	SetColor(RGB(255,255,255));			//white frame color
	SetHighlightColor(RGB(255,0,0));	//red highlight color	

	//Point Size
	glPointSize(3.0);
}


void COpenGLDC::Ready()
{
	wglMakeCurrent(m_hDC,m_hRC);
//	　使一个指定的OpenGL渲染上下文调用线程的当前呈现上下文 。
//	所有后续的OpenGL调用线程所确定的设备 HDC上绘制 。您还可以
//	使用wglMakeCurrent改变，所以旧的上下文将不再是当前调用线程
//	的当前呈现的上下文 。 http://baike.baidu.com/view/3661422.htm

	ClearBkground();

	OnShading();
	m_Camera.projection();
}
void COpenGLDC::CHReady()
{
	wglMakeCurrent(m_hDC,m_hRC);
	CHClearBkground();

	OnShading();
	m_Camera.projection();	
}


void COpenGLDC::Finish()
{
	glFlush();
	SwapBuffers(m_hDC);
	wglMakeCurrent(m_hDC,NULL);
}


//////////////////LIGHT && MATERIALS SETTING//////////
void COpenGLDC::ClearBkground()
{
//	AfxMessageBox("被调用");
	GLclampf	r,g,b;
	r = (GLclampf)GetRValue(m_clrBk)/255.0;
	g = (GLclampf)GetGValue(m_clrBk)/255.0;
	b = (GLclampf)GetBValue(m_clrBk)/255.0;

//	glClearColor(r,g,b,0.0f);//设置背景为黑色
//	glClearColor(0.4,0.5,0.65,0.0f);
	glClearColor(0.629,0.808,0.922,0.0f);//设置背景为黑色
//	glClearColor(1,1,1,0.0f);//设置背景为白色
//	glClear函数来自OPENGL,其中它是通过glClear使用红，
//		绿，蓝以及AFA值来清除颜色缓冲区的，并且都被
//		归一化在（0，1）之间的值，其实就是清空当前的
//		所有颜色。 
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//	glClear（GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT）表示要清除颜色缓冲以及深度缓冲 
}


void COpenGLDC::CHClearBkground()
{
	GLclampf	r,g,b;
	r = (GLclampf)GetRValue(m_clrBk)/255.0;
	g = (GLclampf)GetGValue(m_clrBk)/255.0;
	b = (GLclampf)GetBValue(m_clrBk)/255.0;

	glClearColor(r,g,b,0.0f);//设置背景为黑色
//	glClearColor(0.4,0.5,0.65,0.0f); 
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
}

//setting model
void COpenGLDC::OnShading()
{
	if(m_bShading){
		glEnable( GL_LIGHTING );
	    glEnable(GL_LIGHT0);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
	else{
		glDisable( GL_LIGHTING );
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
}

void COpenGLDC::Shading(BOOL bShading)
{
	m_bShading = bShading;
}

BOOL COpenGLDC::IsShading()
{
	return m_bShading;
}

void COpenGLDC::Lighting(BOOL bLighting)
{
	if(bLighting)
		glEnable( GL_LIGHTING );
	else
		glDisable( GL_LIGHTING );
}

BOOL COpenGLDC::IsLighting()
{
	GLboolean bLighting;
	glGetBooleanv(GL_LIGHTING,&bLighting);   
	return bLighting;
}

void COpenGLDC::SetLightDirection(float dx,float dy,float dz)
{
	m_vecLight[0] = dx;
	m_vecLight[1] = dy;
	m_vecLight[2] = dz;
	GLfloat lightPos[] = { dx, dy, dz, 0.0f };
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
}

void COpenGLDC::GetLightDirection(float& dx,float& dy,float& dz)
{
	dx = m_vecLight[0];
	dy = m_vecLight[1];
	dz = m_vecLight[2];
}

//rendering color
void COpenGLDC::SetMaterialColor(COLORREF clr)
{
	m_clrMaterial = clr;
	BYTE r,g,b;
	r = GetRValue(clr);
	g = GetGValue(clr);
	b = GetBValue(clr);
	GLfloat mat_amb_diff[] = {(GLfloat)r/255,(GLfloat)g/255,(GLfloat)b/255,1.0};
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
}

void COpenGLDC::GetMaterialColor(COLORREF& clr)
{
	clr = m_clrMaterial;
}

void COpenGLDC::SetBkColor(COLORREF clr)
{
	m_clrBk = clr;
}

void COpenGLDC::GetBkColor(COLORREF& clr)
{
	clr = m_clrBk;
}

void COpenGLDC::SetColor(COLORREF clr)
{
	m_clr = clr;
	BYTE r,g,b;
	r = GetRValue(clr);
	g = GetGValue(clr);
	b = GetBValue(clr);
	glColor3ub(r,g,b);
}

void COpenGLDC::GetColor(COLORREF& clr)
{
	clr =  m_clr;
}

void COpenGLDC::SetHighlightColor(COLORREF clr)
{
	m_clrHighlight = clr;
}

void COpenGLDC::GetHighlightColor(COLORREF& clr)
{
	clr = m_clrHighlight;
}

void COpenGLDC::Highlight(BOOL bHighlight)
{
	BYTE r,g,b;
	if(bHighlight){
		r = GetRValue(m_clrHighlight);
		g = GetGValue(m_clrHighlight);
		b = GetBValue(m_clrHighlight);
	}
	else{
		r = GetRValue(m_clrMaterial);
		g = GetGValue(m_clrMaterial);
		b = GetBValue(m_clrMaterial);
	}
	GLfloat mat_amb_diff[] = {(GLfloat)r/255,(GLfloat)g/255,(GLfloat)b/255,1.0};
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
}


//////////////////////// drawing functions ////////////////////////
//draw point
void COpenGLDC::DrawPoint(const CPoint3D& pt)                     //画点
{
	glBegin(GL_POINTS);
		glVertex3f(pt.x,pt.y,pt.z);
	glEnd();
}

void COpenGLDC::DrawLine(const CPoint3D& sp,const CPoint3D& ep)   //画线
{
	glBegin(GL_LINES);
		glVertex3f(sp.x,sp.y,sp.z);
		glVertex3f(ep.x,ep.y,ep.z);
	glEnd();
}

void COpenGLDC::DrawPolyline(const CPoint3D* pt,int size)         //画多段线  pt应该是这个指针列表的指针
{
	glBegin(GL_LINE_STRIP);
	for(int i=0;i<size;i++)
		glVertex3f(pt[i].x,pt[i].y,pt[i].z);
	glEnd();
}

void COpenGLDC::DrawTriChip(double n0,double n1,double n2,
							double v00,double v01,double v02,
							double v10,double v11,double v12,
							double v20,double v21,double v22)//画三角形
{
	glBegin(GL_TRIANGLES);
		glNormal3d(n0,n1,n2);
		glVertex3d(v00,v01,v02);
		glVertex3d(v10,v11,v12);
		glVertex3d(v20,v21,v22);
	glEnd();
}

//Draw 3D Solid
void COpenGLDC::DrawSphere(const CPoint3D& cen,double r,const CVector3D& vec)//画球体?
{
	glPushMatrix();
	glTranslatef(cen.x,cen.y,cen.z);

	CVector3D vecNY(0,-1,0);
	CVector3D axis = vecNY*vec;
	double ang = _AngleBetween(vecNY,vec);
	ang = ang*180/GL_PI;
	glRotatef(ang,axis.dx,axis.dy,axis.dz);

	auxSolidSphere(r);
	glPopMatrix();
}

void COpenGLDC::DrawCylinder(const CPoint3D& cen,double r,const CVector3D& h)//画圆柱体
{
	glPushMatrix();

	glTranslatef(cen.x,cen.y,cen.z);

	CVector3D vecNY(0,-1,0);
	CVector3D axis = vecNY*h;
	double ang = _AngleBetween(vecNY,h);
	ang = ang*180/GL_PI;
	glRotatef(ang,axis.dx,axis.dy,axis.dz);


	auxSolidCylinder(r,h.GetLength());
	glPopMatrix();
}

void COpenGLDC::DrawTorus(const CPoint3D& cen,const CVector3D& ax,double r_in,double r_out)//画圆环体
{
	glPushMatrix();

	glTranslatef(cen.x,cen.y,cen.z);

	CVector3D vecNY(0,-1,0);
	CVector3D axis = vecNY*ax;
	double ang = _AngleBetween(vecNY,ax);
	ang = ang*180/GL_PI;
	glRotatef(ang,axis.dx,axis.dy,axis.dz);


	auxSolidTorus(r_in,r_out);
	glPopMatrix();
}

void COpenGLDC::DrawCone(const CPoint3D& cen,double r,const CVector3D& h)//画圆锥体
{
	glPushMatrix();

	glTranslatef(cen.x,cen.y,cen.z);

	CVector3D vecNY(0,-1,0);
	CVector3D axis = vecNY*h;
	double ang = _AngleBetween(vecNY,h);
	ang = ang*180/GL_PI;

	glRotatef(ang,axis.dx,axis.dy,axis.dz);

	GLfloat angle,x,y;
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0,0,h.GetLength());
		for(angle =0.0f;angle<(2.0f*GL_PI);angle += (GL_PI/8.0f))
		{
			x = r*sin(angle);
			y = r*cos(angle);
			glVertex2f(x,y);
		}
	glEnd();

	// Begin a new triangle fan to cover the bottom
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0f,0.0f);
		for(angle =0.0f;angle<(2.0f*GL_PI);angle += (GL_PI/8.0f))
		{
			x = r*sin(angle);
			y = r*cos(angle);
			glVertex2f(x,y);
		}
	glEnd();
	glPopMatrix();
//	triangle_strip:就是前3个点组成一个简单图形（这里不就是3角形嘛），第4个点和其之前2个点组成又一个简单图形，以此类推。
//triangle_fan:就是前3个点组成一个简单图形，第4个点和其之前一个点以及第一个点组成又一个简单图形，以此类推。
//triangle_list:哈哈，见图。。。。。
}

////////////////////////////////////////

void COpenGLDC::DrawCoord()//画坐标系
{

	BOOL bLighting = IsLighting();
	Lighting(FALSE);

	double width,height;
	m_Camera.get_view_rect(width,height);
	double len = min(width,height);
	len *= 0.2;

	CPoint3D cPt,xPt,yPt,zPt;
	xPt.x = yPt.y = zPt.z = len;

	COLORREF old_clr;
	GetColor(old_clr);

	SetColor(RGB(255,0,255));
	glRasterPos3f(cPt.x, cPt.y,cPt.z);
	drawString("0");
	
	//axis-x: red
	SetColor(RGB(255,0,0));
	DrawLine(cPt,xPt);
	
	//glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos3f(xPt.x, xPt.y,xPt.z);
	drawString("x");

	//axis-y: green
	SetColor(RGB(0,255,0));
	DrawLine(cPt,yPt);
	
	//glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos3f(yPt.x, yPt.y,yPt.z);
	drawString("y");

	//axis-z: blue
	SetColor(RGB(0,0,255));
	DrawLine(cPt,zPt);
	glRasterPos3f(zPt.x, zPt.y,zPt.z);
	drawString("z");

	Lighting(bLighting);
	SetColor(old_clr);
}

//////////////////////////////////////////////////
void COpenGLDC::BeginSelection(int xPos,int yPos)
{
	m_bSelectionMode = TRUE;
	wglMakeCurrent(m_hDC,m_hRC);
	
	
	//set up selection buffer	
	glSelectBuffer(BUFFER_LENGTH,m_selectBuff);
	
	//switch to projection and save the matrix
	m_Camera.selection(xPos,yPos);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	InitNames();
}

int	COpenGLDC::EndSelection(UINT* items)
{
	m_bSelectionMode = FALSE;
	int hits = glRenderMode(GL_RENDER);
	for(int i=0;i<hits;i++){
		items[i] = m_selectBuff[i*4+3];
	}
	wglMakeCurrent(m_hDC,NULL);
	return hits;
}

BOOL COpenGLDC::IsSelectionMode()
{
	return m_bSelectionMode;
}

void COpenGLDC::InitNames()
{
	glInitNames();
	glPushName(0);
}

void COpenGLDC::LoadName(UINT name)
{
	glLoadName(name);
}

void COpenGLDC::PushName(UINT name)
{
	glPushName(name);
}

void COpenGLDC::PopName()
{
	glPopName();
}

//glBegin, glEnd
//The glBegin and glEnd functions delimit the vertices of a primitive or a group of like primitives.
//
//void glBegin(
//  GLenum mode
//);
// 
//void glEnd(
//  void
//);
//Parameters
//mode 
//The primitive or primitives that will be created from vertices presented between glBegin and the subsequent glEnd. The following are accepted symbolic constants and their meanings: 
//GL_POINTS 
//Treats each vertex as a single point. Vertex n defines point n. N points are drawn. 
//GL_LINES 
//Treats each pair of vertices as an independent line segment. Vertices 2n – 1 and 2n define line n. N/2 lines are drawn. 
//GL_LINE_STRIP 
//Draws a connected group of line segments from the first vertex to the last. Vertices n and n+1 define line n. N – 1 lines are drawn. 
//GL_LINE_LOOP 
//Draws a connected group of line segments from the first vertex to the last, then back to the first. Vertices n and n+1 define line n. The last line, however, is defined by vertices N and 1. N lines are drawn. 
//GL_TRIANGLES 
//Treats each triplet of vertices as an independent triangle. Vertices 3n – 2, 3n –1, and 3n define triangle n. N/3 triangles are drawn. 
//GL_TRIANGLE_STRIP 
//Draws a connected group of triangles. One triangle is defined for each vertex presented after the first two vertices. For odd n, vertices n, n + 1, and n + 2 define triangle n. For even n, vertices n + 1, n, and n + 2 define triangle n. N – 2 triangles are drawn. 
//GL_TRIANGLE_FAN 
//Draws a connected group of triangles. One triangle is defined for each vertex presented after the first two vertices. Vertices 1, n + 1, and n + 2 define triangle n. N – 2 triangles are drawn. 
//GL_QUADS 
//Treats each group of four vertices as an independent quadrilateral. Vertices 4n – 3, 4n – 2, 4n – 1, and 4n define quadrilateral n. N/4 quadrilaterals are drawn. 
//GL_QUAD_STRIP 
//Draws a connected group of quadrilaterals. One quadrilateral is defined for each pair of vertices presented after the first pair. Vertices 2n – 1, 2n, 2n + 2, and 2n + 1 define quadrilateral n. N quadrilaterals are drawn. Note that the order in which vertices are used to construct a quadrilateral from strip data is different from that used with independent data. 
//GL_POLYGON 
//Draws a single, convex polygon. Vertices 1 through N define this polygon. 

//
void COpenGLDC::drawString(const char *str)
{
	static int isFirstCall = 1;
    static GLuint lists;
    if( isFirstCall ){
	// 如果是第一次调用，执行初始化
        // 为每一个ASCII字符产生一个显示列表
        isFirstCall = 0;
        // 申请MAX_CHAR个连续的显示列表编号
        lists = glGenLists(MAX_CHAR);
        // 把每个字符的绘制命令都装到对应的显示列表中
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    // 调用每个字符对应的显示列表，绘制每个字符
    for(; *str!='\0'; ++str)
        glCallList(lists + *str);


}



//void COpenGLDC::display()//测试用代码，没有用了
//{
////	glClear(GL_COLOR_BUFFER_BIT);
//
////	glLoadIdentity();
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glRasterPos2f(0.0f, 1.0f);
//	drawString("Hello, World!");
////	glutSwapBuffers();
//
//}

void COpenGLDC::DrawStringPos(const char *str, CPoint3D p3d)    //这应该是那三个X，Y, Z 三个轴的字母的绘制。
{
	glRasterPos3f(p3d.x, p3d.y,p3d.z);
	drawString(str);
}
