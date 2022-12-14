#include "objparser.h"
//#include "utils/scenefilereader.h"

//bool SceneParser::parse(std::string filepath, RenderData &renderData) {
////    ScenefileReader fileReader = ScenefileReader(filepath);
//    bool success = fileReader.readXML();
//    if (!success) {
//        return false;
//    }

//    // TODO: Use your code from Lab 5 here.
//    // Task 4: populate renderData with global data, lights, and camera data
//    renderData.globalData = fileReader.getGlobalData();
//    renderData.lights = fileReader.getLights();
//    renderData.cameraData = fileReader.getCameraData();


//    // Task 5: populate renderData's list of primitives and their transforms.
//    //         This will involve traversing the scene graph, and we recommend you
//    //         create a helper function to do so!
//    auto rootNode = fileReader.getRootNode();
//    renderData.shapes.clear();
//    glm::mat4 emptyMat(1.0f);
//    renderData.shapes = treeSearcher(rootNode, emptyMat);


//    return true;
//}


//ATTEMPT WITH C++ STRINGS
// original attempt, leads to crazy triangles but good overall shape
//std::vector<float> objParser::parse_tomato()  {
//    std::ifstream myfile; myfile.open("C:/Users/cport/OneDrive/Desktop/CS1230/projects-realtime-colbster5/src/utils/Bob_The_Tomato_with_mesh.obj"); //change this to Bob obj file
////    "C:\Users\cport\OneDrive\Desktop\CS1230\projects-realtime-colbster5\src\utils\Bob_The_Tomato_with_mesh.obj"
//    std::string objConts;
//    std::string currLine;
//    std::vector<glm::vec3> vertices;
//    std::vector<glm::vec3> normals;
//    std::vector<glm::vec2> textures;
//    std::vector<glm::vec3> triangleData;
//    std::vector<std::string> faceIndex;
//    vertexData.clear();
////    std::vector<float> vertexData;
//    if (myfile.is_open()) {
//        while (std::getline(myfile, currLine)) {
////            std::cout << currLine << ": " << myfile.tellg() << '\n'; //useless printing
//            if (currLine.substr(0,2) == "# ") {
//                continue;
//            }
//            if (currLine.substr(0,2) == "v ") { //check vertices
//                std::istringstream v(currLine.substr(2));
//                glm::vec3 vert;
//                double x,y,z;
//                v>>x;v>>y;v>>z;
//                vert=glm::vec3(x,y,z);
//                vertices.push_back(vert);
//            } else if(currLine.substr(0,2)=="vn"){  //check
//                std::istringstream v(currLine.substr(3));
//                glm::vec3 norm;
//                float X, Y, Z;
//                v>>X;v>>Y;v>>Z;
//                norm=glm::vec3(X,Y,Z);
//                normals.push_back(norm);
//            } else if(currLine.substr(0,2)=="vt"){  //check
//                std::istringstream v(currLine.substr(3));
//                glm::vec2 tex;
//                int U,V;
//                v>>U;v>>V;
//                tex=glm::vec2(U,V);
//                textures.push_back(tex);
//            } else if(currLine.substr(0,2)=="f "){
//                std::string a,b,c; //to store mesh index
//                int A,B,C; //to store texture index
//                std::istringstream v(currLine.substr(2));
////                const char* chh=currLine.c_str();
////                sscanf (chh, "f %i/%i %i/%i %i/%i",&a,&A,&b,&B,&c,&C); //here it read the line start with f and store the corresponding values in the variables
//                v>>a;v>>b;v>>c;
////                a--;b--;c--;
////                A--;B--;C--;
//                //std::cout<<a<<b<<c<<A<<B<<C;
//                faceIndex.push_back(a);
//                faceIndex.push_back(b);
//                faceIndex.push_back(c);
//              }
//        }
//        for (int i = 0; i<faceIndex.size(); i++) {
//            glm::vec3 vertexIndices;
//            glm::vec3 normalIndices;
//            std::string s = faceIndex[i];
//            int a = s.find("//");
////            std::cout << s << std::endl;
////            std::cout << s.substr(0,a) << std::endl;
////            std::cout << s.substr(a+2) << std::endl;

