#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include "../../lib/glm/gtc/type_ptr.hpp"
#include "../../lib/glm/gtc/matrix_transform.hpp"

#include "../Shader.h"
#include "../Camera.h"
#include "../Mesh.h"
#include "../Editor.h"

class TransformComponent : public Component {
    public:
        TransformComponent(const glm::vec3& _translate, const glm::vec3& _scale, GLfloat _angle, const glm::vec3& _rotate)
            : model(glm::mat4(1.0f)), translate(_translate), scale(_scale), angle(_angle), rotate(_rotate) {  }

        void initialize() override {
            model = glm::translate(model, translate);
            model = glm::scale(model, scale);
            model = glm::rotate(model, angle, rotate);
        }

        void update(float deltaTime) override {
            glUniformMatrix4fv(Editor::shaders[0]->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
        }

        void render() override {
            Editor::mesh[0]->RenderMesh();
        }

    private:
        glm::mat4 model;
        glm::vec3 translate;
        glm::vec3 scale;
        glm::vec3 rotate;
        GLfloat angle;
};

#endif