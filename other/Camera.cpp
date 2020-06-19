#include <Camera/Camera.h>

Camera::Camera (glm::vec3 newPosition)
{
    position = newPosition;

    pitch = 0.0f;
    yaw = -90.0f;
    speed = 2.5f;
    sensitivity = 0.1f;
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    Camera::updateVectors();
}

Camera::~Camera (void) {}

glm::mat4 Camera::getViewMatrix (void)
{
    return glm::lookAt( position, position + front, up );
}

void Camera::keyboard (CameraMovement direction, float deltaTime)
{
    float velocity = deltaTime * speed;

    if( direction == FORWARD )
        position += front * velocity;
    if( direction == BACKWARD )
        position -= front * velocity;
    if( direction == LEFT )
        position -= right * velocity;
    if( direction == RIGHT )
        position += right * velocity;
}

void Camera::mouse (float xOffset, float yOffset)
{
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw = glm::mod( yaw+xOffset, 360.0f );
    pitch += yOffset;

    if( pitch > 89.0f )
        pitch = 89.0f;
    if( pitch < -89.0f )
        pitch = -89.0f;

    Camera::updateVectors();
}

void Camera::updateVectors (void)
{
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(newFront);
    right = glm::normalize( glm::cross(front, worldUp) );
    up = glm::normalize( glm::cross(right, front) );
}
