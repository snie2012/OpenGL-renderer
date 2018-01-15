//
//  lightParser.cpp
//  SnieGL
//
//  Created by snie on 12/16/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#include "lightParser.hpp"

void parseLights(std::string lightPath, lightInfo &lights) {
	std::ifstream file(lightPath);
	std::string line;
	std::string name;

	while (std::getline(file, line)) {
		if (line == "" || line[0] == '#') {
			continue;
		}

		std::istringstream lineStream(line);
		lineStream >> name;

		if (name == "p") {
			lights.count++;
			glm::vec3 tmpPosition;
			sscanf(line.c_str(), "%*s %f %f %f", &tmpPosition.x, &tmpPosition.y, &tmpPosition.z);
			lights.lightPosition.push_back(tmpPosition);
		} else if (name == "ka") {
			glm::vec3 tmpKa;
			sscanf(line.c_str(), "%*s %f %f %f", &tmpKa.x, &tmpKa.y, &tmpKa.z);
			lights.lightKa.push_back(tmpKa);
		} else if (name == "kd") {
			glm::vec3 tmpKd;
			sscanf(line.c_str(), "%*s %f %f %f", &tmpKd.x, &tmpKd.y, &tmpKd.z);
			lights.lightKd.push_back(tmpKd);
		} else if (name == "ks") {
			glm::vec3 tmpKs;
			sscanf(line.c_str(), "%*s %f %f %f", &tmpKs.x, &tmpKs.y, &tmpKs.z);
			lights.lightKs.push_back(tmpKs);
		} else {
			continue;
		}
	}
}
