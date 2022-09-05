#ifndef _HKCAMERA_H_
#define _HKCAMERA_H_

#include <Windows.h>
#include <conio.h>
#include "MvCameraControl.h"
#include <string>

#include "HKError.h"
using std::string;

class HKCamera
{
public:
	explicit HKCamera();
	~HKCamera();

	int Init(const string& camera_ip, const string& net_ip, const string& featuresFile);

	int Close();

private:
	// ѡ�����
	void SelectCamera(const string& camera_ip, const string& net_ip);

	// �����������
	int SetParameters(const string& featuresFile);

	// ̽��������Ѱ���С(ֻ��GigE�����Ч)
	int DetectNetworkOptimalPackageSize();

	// ȡ���߳�
	void WorkThread();

private:
	void* handle_ = NULL;
	MV_CC_DEVICE_INFO stDevInfo_ = { 0 };
	MV_GIGE_DEVICE_INFO stGigEDev_ = { 0 };
	HKError& err_ = HKError::GetInstance();

	bool is_grabbing = true;
};

#endif

