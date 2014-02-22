#include "TypeDefine.h"

#ifndef __GAMECAMP_H__
#define __GAMECAMP_H__

class GameCamp
{
public:
	GameCamp();
	~GameCamp();
	static GameCamp* create(int32t nSN);
	bool initWithGame(int32t nSN);
	int32t getCoreArm() const {return m_nCoreArm;}
	int32t getSN() const {return m_nSN;}

private:
	int32t m_nRes; //资源数量
	int32t m_nCD;	//资源增长cd
	int32t m_nIncreateVal;	//增长数值
	int32t m_nCoreArm;		//核心兵种
	int32t m_nSN;
};

#endif
