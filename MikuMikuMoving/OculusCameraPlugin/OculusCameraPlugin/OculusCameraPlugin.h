// MikuMikuMoving用 OculusRiftカメラプラグイン
// twitter: @GOROman

#pragma once

// OculusRift 管理クラス
#include "OculusMan.h"

using namespace System;
using namespace System::Drawing;
using namespace MikuMikuPlugin;
using namespace DxMath;

#define MMP MikuMikuPlugin

namespace OculusCameraPlugin {

	public ref class OculusCameraPlugin : IResidentPlugin
	{
		OculusRift*	pOR;

	public:

		// コンストラクタ
		OculusCameraPlugin() {
			pOR = new OculusRift;
		}

		virtual ~OculusCameraPlugin() {	
			delete pOR;
		}

		// このプラグインのGUID
	    virtual property System::Guid GUID
        {
            System::Guid get() { return System::Guid("e87adb38-46d3-4c14-b9f3-c6f0a3b35679"); }
        }

		// プラグインの名前や作者名、プラグインの説明
		virtual property String^ Description
        {
            String^ get() { return "OculusRift Camera Plugin v0.01 by GOROman"; }
        }

		// ボタンに表示するテキスト
		virtual property String^ Text
        {
            String^ get() { return "Oculus Rift" + Environment::NewLine + "カメラ"; }
        }

		// ボタンに表示する英語テキスト
		virtual property String^ EnglishText
        {
            String^ get() { return "Oculus Rift" + Environment::NewLine + "Camera"; }
        }

		// メインフォーム
		virtual property System::Windows::Forms::IWin32Window^ ApplicationForm ;

		// シーンオブジェクト
		virtual property MikuMikuPlugin::Scene^ Scene;

		// 中コマンドバーに表示するアイコン画像(20x20)
		virtual property System::Drawing::Image^ SmallImage
		{
			System::Drawing::Image^ get() { return nullptr; }
        }

		// ボタンに表示するアイコン画像(32x32)
		virtual property System::Drawing::Image^ Image
		{
			System::Drawing::Image^ get() { return nullptr; }
        }

		// プラグイン作成時に1度だけ呼ばれます。
		virtual void Initialize()
        {
		}

		// 更新
		virtual void Update(float Frame, float ElapsedTime)
        {
			float yaw, pitch, roll;
			
			// 更新
			pOR->Update();

			// 姿勢を取得
			pOR->GetOrientation( &yaw, &pitch, &roll );

			DxMath::Vector3^ pos   = gcnew DxMath::Vector3( 0, 0, 0 );
			DxMath::Vector3^ angle = gcnew DxMath::Vector3( -pitch, yaw, roll );


			//カメラ
            for each (MikuMikuPlugin::Camera^ camera in Scene->Cameras) {
  
				MikuMikuPlugin::CameraMotionData mdata = camera->CurrentMotion;

//				mdata.Position = *pos;
				mdata.Angle    = *angle;
				mdata.Radius   = 0.0f;

				camera->CurrentMotion = mdata;

				for each (MMP::CameraLayer^ layer in camera->Layers)
                {
					layer->CurrentLocalMotion = mdata;
				}
			}

		}

		// プラグインが有効化されたときに呼び出されます。
		virtual void Enabled()
        {
		}

		// プラグインが無効化されたときに呼び出されます。
		virtual void Disabled()
        {
        }

	};
}
