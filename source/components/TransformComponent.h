#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../EntityManager.h"
#include "../Shader.h"
#include "../Camera.h"
#include "../Mesh.h"
#include "../Editor.h"

class TransformComponent : public Component {
    public:
        glm::mat4 model;
        glm::vec2 translate;
        glm::vec2 scale;
        glm::vec2 rotate;
        float angle;

        TransformComponent(const glm::vec2& _translate, const glm::vec2& _scale, float _angle, const glm::vec2& _rotate)
            : model(glm::mat4(1.0f)), translate(_translate), scale(_scale), angle(_angle), rotate(_rotate) {  }

        void initialize() override {

        }

        void update(float deltaTime) override {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-translate, 0.0f));
            model = glm::scale(model, glm::vec3(scale, 1.0f));
            model = glm::rotate(model, angle, glm::vec3(rotate, 1.0f));

            glUniformMatrix4fv(Editor::shaders[0]->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
        }

        void render() override {

        }
};

#endif