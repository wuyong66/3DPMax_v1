#include "stdafx.h"
#include "CadBase.h"

#include "math.h"


/***********************************************************************************
/
/   CLASS NAME: CPoint2D
/	CLASS DESCRIPATION: Designed for 2 dimensional point
/   CREATED BY: Olive Wang in Apr.28,2000
/   MODIFIED BY:
*************************************************************************************/

// constructor && destructor
CPoint2D::CPoint2D()
{
	x=0.0;
	y=0.0;
}

CPoint2D::CPoint2D(double ix,double iy)
{
	x = ix;
	y = iy;
}

CPoint2D::CPoint2D(const double*p)
{
	x=p[0];
	y=p[1];
}

CPoint2D::CPoint2D(POINT2D p)
{
	x=p.x;
	y=p.y;
}

CPoint2D::~CPoint2D()
{
}


// offsetting with vector
CPoint2D CPoint2D::operator+(VECTOR2D v) const
{
	return CPoint2D(x+v.dx,y+v.dy);
}

void CPoint2D::operator+=(VECTOR2D v)
{
	x+=v.dx;
	y+=v.dy;
}

CPoint2D CPoint2D::operator-(VECTOR2D v) const
{
	return CPoint2D(x-v.dx,y-v.dy);
}

void CPoint2D::operator-=(VECTOR2D v)
{
	x+=v.dx;
	y+=v.dy;
}


// derive vector = this point - sp
CVector2D CPoint2D::operator-(POINT2D sp) const
{
	return CVector2D(x-sp.x,y-sp.y);
}

// transform the point
CPoint2D CPoint2D::operator*(const MATRIX2D& matrix) const
{
	double xx,yy,sc;
	xx = x*matrix.A[0][0]+y*matrix.A[1][0] + matrix.A[2][0];
	yy = x*matrix.A[0][1]+y*matrix.A[1][1] + matrix.A[2][1];
	sc = x*matrix.A[0][2]+y*matrix.A[1][2] + matrix.A[2][2];
	xx /= sc;
	yy /= sc;
	return CPoint2D(xx,yy);
}

void  CPoint2D::operator*=(const MATRIX2D& matrix)
{
	(*this)=(*this)*matrix;
}
/**********************************************************************************
//
//     CLASS NAME: CVector2D
//     DESCRIPTION: designed for 2 dimensional vector
//     CREATED BY: Olive Wang in April 28,2000
//     MODIFIED BY:
//
***********************************************************************************/
// constructor&&destructor
CVector2D::CVector2D()
{
	dx=0.0;
	dy=0.0;
}

CVector2D::CVector2D(double ix,double iy)
{
	dx=ix;
	dy=iy;
}

CVector2D::CVector2D(const double* pv)
{
	dx=pv[0];
	dy=pv[1];
}

CVector2D::CVector2D(VECTOR2D v)
{	
	dx=v.dx;
	dy=v.dy;
}

CVector2D::~CVector2D()
{
}

CVector2D CVector2D::operator+(VECTOR2D v) const
{
	return CVector2D(dx+v.dx,dy+v.dy);
}

CVector2D CVector2D::operator-(VECTOR2D v) const
{
	return CVector2D(dx-v.dx,dy-v.dy);
}

void CVector2D::operator+=(VECTOR2D v)
{
	dx += v.dx;
	dy += v.dy;
}

void CVector2D::operator-=(VECTOR2D v)
{
	dx-=v.dx;
	dy-=v.dy;
}

CVector2D CVector2D::operator*(double d) const
{
	return CVector2D(dx*d,dy*d);
}

void CVector2D::operator*=(double d)
{
	dx *= d;
	dy *= d;
}

CVector2D CVector2D::operator/(double d) const
{
	return CVector2D(dx/d,dy/d);
}
	
void CVector2D::operator/=(double d)
{
	dx /= d;
	dy /= d;
}

// cross product
CVector3D CVector2D::operator*(VECTOR2D v) const
{
	return CVector3D(0.0,0.0,dx*v.dy-v.dx*dy);
}
	
// dot product
double CVector2D::operator|(VECTOR2D v) const
{
	return dx*v.dx+dy*v.dy;
}


