#pragma once

#include "Complex.h"

#define Bus_VT 0
#define Bus_PV 1
#define Bus_PQ 2
#define MAX_BUSES 200
#define MAX_ITERATION 200

//extern int total_buses = 0;
//extern int num_VT = 1;

class Bus
{
public:
	double P;
	double Q;
	double P_es[MAX_ITERATION];						// estimated P
	double Q_es[MAX_ITERATION];						// estimated Q

	double v_rating;								// rating voltage
	Complex v;										// real voltage
	Complex v_es[MAX_ITERATION];					// estimated voltage

	double v_mag;									// magnitude of voltage
	double v_mag_es[MAX_ITERATION];					// estimated magnitude of voltage

	int id;
	int type;						
};

class Line
{
public:
	double r;
	double x;
	double g;
	double b;
	int prebus;
	int nextbus;
};