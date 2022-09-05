#include "HKError.h"

HKError::HKError()
{

}

HKError::~HKError()
{

}

string HKError::ParaseError(const int& err)
{
	switch (err)
	{
	case OK_:
		return string("����������");

	case ACCESSIBLE_:
		return string("������ɴ");

	case CREATE_HANDLE_:
		return string("����������ʧ�ܣ�");

	case OPEN_:
		return string("�����ʧ�ܣ�");

	case SetPacketSize_:
		return string("����������Ѱ�ʧ�ܣ�");

	case GetPacketSize_:
		return string("��ȡ������Ѱ�ʧ�ܣ�");

	case LOADPROPERTIES_:
		return string("�����������ʧ�ܣ�");

	case STARTGRABBING_:
		return string("��ʼȡ��ʧ�ܣ�");

	case GETIMAGE_:
		return string("ͼ��ȡ��ʧ�ܣ�");

	case STOPGRABBING_:
		return string("ֹͣȡ��ʧ�ܣ�");

	case CLOSE_:
		return string("�ر����ʧ�ܣ�");

	case DESTROYHANLDE_:
		return string("����������ʧ�ܣ�");
	}
}