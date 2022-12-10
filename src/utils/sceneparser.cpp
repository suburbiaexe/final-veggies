#include "sceneparser.h"
#include "scenefilereader.h"
#include "glm/gtx/transform.hpp"

#include <chrono>
#include <memory>
#include <iostream>


/**
 * @brief DFS
 * @param node
 * @param ctm
 * @return list of shapes in the scene
 */
std::vector<RenderShapeData> DFS(SceneNode* node, glm::mat4 ctm) {
    std::vector<RenderShapeData> shapes;
    for (int i = 0; i < node->transformations.size(); i++) {
        if (node->transformations[i]->type == TransformationType::TRANSFORMATION_TRANSLATE) {
            ctm *= glm::translate(node->transformations[i]->translate);
        } else if (node->transformations[i]->type == TransformationType::TRANSFORMATION_SCALE) {
            ctm *= glm::scale(node->transformations[i]->scale);
        } else if (node->transformations[i]->type == TransformationType::TRANSFORMATION_ROTATE) {
            ctm *= glm::rotate(node->transformations[i]->angle, node->transformations[i]->rotate);
        } else if (node->transformations[i]->type == TransformationType::TRANSFORMATION_MATRIX) {
            ctm *= node->transformations[i]->matrix;
        }
    }
    for (ScenePrimitive *primitive : node->primitives) {
        shapes.push_back(RenderShapeData{*primitive, ctm});
    }
    for (int i = 0; i < node->children.size(); i++) {
        std::vector<RenderShapeData> childdata = DFS(node->children[i], ctm);
        shapes.insert(shapes.end(), childdata.begin(), childdata.end());
    }
    return shapes;
}

/**
 * @brief SceneParser::parse
 * @param filepath
 * @param renderData
 * @return boolean representing if scene parsing was successful
 */
bool SceneParser::parse(std::string filepath, RenderData &renderData) {
    ScenefileReader fileReader = ScenefileReader(filepath);
    bool success = fileReader.readXML();
    if (!success) {
        return false;
    }

    renderData.globalData = fileReader.getGlobalData();
    renderData.lights = fileReader.getLights();
    renderData.cameraData = fileReader.getCameraData();
    renderData.shapes.clear();
    renderData.shapes = DFS(fileReader.getRootNode(), glm::mat4(1.0f));

    return true;
}
