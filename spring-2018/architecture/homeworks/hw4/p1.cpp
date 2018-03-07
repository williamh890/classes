
#include <avxintrin.h>
#include "osl/floats.h"

/*
 This class represents a ballistic projectile.
*/
class projectile {
public:
	float mass; // mass, kilograms
	float area; // area, square meters (for wind resistance)
	float px,py,pz; // position, in meters
	float vx,vy,vz; // velocity, in meters/second

	void step(float dt) {
		// Start with gravity
		float ax=0.0, ay=0.0, az=-9.8;

		// Add the wind resistance
		float velocity_squared=vx*vx+vy*vy+vz*vz;
		float velocity=sqrt(velocity_squared);
		const static float air_density=1.2; // kg/m^3
		const static float drag_coefficient=-0.7;

		float drag=drag_coefficient*air_density*area*velocity/mass;
		ax+=drag*vx;
        ay+=drag*vy;
        az+=drag*vz;

		// Add coriolis acceleration (rotating coordinate frame)
		const static float earth_rotation_speed=2*3.141592/(24*60*60); // radians/second
		float coriolis=-2*earth_rotation_speed; // around +X axis (north)

		ay+=coriolis*vz;
        az-=coriolis*vy;

		// Take Euler timesteps
		vx+=ax*dt;
        vy+=ay*dt;
        vz+=az*dt;

		px+=vx*dt;
        py+=vy*dt;
        pz+=vz*dt;
	}
};

long foo(void) {
	int altitude_breaches=0;
	int outta_park=0;
	int altitude_ceiling=100.0; // meters of altitude (see FAA regs)

	double start=time_in_seconds();
	const int n_firings=10000;

    projectile b1;
    b1.mass=1.5;
    b1.area=0.1*0.1;

	#pragma omp parallel for							\
		num_threads(6)									\
		schedule(dynamic, 4) 							\
		reduction(+:outta_park, altitude_breaches)
	for (int firing=0;firing<n_firings;firing++)
	{
		b1.px=0.0; b1.py=0.0; b1.pz=1.7;
		b1.vx=10.0;
		b1.vy=30.0;
		b1.vz=firing*0.01;

		//	Move the projectile until it hits the ground, or breaches the altitude limit.
		while (true)
		{
			// Check consistency
			if (b1.pz<0.0) break; // too low
			if (b1.pz>altitude_ceiling) break; // too high

			// Advance physics
			b1.step(0.01);
		}

		if (b1.pz>altitude_ceiling) altitude_breaches++;
		if (b1.py>120.0) outta_park++;
	}

	double elapsed=time_in_seconds()-start;
	std::cout<<"firing: "<<elapsed*1.0e9/n_firings<<" ns/projectile\n",
	std::cout<<"outta park: "<<outta_park*100/n_firings<<"% projectiles\n";

	return altitude_breaches*100/n_firings;
}

    px=is_everyone_done.if_then_else(new_px, px);
    py=is_everyone_done.if_then_else(new_py, py);
    pz=is_everyone_done.if_then_else(new_pz, pz);

    vx=is_everyone_done.if_then_else(new_vx, vx);
    vy=is_everyone_done.if_then_else(new_vy, vy);
    vz=is_everyone_done.if_then_else(new_vz, vz);

    ax=is_everyone_done.if_then_else(new_ax, ax);
    ay=is_everyone_done.if_then_else(new_ay, ay);
    az=is_everyone_done.if_then_else(new_az, az);