//            vertexIndices[0] = std::stoi(s.substr(0,a));
//            normalIndices[0] = std::stoi(s.substr(a+2));
//            i ++;
//            s = faceIndex[i];
//            a = s.find("//");
//            vertexIndices[1] = std::stoi(s.substr(0,a));
//            normalIndices[1] = std::stoi(s.substr(a+2));
//            i ++;
//            s = faceIndex[i];
//            a = s.find("//");
//            vertexIndices[2] = std::stoi(s.substr(0,a));
//            normalIndices[2] = std::stoi(s.substr(a+2));
//            vertexData.push_back(vertices[vertexIndices[0]][0]); //vertex1
//            vertexData.push_back(vertices[vertexIndices[0]][1]);
//            vertexData.push_back(vertices[vertexIndices[0]][2]);
//            vertexData.push_back(vertices[vertexIndices[1]][0]); //vertex2
//            vertexData.push_back(vertices[vertexIndices[1]][1]);
//            vertexData.push_back(vertices[vertexIndices[1]][2]);
//            vertexData.push_back(vertices[vertexIndices[2]][0]); //vertex3
//            vertexData.push_back(vertices[vertexIndices[2]][1]);
//            vertexData.push_back(vertices[vertexIndices[2]][2]);
//            vertexData.push_back(normals[normalIndices[0]][0]); //normal1
//            vertexData.push_back(normals[normalIndices[0]][1]);
//            vertexData.push_back(normals[normalIndices[0]][2]);
//            vertexData.push_back(normals[normalIndices[1]][0]); //normal2
//            vertexData.push_back(normals[normalIndices[1]][1]);
//            vertexData.push_back(normals[normalIndices[1]][2]);
//            vertexData.push_back(normals[normalIndices[2]][0]); //normal3
//            vertexData.push_back(normals[normalIndices[2]][1]);
//            vertexData.push_back(normals[normalIndices[2]][2]);
//            int randInt = rand() % 1500;
//            if (randInt == 345) {
//                std::cout << vertexIndices[0] << " " << vertexIndices[1] << " " << vertexIndices[2] <<std::endl;
//                std::cout << normalIndices[0] << " " << normalIndices[1] << " " << normalIndices[2] <<std::endl;
//            }
//        } //in theory, at this point a face has been added to the vertexData and i has successfully incremented by 3
//        return vertexData;
//    } else {
//        std::cout << "Couldn't open file\n";
//    }
//        return std::vector<float>();


