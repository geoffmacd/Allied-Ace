//formh_game.c- specific api's to load and manage gametime

#include <PalmOS.h>
#include "globals.h"
#include "gameglobals.h"

//variables needed for this file
//for key rates orginals
UInt16 orgDelay;
UInt16 orgPeriod;
Boolean orgQueue;  

Boolean gameHandleEvent(EventType * event)
{
	PointType start;
	Coord x,y;
	Boolean handled = false;
	gaming = true;
	
	//handle normal event
	switch(event->eType)
	{	
		case penDownEvent:
			//this event is sent when pen is first touched on the screen
			//call appropriate functions that handle tap
			x = event->screenX;
			y = event->screenY;	
			//if the user is a bomber fire rear mg		 
			if(game.user.hasRearMg 
			&& game.timerValue > hardLastAction[rearKey] + bInfo[aInfo[game.user.type].rearType].timeout)
			{
				//only if the tap is below the rear machine gun
				if(mapScale(game.user.nextpos.y) > MIN_REAR_MG_Y)
				{
					start.x = game.user.nextpos.x; 
					start.y = game.user.nextpos.y; 
					bulletNew(x, y, start, aInfo[game.user.type].rearType, true);
				}
			}
			handled = true;
			break;
			
		case penMoveEvent:
			//this event is sent when pen is moved on the screen. 
			//only shoot when in a bomber and past y min
			x = event->screenX;
			y = event->screenY;	
			//if the user is a bomber fire rear mg		 
			if(game.user.hasRearMg
			&& game.timerValue > hardLastAction[rearKey] + bInfo[aInfo[game.user.type].rearType].timeout)
			{
				//only if the tap is below the rear machine gun
				if((game.user.oldpos.y - game.curRect.topLeft.y) > MIN_REAR_MG_Y)
				{
					start.x = game.user.nextpos.x; 
					start.y = game.user.nextpos.y; 
					bulletNew(x, y, start, aInfo[game.user.type].rearType, true);
				}
			}				
			handled = true;
			break;	
			
		case penUpEvent:
			//this is called when the pen is lifted from the screen
			//call appropriate functions that handle taps	
			x = event->screenX;
			y = event->screenY;	
			//if the user is a bomber fire rear mg		 
			if(game.user.hasRearMg
			&& game.timerValue > hardLastAction[rearKey] + bInfo[aInfo[game.user.type].rearType].timeout)
			{
				//only if the tap is below the rear machine gun
				if((game.user.oldpos.y - game.curRect.topLeft.y) > MIN_REAR_MG_Y)
				{
					start.x = game.user.nextpos.x; 
					start.y = game.user.nextpos.y; 
					bulletNew(x, y, start, aInfo[game.user.type].rearType, true);
				}
			}	
			if(!game.user.hasRearMg)
			{
				//user is not a bomber, pause the game
				pauseGame();					
			}
			if((game.user.oldpos.y - game.curRect.topLeft.y) < MIN_REAR_MG_Y)
			{
				//is a bomber but need to pause
				pauseGame();	
			}					
			handled = true;
			break;
			
		case keyDownEvent:
			//handle game keys
			handleKeyDown(event);
			handled = true;
			break;
			
		case keyHoldEvent:
			//handle hold event
			//handleKeyHold(event);
			handled = true;
			break;	
			
		case keyUpEvent:
			//handle up key
			handleKeyUp(event);
			handled = true;
			break;	
			
		case nilEvent:

			//handled = true;
			break;
		
		default:
			break;
	}		
}

Boolean pauseHandleEvent(EventType * event)
{
	Boolean handled = false;
	gaming = false;
	
	//handle normal event
	switch(event->eType)
	{	
		case penDownEvent:
			
			handled = true;
			break;
			
		case penMoveEvent:

			
			handled = true;
			break;	
			
		case penUpEvent:
			//this is called when the pen is lifted from the screen
			//call appropriate functions that handle taps	
			//set state
			resume();		
			handled = true;
			break;
			
		case keyDownEvent:
			//call functions that handle
			handled = false;
			break;
		
		default:
			break;
	}		
}

Boolean introHandleEvent(EventType * event)
{
	Boolean handled = false;
	gaming = false;
	
	//handle normal event
	switch(event->eType)
	{	
		case penDownEvent:
			handled = true;
			break;
			
		case penMoveEvent:
			handled = true;
			break;	
			
		case penUpEvent:
			//start the game here 	
			//set state
			resume();	
			handled = true;
			break;
			
		case keyDownEvent:
			handled = false;
			break;
		
		default:
			break;
	}		
}


