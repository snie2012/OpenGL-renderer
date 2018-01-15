//
//  buildObj.cpp
//  SnieGL
//
//  Created by snie on 12/16/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#include "buildObj.hpp"

bool buildObj(std::string fileName, OneObj &oneObj) {
	std::vector<ObjGroup *> objInfo;
	parseObj(fileName, objInfo);
	
	bool textureFlag = true;
	if (objInfo.size() != 0) {
		objInfo[0]->txtcoords.size() == 0 ? textureFlag = false : NULL;
	} else {
		std::cout << objInfo.size() << "\n";
		std::cout << "error!\n";
		exit(0);
	}
	
	std::vector<mtlInfo *> mtlGroup;
	parseMtl(fileName, mtlGroup);
	
	if (textureFlag == true) {
		buildTexture(fileName, mtlGroup);
	}
	
	glGenVertexArrays(1, &oneObj.vertexArrayID);
	glBindVertexArray(oneObj.vertexArrayID);
	
	
	for (unsigned int i = 0; i < objInfo.size(); i++) {
		oneObj.objGroup.push_back(new objBuffer());
		
		oneObj.objGroup[i]->mtl = objInfo[i]->usemtl;
		oneObj.objGroup[i]->size = (int) objInfo[i]->vertices.size();
		
		glGenBuffers(1, &oneObj.objGroup[i]->vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, oneObj.objGroup[i]->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, objInfo[i]->vertices.size() * sizeof(glm::vec3), &objInfo[i]->vertices[0], GL_STATIC_DRAW);
		
		if (textureFlag == true) {
			glGenBuffers(1, &oneObj.objGroup[i]->uvBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, oneObj.objGroup[i]->uvBuffer);
			glBufferData(GL_ARRAY_BUFFER, objInfo[i]->txtcoords.size() * sizeof(glm::vec2), &objInfo[i]->txtcoords[0], GL_STATIC_DRAW);
		};
		
		glGenBuffers(1, &oneObj.objGroup[i]->normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, oneObj.objGroup[i]->normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, objInfo[i]->normals.size() * sizeof(glm::vec3), &objInfo[i]->normals[0], GL_STATIC_DRAW);
		
		for (unsigned int j = 0; j < mtlGroup.size(); j++) {
			if (oneObj.objGroup[i]->mtl == mtlGroup[j]->newmtl) {
				oneObj.objGroup[i]->mtlInfo = *mtlGroup[j];
			}
		}
	}
	
	//glBindVertexArray(0);
	
	return textureFlag;
}