//}
std::vector<std::vector<float>> objParser::parse_tomato()  {
    std::ifstream myfile; myfile.open("C:/Users/cport/OneDrive/Desktop/CS1230/final-veggies/resources/veggie_objects/Bob_The_Tomato_no_uvs.obj"); //change this to Bob obj file
//    "C:/Users/cport/OneDrive/Desktop/CS1230/projects-realtime-colbster5/src/utils/Bob_The_Tomato_pos_X_posY.obj"
//    "C:\Users\cport\OneDrive\Desktop\CS1230\projects-realtime-colbster5\src\utils\Bob_The_Tomato_with_mesh.obj"
//    "C:/Users/cport/OneDrive/Desktop/CS1230/projects-realtime-colbster5/src/utils/Larry The Cucumber_with_mesh_neg_Z_pos_Y.obj"

    std::string objConts;
    std::string currLine;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> triangleData;
    std::vector<std::string> faceIndex;
//    std::vector<std::vector<float>> retData;
    vertexData.clear();
    int currObjIndex = -1;
//    std::vector<float> vertexData;
    if (myfile.is_open()) {
        while (std::getline(myfile, currLine)) {
//            std::cout << currLine << ": " << myfile.tellg() << '\n'; //useless printing
//            std::cout << currLine << std::endl;
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
//                int A,B,C; //to store texture index
                std::istringstream v(currLine.substr(2));
//                const char* chh=currLine.c_str();
//                sscanf (chh, "f %i/%i %i/%i %i/%i",&a,&A,&b,&B,&c,&C); //here it read the line start with f and store the corresponding values in the variables
                v>>a;v>>b;v>>c;
//                a--;b--;c--;
//                A--;B--;C--;
                //std::cout<<a<<b<<c<<A<<B<<C;
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
            } else /*if (s.find("//") != std::string::npos)*/ {  //found // that means there are no uv cords
                int a = s.find("//");
    //            std::cout << s << std::endl;
    //            std::cout << s.substr(0,a) << std::endl;
    //            std::cout << s.substr(a+2) << std::endl;

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
//                vertexData[currObjIndex].push_back(2);
//                vertexData[currObjIndex].push_back(2); //out-of-bounds temp uv
                vertexData[currObjIndex].push_back(vertices[vertexIndices[1]][0]); //vertex2
                vertexData[currObjIndex].push_back(vertices[vertexIndices[1]][1]);
                vertexData[currObjIndex].push_back(vertices[vertexIndices[1]][2]);
                vertexData[currObjIndex].push_back(normals[normalIndices[1]][0]); //normal2
                vertexData[currObjIndex].push_back(normals[normalIndices[1]][1]);
                vertexData[currObjIndex].push_back(normals[normalIndices[1]][2]);
//                vertexData[currObjIndex].push_back(2);
//                vertexData[currObjIndex].push_back(2); //out-of-bounds temp uv
                vertexData[currObjIndex].push_back(vertices[vertexIndices[2]][0]); //vertex3
                vertexData[currObjIndex].push_back(vertices[vertexIndices[2]][1]);
                vertexData[currObjIndex].push_back(vertices[vertexIndices[2]][2]);
                vertexData[currObjIndex].push_back(normals[normalIndices[2]][0]); //normal3
                vertexData[currObjIndex].push_back(normals[normalIndices[2]][1]);
                vertexData[currObjIndex].push_back(normals[normalIndices[2]][2]);
//                vertexData[currObjIndex].push_back(2);
//                vertexData[currObjIndex].push_back(2); //out-of-bounds temp uv
            }
//            int randInt = rand() % 150;
//            if (randInt == 35) {
//                std::cout << vertexIndices[0] << " " << vertexIndices[1] << " " << vertexIndices[2] <<std::endl;
//                std::cout << vertices[vertexIndices[0]][0] << " " << vertices[vertexIndices[0]][1] << " " << vertices[vertexIndices[0]][2] << std::endl;
//                std::cout << vertices[vertexIndices[1]][0] << " " << vertices[vertexIndices[1]][1] << " " << vertices[vertexIndices[1]][2] << std::endl;
//                std::cout << vertices[vertexIndices[2]][0] << " " << vertices[vertexIndices[2]][1] << " " << vertices[vertexIndices[2]][2] << std::endl;
//                std::cout << normalIndices[0] << " " << normalIndices[1] << " " << normalIndices[2] <<std::endl;
//                std::cout << normals[normalIndices[0]][0] << " " << normals[normalIndices[0]][1] << " " << normals[normalIndices[0]][2] << std::endl;
//                std::cout << normals[normalIndices[1]][0] << " " << normals[normalIndices[1]][1] << " " << normals[normalIndices[1]][2] << std::endl;
//                std::cout << normals[normalIndices[2]][0] << " " << normals[normalIndices[2]][1] << " " << normals[normalIndices[2]][2] << std::endl;
//                std::cout << textureIndices[0] << " " << textureIndices[1] << " " << textureIndices[2] <<std::endl;
//                std::cout << textures[textureIndices[0]][0] << " " << textures[textureIndices[0]][1] << std::endl;
//                std::cout << textures[textureIndices[1]][0] << " " << textures[textureIndices[1]][1] << std::endl;
//                std::cout << textures[textureIndices[2]][0] << " " << textures[textureIndices[2]][1] << std::endl;


//            }
        } //in theory, at this point a face has been added to the vertexData and i has successfully incremented by 3
        return vertexData;
    } else {
        std::cout << "Couldn't open file\n";
    }
        return std::vector<std::vector<float>>();


}

