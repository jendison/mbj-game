//auto create by tocpp.rb, plz don't modify it!
//2013-08-24 16:53:26 +0800

#include "TemplateBuilding.h"

using std::string;

TemplateBuilding::TemplateBuilding()
{
	m_sn = 0;
//
}

bool TemplateBuilding::ReadJsonImpl(const CSJson::Value& obj)
{
		//sn
	 getJsonVal(obj["sn"], m_sn); 
		//��Ϸ����ʾ��UI�Ľ����Ӧ�����������
	 getJsonVal(obj["ShowName"], m_ShowName); 
		//������ť��ͼ��
	 getJsonVal(obj["icon"], m_icon); 
		//��Ӧ��������
	 getJsonVal(obj["Arms"], m_Arms); 
		//����
	 m_Cost.ReadJsonImpl(obj["Cost"]); 

	return true;
}



