//gameglobals.h, resources for the game only
//resources: game

//include bitmap enums
#include "bitmaps.h"

/*	these are all configurable game settings for difficulty, etc. all
 * time units are in milliseconds. speeds are in pixels per frame 
 * ALL COORDS are double density!*/

//database information:

//number of bitmaps to preload
#define NUM_BMP_PRELOAD	56
//offset cuz map bmps are before
#define OFFSET_PRELOADBMP	4030	

//ui settings:

#define HEALTH_DIAMETER	56
#define DOUBLE_DENSITY	2

//gameplay/performance:

//play area of the gameplay in standard
#define GAMEPLAY_TOPLEFT_X	0
#define GAMEPLAY_TOPLEFT_Y	0
#define GAMEPLAY_EXTENT_X	320
#define GAMEPLAY_EXTENT_Y	320
//the framerate, will vary performance mostly in ms
//100 updates the screen every tenth of a second
#define DEFAULT_TIME_OUT	100
//exception that wont skip frame when it is a bit too late
#define TIME_EXCEPTION	20
//time when it is okay to delay process 
#define DEFAULT_MIN_DELAY_TIME	10
//rate to repeat key events
#define KEY_REPEAT_TIME	100
#define KEY_DELAY_REPEAT	100
//map segementing
#define MAP_SEGMENT_EXTENT_Y	1280
#define MAP_SEGMENT_EXTENT_X	320
//one and a half load time before mapWinoffset
#define MAP_SEGMENT_LOAD_Y_OFFSET	480
//pixels before end of the map when it starts to repeat itself
#define MAP_END_REPEAT_Y	640
#define MAP_END_START_REPEAT	2	

//player physics:

//number of default lives
#define DEFAULT_LIVES	3
//different strafe speeds
#define STRAFE_FIRST	2
#define STRAFE_NEXT	4			
#define STRAFE	6
//strafe min time
#define STRAFE_TIME_FIRST	0
#define STRAFE_TIME_NEXT	400			
#define STRAFE_TIME	700
//progress per tenth of a second to go in map(scrolls 40 pixels in a second)
#define MAP_DEFAULT_PROGRESS_Y	4
//the minimum y coord the user can move to
#define MAX_USER_Y_POS	200
//the time the user must wait to shoot again
#define MIN_SHOT_INTERVAL	200
//minimum y coord of rear mg fire
#define MIN_REAR_MG_Y	160
//health of different players
#define	HEALTH_spitfire	100
#define	HEALTH_hurricane	110
#define	HEALTH_p51d	150
#define	HEALTH_yak9	80
#define	HEALTH_b17	140
#define	HEALTH_bf109	100
#define	HEALTH_ju87	120
#define	HEALTH_me110	160
#define	HEALTH_fw190	150
#define	HEALTH_zero	110
#define HEALTH_me262	120
//start where user begins
#define USER_START_X	120
#define USER_START_Y	240

//bullet information:

//speeds of bullet categories
#define SPEED_ROCKET	4
#define SPEED_BULLET	6
#define SPEED_CANNON	3
//range of diff guns
#define RANGE_BULLET	400
#define RANGE_ROCKET	300
#define RANGE_CANNON	200
//damage of bullets
#define DAMAGE_MG_8MM
#define DAMAGE_MG_12MM
#define DAMAGE_MG_13MM
#define DAMAGE_MG_16MM
#define DAMAGE_CANNON_20MM
#define DAMAGE_CANNON_30MM
#define DAMAGE_CANNON_MGFF20MM
#define DAMAGE_ROCKET_21CM
//timeouts of different guns
#define TIMEOUT_MG_8MM
#define TIMEOUT_MG_12MM
#define TIMEOUT_MG_13MM
#define TIMEOUT_MG_16MM
#define TIMEOUT_CANNON_20MM
#define TIMEOUT_CANNON_30MM
#define TIMEOUT_CANNON_MGFF20MM
#define TIMEOUT_ROCKET_21CM
//time until bomb explodes
#define BOMB_TRIGGER_TIME	3000
//bomb speed
#define BOMB_SPEED	5
//bomb damages
#define BOMB_DAMAGE_200	50
#define BOMB_DAMAGE_500	100
#define BOMB_DAMAGE_1000	200

