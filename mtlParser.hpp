//
//  mtlParser.hpp
//  SnieGL
//
//  Created by snie on 12/16/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#ifndef mtlParser_hpp
#define mtlParser_hpp

#include <stdio.h>

#include <string>

#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Bitmap.h"
#include "Texture.h"


struct mtlInfo {
	std::string newmtl;
	float Ns;
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	std::string mapKd;
	tdogl::Texture* Texture;
};

void parseMtl(std::string& fileName, std::vector<mtlInfo *> &mtlGroup);

#endif /* mtlParser_hpp */
