#pragma once
#include "tree.h"
#include "../dxlib_ext/dxlib_ext.h"

#define EULER false
#define ROTATE true
#define CONVERT true

namespace ike {

	/// <summary>
	/// 座標、姿勢、サイズを管理するクラス
	/// </summary>
	class Transform{

	public:
		Transform();
		virtual ~Transform();

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
#if EULER
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
		void setLocalEulerAngle(const tnl::Vector3 angle);

#endif
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


		//--------------座標系変換----------------------
		
#if CONVERT

		//親のこの関数に値を渡してやることで、ワールドから子、子からワールドに変換できる
		
		/// <summary>
		/// このTransformの座標系の位置をワールド座標系での位置に変換する
		/// </summary>
		/// <param name="position">ローカル座標系での位置</param>
		/// <returns>ワールド座標系での位置</returns>
		tnl::Vector3 toWarldPosition(const tnl::Vector3& position) const;
		/// <summary>
		/// このTransformの座標系の位置をローカル座標系での位置に変換する
		/// </summary>
		/// <param name="position">ワールド座標系での位置</param>
		/// <returns>ローカル座標系での位置</returns>
		tnl::Vector3 toLocalPosition(const tnl::Vector3& position) const;
		/// <summary>
		/// このTransformの座標系の大きさをワールド座標系での大きさに変換する
		/// </summary>
		/// <param name="scale">ローカル座標系での大きさ</param>
		/// <returns>ワールド座標系での大きさ</returns>
		tnl::Vector3 toWarldScale(const tnl::Vector3& scale) const;
		/// <summary>
		/// このTransformの座標系の大きさをローカル座標系での大きさに変換する
		/// </summary>
		/// <param name="scale">ワールド座標系での大きさ</param>
		/// <returns>ローカル座標系での大きさ</returns>
		tnl::Vector3 toLocalScale(const tnl::Vector3& scale) const;
		/// <summary>
		/// このTransformの座標系の回転をワールド座標系での回転に変換する
		/// </summary>
		/// <param name="rotation">ローカル座標系での回転</param>
		/// <returns>ワールド座標系での回転</returns>
		tnl::Quaternion toWorldRotation(const tnl::Quaternion& rotation) const noexcept;
		/// <summary>
		/// このTransformの座標系の回転をローカル座標系での回転に変換する
		/// </summary>
		/// <param name="rotation">ワールド座標系での回転</param>
		/// <returns>ローカル座標系での回転</returns>
		tnl::Quaternion toLocalRotation(const tnl::Quaternion& rotation) const noexcept;

#endif

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

#if ROTATE
		/// <summary>
		/// 現在の姿勢より自身の座標系でvalue度姿勢を変更する(未)
		/// </summary>
		/// <param name="value"></param>
		void ownEulerRotate(const tnl::Vector3 value);
#endif
		/// <summary>
		/// 現在の座標より自身の座標系でvalue座標を変更する(未)
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
		/// 現在の座標よりワールド座標系でvalue座標を変更する(未)
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