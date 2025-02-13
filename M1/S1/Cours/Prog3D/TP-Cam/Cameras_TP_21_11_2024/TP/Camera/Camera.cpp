#include <TP/Camera/Camera.hpp>
#include <TP/Camera/Camera_Helper.hpp>


// Include GLM
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>


void Camera::init()
{
	m_fovDegree = 45.0f;
	m_position = glm::vec3(0.f, 40.f, 0.f);
	m_eulerAngle = glm::vec3(0.f, 0.f, 0.f);
	m_rotation = glm::quat{};
	m_showImguiDemo = false;

	//m_dist = 0.f; //Failed camera third
	m_pitch_speed = 0.5f;
	m_yaw_speed = 0.5;
	m_speed = 5.f;

	//NEW
	m_transitionTimer = 0.0f;
	m_transitionDuration = 2.0f;
	transitioned = false;

}

void Camera::reset() {
	transitioned = true;
    m_startPosition = m_position;
    m_startRotation = glm::quat(m_eulerAngle);
    m_transitionTimer = 0.0f;
    m_inTransition = true;
	transitioned = true;
}


void Camera::setPosition(glm::vec3 position){
		m_position = position;
}

void Camera::setRotation(glm::quat rotation){
	m_rotation = rotation;
}



void Camera::updateInterface(float _deltaTime)
{
	// ImGUI window creation
	if (ImGui::Begin("Interface"))
	{
		ImGui::Separator();
		ImGui::Text("Welcome to this TP about Cameras! Press escape to close the exe");
		ImGui::Text("Long live to the cameras");
		ImGui::Separator();
		//ImGui::Checkbox("show Imgui Demo", &m_showImguiDemo);

		//Position


		if(ImGui::TreeNode("Basic Camera control")){
			//Position
			ImGui::Text("Position");

			//Same size slider for all coords
			ImGui::SliderFloat3("position", &m_position.x, -50.f, 50.f);

			//Different size slider for each coord
			// ImGui::SliderFloat("x position" , &m_position.x, -50.f, 50.f);
			// ImGui::SliderFloat("y position" , &m_position.y, 30.f, 60.f);
			// ImGui::SliderFloat("z position" , &m_position.z, -80.f, 50.f);

			ImGui::Text("Euler angles");

			//Euler angles pitch slider
			ImGui::SliderFloat("euler pitch", &m_eulerAngle.x , -M_PI/(float)2, M_PI/(float)2);

			//YAWd 
			ImGui::SliderFloat("euler yaw", &m_eulerAngle.y, -M_PI, M_PI);

			//fov
			ImGui::Text("Field of view");
			ImGui::SliderFloat("fov", &m_fovDegree, 10.f, 120.f);

			//speed
			ImGui::Text("Speed");
			ImGui::SliderFloat("pitch rotation speed", &m_pitch_speed, 0.01f, 5.f);
			ImGui::SliderFloat("yaw rotation speed", &m_yaw_speed, 0.005f, 5.f);
			ImGui::SliderFloat("translation speed", &m_speed, 0.1f, 50.f);

			ImGui::TreePop();
		}

		//toggle input
		ImGui::Text("Target options");
		ImGui::Checkbox("Attach to target" , &attachToTarget);
		//Failed camera third
		//ImGui::SliderFloat("Distance" , &m_dist , -6.f , 6.f );

		if (ImGui::Button("Toggle input"))
		{
			m_inputType = (m_inputType == InputType::mode1) ? InputType::mode2 : InputType::mode1;
		}
		ImGui::SameLine();
		ImGui::Text("Input type : %s", (m_inputType == InputType::mode1) ? "mode1" : "mode2");



		//reset
		if (ImGui::Button("Reset"))
		{
			reset();
		}
		//old button
		// if (ImGui::Button("Reset"))
		// {
		// 	init();
		// }

	}
	ImGui::End();

	// if (m_showImguiDemo)
	// {
	// 	ImGui::ShowDemoWindow();
	// }

}

double lastX = 0.0;
double lastY = 0.0;

