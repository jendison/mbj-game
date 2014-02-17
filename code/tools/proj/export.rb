#econding:utf-8

require 'Json'
def traverse_dir(file_path)  
  if File.directory? file_path  
    Dir.foreach(file_path) do |file|  
      if file!="." and file!=".."  and file !~ /^_/
        traverse_dir(file_path+"/"+file){|x| yield x}  
      end  
    end  
  else  
    yield  file_path  
  end  
end

def readFile(path)
	context = ""
	File.open(path, 'r') do |f|
	context = f.read(f.size)
	end
	context.encode("utf-8", "gbk")
end

@commonTemplate = nil

def replaceObject(json, objType, temp, objs)	
		#json = fiedls[key]
		return if json.nil?
		
		isMulti = objType["multi"]
		
		#处理数组
		if isMulti then 
			objTypeClone = objType.clone
			objTypeClone["multi"] = false
			#puts "m #{json} -- #{objTypeClone}"
			json.each do |e|
			#把数组解开
				replaceObject(e, objTypeClone, temp, objs)
			end
		else 
			if objType["name"] == "object" then
					#if json.is_a? Array then				
					#	json.each do |e|
					#		replaceObject(e, key, objType, temp, objs)
					#	end
		
					#else
						#puts "obj #{json.encode('gbk', 'utf-8')} "
						objName = json
						obj = objs[objName]
						raise "#{json.to_s.encode('gbk', 'utf-8')} not find" if obj.nil?
						sn = obj["fields"]["sn"]
						json.replace sn.to_s
						#fiedls[key] = json

				#	end
			
			elsif objType["name"] == "unit" then
			#unit 挨项解开
				#puts "unit ++#{json}"
				unitName = objType["index"]
			
				unit = temp["unit"][unitName] unless temp["unit"].nil?					
				unit = @commonTemplate["unit"][unitName] if unit.nil?
						
				puts "unit #{objType} - #{unitName} not found!!" if unit.nil? 				
				json.each do |k, v|
					puts "unit field #{k} nil" if unit[k].nil?					
					replaceObject(v, unit[k]["type"], temp, objs)
				end	

	
			else 
				
			end
		end
end


system("del /q data\\*")

templatepath="模板"
path="物体"

#打开模板
 temps={}
 traverse_dir(templatepath.encode("gbk")) do |f|  
	curFile=f.to_s()
	if curFile =~ /\.js$/ then
		fileName=File.basename(curFile, ".js")
		fileName=fileName.encode("utf-8", "gbk")
		puts "template - #{fileName}"		
		
		jObj=JSON.parse(readFile(curFile))	
		temps[fileName] = jObj
	end 
 end
 
@commonTemplate = temps["common"]
 
 #打开物体
objs={}
 traverse_dir(path.encode("gbk")) do |f|  
	curFile=f.to_s()
	puts "obj - #{curFile}"
	begin
		if curFile !~ /\.js$/ then		
			break
		end
		
		fileName=File.basename(curFile, ".js").encode("utf-8", "gbk")
		
	  if not objs[fileName].nil? then
		puts "error --- [#{fileName}] found"
		break
	  end
	  	
		s = readFile(curFile)
		jObj = JSON.parse(s)
		tempName = jObj['base']['template']
		t = temps[tempName]
		tbase = t["template_base"]
		snMin = tbase["sn_min"]
		snMax = tbase["sn_max"]
		
		fields = jObj["fields"]
		sn = fields["sn"].to_i
		#验证SN
		if sn < snMin || sn > snMax then
			puts "error sn(#{sn}) must be in [#{snMin}, #{snMax})"
			break
		end
			
		#验证字段是否缺少
		tfields = t["fields"]
		tfields.each do |j|
			jkey=j["key"]
			if fields[jkey].nil? then
				puts "warning -- obj[#{fileName}] , key[#{jkey}] is nil"
			end
		end		
				
		objs[fileName] = jObj				
	  
	end while false
	 
 end
 

 #替换物体名为SN
 jsons = []
 
 objs.each do |key, jObj|
		tempName = jObj['base']['template']
		fields = jObj["fields"]
		t = temps[tempName]
	
		tfields = t["fields"]
		puts "replace obj - #{key}"
		
		tfields.each do |j|		
			replaceObject(fields[j["key"]], j["type"], t, objs)			
		end
		jsons << jObj
 end
 

 jsons.each do |e|
	fileds = e["fields"]
	sn = fileds["sn"].to_i
	 
	if sn != 0 then
		File.open("data/#{sn}.js", "w") do |f|
			f.write fileds.to_json
		end
	end
 end

 system("pause")
 
 
 
 
 
 
 
 
 