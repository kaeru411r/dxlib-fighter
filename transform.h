#pragma once
#include "tree.h"
#include "../dxlib_ext/dxlib_ext.h"

#define EULER false
#define ROTATE true
#define CONVERT true

namespace ike {

	/// <summary>
	/// ���W�A�p���A�T�C�Y���Ǘ�����N���X
	/// </summary>
	class Transform{

	public:
		Transform();
		virtual ~Transform();

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


		//--------------���W�n�ϊ�----------------------
		
#if CONVERT

		//�e�̂��̊֐��ɒl��n���Ă�邱�ƂŁA���[���h����q�A�q���烏�[���h�ɕϊ��ł���
		
		/// <summary>
		/// ����Transform�̍��W�n�̈ʒu�����[���h���W�n�ł̈ʒu�ɕϊ�����
		/// </summary>
		/// <param name="position">���[�J�����W�n�ł̈ʒu</param>
		/// <returns>���[���h���W�n�ł̈ʒu</returns>
		tnl::Vector3 toWarldPosition(const tnl::Vector3& position) const;
		/// <summary>
		/// ����Transform�̍��W�n�̈ʒu�����[�J�����W�n�ł̈ʒu�ɕϊ�����
		/// </summary>
		/// <param name="position">���[���h���W�n�ł̈ʒu</param>
		/// <returns>���[�J�����W�n�ł̈ʒu</returns>
		tnl::Vector3 toLocalPosition(const tnl::Vector3& position) const;
		/// <summary>
		/// ����Transform�̍��W�n�̑傫�������[���h���W�n�ł̑傫���ɕϊ�����
		/// </summary>
		/// <param name="scale">���[�J�����W�n�ł̑傫��</param>
		/// <returns>���[���h���W�n�ł̑傫��</returns>
		tnl::Vector3 toWarldScale(const tnl::Vector3& scale) const;
		/// <summary>
		/// ����Transform�̍��W�n�̑傫�������[�J�����W�n�ł̑傫���ɕϊ�����
		/// </summary>
		/// <param name="scale">���[���h���W�n�ł̑傫��</param>
		/// <returns>���[�J�����W�n�ł̑傫��</returns>
		tnl::Vector3 toLocalScale(const tnl::Vector3& scale) const;
		/// <summary>
		/// ����Transform�̍��W�n�̉�]�����[���h���W�n�ł̉�]�ɕϊ�����
		/// </summary>
		/// <param name="rotation">���[�J�����W�n�ł̉�]</param>
		/// <returns>���[���h���W�n�ł̉�]</returns>
		tnl::Quaternion toWorldRotation(const tnl::Quaternion& rotation) const noexcept;
		/// <summary>
		/// ����Transform�̍��W�n�̉�]�����[�J�����W�n�ł̉�]�ɕϊ�����
		/// </summary>
		/// <param name="rotation">���[���h���W�n�ł̉�]</param>
		/// <returns>���[�J�����W�n�ł̉�]</returns>
		tnl::Quaternion toLocalRotation(const tnl::Quaternion& rotation) const noexcept;

#endif

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

#if ROTATE
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

#if ROTATE
		/// <summary>
		/// 
		/// </summary>
		/// <param name="value"></param>
		void eulerRotate(const tnl::Vector3 value);
#endif
		/// <summary>
		/// ���݂̍��W��胏�[���h���W�n��value���W��ύX����(��)
		/// </summary>
		/// <param name="value"></param>
		void move(const tnl::Vector3 value);



	protected:



	private:
#if EULER
		tnl::Quaternion eulerToQuaternion(tnl::Vector3 euler);
#endif

		ike::Tree<Transform>* tree_;

		tnl::Quaternion localRotation_;
		tnl::Vector3 localPosition_;
		tnl::Vector3 localScale_;


	};
}