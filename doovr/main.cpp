/* 
   	DooVR, Modelling application using Oculus Rift and Sixense STEM.
    Copyright (C) 2015  Isabelle Forsman, Olle Grahn, Jonathan Bosson, Johan Nordin.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	isafo268@student.liu.se, ollgr444@student.liu.se, jonbo665@student.liu.se, johno855@student.liu.se,
*/

/*! \mainpage DooVR
*
* \section intro_sec Introduction
*
* This is the introduction.
*
* \section install_sec Compiling and running
* DooVR is tested to work with the compiler VC12. 
*
* - Get all requierd libraries\ref found in \ref dependencies_sec and install them. 
* - Create a project in Visual studio 2013 and add the files in DooVR
* - Link the required libraries in the project properties
* - Build and run the project
* 
* - To run the wand configuration type "C" in the console
* - To run the application using a Oculus display type "O" in the console
*
* \section dependencies_sec Dependencies
*	- OpenGL
*	- GLFW
*	- GLEW
*	- libOVR
*	- VRPN
*	- wand3D
*	- Armadillo
*
*/


#include <iostream>
#include <time.h>

#include "Utilities.h"

#include "Shader.h"
#include "MatrixStack.h"
#include "Entity.h"
#include "Sphere.h"

#include "twoDim.h"
#include "Oculus.h"
#include "configure.h"

char DeviceType;

//! main 

/*!
Very short function. Simply decides which mode the user wants to use and then 
redirects to two different namespaces depending on the choice. 
*/
int main() {

	int runSuccess = 0;
	
	
	while (runSuccess == 0) {
		cin >> DeviceType;
		if (DeviceType == 'C')
			runSuccess = configure::coRegister();
		else if (DeviceType == 'O')
			runSuccess = Oculus::runOvr();
	}
	
	return runSuccess;
}
