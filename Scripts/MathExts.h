#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

namespace KrostganEngine {

	static inline const double Rad2DegCoef = 180 / M_PI;

	static double Deg2Rad(double radian) {
		return radian / Rad2DegCoef;
	}
	static double Rad2Deg(double degress) {
		return degress * Rad2DegCoef;
	}
}