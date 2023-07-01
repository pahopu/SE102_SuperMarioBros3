#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO									0
#define ID_TEX_ENEMY									10
#define ID_TEX_MISC										20


#define OBJECT_TYPE_MARIO								0
#define OBJECT_TYPE_BRICK								1
#define OBJECT_TYPE_GOOMBA								2
#define OBJECT_TYPE_KOOPA_TROOPA						3
#define OBJECT_TYPE_COIN								4
#define OBJECT_TYPE_PLATFORM							5
#define OBJECT_TYPE_PIRANHA_PLANT						6
#define OBJECT_TYPE_INVISIBLE_OBJECT					7
#define OBJECT_TYPE_TELEPORT							8
#define OBJECT_TYPE_PLATFORM_ANIMATE					9

#define OBJECT_TYPE_PORTAL								50


#pragma region MARIO 

#define ID_SPRITE_MARIO									10000

#define ID_SPRITE_MARIO_DIE								(ID_SPRITE_MARIO + 1000)

#define ID_SPRITE_MARIO_SMALL							(ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE						(ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT					(ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT				(ID_SPRITE_MARIO_SMALL_IDLE + 20)
#define ID_SPRITE_MARIO_SMALL_IDLE_FRONT				(ID_SPRITE_MARIO_SMALL_IDLE + 30)

#define ID_SPRITE_MARIO_SMALL_WALKING					(ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT				(ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT				(ID_SPRITE_MARIO_SMALL_WALKING + 20)

#define ID_SPRITE_MARIO_SMALL_RUNNING					(ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT				(ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT				(ID_SPRITE_MARIO_SMALL_RUNNING + 20)

#define ID_SPRITE_MARIO_SMALL_JUMP						(ID_SPRITE_MARIO_SMALL + 400)

#define ID_SPRITE_MARIO_SMALL_JUMP_WALK					(ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT			(ID_SPRITE_MARIO_SMALL_JUMP_WALK + 1)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT			(ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)

#define ID_SPRITE_MARIO_SMALL_JUMP_RUN					(ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT				(ID_SPRITE_MARIO_SMALL_JUMP_RUN + 1)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT			(ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)

#define ID_SPRITE_MARIO_SMALL_BRACE						(ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT				(ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT				(ID_SPRITE_MARIO_SMALL_BRACE + 20)

#define ID_SPRITE_MARIO_SMALL_KICK						(ID_SPRITE_MARIO_SMALL + 600)
#define ID_SPRITE_MARIO_SMALL_KICK_LEFT					(ID_SPRITE_MARIO_SMALL_KICK + 10)
#define ID_SPRITE_MARIO_SMALL_KICK_RIGHT				(ID_SPRITE_MARIO_SMALL_KICK + 20)

#define ID_SPRITE_MARIO_SMALL_GET_INTO_PIPE				(ID_SPRITE_MARIO_BIG + 800)

#define ID_SPRITE_MARIO_BIG								(ID_SPRITE_MARIO + 3000)
#define ID_SPRITE_MARIO_BIG_IDLE						(ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT					(ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT					(ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING						(ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT				(ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT				(ID_SPRITE_MARIO_BIG_WALKING + 20)

#define ID_SPRITE_MARIO_BIG_RUNNING						(ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT				(ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT				(ID_SPRITE_MARIO_BIG_RUNNING + 20)

#define ID_SPRITE_MARIO_BIG_JUMP						(ID_SPRITE_MARIO_BIG + 400)

#define ID_SPRITE_MARIO_BIG_JUMP_WALK					(ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT				(ID_SPRITE_MARIO_BIG_JUMP_WALK + 1)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT				(ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)

#define ID_SPRITE_MARIO_BIG_JUMP_RUN					(ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT				(ID_SPRITE_MARIO_BIG_JUMP_RUN + 1)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT				(ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)

#define ID_SPRITE_MARIO_BIG_SIT							(ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT					(ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT					(ID_SPRITE_MARIO_BIG_SIT + 20)

