//formh_newgame.c - file that handles everything on new game form

//includes:
#include <PalmOS.h>
#include "globals.h"
#include "gameglobals.h"

//globals
ListType * mapList;
ListType * diffList; 

//functions:

void newGame()
{
	GameStruct temp;
	MemHandle newRecordH;
	GameStruct * newRecord;
	MapStruct * mapRec;
	MemHandle mapRecH;	
	
	temp.mapID = MAPID + LstGetSelection(mapList) + 1;
		
	mapRecH = DmGetResource(MAPTYPE, temp.mapID);
	ErrFatalDisplayIf(!mapRecH, "In loadGame, couldn't load map structure");
	mapRec = (MapStruct *)MemHandleLock(mapRecH); 
	map = *mapRec;
	MemHandleUnlock(mapRecH);
	DmReleaseResource(mapRecH);	
	
	temp.state = intro;
	temp.diff = LstGetSelection(diffList);
	temp.curRect.topLeft.x = 0;
	temp.curRect.topLeft.y = map.mapRect.extent.y - GAMEPLAY_EXTENT_Y;
	temp.curRect.extent.x = map.mapRect.extent.x;
	temp.curRect.extent.y = map.mapRect.extent.y;	
	
	//set aircraft specs
	//set user values
	temp.user.type = map.userType;
	temp.user.health = aInfo[temp.user.type].orgHealth;
	temp.user.nextpos.x = USER_START_X;
	temp.user.nextpos.y = (map.mapRect.extent.y - GAMEPLAY_EXTENT_Y) + USER_START_Y;
	temp.user.oldpos = temp.user.nextpos;
	
	//game values
	temp.score = 0;
	temp.lives = DEFAULT_LIVES;
	temp.timerValue = 0;
	temp.numPlayersOnScreen = 0;
	temp.numBulletsOnScreen = 0;
	temp.numBombsOnScreen = 0;
	temp.numObjsOnScreen = 0;
	temp.objectYOffset = 0;
	
	newRecordH = DmNewResource(db, GAMETYPE, GAMEID, sizeof(GameStruct));
	ErrFatalDisplayIf(!newRecordH, "In newGame(), couldn't make new game resource");
	newRecord = (GameStruct *)MemHandleLock(newRecordH);
	MemMove(newRecord, &temp, sizeof(GameStruct));
	MemHandleUnlock(newRecordH);
	DmReleaseResource(newRecordH);
	
}

UInt8 numDbMaps()
{
	 UInt16 i = 0;
	 Int16 result;
	 
	 numMaps = 0;	 
	 //search through id's 7000-8000 for any maps you can find
	 for(i = MAPID; i < MAPID + 1000; i++)
	 {
	 	//use dmfindresourcetype next
	 	result = DmFindResource(db, MAPTYPE, i, NULL);
	 	
	 	if(result != -1)
	 	{
	 		//found mapdata record
	 		numMaps++;	
	 	}
	 }	
	 
}

void newFormUninit()
{
	removeButton(newGameBack);
	removeButton(newGameStart);
	
	uiInit = false;
}

void newFormInit()
{	
	//two new buttons
	newButton(getObjectRect(newGameBack), newGameBackTxt, newGameBack);
	newButton(getObjectRect(newGameStart), newGameStartTxt, newGameStart);
	
	//set list handler
	mapList = (ListType *)getObjectPtr(newGameMapList);
	LstSetDrawFunction(mapList, (ListDrawDataFuncPtr)mapListDraw);
    //set numchoices
	LstSetListChoices(mapList, NULL, numMaps);
	//draw
	LstDrawList(mapList);
	//set the selection to the first map
	LstSetSelection(mapList, prefs.level - 1);

	//set popup to preferences
	diffList = (ListType *)getObjectPtr(newGameDifficultyList);
	LstSetDrawFunction(diffList, (ListDrawDataFuncPtr)diffListDraw);
    //set numchoices
	LstSetListChoices(diffList, NULL, 3);
	//draw
	LstDrawList(diffList);
	//set the selection to the first map
	LstSetSelection(diffList, prefs.difficulty);
	
	uiInit = true;
}

Boolean NewGameFormHandleEvent(EventType * event)
{
	Boolean handled = false;
	FormType * form;

	
	switch(event->eType){
		
		case frmOpenEvent:
			form = FrmGetActiveForm();
			newFormInit();			
			drawForm(form);
			handled = true;
			break;
			
		case ctlSelectEvent:
			switch(event->data.ctlSelect.controlID)
			{
				case newGameBack:
					FrmGotoForm(MainForm);
					break;
					
				case newGameStart:
					newGame();
					FrmGotoForm(GameForm);
					break;														
			}
			handled = true;
			break;	
			
		case frmCloseEvent:
			newFormUninit();
			handled = false;
			break;		
			
		default:
			break;				
	}
	return handled;
}