//matrix transform
CVector2D CVector2D::operator*(const MATRIX2D& matrix) const
{
	double x,y,sc;
	x = dx*matrix.A[0][0]+dy*matrix.A[1][0] + matrix.A[2][0];
	y = dx*matrix.A[0][1]+dy*matrix.A[1][1] + matrix.A[2][1];
	sc= dx*matrix.A[0][2]+dy*matrix.A[1][2] + matrix.A[2][2];
	x /= sc;
	y /= sc;
	return CVector2D(x,y);
}

void CVector2D::operator*=(const MATRIX2D& matrix)
{
	(*this)=(*this)*matrix;
}

double CVector2D::GetLength() const
{
	return sqrt(dx*dx+dy*dy);
}

CVector2D CVector2D::GetNormal() const
{
	double len = GetLength();
	return CVector2D(dx/len,dy/len);
}

void CVector2D::Normalize()
{
	double len = GetLength();
	dx = dx/len;
	dy = dy/len;
}

BOOL CVector2D::IsZeroLength() const
{
	return IS_ZERO(GetLength());
}

/***********************************************************************************
/
/   CLASS NAME: CPoint3D
/	CLASS DESCRIPATION: Designed for 2 dimensional point
/   CREATED BY: Olive Wang in Apr.28,2000
/   MODIFIED BY:
*************************************************************************************/

// constructor && destructor
CPoint3D::CPoint3D()
{
	x=0.0;
	y=0.0;
	z=0.0;
}

CPoint3D::CPoint3D(double ix,double iy,double iz)
{
	x = ix;
	y = iy;
	z = iz; 
}

CPoint3D::CPoint3D(const double*p)
{
	x=p[0];
	y=p[1];
	z=p[2];
}

CPoint3D::CPoint3D(POINT3D p)
{
	x=p.x;
	y=p.y;
	z=p.z;
}

CPoint3D::~CPoint3D()
{
}

//operators
CPoint3D CPoint3D::operator*(const MATRIX3D& matrix) const
{
	double rx,ry,rz,sc;
	rx = x * matrix.A[0][0] + y * matrix.A[1][0] + z * matrix.A[2][0] + matrix.A[3][0];
	ry = x * matrix.A[0][1] + y * matrix.A[1][1] + z * matrix.A[2][1] + matrix.A[3][1];
	rz = x * matrix.A[0][2] + y * matrix.A[1][2] + z * matrix.A[2][2] + matrix.A[3][2];
	sc = x * matrix.A[0][3] + y * matrix.A[1][3] + z * matrix.A[2][3] + matrix.A[3][3];
	rx /= sc;
	ry /= sc;
	rz /= sc;
	return CPoint3D(rx,ry,rz);
}

void  CPoint3D::operator*=(const MATRIX3D& matrix)
{
	(*this) = (*this)*matrix;
}

// offsetting with vector
CPoint3D CPoint3D::operator+(VECTOR3D v) const
{
	return CPoint3D(x+v.dx,y+v.dy,z+v.dz);
}

void CPoint3D::operator+=(VECTOR3D v)
{
	x+=v.dx;
	y+=v.dy;
	z+=v.dz;
}

CPoint3D CPoint3D::operator-(VECTOR3D v) const
{
	return CPoint3D(x-v.dx,y-v.dy,z-v.dz);
}

void CPoint3D::operator-=(VECTOR3D v)
{
	x-=v.dx;
	y-=v.dy;
	z-=v.dz;
}


// derive vector = this point - sp
CVector3D CPoint3D::operator-(POINT3D sp) const
{
	return CVector3D(x-sp.x,y-sp.y,z-sp.z);
}

BOOL CPoint3D::operator==(POINT3D pos) const
{
	CVector3D  vect(x-pos.x,y-pos.y,z-pos.z);

	if( IS_ZERO( vect.GetLength( ) ) ) return TRUE;
	else return FALSE;

}
BOOL CPoint3D::operator!=(POINT3D pos) const
{
	CVector3D  vect(x-pos.x,y-pos.y,z-pos.z);

	if( IS_ZERO( vect.GetLength( ) ) ) return FALSE;
	else return TRUE;
}


