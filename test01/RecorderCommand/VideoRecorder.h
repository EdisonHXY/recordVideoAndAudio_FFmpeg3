#pragma once
class CVideoRecorder
{
public:
	CVideoRecorder(void);
	~CVideoRecorder(void);

public:
	
	void SetVideoBuffer(unsigned char * src,long width,long height);

};

