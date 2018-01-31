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
#ifndef CELESTIALBODY_H_
#define CELESTIALBODY_H_

#include "CelestialBodyData.h"
#include <vector>
#include <memory>

namespace planets {

/**
 * A CelestialBody is a massive celestial object with a position, velocity, and
 * other properties. Celestial bodies include planets, dwarf planets, stars,
 * and other objects. The CelestialBody class is the base class for all other
 * celestial bodies.
 *
 * The base data for a CelestialBody is stored on in a CelestialBodyData
 * object. This demonstrates the concept of delegation and makes it possible to
 * do nifty things with the body data, which is just Plain Old Data (POD). It
 * is tempting to simply put the data directly on this class. However,
 * astronomical data is dirty, prone to change, and subject to ever changing
 * units. Thus in this case delegating the POD to another class allows the data
 * to change without affecting this class nor preventing smart unit scaling
 * operations at this level as well.
 *
 * This class could be extended in a useful way by delegating the computation
 * of the gravitational potential to a PotentialSolver class. However, for the
 * purposes of this sample, it is sufficient to use a direct n-body
 * computation.
 */
class CelestialBody {

	/// The physical data for the body - position, mass, etc.
	CelestialBodyData bodyData;

public:

	/**
	 * Body data copy constructor
	 * @param data the physical data that describes this celestial body
	 */
	CelestialBody(const CelestialBodyData & data);

	/**
	 * Move Constructor
	 * @param data the physical data that describes this celestial body
	 */
	CelestialBody(CelestialBodyData && data);

	/**
	 * Destructor
	 */
	virtual ~CelestialBody();

	/**
	 * This operation returns the current position of the celestial body.
	 * @return pos the position of the body
	 */
	const std::array<double,3> & pos() const;

	/**
	 * This operation sets the position of the body.
	 * @param _pos the new position of the body
	 */
	void pos(const std::array<double,3> & _pos);

	/**
	 * This operation returns the velocity of the body.
	 * @return vel the velocity
	 */
	const std::array<double,3> & vel() const;

	/**
	 * This operation sets the velocity of the body.
	 * @param _vel the new velocity of the body
	 */
	void vel(const std::array<double,3> & _vel);

	/**
	 * This operation returns the mass of the body.
	 * @return mass the mass
	 */
	const double & mass() const;

	/**
	 * This operation sets the mass of the body.
	 * @param _mass the new mass of the body
	 */
	void mass(const double & _mass);

	/**
	 * This operation returns the name of the body.
	 * @return name the name
	 */
	const std::string & name() const;

	/**
	 * This operation sets the name of the body.
	 * @param _name the new name of the body
	 */
	void name(const std::string & _name);

	/**
	 * This operation returns the type of the body.
	 * @return type the type
	 */
	const CelestialBodyType & type() const;

	/**
	 * This operation sets the type of the body.
	 * @param _type the new type of the body
	 */
	void type(const CelestialBodyType & _type);

	/**
	 * Given a set of "neighboring" celestial bodies, this operation will
	 * compute the gravitational potential of this body with respect to the
	 * full system.
	 * @param system the list of all other bodies that makeup the local system
	 * @param thisIndex the index of this body in the list so that the
	 * singularity can be avoided. It is ignored if the value is less than 0,
	 * which, by conventional, is taken to mean this body is not in the system.
	 * @return pot the potential
	 */
	double getGravitationalPotential(
			const std::vector<CelestialBody> & system, int thisIndex) const;
};

} /* namespace planets */

#endif /* CELESTIALBODY_H_ */
