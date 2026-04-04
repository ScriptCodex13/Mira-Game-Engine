#pragma once 
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Zap.h>
#include <Graphics.h>
#include <vector>

#include "../Window/WindowSettings.h"

namespace mira
{
	struct Transform
	{
		Transform();
		~Transform();

		void UpdateMatrix();

		void Move(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		void SetRotaton(float x, float y, float z);
		void Rotate(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void Scale(float x, float y, float z);

		glm::mat4 transform = glm::mat4(1.0f);

		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	};

	// Texture settings

	struct TextureSettings
	{
		zap::TextureFilter filter = zap::TextureFilter::LINEAR;
		zap::MipmapSetting mipmap = zap::MipmapSetting::LINEAR_MIPMAP_LINEAR;
		zap::TextureWrapping wrapping = zap::TextureWrapping::CLAMP_TO_BORDER;
	};

	//

	struct Texture : public zap::Texture
	{
		Texture(int hash, std::string path);
		Texture(int hash, std::string path, TextureSettings settings);
		~Texture();

		TextureSettings m_settings;
	};

	class Camera3D : public zap::SceneCamera
	{
	public:
		Camera3D(float x, float y, float z);
		~Camera3D();

		void Update();

	public:
		glm::mat4 m_projection = glm::mat4(1.0f);
		glm::mat4 m_view = glm::mat4(1.0f);
	};

	class Mesh3D : public zap::Mesh
	{
	public:
		Mesh3D(std::vector<float> vertices, std::vector<unsigned int> indices);
		~Mesh3D();

		void SetShader(std::string vertex_shader, std::string fragment_shader); // Should be removed
		void SetTexture(Texture& texture, std::string texture_uniform_name);
		void SetTransform(glm::mat4 model);
		void SetCamera(glm::mat4 view, glm::mat4 projection);
		void Update();
		void Enable(bool state);
		void ModelMatrixLocation(std::string model_matrix_name);
		void ViewMatrixLocation(std::string view_matrix_name);
		void ProjectionMatrixLocation(std::string projection_matrix_name);

	private:
		glm::mat4 model_matrix = glm::mat4(1.0f);
		glm::mat4 view_matrix = glm::mat4(1.0f);
		glm::mat4 projection_matrix = glm::mat4(1.0f);

		bool is_finished = false;
		bool use_model_matrix = true;

		unsigned int model_matrix_location;
		unsigned int view_matrix_location;
		unsigned int projection_matrix_location;
	};

	class Camera2D : public zap::SceneCamera
	{
	public:
		Camera2D(float x, float y, float zoom = 1.0f);
		~Camera2D();

		void SetZoom(float zoom);
		void Update();

	public:
		float m_zoom = 1.0f;

		glm::mat4 m_projection = glm::mat4(1.0f);
		glm::mat4 m_view = glm::mat4(1.0f);

	private:
		int window_width = window_settings::width;
		int window_height = window_settings::height;
	};

	class Sprite2D : private zap::Mesh
	{
	public:
		Sprite2D(std::array<float, 2> top_left_texture, std::array<float, 2> down_right_texture);
		~Sprite2D();

		void SetTexture(Texture& texture);
		void SetTransform(glm::mat4 transform);
		void SetCamera(glm::mat4 view, glm::mat4 projection);
		void Update(Texture& texture);

	private:
		std::array<float, 2> m_top_left;
		std::array<float, 2> m_down_right;

		bool camera_set = false;
		unsigned int model_matrix_location;
		unsigned int camera_present_location;
		unsigned int view_matrix_location;
		unsigned int projection_matrix_location;

		glm::mat4 model_matrix = glm::mat4(1.0);
		glm::mat4 view_matrix = glm::mat4(1.0);
		glm::mat4 projection_matrix = glm::mat4(1.0);

	private:
		const char* vertex_shader_source = 
			R"glsl(
				#version 330 core

				layout(location = 0) in vec3 aPos;
				layout(location = 1) in vec2 aTexCoord;

				out vec2 TexCoord;

				uniform int camera_present;

				uniform mat4 model;  
				uniform mat4 view; 
				uniform mat4 projection;

				void main()
				{
					TexCoord = aTexCoord;

					if(camera_present == 1)
					{
						gl_Position = projection * view * model * vec4(aPos, 1.0);
					}
					else if(camera_present == 0)
					{
						gl_Position = model * vec4(aPos, 1.0);
					}		
				}
			)glsl";

		const char* fragment_shader_source = 
			R"glsl(
					#version 330 core

					in vec2 TexCoord;

					out vec4 FragColor;

					uniform sampler2D texture1;

					void main()
					{
						FragColor = texture(texture1, TexCoord);
					}
					
			)glsl";



		std::vector<float> vertices =
		{
			// positions            // texture coords
			 0.5f,  0.5f, 0.0f,     1.0f, 1.0f,   // top right 
			 0.5f, -0.5f, 0.0f,     1.0f, 0.0f,   // bottom right  
			-0.5f, -0.5f, 0.0f,     0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,     0.0f, 1.0f    // top left

		};

		std::vector<unsigned int> indices =
		{
			0, 1, 3,
			1, 2, 3
		};
	};
}

#endif