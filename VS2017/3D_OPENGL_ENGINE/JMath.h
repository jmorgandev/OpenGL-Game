#ifndef JAMIE_MATH
#define JAMIE_MATH

class Math {
public:

	static float Clamp(float value, float min, float max) {
		if (value > max) return max;
		if (value < min) return min;
		return value;
	}

	static float Wrap(float value, float min, float max) {
		if (value > max) return min;
		if (value < min) return max;
		return value;
	}

	static float Lerp(float from, float to, float percent) {
		return (from + percent*(to - from));
	}

	static int forceSign(float value) {
		if (value >= 0.0f) return 1;
		else return -1;
	}
};

#endif