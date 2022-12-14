#include "objparser.h"
#include <filesystem>
namespace fs = std::filesystem;

std::vector<std::vector<float>> objParser::parse_tomato()  {
    std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
    parentDir = parentDir + "/final-veggies/resources/veggie_objects/Bob_The_Tomato_no_uvs.obj";
    std::ifstream myfile;
    myfile.open(parentDir);

    std::string objConts;
    std::string currLine;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> triangleData;
    std::vector<std::string> faceIndex;
    vertexData.clear();
    int currObjIndex = -1;
    if (myfile.is_open()) {
        while (std::getline(myfile, currLine)) {
            if (currLine.substr(0,2) == "# ") {
                continue;
            }
            if (currLine.substr(0,2) == "us") {
                faceIndex.push_back("-1");
                faceIndex.push_back("-1");
                faceIndex.push_back("-1");
            } else if (currLine.substr(0,2) == "v ") { //check vertices
                std::istringstream v(currLine.substr(2));
                glm::vec3 vert;
                float x,y,z;
                v>>x;v>>y;v>>z;
                vert=glm::vec3(x,y,z);
                vertices.push_back(vert);
            } else if(currLine.substr(0,2)=="vn"){  //check
                std::istringstream v(currLine.substr(3));
                glm::vec3 norm;
                float X, Y, Z;
                v>>X;v>>Y;v>>Z;
                norm=glm::vec3(X,Y,Z);
                normals.push_back(norm);
            } else if(currLine.substr(0,2)=="vt"){  //check
                std::istringstream v(currLine.substr(3));
                glm::vec2 tex;
                float U,V;
                v>>U;v>>V;
                tex=glm::vec2(U,V);
                textures.push_back(tex);
            } else if(currLine.substr(0,2)=="f "){
                std::string a,b,c; //to store mesh index
                std::istringstream v(currLine.substr(2));
                v>>a;v>>b;v>>c;

                faceIndex.push_back(a);
                faceIndex.push_back(b);
                faceIndex.push_back(c);
              }
        }
        for (int i = 0; i<faceIndex.size(); i++) {
            glm::vec3 vertexIndices;
            glm::vec3 normalIndices;
            glm::vec3 textureIndices;
            std::string s = faceIndex[i];
            if (s == "-1") {
                currObjIndex +=1 ;
                i++;
                i++;
                vertexData.push_back(std::vector<float>{});
            } else {
                int a = s.find("//");

                vertexIndices[0] = std::stoi(s.substr(0,a)) - 1;
                normalIndices[0] = std::stoi(s.substr(a+2)) - 1;
                i ++;
                s = faceIndex[i];
                a = s.find("//");
                vertexIndices[1] = std::stoi(s.substr(0,a)) -1;
                normalIndices[1] = std::stoi(s.substr(a+2)) -1;
                i ++;
                s = faceIndex[i];
                a = s.find("//");
                vertexIndices[2] = std::stoi(s.substr(0,a)) -1;
                normalIndices[2] = std::stoi(s.substr(a+2)) -1;
                vertexData[currObjIndex].push_back(vertices[vertexIndices[0]][0]); //vertex1
                vertexData[currObjIndex].push_back(vertices[vertexIndices[0]][1]);
                vertexData[currObjIndex].push_back(vertices[vertexIndices[0]][2]);
                vertexData[currObjIndex].push_back(normals[normalIndices[0]][0]); //normal1
                vertexData[currObjIndex].push_back(normals[normalIndices[0]][1]);
                vertexData[currObjIndex].push_back(normals[normalIndices[0]][2]);

                vertexData[currObjIndex].push_back(vertices[vertexIndices[1]][0]); //vertex2
                vertexData[currObjIndex].push_back(vertices[vertexIndices[1]][1]);
                vertexData[currObjIndex].push_back(vertices[vertexIndices[1]][2]);
                vertexData[currObjIndex].push_back(normals[normalIndices[1]][0]); //normal2
                vertexData[currObjIndex].push_back(normals[normalIndices[1]][1]);
                vertexData[currObjIndex].push_back(normals[normalIndices[1]][2]);

                vertexData[currObjIndex].push_back(vertices[vertexIndices[2]][0]); //vertex3
                vertexData[currObjIndex].push_back(vertices[vertexIndices[2]][1]);
                vertexData[currObjIndex].push_back(vertices[vertexIndices[2]][2]);
                vertexData[currObjIndex].push_back(normals[normalIndices[2]][0]); //normal3
                vertexData[currObjIndex].push_back(normals[normalIndices[2]][1]);
                vertexData[currObjIndex].push_back(normals[normalIndices[2]][2]);

            }

        } //in theory, at this point a face has been added to the vertexData and i has successfully incremented by 3
        return vertexData;
    } else {
        std::cout << "Couldn't open file\n";
    }
        return std::vector<std::vector<float>>();
}