#define ID_SPRITE_MARIO_BIG_BRACE						(ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT					(ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT					(ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_BIG_KICK						(ID_SPRITE_MARIO_BIG + 700)
#define ID_SPRITE_MARIO_BIG_KICK_LEFT					(ID_SPRITE_MARIO_BIG_KICK + 10)
#define ID_SPRITE_MARIO_BIG_KICK_RIGHT					(ID_SPRITE_MARIO_BIG_KICK + 20)

#define ID_SPRITE_MARIO_BIG_GET_INTO_PIPE				(ID_SPRITE_MARIO_BIG + 900)

#define ID_SPRITE_MARIO_RACOON							(ID_SPRITE_MARIO + 4000)
#define ID_SPRITE_MARIO_RACOON_IDLE						(ID_SPRITE_MARIO_RACOON + 100)
#define ID_SPRITE_MARIO_RACOON_IDLE_LEFT				(ID_SPRITE_MARIO_RACOON_IDLE + 10)
#define ID_SPRITE_MARIO_RACOON_IDLE_RIGHT				(ID_SPRITE_MARIO_RACOON_IDLE + 20)

#define ID_SPRITE_MARIO_RACOON_WALKING					(ID_SPRITE_MARIO_RACOON + 200)
#define ID_SPRITE_MARIO_RACOON_WALKING_LEFT				(ID_SPRITE_MARIO_RACOON_WALKING + 10)
#define ID_SPRITE_MARIO_RACOON_WALKING_RIGHT			(ID_SPRITE_MARIO_RACOON_WALKING + 20)

#define ID_SPRITE_MARIO_RACOON_RUNNING					(ID_SPRITE_MARIO_RACOON + 300)
#define ID_SPRITE_MARIO_RACOON_RUNNING_LEFT				(ID_SPRITE_MARIO_RACOON_RUNNING + 10)
#define ID_SPRITE_MARIO_RACOON_RUNNING_RIGHT			(ID_SPRITE_MARIO_RACOON_RUNNING + 20)

#define ID_SPRITE_MARIO_RACOON_JUMP						(ID_SPRITE_MARIO_RACOON + 400)

#define ID_SPRITE_MARIO_RACOON_JUMP_WALK				(ID_SPRITE_MARIO_RACOON_JUMP + 10)
#define ID_SPRITE_MARIO_RACOON_JUMP_WALK_LEFT			(ID_SPRITE_MARIO_RACOON_JUMP_WALK + 1)
#define ID_SPRITE_MARIO_RACOON_JUMP_WALK_RIGHT			(ID_SPRITE_MARIO_RACOON_JUMP_WALK + 2)

#define ID_SPRITE_MARIO_RACOON_JUMP_RUN					(ID_SPRITE_MARIO_RACOON_JUMP + 20)
#define ID_SPRITE_MARIO_RACOON_JUMP_RUN_LEFT			(ID_SPRITE_MARIO_RACOON_JUMP_RUN + 1)
#define ID_SPRITE_MARIO_RACOON_JUMP_RUN_RIGHT			(ID_SPRITE_MARIO_RACOON_JUMP_RUN + 4)

#define ID_SPRITE_MARIO_RACOON_SIT						(ID_SPRITE_MARIO_RACOON + 500)
#define ID_SPRITE_MARIO_RACOON_SIT_LEFT					(ID_SPRITE_MARIO_RACOON_SIT + 10)
#define ID_SPRITE_MARIO_RACOON_SIT_RIGHT				(ID_SPRITE_MARIO_RACOON_SIT + 20)

#define ID_SPRITE_MARIO_RACOON_BRACE					(ID_SPRITE_MARIO_RACOON + 600)
#define ID_SPRITE_MARIO_RACOON_BRACE_LEFT				(ID_SPRITE_MARIO_RACOON_BRACE + 10)
#define ID_SPRITE_MARIO_RACOON_BRACE_RIGHT				(ID_SPRITE_MARIO_RACOON_BRACE + 20)

