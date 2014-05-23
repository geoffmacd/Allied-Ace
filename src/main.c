//main.c - starts application up

#include <PalmOS.h>
#include <MathLib.h>
//app defined headers
//for menus
#include "globals.h"
//for game
#include "gameglobals.h"
//for 5-way and other palmone hardware
#include <palmOne_68K.h>


//game global variables:

UInt16 gameIndex;
//for actual screen coords, not map coords
RectangleType playArea;
//game
GameStruct game;
//for double buffering when using updategame();
WinHandle ofsWin;
//window for the map
WinHandle mapWin;
//the gameWin is display window
WinHandle gameWin;
//script win for objectives
WinHandle scriptWin;
//gameform
FormType * gameForm;
//handles for the preloaded bitmaps
MemHandle preloadH[NUM_BMP_PRELOAD];
//preloaded bmps
BitmapType * preloadBmp[NUM_BMP_PRELOAD];
//windows that hold the bitmaps
WinHandle preloadWindow[NUM_BMP_PRELOAD];
//rectangles for each preloaded bmp
RectangleType preloadBounds[NUM_BMP_PRELOAD];
Boolean bitmapsPreloaded = false;
//level selected for play
Int16 selectedLevel = 1;
//stack of players all controled by ai
PlayerStruct * player;
MemHandle playerH;
//stack of objectives
MemHandle objH;
ObjStruct * obj;
//bullet structure
BulletStruct * bullet;
MemHandle bulletH;
//map data
MemHandle mapDataH;
MapData * mapData;	
//map structure of current map, no pointer
MapStruct map;
//script
MemHandle scriptH;
ScriptType * script;
//for game play
MemHandle recH;
GameStruct * recP;
//whether to stop the game or not
Boolean stopgame = false;
//system ticks per second
UInt32 ticksPerSecond;
//last time of evtgetevent
UInt32 lastHandleTime;
//timeout value
Int32 timeOutValue;
//array for direction timing (5 directions (center)
UInt32 dirTimeHeld[5];
//array for when a button was first pressed
UInt32 dirTimePushed[5];
//direction speed variable
UInt8 dirSpeed[5];	
Boolean dirPushed[5];
//map overlay of rectangles
RectangleType * rectLayer;
MemHandle rectLayerH;	
//hard keys
Boolean hardPushed[5];
UInt32 hardLastAction[5];
//min segment y
Coord mapWinYOffset = 0;
//bullet information var (11 for num bullet types)
BulletInfo bInfo[11];
//aircraft info (11 for num craft types)
AircraftInfo aInfo[11];

//needed THROUGHOUT:

PrefType prefs;
Boolean optionsFromGame = false;
Boolean resuming;
Boolean gaming;
UInt8 numMaps;

//needed for MAINMENU:

Menu menu;
DmOpenRef db;
Boolean keyed = false;
int highlighted;


//needed for this file:

UInt16 orgDensity;
 
Err appStart()
{
	Err err = false;
	UInt32 romVersion;
	UInt16 prefsize;
	Err matherr;
	LocalID dbid;
	UInt32 depth;
	UInt16 density = 0;
	
	//detect os version, make sure it is os 4 and up
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
	if(sysGetROMVerMajor(romVersion) < 4 && sysGetROMVerMinor(romVersion) < 0)
	{
		ErrDisplay("Palm OS version not compatible. OS 4 or higher. Sorry!");
		err = true;
	}
	
	//open database
	//look for db
	dbid = DmFindDatabase(0, MAPDBNAME);
	if(dbid)
	{
		//db was found, open it in read/write
		db = DmOpenDatabase(0, dbid, dmModeReadOnly);
		ErrFatalDisplayIf(!db, "Database could not be opened!");
	}
	else
	{
		ErrDisplay("In appStart(), couldn't find 'AlliedAce-MapDB'. Please install this file by dragging AlliedAce-MapDB.pdb to quick install");	
	}
	
	//load the mathlib
	err = SysLibFind(MathLibName, &MathLibRef);
	if (err)
    	err = SysLibLoad(LibType, MathLibCreator, &MathLibRef);
	ErrFatalDisplayIf(err, "Can't find MathLib. Please install mathlib.prc!"); // Just an example; handle it gracefully
	matherr = MathLibOpen(MathLibRef, MathLibVersion);
	ErrFatalDisplayIf(err, "Can't open MathLib. Please install mathlib.prc!"); 	
	
	//retrieve preferences
	prefsize = sizeof(PrefType);
	if(PrefGetAppPreferences(CREATORID, 0, &prefs, &prefsize, true) == noPreferenceFound)	
	{
		prefs.bitDepth = 16;
		prefs.soundVol = 0; //mute for now
		prefs.difficulty = medium; 	
		prefs.level = 1;
		prefs.exitWhilePlaying = false;
		prefs.mgKey = keyBitHard4; 
		//rockets and cannons never coincide
		prefs.cannonKey = keyBitHard3; 
		prefs.rocketKey = keyBitHard3; 
		prefs.bombKey = navBitSelect; 
		prefs.pauseKey = keyBitHard1;
		PrefSetAppPreferences(CREATORID, 0, 1, &prefs, sizeof(prefs), true);
	}

	//detect screen depth
	WinScreenMode(winScreenModeGetSupportedDepths, NULL, NULL, &depth, NULL);
	//test for 8 or 16 bit mode
	if(0x8000 & depth)
	{
		//compatible
		prefs.bitDepth = 16;
	}
	else if(0x0080 & depth)
	{
		//compatible
		prefs.bitDepth = 8;
	}
	else
	{
		//not compatible	
		return false;
	}	
	WinScreenMode(winScreenModeSet, NULL, NULL, prefs.bitDepth, NULL);
	
	if(err = false)
	{
		if(prefs.exitWhilePlaying != true)
		{
			FrmGotoForm(MainForm);
		}
		else
		{	
			resuming = true;
			//goto game form and load last game played	
			FrmGotoForm(GameForm);	
		}
	}		
	
	return err;
} 


