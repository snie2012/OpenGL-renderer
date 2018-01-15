//
//  mtlParser.cpp
//  SnieGL
//
//  Created by snie on 12/16/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#include "mtlParser.hpp"

void parseMtl(std::string& fileName, std::vector<mtlInfo *> &mtlGroup) {
	std::string mtlPath = "Resource/obj/" + fileName + "/" + fileName + ".mtl";
	
	std::ifstream file(mtlPath);
	std::string line;
	std::string name;
	
	int group = -1;
	
	while (std::getline(file, line)) {
		if (line == "" || line[0] == '#') {
			continue;
		};
		
		std::istringstream lineStream(line);
		lineStream >> name;
		
		if (name == "newmtl") {
			group++;
			mtlGroup.push_back(new mtlInfo());
			lineStream >> mtlGroup[group]->newmtl;
		} else if (name == "Ns") {
			sscanf(line.c_str(), "%*s %f", &mtlGroup[group]->Ns);
		} else if (name == "Ka") {
			sscanf(line.c_str(), "%*s %f %f %f", &mtlGroup[group]->Ka.x, &mtlGroup[group]->Ka.y, &mtlGroup[group]->Ka.z);
		} else if (name == "Kd") {
			sscanf(line.c_str(), "%*s %f %f %f", &mtlGroup[group]->Kd.x, &mtlGroup[group]->Kd.y, &mtlGroup[group]->Kd.z);
		} else if (name == "Ks") {
			sscanf(line.c_str(), "%*s %f %f %f", &mtlGroup[group]->Ks.x, &mtlGroup[group]->Ks.y, &mtlGroup[group]->Ks.z);
		} else if (name == "map_Kd") {
			lineStream >> mtlGroup[group]->mapKd;
		} else {
			continue;
		}
	}
}