/************************************************************************************
/	
/	CLASS NAME:  CVector3D
/   DESCRIPTION: designed for 3 dimensional vector
/   CREATED BY: Olive Wang in Apr.28,2000
/   MODIFIED By:
/
************************************************************************************/
// constructor&&destructor
CVector3D::CVector3D()
{
	dx=0.0;
	dy=0.0;
	dz=0.0;
}

CVector3D::CVector3D(double ix,double iy,double iz)
{
	dx=ix;
	dy=iy;
	dz=iz;
}

CVector3D::CVector3D(const double* pv)
{
	dx=pv[0];
	dy=pv[1];
	dz=pv[2];
}

CVector3D::CVector3D(VECTOR3D v)
{	
	dx=v.dx;
	dy=v.dy;
	dz=v.dz;
}

CVector3D::~CVector3D()
{
}

CVector3D CVector3D::operator+(VECTOR3D v) const
{
	return CVector3D(dx+v.dx,dy+v.dy,dz+v.dz);
}

CVector3D CVector3D::operator-(VECTOR3D v) const
{
	return CVector3D(dx-v.dx,dy-v.dy,dz-v.dz);
}

void CVector3D::operator+=(VECTOR3D v)
{
	dx += v.dx;
	dy += v.dy;
	dz += v.dz;
}

void CVector3D::operator-=(VECTOR3D v)
{
	dx -= v.dx;
	dy -= v.dy;
	dz -= v.dz;
}

CVector3D CVector3D::operator*(double d) const
{
	return CVector3D(dx*d,dy*d,dz*d);
}

void CVector3D::operator*=(double d)
{
	dx *= d;
	dy *= d;
	dz *= d;
}

CVector3D CVector3D::operator/(double d) const
{
	return CVector3D(dx/d,dy/d,dz/d);
}
	
void CVector3D::operator/=(double d)
{
	dx /= d;
	dy /= d;
	dz /= d;
}

// cross product
CVector3D CVector3D::operator*(VECTOR3D v) const
{
	return CVector3D(dy*v.dz-v.dy*dz,v.dx*dz-dx*v.dz,dx*v.dy-v.dx*dy);
}
	
// dot product
double CVector3D::operator|(VECTOR3D v) const
{
	return dx*v.dx+dy*v.dy+dz*v.dz;
}

//methods implementation
double CVector3D::GetLength() const
{
	return sqrt(dx*dx+dy*dy+dz*dz);
}

double CVector3D::GetLengthXY() const
{
	return sqrt(dx*dx+dy*dy);
}

double CVector3D::GetLengthYZ() const
{
	return sqrt(dy*dy+dz*dz);
}

double CVector3D::GetLengthZX() const
{
	return sqrt(dx*dx+dz*dz);
}

CVector3D CVector3D::GetNormal() const
{
	double len = GetLength();
	return CVector3D(dx/len,dy/len,dz/len);
}

void CVector3D::Normalize()
{
	double len = GetLength();
	dx /= len;
	dy /= len;
	dz /= len;
}

BOOL CVector3D::IsZeroLength() const
{
	return IS_ZERO(GetLength());
}

CVector3D CVector3D::operator*(const MATRIX3D& matrix) const
{
	double rx,ry,rz,sc;
	rx = dx * matrix.A[0][0] + dy * matrix.A[1][0] + dz * matrix.A[2][0] + matrix.A[3][0];
	ry = dx * matrix.A[0][1] + dy * matrix.A[1][1] + dz * matrix.A[2][1] + matrix.A[3][1];
	rz = dx * matrix.A[0][2] + dy * matrix.A[1][2] + dz * matrix.A[2][2] + matrix.A[3][2];
	sc = dx * matrix.A[0][3] + dy * matrix.A[1][3] + dz * matrix.A[2][3] + matrix.A[3][3];
	rx /= sc;
	ry /= sc;
	rz /= sc;
	return CVector3D(rx,ry,rz);
}

void  CVector3D::operator*=(const MATRIX3D& matrix)
{
	(*this) = (*this)*matrix;
}

