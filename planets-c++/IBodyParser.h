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
#ifndef IBODYPARSER_H_
#define IBODYPARSER_H_

#include <vector>
#include <string>
#include "CelestialBody.h"

namespace planets {

/**
 * This is a simple interface for describing the process of parsing an input
 * file and returning a list of Celestial Bodies. This interface was
 * specifically included to show interface realization in C++. In other
 * situations I prefer to handle I/O with templated functions.
 */
class IBodyParser {

public:

	/**
	 * Destructor.
	 */
	virtual ~IBodyParser() {};

	/**
	 * This operation parses an input file that contains information about
	 * celestial bodies.
	 * @param inputFile the name of the input file containing information about
	 * the bodies.
	 * @return a standard vector containing the bodies. Notes that this is
	 * provided directly as a return value because the compiler with move the
	 * result (C++11) instead of copying it.
	 */
	virtual std::vector<CelestialBody> parseBodies(const std::string & inputFile) const = 0;
};

} /* namespace planets */

#endif /* IBODYPARSER_H_ */
