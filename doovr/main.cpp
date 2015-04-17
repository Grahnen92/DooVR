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

#include <iostream>
#include <time.h>

#include "Utilities.h"

#include "Shader.h"
#include "MatrixStack.h"
#include "Entity.h"
#include "Sphere.h"

#include "twoDim.h"
#include "Oculus.h"

char DeviceType;

//! main 

/*!
Very short function. Simply decides which mode the user wants to use and then 
redirects to two different namespaces depending on the choice. 
*/
int main() {

	int runSuccess = 0;
	
	cin >> DeviceType;

	if (DeviceType == 'O') 
		runSuccess = Oculus::runOvr();
	else if (DeviceType == 'D') 
		runSuccess = twoDim::run2D();
	
	return runSuccess;
}