void Camera::updateFreeInput(float _deltaTime, GLFWwindow* _window)
{


	if (glfwGetKey(_window, GLFW_KEY_Z) == GLFW_PRESS && !keyPressed)
	{
		m_inputType = (m_inputType == InputType::mode1) ? InputType::mode2 : InputType::mode1;
		keyPressed = true;
	}
	else if (glfwGetKey(_window, GLFW_KEY_Z) == GLFW_RELEASE)
	{
		keyPressed = false;
	}

	//mode1
	if (m_inputType == InputType::mode1 && !attachToTarget)
    {
		//Look around with mouse
    	double mouseX, mouseY;
    	glfwGetCursorPos(_window, &mouseX, &mouseY);

    	double deltaX = mouseX - lastX;
    	double deltaY = mouseY - lastY;

		m_eulerAngle.y = Camera_Helper::clipAngle180(m_eulerAngle.y + (-1*(deltaX * _deltaTime * m_yaw_speed)));
		m_eulerAngle.x += deltaY * _deltaTime * m_pitch_speed * 10;

		m_eulerAngle.x = glm::clamp(m_eulerAngle.x , -M_PI/(float)2 , M_PI/(float)2);


    	lastX = mouseX;
    	lastY = mouseY;

		//Movement
	
		glm::vec3 cFront = m_rotation * VEC_FRONT;
		glm::vec3 cRight = glm::normalize(glm::cross(VEC_UP, cFront));
		glm::vec3 cUp = glm::normalize(glm::cross(cRight,cFront));
		cRight = glm::normalize(glm::cross(cFront , cUp));

		//forward with z (w)
		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_position += m_speed * cFront * _deltaTime; 
		}
		//backward with s
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_position += m_speed * -cFront * _deltaTime; 
		}
		//left with q (s)
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_position += m_speed * cRight * _deltaTime; 
		}
		//right with d
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_position += m_speed * -cRight * _deltaTime; 
		}

    }
	if (m_inputType == InputType::mode2 && !attachToTarget){
		//arrow keys allow you to rotate the camera
		if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			m_eulerAngle.x = glm::clamp((m_eulerAngle.x - (m_pitch_speed * _deltaTime)),-M_PI/(float)2 , M_PI/(float)2);
		}
		if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			m_eulerAngle.x = glm::clamp((m_eulerAngle.x + (m_pitch_speed * _deltaTime)),-M_PI/(float)2 , M_PI/(float)2);
		}
		if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			m_eulerAngle.y = Camera_Helper::clipAngle180(m_eulerAngle.y + (m_yaw_speed * _deltaTime));
		}
		if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			m_eulerAngle.y = Camera_Helper::clipAngle180(m_eulerAngle.y - (m_yaw_speed * _deltaTime));
		}
		
		glm::vec3 cFront = glm::quat(m_eulerAngle) * VEC_FRONT;
		glm::vec3 cFrontH = glm::normalize(glm::cross(VEC_UP, glm::cross(cFront, VEC_UP)));
		glm::vec3 cRight = glm::normalize(glm::cross(VEC_UP, cFront));
		glm::vec3 cUp = glm::normalize(glm::cross(cRight,cFront));
		cRight = glm::normalize(glm::cross(cFront , cUp));

		//forward with z (w)
		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_position += m_speed * cFrontH * _deltaTime; 
		}
		//backward with s
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_position += m_speed * -cFrontH * _deltaTime; 
		}
		//left with q (s)
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_position += m_speed * cRight * _deltaTime; 
		}
		//right with d
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_position += m_speed * -cRight * _deltaTime; 
		}

		//height with a (q) and e
		if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			m_position += m_speed * VEC_UP; 
		}
		if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
		{
			m_position += m_speed * -VEC_UP; 
		}

	}

}

void Camera::updateTransition(float _deltaTime) {
    if (!m_inTransition) return;

	//manag time
    m_transitionTimer += _deltaTime;
    float ratio = glm::clamp(m_transitionTimer / m_transitionDuration, 0.0f, 1.0f);

    float smoothRatio = Camera_Helper::interpolationRatio(ratio, InterpolationType::cos);

    m_position = glm::mix(m_startPosition, glm::vec3(0.f, 40.f, 0.f), smoothRatio);

    glm::quat targetRotation = glm::quat(glm::vec3(0.f, 0.f, 0.f));
    m_rotation = glm::slerp(m_startRotation, targetRotation, smoothRatio);

    if (ratio >= 1.0f) {
        m_inTransition = false;
        init();  
	}
}


void Camera::update(float _deltaTime, GLFWwindow* _window)
{
	updateInterface(_deltaTime);
    if (!m_inTransition) {
        updateFreeInput(_deltaTime, _window);
    } else {
        updateTransition(_deltaTime);
    }
	//Quaternions
	//Camera_Helper::computeFinalView(m_projectionMatrix, m_viewMatrix, m_position, m_rotation, m_fovDegree);
	
	//Euler
	if(!attachToTarget && !transitioned) m_rotation = glm::quat(m_eulerAngle);
	Camera_Helper::computeFinalView(m_projectionMatrix, m_viewMatrix, m_position, m_rotation, m_fovDegree);
}