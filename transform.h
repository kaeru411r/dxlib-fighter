#pragma once
#include "tree.h"
#include "../dxlib_ext/dxlib_ext.h"

namespace ike {

	/// <summary>
	/// 座標、姿勢、サイズを管理するクラス
	/// </summary>
	class Transform : public ike::Tree {

	public:
		Transform();
		~Transform();

		//-------------Position--------------------------------------------------

		/// <summary>
		/// 現在のワールド座標系でのPositionを返す
		/// </summary>
		/// <returns>座標</returns>
		tnl::Vector3 getPosition() const;
		/// <summary>
		/// ワールド座標系でのPositionをpositionに変更する
		/// </summary>
		/// <param name="position"></param>
		void setPosition(const tnl::Vector3 position);
		/// <summary>
		/// 現在のローカル座標系でのPositionを返す
		/// </summary>
		/// <returns>座標</returns>
		tnl::Vector3 getLocalPosition() const;
		/// <summary>
		/// ローカル座標系でのPositionをpositionに変更する
		/// </summary>
		/// <param name="position"></param>
		void setLocalPosition(const tnl::Vector3 position);


		//--------------Rotation---------------------------------------------------

		/// <summary>
		/// 現在のワールド座標系でのRotationを返す
		/// </summary>
		/// <returns>姿勢</returns>
		tnl::Quaternion getRotation() const;
		/// <summary>
		/// ワールド座標系でのRotationをrotationに変更する
		/// </summary>
		/// <param name="rotation"></param>
		void setRotation(const tnl::Quaternion rotation);
		/// <summary>
		/// 現在のローカル座標系でのRotationを返す
		/// </summary>
		/// <returns>姿勢</returns>
		tnl::Quaternion getLocalRotation() const;
		/// <summary>
		/// ローカル座標系でのRotationをrotationに変更する
		/// </summary>
		/// <param name="rotation"></param>
		void setLocalRotation(const tnl::Quaternion rotation);

		//--------------EulerAngle-------------------------------------------------

		/// <summary>
		/// 現在のワールド座標系でのEulerAngleを返す
		/// </summary>
		/// <returns>角度</returns>
		tnl::Vector3 getEulerAngle() const;
		/// <summary>
		/// ワールド座標系でのEulerAngleをangleに変更する
		/// </summary>
		/// <param name="angle"></param>
		tnl::Vector3 getLocalEulerAngle() const;
		/// <summary>
		/// 現在のローカル座標系でのEulerAngleを返す
		/// </summary>
		/// <returns>角度</returns>
		void setEulerAngle(const tnl::Vector3 angle);
		/// <summary>
		/// ローカル座標系でのEulerAngleをangleに変更する
		/// </summary>
		/// <param name="angle"></param>
		void setLoaclEulerAngle(const tnl::Vector3 angle);


		//------------------Scale---------------------------------------------------

		/// <summary>
		/// 現在のワールド座標系でのScaleを返す
		/// </summary>
		/// <returns>角度</returns>
		tnl::Vector3 getScale() const;
		/// <summary>
		/// ワールド座標系でのScaleをscaleに変更する
		/// </summary>
		/// <param name="scale"></param>
		void setScale(const tnl::Vector3 scale);
		/// <summary>
		/// 現在のローカル座標系でのScaleを返す
		/// </summary>
		/// <returns>角度</returns>
		tnl::Vector3 getLocalScale() const;
		/// <summary>
		/// ローカル座標系でのScaleをscaleに変更する
		/// </summary>
		/// <param name="scale"></param>
		void setLocalScale(const tnl::Vector3 scale);


		//-----------------tree-------------------------------------------------------

		/// <summary>
		/// <para>親オブジェクトをparentに設定する</para>
		/// <para>nullptrを渡すとワールド座標系直下になる</para>
		/// </summary>
		/// <param name="parent"></param>
		/// <returns>成功したか</returns>
		bool setParent(Transform* parent);

		/// <summary>
		/// 現在の親オブジェクトを取得する
		/// </summary>
		/// <returns>親オブジェクト</returns>
		Transform* getParent() const;
		/// <summary>
		/// 現在の直下の子オブジェクトを取得する
		/// </summary>
		/// <returns>子オブジェクトのリスト</returns>
		std::list<Transform*> getChildren() const;

		/// <summary>
		/// dataが直下の子オブジェクトか否か
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		bool childrenContains(const Transform* data);
		/// <summary>
		/// dataがこのオブジェクト下に存在するか否か
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		bool allChildrenContains(const Transform* data);


		//--------------その他--------------------------

		/// <summary>
		/// このオブジェクトの上方向ベクトル
		/// </summary>
		tnl::Vector3 up() const;
		/// <summary>
		/// このオブジェクトの右方向ベクトル
		/// </summary>
		tnl::Vector3 right() const;
		/// <summary>
		/// このオブジェクトの前方向ベクトル
		/// </summary>
		tnl::Vector3 front() const;

		/// <summary>
		/// 現在の姿勢より自身の座標系でvalue度姿勢を変更する(未)
		/// </summary>
		/// <param name="value"></param>
		void ownEulerRotate(const tnl::Vector3 value);
		/// <summary>
		/// 現在の座標より自身の座標系でvalue座標を変更する(未)
		/// </summary>
		/// <param name="value"></param>
		void ownMove(const tnl::Vector3 value);

		//virtual void localEulerRotate(const tnl::Vector3 value);
		//virtual void localMove(const tnl::Vector3 value);

		/// <summary>
		/// 現在の姿勢よりワールド座標系でvalue度姿勢を変更する(未)
		/// </summary>
		/// <param name="value"></param>
		void eulerRotate(const tnl::Vector3 value);
		/// <summary>
		/// 現在の座標よりワールド座標系でvalue座標を変更する(未)
		/// </summary>
		/// <param name="value"></param>
		void move(const tnl::Vector3 value);

	private:


		tnl::Quaternion localRotation_;
		tnl::Vector3 localPosition_;
		tnl::Vector3 localScale_;

	};
}