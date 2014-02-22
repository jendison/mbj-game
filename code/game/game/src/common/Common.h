#ifndef __COMMON_H__
#define __COMMON_H__
#include <iostream>
#include "cocoa/CCGeometry.h"

struct CallBackArg
{
	CallBackArg() {nArgs = 0; memset(args, 0, sizeof(args));}
	int nArgs;
	void* args[5];
};

class CallBackArgPointer
{
public:
	CallBackArgPointer(CallBackArg* p) : pArg(p) {}
	~CallBackArgPointer(){delete pArg; pArg = nullptr;}
	CallBackArg* operator ->()
	{
		return pArg;
	}
private:
	CallBackArg* pArg;
};

namespace MathTools
{
	bool IsPointInCircularSector(const cocos2d::CCPoint& orign, float fRadio, float fTheta1, float fTheta2, const cocos2d::CCPoint& point);
}


namespace cocos2d 
{
	/** draws a solid circle given the center, radius and number of segments. */
	void ccDrawSolidCircle(const CCPoint& center, float radius,  //���ĵ㼰�뾶
		float startDegree, //��ʼ�Ƕȣ�x��������Ϊ0��
		float degree,      //�����Ƕȣ���ʱ��Ϊ����������
		int segments,      //���Բ�ε����θ���
		float scaleX, float scaleY);

}
#endif //__COMMON_H__