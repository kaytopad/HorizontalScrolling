#pragma once
class Animation
{
private:
	
	// 分割画像
	int* images;
	int startFrame;
	int frameCount;
	int speed;
	int startTime;
public:
	//===============================
	// コンストラクタ
	//===============================
	Animation();

	void SetImages(int *img);

	void Play(int startFrame, int frameCount, int speed,int currentTime);

	int GetImage(int currentTime);




};

