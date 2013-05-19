// MikuMikuMoving�p OculusRift�J�����v���O�C��
// twitter: @GOROman

#pragma once

// OculusRift �Ǘ��N���X
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

		// �R���X�g���N�^
		OculusCameraPlugin() {
			pOR = new OculusRift;
		}

		virtual ~OculusCameraPlugin() {	
			delete pOR;
		}

		// ���̃v���O�C����GUID
	    virtual property System::Guid GUID
        {
            System::Guid get() { return System::Guid("e87adb38-46d3-4c14-b9f3-c6f0a3b35679"); }
        }

		// �v���O�C���̖��O���Җ��A�v���O�C���̐���
		virtual property String^ Description
        {
            String^ get() { return "OculusRift Camera Plugin v0.01 by GOROman"; }
        }

		// �{�^���ɕ\������e�L�X�g
		virtual property String^ Text
        {
            String^ get() { return "Oculus Rift" + Environment::NewLine + "�J����"; }
        }

		// �{�^���ɕ\������p��e�L�X�g
		virtual property String^ EnglishText
        {
            String^ get() { return "Oculus Rift" + Environment::NewLine + "Camera"; }
        }

		// ���C���t�H�[��
		virtual property System::Windows::Forms::IWin32Window^ ApplicationForm ;

		// �V�[���I�u�W�F�N�g
		virtual property MikuMikuPlugin::Scene^ Scene;

		// ���R�}���h�o�[�ɕ\������A�C�R���摜(20x20)
		virtual property System::Drawing::Image^ SmallImage
		{
			System::Drawing::Image^ get() { return nullptr; }
        }

		// �{�^���ɕ\������A�C�R���摜(32x32)
		virtual property System::Drawing::Image^ Image
		{
			System::Drawing::Image^ get() { return nullptr; }
        }

		// �v���O�C���쐬����1�x�����Ă΂�܂��B
		virtual void Initialize()
        {
		}

		// �X�V
		virtual void Update(float Frame, float ElapsedTime)
        {
			float yaw, pitch, roll;
			
			// �X�V
			pOR->Update();

			// �p�����擾
			pOR->GetOrientation( &yaw, &pitch, &roll );

			DxMath::Vector3^ pos   = gcnew DxMath::Vector3( 0, 0, 0 );
			DxMath::Vector3^ angle = gcnew DxMath::Vector3( -pitch, yaw, roll );


			//�J����
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

		// �v���O�C�����L�������ꂽ�Ƃ��ɌĂяo����܂��B
		virtual void Enabled()
        {
		}

		// �v���O�C�������������ꂽ�Ƃ��ɌĂяo����܂��B
		virtual void Disabled()
        {
        }

	};
}