//ai information:

//shooting range of ai in pixels of standard coord system
#define SHOOTING_RANGE_MAX 	135
//difficulty shoot delay in milliseconds 
#define EASY_SHOOT_DELAY 	500
#define MEDIUM_SHOOT_DELAY 	400
#define HARD_SHOOT_DELAY 	340
//rapid fire shooting delay in difficulties
#define EASY_RAPID_SHOOT_DELAY	300
#define MEDIUM_RAPID_SHOOT_DELAY	200
#define HARD_RAPID_SHOOT_DELAY 	150
//radius of center of player difficulty in pixels
#define EASY_CENTER_RADIUS 	40
#define MEDIUM_CENTER_RADIUS	35
#define HARD_CENTER_RADIUS	28
//time since last shot required to stay in one position in ms
#define TIME_SHOT_LAST_MAX	200
//rapid fire occurences for random
#define RANDOM_RAPID_FIRE	4
//distance to stop ai at 
#define DISTANCE_X_STOP	60
//the last direction change of heli in diff difficulties min for change IN MS	
#define DIR_CHANGE_MIN_EASY	1700
#define DIR_CHANGE_MIN_MEDIUM	1400
#define DIR_CHANGE_MIN_HARD	1000
// ai vertical movements
#define AI_EASY_VERT	3
//for when to put objectives on screen
#define OBJ_Y_PREPLACEMENT	160
//obj healths
#define OBJ_HEALTH_MINOR	50
#define OBJ_HEALTH_MEDIUM	100
#define OBJ_HEALTH_MAJOR	200


//structures:

//hardkey reference
typedef enum hardKey{
	mgKey = 0,
	rocketKey,
	cannonKey,
	bombKey,
	rearKey,
	pauseKey
}HardKey;

//gamestate
typedef enum gameState{
	paused = 0,
	intro,
	playing,
	message
}GameState;	

typedef enum bulletType{
	mg8mm = 0,
	mg12mm,
	mg13mm,
	mg16mm,
	cannon20mm,
	mgff20mm,
	rocket21cm,
	cannon30mm	
}BulletType;

//up from bulletType to get info variable
typedef enum bombType{
	pL200 = 8,
	pL500,
	pL1000	
}BombType; 	

typedef enum bulletCategory{
	mg,
	cannon,
	rocket	
}BulletCategory;

typedef struct bulletInfo{
	RectangleType rect;
	UInt16 range;
	BulletBmp bmp;
	UInt8 speed;
	UInt8 damage;
	UInt32 timeout;	
	BulletCategory category;
}BulletInfo;

typedef struct bombStruct{
	BombType type;
	BulletBmp bmp;
	PointType nextpos;
	Boolean downAngle;
	UInt32 dropTime;		
}BombStruct;	

//bullet data
typedef struct bulletStruct{
	BulletType type;
	PointType start;
	PointType oldpos;	
	PointType nextpos;
	PointType target;
	UInt16 distance;
	Boolean multiAngle;
	//for up/down/multiple angles
	Boolean downAngle;
	//for multiple angles
	UInt16 angle;
	Boolean reverseAngle;
}BulletStruct;

//mapdata
typedef struct mapData{
	MapBmp type;
} MapData;

//type of enemy
typedef enum objectiveType {
	munitionsObj = 0,
	coalplantObj,
	v2Obj,
	aagunObj,
	art88mmObj,
	howitzersObj,
	radarstationObj,
	panzersObj,
	kingtigersObj,
	bunkerObj,		
	bf109Obj,
	ju87Obj,
	me110Obj,
	fw190Obj,
	zeroObj,
	me262Obj	
}ObjectiveType;

//obj struct
typedef struct objStruct{
	ObjectiveType type;
	PointType pos;
	ObjBmp bmp;
	UInt8 health;
}ObjStruct;

