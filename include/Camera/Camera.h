#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
    public:
        Camera (glm::vec3 position);
        ~Camera (void);
        
        glm::mat4 getViewMatrix (void);
        void keyboard (CameraMovement direction, float deltaTime);
        void mouse (float xOffset, float yOffset);

    private:
        float pitch;
        float yaw;
        float speed;
        float sensitivity;

        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 worldUp;
        glm::vec3 up;
        glm::vec3 right;

        void updateVectors (void);
        Camera (void);
};

#endif