/************************************************************************************
/	
/	CLASS NAME:  CMatrix2D
/   DESCRIPTION: designed for 2*2 dimensional matrix
/   CREATED BY: Olive Wang in Apr.28,2000
/   MODIFIED By:
/
************************************************************************************/

//construction&&destruction
CMatrix2D::CMatrix2D()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++){
			if(i==j)
				A[i][j] = 1.0;
			else
				A[i][j] = 0.0;
		}
}

CMatrix2D::CMatrix2D(const MATRIX2D& matrix)
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			A[i][j]=matrix.A[i][j];
}

CMatrix2D::CMatrix2D(const double* matrix)
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			A[i][j]=matrix[i*3+j];
}


CMatrix2D::~CMatrix2D()
{
}

//operators
CMatrix2D CMatrix2D::operator*(const MATRIX2D& matrix2) const
{
	CMatrix2D matrix;
	for(int i=0;i<3;i++)
	for(int j=0;j<3;j++){
		matrix.A[i][j] = A[i][0]*matrix2.A[0][j]
					   + A[i][1]*matrix2.A[1][j]
					   + A[i][2]*matrix2.A[2][j];
	}
	return matrix;
}

void CMatrix2D::operator*=(const MATRIX2D& matrix2)
{
	(*this)=(*this)*matrix2;
}

//methods
void CMatrix2D::IdenticalMatrix()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++){
			if(i==j)
				A[i][j] = 1.0;
			else
				A[i][j] = 0.0;
		}
}

double CMatrix2D::GetValue() const
{
	return A[0][0]*A[1][1]-A[0][1]*A[1][0];
}

// static member functions
double CMatrix2D::GetValue(double a00, double a01,
			   double a10, double a11)
{
	return a00*a11-a01*a10;
}

CMatrix2D CMatrix2D::CreateMirrorMatrix(VECTOR2D v)
{
	double len=((CVector2D)v).GetLength();
	CMatrix2D matrix;
	matrix.A[0][0]=(v.dx*v.dx - v.dy*v.dy)/len;
	matrix.A[0][1]=2.0*(v.dx*v.dy)/len;
	matrix.A[1][0]=2.0*(v.dx*v.dy)/len;
	matrix.A[1][1]= -matrix.A[0][0];
	return matrix;
}

CMatrix2D CMatrix2D::CreateRotateMatrix(double angle)
{
	CMatrix2D m;
	m.A[0][0]=m.A[1][1]=cos(angle);
	m.A[0][1]=sin(angle);m.A[1][0]= -sin(angle);
	return m;
}

CMatrix2D CMatrix2D::CreateScaleMatrix(double d)
{
	CMatrix2D m;
	m.A[0][0]=m.A[1][1]=d;
	return m;
}

CMatrix2D CMatrix2D::CreateTransfMatrix(VECTOR2D vec)
{
	CMatrix2D m;
	m.A[2][0]=vec.dx;
	m.A[2][1]=vec.dy;
	return m;
}

/************************************************************************************
/	
/	CLASS NAME: CMatrix3D
/   DESCRIPTION: designed for 3 dimensional matrix
/   CREATED BY: Olive Wang in Apr.28,2000
/   MODIFIED By:
/
************************************************************************************/

//construction&&destruction
CMatrix3D::CMatrix3D()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			A[i][j] = (i==j)?1.0:0.0;
		}
}

CMatrix3D::CMatrix3D(const MATRIX3D& matrix)
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			A[i][j] = matrix.A[i][j];
		}
}

CMatrix3D::CMatrix3D(const double *matrix)
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			A[i][j] = matrix[i*4+j];
		}
}

CMatrix3D::~CMatrix3D()
{
}

//operators
CMatrix3D CMatrix3D::operator*(const MATRIX3D& matrix2) const
{ 
	CMatrix3D matrix;
	for(int i=0;i<4;i++)
	for(int j=0;j<4;j++){
		matrix.A[i][j] = A[i][0]*matrix2.A[0][j]
					   + A[i][1]*matrix2.A[1][j]
					   + A[i][2]*matrix2.A[2][j]
					   + A[i][3]*matrix2.A[3][j];
	}
	return matrix;
}

void CMatrix3D::operator*=(const MATRIX3D& matrix)
{
	(*this) = (*this)*matrix;
}

