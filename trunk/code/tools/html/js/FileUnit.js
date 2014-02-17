function File(fileName, flgs){

this.open = function(){
	var ret = window.external.open(fileName, flgs);
	var r = $.parseJSON(ret);
	if (!r.success){
	    throw r.msg;
	}
},

this.readAll = function(){
	var ret = window.external.all();
	var r = $.parseJSON(ret);
	if (!r.success){
	    throw r.msg;
	}
	
	return r.msg;
},

this.close = function(){
	window.external.close();
},

this.write = function(str){
	var ret = window.external.write(str, 1, 0);
	var r = $.parseJSON(ret);
	if (!r.success){
	    throw r.msg;
	}
},

this.seekg = function (pos) {
	window.external.seekg(pos)
}
}


function GetAllInDir(path){
return window.external.getDir(path);
}


function GetPathFileName(path){
	var value=path;
     var last=value.lastIndexOf("\\");
     var filename=value.substring(last+1,value.length);
	 return filename;
}

function exeContentCmd(path, cmd){
	var ret = window.external.exeContentCmd(path, cmd)
	var r = $.parseJSON(ret);
	return r.success;
}
