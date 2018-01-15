//
//  buildObj.hpp
//  SnieGL
//
//  Created by snie on 12/16/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#ifndef buildObj_hpp
#define buildObj_hpp

#include <stdio.h>

#include <string>

#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "objParser.hpp"
#include "mtlParser.hpp"
#include "snieTexture.hpp"

struct objBuffer {
	int size;
	std::string mtl;
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;
	mtlInfo mtlInfo;
};

struct OneObj {
	std::vector<objBuffer *> objGroup;
	GLuint vertexArrayID;
};

bool buildObj(std::string fileName, OneObj &oneObj);


#endif /* buildObj_hpp */
