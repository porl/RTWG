/* 
 * File:   camaraHandler.cpp
 * Author: tg
 * 
 * Created on 19. Februar 2015, 08:24
 */

#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Camera.h"


void camaraHandler::Update(uint64_t time)
{
    camera_direction = glm::normalize(camera_look_at - camera_position);
    
    glm::vec3 axis = glm::cross(camera_direction,camera_up);
    glm::quat pitch_quat = glm::angleAxis(pitch ,camera_up);
    glm::quat roll_quat = glm::angleAxis(roll ,axis);
    glm::quat temp = glm::cross(pitch_quat,roll_quat);
    temp = glm::normalize(temp);
    
    camera_direction = glm::rotate(temp,camera_direction);
    camera_position += camera_position_delta;
    camera_look_at = camera_position + camera_direction * 1.0f;
    camera_position_delta = glm::vec3(0.0);
    pitch *= 0.1;
    roll *= 0.1;
}

void camaraHandler::SetPitch(double degrees)
{
    if(degrees < -max_pitch)
    {
        degrees = -max_pitch;
    }
    else if(degrees >  max_pitch)
    {
        degrees =  max_pitch;
    }
    
    pitch += degrees;
    
    if(pitch > 360.0f)
    {
        pitch -= 360.0f;
    }
    else if(pitch < -360.0f)
    {
        pitch += 360.0f;
    }    
}

void camaraHandler::SetRoll(double degrees)
{
    if(degrees < -max_roll)
    {
        degrees = -max_roll;
    }
    else if(degrees >  max_roll)
    {
        degrees =  max_roll;
    }
    
    roll += degrees;
    
    if(roll > 360.0f)
    {
        roll -= 360.0f;
    }
    else if(roll < -360.0f)
    {
        roll += 360.0f;
    }        
}

void camaraHandler::SetYaw(double degrees)
{
    if(degrees < -max_yaw)
    {
        degrees = -max_yaw;
    }
    else if(degrees >  max_yaw)
    {
        degrees =  max_yaw;
    }
    
    yaw += degrees;
    
    if(yaw > 360.0f)
    {
        yaw -= 360.0f;
    }
    else if(yaw < -360.0f)
    {
        yaw += 360.0f;
    }        
}

void camaraHandler::MoveX(double distance)
{
    camera_position_delta += glm::cross(camera_direction,camera_up) * (float)distance;

}

void camaraHandler::MoveY(double distance)
{
    camera_position_delta += camera_up * (float)distance;
}

void camaraHandler::MoveZ(double distance)
{
    camera_position_delta += camera_direction * (float)distance;
}

void camaraHandler::MoveHead(double x, double y)
{
   
    SetPitch(x);
    SetRoll(y);
    
}

void camaraHandler::setViewport(int x, int y, int width,  int height)
{
    viewport_x = x;
    viewport_y = y;
    window_width = width;
    window_heigth = height;
    aspect = (double)width/ (double)height;
    projection = glm::perspective(field_of_view,aspect,near_clip,far_clip);
}

void camaraHandler::setClipping(double near_clip, double far_clip)
{
    this->near_clip = near_clip;
    this->far_clip = far_clip;
    projection = glm::perspective(field_of_view,aspect,near_clip,far_clip);
}

glm::mat4 camaraHandler::getProjection()
{
    return projection;
}

glm::mat4 camaraHandler::getView()
{
    return glm::lookAt(camera_look_at,camera_position,camera_up);
}



void camaraHandler::loadViewPort() 
{
    glViewport(viewport_x,viewport_y,window_width,window_heigth);
}


void camaraHandler::SetCamera_look_at(glm::vec3 camera_look_at) 
{
    this->camera_look_at = camera_look_at;
}

void camaraHandler::SetCamera_position(glm::vec3 camera_position) 
{
    this->camera_position = camera_position;
}

void camaraHandler::SetMove_camera(bool move_camera) 
{
    this->move_camera = move_camera;
}

void camaraHandler::SetField_of_view(double field_of_view) 
{
    this->field_of_view = field_of_view;
    projection = glm::perspective(field_of_view,aspect,near_clip,far_clip);
}

void camaraHandler::SetAspect(double aspect) {
    this->aspect = aspect;
}

glm::vec2 camaraHandler::getViewPort()
{
    return glm::vec2(viewport_x,viewport_y);
}
