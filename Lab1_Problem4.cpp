/*
Author: Deanna Gierzak
Class: ECE 6122
Last Date Modified: 9/14/2020

Description:

Reflections in a White Cell:

This program uses a starting value for a point on an ellipse that represents the entrance/exit of a white cell
in which a laser enters the cell at a particular angle. The second point is given for the first reflection.
This program calculations the number of times the laser reflects within the cell before it exits the cell.
This problem was worked out geometrically with the use of tangent identities, and the analytical solution
on paper is given in the submission of this assignment on Canvas.

The resulting number of reflections is output to a file calling Output4.txt

*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() 
{
	double a = 5.0, b = 10.0;					// for ellipse equation
	double xStart = 0.0, yStart = 10.1;			// starting point
	double xReflect = 1.4, yReflect = -9.6;		// point of reflection on ellipse (first one declared here)
	unsigned long reflections = 0;				// initialize total summed reflections to zero

	double slopeA, slopeO, tanA, slopeB, c_interceptB, A, B, C, xroot1, xroot2, test1, test2; // declared variables for use in loop

	while (xReflect > 0.01 || xReflect < -0.01 || yReflect < 0)
	{
		slopeA = (yReflect - yStart) / (xReflect - xStart);		// calculate slope of A, starting point
		slopeO = -4 * xReflect / yReflect;						// calculate slope of the line tangent to ellipse at next point
	
		tanA = (slopeA - slopeO) / (1 + slopeA * slopeO);		// calculate the slope for line B starting with tangent identity
		slopeB = (slopeO - tanA) / (1 + tanA * slopeO);			// calculate the slope for line B from the calculated tangent of the angle between tangent line and angle of incidence/reflection

		c_interceptB = yReflect - slopeB * xReflect;			// with the x,y coordinates of the reflection and the calculated slope, can now find the y-intercept (referred to as c to avoid confusion with ellipse equation)

		A = pow(a, 2)*pow(slopeB, 2) + pow(b, 2);				// calculate A for Ax^2 + Bx + C <===> from equation of intersection of line with an ellipse
		B = 2 * pow(a, 2)*slopeB*c_interceptB;					// calculate B for Ax^2 + Bx + C <===> from equation of intersection of line with an ellipse
		C = pow(a, 2)* (pow(c_interceptB, 2) - pow(b, 2));		// calculate C for Ax^2 + Bx + C <===> from equation of intersection of line with an ellipse

		xroot1 = (-B + sqrt( pow(B,2) - 4 * A*C)) / (2 * A);	// solve for two roots with quadratic formula
		xroot2 = (-B - sqrt( pow(B, 2) - 4 * A*C)) / (2 * A);	// solve for two roots with quadratic formula

		xStart = xReflect; yStart = yReflect;   // set new coordinates of X, Y 

		test1 = abs(xroot1 - xReflect);			// distance from first root to x point of reflection
		test2 = abs(xroot2 - xReflect);			// distance from second root to x point of reflection

		// Whichever one has the larger value is the one that should be set to the new point of reflection
		// since a line crosses an ellipse at most two points, and we are calculating the next point of reflection
		// from the calculated slope, then it would reason that one of the roots should be = to the current point.
		// Therefore, to ensure we find the next point, rather than checking if one root is = to current x point,
		// we look for the one that has the larger difference (because they may not be exactly = due to calculation)
		if (test1 > test2) 
		{
			xReflect = xroot1; // set X of the next point of reflection 
		}

		if (test2 > test1)
		{
			xReflect = xroot2; // set X of the next point of reflection 
		}

		yReflect = slopeB * xReflect + c_interceptB;	// Calculate Y of the next point of reflection from roots test and calculated intercept

		reflections = reflections + 1;					// Add a reflection to the total count

	}
	// cout << reflections << endl << endl; // for debugging
	ofstream ofs;					// define an ofstream object
	ofs.open("Output4.txt");		// use to open a text file (or create one)
	ofs << reflections;				// put the sum of reflections into this file
	ofs.close();					// close the file

	// cin.ignore();

	return 0;
}
