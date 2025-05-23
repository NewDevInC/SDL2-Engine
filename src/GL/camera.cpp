//
// Created by NewDevInC on 2.10.2024.
//

#include "camera.hpp"

glCamera::glCamera(float aspectRatio, glm::vec3 position) {
    this->aspectRatio = aspectRatio;
    this->position = position;
}

glCamera::glCamera(float aspectRatio, glm::vec3 position, float farPlane, float closePlane, float fov){
    this->aspectRatio = aspectRatio;
    this->position = position;

    this->farPlane = farPlane;
    this->closePlane = closePlane;
    this->fov = fov;
}


void glCamera::updateMatrix() {
    // Initializes matrices since otherwise they will be the null matrix
    auto view = glm::mat4(1.0f);
    auto projection = glm::mat4(1.0f);

    view = glm::lookAt(this->position, this->position + this->orientation, this->up);
    projection = glm::perspective(glm::radians(this->fov), this->aspectRatio, this->closePlane, this->farPlane);

    this->matrix = projection * view;

}

void glCamera::exportMatrix(glShader *shader, const char *uniform) {

    // Exports the camera matrix to the Vertex Shader
    glUniformMatrix4fv(glGetUniformLocation(shader->id, uniform), 1, GL_FALSE, glm::value_ptr(this->matrix));
}