//std::vector<std::vector<float>> objParser::parse_tomato()  {
//    std::ifstream myfile; myfile.open("C:/Users/cport/OneDrive/Desktop/CS1230/projects-realtime-colbster5/src/utils/Larry The Cucumber_uv_normals.obj"); //change this to Bob obj file
////    "C:/Users/cport/OneDrive/Desktop/CS1230/projects-realtime-colbster5/src/utils/Bob_The_Tomato_pos_X_posY.obj"
////    "C:\Users\cport\OneDrive\Desktop\CS1230\projects-realtime-colbster5\src\utils\Bob_The_Tomato_with_mesh.obj"
////    "C:/Users/cport/OneDrive/Desktop/CS1230/projects-realtime-colbster5/src/utils/Larry The Cucumber_with_mesh_neg_Z_pos_Y.obj"
//    std::string objConts;
//    std::string currLine;
//    std::vector<glm::vec3> vertices;
//    std::vector<glm::vec3> normals;
//    std::vector<glm::vec2> textures;
//    std::vector<glm::vec3> triangleData;
//    std::vector<std::string> faceIndex;
////    std::vector<std::vector<float>> retData;
//    vertexData.clear();
//    int currObjIndex = 0;
////    std::vector<float> vertexData;
//    if (myfile.is_open()) {
//        while (std::getline(myfile, currLine)) {
////            std::cout << currLine << ": " << myfile.tellg() << '\n'; //useless printing
////            std::cout << currLine << std::endl;
//            if (currLine.substr(0,2) == "# ") {
//                continue;
//            }
//            if (currLine.substr(0,2) == "us") {
//                faceIndex.push_back("-1");
//                faceIndex.push_back("-1");
//                faceIndex.push_back("-1");
//            } else if (currLine.substr(0,2) == "v ") { //check vertices
//                std::istringstream v(currLine.substr(2));
//                glm::vec3 vert;
//                float x,y,z;
//                v>>x;v>>y;v>>z;
//                vert=glm::vec3(x,y,z);
//                vertices.push_back(vert);
//            } else if(currLine.substr(0,2)=="vn"){  //check
//                std::istringstream v(currLine.substr(3));
//                glm::vec3 norm;
//                float X, Y, Z;
//                v>>X;v>>Y;v>>Z;
//                norm=glm::vec3(X,Y,Z);
//                normals.push_back(norm);
//            } else if(currLine.substr(0,2)=="vt"){  //check
//                std::istringstream v(currLine.substr(3));
//                glm::vec2 tex;
//                float U,V;
//                v>>U;v>>V;
//                tex=glm::vec2(U,V);
//                textures.push_back(tex);
//            } else if(currLine.substr(0,2)=="f "){
//                std::string a,b,c; //to store mesh index
////                int A,B,C; //to store texture index
//                std::istringstream v(currLine.substr(2));
////                const char* chh=currLine.c_str();
////                sscanf (chh, "f %i/%i %i/%i %i/%i",&a,&A,&b,&B,&c,&C); //here it read the line start with f and store the corresponding values in the variables
//                v>>a;v>>b;v>>c;
////                a--;b--;c--;
////                A--;B--;C--;
//                //std::cout<<a<<b<<c<<A<<B<<C;
//                faceIndex.push_back(a);
//                faceIndex.push_back(b);
//                faceIndex.push_back(c);
//              }
//        }
//        for (int i = 0; i<faceIndex.size(); i++) {
//            glm::vec3 vertexIndices;
//            glm::vec3 normalIndices;
//            glm::vec3 textureIndices;
//            std::string s = faceIndex[i];
//            if (s == "-1") {
//                currObjIndex +=1 ;
//            } else if (s.find("//") != std::string::npos) {  //found // that means there are no uv cords
//                int a = s.find("//");
//    //            std::cout << s << std::endl;
//    //            std::cout << s.substr(0,a) << std::endl;
//    //            std::cout << s.substr(a+2) << std::endl;

