//auto create by tocpp.rb, plz don't modify it!
//#{Time.now}
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _#{FileName}_H__
#define _#{FileName}_H__
using std::string;
#{enumClass}
#{unitStruct}
class #{ClassName} : public TemplateBase
{
public:
	#{ClassName}();
	~#{ClassName}(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
#{getter}
	
private:
#{memberList}
};

#endif //_#{FileName}_H__
