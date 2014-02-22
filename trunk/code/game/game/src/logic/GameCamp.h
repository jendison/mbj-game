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
	int32t m_nRes; //��Դ����
	int32t m_nCD;	//��Դ����cd
	int32t m_nIncreateVal;	//������ֵ
	int32t m_nCoreArm;		//���ı���
	int32t m_nSN;
};

#endif
