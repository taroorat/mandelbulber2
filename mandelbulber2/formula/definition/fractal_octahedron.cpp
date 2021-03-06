/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * reference: eiifie paxis2 https://www.shadertoy.com/view/XlSGDc
 * paxis idea from dila originally at https://www.shadertoy.com/view/Xlj3DK
 */

#include "all_fractal_definitions.h"

cFractalOctahedron::cFractalOctahedron() : cAbstractFractal()
{
	nameInComboBox = "Octahedron";
	internalName = "octahedron";
	internalID = fractal::octahedron;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalOctahedron::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 a;
	double b = 1.0;
	double d;
	double limitA = fractal->transformCommon.offset0;
	double limitB = fractal->transformCommon.offsetA0;

	for (int i = 0; i < fractal->transformCommon.int3X; i++)
	{
		double sizer1 = fractal->transformCommon.scale1 * b;
		a = fabs(z);
		z.x -= sign(z.x) * max(double(sign(a.x - max(a.y, a.z))), limitA) * sizer1;
		z.y -= sign(z.y) * max(double(sign(a.y - max(a.z, a.x))), limitA) * sizer1;
		z.z -= sign(z.z) * max(double(sign(a.z - max(a.x, a.y))), limitA) * sizer1;
		b *= fractal->transformCommon.scale05;
	}

	 d = z.Length() - fractal->transformCommon.minR2p25;
	for (int i = 0; i < fractal->transformCommon.int3Y; i++)
	{
		double sizer2 = fractal->transformCommon.scaleA1 * b;
		 a = fabs(z);
		z.x -= sign(z.x) * max(double(sign(a.x - min(a.y, a.z))), limitB) * sizer2;
		z.y -= sign(z.y) * max(double(sign(a.y - min(a.z, a.x))), limitB) * sizer2;
		z.z -= sign(z.z) * max(double(sign(a.z - min(a.x, a.y))), limitB) * sizer2;
		b *= fractal->transformCommon.minR05;
	}
	z = fractal->transformCommon.rotationMatrix.RotateVector(z);
	a = fabs(z);
	double d2;

	if (!fractal->transformCommon.functionEnabledFalse)
		d2 = max(a.x, max(a.y, a.z)) - b;
	else
		d2 = a.Length() - b;

	 d2 = max(d2, -d);
	 //aux.dist = d2;

	if (!fractal->transformCommon.functionEnabledAFalse) aux.dist = d2;
	else aux.dist = min(aux.dist, d2);
}
