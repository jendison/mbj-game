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
			"name" : "��ʾ��",
			"key" : "ShowName",
			"type" : {
				"name" : "string"
			},
			"editor" : "text",
			"comment" : "��ʾ��"
		}, {
			"name" : "�ؿ�",
			"key" : "Stages",
			"type" : {
				"name" : "unit",
				"index" : "UStage",
				"multi":true
			},
			"editor" : "text",
			"comment" : "�ؿ�"
		}
	],
	"unit" : {
		"UStage" : {
			"ID" : {
				"name" : "�ؿ�id",
				"type" : {
					"name" : "int"
				},
				"editor" : "numberbox",
				"comment" : "�ؿ�id"
			},
			"MapPath" : {
				"name" : "�ؿ���ͼ�ļ�·��",
				"type" : {
					"name" : "string"
				},
				"editor" : "text",
				"comment" : "�ؿ���ͼ�ļ�·��"
			},
			"Prompt" : {
				"name" : "��ʾ��",
				"type" : {
					"name" : "string"
				},
				"editor" : "text",
				"comment" : "��ʾ��"
			},
			"Congratulations" : {
				"name" : "���غش�",
				"type" : {
					"name" : "string"
				},
				"editor" : "text",
				"comment" : "���غش�"
			}
		}
	}
}
