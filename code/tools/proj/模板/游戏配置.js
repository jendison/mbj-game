{
	"template_base" : {
		"version" : 1,
		"sn_min" : 1,
		"sn_max" : 9999,
		"key" : "game"
	},
	"fields" : [{
			"name" : "SN",
			"key" : "sn",
			"editor" : "text",
			"type" : {
				"name" : "int",
				"init" : "1"
			},
			"init" : "0",
			"value" : "1"
		}, {
			"name" : "显示名",
			"key" : "ShowName",
			"type" : {
				"name" : "string"
			},
			"editor" : "text",
			"comment" : "显示名"
		}, {
			"name" : "关卡",
			"key" : "Stages",
			"type" : {
				"name" : "unit",
				"index" : "UStage",
				"multi":true
			},
			"editor" : "text",
			"comment" : "关卡"
		}
	],
	"unit" : {
		"UStage" : {
			"ID" : {
				"name" : "关卡id",
				"type" : {
					"name" : "int"
				},
				"editor" : "numberbox",
				"comment" : "关卡id"
			},
			"MapPath" : {
				"name" : "关卡地图文件路径",
				"type" : {
					"name" : "string"
				},
				"editor" : "text",
				"comment" : "关卡地图文件路径"
			},
			"Prompt" : {
				"name" : "提示语",
				"type" : {
					"name" : "string"
				},
				"editor" : "text",
				"comment" : "提示语"
			},
			"Congratulations" : {
				"name" : "过关贺词",
				"type" : {
					"name" : "string"
				},
				"editor" : "text",
				"comment" : "过关贺词"
			}
		}
	}
}
