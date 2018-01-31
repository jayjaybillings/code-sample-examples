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
#ifndef CSVBODYPARSER_H_
#define CSVBODYPARSER_H_

#include "IBodyParser.h"

namespace planets {

/**
 * This is an implementation of IBodyParser that can parse a list of
 * celestial bodies from a CSV file. The file should contain a line per body
 * with the following contents:
 * x - x position of the planet
 * y - y position of the planet
 * z - z position of the planet
 * v_x - x component of the instantaneous velocity of the planet
 * v_y - y component of the instantaneous velocity of the planet
 * v_z - z component of the instantaneous velocity of the planet
 * m - the mass of the plant
 * label - a label to describe the planet, such as "Jupiter" or "Earth"
 * type - the type of the planet such as "planet," "dwarf," or "star"
 *
 * A sample entry would be:
 * 100.0, 100.0, -4.0, 1200, 1200, 1200, 1.0e21, "JayWorld", 0
 *
 * The "type" attribute was added specifically to demonstrate processing input
 * logic and would be handled differently in an optimized code.
 */
class CSVBodyParser: public IBodyParser {

private:

	/**
	 * This is a private factory function for loading CelestialBodies from a
	 * vector of strings. It returns by value, evoking move semantics/RVO.
	 */
	CelestialBody loadBody(const std::vector<std::string> & lineVec) const;

public:

	/**
	 * Constructor
	 */
	CSVBodyParser();

	/**
	 * Destructor
	 */
	virtual ~CSVBodyParser();

	virtual std::vector<CelestialBody> parseBodies(
			const std::string & inputFile) const;

};

} /* namespace planets */

#endif /* CSVBODYPARSER_H_ */