//methods
void CMatrix3D::IdenticalMatrix()
{
	for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
	{
		A[i][j] = (i==j)?1.0:0.0;
	}
}

double CMatrix3D::GetValue() const
{
	return  A[0][0]*A[1][1]*A[2][2] +
			A[0][1]*A[1][2]*A[2][0] +
			A[0][2]*A[1][0]*A[2][1] -
			A[0][2]*A[1][1]*A[2][0] -
			A[0][1]*A[1][0]*A[2][2] -
			A[0][0]*A[1][2]*A[2][1];
}

// static member functions
double CMatrix3D::GetValue(double a00, double a01, double a02,
			                  double a10, double a11, double a12,
			                  double a20, double a21, double a22)
{
	return  a00*a11*a22 +
			a01*a12*a20 +
			a02*a10*a21 -
			a02*a11*a20 -
			a01*a10*a22 -
			a00*a12*a21;
}

CMatrix3D CMatrix3D::CreateMirrorMatrix(VECTOR3D v)
{
	double len=((CVector3D)v).GetLength();
	CMatrix3D matrix;
	matrix.A[0][0]= (v.dx*v.dx -1.0)*2.0/len/len;
	matrix.A[1][1]= (v.dy*v.dy -1.0)*2.0/len/len;
	matrix.A[2][2]= (v.dz*v.dz -1.0)*2.0/len/len;
	matrix.A[0][1]=matrix.A[1][0]= v.dx*v.dy*2.0/len/len;
	matrix.A[0][2]=matrix.A[2][0]= v.dx*v.dz*2.0/len/len;
	matrix.A[1][2]=matrix.A[2][1]= v.dz*v.dy*2.0/len/len;
	return matrix;
}

CMatrix3D CMatrix3D::CreateRotateMatrix(double da,VECTOR3D v)
{
	CMatrix3D R;
	CVector3D bv(v);

	if(IS_ZERO(da))	return R;

	ASSERT(!bv.IsZeroLength());

	double lxy=bv.GetLengthXY();
	if(IS_ZERO(lxy))
	{
		if(bv.dz < 0.0) da *= -1.0;
		R.A[0][0]=R.A[1][1]=cos(da);
		R.A[0][1]=sin(da);R.A[1][0]=-sin(da);
		return R;
	}
	double lyz=bv.GetLengthYZ();
	if(IS_ZERO(lyz))
	{
		if(bv.dx < 0.0) da *= -1.0;
		R.A[2][2]=R.A[1][1]=cos(da);
		R.A[1][2]=sin(da);R.A[2][1]= -sin(da);
		return R;
	}
	double lxz=bv.GetLengthZX();
	if(IS_ZERO(lxz))
	{
		if(bv.dy < 0.0) da *= -1.0;
		R.A[0][0]=R.A[2][2]=cos(da);
		R.A[0][2]=-sin(da);R.A[2][0]=sin(da);
		return R;
	}

	CMatrix3D Rz;
	Rz.A[0][0]=Rz.A[1][1]=bv.dy/lxy;
	Rz.A[0][1]=bv.dx/lxy;Rz.A[1][0]= -bv.dx/lxy;

	double len=bv.GetLength();
	CMatrix3D Rx;
	Rx.A[2][2]=Rx.A[1][1]=bv.dz/len;
	Rx.A[1][2]=lxy/len;Rx.A[2][1]= -lxy/len;

	R.A[0][0]=R.A[1][1]=cos(da);
	R.A[0][1]=sin(da);R.A[1][0]= -sin(da);
	
	CMatrix3D Rxn;
	Rxn.A[2][2]=Rxn.A[1][1]=bv.dz/len;
	Rxn.A[2][1]=lxy/len;Rxn.A[1][2]= -lxy/len;

	CMatrix3D Rzn;
	Rzn.A[0][0]=Rzn.A[1][1]=bv.dy/lxy;
	Rzn.A[1][0]=bv.dx/lxy;Rzn.A[0][1]= - bv.dx/lxy;

	return Rz*Rx*R*Rxn*Rzn;
}

