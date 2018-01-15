//
//  objParser.hpp
//  OpenCVTest
//
//  Created by snie on 12/15/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#ifndef objParser_hpp
#define objParser_hpp
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include <stdio.h>

struct ObjGroup {
	std::string usemtl;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> txtcoords;
	std::vector<glm::vec3> normals;
};

void parseObj (std::string& fileName, std::vector<ObjGroup *> &objInfo);

#endif /* objParser_hpp */
