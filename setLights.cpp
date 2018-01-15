//
//  initShaderParameter.cpp
//  SnieGL
//
//  Created by snie on 12/16/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#include "setLights.hpp"
#include <glm/gtc/type_ptr.hpp>

void setLights(GLuint &programID) {
	glUseProgram(programID); // Set this every time before setting any value in the shaders!!!
	
	lightInfo lights;
	parseLights("settings/lights.txt", lights);
	
	glUniform1f(glGetUniformLocation(programID, "lightsCount"), lights.count);
	
	glUniform3fv(glGetUniformLocation(programID, "lightPositions"), (int)lights.lightPosition.size() * sizeof(glm::vec3), glm::value_ptr(lights.lightPosition[0]));
	
	glUniform3fv(glGetUniformLocation(programID, "lightKa"), (int)lights.lightKa.size() * sizeof(glm::vec3), glm::value_ptr(lights.lightKa[0]));
	
	glUniform3fv(glGetUniformLocation(programID, "lightKd"), (int)lights.lightKd.size() * sizeof(glm::vec3), glm::value_ptr(lights.lightKd[0]));
	
	glUniform3fv(glGetUniformLocation(programID, "lightKs"), (int)lights.lightKs.size() * sizeof(glm::vec3), glm::value_ptr(lights.lightKs[0]));
}