// OculusRift �Ǘ��N���X
// twitter: @GOROman

#pragma once

// Oculus SDK
#include "LibOVR\Include\OVR.h"

// OculusSDK ���C�u����
#pragma comment( lib, "LibOVR/Lib/Win32/libovr.lib" )

// �ˑ����Ă��郉�C�u�����Q
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "user32.lib" )

// OculusRift �Ǘ��N���X
class OculusRift {
	// �f�o�C�X�}�l�[�W���[
	OVR::Ptr<OVR::DeviceManager> pManager;

	// HMD�f�o�C�X
	OVR::Ptr<OVR::HMDDevice>     pHMD;

	// �Z���T�[�f�o�C�X
	OVR::Ptr<OVR::SensorDevice>  pSensor;

	// �Z���T�[�t�B�[�W����
	OVR::SensorFusion		     SFusion;

	// �p��(�N�H�[�^�j�I��)
	OVR::Quatf					 hmdOrient;

public:

	// �R���X�g���N�^
	OculusRift() {
		Init();
	}

	// �f�X�g���N�^
	~OculusRift() {
		Destroy();
	}

	// ������
	void Init() {
		// �V�X�e���̏�����
		OVR::System::Init();

		// �f�o�C�X�}�l�[�W���[�̐���
		pManager = *OVR::DeviceManager::Create();

		// HMD�f�o�C�X�̐���
		pHMD	 = *pManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();

		// �Z���T�[�f�o�C�X�̎擾
		pSensor  = *pHMD->GetSensor();

		// �Z���T�[���Z���T�[�t�B�[�W�����փA�^�b�`
		if ( pSensor ) {
			SFusion.AttachToSensor( pSensor );
		}
	}

	// �j��
	void Destroy() {
		pSensor.Clear();
		pHMD.Clear();
		pManager.Clear();

		// �V�X�e���̔j��
		OVR::System::Destroy();
	}

	// ���݂̎p���𓾂�
	const int Update() {

		// �A�^�b�`����Ă��邩�H
		if ( SFusion.IsAttachedToSensor() == false ) {
			return 1;												// �Z���T�[�������ꍇ�̓G���[
		}

		// all orintations are in degrees
		hmdOrient = SFusion.GetOrientation();

		return 0;
	}

	// �p�x���I�C���[�p�œ���
	void GetOrientation(float* yaw, float* pitch, float* roll) 
	{
		hmdOrient.GetEulerAngles<OVR::Axis_Y, OVR::Axis_X, OVR::Axis_Z>(yaw, pitch, roll);
	}

	// �p�����s��œ���
	void GetMatrix( OVR::Matrix4f* matrix )
	{
		// �N�H�[�^�j�I������s��֕ϊ�
		*matrix = hmdOrient;
	}

};