//map script
typedef struct scriptType{
	Coord y;
	Coord x;
	ObjectiveType type;
}ScriptType;

typedef enum direct {
	up = 0,
	down,
	left,
	right,
	select	
}Direct;

typedef enum playerType{
	spitfire,
	hurricane,
	p51d,
	yak9,
	b17,	
	bf109,
	ju87,
	me110,
	fw190,
	zero,
	me262
}PlayerType;

//map structure
//about 230 bytes
//remember this struct will not be changed in the program 
//and is read only. this means nothing about the gameplay
typedef struct mapstruct{
	char name[30];
	char about[200];
	RectangleType mapRect;
	UInt16 numBlocks;
	UInt16 numCmds;
	RectangleType blockRect;
	DmResID data;
	DmResID script;
	PlayerType userType;
	//now contains the whole map in one record
	//because map data is small and only consists of numbers for each block
	//this is a 'mapD' resource in the main db
} MapStruct;

//aircraft struct
typedef struct aircraftInfo{
	AircraftBmp bmp;	
	//rect is aligned with actual pixels not the map area
	RectangleType rect;	
	//mg info
	Boolean hasMg;
	Boolean doubleMg;
	BulletType mgType;
	PointType mgPt[2];
	//cannon info
	Boolean hasCannon;	
	BulletType cannonType;
	PointType cannonPt;
	//rocket info
	Boolean hasRocket;
	BulletType rocketType;
	PointType rocketPt;
	//rear mg info
	Boolean hasRearMg;
	BulletType rearType;
	PointType rearMgPt;
	//for bombs
	Boolean hasBomb;
	BombType bombType;
	PointType bombPt;
	//for ai if shooting alot		
	Boolean bursting;	
	//orignal health/armour
	UInt8 orgHealth;	
}AircraftInfo;

//player structure
typedef struct playerStruct{
	//these positions are within the virtual map not within actual
	PointType oldpos;
	PointType nextpos;
	//health is airplane dependant
	UInt8 health;
	//gun variables
	PlayerType type;
	//type of craft
	//direction for ai, 5 for direction enum 
	UInt8 dirSpeed[5];
	UInt32 dirSpeedTime[5];
	UInt32 dirHeldTime[5];
} PlayerStruct;

//Game structure
typedef struct gameStruct{
	GameState state;
	Difficulty diff;
	DmResID mapID;
	PlayerStruct user;
	UInt16 score;
	UInt8 lives;
	UInt32 timerValue;
	//RectangleType oldRect;
	//the current rect of virtual area, ie., x can equal 1000
	RectangleType curRect;
	//number of bullets and players, bombs
	UInt8 numPlayersOnScreen;
	UInt16 numBulletsOnScreen;
	UInt8 numBombsOnScreen;
	UInt8 numObjsOnScreen;
	//y coord offset for objects
	Coord objectYOffset;
} GameStruct;


//needed for gameplay
//global game variables:
//all externs

