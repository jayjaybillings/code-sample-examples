/**----------------------------------------------------------------------------
 Copyright (c) 2018-, UT-Battelle, LLC
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 * Neither the name of the copyright holder nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 Author(s): Jay Jay Billings (jayjaybillings <at> gmail <dot> com)
 -----------------------------------------------------------------------------*/
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE planets

#if defined __GNUC__ && __GNUC__>=6
  #pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <memory>
#include <math.h>
#include <iostream>
#include "../CelestialBodyData.h"
#include "../CelestialBody.h"

using namespace std;
using namespace planets;

/**
 * This operation checks the basic getters and setters on the celestial body
 */
BOOST_AUTO_TEST_CASE(checkAccessors) {

	// Create some data for the body
	CelestialBodyData data;
	data.pos[0] = 1.0;
	data.pos[1] = 2.0;
	data.pos[2] = 3.0;
	data.vel[0] = 4.0;
	data.vel[1] = 5.0;
	data.vel[2] = 6.0;
	data.mass = 7.0;
	data.label = "Kitten";
	data.type = Star;

	// Create a celestial body and inject the test data
	CelestialBody body(data);

	// Check getting
	BOOST_REQUIRE_CLOSE(1.0,body.pos()[0],1.0e-15);
	BOOST_REQUIRE_CLOSE(2.0,body.pos()[1],1.0e-15);
	BOOST_REQUIRE_CLOSE(3.0,body.pos()[2],1.0e-15);
	BOOST_REQUIRE_CLOSE(4.0,body.vel()[0],1.0e-15);
	BOOST_REQUIRE_CLOSE(5.0,body.vel()[1],1.0e-15);
	BOOST_REQUIRE_CLOSE(6.0,body.vel()[2],1.0e-15);
	BOOST_REQUIRE_CLOSE(7.0,body.mass(),1.0e-15);
	BOOST_REQUIRE_EQUAL("Kitten",body.name());
	BOOST_REQUIRE_EQUAL(Star,body.type());

	// Use the body setters to reset these values
	std::array<double,3> newPos = {10.0,11.0,12.0};
	std::array<double,3> newVel = {13.0,14.0,15.0};
	body.pos(newPos);
	body.vel(newVel);
	body.mass(16.0);
	body.name("Cat");
	body.type(Planetary);

	// Check that the setters worked
	BOOST_REQUIRE_CLOSE(10.0,body.pos()[0],1.0e-15);
	BOOST_REQUIRE_CLOSE(11.0,body.pos()[1],1.0e-15);
	BOOST_REQUIRE_CLOSE(12.0,body.pos()[2],1.0e-15);
	BOOST_REQUIRE_CLOSE(13.0,body.vel()[0],1.0e-15);
	BOOST_REQUIRE_CLOSE(14.0,body.vel()[1],1.0e-15);
	BOOST_REQUIRE_CLOSE(15.0,body.vel()[2],1.0e-15);
	BOOST_REQUIRE_CLOSE(16.0,body.mass(),1.0e-15);
	BOOST_REQUIRE_EQUAL("Cat",body.name());
	BOOST_REQUIRE_EQUAL(Planetary,body.type());

	return;
}

/**
 * This operation checks the potential calculation on the celestial body
 */
BOOST_AUTO_TEST_CASE(checkPotential) {

	int size = 10;
	std::vector<CelestialBodyData> data(size);
	std::vector<CelestialBody> bodies;

	// Setup the data and bodies
	for (int i = 0; i < size; i++) {
		double iD = ((double) i) + 1.0;
		// Create the data
		data[i].pos[0] = iD;
		data[i].pos[1] = 2.0*iD;
		data[i].pos[2] = 3.0*iD;
		data[i].vel[0] = 4.0*iD;
		data[i].vel[1] = 5.0*iD;
		data[i].vel[2] = 6.0*iD;
		data[i].mass = 7.0*iD;
		data[i].label = "Kitten" + i;
		data[i].type = Planetary;
		// Create the body
		bodies.push_back(CelestialBody(data[i]));
	}

	// Create the body at which the potential will be calculated
	CelestialBodyData centerBodyData;
	centerBodyData.pos[0] = 0.0;
	centerBodyData.pos[1] = 0.0;
	centerBodyData.pos[2] = 0.0;
	centerBodyData.vel[0] = 0.0;
	centerBodyData.vel[1] = 0.0;
	centerBodyData.vel[2] = 0.0;
	centerBodyData.mass = 1000;
	centerBodyData.label = "Momma cat";
	centerBodyData.type = Star;
	CelestialBody centerBody(centerBodyData);

	// Compute the reference potential using direct summation
	double refPot = 0.0, G = 6.67408e-11, dist = 0.0;
	double dx = 0.0, dy = 0.0, dz = 0.0;
	// Compute the base potential for G = 1 and M = 1
	for (int i = 0; i < 1; i++) {
		// Compute the distance between the current
		dx = centerBody.pos()[0] - bodies[i].pos()[0];
		dy = centerBody.pos()[1] - bodies[i].pos()[1];
		dz = centerBody.pos()[2] - bodies[i].pos()[2];
		dist = sqrt(dx*dx + dy*dy + dz*dz);
		// Compute the base potential
		refPot += bodies[i].mass()/dist;
	}
	// Scale by G and M
	refPot *= -G*centerBodyData.mass;

	// Check the result
	BOOST_REQUIRE_CLOSE(refPot,centerBody.getGravitationalPotential(bodies,-1),1.0e-8);

	return;
}
