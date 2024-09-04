#ifndef STEERING_OUTPUT_H
#define STEERING_OUTPUT_H

#include <Vector.h>
using namespace MATH;

class SteeringOutput
{
public:
	// Yes these are public! 
	// The steering algorithms will be creating instances and then setting the values.
	// There might be a better way, but I can't think of it right now.
	// This class does not have any behaviours, just constructors!

	Vec3 linear;
	float angular;

	SteeringOutput() {
		linear = Vec3(0, 0, 0);
		angular = 0.0f;
	}
	SteeringOutput( Vec3 linear_, float angular_ ) {
		linear = linear_;
		angular = angular_;
	}
	inline const SteeringOutput operator + ( const SteeringOutput& v ) const {
		return SteeringOutput( linear + v.linear, angular + v.angular );
	}
	inline SteeringOutput& operator += ( const SteeringOutput& v ) {
		linear += v.linear;
		angular += v.angular;
		return *this;
	}
};
#endif
