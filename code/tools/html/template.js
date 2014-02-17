function Create(template){
var strs = []
for(var j = 0; j < template.length; ++j){
	var t = template[j]
	if(t.type == "text"){
		var val = t.value
		if (val == null ){
		val = t.init
		}
		strs.push({t.name +":<input type='text' id='"+t.key+"' value='"+val+"' />"})
	}
	else if (t.obj_type == "select")
	{
	    var str = "<select id ='" + t.key + "'>"
		var val = t.value
	    for (var i = 0; i < t.options.length; ++i) {      
			if (val == t.options[i]){
			 str += "<option selected>"
			}
			else
			{
			  str += "<option>"
			}
	        str += t.options[i]
            str += "</option>"
	    }
	    str += "</select>"
	    strs.push(str)
	}
	else if (t.type == "table") {
	    var str = ""
	    str += "<table id='" + t.key + "' style='border:1px solid #ace; width:1200px'  >"
	
		var rows= t.rows
		var cols = t.columns
		if (rows){	
		    for (var i = 0; i < rows.length; ++i) {
            var row = rows[i]
			str +="<tr>"
			var json = { type: row[3], key: row[1], value: row[4], option: row[2] }
			str += "<td>"
			str += row[0] + "</td><td>"
            str += row[2] +"</td><td>"
			str += create_input(json)		
			str += "</td></tr>"
			}
		}		
	    str += "</table>"
	    strs.push(str)
	}
}
return strs;
}

function create_input(json){

if (json.type == "text"){
    var str = '<input type="text" id="_id" value="_val" />'
    str = str.replace(/_id/g, json.key)
    str = str.replace(/_val/g, json.value)
    return str;
}
else if (json.type == "select") {

    var str = '<select id="_id" value="_val" >_option</select>'
    str = str.replace(/_id/g, json.key)
    str = str.replace(/_val/g, json.value)
    str = str.replace("_option", json.option)
    return str;
}
    return ""
}

function add_tr(tb){
		var mytable = document.getElementById(tb);
				
		var myrow = document.getElementById("tr_"+tb);  
		var th_cells = myrow.cells;

		var lineID = mytable.lineID;
		if (lineID == null)
			lineID = mytable.rows.length;
			
		var mytr = mytable.insertRow(); 
		mytr.setAttribute("id","tr_"+lineID) 
		
		var td0 = mytr.insertCell();
		td0.innerHTML ="<a href='javascript:del_tr(\""+tb+"\","+lineID+")'>"+ lineID +"</a>";

		for (var i = 1; i < th_cells.length; ++i) {
		    var td = mytr.insertCell(); 
		    var hi = th_cells[i].all[0]
		    if (hi.init__) {
		        td.innerHTML = hi.init__;
		    }

		    if (hi.type__ == "text") {
		        var f = new onclickAddAEditor(td, hi.init__)
		        td.onclick = f.onclick;
		    }
		    else if (hi.type__ == "select") {
		        var f = new onclickAddASelect(td, hi.options__, hi.init__)
		        td.onclick = f.onclick;
		    }
		}
		
		lineID += 1;
		mytable.lineID = lineID
}

function del_tr(tb, line){
	 var mytable = document.getElementById(tb);     
	 var myrow = document.getElementById("tr_"+line);       
	 mytable.deleteRow(myrow.rowIndex); 
}

function onClickTdText(obj){
var f = new onclickAddAEditor(obj)
f.onclick();
}

function onclickAddAEditor(obj) {
    this.onclick = function () {
        if (obj.hasTexflied) return;

        var textflied = document.createElement("input")
        textflied.onblur = function () {
            obj.removeChild(textflied)
            obj.innerHTML = textflied.value
            obj.hasTexflied = false;
        }
        textflied.onclick = function () { }
        textflied.value = obj.innerHTML
        obj.innerHTML = ""
        obj.appendChild(textflied)
        textflied.focus()
        obj.hasTexflied = true;
        textflied.style.width = obj.style.width
    };
}

function onClickTdSelect(obj){
var f = new onclickAddASelect(obj)
f.onclick();
}
function onclickAddASelect(obj, options, init) {

    this.onclick = function () {
        if (obj.hasSelectFlied) return false;
    
        var val = obj.innerHTML
        obj.innerHTML = "<select>"+options +"<select>"
        selectFlied = obj.all[0]
        selectFlied.value = val
        selectFlied.onblur = function () {
            obj.removeChild(selectFlied)
            obj.innerHTML = selectFlied.options[selectFlied.selectedIndex].text
            obj.hasSelectFlied = false
        }

        obj.hasSelectFlied = true
    }
}