//                vertexIndices[0] = std::stoi(s.substr(0,a)) - 1;
//                normalIndices[0] = std::stoi(s.substr(a+2)) - 1;
//                i ++;
//                s = faceIndex[i];
//                a = s.find("//");
//                vertexIndices[1] = std::stoi(s.substr(0,a)) -1;
//                normalIndices[1] = std::stoi(s.substr(a+2)) -1;
//                i ++;
//                s = faceIndex[i];
//                a = s.find("//");
//                vertexIndices[2] = std::stoi(s.substr(0,a)) -1;
//                normalIndices[2] = std::stoi(s.substr(a+2)) -1;
//                vertexData[currObjIndex].push_back(vertices[vertexIndices[0]][0]); //vertex1
//                vertexData[currObjIndex].push_back(vertices[vertexIndices[0]][1]);
//                vertexData[currObjIndex].push_back(vertices[vertexIndices[0]][2]);
//                vertexData[currObjIndex].push_back(normals[normalIndices[0]][0]); //normal1
//                vertexData[currObjIndex].push_back(normals[normalIndices[0]][1]);
//                vertexData[currObjIndex].push_back(normals[normalIndices[0]][2]);
//                vertexData[currObjIndex].push_back(2);
//                vertexData[currObjIndex].push_back(2); //out-of-bounds temp uv
//                vertexData[currObjIndex].push_back(vertices[vertexIndices[1]][0]); //vertex2
//                vertexData[currObjIndex].push_back(vertices[vertexIndices[1]][1]);
//                vertexData[currObjIndex].push_back(vertices[vertexIndices[1]][2]);
//                vertexData[currObjIndex].push_back(normals[normalIndices[1]][0]); //normal2
//                vertexData[currObjIndex].push_back(normals[normalIndices[1]][1]);
//                vertexData[currObjIndex].push_back(normals[normalIndices[1]][2]);
//                vertexData[currObjIndex].push_back(2);
//                vertexData[currObjIndex].push_back(2); //out-of-bounds temp uv
//                vertexData[currObjIndex].push_back(vertices[vertexIndices[2]][0]); //vertex3
//                vertexData[currObjIndex].push_back(vertices[vertexIndices[2]][1]);
//                vertexData[currObjIndex].push_back(vertices[vertexIndices[2]][2]);
//                vertexData[currObjIndex].push_back(normals[normalIndices[2]][0]); //normal3
//                vertexData[currObjIndex].push_back(normals[normalIndices[2]][1]);
//                vertexData[currObjIndex].push_back(normals[normalIndices[2]][2]);
//                vertexData[currObjIndex].push_back(2);
//                vertexData[currObjIndex].push_back(2); //out-of-bounds temp uv
//            } else {
//                int a = s.find("/");
//                vertexIndices[0] = std::stoi(s.substr(0,a)) - 1;
//                int b = s.find("/", a+1);
//                textureIndices[0] = std::stoi(s.substr(a+1, b)) - 1;
//                normalIndices[0] = std::stoi(s.substr(b+1)) - 1;
//                i ++;
//                s = faceIndex[i];
//                a = s.find("/");
//                vertexIndices[1] = std::stoi(s.substr(0,a)) -1;
//                b = s.find("/", a+1);
//                textureIndices[1] = std::stoi(s.substr(a+1, b)) - 1;
//                normalIndices[1] = std::stoi(s.substr(b+1)) - 1;
//                i ++;
//                s = faceIndex[i];
//                a = s.find("/");
//                vertexIndices[2] = std::stoi(s.substr(0,a)) -1;
//                b = s.find("/", a+1);
//                textureIndices[2] = std::stoi(s.substr(a+1, b)) - 1;
//                normalIndices[2] = std::stoi(s.substr(b+1)) - 1;
//                vertexData.push_back(vertices[vertexIndices[0]][0]); //vertex1
//                vertexData.push_back(vertices[vertexIndices[0]][1]);
//                vertexData.push_back(vertices[vertexIndices[0]][2]);
//                vertexData.push_back(normals[normalIndices[0]][0]); //normal1
//                vertexData.push_back(normals[normalIndices[0]][1]);
//                vertexData.push_back(normals[normalIndices[0]][2]);
//                vertexData.push_back(textures[textureIndices[0]][0]);
//                vertexData.push_back(textures[textureIndices[0]][1]); //out-of-bounds temp uv
//                vertexData.push_back(vertices[vertexIndices[1]][0]); //vertex2
//                vertexData.push_back(vertices[vertexIndices[1]][1]);
//                vertexData.push_back(vertices[vertexIndices[1]][2]);
//                vertexData.push_back(normals[normalIndices[1]][0]); //normal2
//                vertexData.push_back(normals[normalIndices[1]][1]);
//                vertexData.push_back(normals[normalIndices[1]][2]);
//                vertexData.push_back(textures[textureIndices[1]][0]);
//                vertexData.push_back(textures[textureIndices[1]][1]); //out-of-bounds temp uv
//                vertexData.push_back(vertices[vertexIndices[2]][0]); //vertex3
//                vertexData.push_back(vertices[vertexIndices[2]][1]);
//                vertexData.push_back(vertices[vertexIndices[2]][2]);
//                vertexData.push_back(normals[normalIndices[2]][0]); //normal3
//                vertexData.push_back(normals[normalIndices[2]][1]);
//                vertexData.push_back(normals[normalIndices[2]][2]);
//                vertexData.push_back(textures[textureIndices[2]][0]);
//                vertexData.push_back(textures[textureIndices[2]][1]); //out-of-bounds temp uv
//            }

////            int randInt = rand() % 150;
////            if (randInt == 35) {
////                std::cout << vertexIndices[0] << " " << vertexIndices[1] << " " << vertexIndices[2] <<std::endl;
////                std::cout << vertices[vertexIndices[0]][0] << " " << vertices[vertexIndices[0]][1] << " " << vertices[vertexIndices[0]][2] << std::endl;
////                std::cout << vertices[vertexIndices[1]][0] << " " << vertices[vertexIndices[1]][1] << " " << vertices[vertexIndices[1]][2] << std::endl;
////                std::cout << vertices[vertexIndices[2]][0] << " " << vertices[vertexIndices[2]][1] << " " << vertices[vertexIndices[2]][2] << std::endl;
////                std::cout << normalIndices[0] << " " << normalIndices[1] << " " << normalIndices[2] <<std::endl;
////                std::cout << normals[normalIndices[0]][0] << " " << normals[normalIndices[0]][1] << " " << normals[normalIndices[0]][2] << std::endl;
////                std::cout << normals[normalIndices[1]][0] << " " << normals[normalIndices[1]][1] << " " << normals[normalIndices[1]][2] << std::endl;
////                std::cout << normals[normalIndices[2]][0] << " " << normals[normalIndices[2]][1] << " " << normals[normalIndices[2]][2] << std::endl;
////                std::cout << textureIndices[0] << " " << textureIndices[1] << " " << textureIndices[2] <<std::endl;
////                std::cout << textures[textureIndices[0]][0] << " " << textures[textureIndices[0]][1] << std::endl;
////                std::cout << textures[textureIndices[1]][0] << " " << textures[textureIndices[1]][1] << std::endl;
////                std::cout << textures[textureIndices[2]][0] << " " << textures[textureIndices[2]][1] << std::endl;


