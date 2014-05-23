//globals.h - declare structures, variables, enumerations

//definitions:

//data: program data
#define DBTYPE 'DATA'
#define DBNAME "AlliedAce"
#define MAPDBNAME "AlliedAce-MapDB"
#define CREATORID 'aaGM'

//data types and offsets
//regular database:
#define BMPTYPE	'Tbmp'
#define BMPID	4000
#define WAVTYPE 'wave'
#define WAVID	5000
#define GAMETYPE	'game'
#define	GAMEID	6000
//map database:
#define MAPTYPE 'mapD'
#define MAPID	7000
#define SCRIPTTYPE 'scrT'
#define SCRIPTID	8000
#define MAPDATATYPE 'datM'
#define DATAID	9000

//resources are in capitals expect for the form
//objects like controls

//resources: forms
#define MainForm 1000 
#define GameForm 1020
#define	NewGameForm 1040
#define OptionsForm	1060

//main form resources:
#define menuSelect1	1001
#define menuSelect2	1002
#define menuSelect3	1003
#define menuSelect4	1004
#define menuNewGame "New Game"
#define menuContinueGame	"Continue Game"
#define menuOptions "Options"
#define menuExit	"Exit"
#define menuHighlightedFont	boldFont
#define menuFont stdFont	

//gameform resources
#define gameScore	1021
#define gameHealth	1022
#define gamePause	1023

//newgameform resources:
#define newGameBackTxt	"Back"
#define newGameBack	
#define newGameStartTxt	"Start"
#define newGameStart	
#define newGameMapList	
#define newGameDifficultyList

//optionsform resources:



//structures for everything except the game:

//button type
typedef struct buttonType{
	char text[20];
	UInt16 id;
	RectangleType rect;
	Boolean pushed;
	Boolean visible;
	Boolean customFont;
}ButtonType;

//main menu structure	
typedef struct Menu{
	RectangleType labels[4];
	Boolean pressed[4];
	char selections[4][10];
	Boolean music;
} Menu;	

typedef enum difficulty{
	easy = 0,
	medium,
	hard
}Difficulty;

//Preferences for game
typedef struct prefType{
	int bitDepth;
	int soundVol;
	Difficulty difficulty;
	int level;
	Boolean exitWhilePlaying;
	WChar mgKey;
	WChar cannonKey;
	WChar rocketKey;
	WChar bombKey;
	WChar pauseKey;
} PrefType;

//global vars:

//needed THROUGHOUT
//for double buffering when using updategame();
extern WinHandle ofsWin;
extern PrefType prefs;
extern Boolean optionsFromGame;
extern Boolean resuming;
extern Boolean gaming;
extern Boolean uiInit;
extern UInt8 numMaps;


//needed for MAINMENU
extern Menu menu;
extern DmOpenRef db;
extern Boolean keyed;
extern int highlighted;


//function protos:

//main menu
Boolean MainFormHandleEvent(EventType * event);
void eraseMenuSelection(int select);
void menuInit();
void drawMenuSelection(int forget);
void menuHighlight(int highlightIndex, Boolean highlight);
void doMenuAction(int command);

//options form
Boolean OptionsFormHandleEvent(EventType * event);

//new game form




				