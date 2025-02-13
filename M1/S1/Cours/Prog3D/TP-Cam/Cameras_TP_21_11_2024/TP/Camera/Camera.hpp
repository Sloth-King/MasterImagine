#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

class Camera
{
public: 

	void init();
	void update(float _deltaTime, GLFWwindow* _window);
	void updateInterface(float _deltaTime);
	void updateFreeInput(float _deltaTime, GLFWwindow* _window);
	void computeFinalView();

	glm::quat getRotation() const {return m_rotation;}
	glm::mat4 getViewMatrix() const {return m_viewMatrix;}
	glm::mat4 getProjectionMatrix() const {return m_projectionMatrix;}
	

	//NEW	
	void setPosition(glm::vec3 position);
	void setRotation(glm::quat rotation);
	bool isAttachedToTarget() const {return attachToTarget;}
	//These are for the failed camera third
	// float getDist() const {return m_dist;}
	// glm::vec3 getEulerAngle() const {return m_eulerAngle;} 
	void reset();
	void updateTransition(float _deltaTime);

private:

	enum InputType
	{
		mode1, 
		mode2,
		//controller 
	};

	//Camera parameters 
	float		m_fovDegree{ 45.0f };
	glm::vec3	m_position{ glm::vec3(0.f, 40.f, 0.f) };
	glm::vec3	m_eulerAngle{ glm::vec3(0.f, 0.f, 0.f) };
	glm::quat	m_rotation{};
	float		m_pitch_speed{};
	float		m_yaw_speed{};
	float 		m_speed{};
	InputType	m_inputType{ InputType::mode2 };
	bool		keyPressed{ false };
	//NEW
	bool		attachToTarget{false};	
	//float		m_dist; //failed camera third
	//NEWNEW
	bool m_inTransition{false};         
    float m_transitionDuration;   
    float m_transitionTimer;      
    glm::vec3 m_startPosition;           
    glm::quat m_startRotation;    
	bool transitioned{false};      



	//Interface option
	bool m_showImguiDemo{ false };

	//View
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
};