#define ID_SPRITE_MARIO_RACOON_KICK						(ID_SPRITE_MARIO_RACOON + 700)
#define ID_SPRITE_MARIO_RACOON_KICK_LEFT				(ID_SPRITE_MARIO_RACOON_KICK + 10)
#define ID_SPRITE_MARIO_RACOON_KICK_RIGHT				(ID_SPRITE_MARIO_RACOON_KICK + 20)

#define ID_SPRITE_MARIO_RACOON_FLOAT					(ID_SPRITE_MARIO_RACOON + 900)
#define ID_SPRITE_MARIO_RACOON_FLOAT_LEFT				(ID_SPRITE_MARIO_RACOON_FLOAT + 21)
#define ID_SPRITE_MARIO_RACOON_FLOAT_RIGHT				(ID_SPRITE_MARIO_RACOON_FLOAT + 23)

#define ID_SPRITE_MARIO_RACOON_GET_INTO_PIPE			(ID_SPRITE_MARIO_RACOON_IDLE + 31)

#pragma endregion 


#define ID_SPRITE_BRICK									20000


#define ID_SPRITE_GOOMBA								30000
#define ID_SPRITE_GOOMBA_WALK							(ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE							(ID_SPRITE_GOOMBA + 2000)


#define ID_SPRITE_COIN									40000


#define ID_SPRITE_CLOUD									50000
#define ID_SPRITE_CLOUD_BEGIN							(ID_SPRITE_CLOUD + 1000)
#define ID_SPRITE_CLOUD_MIDDLE							(ID_SPRITE_CLOUD + 2000)
#define ID_SPRITE_CLOUD_END								(ID_SPRITE_CLOUD + 3000)


#define ID_SPRITE_MUSHROOM								60000
#define ID_SPRITE_MUSHROOM_SUPER						(ID_SPRITE_MUSHROOM + 1000)
#define ID_SPRITE_MUSHROOM_1UP							(ID_SPRITE_MUSHROOM + 2000)
#define ID_SPRITE_SUPER_LEAF_LEFT						(ID_SPRITE_MUSHROOM + 3000)
#define ID_SPRITE_SUPER_LEAF_RIGHT						(ID_SPRITE_MUSHROOM + 3100)

#define ID_SPRITE_KOOPA_TROOPA							70000

#define ID_SPRITE_GREEN_KOOPA_TROOPA					(ID_SPRITE_KOOPA_TROOPA + 1000)

#define ID_SPRITE_GREEN_KOOPA_TROOPA_WALK				(ID_SPRITE_GREEN_KOOPA_TROOPA + 100)
#define ID_SPRITE_GREEN_KOOPA_TROOPA_WALK_LEFT			(ID_SPRITE_GREEN_KOOPA_TROOPA_WALK + 10)
#define ID_SPRITE_GREEN_KOOPA_TROOPA_WALK_RIGHT			(ID_SPRITE_GREEN_KOOPA_TROOPA_WALK + 20)

#define ID_SPRITE_GREEN_KOOPA_TROOPA_SHELL				(ID_SPRITE_GREEN_KOOPA_TROOPA + 200)
#define ID_SPRITE_GREEN_KOOPA_TROOPA_SHELL_UP			(ID_SPRITE_GREEN_KOOPA_TROOPA_SHELL + 10)
#define ID_SPRITE_GREEN_KOOPA_TROOPA_SHELL_DOWN			(ID_SPRITE_GREEN_KOOPA_TROOPA_SHELL + 20)

#define ID_SPRITE_RED_KOOPA_TROOPA						(ID_SPRITE_KOOPA_TROOPA + 2000)

#define ID_SPRITE_RED_KOOPA_TROOPA_WALK					(ID_SPRITE_RED_KOOPA_TROOPA + 100)
#define ID_SPRITE_RED_KOOPA_TROOPA_WALK_LEFT			(ID_SPRITE_RED_KOOPA_TROOPA_WALK + 10)
#define ID_SPRITE_RED_KOOPA_TROOPA_WALK_RIGHT			(ID_SPRITE_RED_KOOPA_TROOPA_WALK + 20)

