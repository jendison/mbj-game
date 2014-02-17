{
	"template_base" : {
		"version" : 0,
		"sn_min" : 0,
		"sn_max" : 0,
		"key" : "common"
	},
	"fields" : [{
			"name" : "SN",
			"key" : "sn",
			"type" : {
				"name" : "int",
				"init" : "40000"
			},
			"editor" : "text",
			"comment" : "sn"
		}
	],
	"enum" : {
		"TBool" : [{
				"key" : "NULL",
				"name" : "��",
				"value" : 0
			}, {
				"key" : "true",
				"name" : "��",
				"value" : 1
			}, {
				"key" : "false",
				"name" : "��",
				"value" : 2
			}
		],
		"TBuffEffectType" : [{
				"key" : "NULL",
				"name" : "��",
				"value" : 0
			}, {
				"key" : "reduceSpeed",
				"name" : "����",
				"value" : 1
			}, {
				"key" : "frozen",
				"name" : "����",
				"value" : 2
			}, {
				"key" : "attack",
				"name" : "������",
				"value" : 3
			}, {
				"key" : "defence",
				"name" : "������",
				"value" : 4
			}, {
				"key" : "addHp",
				"name" : "�ָ�hp",
				"value" : 5
			}, {
				"key" : "addPower",
				"name" : "�ָ�����",
				"value" : 6
			}, {
				"key" : "changeHpOfTimer",
				"name" : "����Ӱ������",
				"value" : 7
			}, {
				"key" : "addMaxHP",
				"name" : "��������",
				"value" : 8
			}, {
				"key" : "addMaxPower",
				"name" : "��������",
				"value" : 9
			}, {
				"key" : "damageScript",
				"name" : "�˺��ű�",
				"value" : 10
			}
			, {
				"key" : "addAirDamage",
				"name" : "���ӶԿ��˺�",
				"value" : 11
			}
			, {
				"key" : "addLandDamage",
				"name" : "���ӶԵ��˺�",
				"value" : 12
			}
		],
		"TValuetype" : [{
				"key" : "NULL",
				"name" : "��",
				"value" : 0
			}, {
				"key" : "value1",
				"name" : "��ֵ���������",
				"value" : 1
			}, {
				"key" : "percent1",
				"name" : "�ٷֱ�",
				"value" : 2
			}
		],
		"TRange" : [{
				"key" : "NULL",
				"name" : "��",
				"value" : 0
			}, {
				"key" : "circular",
				"name" : "Բ��",
				"value" : 1
			}, {
				"key" : "sector",
				"name" : "����",
				"value" : 2
			}, {
				"key" : "rectangle",
				"name" : "����",
				"value" : 3
			}
		],
		"TOrbit" : [{
				"key" : "NULL",
				"name" : "��",
				"value" : 0
			}, {
				"key" : "line",
				"name" : "ֱ��",
				"value" : 1
			}, {
				"key" : "parabola",
				"name" : "������",
				"value" : 2
			}, {
				"key" : "bezier",
				"name" : "����������",
				"value" : 3
			}
		],
		"TDeadType" : [{
				"key" : "animate",
				"name" : "����",
				"value" : "0"
			}, {
				"key" : "phy",
				"name" : "����",
				"value" : "1"
			}
		],
		"TWeaponHand" : [{
				"key" : "left",
				"name" : "����",
				"value" : 0
			}, {
				"key" : "right",
				"name" : "����",
				"value" : 1
			}
		]
	},
	"unit" : {
		"ULevelUp" : {
			"level" : {
				"name" : "�ȼ�",
				"type" : {
					"name" : "int"
				},
				"editor" : "numberbox",
				"comment" : "�ȼ�"
			},
			"buff" : {
				"name" : "����buff",
				"type" : {
					"name" : "object",
					"index" : "BUFF"
				},
				"editor" : "objectselect",
				"comment" : "����buff"
			},
			"money" : {
				"name" : "������Ǯ",
				"type" : {
					"name" : "int"
				},
				"editor" : "numberBox",
				"comment" : "��ǰһ��������������Ҫ�Ľ�Ǯ"
			},
			"effect_explain" : {
				"name" : "Ч��˵��",
				"type" : {
					"name" : "string"
				},
				"editor" : "text",
				"comment" : "Ч��˵��"
			}
		},
		"aroundBox" : {
			"width" : {
				"name" : "��Χ��-��(����)",
				"type" : {
					"name" : "int",
					"init" : "32"
				},
				"editor" : "numberbox",
				"comment" : "����-��Χ��-��(����) 32����Ϊ1��"
			},
			"height" : {
				"name" : "��Χ��-�ߣ�����)",
				"type" : {
					"name" : "int",
					"init" : "32"
				},
				"editor" : "numberbox",
				"comment" : "����-��Χ��-��(����) 32����Ϊ1��"
			}

		}
	}
}
