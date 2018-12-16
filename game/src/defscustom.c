/*
MIT License

Copyright (c) 2018 Antonio "toneddu2000" Latronico

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//sound prop
const	float	SOUND_ATTENUATION_DEFAULT = 1;
//crumb
const	float	CRUMB_TOTAL = 50;
.entity			crumbFirstEnt,crumbLastEnt,crumbActual,crumbAttached[CRUMB_TOTAL];
.entity			crumbPrevious,crumbNext,crumbParent;
.float			crumbFollow;
.float			crumbFirst,crumbLast;
.vector			crumbFirstOrg;
//comp
.float			compLightRadius;
.vector			compLightColor;
//ent
.float			entHealth,entCanBeDamaged,entSpeedChase,entSpeedPatrol;
.float			entAttackDamageCurrent;
.float			entInjured,entProjLife,entProjVelocity;
.float			entLightRadius;
.vector			entSightHeight,entSightOrg,entMeleeOrg,entOngroundOrg,entSizeMin,entSizeMax;
.string			entSoundAwake,entSoundPatrol,entSoundInjured,entSoundDead,entSoundAttackNear,entSoundAttackFar;
.string			entProjectileModel;
//ai
.float			aiState,aiAwake,aiPlayerDist,aiAttackNearDamage,aiAttackFarDamage,aiAttackNearOnly;
const	float 	AI_STATE_NULL = 0;
const	float 	AI_STATE_IDLE = 1;
const	float 	AI_STATE_PATROL = 2;
const	float	AI_STATE_CHASE = 3;
const	float	AI_STATE_ATTACKFAR = 4;
const	float	AI_STATE_ATTACKNEAR = 5;
const	float	AI_STATE_INJURED = 6;
const	float	AI_STATE_DEAD = 7;
const	float	AI_STATE_ATTACKFARWAIT = 8;
const	float	AI_PATROL_RADIUS = 900;
const	float	AI_AWAKE_RADIUS = 400;	
const	float	AI_CHASE_DISTANCE = 700;
const	float	AI_ATTACKFAR_DISTANCE = 700;
const	float	AI_ATTACKNEAR_DISTANCE = 120;	
//game
entity			gameDelayer;
float			gameState,gameFileFound;
.float			gameClass;
float			gameCanStart;

const	float 	GAME_DELAYER_TIME = 1.5;
const	float 	GAME_FRAMESPERSEC = 10;
const	float	GAME_FRAMEINCREMENT = 1;
const	float 	GAME_THINK_REFRESH = 0.1;
const	float 	GAME_LEVEL_LOADING_TIME = 1.5;
const float 	GAME_STATE_INITFIRST = 0;
const float 	GAME_STATE_MENU = 1;
const float 	GAME_STATE_PRERUNNING = 2;
const float 	GAME_STATE_RUNNING = 3;
const float 	GAME_STATE_PAUSED = 4;
const float 	GAME_STATE_WIN = 5;
const float 	GAME_STATE_LOSE = 6;
const float 	GAME_STATE_TIMEUP = 7;
const float 	GAME_STATE_CHANGELEVEL = 8;
const float 	GAME_STATE_ED = 9;
const float 	GAME_STATE_MULTI_CONNECTING = 10;
const float 	GAME_STATE_MULTI_CONNECTED = 12;
const float 	GAME_STATE_MULTI_REFUSED = 13;
const float 	GAME_STATE_MULTI_DISCONNECTING = 14;
const float 	GAME_STATE_MULTI_DISCONNECTED = 15;
//player
entity			player;
const	float	PLAYER_HEALTH_MAX = 100;
//camera
entity			camera;
float			cameraSpeed;
vector			cameraAttachedOrg;
const 	float	CAMERA_SPEED_INIT=0.2,CAMERA_SPEED_INCREMENT=0.005,CAMERA_SPEED_MAX=2,CAMERA_SPEED_MIN=0.001;
//anim
float			animTimelinePercentage,animTimelineWidth,animTimelineDuration;
.float			animMix,animMixTime;
.float			animIdleTime,animIdleEndFrame;
const float		ANIM_TOTAL = 10;
const float		ANIM_EV_OFFSET = 0.08;
.float 			animEvTime[ANIM_TOTAL];
.float			animTime[ANIM_TOTAL],animLoop[ANIM_TOTAL];
.string			animEvName[ANIM_TOTAL];
//animtest
.float			animTestLoop,animTestDuration;
//ui
entity			uiElScreen,uiElHeader,uiElButHeadSel,uiElButHeadMove,uiElButHeadRot,uiElButHeadMesh,uiElButHeadChar;
entity			uiElButHeadCrumb,uiElButHeadSave,uiElButHeadLoad,uiElButHeadLayer,uiElButHeadSelByType,uiElButHeadPrefab,uiElButHeadTimeline;
entity			uiElWinPropMesh,uiElButMeshFolderUp,uiElButMeshFolderDown,uiElButMeshCatUp,uiElButMeshCatDown,uiElButMeshIncr,uiElButMeshDecr,uiElButMeshPlace;
entity			uiElListLevel,uiElListLayer,uiElListPrefab,uiElListTimelineMeshes,uiElListEntFuncs;
entity			uiElWinPropTime,uiElButTimeClose,uiElButTimeFrmIncr,uiElButTimeFrmDecr,uiElButTimeSpeedIncr,uiElButTimeSpeedDecr;
entity			uiElButLayerToggle,uiElButLayerAddObj,uiElListSelByType,uiElWinLevOverwrite,uiElLblLevOverwrite,uiElButLevOverwrite,uiElButLevOverwriteExit;
string			uiPanelMeshArray[100],uiMeshCategoriesArray[15],uiMeshFoldersArray[15],uiMeshFolderSelected;
entity			uiPanelMeshModel,uiTimelineModel;
float			uiWarningTime,uiMessageTime,uiWarningAlpha,uiMessageAlpha,uiMessageMode,uiMeshCategoriesTotal,uiMeshCategoriesIndex;
float			uiTimeline,uiTimelineMenu,uiTimelineTime,uiTimelineSpeed,uiTimelinePlay,uiTimelineEntIndex,uiTimelineFrameIndex;
float			uiPanelMesh,uiMeshFoldersIndex,uiMeshFoldersTotal,uiPanelMeshIndex,uiPanelEntFuncs;
string			uiWarningText,uiLoadingText,uiMessageText,uiMessageBigText,uiListText,uiTimelineFunc;
const	vector	UI_FONT_TINY = [4,4,0];
const	vector	UI_FONT_SMALL = [7,7,0];
const	vector	UI_FONT_MEDIUM = [10,10,0];
const	vector	UI_FONT_MEDIUM2 = [12,12,12];
const	vector	UI_FONT_BIG = [15,15,0];
const	vector	UI_FONT_HUGE = [22,22,0];
const	vector	UI_HEAD_COLOR = [35/255, 39/255, 48/255];
const	vector	UI_WINPROP_COLOR = [60/255, 60/255, 60/255];
const	vector	UI_WINPROP_SIZE = [400,400,0];
const	vector	UI_WINPROP_COORD = [0,20,0];
const	vector	UI_HEADBUT_COLOR = [1,1,1];
const	vector	UI_BUTHEAD_COORD = [8,0,0];
const	vector	UI_HEADPROP_COLOR = [1,1,1];
const	vector	UI_PREVIEWMODELWIN_COORD = [0,90,0];
const	vector	UI_PREVIEWMODELWIN_SIZE = [200,200,0];
const	vector	UI_POPUP_COORD = [20,20,0];
const	vector	UI_POPUP_COLOR_BG_BORDER = [1,1,1];
const	vector	UI_POPUP_COLOR_BG = UI_WINPROP_COLOR;
const	vector	UI_TIMELINEWIN_COORD = [10,150,0];
const	vector	UI_HOVER_COLOR = [1,1,1];
const	vector	UI_BRIGHT_COLOR = [36/255,43/255,53/255];
const	vector	UI_DARK_COLOR = [22/255,24/255,31/255];
const	vector	UI_DARKER_COLOR = [8/255,9/255,11/255];
const	vector	UI_COLOR_GRAY = [60/255,60/255,60/255];
const	vector	UI_COLOR_WHITE = [205/255,205/255,205/255];
const	float	UI_VIS_NULL = 0;
const	float	UI_VIS_PROPMESH = 1;
const	float	UI_VIS_PROPCOLL = 2;
const	float	UI_VIS_LEVELLOAD = 3;
const	float	UI_VIS_LAYER = 4;
const	float	UI_VIS_SELBYTYPE = 5;
const	float	UI_VIS_LEVELOVERWRITE = 6;
const	float	UI_VIS_PREFAB = 7;
const	float	UI_VIS_TIMELINE = 8;
const	float	UI_VIS_TIMELINEMENU = 9;
const	float	UI_VIS_VC = 10;
const	float	UI_VIS_MENU = 11;
const	float	UI_VIS_ED_LAYOUT = 12;
const	float	UI_VIS_ENTFUNCS = 13;
const	float	UI_HEADER_HEIGHT = 18;
const	float	UI_HEADER_SAFEZONE = UI_HEADER_HEIGHT * 4;
const	float	UI_LIST_ELEM_TOTAL = 40;
const	string	UI_BUT_IMG_SEL = "textures/ed/select.tga";
const	string	UI_BUT_IMG_MOVE = "textures/ed/move.tga";
const	string	UI_BUT_IMG_ROT = "textures/ed/rotate.tga";
const	string	UI_BUT_IMG_MESH = "textures/ed/mesh.tga";
const	string	UI_BUT_IMG_CHAR = "textures/ed/char.tga";
const	string	UI_BUT_IMG_ITEM = "textures/ed/item.tga";
const	string	UI_BUT_IMG_CRUMB = "textures/ed/crumb.tga";
const	string	UI_BUT_IMG_MODECOLL = "textures/ed/modecol.tga";
const	string	UI_BUT_IMG_ARWLEFT = "textures/ed/arwleft.tga";
const	string	UI_BUT_IMG_ARWRIGHT = "textures/ed/arwright.tga";
const	string	UI_BUT_IMG_DBARWLEFT = "textures/ed/dbarwleft.tga";
const	string	UI_BUT_IMG_DBARWRIGHT = "textures/ed/dbarwright.tga";
const	string	UI_BUT_IMG_FOLDUP = "textures/ed/folderup.tga";
const	string	UI_BUT_IMG_FOLDDOWN = "textures/ed/folderdown.tga";
const	string	UI_BUT_IMG_LINKCOLL = "textures/ed/linkcoll.tga";
const	string	UI_BUT_IMG_CLOSE = "textures/ed/close.tga";
const	string	UI_BUT_IMG_SAVE = "textures/ed/save.tga";
const	string	UI_BUT_IMG_LOAD = "textures/ed/load.tga";
const	string	UI_BUT_IMG_LAYER = "textures/ed/layer.tga";
const	string	UI_BUT_IMG_LAYERTOGGLE = "textures/ed/layertoggle.tga";
const	string	UI_BUT_IMG_LAYERADDOBJ = "textures/ed/layeraddobj.tga";
const	string	UI_BUT_IMG_SELBYTYPE = "textures/ed/selectbytype.tga";
const	string	UI_BUT_IMG_PREFAB = "textures/ed/prefab.tga";
const	string	UI_BUT_IMG_TIMELINE = "textures/ed/timeline.tga";
//cui
entity			cuiEntity,cuiListDown,cuiListUp,cuiListOk,cuiListCancel,cuiListCtrlbar;
.entity			cuiParent,cuiChildLsUp,cuiChildLsDown,cuiChildLsOk,cuiChildLsCancel,cuiChildLsCtrlbar;
.vector			cuiCoords,cuiDim,cuiBgCol,cuiBgColOld,cuiTextCol,cuiTextDim,cuiListTextCol,cuiListBarCol;
.float			cuiClass,cuiVis,cuiAlpha,cuiAlphaOld,cuiClicked,cuiActive,cuiListIndex,cuiListTextIndex,cuiListBarPosY,cuiListBarHeight,cuiListTotal;
.float			cuiListCanGoDown,cuiListCanGoUp,cuiListMargin;
.string			cuiBgImg,cuiLabel,cuiListTextArray[UI_LIST_ELEM_TOTAL];
const float		CUI_CLASS_ROOT = 0;
const float		CUI_CLASS_WINDOW = 1;
const float		CUI_CLASS_BUTTON = 2;
const float		CUI_CLASS_LIST = 3;
const float		CUI_CLASS_LABEL = 4;
const float		CUI_CLASS_LISTARROWUP = 4;
const float		CUI_CLASS_LISTARROWDOWN = 5;
const float		CUI_CLASS_LISTOK = 6;
const float		CUI_CLASS_LISTCANCEL = 7;
const float		CUI_BUTTON_MENU = 1;
const float		CUI_BUTTON_HEAD = 2;
const float		CUI_BUTTON_PROP = 3;
const float		CUI_BUTTON_LIST_PROP = 4;
.void() 		cuiOnRelease;
//menu
entity			menuButNewGame,menuButEditor;
//input
float			inputImpulses,inputFireButton,inputCtrlPressed,inputShiftPressed,inputMouse1Pressed,inputMouse3Pressed;
float			inputCursor,inputCursorDeltaOld,inputGetScan,inputMove,inputCursorDir,inputCursorMoveTime,inputCursorMoveBlock;
vector			inputCursorOrigin,inputCursorDelta,inputCursor3dOrg,inputTemp3dOrg;
//physics
.float			physicsOnGround,physicsFallFrac,physicsForwardFrac;
.vector			physicsStepOrg;
//weap
entity			weap,weapProjectile;
float			weapShot,weapFireTime;
vector			weapTraceOrg;
.entity			weapParent;
.float			weapNumber,weapProjLife,weapProjVelocity;
//ed
entity			edEntity,edEntitySearch,edRotPivot;
string			edShaderStored,edMeshStored,edMeshesFolder,edCursorImg;
float			edElevation,edGrid,edMode,edPlayerPlaced,edLayerOpen,edSelByTypeOpen,edPrefabOpen;
float			edGroupIndex;
.entity			edCollisionParent;
.float			edSelectable,edSelected,edPlaceable,edSolidOld,edGroupedIndex,edLayer;
.float			edSelectedByType,edLayerActive;
.vector			edPlacedOrg,edPlacedAngles;
.string			edShader;
const	float	ED_GRID_SIZE = 4096;
const	float	ED_GRID_16=0;
const	float	ED_GRID_32=1;
const	float	ED_GRID_64=2;
const	float	ED_GRID_128=3;
const	float	ED_GRID_256=4;
const	float	ED_GRID_512=5;
const	float	ED_GRID_1024=6;
const	float	ED_GRID_2048=7;
const	float	ED_GROUND_MARGIN = 32;	
const	float	ED_MODE_SELECT = 0;
const	float	ED_MODE_MOVE = 1;
const	float	ED_MODE_ROTATE = 2;
const	float	ED_MODE_MESH = 3;
const	float	ED_MODE_ENT = 4;
const	float	ED_MODE_ITEM = 5;
const	float	ED_MODE_CRUMB = 6;
const	float	ED_MODE_COLLISION = 7;
const	float	ED_TOTAL_SELECTED = 10;
const	float	ED_ROTATE_INCREMENT = 45;
const	vector	ED_PLACE_FIXORG = [0,0,0];
const	vector	ED_PLACE_CHAR_FIXORG = [0,0,64];
entity			edSelectedArray[ED_TOTAL_SELECTED],edLayerArray[ED_TOTAL_SELECTED];
vector			edMoveOffset[ED_TOTAL_SELECTED];
.entity			edCollisionChildren[ED_TOTAL_SELECTED],edGroupedEnt[ED_TOTAL_SELECTED];
.vector			edParentOffset[ED_TOTAL_SELECTED];
string			edLayerNameArray[ED_TOTAL_SELECTED];
//sound
.float 			soundWeaponUsed,soundInjuredUsed,soundDeadUsed,soundAwakeUsed;
const	float	SOUND_IDLE = 0;
const	float	SOUND_AWAKE = 1;
const	float	SOUND_ATTACKNEAR = 2;
const	float	SOUND_ATTACKFAR = 3;
const	float	SOUND_INJURED = 4;
const	float	SOUND_DEAD = 5;
const	float	SOUND_ITEM_VOLUME = 0.6;
const	float	SOUND_ITEM_ATTENUATION = 0.8;
//render
entity			renderEntity;
float			renderSelectedShader,renderShadingToggle;
const	float 	RENDER_MASK_PREVIEWMODEL = 4;
//view
float			viewTop,viewTopZoom;
//bsp
entity			bspEntity;
float			bspLoaded;
//level
entity			levelEntity;
float			levelSave,levelNew,levelOpen,levelOverwrite;
string			levelOverwriteName;
.float			levelSaveThis;
//ent
const	float	ENT_CLASS_NULL = 0;
const	float	ENT_CLASS_PLAYER = 1;
const	float	ENT_CLASS_NPC = 2;
const	float	ENT_CLASS_WEAP = 3;
const	float	ENT_CLASS_ITEM = 4;
const	float	ENT_CLASS_MESH = 5;
const	float	ENT_CLASS_MESHCOLLISION = 6;
const	float	ENT_CLASS_GROUP = 7;
const	float	ENT_CLASS_PREFAB = 8;
const	float	ENT_CLASS_PROJECTILE = 9;
const	float	ENT_CLASS_CRUMB = 10;
const	float	ENT_CLASS_VC = 11;
const	float	ENT_CLASS_BLANK = 12;
const	float	ENT_CLASS_SCRIPTED = 13;
//skel
.float			skelEnabled;
//part
.string			partName;
//fx
float			fxInjuredTime,fxGlslTimer,fxPostprocessColor,fxPostprocessDepth;
string			fxName;
//debug
float			debugTraceFracFall,debugTraceFracForward;
vector			debugTraceStepOrg;
