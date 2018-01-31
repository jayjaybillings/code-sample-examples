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
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "CSVBodyParser.h"

using namespace std;

namespace planets {

CSVBodyParser::CSVBodyParser() {
	// TODO Auto-generated constructor stub

}

CSVBodyParser::~CSVBodyParser() {
	// TODO Auto-generated destructor stub
}

CelestialBody CSVBodyParser::loadBody(
		const std::vector<std::string> & lineVec) const {

	// Create a simple map for the enumerated types. Cheap and fast this way.
	CelestialBodyType types[3] = {Star, Planetary, DwarfPlanetary};

	// Create the body data. For the purposes of this code sample, it is
	// sufficient to assume there are no errors in the individual lines.
	CelestialBodyData data;
	data.pos[0] = strtod(lineVec[0].c_str(), NULL);
	data.pos[1] = strtod(lineVec[1].c_str(), NULL);
	data.pos[2] = strtod(lineVec[2].c_str(), NULL);
	data.vel[0] = strtod(lineVec[3].c_str(), NULL);
	data.vel[1] = strtod(lineVec[4].c_str(), NULL);
	data.vel[2] = strtod(lineVec[5].c_str(), NULL);
	data.mass = strtod(lineVec[6].c_str(), NULL);
	data.label = lineVec[7];
	// Pull the data type from the map
	data.type = types[atoi(lineVec[8].c_str())];

	// Load and return the body
	CelestialBody body(move(data));

	return body;
}

std::vector<CelestialBody> CSVBodyParser::parseBodies(
		const std::string & inputFile) const {
	std::vector<CelestialBody> bodies;

	// Note: "data" has already been initialized by the base class.
	// Load the contents of the file
	string delimiter = ",", commentChar = "#";
	string value, line;
	ifstream fileStream(inputFile);
	// Pull each line and push it into the list
	if (fileStream.is_open()) {
		// Pull each line from the file
		while (getline(fileStream,line)) {
			if (!line.empty() && !line.find(commentChar) == 0) {
			   istringstream ss(line);
			   vector<string> lineVec;
				// Split the line and push each element into the line list.
			   while (getline(ss,value,*delimiter.c_str())) {
			       lineVec.push_back(value);
			   }
			   // Call a separate function to create the body and put it into
			   // the vector.
			   bodies.push_back(loadBody(lineVec));
			}
		}
		fileStream.close();
	} else {
		throw "Text file stream not open! Check path?";
	}

	return bodies;
}

} /* namespace planets */
