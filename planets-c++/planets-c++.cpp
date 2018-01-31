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
#include <vector>
#include <random>
#include <iostream>
#include <iomanip>
#include "CSVBodyParser.h"
#include "Planet.h"
#include "DwarfPlanet.h"

using namespace planets;
using namespace std;

/**
 * This operation computes the gravitational potential at each body and sets
 * the fictitious planetary radius for planets and dwarf planets.
 * @param bodies the list of bodies for which I should compute the potential
 * and set the planetary radius if applicable
 */
vector<double> getPotentials(const vector<CelestialBody> & bodies) {

	// Create a random number generator for radii
	mt19937 rng(123456);

	// Compute the gravitational potential at each body and set other properties
	int numBodies = bodies.size();
	vector<double> potentials(numBodies);
	for (int i = 0; i < numBodies; i++) {
		// Compute the potential
		potentials[i] = bodies[i].getGravitationalPotential(bodies,i);
		// Set radius for planets and dwarf planets
		if (bodies[i].type() != Star) {
			double radius = ((double) i+rng());
			((Planet &) bodies[i]).radius(radius);
		}
	}

	return potentials;
}

/**
 * Main function
 * @param argc number of input arguments
 * @param argv pointer to an array of input arguments
 * @return EXIT_SUCCESS return code if successfully executed, otherwise not
 */
int main(int argc, char * argv[]) {

	// Set output precision to double
	cout << std::fixed << setprecision(8);

	// Load the celestial body parse
	CSVBodyParser parser;
	// Parse the bodies. The result is acquired by value and takes advantage of
	// move semantics.
	auto bodies = parser.parseBodies("planetary-system.csv");

	// Get the potentials
	auto potentials = getPotentials(bodies);

	// Pretty-print the results. Set precision to double.
	int numBodies = bodies.size();
	for (int i = 0; i < numBodies; i++) {
		cout << bodies[i].name() << ", potential = " << potentials[i] << endl;
	}

	// Compute the volume of all dwarf planets

	return EXIT_SUCCESS;
}