CMatrix3D CMatrix3D::CreateScaleMatrix(double d)
{
	CMatrix3D m;
	m.A[0][0]=m.A[1][1]=m.A[2][2]=d;
	return m;
}

CMatrix3D CMatrix3D::CreateTransfMatrix(VECTOR3D vec)
{
	CMatrix3D m;
	m.A[3][0]=vec.dx;
	m.A[3][1]=vec.dy;
	m.A[3][2]=vec.dz;
	return m;
}


////////////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  CBox2D
//
//
//
/////////////////////////////////////////////////////////////////////////////////////
//constructor && destructor
CBox2D::CBox2D()
{
	x0=y0=x1=y1=0;
}

CBox2D::CBox2D(double ix0,double iy0,double ix1,double iy1)
{
	x0 = ix0; y0=iy0; x1=ix1; y1=iy1;
	normalize();
}

CBox2D::CBox2D(POINT2D pt0,POINT2D pt1)
{
	x0 = pt0.x; y0=pt0.y; x1=pt1.x; y1=pt1.y;
	normalize();
}

CBox2D::CBox2D(BOX2D b)
{
	x0=b.x0; y0=b.y0;
	x1=b.x1; y1=b.y1;
	normalize();
}

CBox2D::CBox2D(POINT2D p,VECTOR2D v)
{
	x0=p.x; y0=p.y;
	x1=p.x+v.dx;
	y1=p.x+v.dy;
	normalize();
}

CBox2D::~CBox2D()
{
}

// operator
//// get the union box of this and box b.
CBox2D CBox2D::operator+(BOX2D b) const
{
	CBox2D box;
	box.x0 = (x0<b.x0)?x0:b.x0;
	box.y0 = (y0<b.y0)?y0:b.y0;
	box.x1 = (x1>b.x1)?x1:b.x1;
	box.y1 = (y1>b.y1)?y1:b.y1;
	return box;
}

void CBox2D::operator+=(BOX2D b)
{
	CBox2D box = (*this)+b;
	(*this) = box;
}

//// get the intersect box of this and box b.
CBox2D CBox2D::operator&(BOX2D b) const
{
	CBox2D box;
	double xx0,yy0,xx1,yy1;
	xx0 = (x0>b.x0)?x0:b.x0;
	yy0 = (y0>b.y0)?y0:b.y0;
	xx1 = (x1<b.x1)?x1:b.x1;
	yy1 = (y1<b.y1)?y1:b.y1;
	if((xx1>xx0) && (yy1>yy0)){
		box = CBox2D(xx0,yy0,xx1,yy1);
	}
	return box;
}

void CBox2D::operator&=(BOX2D b)
{
	CBox2D box = (*this)&b;
	*this = box;
}

// get attribs
BOOL CBox2D::IsZero() const
{
	return IS_ZERO(Width()*Height());
}

double CBox2D::Width() const // Length of X direction
{
	return x1-x0;
}

double CBox2D::Height() const // Length of Y direction
{
	return y1-y0;
}

// relationship culation
// there may be four cases:
// <enumSeparated,enumIntersected>
UINT CBox2D::GetRelationWith(BOX2D b) const
{
	CBox2D box;
	box = (*this)&b;
	if(box.IsZero())
		return enumSeparated;
	else
		return enumIntersected;
}

void CBox2D::normalize()
{
	double xx0,yy0,xx1,yy1;
	xx0 = (x0<x1)?x0:x1;
	xx1 = (x0>x1)?x0:x1;
	yy0 = (y0<y1)?y0:y1;
	yy1 = (y0>y1)?y0:y1;
	x0 = xx0; y0 = yy0; x1 = xx1; y1 = yy1;
}

////////////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  CBox3D
//
//
//
/////////////////////////////////////////////////////////////////////////////////////
//constructor && destructor
CBox3D::CBox3D()
{
	x0=y0=z0=x1=y1=z1=0;
}

CBox3D::CBox3D(double ix0,double iy0,double iz0,double ix1,double iy1, double iz1)
{
	x0 = ix0; y0=iy0; z0=iz0;x1=ix1; y1=iy1;z1=iz1;
	normalize();
}