#define ID_SPRITE_RED_KOOPA_TROOPA_SHELL				(ID_SPRITE_RED_KOOPA_TROOPA + 200)
#define ID_SPRITE_RED_KOOPA_TROOPA_SHELL_UP				(ID_SPRITE_RED_KOOPA_TROOPA_SHELL + 10)
#define ID_SPRITE_RED_KOOPA_TROOPA_SHELL_DOWN			(ID_SPRITE_RED_KOOPA_TROOPA_SHELL + 20)

#define ID_SPRITE_GREEN_PARA_KOOPA_TROOPA				(ID_SPRITE_KOOPA_TROOPA + 3000)

#define ID_SPRITE_GREEN_PARA_KOOPA_TROOPA_FLY			(ID_SPRITE_GREEN_PARA_KOOPA_TROOPA + 100)
#define ID_SPRITE_GREEN_PARA_KOOPA_TROOPA_FLY_LEFT		(ID_SPRITE_GREEN_PARA_KOOPA_TROOPA_FLY + 10)
#define ID_SPRITE_GREEN_PARA_KOOPA_TROOPA_FLY_RIGHT		(ID_SPRITE_GREEN_PARA_KOOPA_TROOPA_FLY + 20)


#define ID_SPRITE_PLANT									80000
#define ID_SPRITE_PIRANHA_PLANT							(ID_SPRITE_PLANT + 1000)
#define ID_SPRITE_PIPE									(ID_SPRITE_PLANT + 2000)
#define ID_SPRITE_BULLET								(ID_SPRITE_PLANT + 3000)

#define ID_SPRITE_PSWITCH								45000
#define ID_SPRITE_PSWITCH_ACTIVED						(ID_SPRITE_PSWITCH + 100)

#define ID_SPRITE_GIFT_BOX								55641
#define ID_SPRITE_GIFT_MUSHROOM							55651
#define ID_SPRITE_GIFT_FLOWER							55661
#define ID_SPRITE_GIFT_STAR								55671

#pragma region Effect

#define ID_SPRITE_TAIL_MARIO_ATTACK						55710
#define ID_SPRITE_BIG_MARIO_EAT_SUPERLEAF				55720

#define ID_ANI_BIG_MARIO_EATING_SUPERLEAF				9000
#define ID_ANI_TAIL_MARIO_ATTACKED_ENEMIES				9100

#pragma endregion


#pragma region HUD&FONT

////		HUD			////
#define ID_SPRITE_HUD									70000
#define ID_SPRITE_GIFT_BOX_BLUE							(ID_SPRITE_HUD + 1)

#define ID_SPRITE_SYMBOL_M								(ID_SPRITE_HUD + 10)
#define ID_SPRITE_SYMBOL_L								(ID_SPRITE_SYMBOL_M + 1)

#define ID_SPRITE_ARROW_WHITE							(ID_SPRITE_HUD + 20)
#define ID_SPRITE_ARROW_BLACK							(ID_SPRITE_ARROW_WHITE + 1)

#define ID_SPRITE_P_WHITE								(ID_SPRITE_ARROW_WHITE + 5)
#define ID_SPRITE_P_BLACK								(ID_SPRITE_ARROW_WHITE + 6)


////		FONT		////
#define ID_SPRITE_FONT									75000

#define ID_SPRITE_NUMBER								(ID_SPRITE_FONT + 100)
#define ID_SPRITE_NUMBER_0								(ID_SPRITE_NUMBER + 0)
#define ID_SPRITE_NUMBER_1								(ID_SPRITE_NUMBER + 1)
#define ID_SPRITE_NUMBER_2								(ID_SPRITE_NUMBER + 2)
#define ID_SPRITE_NUMBER_3								(ID_SPRITE_NUMBER + 3)
#define ID_SPRITE_NUMBER_4								(ID_SPRITE_NUMBER + 4)
#define ID_SPRITE_NUMBER_5								(ID_SPRITE_NUMBER + 5)
#define ID_SPRITE_NUMBER_6								(ID_SPRITE_NUMBER + 6)
#define ID_SPRITE_NUMBER_7								(ID_SPRITE_NUMBER + 7)
#define ID_SPRITE_NUMBER_8								(ID_SPRITE_NUMBER + 8)
#define ID_SPRITE_NUMBER_9								(ID_SPRITE_NUMBER + 9)