extern UInt16 gameIndex;
//for actual screen coords, not map coords
extern RectangleType playArea;
//game
extern GameStruct game;
//for double buffering when using updategame();
extern WinHandle ofsWin;
//window for the map
extern WinHandle mapWin;
//the gameWin is display window
extern WinHandle gameWin;
//script win for objectives
extern WinHandle scriptWin;
//gameform
extern FormType * gameForm;
//handles for the preloaded bitmaps
extern MemHandle preloadH[NUM_BMP_PRELOAD];
//preloaded bmps
extern BitmapType * preloadBmp[NUM_BMP_PRELOAD];
//windows that hold the bitmaps
extern WinHandle preloadWindow[NUM_BMP_PRELOAD];
//rectangles for each preloaded bmp
extern RectangleType preloadBounds[NUM_BMP_PRELOAD];
extern Boolean bitmapsPreloaded;
//level selected for play
extern Int16 selectedLevel;
//stack of players all controled by ai
extern PlayerStruct * player;
extern MemHandle playerH;
//bullet structure
extern BulletStruct * bullet;
extern MemHandle bulletH;
//bomb structure
extern BombStruct * bomb;
extern MemHandle bombH;
//map structure of current map, no pointer
extern MapStruct map;
//map data
extern MemHandle mapDataH;
extern MapData * mapData;	
//script
extern MemHandle scriptH;
extern ScriptType * script;
//stack of objectives
extern MemHandle objH;
extern ObjStruct * obj;
//for game play
extern MemHandle recH;
extern GameStruct * recP;
//whether to stop the game or not
extern Boolean stopgame;
//system ticks per second
extern UInt32 ticksPerSecond;
//last time of evtgetevent
extern UInt32 lastHandleTime;
//timeout value
extern Int32 timeOutValue;
//array for direction timing (5 directions (center)
extern UInt32 dirTimeHeld[5];
//array for when a button was first pressed
extern UInt32 dirTimePushed[5];
//direction speed variable
extern UInt8 dirSpeed[5];	
extern Boolean dirPushed[5];
//hardkey pushing (includes rear mg pen events)
extern Boolean hardPushed[5];
extern UInt32 hardLastAction[5];
//map overlay of rectangles
extern RectangleType * rectLayer;
extern MemHandle rectLayerH;	
//min y coord for current map segment
extern Coord mapWinYOffset;
//bullet information var (11 for num bullet types)
extern BulletInfo bInfo[11];
//aircraft info (11 for num craft types)
extern AircraftInfo aInfo[11];


//function prototypes
//for reference only:

//ai:
void addAI(PlayerType type, PointType firstPos);
void updateAI(PlayerStruct * ai);
Coord calcAIBulletPosition(Difficulty diff, Boolean xcoord);
void calcAIMove(PlayerStruct * ai);
void calcAIPos(PlayerStruct * ai, Difficulty diff);
void calcScriptCmd();
void removeAI(UInt8 aiNum);
void sortScript();
Boolean cmdIsAI();

//bullet:
void bulletNew(Coord x, Coord y, PointType start, BulletType type, Boolean multiAngle);
void bulletRemove(UInt16 bNumber);
Boolean calcBulletPos(BulletStruct * b);
void calcBulletHit(BulletStruct * b, UInt16 bulletNum);

//draw:
void copyMap();
void drawBullets();
void drawBitmap(DmResID type, Coord x, Coord y);
void drawControls();
void drawScore();
void drawLives();
void drawHealth();
void drawMap(Coord y);
void drawObjectives();
void drawPlayers();
void drawPreloadedBitmap(UInt16 bmpID, Coord x, Coord y, WinDrawOperation op);
void drawText(char * string, Coord x, Coord y);
void drawTimer(Int32 value);
Coord mapScale(Coord y);

//gamef
Boolean messageHandleEvent(EventType * event);
Boolean introHandleEvent(EventType * event);
Boolean pauseHandleEvent(EventType * event);
Boolean gameHandleEvent(EventType * event);
Boolean osHandleEvent(EventType * event);

//main
Err appStart();
void appEventLoop();
Boolean appHandleEvent(EventType * event);
void appStop();
UInt32 PilotMain (UInt16 cmd, void * cmdPBP, UInt16 launchFlags);

//utilites
void destroyWin(WinHandle win);
void deleteMapOverlay();
UInt16 calcAngle(PointType trg, PointType pos, BulletStruct * b);
UInt8 calcDirectionSpeed(UInt32 time);
void calcUserPos();
void delayProcess(UInt32 ms);
void displayLevelInfo();
UInt16 distance(PointType a, PointType b);
void gameEventLoop(EventType * event);
Boolean handleKeyDown(EventType * event);
void initGame();
Err loadGame();
void makeMapOverlay();
UInt32 milliseconds();
void pauseGame();
void playSound(UInt16 noiseid);
void preloadBitmaps();
Int32 random(Int32 maxvalue);
void startGame();
void stopGame(Boolean exit);
void unloadBitmaps();
void updateGame();	
void updateMap();