Boolean messageHandleEvent(EventType * event)
{
	Boolean handled = false;
	gaming = false;
	
	//handle normal event
	switch(event->eType)
	{	
		case penDownEvent:

			handled = true;
			break;
			
		case penMoveEvent:
			handled = true;
			break;	
			
		case penUpEvent:
			//set state
			resume();				
			handled = true;
			break;
			
		case keyDownEvent:
			
			break;
		
		default:
			break;
	}		
}

/*handle all os generated events and convert them to 
something in the game. must split the function into one
that handles intro, playing, message and pause states of 
the game.*/
Boolean osHandleEvent(EventType * event)
{
	//for pen points
	Coord x,y;
	//handled boolean for returning
	Boolean handled = false;
	//form
	FormType * form;
	UInt16 keyRepeat;
	UInt16 keyDelay;
	RectangleType rect;
		
	//handle normal event
	switch(event->eType)
	{
		case frmOpenEvent:
			form = FrmGetActiveForm();
			gameForm = form;
			FrmDrawForm(form);		
			//display intro/load image
			//get paused gadget bounds
			FrmGetObjectBounds(gameForm, FrmGetObjectIndex(gameForm, gamePause), &rect);	
			//draw paused graphic
			drawPreloadedBitmap(loadingBmp, rect.topLeft.x, rect.topLeft.y, winOverlay);			
			/*use double density always, doesn't matter what type the
			 * actual screen is. app must have hi res feature set so
			 * double density will be recognized regardless*/
			orgDensity = WinSetCoordinateSystem(kCoordinatesDouble);
			//load game mem handles etc.
			ErrFatalDisplayIf(loadGame(), "In loadGame(), Error loading game");
			//may validate structure of gamestruct here in future or release
			//initilize game and ai and map etc.
			initGame();	
			//set key repeat rate
			KeyRates(false, &orgDelay, &orgPeriod, NULL, &orgQueue);
			keyDelay = (KEY_DELAY_REPEAT * ticksPerSecond)/1000;
			keyRepeat = (KEY_REPEAT_TIME * ticksPerSecond)/1000;
			KeyRates(true, &keyDelay, &keyRepeat, NULL, false);						
			//wait for next event to update the screen			
			handled = true;
			break;
			
		//when the game closes	
		case frmCloseEvent:
			/* unload everything
			 * make organized */
			 
			//uninitialize
			//pause for saved game
			gaming = false;
			game.state = paused;

			//only unload if they were loaded
			if(bitmapsPreloaded)
				unloadBitmaps();
			
			//save game progress
			saveGame();	
			//release handles
			if(scriptH)
			{
				MemHandleUnlock(scriptH);
				DmReleaseResource(scriptH);	
			}
			if(objH)
			{
				MemHandleUnlock(objH);
				MemHandleFree(objH);						
			}
			if(bulletH)
			{
				MemHandleUnlock(bulletH);
				MemHandleFree(bulletH);	
			}
			if(bombH)
			{
				MemHandleUnlock(bombH);
				MemHandleFree(bombH);	
			}			
			if(playerH)
			{
				MemHandleUnlock(playerH);
				MemHandleFree(playerH);				
			}	
			if(mapDataH)
			{	
				//free mapdata
				MemHandleUnlock(mapDataH);
				DmReleaseResource(mapDataH);	
			}	
			//free the rectangle overlay here for room in dynamic heap
			deleteMapOverlay();					
			//delete the windows	
			WinDeleteWindow(ofsWin, false);
			WinDeleteWindow(mapWin, false);
			//set coords back
    		WinSetCoordinateSystem(orgDensity);
			//set key rate back
			KeyRates(true, &orgDelay, &orgPeriod, NULL, &orgQueue);
			//leave false to let system release everything else
			handled = false;	
			break;
				
		default:
			break;	
		//end of event switch check	
	}
	
	if(!handled && event->eType != frmCloseEvent)
	{
		//there is never no gamestate without first opening form
		switch(game.state)
		{
			case intro:
				handled = introHandleEvent(event);
				break;
			case playing:
				handled = gameHandleEvent(event);
				break;
			case message:
				handled = messageHandleEvent(event);
				break;
			case paused:
				handled = pauseHandleEvent(event);
				break;			
			default:
				ErrDisplay("In osHandleEvent, no such game state");
				break;
		}
	}
	//return handled or not
	return handled;	
}