////            }
//        } //in theory, at this point a face has been added to the vertexData and i has successfully incremented by 3
//        return vertexData;
//    } else {
//        std::cout << "Couldn't open file\n";
//    }
//        return std::vector<float>();


//}

//std::vector<float> objParser::parse_tomato_quads()  {
//    std::ifstream myfile; myfile.open("C:/Users/cport/OneDrive/Desktop/CS1230/projects-realtime-colbster5/src/utils/Junior_Asparagus_Prototype.obj"); //change this to Bob obj file
////    "C:/Users/cport/OneDrive/Desktop/CS1230/projects-realtime-colbster5/src/utils/Bob_The_Tomato_pos_X_posY.obj"
////    "C:\Users\cport\OneDrive\Desktop\CS1230\projects-realtime-colbster5\src\utils\Bob_The_Tomato_with_mesh.obj"
//    std::string objConts;
//    std::string currLine;
//    std::vector<glm::vec3> vertices;
//    std::vector<glm::vec3> normals;
//    std::vector<glm::vec2> textures;
//    std::vector<glm::vec3> triangleData;
//    std::vector<std::string> faceIndex;
//    vertexData.clear();
////    std::vector<float> vertexData;
//    if (myfile.is_open()) {
//        while (std::getline(myfile, currLine)) {
////            std::cout << currLine << ": " << myfile.tellg() << '\n'; //useless printing
//            std::cout << currLine << std::endl;
//            if (currLine.substr(0,2) == "# ") {
//                continue;
//            }
//            if (currLine.substr(0,2) == "v ") { //check vertices
//                std::istringstream v(currLine.substr(2));
//                glm::vec3 vert;
//                float x,y,z;
//                v>>x;v>>y;v>>z;
//                vert=glm::vec3(x,y,z);
//                vertices.push_back(vert);
//            } else if(currLine.substr(0,2)=="vn"){  //check
//                std::istringstream v(currLine.substr(3));
//                glm::vec3 norm;
//                float X, Y, Z;
//                v>>X;v>>Y;v>>Z;
//                norm=glm::vec3(X,Y,Z);
//                normals.push_back(norm);
//            } else if(currLine.substr(0,2)=="vt"){  //check
//                std::istringstream v(currLine.substr(3));
//                glm::vec2 tex;
//                int U,V;
//                v>>U;v>>V;
//                tex=glm::vec2(U,V);
//                textures.push_back(tex);
//            } else if(currLine.substr(0,2)=="f "){
//                std::string a,b,c; //to store mesh index
//                int A,B,C; //to store texture index
//                std::istringstream v(currLine.substr(2));
////                const char* chh=currLine.c_str();
////                sscanf (chh, "f %i/%i %i/%i %i/%i",&a,&A,&b,&B,&c,&C); //here it read the line start with f and store the corresponding values in the variables
//                v>>a;v>>b;v>>c;
////                a--;b--;c--;
////                A--;B--;C--;
//                //std::cout<<a<<b<<c<<A<<B<<C;
//                faceIndex.push_back(a);
//                faceIndex.push_back(b);
//                faceIndex.push_back(c);
//              }
//        }
//        for (int i = 0; i<faceIndex.size(); i++) {
//            glm::vec3 vertexIndices;
//            glm::vec3 normalIndices;
//            std::string s = faceIndex[i];
//            int a = s.find("//");
////            std::cout << s << std::endl;
////            std::cout << s.substr(0,a) << std::endl;
////            std::cout << s.substr(a+2) << std::endl;

