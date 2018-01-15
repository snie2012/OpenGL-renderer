//
//  main.cpp
//  OpenCVTest
//
//  Created by snie on 10/28/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "main.hpp"

#include "shader.hpp"
#include "setLights.hpp"
#include "buildObj.hpp"

#include "controls.hpp"

GLFWwindow* window;
const glm::vec2 SCREEN_SIZE(600, 600);

ProgramInfo programInfo;
OneObj oneObj;

void initprogramInfo() {
	programInfo.programID = LoadShaders("Resource/shaders/vs.glsl", "Resource/shaders/fs.glsl");
	
	glUseProgram(programInfo.programID);
	programInfo.mvpID = glGetUniformLocation(programInfo.programID, "MVP");
	programInfo.textureID  = glGetUniformLocation(programInfo.programID, "uSampler");
	programInfo.mtlKaID = glGetUniformLocation(programInfo.programID, "mtlKa");
	programInfo.mtlKdID = glGetUniformLocation(programInfo.programID, "mtlKd");
	programInfo.mtlKsID = glGetUniformLocation(programInfo.programID, "mtlKs");
	programInfo.nsID = glGetUniformLocation(programInfo.programID, "shininess");
	programInfo.tFlagID = glGetUniformLocation(programInfo.programID, "tFlag");
}

int initGL() {
	if (!glfwInit())
	{
		fprintf (stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, "Snie GL", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, SCREEN_SIZE.x/2, SCREEN_SIZE.y/2);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	return 0;
}

void drawAtIndex() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(programInfo.programID);
	for (unsigned i = 0; i < oneObj.objGroup.size(); i++) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, oneObj.objGroup[i]->vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		
		if (programInfo.textureFlag == true) {
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, oneObj.objGroup[i]->uvBuffer);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, oneObj.objGroup[i]->mtlInfo.Texture->object());
			glUniform1i(programInfo.textureID, 0);
		}
			
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, oneObj.objGroup[i]->normalBuffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		
		glUniform3f(programInfo.mtlKaID, oneObj.objGroup[i]->mtlInfo.Ka.x, oneObj.objGroup[i]->mtlInfo.Ka.y, oneObj.objGroup[i]->mtlInfo.Ka.z);
		
		glUniform3f(programInfo.mtlKdID, oneObj.objGroup[i]->mtlInfo.Kd.x, oneObj.objGroup[i]->mtlInfo.Kd.y, oneObj.objGroup[i]->mtlInfo.Kd.z);
		
		glUniform3f(programInfo.mtlKsID, oneObj.objGroup[i]->mtlInfo.Ks.x, oneObj.objGroup[i]->mtlInfo.Ks.y, oneObj.objGroup[i]->mtlInfo.Ks.z);
		
		glUniform1f(programInfo.nsID, oneObj.objGroup[i]->mtlInfo.Ns);
		
		glDrawArrays(GL_TRIANGLES, 0, oneObj.objGroup[i]->size);
	}
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void setMVP() {
	computeMatricesFromInputs();
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	
	if(glfwGetKey(window, 'S')){
		std::cout << "haha\n";
	} else if(glfwGetKey(window, 'W')){
		
	}
	if(glfwGetKey(window, 'A')){
		
	} else if(glfwGetKey(window, 'D')){
		
	}
	if(glfwGetKey(window, 'Z')){
		
	} else if(glfwGetKey(window, 'X')){
		
	}
	 
	glUniformMatrix4fv(programInfo.mvpID, 1, GL_FALSE, &MVP[0][0]);
}


void deleteGL() {
	for (unsigned i = 0; i < oneObj.objGroup.size(); i++) {
		glDeleteBuffers(1, &oneObj.objGroup[i]->vertexBuffer);
		glDeleteBuffers(1, &oneObj.objGroup[i]->uvBuffer);
		glDeleteBuffers(1, &oneObj.objGroup[i]->normalBuffer);
	}
	glDeleteTextures(1, &programInfo.textureID);
	
	glDeleteVertexArrays(1, &oneObj.vertexArrayID);
	
	glDeleteProgram(programInfo.programID);
}


int main() {
	if (initGL() == -1) {
		return -1;
	}

	// buildObj() has to proceed initShaderParams(), or rendering cannot
	// be done properly. Don't know why yet
	programInfo.textureFlag = buildObj("qknight", oneObj);
	initprogramInfo();
	glUniform1f(programInfo.tFlagID, programInfo.textureFlag);
	
	setLights(programInfo.programID);
	
	std::cout << "what about here?\n";

	do {
		setMVP();
		drawAtIndex();
		glfwSwapBuffers(window);
		glfwPollEvents();
		
		// check for errors
		/*
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
			std::cerr << "OpenGL Error " << error << std::endl;
		*/
		
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	
	deleteGL();

	glfwTerminate();
	
	return 0;
}










