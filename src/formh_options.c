//formh_options.c - handles everything in options form

//includes:
#include <PalmOS.h>
#include "globals.h"
#include "gameglobals.h"

//functions:
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

Boolean OptionsFormHandleEvent(EventType * event)
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
					
			}
			handled = true;
			break;	
			
		case lstSelectEvent:
			
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
