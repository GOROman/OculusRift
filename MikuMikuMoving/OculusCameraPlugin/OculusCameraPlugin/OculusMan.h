// OculusRift 管理クラス
// twitter: @GOROman

#pragma once

// Oculus SDK
#include "LibOVR\Include\OVR.h"

// OculusSDK ライブラリ
#pragma comment( lib, "LibOVR/Lib/Win32/libovr.lib" )

// 依存しているライブラリ群
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "user32.lib" )

// OculusRift 管理クラス
class OculusRift {
	// デバイスマネージャー
	OVR::Ptr<OVR::DeviceManager> pManager;

	// HMDデバイス
	OVR::Ptr<OVR::HMDDevice>     pHMD;

	// センサーデバイス
	OVR::Ptr<OVR::SensorDevice>  pSensor;

	// センサーフィージョン
	OVR::SensorFusion		     SFusion;

	// 姿勢(クォータニオン)
	OVR::Quatf					 hmdOrient;

public:

	// コンストラクタ
	OculusRift() {
		Init();
	}

	// デストラクタ
	~OculusRift() {
		Destroy();
	}

	// 初期化
	void Init() {
		// システムの初期化
		OVR::System::Init();

		// デバイスマネージャーの生成
		pManager = *OVR::DeviceManager::Create();

		// HMDデバイスの生成
		pHMD	 = *pManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();

		// センサーデバイスの取得
		pSensor  = *pHMD->GetSensor();

		// センサーをセンサーフィージョンへアタッチ
		if ( pSensor ) {
			SFusion.AttachToSensor( pSensor );
		}
	}

	// 破棄
	void Destroy() {
		pSensor.Clear();
		pHMD.Clear();
		pManager.Clear();

		// システムの破棄
		OVR::System::Destroy();
	}

	// 現在の姿勢を得る
	const int Update() {

		// アタッチされているか？
		if ( SFusion.IsAttachedToSensor() == false ) {
			return 1;												// センサーが無い場合はエラー
		}

		// all orintations are in degrees
		hmdOrient = SFusion.GetOrientation();

		return 0;
	}

	// 角度をオイラー角で得る
	void GetOrientation(float* yaw, float* pitch, float* roll) 
	{
		hmdOrient.GetEulerAngles<OVR::Axis_Y, OVR::Axis_X, OVR::Axis_Z>(yaw, pitch, roll);
	}

	// 姿勢を行列で得る
	void GetMatrix( OVR::Matrix4f* matrix )
	{
		// クォータニオンから行列へ変換
		*matrix = hmdOrient;
	}

};
