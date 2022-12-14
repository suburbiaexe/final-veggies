#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>

class objParser {
public:
    std::vector<std::vector<float>> parse_tomato();
    std::vector<float> parse_cucumber();
    std::vector<std::vector<float>> vertexData;
};

/* Plan for importing tomato obj:
 *   parse the obj file
 *      add the vertex, normal, and uv data to a vector of floats
 *      have a different vector of floats per material
 *   parse the mtl file
 *      for each material, have a vector a floats that just has the relevant values in it (in the order the come in in the mtl file)
 *      when we do the lighting, just put these values in for ka,kd,ks,specular, etc
 *
 *
 *   How do I link the objects with their associated mtl files???
 */



//#endif // OBJPARSER_H
