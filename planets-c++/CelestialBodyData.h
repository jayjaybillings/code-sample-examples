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
#ifndef CELESTIALBODYDATA_H_
#define CELESTIALBODYDATA_H_

#include <memory>
#include <string>

namespace planets {

/**
 * A simple enumeration that describes the type of the celestial body.
 */
enum CelestialBodyType {
	Star,
	Planetary,
	DwarfPlanetary
};

/**
 * This is the collection of data used by celestial bodies . The properties on
 * this struct are all public. While in some codes it might be necessary to
 * access the data members through accessor functions, there is no good
 * reason to protect the members in this code because they are both modified
 * frequently by clients and require neither special treatment nor computation.
 * For the same reason, a struct was used instead of a class. That is to say,
 * all of this is just Plain Old Data (POD).
 */
struct CelestialBodyData {

	/// The position of the body
	std::array<double,3> pos;

	/// The velocity of the body
	std::array<double,3> vel;

	/// The mass of the body
	double mass;

	/// A short label describing the body
	std::string label;

	/// The type of the body
	CelestialBodyType type;

};

} /* namespace planets */

#endif /* CELESTIALBODYDATA_H_ */
