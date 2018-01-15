//
//  objParser.cpp
//  OpenCVTest
//
//  Created by snie on 12/15/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#include "objParser.hpp"

#include <string>

#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct GroupIndices {
	std::string usemtl;
	std::vector<unsigned int> vertexIndices, txtIndices, normalIndices;
};

void parseObj (std::string& fileName, std::vector<ObjGroup *> &objInfo) {
	std::string objPath = "Resource/obj/" + fileName + "/" + fileName + ".obj";
	
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempTxtcoords;
	std::vector<glm::vec3> tempNormals;
		
	std::ifstream file(objPath);
	std::string line;
	std::string name;
	
	int group = -1;
	//std::vector<GroupIndices> *groupInfo = new std::vector<GroupIndices>();
	std::vector<GroupIndices *> groupInfo;
	
	while (std::getline(file, line)) {
		if (line == "" || line[0] == '#')
			continue;
		
		std::istringstream lineStream(line);
		lineStream >> name;
		
		if (name == "v") {
			glm::vec3 vertex;
			sscanf(line.c_str(), "%*s %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		} else if (name == "vt") {
			glm::vec2 uv;
			sscanf(line.c_str(), "%*s %f %f", &uv.x, &uv.y);
			tempTxtcoords.push_back(uv);
		} else if (name == "vn") {
			glm::vec3 normal;
			sscanf(line.c_str(), "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		} else if (name == "usemtl") {
			group++;
			groupInfo.push_back(new GroupIndices());
			lineStream >> groupInfo[group]->usemtl;
		} else if (name == "f") {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = sscanf(line.c_str(), "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
			}
			groupInfo[group]->vertexIndices.push_back(vertexIndex[0]);
			groupInfo[group]->vertexIndices.push_back(vertexIndex[1]);
			groupInfo[group]->vertexIndices.push_back(vertexIndex[2]);
			groupInfo[group]->txtIndices.push_back(uvIndex[0]);
			groupInfo[group]->txtIndices.push_back(uvIndex[1]);
			groupInfo[group]->txtIndices.push_back(uvIndex[2]);
			groupInfo[group]->normalIndices.push_back(normalIndex[0]);
			groupInfo[group]->normalIndices.push_back(normalIndex[1]);
			groupInfo[group]->normalIndices.push_back(normalIndex[2]);
		} else {
			continue;
		}
	}
	
	for (unsigned int i = 0; i < groupInfo.size(); i ++) {
		objInfo.push_back(new ObjGroup());
		objInfo[i]->usemtl = groupInfo[i]->usemtl;
		for (unsigned int j = 0; j < groupInfo[i]->vertexIndices.size(); j++) {
			
			unsigned int vertexIndex = groupInfo[i]->vertexIndices[j];
			unsigned int uvIndex = groupInfo[i]->txtIndices[j];
			unsigned int normalIndex = groupInfo[i]->normalIndices[j];
			
			glm::vec3 vertex = tempVertices[vertexIndex-1];
			glm::vec3 normal = tempNormals[normalIndex-1];
			
			objInfo[i]->vertices.push_back(vertex);
			objInfo[i]->normals.push_back(normal);
			
			if (tempTxtcoords.size() > 0) {
				glm::vec2 uv = tempTxtcoords[uvIndex-1];
				objInfo[i]->txtcoords.push_back(uv);
			}
		}
	}
}