#define ID_SPRITE_POINTS								(ID_SPRITE_FONT + 200)
#define ID_SPRITE_POINTS_100							(ID_SPRITE_POINTS + 1)
#define ID_SPRITE_POINTS_200							(ID_SPRITE_POINTS + 2)
#define ID_SPRITE_POINTS_400							(ID_SPRITE_POINTS + 3)
#define ID_SPRITE_POINTS_800							(ID_SPRITE_POINTS + 4)
#define ID_SPRITE_POINTS_1000							(ID_SPRITE_POINTS + 5)
#define ID_SPRITE_POINTS_2000							(ID_SPRITE_POINTS + 6)
#define ID_SPRITE_POINTS_4000							(ID_SPRITE_POINTS + 7)
#define ID_SPRITE_POINTS_8000							(ID_SPRITE_POINTS + 8)
#define ID_SPRITE_POINTS_1UP							(ID_SPRITE_POINTS + 9)

#define ID_SPRITE_PAUSE									(ID_SPRITE_FONT + 300)

#pragma endregion

#pragma region World Map GrassLand

#define ID_SPRITE_WORLD_MAP								80000

#define ID_SPRITE_SYMBOL_START							(ID_SPRITE_WORLD_MAP + 0)

#define ID_SPRITE_SCENE									(ID_SPRITE_WORLD_MAP + 10)
#define ID_SPRITE_SCENE_1								(ID_SPRITE_SCENE + 0)
#define ID_SPRITE_SCENE_2								(ID_SPRITE_SCENE + 1)
#define ID_SPRITE_SCENE_3								(ID_SPRITE_SCENE + 2)
#define ID_SPRITE_SCENE_4								(ID_SPRITE_SCENE + 3)
#define ID_SPRITE_SCENE_5								(ID_SPRITE_SCENE + 4)
#define ID_SPRITE_SCENE_6								(ID_SPRITE_SCENE + 5)
#define ID_SPRITE_SCENE_7								(ID_SPRITE_SCENE + 6)
#define ID_SPRITE_SCENE_8								(ID_SPRITE_SCENE + 7)
#define ID_SPRITE_SCENE_9								(ID_SPRITE_SCENE + 8)
#define ID_SPRITE_SCENE_10								(ID_SPRITE_SCENE + 9)

#define ID_SPRITE_SYMBOL_ACE							(ID_SPRITE_WORLD_MAP + 20)
#define ID_SPRITE_GATE									(ID_SPRITE_SYMBOL_ACE + 1)
#define ID_SPRITE_DOOR									(ID_SPRITE_SYMBOL_ACE + 2)
#define ID_SPRITE_MUSHROOM_HOUSE						(ID_SPRITE_SYMBOL_ACE + 3)
#define ID_SPRITE_CASTLE_BODY							(ID_SPRITE_SYMBOL_ACE + 4)
#define ID_SPRITE_CASTLE_TOP							(ID_SPRITE_SYMBOL_ACE + 5)
#define ID_SPRITE_SYMBOL_HELP							(ID_SPRITE_SYMBOL_ACE + 6)

#define ID_SPRITE_PATH									(ID_SPRITE_WORLD_MAP + 30)
#define ID_SPRITE_PATH_HORIZONTAL						(ID_SPRITE_PATH + 0)
#define ID_SPRITE_PATH_VERTICAL							(ID_SPRITE_PATH + 1)
#define ID_SPRITE_SEED									(ID_SPRITE_PATH + 1)
#define ID_SPRITE_PATH_HORIZONTAL_WITH_SEED				(ID_SPRITE_PATH + 3)
#define ID_SPRITE_PATH_VERTICAL_WITH_SEED				(ID_SPRITE_PATH + 4)
#define ID_SPRITE_PATH_HORIZONTAL_VERTICAL_WITH_SEED	(ID_SPRITE_PATH + 5)