void appEventLoop()
{
	EventType	event;	
	do {	
				
		if(gaming)
		{
			//if the user is playing
			EvtGetEvent(&event, timeOutValue);
			gameEventLoop(&event);
			//if a hard key was pressed goto form handle
			if((event.eType == keyDownEvent 
			//|| event.eType == keyHoldEvent , dont care about this for now
			|| event.eType == keyUpEvent)
			&& (TxtCharIsHardKey(event.data.keyDown.modifiers, event.data.keyDown.chr)
			|| TxtCharIsHardKey(event.data.keyHold.modifiers, event.data.keyHold.chr)
			|| TxtCharIsHardKey(event.data.keyUp.modifiers, event.data.keyUp.chr)))
				goto _frmhandle;
		}
		else 
		{
			//if the user isn't playing the game
			//saves power for main menu, options, newgame, intro of game
			EvtGetEvent(&event, evtWaitForever);			
		}

						 	
		if (SysHandleEvent(&event))
			if (appHandleEvent(&event))
_frmhandle:		FrmDispatchEvent(&event);
						
		
	} while (event.eType != appStopEvent);
	//wait until the app stops with this etype
}

Boolean appHandleEvent(EventType * event)
{
	UInt16 		id;
	FormType *	form;
	Boolean		handled = false;

	if (event->eType == frmLoadEvent) {
		// Load the form resource.
		id = event->data.frmLoad.formID;
		
		form = FrmInitForm(id);
		FrmSetActiveForm(form);

		// Set the event handler for the form.  The handler of the currently
		// active form is called by FrmHandleEvent each time is receives an
		// event.
		switch(id) 
		{
			case MainForm:
				FrmSetEventHandler(form, MainFormHandleEvent);
				break;
				
			case OptionsForm:	
				//FrmSetEventHandler(form, OptionsMenuHandleEvent);
				break;
				
			case NewGameForm:
				FrmSetEventHandler(form, NewGameFormHandleEvent);
				break;	
				
			case GameForm:					
				FrmSetEventHandler(form, osHandleEvent);
				break;
								
			default:
				ErrDisplay("Invalid form goto command in appEventLoop()");
				break;
		}
		handled = true;
	}
	
	if(uiInit)
	{
		handled = uiHandleEvent(event);	
	}
	
	return handled;
}

void appStop()
{
	//unload everything loaded in appStart()	
	UInt usecount;
	Err err;

	//close mathlib
	err = MathLibClose(MathLibRef, &usecount);
	ErrFatalDisplayIf(err, "Can't close MathLib");
	if (usecount == 0)
	    SysLibRemove(MathLibRef); 
	
	//save prefs
	PrefSetAppPreferences(CREATORID, 0, 1, &prefs, sizeof(PrefType), true);
    
    //close database
    err = DmCloseDatabase(db);	
    ErrFatalDisplayIf(err != errNone, "In appStop(), couldn't close database");
    
    uiInit = false;
    
    //close all forms	
	FrmCloseAllForms();	
}

UInt32 PilotMain (UInt16 cmd, void * cmdPBP, UInt16 launchFlags) 
{ 
	//check for system version
	Err error = errNone;

	switch (cmd) {
		case sysAppLaunchCmdNormalLaunch:
			if ((error = appStart()) == 0) {			
				appEventLoop();
				appStop();
			}
			break;
			
		//no other cmds i want to handle	

		default:
			break;
	}
	
	return error;
} 