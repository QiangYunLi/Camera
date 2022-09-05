#ifndef _HKCAMERA_H_
#define _HKCAMERA_H_

#include "MvCameraControl.h"

class HKCamera
{
public:
	explicit HKCamera();
	~HKCamera();

	int Init();

private:
	// Ñ¡ÔñÏà»ú
	int SelectCameraByEnumIndex(const int& camera_index);
	int SelectCameraBy
};

#endif

