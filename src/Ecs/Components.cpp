#include "Components.h"

namespace mira
{
	Mesh3D::Mesh3D(std::vector<float> vertices, std::vector<unsigned int> indices) : zap::Mesh(vertices, indices)
	{

	}

	Mesh3D::~Mesh3D()
	{

	}

	void Mesh3D::SetShader(std::string vertex_shader, std::string fragment_shader)
	{
		SetVertexShaderSource(vertex_shader);
		SetFragmentShaderSource(fragment_shader);
	}

	void Mesh3D::SetTexture(Texture& texture, std::string texture_uniform_name)
	{
		Mesh::UseProgram();

		texture.Bind();
		glUniform1i(glGetUniformLocation(Mesh::GetProgram(), texture_uniform_name.c_str()), texture.getHash());
	}

	void Mesh3D::SetTransform(glm::mat4 model)
	{
		model_matrix = model;
	}

	void Mesh3D::SetCamera(glm::mat4 view, glm::mat4 projection)
	{
		view_matrix = view;
		projection_matrix = projection;
	}

	void Mesh3D::Update()
	{
		if (!is_finished) return;

		UseProgram();

		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(projection_matrix));
		
		Bind();
		Draw();
	}

	void Mesh3D::Enable(bool state)
	{
		is_finished = state;

		if (state) 
		{ 
			Mesh::Finish(); 
			Mesh::UseProgram();
		}
	}

	void Mesh3D::ModelMatrixLocation(std::string model_matrix_name)
	{
		model_matrix_location = glGetUniformLocation(Mesh::GetProgram(), model_matrix_name.c_str());
	}

	void Mesh3D::ViewMatrixLocation(std::string view_matrix_name)
	{
		view_matrix_location = glGetUniformLocation(Mesh::GetProgram(), "view");
	}

	void Mesh3D::ProjectionMatrixLocation(std::string projection_matrix_name)
	{
		projection_matrix_location = glGetUniformLocation(Mesh::GetProgram(), "projection");
	}

	/*******************************************************************************************************/

	Camera3D::Camera3D(float x, float y, float z) : 
		SceneCamera
		(
			(int&)window_settings::width,
			(int&)window_settings::height,
			zap::CameraTypes::PERSPECTIVE,
			zap::OrthographicalDimensions(-2.0f, 2.0f, -1.5f, 1.5f),
			{x, y, z}
		)
	{
		
	}

	Camera3D::~Camera3D()
	{

	}

	void Camera3D::Update()
	{
		SceneCamera::UpdateRotation();

		m_projection = SceneCamera::GetProjection();
		m_view = SceneCamera::GetView();
	}

	/*******************************************************************************************************/

	zap::OrthographicalDimensions CalculateDimensions(float width, float height, float zoom)
	{
		// Zoom wirkt wie ein "Vergrößerungsfaktor"
		float half_width = width / zoom;
		float half_height = height / zoom;

		std::array<float, 2> dimensions = zap::util::pixel_to_gl_coords({ (int)width, (int)height }, half_width, half_height );

		half_width = dimensions[0];
		half_height = -dimensions[1];

		return zap::OrthographicalDimensions
		(
			-half_width,   // left
			half_width,   // right
			-half_height,  // bottom
			half_height   // top
		);
	}


	Camera2D::Camera2D(float x, float y, float zoom) :
		m_zoom(zoom),
		zap::SceneCamera
		(
			(int&)window_settings::width,
			(int&)window_settings::height,
			zap::CameraTypes::ORTHOGRAPHIC,
			CalculateDimensions(window_settings::width, window_settings::height, 1.0f)
			//{ x, y, 3.0f },
			//-1.0f,
			//1.0f
		)
	{

	}

	Camera2D::~Camera2D()
	{

	}

	void Camera2D::SetZoom(float zoom)
	{
		m_zoom = zoom;
	}

	void Camera2D::Update()
	{
		SceneCamera::UpdateRotation();

		m_projection = SceneCamera::GetProjection();
		m_view = SceneCamera::GetView();

		SceneCamera::SetOrthographicalDimensions(CalculateDimensions(window_settings::width, window_settings::height, m_zoom));
	}

	/*******************************************************************************************************/

	std::vector<float> CalculateVertices(std::array<float, 2> top_left, std::array<float, 2> down_right)
	{
		auto m_top_left = zap::util::pixel_to_gl_coords({ (int)window_settings::width, (int)window_settings::height }, top_left);
		auto m_down_right = zap::util::pixel_to_gl_coords({ (int)window_settings::width, (int)window_settings::height }, down_right);

		float cx = (m_top_left[0] + m_down_right[0]) * 0.5f;
		float cy = (m_top_left[1] + m_down_right[1]) * 0.5f;

		float left = m_top_left[0] - cx;
		float right = m_down_right[0] - cx;
		float top = m_top_left[1] - cy;
		float bottom = m_down_right[1] - cy;

		return
		{
			right,  top,    0.0f, 1.0f, 1.0f,
			right,  bottom, 0.0f, 1.0f, 0.0f,
			left,   bottom, 0.0f, 0.0f, 0.0f,
			left,   top,    0.0f, 0.0f, 1.0f
		};
	}

	Sprite2D::Sprite2D(std::array<float, 2> top_left, std::array<float, 2> down_right) :
		Mesh(CalculateVertices(top_left, down_right), {0, 1, 3, 1, 2, 3})
	{
		Mesh::SetAttribPointer(0, 3, 5, 0);
		Mesh::SetAttribPointer(1, 2, 5, 3);

		Mesh::SetVertexShaderSource(vertex_shader_source);
		Mesh::SetFragmentShaderSource(fragment_shader_source);

		Mesh::Finish();

		model_matrix_location = glGetUniformLocation(Mesh::GetProgram(), "model");
		camera_present_location = glGetUniformLocation(Mesh::GetProgram(), "camera_present");
		view_matrix_location = glGetUniformLocation(Mesh::GetProgram(), "view");
		projection_matrix_location = glGetUniformLocation(Mesh::GetProgram(), "projection");
	}

	Sprite2D::~Sprite2D()
	{

	}

	void Sprite2D::SetTexture(Texture& texture)
	{
		Mesh::UseProgram();

		texture.Bind();
		glUniform1i(glGetUniformLocation(Mesh::GetProgram(), "texture1"), texture.getHash());
	}

	void Sprite2D::SetTransform(glm::mat4 transform)
	{
		model_matrix = transform;
	}

	void Sprite2D::SetCamera(glm::mat4 view, glm::mat4 projection)
	{
		view_matrix = view;
		projection_matrix = projection;

		camera_set = true;
	}

	void Sprite2D::Update(Texture& texture)
	{
		Mesh::UseProgram();
		
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(projection_matrix));
		glUniform1i(camera_present_location, (int)camera_set);

		texture.Bind();

		Mesh::Bind();
		Mesh::Draw();

		camera_set = false;
	}

	/*******************************************************************************************************/

	Transform::Transform()
	{
		
	}

	Transform::~Transform()
	{

	}

	void Transform::UpdateMatrix()
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, position);

		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

		model = glm::scale(model, scale);

		transform = model;
	}

	void Transform::Move(float x, float y, float z)
	{
		position += glm::vec3(x, y, z);

		UpdateMatrix();
	}

	void Transform::SetPosition(float x, float y, float z)
	{	
		position = glm::vec3(x, y, z);

		UpdateMatrix();
	}

	void Transform::SetRotaton(float x, float y, float z)
	{
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;

		UpdateMatrix();
	}

	void Transform::Rotate(float x, float y, float z)
	{
		rotation.x += x;
		rotation.y += y;
		rotation.z += z;

		glm::mat4 model = glm::mat4(1.0f);

		UpdateMatrix();
	}

	void Transform::SetScale(float x, float y, float z)
	{
		scale.x = x;
		scale.y = y;
		scale.z = z;

		UpdateMatrix();
	}

	void Transform::Scale(float x, float y, float z)
	{
		scale.x *= x;
		scale.y *= y;
		scale.z *= z;

		UpdateMatrix();
	}

	/*******************************************************************************************************/

	Texture::Texture(int hash, std::string path) : zap::Texture(hash, path, m_settings.filter, m_settings.mipmap, m_settings.wrapping)
	{
		messages::PrintMessage("Loading texture from " + std::string(path), "", MessageTypes::api_core_info, false);
	}

	Texture::Texture(int hash, std::string path, TextureSettings settings) : m_settings(settings), zap::Texture(hash, path, settings.filter, settings.mipmap, settings.wrapping)
	{

	}

	Texture::~Texture()
	{

	}
}