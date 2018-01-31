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
#include "CelestialBody.h"
#include <math.h>

namespace planets {

CelestialBody::CelestialBody(const CelestialBodyData & data) :
		bodyData(data) {

}

CelestialBody::CelestialBody(CelestialBodyData && data) :
		bodyData(data) {

}

CelestialBody::~CelestialBody() {

}

const std::array<double, 3> & CelestialBody::pos() const {
	return bodyData.pos;
}

void CelestialBody::pos(const std::array<double, 3> & _pos) {
	bodyData.pos = _pos;
}

const std::array<double, 3> & CelestialBody::vel() const {
	return bodyData.vel;
}

void CelestialBody::vel(const std::array<double, 3> & _vel) {
	bodyData.vel = _vel;
}

const double & CelestialBody::mass() const {
	return bodyData.mass;
}

void CelestialBody::mass(const double & _mass) {
	bodyData.mass = _mass;
}

const std::string & CelestialBody::name() const {
	return bodyData.label;
}

void CelestialBody::name(const std::string & _name) {
	bodyData.label = _name;
}

const CelestialBodyType & CelestialBody::type() const {
	return bodyData.type;
}

void CelestialBody::type(const CelestialBodyType & _type) {
	bodyData.type = _type;
}

double CelestialBody::getGravitationalPotential(
		const std::vector<CelestialBody> & system, int thisIndex) const {
	double pot = 0.0, G = 6.67408e-11, dist = 0.0;
	double dx = 0.0, dy = 0.0, dz = 0.0;

	// Compute the base potential for G = 1 and M = 1 using direct summation
	int systemSize = system.size();
	for (int i = 0; i < systemSize; i++) {
		// Compute the distance between the current
		dx = bodyData.pos[0] - system[i].pos()[0];
		dy = bodyData.pos[1] - system[i].pos()[1];
		dz = bodyData.pos[2] - system[i].pos()[2];
		dist = sqrt(dx * dx + dy * dy + dz * dz);
		if (i != thisIndex) {
			// Compute the base potential
			pot += system[i].mass() / dist;
		}
	}
	// Scale by G and M
	pot *= -G * bodyData.mass;

	return pot;
}

} /* namespace planets */
