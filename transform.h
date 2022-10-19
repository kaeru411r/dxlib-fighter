#pragma once
#include "tree.h"
#include "../dxlib_ext/dxlib_ext.h"

//�I�C���[�p����̃r���h�X�C�b�`
#define EULER false

namespace ike {

	/// <summary>
	/// ���W�A�p���A�T�C�Y���Ǘ�����N���X
	/// </summary>
	class Transform{

	public:
		Transform();
		~Transform();

		//-------------Position--------------------------------------------------

		/// <summary>
		/// ���݂̃��[���h���W�n�ł�Position��Ԃ�
		/// </summary>
		/// <returns>���W</returns>
		tnl::Vector3 getPosition() const;
		/// <summary>
		/// ���[���h���W�n�ł�Position��position�ɕύX����
		/// </summary>
		/// <param name="position"></param>
		void setPosition(const tnl::Vector3 position);
		/// <summary>
		/// ���݂̃��[�J�����W�n�ł�Position��Ԃ�
		/// </summary>
		/// <returns>���W</returns>
		tnl::Vector3 getLocalPosition() const;
		/// <summary>
		/// ���[�J�����W�n�ł�Position��position�ɕύX����
		/// </summary>
		/// <param name="position"></param>
		void setLocalPosition(const tnl::Vector3 position);


		//--------------Rotation---------------------------------------------------

		/// <summary>
		/// ���݂̃��[���h���W�n�ł�Rotation��Ԃ�
		/// </summary>
		/// <returns>�p��</returns>
		tnl::Quaternion getRotation() const;
		/// <summary>
		/// ���[���h���W�n�ł�Rotation��rotation�ɕύX����
		/// </summary>
		/// <param name="rotation"></param>
		void setRotation(const tnl::Quaternion rotation);
		/// <summary>
		/// ���݂̃��[�J�����W�n�ł�Rotation��Ԃ�
		/// </summary>
		/// <returns>�p��</returns>
		tnl::Quaternion getLocalRotation() const;
		/// <summary>
		/// ���[�J�����W�n�ł�Rotation��rotation�ɕύX����
		/// </summary>
		/// <param name="rotation"></param>
		void setLocalRotation(const tnl::Quaternion rotation);

		//--------------EulerAngle-------------------------------------------------
#if EULER
		/// <summary>
		/// ���݂̃��[���h���W�n�ł�EulerAngle��Ԃ�
		/// </summary>
		/// <returns>�p�x</returns>
		tnl::Vector3 getEulerAngle() const;
		/// <summary>
		/// ���[���h���W�n�ł�EulerAngle��angle�ɕύX����
		/// </summary>
		/// <param name="angle"></param>
		tnl::Vector3 getLocalEulerAngle() const;
		/// <summary>
		/// ���݂̃��[�J�����W�n�ł�EulerAngle��Ԃ�
		/// </summary>
		/// <returns>�p�x</returns>
		void setEulerAngle(const tnl::Vector3 angle);
		/// <summary>
		/// ���[�J�����W�n�ł�EulerAngle��angle�ɕύX����
		/// </summary>
		/// <param name="angle"></param>
		void setLocalEulerAngle(const tnl::Vector3 angle);

#endif
		//------------------Scale---------------------------------------------------

		/// <summary>
		/// ���݂̃��[���h���W�n�ł�Scale��Ԃ�
		/// </summary>
		/// <returns>�p�x</returns>
		tnl::Vector3 getScale() const;
		/// <summary>
		/// ���[���h���W�n�ł�Scale��scale�ɕύX����
		/// </summary>
		/// <param name="scale"></param>
		void setScale(const tnl::Vector3 scale);
		/// <summary>
		/// ���݂̃��[�J�����W�n�ł�Scale��Ԃ�
		/// </summary>
		/// <returns>�p�x</returns>
		tnl::Vector3 getLocalScale() const;
		/// <summary>
		/// ���[�J�����W�n�ł�Scale��scale�ɕύX����
		/// </summary>
		/// <param name="scale"></param>
		void setLocalScale(const tnl::Vector3 scale);


		//-----------------tree-------------------------------------------------------

		/// <summary>
		/// <para>�e�I�u�W�F�N�g��parent�ɐݒ肷��</para>
		/// <para>nullptr��n���ƃ��[���h���W�n�����ɂȂ�</para>
		/// </summary>
		/// <param name="parent"></param>
		/// <returns>����������</returns>
		bool setParent(Transform* parent);

		/// <summary>
		/// ���݂̐e�I�u�W�F�N�g���擾����
		/// </summary>
		/// <returns>�e�I�u�W�F�N�g</returns>
		Transform* getParent() const;
		/// <summary>
		/// ���݂̒����̎q�I�u�W�F�N�g���擾����
		/// </summary>
		/// <returns>�q�I�u�W�F�N�g�̃��X�g</returns>
		std::list<Transform*> getChildren() const;

		/// <summary>
		/// data�������̎q�I�u�W�F�N�g���ۂ�
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		bool childrenContains(const Transform* data);
		/// <summary>
		/// data�����̃I�u�W�F�N�g���ɑ��݂��邩�ۂ�
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		bool allChildrenContains(const Transform* data);


		//--------------���̑�--------------------------

		/// <summary>
		/// ���̃I�u�W�F�N�g�̏�����x�N�g��
		/// </summary>
		tnl::Vector3 up() const;
		/// <summary>
		/// ���̃I�u�W�F�N�g�̉E�����x�N�g��
		/// </summary>
		tnl::Vector3 right() const;
		/// <summary>
		/// ���̃I�u�W�F�N�g�̑O�����x�N�g��
		/// </summary>
		tnl::Vector3 front() const;

#if EULER
		/// <summary>
		/// ���݂̎p����莩�g�̍��W�n��value�x�p����ύX����(��)
		/// </summary>
		/// <param name="value"></param>
		void ownEulerRotate(const tnl::Vector3 value);
#endif
		/// <summary>
		/// ���݂̍��W��莩�g�̍��W�n��value���W��ύX����(��)
		/// </summary>
		/// <param name="value"></param>
		void ownMove(const tnl::Vector3 value);

		//virtual void localEulerRotate(const tnl::Vector3 value);
		//virtual void localMove(const tnl::Vector3 value);

#if EULER
		/// <summary>
		/// ���݂̎p����胏�[���h���W�n��value�x�p����ύX����(��)
		/// </summary>
		/// <param name="value"></param>
		void eulerRotate(const tnl::Vector3 value);
#endif
		/// <summary>
		/// ���݂̍��W��胏�[���h���W�n��value���W��ύX����(��)
		/// </summary>
		/// <param name="value"></param>
		void move(const tnl::Vector3 value);



		void removeAllChildren();
	protected:


		bool setParent(Transform* data);

		//Transform* getParent2() const;
		//std::list<Transform*> getChildren2() const;

		bool childrenContains(const Transform* data);
		bool allChildrenContains(const Transform* data);


	private:
#if EULER
		tnl::Quaternion eulerToQuaternion(tnl::Vector3 euler);
#endif

		tnl::Quaternion localRotation_;
		tnl::Vector3 localPosition_;
		tnl::Vector3 localScale_;


		Transform* parent_ = nullptr;
		std::list<Transform*> children_;

		void addChild(Transform* data);
		void removeChild(Transform* data);
	};
}