//auto create by tocpp.rb, plz don't modify it!
//2013-08-24 16:53:27 +0800

#include "TemplateCamp.h"

using std::string;

TemplateCamp::TemplateCamp()
{
	m_sn = 0;
	m_InitResouce = 0;
	m_ResouceIncCD = 0;
	m_ResouceIncNum = 0;
	m_IsRebot = 0;

}

bool TemplateCamp::ReadJsonImpl(const CSJson::Value& obj)
{
		//sn
	 getJsonVal(obj["sn"], m_sn); 
		//��ʾ��
	 getJsonVal(obj["ShowName"], m_ShowName); 
		//���ı���
	 getJsonVal(obj["CoreArm"], m_CoreArm); 
		//��ʼ��Դ����
	 getJsonVal(obj["InitResouce"], m_InitResouce); 
		//��Դ������cd
	 getJsonVal(obj["ResouceIncCD"], m_ResouceIncCD); 
		//��Դ��������ֵ
	 getJsonVal(obj["ResouceIncNum"], m_ResouceIncNum); 
		//�Ƿ������
	 getJsonVal(obj["IsRebot"], m_IsRebot); 
		//��ʼ�����б�
	 getJsonVal(obj["InitBuilding"], m_InitBuilding); 

	return true;
}



