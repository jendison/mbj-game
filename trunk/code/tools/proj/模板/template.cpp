//auto create by tocpp.rb, plz don't modify it!
//#{Time.now}

#include "#{ClassName}.h"

using std::string;

#{ClassName}::#{ClassName}()
{
#{initlist}
}

bool #{ClassName}::ReadJsonImpl(const CSJson::Value& obj)
{
#{reaeJson}
	return true;
}



