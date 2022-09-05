#include "HKCamera.h"

#include <thread>

HKCamera::HKCamera()
{

}

HKCamera::~HKCamera()
{
	is_grabbing = false;
	Sleep(1000);

}

int HKCamera::Init(const string& camera_ip, const string& net_ip, const string& featuresFile)
{
	int nRet = MV_OK;

	// 1. ѡ�����
	SelectCamera(camera_ip, net_ip);

	// 2. �ж�����Ƿ�ɷ���
	unsigned int accessMode;
	nRet = MV_CC_IsDeviceAccessible(&stDevInfo_, accessMode);
	if (MV_OK != nRet)
	{
		err_.CREATE_HANDLE_;
	}

	// 3. ����������
	nRet = MV_CC_CreateHandle(&handle_, &stDevInfo_);
	if (MV_OK != nRet)
	{
		return err_.CREATE_HANDLE_;
	}

	// 4. �������
	nRet = MV_CC_OpenDevice(handle_);
	if (MV_OK != nRet)
	{
		return err_.OPEN_;
	}

	// 5. ��������
	SetParameters(featuresFile);

	// 7. ����ȡ���� ����ȡ������Ҫ6
	nRet = MV_CC_StartGrabbing(handle_);
	if (MV_OK != nRet)
	{
		return err_.STARTGRABBING_;
	}

	// 8. ȡ���߳�
	std::thread thread_imgPro = std::thread(&HKCamera::WorkThread, this);
	thread_imgPro.detach();

	return err_.OK_;
}

int HKCamera::Close()
{
	int nRet = MV_OK;

	// 9. ֹͣȡ��
	nRet = MV_CC_StopGrabbing(handle_);
	if (MV_OK != nRet)
	{
		return err_.STOPGRABBING_;
	}

	// 10. �ر��豸
	nRet = MV_CC_CloseDevice(handle_);
	if (MV_OK != nRet)
	{
		return err_.CLOSE_;
	}

	// 11. ���پ�� 
	nRet = MV_CC_DestroyHandle(handle_);
	if (MV_OK != nRet)
	{
		return err_.DESTROYHANLDE_;
	}

	return err_.OK_;
}

void HKCamera::WorkThread()
{
	int nRet = MV_OK;
	MV_FRAME_OUT stOutFrame = { 0 };

	while (is_grabbing)
	{
		nRet = MV_CC_GetImageBuffer(handle_, &stOutFrame, 1000);
		if (MV_OK != nRet)
		{
			printf("Get Image fail! nRet [0x%x]\n", nRet);
			continue;
		}

		// ͼ������صĴ���
		nRet = MV_CC_FreeImageBuffer(handle_, &stOutFrame);
		if (nRet != MV_OK)
		{
			printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
		}
	}
}

int HKCamera::SetParameters(const string& featuresFile)
{
	DetectNetworkOptimalPackageSize();

	int nRet = MV_CC_FeatureSave(handle_, featuresFile.c_str());
	if (MV_OK != nRet)
	{
		return err_.LOADPROPERTIES_;
	}

	return err_.OK_;
}

int HKCamera::DetectNetworkOptimalPackageSize()
{
	if (stDevInfo_.nTLayerType == MV_GIGE_DEVICE)
	{
		int nPacketSize = MV_CC_GetOptimalPacketSize(handle_);
		if (nPacketSize > 0)
		{
			int nRet = MV_CC_SetIntValue(handle_, "GevSCPSPacketSize", nPacketSize);
			if (nRet != MV_OK)
			{
				return err_.SetPacketSize_;
			}
		}
		else
		{
			return err_.GetPacketSize_;
		}
	}
}

// ͨ��ipѡ�����
void HKCamera::SelectCamera(const string& camera_ip, const string& net_ip)
{
	unsigned int nIp1, nIp2, nIp3, nIp4, nIp;
	sscanf_s(camera_ip.c_str(), "%d.%d.%d.%d", &nIp1, &nIp2, &nIp3, &nIp4);
	nIp = (nIp1 << 24) | (nIp2 << 16) | (nIp3 << 8) | nIp4;
	stGigEDev_.nCurrentIp = nIp;

	sscanf_s(net_ip.c_str(), "%d.%d.%d.%d", &nIp1, &nIp2, &nIp3, &nIp4);
	nIp = (nIp1 << 24) | (nIp2 << 16) | (nIp3 << 8) | nIp4;
	stGigEDev_.nNetExport = nIp;

	stDevInfo_.nTLayerType = MV_GIGE_DEVICE;// ch:��֧��GigE��� | en:Only support GigE camera
	stDevInfo_.SpecialInfo.stGigEInfo = stGigEDev_;
}


