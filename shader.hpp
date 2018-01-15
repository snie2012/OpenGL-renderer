//
//  shader.hpp
//  OpenCVTest
//
//  Created by snie on 12/15/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

GLuint LoadShaders( const char* vertex_file_path, const char* fragment_file_path);

#endif /* shader_hpp */
