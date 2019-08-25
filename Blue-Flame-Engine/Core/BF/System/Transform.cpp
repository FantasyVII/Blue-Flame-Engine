#include "Transform.h"
#include "BF/ECS/GameObject.h"
#include "BF/System/Debug.h"

namespace BF
{
	namespace System
	{
		using namespace BF::Math;

		Transform::Transform() :
			transformation(Matrix4::Identity()), worldTransformation(Matrix4::Identity()), position(0), rotation(0), scale(1), angle(0), updatePosition(false)
		{
		}

		Transform::~Transform()
		{
		}

		void Transform::SetPosition(const Vector3f& position)
		{
			updatePosition	= true;
			prevPos			= this->position;
			this->position	= position;
		}

		void Transform::SetRotation(float angle, const Vector3f& rotation)
		{
			this->angle = angle;
			this->rotation = rotation;
			transformation = Matrix4::Translate(position) * Matrix4::Rotate(angle, rotation) * Matrix4::Scale(scale);

			UpdateTransform();
		}

		void Transform::SetScale(const Vector3f& scale)
		{
			this->scale = scale;
			transformation = Matrix4::Translate(position) * Matrix4::Rotate(angle, rotation) * Matrix4::Scale(scale);
			this->scale = transformation.GetScaleVector();

			UpdateTransform();
		}

		void Transform::UpdateTransform()
		{
			/*if (this->gameObject->parent == nullptr)
			{
				worldTransformation = transformation;
			}
			else
			{
				worldTransformation = this->gameObject->parent->GetTransform()->worldTransformation * transformation;
			}*/

			/*for (size_t i = 0; i < this->gameObject->gameObjects.size(); i++)
			{
				this->gameObject->gameObjects[i]->GetTransform()->worldTransformation = worldTransformation * this->gameObject->gameObjects[i]->GetTransform()->transformation;
			}*/
		}
	}
}