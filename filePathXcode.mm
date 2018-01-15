//
//  filePathXcode.m
//  OpenCVTest
//
//  Created by snie on 12/15/15.
//  Copyright © 2015 com.snie. All rights reserved.
//

#import "filePathXcode.hpp"
#import <Foundation/Foundation.h>

// returns the full path to the file `fileName` in the resources directory of the app bundle
std::string ResourcePath(std::string fileName) {
  NSString* fname = [NSString stringWithCString:fileName.c_str() encoding:NSUTF8StringEncoding];
  NSString* path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fname];
  return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}
