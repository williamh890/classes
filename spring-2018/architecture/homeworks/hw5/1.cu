/*
 This class represents a ballistic projectile.
*/
class projectile {
public:
	float mass; // mass, kilograms
	float area; // area, square meters (for wind resistance)
	float px,py,pz; // position, in meters
	float vx,vy,vz; // velocity, in meters/second

	__device__ void step(float dt) {
		// Start with gravity
		float ax=0.0, ay=0.0, az=-9.8;

		// Add the wind resistance
		float velocity_squared=vx*vx+vy*vy+vz*vz;
		float velocity=sqrt(velocity_squared);

		const float air_density=1.2; // kg/m^3
		const float drag_coefficient=-0.7;
		float drag=drag_coefficient*air_density*area*velocity/mass;
		ax+=drag*vx; ay+=drag*vy; az+=drag*vz;

		// Add coriolis acceleration (rotating coordinate frame)
		const float earth_rotation_speed=2*3.141592/(24*60*60); // radians/second
		float coriolis=-2*earth_rotation_speed; // around +X axis (north)
		ay+=coriolis*vz; az-=coriolis*vy;

		// Take Euler timesteps
		vx+=ax*dt; vy+=ay*dt; vz+=az*dt;
		px+=vx*dt; py+=vy*dt; pz+=vz*dt;
	}
};

__global__ void fire_one(int *arr_outta, int *arr_altitude) {
	int altitude_ceiling=100.0; // meters of altitude (see FAA regs)
    int firing = threadIdx.x + blockIdx.x*blockDim.x;

	projectile b;
	b.mass=1.5;
	b.area=0.1*0.1;
	b.px=0.0; b.py=0.0; b.pz=1.7;
	b.vx=10.0;
	b.vy=30.0;
	b.vz=firing*0.01;

	//	Move the projectile until it hits the ground, or breaches the altitude limit.
	while (true)
	{
		// Check consistency
		if (b.pz<0.0) break; // too low
		if (b.pz>altitude_ceiling) break; // too high

		// Advance physics
		b.step(0.01);
	}

	if (b.pz>altitude_ceiling)
		arr_altitude[firing]=1;
	else
		arr_altitude[firing]=0;

	if (b.py>120.0)
		arr_outta[firing]=1;
	else
		arr_outta[firing]=0;
}

long foo(void) {
	const int n_firings=10000;
	int *gpu_arr_altitude=new int[n_firings];
	int *gpu_arr_outta=new int[n_firings];

	int *cpu_arr_altitude=new int[n_firings];
	int *cpu_arr_outta=new int[n_firings];

    gpu_check(cudaMalloc(&gpu_arr_altitude, n_firings*sizeof(int)));
    gpu_check(cudaMalloc(&gpu_arr_outta, n_firings*sizeof(int)));

	double start=time_in_seconds();

    fire_one<<<n_firings / 256, 256>>>(gpu_arr_outta, gpu_arr_altitude);

	gpu_check(cudaDeviceSynchronize()); // join
	gpu_check(cudaGetLastError());

	gpu_check(cudaMemcpy(cpu_arr_outta, gpu_arr_outta, n_firings*sizeof(int), cudaMemcpyDeviceToHost));
	gpu_check(cudaMemcpy(cpu_arr_altitude, gpu_arr_altitude, n_firings*sizeof(int), cudaMemcpyDeviceToHost));

	int altitude_breaches=0, outta_park=0;

	for (int firing=0;firing<n_firings;firing++) {
		if (cpu_arr_outta[firing]) outta_park++;
		if (cpu_arr_altitude[firing]) altitude_breaches++;
	}

	double elapsed=time_in_seconds()-start;
	std::cout<<"firing: "<<elapsed*1.0e9/n_firings<<" ns/projectile\n",
	std::cout<<"outta park: "<<outta_park*100/n_firings<<"% projectiles\n";

	return altitude_breaches*100/n_firings;
}