//            vertexIndices[0] = std::stoi(s.substr(0,a));
//            normalIndices[0] = std::stoi(s.substr(a+2));
//            i ++;
//            s = faceIndex[i];
//            a = s.find("//");
//            vertexIndices[1] = std::stoi(s.substr(0,a));
//            normalIndices[1] = std::stoi(s.substr(a+2));
//            i ++;
//            s = faceIndex[i];
//            a = s.find("//");
//            vertexIndices[2] = std::stoi(s.substr(0,a));
//            normalIndices[2] = std::stoi(s.substr(a+2));
//            vertexData.push_back(vertices[vertexIndices[0]][0]); //vertex1
//            vertexData.push_back(vertices[vertexIndices[0]][1]);
//            vertexData.push_back(vertices[vertexIndices[0]][2]);
//            vertexData.push_back(normals[normalIndices[0]][0]); //normal1
//            vertexData.push_back(normals[normalIndices[0]][1]);
//            vertexData.push_back(normals[normalIndices[0]][2]);
//            vertexData.push_back(vertices[vertexIndices[1]][0]); //vertex2
//            vertexData.push_back(vertices[vertexIndices[1]][1]);
//            vertexData.push_back(vertices[vertexIndices[1]][2]);
//            vertexData.push_back(normals[normalIndices[1]][0]); //normal2
//            vertexData.push_back(normals[normalIndices[1]][1]);
//            vertexData.push_back(normals[normalIndices[1]][2]);
//            vertexData.push_back(vertices[vertexIndices[2]][0]); //vertex3
//            vertexData.push_back(vertices[vertexIndices[2]][1]);
//            vertexData.push_back(vertices[vertexIndices[2]][2]);
//            vertexData.push_back(normals[normalIndices[2]][0]); //normal3
//            vertexData.push_back(normals[normalIndices[2]][1]);
//            vertexData.push_back(normals[normalIndices[2]][2]);
//            int randInt = rand() % 1500;
//            if (randInt == 35) {
//                std::cout << vertexIndices[0] << " " << vertexIndices[1] << " " << vertexIndices[2] <<std::endl;
//                std::cout << vertices[vertexIndices[0]][0] << " " << vertices[vertexIndices[0]][1] << " " << vertices[vertexIndices[0]][2] << std::endl;
//                std::cout << vertices[vertexIndices[1]][0] << " " << vertices[vertexIndices[1]][1] << " " << vertices[vertexIndices[1]][2] << std::endl;
//                std::cout << vertices[vertexIndices[2]][0] << " " << vertices[vertexIndices[2]][1] << " " << vertices[vertexIndices[2]][2] << std::endl;
//                std::cout << normalIndices[0] << " " << normalIndices[1] << " " << normalIndices[2] <<std::endl;
//                std::cout << normals[normalIndices[0]][0] << " " << normals[normalIndices[0]][1] << " " << normals[normalIndices[0]][2] << std::endl;
//                std::cout << normals[normalIndices[1]][0] << " " << normals[normalIndices[1]][1] << " " << normals[normalIndices[1]][2] << std::endl;
//                std::cout << normals[normalIndices[2]][0] << " " << normals[normalIndices[2]][1] << " " << normals[normalIndices[2]][2] << std::endl;

//            }
//        } //in theory, at this point a face has been added to the vertexData and i has successfully incremented by 3
//        return vertexData;
//    } else {
//        std::cout << "Couldn't open file\n";
//    }
//        return std::vector<float>();


//}


//std::vector<float> objParser::parse_cucumber()  {
//    std::ifstream myfile; myfile.open("C:/Users/cport/OneDrive/Desktop/CS1230/projects-realtime-colbster5/src/utils/Larry The Cucumber_with_mesh_neg_Z_pos_Y.obj"); //change this to Bob obj file
////    "C:\Users\cport\OneDrive\Desktop\CS1230\projects-realtime-colbster5\src\utils\Bob_The_Tomato_with_mesh.obj"

