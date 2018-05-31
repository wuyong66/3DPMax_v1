#include "stdafx.h"
#include "CadBase.h"
#include "math.h"


double _AngleBetween(VECTOR2D v1,VECTOR2D v2)
{
	if(_IsParallel(v1,v2))	return 0;
	CVector2D cv1(v1),cv2(v2);
	return acos((cv1|cv2.GetNormal())/cv1.GetLength());
}

double _AngleBetween(VECTOR3D v1,VECTOR3D v2)
{
	if(_IsParallel(v1,v2))	return 0;
	CVector3D cv1(v1),cv2(v2);
	return acos((cv1|cv2.GetNormal())/cv1.GetLength());
}

double _DistOf(POINT2D pt0,POINT2D pt1)
{
	CVector2D vec(pt1.x-pt0.x,pt1.y-pt0.y);
	return vec.GetLength();
}

double _DistOf(POINT3D pt0,POINT3D pt1)
{
	CVector3D vec(pt1.x-pt0.x,pt1.y-pt0.y);
	return vec.GetLength();
}

BOOL _IsParallel(VECTOR2D v0,VECTOR2D v1)
{
	CVector2D cv0(v0),cv1(v1);
	return IS_ZERO((cv0*cv1).dz);
}

BOOL _IsParallel(VECTOR3D v0,VECTOR3D v1)//返回两个向量相乘的双浮点数的长度？
{										 //明明是返回判断是否乘积是否为零，即是否平行
	CVector3D cv0(v0),cv1(v1);
	return IS_ZERO((cv0*cv1).GetLength());
}

BOOL _IsOrthogonal(VECTOR3D v0,VECTOR3D v1)
{
	CVector3D cv0(v0),cv1(v1);
	return IS_ZERO(cv0|cv1);
}
