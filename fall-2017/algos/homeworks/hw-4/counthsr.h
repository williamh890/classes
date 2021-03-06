// counthsr.h
// William Horn
// Oct 11, 2017
// cs311 assignment 4 header


#ifndef COUNTHSR_H
#define COUNTHSR_H

// countHSR
// find the total number of 'holey spider runs'
// pre: all values must be positive,
//      hole, start, and finish must be coordinates inside dimension
int countHSR(int dim_x, int dim_y,
             int hole_x, int hole_y,
             int start_x, int start_y,
             int finish_x, int finish_y);


#endif // END COUNTHSR_H
