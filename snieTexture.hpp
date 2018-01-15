//
//  snieTexture.hpp
//  SnieGL
//
//  Created by snie on 12/16/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#ifndef snieTexture_hpp
#define snieTexture_hpp

#include <stdio.h>
#include "Bitmap.h"
#include "Texture.h"

#include "mtlParser.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void buildTexture (std::string& fileName, std::vector<mtlInfo *> &mtlGroup);

#endif /* snieTexture_hpp */
