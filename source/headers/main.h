#ifndef MAIN_H
#define MAIN_H

#include "headers.h"

extern float values[];

extern float control_values[];

extern float winWidth, winHeight;

extern float xrot, 		yrot;
extern float xrotStep, 	yrotStep;

extern bool points, pointsBuf;
extern bool axis, 	axisBuf;

extern std::string portFromFile;

extern int control_value_select;

extern Socket sendValues;

#endif