CBox3D::CBox3D(POINT3D pt0,POINT3D pt1)
{
	x0 = pt0.x; y0=pt0.y; z0=pt0.z;x1=pt1.x; y1=pt1.y;z1=pt1.z;
	normalize();
}

CBox3D::CBox3D(BOX3D b)
{
	x0=b.x0; y0=b.y0;z0=b.z0;
	x1=b.x1; y1=b.y1;z1=b.z1;
	normalize();
}

CBox3D::CBox3D(POINT3D p,VECTOR3D v)
{
	x0=p.x; y0=p.y; z0=p.z;
	x1=p.x+v.dx;
	y1=p.x+v.dy;
	z1=p.x+v.dz;
	normalize();
}

CBox3D::~CBox3D()
{
}

// operator
//// get the union box of this and box b.//或得a和b中的最小点和最大点
CBox3D CBox3D::operator+(BOX3D b) const
{
	CBox3D box = *this;

	if( ((CBox3D)b).IsEmpty( ) ) return  box;
	if( IsEmpty( ) ) return b;

	box.x0 = (x0<b.x0)?x0:b.x0;
	box.y0 = (y0<b.y0)?y0:b.y0;
	box.z0 = (z0<b.z0)?z0:b.z0;
	box.x1 = (x1>b.x1)?x1:b.x1;
	box.y1 = (y1>b.y1)?y1:b.y1;
	box.z1 = (z1>b.z1)?z1:b.z1;

	return box;
}

void CBox3D::operator*= ( double sc )
{
	x0 = x0*sc;
	y0 = y0*sc;
	z0 = z0*sc;
	x1 = x1*sc;
	y1 = y1*sc;
	z1 = z1*sc;
}

CBox3D CBox3D::operator*( const MATRIX3D& matrix ) const
{
	CPoint3D p0(x0,y0,z0);
	CPoint3D p1(x1,y1,z1);

	p0 *= matrix;
	p1 *= matrix;

	return 	CBox3D(p0,p1);
}

void CBox3D::operator*=(const MATRIX3D& matrix )
{
	(*this) = (*this)*matrix;
}

CBox3D CBox3D::operator*( double sc ) const
{
	CBox3D box;
	box.x0 = x0*sc;
	box.y0 = y0*sc;
	box.z0 = z0*sc;
	box.x1 = x1*sc;
	box.y1 = y1*sc;
	box.z1 = z1*sc;
	return box;
}

void CBox3D::operator+=(BOX3D b)
{
	CBox3D box = (*this)+b;
	(*this) = box;
}

//// get the intersect box of this and box b.
CBox3D CBox3D::operator&(BOX3D b) const
{
	CBox3D box;

	if( ((CBox3D)b).IsEmpty( ) || ((CBox3D *)this)->IsEmpty( ) ) return box;

	double xx0,yy0,zz0,xx1,yy1,zz1;
	xx0 = (x0>b.x0)?x0:b.x0;
	yy0 = (y0>b.y0)?y0:b.y0;
	zz0 = (z0>b.z0)?z0:b.z0;
	xx1 = (x1<b.x1)?x1:b.x1;
	yy1 = (y1<b.y1)?y1:b.y1;
	zz1 = (z1<b.z1)?z1:b.z1;
	if((xx1>xx0) && (yy1>yy0) && (zz1>zz0)){
		box = CBox3D(xx0,yy0,zz0,xx1,yy1,zz1);
	}
	return box;
}

void CBox3D::operator&=(BOX3D b)
{
	CBox3D box = (*this)&b;
	*this = box;
}

BOOL CBox3D::operator<<(BOX3D  b) const
{
	if( IsEmpty( ) ) return TRUE;

	if( (x0 >= b.x0) && (y0 >= b.y0) && (z0 >= b.z0) &&
		(x1 <= b.x1) && (y1 <= b.y1) && (z1 <= b.z1)  ) return TRUE;
	else
		return FALSE;
}

BOOL CBox3D::operator>>(BOX3D b) const
{
	if( ((CBox3D)b).IsEmpty( ) ) return TRUE;

	if( (x0 >= b.x0) && (y0 >= b.y0) && (z0 >= b.z0) &&
		(x1 <= b.x1) && (y1 <= b.y1) && (z1 <= b.z1)  ) return FALSE;
	else
		return TRUE;
}

