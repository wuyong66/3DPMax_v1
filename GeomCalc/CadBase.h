#ifndef _CAD_DEF_H_
#define _CAD_DEF_H_

#include <math.h>
#include <afxtempl.h>
//此工程，定义了画图过程中可能遇到的集合对象，二维点，二维的BOX（两个二维点），
//三维点，三维的BOX（两个三维点），以及一个三维，一个四维矩阵
//最重要的是，在几何对象的定义中，重载了&，&=，*，*=，+，+=，-，-=，<<，>>,|,|=等运算符
//在矩阵的定义中，定义了求镜像、旋转、缩放、平移，的矩阵变换函数，以及求矩阵的秩等。


#define CAD_ZERO		1.0E-6
#define NC_ZERO		1.0E-3
#define IS_ZERO(x)		(fabs(x)<=CAD_ZERO)
#define IS_NCZERO(x)		(fabs(x)<=NC_ZERO)
#define IS_BETWEEN(x,min,max) (x<=max && x>=min)
#define PI	3.1415926535

typedef struct tagPoint2D{
	double x; 
	double y;
} POINT2D, *PPOINT2D;

typedef struct tagVector2D{
	double dx;
	double dy;
} VECTOR2D,*PVECTOR2D;

typedef struct tagPoint3D{
	double x;
	double y;
	double z;
} POINT3D, *PPOINT3D;

typedef struct tagVector3D{
	double dx;
	double dy;
	double dz;
} VECTOR3D,*PVECTOR3D;

typedef struct tagMatrix2D{
	double A[3][3];
} MATRIX2D, *PMATRIX2D;

typedef struct  tagMatrix3D{
	double A[4][4];
} MATRIX3D, *PMATRIX3D;

class CPoint2D;
class CPoint3D;
class CVector2D;
class CVector3D;
class CMatrix2D;
class CMatrix3D;

class CPoint2D :public POINT2D
{
public:
	CPoint2D();
	CPoint2D(double ix,double iy);
	CPoint2D(const double*);
	CPoint2D(POINT2D p);
	~CPoint2D();

public:
	//operators
	CPoint2D operator*(const MATRIX2D& matrix) const;
	void  operator*=(const MATRIX2D& matrix);

	//offsetting with vector
	CPoint2D operator+(VECTOR2D v) const;
	void operator+=(VECTOR2D v);
	CPoint2D operator-(VECTOR2D v) const;
	void operator-=(VECTOR2D v);

	//derived vector = this point - sp
	CVector2D operator-(POINT2D sp) const;
} ;

// Intersection Point structure
typedef struct tagInterPOINT2D{
	CPoint2D interPt;
	double t0;
	double t1;
} INTERPOINT2D,*PINTERPOINT2D;

class CVector2D : public VECTOR2D  
{
public:
	CVector2D();
	CVector2D(double ix,double iy=0.0);
	CVector2D(const double* pv);
	CVector2D(VECTOR2D v);
	virtual ~CVector2D();

public:
	//operators declaration
	CVector2D operator+(VECTOR2D v) const;
	CVector2D operator-(VECTOR2D v) const;
	void operator+=(VECTOR2D v);
	void operator-=(VECTOR2D v);
	CVector2D operator*(double d) const;
	void operator*=(double d);
	CVector2D operator/(double d) const;
	void operator/=(double d);

	// cross product
	CVector3D operator*(VECTOR2D v) const;
	
	// dot product
	double operator|(VECTOR2D v) const;

	//matrix transformation
    CVector2D operator*(const MATRIX2D& matrix ) const;
    void operator*=(const MATRIX2D& matrix );

	//methods declaration
	double GetLength()const;
	CVector2D GetNormal()const;
	void Normalize();
	BOOL   IsZeroLength() const;
};

class  CPoint3D :public POINT3D
{
public:
	CPoint3D();
	CPoint3D(double ix,double iy,double iz=0.0);
	CPoint3D(const double*);
	CPoint3D(POINT3D p);
	~CPoint3D();

public:
	//operators
	CPoint3D operator*(const MATRIX3D& matrix) const;
	void  operator*=(const MATRIX3D& matrix);

	//offsetting with vector
	CPoint3D operator+(VECTOR3D v) const;
	void operator+=(VECTOR3D v);
	CPoint3D operator-(VECTOR3D v) const;
	void operator-=(VECTOR3D v);

	BOOL operator==(POINT3D pos) const;
	BOOL operator!=(POINT3D pos) const;

	//derived vector = this point - sp
	CVector3D operator-(POINT3D sp) const;
} ;

class  CVector3D: public VECTOR3D
{
public:
	CVector3D();
	CVector3D(double dx,double dy,double dz=0);
	CVector3D(const double*);
	CVector3D(VECTOR3D v);
	virtual ~CVector3D();

	//operator
	CVector3D operator+(VECTOR3D v) const;
	void operator+=(VECTOR3D v);
	CVector3D operator-(VECTOR3D v) const;
	void operator-=(VECTOR3D v);

	CVector3D operator*(double d) const;
	void operator*=(double d);
	CVector3D operator/(double d) const;
	void operator/=(double d);

	//cross product
	CVector3D operator*(VECTOR3D v) const;
	
	//dot product
	double operator|(VECTOR3D v) const;

	CVector3D operator*(const MATRIX3D& matrix) const;
	void  operator*=(const MATRIX3D& matrix);

	//length
	double GetLength() const;
	double GetLengthXY() const;
	double GetLengthYZ() const;
	double GetLengthZX() const;
	
