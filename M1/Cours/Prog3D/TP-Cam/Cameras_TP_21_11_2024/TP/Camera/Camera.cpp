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

	m_pitch_speed = 0.5f;
	m_yaw_speed = 0.05;
	m_speed = 5.f;
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
			ImGui::SliderFloat("euler pitch", &m_eulerAngle.x , -5.f, 5.f);

			//YAWd 
			ImGui::SliderFloat("euler yaw", &m_eulerAngle.y, -5.f, 5.f);

			//fov
			ImGui::Text("Field of view");
			ImGui::SliderFloat("fov", &m_fovDegree, 10.f, 120.f);



			//speed
			ImGui::Text("Speed");
			ImGui::SliderFloat("pitch rotation speed", &m_pitch_speed, 0.01f, 1.f);
			ImGui::SliderFloat("yaw rotation speed", &m_yaw_speed, 0.005f, 1.f);
			ImGui::SliderFloat("translation speed", &m_speed, 0.1f, 50.f);

			ImGui::TreePop();

		}

		//toggle input
		//TODO make this work for more than 2 in the enum
		if (ImGui::Button("Toggle input"))
		{
			m_inputType = (m_inputType == InputType::mode1) ? InputType::mode2 : InputType::mode1;
		}
		ImGui::SameLine();
		ImGui::Text("Input type : %s", (m_inputType == InputType::mode1) ? "mode1" : "mode2");



		//reset
		if (ImGui::Button("Reset"))
		{
			init();
		}
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
	if (m_inputType == InputType::mode1)
    {
		//Look around with mouse
    	double mouseX, mouseY;
    	glfwGetCursorPos(_window, &mouseX, &mouseY);

    	double deltaX = mouseX - lastX;
    	double deltaY = mouseY - lastY;

    	m_eulerAngle.y += -1*(deltaX * _deltaTime * m_pitch_speed);
		m_eulerAngle.x += deltaY * _deltaTime * m_yaw_speed * 10;

		m_eulerAngle.x = glm::clamp(m_eulerAngle.x , -2.f , 2.f);


    	lastX = mouseX;
    	lastY = mouseY;

		//Movement

		glm::vec3 cFront = glm::quat(m_eulerAngle) * VEC_FRONT;
		glm::vec3 cRight = glm::normalize(glm::cross(VEC_UP, cFront));
		glm::vec3 cUp = glm::normalize(glm::cross(cRight,cFront));
		cRight = glm::normalize(glm::cross(cFront , cUp));

		//forward with z (w)
		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_position += m_speed * cFront; 
		}
		//backward with s
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_position += m_speed * -cFront; 
		}
		//left with q (s)
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_position += m_speed * cRight; 
		}
		//right with d
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_position += m_speed * -cRight; 
		}

    }
	if(m_inputType == InputType::mode2){
		//arrow keys allow you to rotate the camera
		if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			m_eulerAngle.x -= m_pitch_speed * _deltaTime;
		}
		if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			m_eulerAngle.x += m_pitch_speed * _deltaTime;
		}
		if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			m_eulerAngle.y += m_yaw_speed * _deltaTime;
		}
		if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			m_eulerAngle.y -= m_yaw_speed * _deltaTime;
		}
		
		//e déplacement avant/ arrière se fait dans le front horizontal de la caméra (SANS changement de hauteur).
		glm::vec3 cFront = glm::quat(m_eulerAngle) * VEC_FRONT;
		glm::vec3 cFrontH = glm::normalize(glm::cross(VEC_UP, glm::cross(cFront, VEC_UP)));
		glm::vec3 cRight = glm::normalize(glm::cross(VEC_UP, cFront));
		glm::vec3 cUp = glm::normalize(glm::cross(cRight,cFront));
		cRight = glm::normalize(glm::cross(cFront , cUp));

		//forward with z (w)
		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_position += m_speed * cFrontH; // Move forward
		}
		//backward with s
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_position += m_speed * -cFrontH; // Move forward
		}
		//left with q (s)
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_position += m_speed * cRight; 
		}
		//right with d
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_position += m_speed * -cRight; 
		}

		//height with a (q) and e
		if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			m_position += m_speed * VEC_UP; // Move forward
		}
		if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
		{
			m_position += m_speed * -VEC_UP; // Move forward
		}

	}


}


void Camera::update(float _deltaTime, GLFWwindow* _window)
{
	updateInterface(_deltaTime);
	updateFreeInput(_deltaTime, _window);

	//Quaternions
	//Camera_Helper::computeFinalView(m_projectionMatrix, m_viewMatrix, m_position, m_rotation, m_fovDegree);
	
	//Euler
	glm::quat rotation = glm::quat(m_eulerAngle);
	Camera_Helper::computeFinalView(m_projectionMatrix, m_viewMatrix, m_position, rotation, m_fovDegree);
}