//    std::string objConts;
//    std::string currLine;
//    std::vector<glm::vec3> vertices;
//    std::vector<glm::vec3> normals;
//    std::vector<glm::vec2> textures;
//    std::vector<glm::vec3> triangleData;
//    std::vector<std::string> faceIndex;
//    vertexData.clear();
////    std::vector<float> vertexData;
//    if (myfile.is_open()) {
//        while (std::getline(myfile, currLine)) {
////            std::cout << currLine << ": " << myfile.tellg() << '\n'; //useless printing
//            if (currLine.substr(0,2) == "# ") {
//                continue;
//            }
//            if (currLine.substr(0,2) == "v ") { //check vertices
//                std::istringstream v(currLine.substr(2));
//                glm::vec3 vert;
//                double x,y,z;
//                v>>x;v>>y;v>>z;
//                vert=glm::vec3(x,y,z);
//                vertices.push_back(vert);
//            } else if(currLine.substr(0,2)=="vn"){  //check
//                std::istringstream v(currLine.substr(3));
//                glm::vec3 norm;
//                float X, Y, Z;
//                v>>X;v>>Y;v>>Z;
//                norm=glm::vec3(X,Y,Z);
//                normals.push_back(norm);
//            } else if(currLine.substr(0,2)=="vt"){  //check
//                std::istringstream v(currLine.substr(3));
//                glm::vec2 tex;
//                int U,V;
//                v>>U;v>>V;
//                tex=glm::vec2(U,V);
//                textures.push_back(tex);
//            } else if(currLine.substr(0,2)=="f "){
//                std::string a,b,c; //to store mesh index
//                int A,B,C; //to store texture index
//                std::istringstream v(currLine.substr(2));
////                const char* chh=currLine.c_str();
////                sscanf (chh, "f %i/%i %i/%i %i/%i",&a,&A,&b,&B,&c,&C); //here it read the line start with f and store the corresponding values in the variables
//                v>>a;v>>b;v>>c;
////                a--;b--;c--;
////                A--;B--;C--;
//                //std::cout<<a<<b<<c<<A<<B<<C;
//                faceIndex.push_back(a);
//                faceIndex.push_back(b);
//                faceIndex.push_back(c);
//              }
//        }
//        for (int i = 0; i<faceIndex.size(); i++) {
//            glm::vec3 vertexIndices;
//            glm::vec3 normalIndices;
//            std::string s = faceIndex[i];
//            int a = s.find("//");
////            std::cout << s << std::endl;
////            std::cout << s.substr(0,a) << std::endl;
////            std::cout << s.substr(a+2) << std::endl;

//            vertexIndices[0] = std::stoi(s.substr(0,a));
//            normalIndices[0] = std::stoi(s.substr(a+2));
//            i ++;
//            s = faceIndex[i];
//            a = s.find("//");
//            vertexIndices[1] = std::stoi(s.substr(0,a));
//            normalIndices[1] = std::stoi(s.substr(a+2));
//            i ++;
//            s = faceIndex[i];
//            a = s.find("//");
//            vertexIndices[2] = std::stoi(s.substr(0,a));
//            normalIndices[2] = std::stoi(s.substr(a+2));
//            vertexData.push_back(vertices[vertexIndices[0]][0]); //vertex1
//            vertexData.push_back(vertices[vertexIndices[0]][1]);
//            vertexData.push_back(vertices[vertexIndices[0]][2]);
//            vertexData.push_back(vertices[vertexIndices[1]][0]); //vertex2
//            vertexData.push_back(vertices[vertexIndices[1]][1]);
//            vertexData.push_back(vertices[vertexIndices[1]][2]);
//            vertexData.push_back(vertices[vertexIndices[2]][0]); //vertex3
//            vertexData.push_back(vertices[vertexIndices[2]][1]);
//            vertexData.push_back(vertices[vertexIndices[2]][2]);
//            vertexData.push_back(normals[normalIndices[0]][0]); //normal1
//            vertexData.push_back(normals[normalIndices[0]][1]);
//            vertexData.push_back(normals[normalIndices[0]][2]);
//            vertexData.push_back(normals[normalIndices[1]][0]); //normal2
//            vertexData.push_back(normals[normalIndices[1]][1]);
//            vertexData.push_back(normals[normalIndices[1]][2]);
//            vertexData.push_back(normals[normalIndices[2]][0]); //normal3
//            vertexData.push_back(normals[normalIndices[2]][1]);
//            vertexData.push_back(normals[normalIndices[2]][2]);
//            int randInt = rand() % 1500;
//            if (randInt == 345) {
//                std::cout << vertexIndices[0] << " " << vertexIndices[1] << " " << vertexIndices[2] <<std::endl;
//                std::cout << normalIndices[0] << " " << normalIndices[1] << " " << normalIndices[2] <<std::endl;
//            }
//        } //in theory, at this point a face has been added to the vertexData and i has successfully incremented by 3
//        return vertexData;
//    } else {
//        std::cout << "Couldn't open file\n";
//    }
//        return std::vector<float>();


//}



//ATTEMPT WITH CSTRING
//bool parseTomato() {
//    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
//    std::vector< glm::vec3 > temp_vertices;
//    std::vector< glm::vec2 > temp_uvs;
//    std::vector< glm::vec3 > temp_normals;
//    FILE * file = fopen("path", "r"); //replace path with actual filepath!!!!!!!!!
//    if( file == NULL ){
//        printf("Impossible to open the file !\n");
//        return false;
//    } else {
//        while (1) {

//        }
//    }
//}
