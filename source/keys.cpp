#include "headers/headers.h"

bool keyStates[256];
bool specialKeyStates[256];

bool points = true;
bool pointsBuf = false;

bool axis = false;
bool axisBuf = false;

bool left_key_buffer;
bool right_key_buffer;
bool up_key_buffer;
bool down_key_buffer;

void keyPressed (unsigned char key, int x, int y) {
    keyStates[key] = true;
}

void keyUp (unsigned char key, int x, int y) {
    keyStates[key] = false;
}

void specialKeyPressed(int key, int x, int y) {
    specialKeyStates[key] = true;
}

void specialKeyUp(int key, int x, int y) {
    specialKeyStates[key] = false;
}

void keyOps()
{
    if(keyStates['a'])
	{
		xrot -= xrotStep;
	}

	if(keyStates['d'])
	{
		xrot += xrotStep;
	}

	if(keyStates['w'])
	{
		yrot += yrotStep;
	}

	if(keyStates['s'])
	{
		yrot -= yrotStep;
	}

	if(keyStates['q'])
	{
		yrot = 0;
		xrot = 45;
	}

	if(keyStates['1'])
	{
		if(pointsBuf == false)
		{
			if(points) {
				points = false;
			}
			else 
			{
				points = true;
			}
			pointsBuf = true;
		}
	}

	if(!keyStates['1'])
	{
		pointsBuf = false;
	}

	if(keyStates['2'])
	{
		if(axisBuf == false)
		{
			if(axis) {
				axis = false;
			}
			else 
			{
				axis = true;
			}
			axisBuf = true;
		}
	}
	
	if(!keyStates['2'])
	{
		axisBuf = false;
	}

	if(specialKeyStates[GLUT_KEY_LEFT])
	{
		if(control_value_select > 0 && !left_key_buffer)
		{
			control_value_select--;
			left_key_buffer = true;
		}
	}

	if(!specialKeyStates[GLUT_KEY_LEFT])
	{
		left_key_buffer = false;
	}

	if(specialKeyStates[GLUT_KEY_RIGHT])
	{
		if(control_value_select < 5 && !right_key_buffer)
		{
			control_value_select++;
			right_key_buffer = true;
		}
	}

	if(!specialKeyStates[GLUT_KEY_RIGHT])
	{
		right_key_buffer = false;
	}

	if(specialKeyStates[GLUT_KEY_UP])
	{
		if(!up_key_buffer)
		{
			control_values[control_value_select] += .5;
			sendValues.send(control_value_select, control_values[control_value_select]);
			up_key_buffer = true;
		}
	}

	if(!specialKeyStates[GLUT_KEY_UP])
	{
		up_key_buffer = false;
	}

	if(specialKeyStates[GLUT_KEY_DOWN])
	{
		if(!down_key_buffer)
		{
			control_values[control_value_select] -= .5;
			sendValues.send(control_value_select, control_values[control_value_select]);
			down_key_buffer = true;
		}
	}

	if(!specialKeyStates[GLUT_KEY_DOWN])
	{
		down_key_buffer = false;
	}

}