	CVector3D	GetNormal() const;
	void		Normalize();
	BOOL		IsZeroLength() const;
};


class  CMatrix2D : public MATRIX2D
{
public:
	CMatrix2D();
	CMatrix2D(const MATRIX2D&);
	CMatrix2D(const double *);
	virtual ~CMatrix2D();

	//operators
	CMatrix2D operator*(const MATRIX2D&) const;
	void operator*=(const MATRIX2D&);

	//methods
	void	IdenticalMatrix();
	double	GetValue() const;
public:
	// static member functions
	static double GetValue(double a00, double a01,
						   double a10, double a11);
	static CMatrix2D CreateMirrorMatrix(VECTOR2D vect);
	static CMatrix2D CreateRotateMatrix(double angle);
	static CMatrix2D CreateScaleMatrix(double);
	static CMatrix2D CreateTransfMatrix(VECTOR2D vect);
} ; 

class  CMatrix3D : public MATRIX3D
{
public:
	CMatrix3D();
	CMatrix3D(const MATRIX3D&);
	CMatrix3D(const double *);
	virtual ~CMatrix3D();
public:
	//operators
	CMatrix3D operator*(const MATRIX3D& matrix)const;
	void operator*=(const MATRIX3D& matrix);

	//methods
	void   IdenticalMatrix();
	double GetValue() const;

public:
	// static member functions
	static double GetValue(double a00, double a01, double a02,
						   double a10, double a11, double a12,
						   double a20, double a21, double a22);
	static CMatrix3D CreateMirrorMatrix(VECTOR3D plnNorm);
	static CMatrix3D CreateRotateMatrix(double da,VECTOR3D bv);
	static CMatrix3D CreateScaleMatrix(double);
	static CMatrix3D CreateTransfMatrix(VECTOR3D vec);
} ; 

//////////////////////////////////////////////////////////////////////////
//  (x0,y0): the left and bottom corner
//  (x1,y1): the right and top corner
//////////////////////////////////////////////////////////////////////////
typedef struct tagBox2D{
	double x0;
	double y0;
	double x1;
	double y1;
} BOX2D , *PBOX2D;

class  CBox2D : public BOX2D
{

//constructor && destructor
public:
	CBox2D();
	CBox2D(double ix0,double iy0,double ix1,double iy1);
	CBox2D(POINT2D pt0,POINT2D pt1);
	CBox2D(BOX2D b);
	CBox2D(POINT2D p,VECTOR2D v);
	virtual ~CBox2D();

// operator
public:
//// get the union box of this and box b.
	CBox2D operator+(BOX2D b) const;
	void operator+=(BOX2D b);

//// get the intersect box of this and box b.
	CBox2D operator&(BOX2D b) const;
	void operator&=(BOX2D b);

// get attribs
public:
	BOOL   IsZero() const;
	double Width() const;		// Length of X direction
	double Height()const;		// Length of Y direction

// relationship culation
public:
	enum {enumSeparated,enumIntersected};
	UINT GetRelationWith(BOX2D b) const;
protected:
	void normalize();
};

//////////////////////////////////////////////////////////////////////////
//  (x0,y0): the left and bottom corner
//  (x1,y1): the right and top corner
//////////////////////////////////////////////////////////////////////////
typedef struct tagBox3D{
	double x0;
	double y0;
	double z0;
	double x1;
	double y1;
	double z1;
} BOX3D , *PBOX3D;

class  CBox3D : public BOX3D
{

//constructor && destructor
public:
	CBox3D();
	CBox3D(double ix0,double iy0,double iz0, double ix1,double iy1, double iz1);
	CBox3D(POINT3D pt0,POINT3D pt1);
	CBox3D(BOX3D b);
	CBox3D(POINT3D p,VECTOR3D v);
	virtual ~CBox3D();

// operator
public:
//// get the union box of this and box b.
	CBox3D operator+(BOX3D b) const;
	void operator+=(BOX3D b);

//// get the intersect box of this and box b.
	CBox3D operator&(BOX3D b) const;
	void operator&=(BOX3D b);
	CBox3D operator*( double sc ) const;
	void operator*= ( double sc );
	CBox3D operator*( const MATRIX3D& matrix ) const;
	void operator*= ( const MATRIX3D& matrix );
	BOOL operator<< ( BOX3D b )const ;
	BOOL operator>> ( BOX3D b ) const;
	BOOL operator>> ( POINT3D p ) const;
	CBox3D operator|(BOX3D b) const;
	void operator|=(BOX3D b);

	CBox3D operator+(VECTOR3D vect) const;
	void operator+=(VECTOR3D vect);
	CBox3D operator-(VECTOR3D vect)const;
	void operator-=(VECTOR3D vect);

// get attribs
	BOOL	IsEmpty() const;
	double	Width() const;	 //// Length of X direction
	double	Height() const; //// Length of Z direction
	double	Length( )const; //// Length of Y direction

	enum {enumSeparated,enumIntersected};
	UINT GetRelationWith(BOX3D b) const;

protected:
	void normalize();
};

// exported API functions
double	 _AngleBetween(VECTOR2D v1,VECTOR2D v2);  //
double	 _AngleBetween(VECTOR3D v1,VECTOR3D v2);
double	 _DistOf(POINT2D pt0, POINT2D pt1);
double	 _DistOf(POINT3D pt0, POINT3D pt1);
BOOL	 _IsParallel(VECTOR2D v0,VECTOR2D v1);
BOOL	 _IsParallel(VECTOR3D v0,VECTOR3D v1);
BOOL	 _IsOrthogonal(VECTOR3D v0,VECTOR3D v1);
#endif