BOOL CBox3D::operator>>(POINT3D p) const
{
	if( (x0 <= p.x) && (y0 <= p.y) && (z0 <= p.z) &&
		(x1 >= p.x) && (y1 >= p.y) && (z1 >= p.z)  ) return TRUE;
	else
		return FALSE;
}

//// get the intersect box of this and box b.得到相交的那一部分
CBox3D CBox3D::operator|(BOX3D b) const//返回最大范围的BOX
{
	CBox3D box;

	if( ((CBox3D *)this)->IsEmpty( ) ) {
		box = b;
		return box;
	}
	if( ((CBox3D)b).IsEmpty( ) ) {
		box = *this;
		return box;
	}

	double xx0,yy0,zz0,xx1,yy1,zz1;
	xx0 = (x0<b.x0)?x0:b.x0;
	yy0 = (y0<b.y0)?y0:b.y0;
	zz0 = (z0<b.z0)?z0:b.z0;
	xx1 = (x1>b.x1)?x1:b.x1;
	yy1 = (y1>b.y1)?y1:b.y1;
	zz1 = (z1>b.z1)?z1:b.z1;
	if((xx1>=xx0) && (yy1>=yy0) && (zz1>=zz0)){
		box = CBox3D(xx0,yy0,zz0,xx1,yy1,zz1);
	}
	return box;
}

void CBox3D::operator|=(BOX3D b)
{
	CBox3D box = (*this)|b;
	*this = box;
}

// get attribs
BOOL CBox3D::IsEmpty() const
{
	return	IS_ZERO(Width()) &&
			IS_ZERO(Height()) &&
			IS_ZERO(Length());
}

double CBox3D::Width() const // Length of X direction
{
	return x1-x0;
}

double CBox3D::Height() const // Length of Z direction
{
	return z1-z0;
}
double CBox3D::Length() const // Length of Z direction
{
	return y1-y0;
}

// relationship culation
// there may be four cases:
// <enumSeparated,enumIntersected>
UINT CBox3D::GetRelationWith(BOX3D b) const
{
	CBox3D box;
	box = (*this)&b;
	if(box.IsEmpty())
		return enumSeparated;
	else
		return enumIntersected;
}

void CBox3D::normalize()
{
	double xx0,yy0,xx1,yy1,zz0,zz1;
	xx0 = (x0<x1)?x0:x1;
	xx1 = (x0>x1)?x0:x1;
	yy0 = (y0<y1)?y0:y1;
	yy1 = (y0>y1)?y0:y1;
	zz0 = (z0<z1)?z0:z1;
	zz1 = (z0>z1)?z0:z1;
	x0 = xx0; y0 = yy0; x1 = xx1; y1 = yy1;
	z0 = zz0; z1 = zz1;
}

CBox3D CBox3D::operator+(VECTOR3D vect) const
{
	CBox3D box;

	box.x0 = x0+vect.dx;
	box.y0 = y0+vect.dy;
	box.z0 = z0+vect.dz;
	box.x1 = x1+vect.dx;
	box.y1 = y1+vect.dy;
	box.z1 = z1+vect.dz;
	
	return box;
}

void CBox3D::operator+=(VECTOR3D vect)
{
	x0 = x0+vect.dx;
	y0 = y0+vect.dy;
	z0 = z0+vect.dz;
	x1 = x1+vect.dx;
	y1 = y1+vect.dy;
	z1 = z1+vect.dz;	
}

CBox3D CBox3D::operator-(VECTOR3D vect) const
{
	CBox3D box;

	box.x0 = x0-vect.dx;
	box.y0 = y0-vect.dy;
	box.z0 = z0-vect.dz;
	box.x1 = x1-vect.dx;
	box.y1 = y1-vect.dy;
	box.z1 = z1-vect.dz;
	
	return box;
}

void CBox3D::operator-=(VECTOR3D vect)
{
	x0 = x0-vect.dx;
	y0 = y0-vect.dy;
	z0 = z0-vect.dz;
	x1 = x1-vect.dx;
	y1 = y1-vect.dy;
	z1 = z1-vect.dz;
}
