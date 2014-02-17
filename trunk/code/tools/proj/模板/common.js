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
				"name" : "无",
				"value" : 0
			}, {
				"key" : "true",
				"name" : "是",
				"value" : 1
			}, {
				"key" : "false",
				"name" : "否",
				"value" : 2
			}
		],
		"TBuffEffectType" : [{
				"key" : "NULL",
				"name" : "无",
				"value" : 0
			}, {
				"key" : "reduceSpeed",
				"name" : "减速",
				"value" : 1
			}, {
				"key" : "frozen",
				"name" : "冰冻",
				"value" : 2
			}, {
				"key" : "attack",
				"name" : "攻击力",
				"value" : 3
			}, {
				"key" : "defence",
				"name" : "防御力",
				"value" : 4
			}, {
				"key" : "addHp",
				"name" : "恢复hp",
				"value" : 5
			}, {
				"key" : "addPower",
				"name" : "恢复能量",
				"value" : 6
			}, {
				"key" : "changeHpOfTimer",
				"name" : "持续影响生命",
				"value" : 7
			}, {
				"key" : "addMaxHP",
				"name" : "生命上限",
				"value" : 8
			}, {
				"key" : "addMaxPower",
				"name" : "能量上限",
				"value" : 9
			}, {
				"key" : "damageScript",
				"name" : "伤害脚本",
				"value" : 10
			}
			, {
				"key" : "addAirDamage",
				"name" : "增加对空伤害",
				"value" : 11
			}
			, {
				"key" : "addLandDamage",
				"name" : "增加对地伤害",
				"value" : 12
			}
		],
		"TValuetype" : [{
				"key" : "NULL",
				"name" : "无",
				"value" : 0
			}, {
				"key" : "value1",
				"name" : "数值（可填负数）",
				"value" : 1
			}, {
				"key" : "percent1",
				"name" : "百分比",
				"value" : 2
			}
		],
		"TRange" : [{
				"key" : "NULL",
				"name" : "无",
				"value" : 0
			}, {
				"key" : "circular",
				"name" : "圆形",
				"value" : 1
			}, {
				"key" : "sector",
				"name" : "扇形",
				"value" : 2
			}, {
				"key" : "rectangle",
				"name" : "矩形",
				"value" : 3
			}
		],
		"TOrbit" : [{
				"key" : "NULL",
				"name" : "无",
				"value" : 0
			}, {
				"key" : "line",
				"name" : "直线",
				"value" : 1
			}, {
				"key" : "parabola",
				"name" : "抛物线",
				"value" : 2
			}, {
				"key" : "bezier",
				"name" : "贝塞尔曲线",
				"value" : 3
			}
		],
		"TDeadType" : [{
				"key" : "animate",
				"name" : "动画",
				"value" : "0"
			}, {
				"key" : "phy",
				"name" : "物理",
				"value" : "1"
			}
		],
		"TWeaponHand" : [{
				"key" : "left",
				"name" : "左手",
				"value" : 0
			}, {
				"key" : "right",
				"name" : "右手",
				"value" : 1
			}
		]
	},
	"unit" : {
		"ULevelUp" : {
			"level" : {
				"name" : "等级",
				"type" : {
					"name" : "int"
				},
				"editor" : "numberbox",
				"comment" : "等级"
			},
			"buff" : {
				"name" : "调用buff",
				"type" : {
					"name" : "object",
					"index" : "BUFF"
				},
				"editor" : "objectselect",
				"comment" : "调用buff"
			},
			"money" : {
				"name" : "升级金钱",
				"type" : {
					"name" : "int"
				},
				"editor" : "numberBox",
				"comment" : "从前一级升到本级别需要的金钱"
			},
			"effect_explain" : {
				"name" : "效果说明",
				"type" : {
					"name" : "string"
				},
				"editor" : "text",
				"comment" : "效果说明"
			}
		},
		"aroundBox" : {
			"width" : {
				"name" : "包围框-宽(像素)",
				"type" : {
					"name" : "int",
					"init" : "32"
				},
				"editor" : "numberbox",
				"comment" : "物理-包围框-宽(像素) 32像素为1米"
			},
			"height" : {
				"name" : "包围框-高（像素)",
				"type" : {
					"name" : "int",
					"init" : "32"
				},
				"editor" : "numberbox",
				"comment" : "物理-包围框-高(像素) 32像素为1米"
			}

		}
	}
}