#define ID_SPRITE_MAP_BORDER							(ID_SPRITE_WORLD_MAP + 100)
#define ID_SPRITE_MAP_BORDER_TOP_LEFT					(ID_SPRITE_MAP_BORDER + 0)
#define ID_SPRITE_MAP_BORDER_TOP_MID					(ID_SPRITE_MAP_BORDER + 1)
#define ID_SPRITE_MAP_BORDER_TOP_RIGHT					(ID_SPRITE_MAP_BORDER + 2)
#define ID_SPRITE_MAP_BORDER_MID_LEFT					(ID_SPRITE_MAP_BORDER + 10)
#define ID_SPRITE_MAP_BORDER_MID_RIGHT					(ID_SPRITE_MAP_BORDER + 11)
#define ID_SPRITE_MAP_BORDER_BOT_LEFT					(ID_SPRITE_MAP_BORDER + 20)
#define ID_SPRITE_MAP_BORDER_BOT_MID					(ID_SPRITE_MAP_BORDER + 21)
#define ID_SPRITE_MAP_BORDER_BOT_RIGHT					(ID_SPRITE_MAP_BORDER + 22)

#define ID_SPRITE_BACKGROUND_COLOR						(ID_SPRITE_WORLD_MAP + 200)

#define ID_SPRITE_GRASS									(ID_SPRITE_WORLD_MAP + 300)
#define ID_SPRITE_GRASS_0								(ID_SPRITE_GRASS + 0)
#define ID_SPRITE_GRASS_1								(ID_SPRITE_GRASS + 1)
#define ID_SPRITE_GRASS_2								(ID_SPRITE_GRASS + 2)
#define ID_SPRITE_GRASS_3								(ID_SPRITE_GRASS + 3)
#define ID_ANI_GRASS_DANCING							20000

#define ID_SPRITE_MOUNTAIN								(ID_SPRITE_GRASS + 10)
#define ID_SPRITE_BRIDGE								(ID_SPRITE_GRASS + 20)

#define ID_SPRITE_DRAIN									(ID_SPRITE_WORLD_MAP + 400)
#define ID_SPRITE_DRAIN_TOP_0							(ID_SPRITE_DRAIN + 0)
#define ID_SPRITE_DRAIN_TOP_1							(ID_SPRITE_DRAIN + 1)
#define ID_SPRITE_DRAIN_TOP_2							(ID_SPRITE_DRAIN + 2)
#define ID_SPRITE_DRAIN_TOP_3							(ID_SPRITE_DRAIN + 3)
#define ID_SPRITE_DRAIN_MID1_0							(ID_SPRITE_DRAIN + 10)
#define ID_SPRITE_DRAIN_MID1_1							(ID_SPRITE_DRAIN + 11)
#define ID_SPRITE_DRAIN_MID1_2							(ID_SPRITE_DRAIN + 12)
#define ID_SPRITE_DRAIN_MID1_3							(ID_SPRITE_DRAIN + 13)
#define ID_SPRITE_DRAIN_MID2_0							(ID_SPRITE_DRAIN + 20)
#define ID_SPRITE_DRAIN_MID2_1							(ID_SPRITE_DRAIN + 21)
#define ID_SPRITE_DRAIN_MID2_2							(ID_SPRITE_DRAIN + 22)
#define ID_SPRITE_DRAIN_MID2_3							(ID_SPRITE_DRAIN + 23)
#define ID_SPRITE_DRAIN_BOT_0							(ID_SPRITE_DRAIN + 30)
#define ID_SPRITE_DRAIN_BOT_1							(ID_SPRITE_DRAIN + 31)
#define ID_SPRITE_DRAIN_BOT_2							(ID_SPRITE_DRAIN + 32)
#define ID_SPRITE_DRAIN_BOT_3							(ID_SPRITE_DRAIN + 33)

#pragma endregion