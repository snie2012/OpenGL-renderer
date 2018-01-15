//
//  snieTexture.cpp
//  SnieGL
//
//  Created by snie on 12/16/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#include "snieTexture.hpp"

void buildTexture (std::string& fileName, std::vector<mtlInfo *> &mtlGroup) {
	for (unsigned int i = 0; i < mtlGroup.size(); i++) {
		std::string texturePath = "Resource/obj/" + fileName + "/" + mtlGroup[i]->mapKd;
		//std::cout << "check point " << texturePath << "\n";
		tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(texturePath);
		bmp.flipVertically();
		mtlGroup[i]->Texture = new tdogl::Texture(bmp);
		//mtlGroup[i]->Texture = new tdogl::Texture;
		//loadTexture(texturePath, mtlGroup[i]->Texture);
	}
}
