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
		return string("运行正常。");

	case ACCESSIBLE_:
		return string("相机不可达！");

	case CREATE_HANDLE_:
		return string("创建相机句柄失败！");

	case OPEN_:
		return string("打开相机失败！");

	case SetPacketSize_:
		return string("设置网络最佳包失败！");

	case GetPacketSize_:
		return string("获取网络最佳包失败！");

	case LOADPROPERTIES_:
		return string("加载相机属性失败！");

	case STARTGRABBING_:
		return string("开始取流失败！");

	case GETIMAGE_:
		return string("图像取流失败！");

	case STOPGRABBING_:
		return string("停止取流失败！");

	case CLOSE_:
		return string("关闭相机失败！");

	case DESTROYHANLDE_:
		return string("销毁相机句柄失败！");
	}
}