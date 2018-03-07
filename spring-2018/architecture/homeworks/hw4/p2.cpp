#include <avxintrin.h>
#include "osl/floats.h"

/*
 This class represents a ballistic projectile.
*/
class projectile {
public:
	floats mass; // mass, kilograms
	floats area; // area, square meters (for wind resistance)
	floats px,py,pz; // position, in meters
	floats vx,vy,vz; // velocity, in meters/second
	floats dt;
	floats offsets;
	bool is_not_done;

	void step() {
		bools keep_going = (pz>=0.0 && pz<=100.0);

		if (keep_going == false) {
			is_not_done = false;
			return;
		}
		// Start with gravity
		floats ax=0.0, ay=0.0, az=-9.8;

		// Add the wind resistance
		floats velocity_squared=vx*vx+vy*vy+vz*vz;
		floats velocity=sqrt(velocity_squared);
		const floats air_density=1.2; // kg/m^3
		const floats drag_coefficient=-0.7;

		floats drag=drag_coefficient*air_density*area*velocity/mass;
		const floats earth_rotation_speed=2*3.141592/(24*60*60); // radians/second
		floats coriolis=-2*earth_rotation_speed; // around +X axis (north)

		floats new_ax = ax + drag*vx;
		floats new_ay = ay + drag*vy + coriolis*vz;
		floats new_az = az + drag*vz + coriolis*vy;

		// ax+=drag*vx;
		// ay+=drag*vy;
		// az+=drag*vz;

		// Add coriolis acceleration (rotating coordinate frame)
		// ay+=coriolis*vz;
		// az-=coriolis*vy;

		// Take Euler timesteps
		floats new_vx = vx + new_ax * dt;
		floats new_vy = vy + new_ay * dt;
		floats new_vz = vz + new_az * dt;

		floats new_px = px + new_vx * dt;
		floats new_py = py + new_vy * dt;
		floats new_pz = pz + new_vz * dt;

        px=keep_going.if_then_else(new_px, px);
        py=keep_going.if_then_else(new_py, py);
        pz=keep_going.if_then_else(new_pz, pz);

        vx=keep_going.if_then_else(new_vx, vx);
        vy=keep_going.if_then_else(new_vy, vy);
        vz=keep_going.if_then_else(new_vz, vz);

        ax=keep_going.if_then_else(new_ax, ax);
        ay=keep_going.if_then_else(new_ay, ay);
        az=keep_going.if_then_else(new_az, az);
	}
};

long foo(void) {
	int altitude_breaches=0;
	int outta_park=0;
	int altitude_ceiling=100.0; // meters of altitude (see FAA regs)

	double start=time_in_seconds();
	const int n_firings=10000;

	projectile b1;
 	const float offs[8]={0,1,2,3,4,5,6,7};
	b1.offsets = floats(offs);
    b1.mass=1.5;
    b1.area=0.1*0.1;
	b1.dt = 0.01;

	#pragma omp parallel for							\
		num_threads(6)									\
		schedule(dynamic, 4) 							\
		reduction(+:outta_park, altitude_breaches)		\
		firstprivate(b1)
	for (int firing=0;firing<n_firings;firing+=8)
	{

		b1.px=0.0; b1.py=0.0; b1.pz=1.7;
		b1.vx=10.0;
		b1.vy=30.0;
		b1.vz=(b1.offsets + firing)*0.01;
		b1.is_not_done = true;

		//	Move the projectile until it hits the ground, or breaches the altitude limit.
		while (b1.is_not_done)
		{
			// Advance physics
			b1.step();
		}

		for (int lane=0;lane<8;lane++)
		{
			if (b1.pz[lane]>altitude_ceiling) altitude_breaches++;
			if (b1.py[lane]>120.0) outta_park++;
		}
	}

	outta_park+=8;	// Do I have an off by one error somewhere?!

	double elapsed=time_in_seconds()-start;
	std::cout<<"firing: "<<elapsed*1.0e9/n_firings<<" ns/projectile\n",
	std::cout<<"outta park: "<<outta_park*100/n_firings<<"% projectiles\n";

	return altitude_breaches*100/n_firings;
}
