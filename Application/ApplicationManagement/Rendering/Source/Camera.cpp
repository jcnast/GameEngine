#include "ApplicationManagement/Rendering/Headers/Camera.h"

#include "ApplicationManagement/Rendering/Headers/CameraUtils.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/MatrixFunctions.h"
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Application
{
	namespace Rendering
	{
		const Float3 Camera::DefaultDirection = Float3(0.0f, 0.0f, -1.0f);

		Camera::Camera(const float& aspectRatio, Transform& transform, const Float3& direction)
			: CameraTransform(transform)
		{
			LookAt(CameraTransform.GetPosition() + direction);

			SetProjectionVariables(FOVY, aspectRatio, NearPlane, FarPlane);
		}

		Transform& Camera::GetCameraTransform()
		{
			return CameraTransform;
		}
		
		void Camera::SetCameraTransform(Transform& transform)
		{
			CameraTransform = transform;
		}

		Float4x4 Camera::GetTransformationMatrix() const
		{
			// Reference: http://www.ntu.edu.sg/home/ehchua/programming/opengl/cg_basicstheory.html
			Float4x4 transformationMatrix(II{});

			// rotation
			Float3x3 rotationMatrix = CameraTransform.GetRotationMatrix();
			std::cout << "Rotation: " + QuaternionString(CameraTransform.GetRotation()) << std::endl;
			std::cout << "Rotation Matrix: " + MatrixString(rotationMatrix) << std::endl;
			Float4x4 inverseRotationMatrix = Float4x4(Transpose(rotationMatrix), Float4(0.0f, 0.0f, 0.0f, 1.0f));
			transformationMatrix = inverseRotationMatrix * transformationMatrix; // can probably just set the transformation matrix to tbe the inverse rotation matrix, doing this for clarity

			// translation
			Float3 Position = CameraTransform.GetPosition();
			std::cout << "Position: " + VectorString(Position) << std::endl;
			//Float4 rotatedPosition = inverseRotationMatrix * Float4(-1.0f * Position, 1.0f);
			//transformationMatrix.E4 = rotatedPosition;
			transformationMatrix.E4 = Float4(-Dot(rotationMatrix.E1, Position), -Dot(rotationMatrix.E2, Position), -Dot(rotationMatrix.E3, Position), 1.0f);
			std::cout << "View Matrix: " + MatrixString(transformationMatrix) << std::endl;

			// projection
			transformationMatrix = ProjectionMatrix * transformationMatrix;

			return transformationMatrix;
		}

		void Camera::LookAt(Float3 position)
		{
			Direction = Normalize(position - CameraTransform.GetPosition());

			CameraTransform.SetRotation(RotationBetweenVectors(DefaultDirection, Direction));
		}

		void Camera::SetFOVY(Rad fovy)
		{
			FOVY = fovy;

			RecalculateProjectionMatrix();
		}

		void Camera::SetAspectRatio(float width, float height)
		{
			SetAspectRatio(Float2(width, height));
		}

		void Camera::SetAspectRatio(Float2 viewRect)
		{
			SetAspectRatio(viewRect.X / viewRect.Y);
		}

		void Camera::SetAspectRatio(float aspectRatio)
		{
			AspectRatio = aspectRatio;

			RecalculateProjectionMatrix();
		}

		void Camera::SetNearPlane(const float& nearPlane)
		{
			SetPlanes(nearPlane, FarPlane);
		}

		void Camera::SetFarPlane(const float& farPlane)
		{
			SetPlanes(NearPlane, farPlane);
		}

		void Camera::SetPlanes(const float& nearPlane, const float& farPlane)
		{
			SetPlanes(Float2(nearPlane, farPlane));
		}

		void Camera::SetPlanes(const Float2& planes)
		{
			NearPlane = planes.X;
			FarPlane = planes.Y;

			RecalculateProjectionMatrix();
		}

		void Camera::SetProjectionVariables(const Rad& fovy, const float& aspectRatio, const float& nearPlane, const float& farPlane)
		{
			FOVY = fovy;

			AspectRatio = aspectRatio;

			NearPlane = nearPlane;
			FarPlane = farPlane;

			RecalculateProjectionMatrix();
		}

		void Camera::RecalculateProjectionMatrix()
		{
			ProjectionMatrix = CalculatePerspectiveMatrix(FOVY, AspectRatio, NearPlane, FarPlane);
		}
	}
}