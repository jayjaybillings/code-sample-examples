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
#include <string>
#include <random>
#include "../CSVBodyParser.h"
#include "../CelestialBody.h"
#include "../CelestialBodyData.h"

using namespace std;
using namespace planets;

/// Simple flag for the number of bodies to put into the file.
const int numTestBodies = 3;

/// Test data file name
const string testFileName = "test.csv";

/// The reference test data written during setup
vector<CelestialBodyData> bodyData;

/**
 * This function gets the test data.
 * @param the number of bodies to create
 * @return a vector of the body test data, not bodies
 */
vector<CelestialBodyData> getTestBodyData(const int & numBodies) {
	// Use a Mersenne Twister for generating the test data with the world's
	// best test seed!
	mt19937 rng(123456);
	vector<CelestialBodyData> bodies;
	// Just create some random data for the test
	for (int i = 0; i < numBodies; i++) {
		CelestialBodyData data;
		data.pos[0] = (double) rng();
		data.pos[1] = (double) rng();
		data.pos[2] = (double) rng();
		data.vel[0] = (double) rng();
		data.vel[1] = (double) rng();
		data.vel[2] = (double) rng();
		data.mass = (double) rng();
		data.label = to_string(i);
		// Set everything to Star by default. Will fix below.
		data.type = Star;
		bodies.push_back(move(data));
	}

	// Fix the types. Ignore the first since they it is correct. Exploit
	// numBodies = 3 since this is just a sample and generality is not
	// required.
	bodies[1].type = Planetary;
	bodies[2].type = DwarfPlanetary;

	return bodies;
}

/**
 * This function writes test data to a file.
 * @param the name of the file to which the data should be written
 * @param the data to be written
 */
void writeTestData(const string & filename,
		vector<CelestialBodyData> bodies) {
	// Open the file
	ofstream output(filename.c_str());
	output << std::fixed << std::setprecision(8);

	// Write the line for each body
	for (int i = 0; i < bodies.size(); i++) {
		auto & bodyData = bodies[i];
		output << bodies[i].pos[0] << "," << bodies[i].pos[1] << ","
				<< bodies[i].pos[2];
		output << "," << bodies[i].vel[0] << "," << bodies[i].vel[1] << ","
				<< bodies[i].vel[2];
		output << "," << bodies[i].mass;
		output << "," << bodies[i].label;
		output << "," << bodies[i].type;
		output << endl;
	}

	// Close the file
	output.close();
}

/**
 * This is the test fixture that is executed at setup and teardown.
 */
struct Fixture {

	Fixture() {
		// Get, store, and write the data
		bodyData = getTestBodyData(numTestBodies);
		writeTestData(testFileName,bodyData);
		writeTestData("testData",getTestBodyData(10));
	}

	~Fixture() {
		// Delete the test file
		remove(testFileName.c_str());
	}
};

/**
 * Initialize the test suite
 */
BOOST_FIXTURE_TEST_SUITE(s,Fixture)

/**
 * This operation checks the basic getters and setters on the celestial body
 */
BOOST_AUTO_TEST_CASE(checkParse) {

	// Create the parser and load the data
	CSVBodyParser bodyParser;
	auto parsedBodies = bodyParser.parseBodies(testFileName);

	// This file only has three bodies - one of each - so check them.
	BOOST_REQUIRE_EQUAL(numTestBodies,parsedBodies.size());
	for (int i = 0; i < numTestBodies; i++) {
		BOOST_REQUIRE_CLOSE(bodyData[i].pos[0],parsedBodies[i].pos()[0],1.0e-15);
		BOOST_REQUIRE_CLOSE(bodyData[i].pos[1],parsedBodies[i].pos()[1],1.0e-15);
		BOOST_REQUIRE_CLOSE(bodyData[i].pos[2],parsedBodies[i].pos()[2],1.0e-15);
		BOOST_REQUIRE_CLOSE(bodyData[i].vel[0],parsedBodies[i].vel()[0],1.0e-15);
		BOOST_REQUIRE_CLOSE(bodyData[i].vel[1],parsedBodies[i].vel()[1],1.0e-15);
		BOOST_REQUIRE_CLOSE(bodyData[i].vel[2],parsedBodies[i].vel()[2],1.0e-15);
		BOOST_REQUIRE_CLOSE(bodyData[i].mass,parsedBodies[i].mass(),1.0e-15);
		BOOST_REQUIRE_EQUAL(bodyData[i].label,parsedBodies[i].name());
		BOOST_REQUIRE_EQUAL(bodyData[i].type,parsedBodies[i].type());
	}

	return;
}

BOOST_AUTO_TEST_SUITE_END()
