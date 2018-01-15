//
//  lightParser.hpp
//  SnieGL
//
//  Created by snie on 12/16/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#ifndef lightParser_hpp
#define lightParser_hpp

#include <string>

#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <stdio.h>

struct lightInfo {
	int count;
	std::vector<glm::vec3> lightPosition;
	std::vector<glm::vec3> lightKa;
	std::vector<glm::vec3> lightKd;
	std::vector<glm::vec3> lightKs;
};

void parseLights(std::string lightPath, lightInfo &lights);

#endif /* lightParser_hpp */
