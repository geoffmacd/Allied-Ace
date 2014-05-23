//utilities.c- diff game utils 

#include <PalmOS.h>
#include "globals.h"
#include "gameglobals.h"
//for 5-way and other palmone hardware
#include <palmOne_68K.h>
//for math
#include "MathLib.h"

//functions

void resume()
{
	game.state = playing;
	lastHandleTime = milliseconds();
	gaming = true;		
}

void destroyWin(WinHandle win)
{
	WinDeleteWindow(win, false);		
}

void saveGame()
{
	Err err;
	
	//save the game in the regular database
	game.numPlayersOnScreen = 0;
	game.numBulletsOnScreen = 0;
	game.numBombsOnScreen = 0;
	game.timerValue = 0;
	game.state = paused;
	
	err = DmWrite(recP, 0, (GameStruct *)&game, sizeof(GameStruct));
	ErrFatalDisplayIf(err != errNone, "In saveGame(), couldn't write to database");
	
	MemHandleUnlock(recH);
	DmReleaseResource(recH);
		
}

void deleteMapOverlay()
{
	if(rectLayerH)
	{
		MemHandleUnlock(rectLayerH);	
		MemHandleFree(rectLayerH);
	}
}

UInt16 calcAngle(PointType trg, PointType pos, BulletStruct * b)
{
	/*calculate angle by making a tangent to the target with
	 * 2 new lines then finding the distances of those two
	 * lines, then using sine to figure out angle and return.
	 * should be calced like tan-1 function*/
	 
	PointType oppang; 
	UInt16 adjside;
	UInt16 oppside;
	UInt16 angle;
	
	oppang.x = trg.x;
	oppang.y = pos.y;
	
	//calc distance of opp and adj sides
	adjside = distance(pos, oppang);
	oppside = distance(oppang, trg);
	
	//divide opp over adj like SOA
	angle = ((double)oppside) / ((double)adjside);
	//tan-1 the double value and x by radian-degree ratio;
	angle = (UInt16) atan(angle) * 57.29578;

	//figure out if what type of angle it is
	//if target is behind pos on x axis it's reversed
	if(trg.x < pos.x)
	{
		b->reverseAngle = true;
	}
	else
	{
		b->reverseAngle = false;	
	}
	//if trg.y is higher than pos.y, than the shot is going down
	if(trg.y > pos.y)
	{
		b->downAngle = true;	
	}
	else
	{
		b->downAngle = false;	
	}
	//set angle
	b->angle = angle;
	
	return angle;
}

UInt8 calcDirectionSpeed(UInt32 time)
{
	if(time < STRAFE_TIME_NEXT)
	{
		return STRAFE_FIRST;	
	}	
	else if(time < STRAFE_TIME)
	{
		return STRAFE_NEXT;	
	}
	else
	{
		return STRAFE;
	}
	
	//should never get to this point
}

void calcUserPos()
{
	/*important. moves user depending on what keys 
	 * are pressed. may be wrong or too slow/fast.*/
	PointType * old = &game.user.oldpos;
	PointType * next = &game.user.nextpos;

	//if turing left	
	if(dirTimeHeld[left] && old->x > game.curRect.topLeft.x)
	{
		//subtract x coord to move left				
		next->x -= dirSpeed[left];
	}
	//if right point of heli isnt past right x of map
	if(dirTimeHeld[right] && old->x + aInfo[game.user.type].rect.extent.x 
	< game.curRect.topLeft.x + game.curRect.extent.x)
	{
		//move right
		next->x += dirSpeed[right];
	}
	//if its up and user isnt above maximum line
	if(dirTimeHeld[up] && old->y > MAX_USER_Y_POS + game.curRect.topLeft.y)
	{
		//move up a bit, although the screen is already moved up
		next->y -= dirSpeed[up];	
	} 
	//if  its down and the user isn't below the actual screen
	if(dirTimeHeld[down] && old->y < game.curRect.topLeft.y + playArea.extent.y)
	{
		//move down a little
		next->y += dirSpeed[down];		
	} 
	//select button, shoot if delay is over
	if(dirTimeHeld[select])
	{
		if(game.timerValue - game.user.lastshot > MIN_SHOT_INTERVAL)
		{
			//bomb
		}
	}		
	//update default progrss			
	next->y -= MAP_DEFAULT_PROGRESS_Y;	
	//set new to old
	*old = *next;
	
	//everything is ready to be updated
}

void delayProcess(UInt32 ms)
{
	//delays processor for ms milliseconds	
	//turn ms into ticks
	SysTaskDelay((ms * ticksPerSecond)/1000);	
}

void displayLevelInfo()
{
	char level[20];
	char about[200];
	char temp[20];
	Coord x, y;
	Int16 i, k, length;
	
	StrCopy((char *)&level, (char *)&map.name);
	StrCopy((char *)&about, (char *)&map.about);
	length = StrLen((char *)&about);
	
	for(i = 0; i < 10; i++)
	{
		for(k= 0; k < 20; k++)
		{
			if(about[i * 20 + k] != '\n')
			{
				StrNCopy((char *)&temp, (char *)&about[i * 20 + k], sizeof(char));
			}
			else
			{
				StrNCopy((char *)&temp, (char *)&about[i * 20 + k], sizeof(char) * k);
				drawText((char *)&temp, 15, 20 + (i * 12));	
				return;
			}
		}
		//set x and y 
		drawText((char *)&temp, 15, 20 + (i * 12));		
	}
	//draw name
	drawText((char *)&level, 2, 2);
}

UInt16 distance(PointType a, PointType b)
{
	double distance, temptotal;
	Int16 tempx, tempy;
	
	//calculate length of a line using 
	//length of line formula
	//ab = ?(x2-x1)^2 + (y2-y1)^2	
	tempx = b.x - a.x;
	tempy = b.y - a.y;
	
	tempx *= tempx;
	tempy *= tempy;	
	
	temptotal = (double)tempx + (double)tempy;
	distance = sqrt(temptotal);
	
	//if its negative make it the opposite positive value
	if(distance < 1)
		distance *= -1;
	
	ErrFatalDisplayIf(distance < 0, "Negative distance value in distance()");
	return (UInt16)distance;
}

void gameEventLoop(EventType * event)
{
	/*calculate whether to skip a frame or not in this*/
	Int16 loopTimeDiff;
			
	//set last handletime
	lastHandleTime = game.timerValue;		
	//set timer
	game.timerValue = milliseconds();
	//difference of supposed and actual timing					
	loopTimeDiff = game.timerValue - (lastHandleTime + timeOutValue);
	//set last to now for next loop
	lastHandleTime = game.timerValue;
			
	//if suposed time is less than or greater than timeexception, then skip this frame
	if(loopTimeDiff < TIME_EXCEPTION && loopTimeDiff > -(TIME_EXCEPTION))
	{					
		//if it isn't closing, update
		if(event->data.keyDown.chr != frmCloseEvent)
		{
			updateGame();
		}
	}
	else if(loopTimeDiff < -(DEFAULT_MIN_DELAY_TIME))
	{
		//delay until timeout has been reached
		//make sure it is positive milliseconds
		delayProcess(loopTimeDiff * -1);
		//now it is the right time
		if(event->data.keyDown.chr != frmCloseEvent)
		{
			updateGame();
		}		
	}
	else if(loopTimeDiff > TIME_EXCEPTION)
	{
		//skip a frame so don't update
		//delay processor until next timeout
		delayProcess(timeOutValue - loopTimeDiff);
		if(event->data.keyDown.chr != frmCloseEvent)
		{
			updateGame();
		}				
		//in future put a warning symbol up for debugging	
		//also make the timeout value bigger since
		//this processor obviously cant handle it	
	}	
	
}

Boolean handleKeyDown(EventType * event)
{
	//the navchanges are when the key held is changed
	//the navbits are what button is down after holding it a second or 2
	Coord x,y;
	PointType target;
	PointType org;
	
   	switch(event->data.keyDown.keyCode & (navChangeBitsAll | keyBitsAll))
    {
      		//do 5-way nav actions
      		case navChangeUp:
      			dirTimePushed[up]= game.timerValue;
      			dirTimeHeld[up]= 0;
      			dirPushed = true;
   				break;
      					
       		case navChangeDown:
       			dirTimePushed[down]= game.timerValue;
       			dirTimeHeld[down]= 0;
      			dirPushed = true;
      			break;      					
      					
      		case navChangeLeft:
      			dirTimePushed[left]= game.timerValue;
      			dirTimeHeld[left]= 0;
      			dirPushed = true;
      			break;      					
      					
      		case navChangeRight:
      			dirTimePushed[right]= game.timerValue;
      			dirTimeHeld[right]= 0;
      			dirPushed = true;
      			break;      					
      					
      		case navChangeSelect:
      			dirTimePushed[select]= game.timerValue;
      			dirTimeHeld[select]= 0;
      			dirPushed = true;
       			break; 
       			
       	    // a hard key was pressed    					   						  
	      	case prefs.mgKey:
				//fire mg
				org.x = game.user.oldpos.x;
				org.y = game.user.oldpos.y;	
				x = game.user.oldpos.x;
				y = game.user.oldpos.y - RANGE_BULLET;	
				bulletNew(x, y, org, game.user.craft.mgType, false);
				hardPushed[mgKey] = true;
				hardLastAction[mgKey] = game.timerValue;
				break;
				
			case prefs.rocketKey:
				//fire rocket			
				org.x = game.user.oldpos.x;
				org.y = game.user.oldpos.y;	
				x = game.user.oldpos.x;
				y = game.user.oldpos.y - RANGE_ROCKET;	
				bulletNew(x, y, org, rocket21cm, false);
				hardPushed[rocketKey] = true;
				hardLastAction[rocketKey] = game.timerValue;			
				break;
				
			case prefs.cannonKey:
				//fire cannon
				org.x = game.user.oldpos.x;
				org.y = game.user.oldpos.y;	
				x = game.user.oldpos.x;
				y = game.user.oldpos.y - RANGE_CANNON;	
				bulletNew(x, y, org, game.user.craft.cannonType, false);	
				hardPushed[cannonKey] = true;
				hardLastAction[cannonKey] = game.timerValue;			
				break;
			
			case prefs.bombKey:
				//drop bomb
				org.x = game.user.oldpos.x;
				org.y = game.user.oldpos.y;
				bombNew(org, game.user.craft.bombType);
				hardPushed[bombKey] = true;
				hardLastAction[bombKey] = game.timerValue;
				break;
				
			case prefs.pauseKey:
				//pause game
				pauseGame();
				break;  					 
      					     					        					    						
      		default:
      			break;	     				
      	
    }	
	return true;	
}


void initGame()
{
	//initialize playing
	if(!resuming)
	{
		//starting new game, show display
		displayLevelInfo(); //display level info
		//gaming is always false during intro
		gaming = false;
		//put game state to intro
		game.state = intro;
		game.objectYOffset = 0;	
	}
	else
	{	
		//resuming,set gaming to false				
		gaming = false;
		game.state = paused;	
	}
	
	//set play area for pen events				
	playArea.topLeft.x = GAMEPLAY_TOPLEFT_X;
	playArea.topLeft.y = GAMEPLAY_TOPLEFT_Y;	
	playArea.extent.x = GAMEPLAY_EXTENT_X;	
	playArea.extent.y = GAMEPLAY_EXTENT_Y;
	//current position of map is set in newgame or saved game	
	
	//set segment positions
	mapWinYOffset = map.mapRect.extent.y - MAP_SEGMENT_EXTENT_Y;	
	
	//make sure this is set for milliseconds function
	ticksPerSecond = SysTicksPerSecond();
	//set time out value or updates for every second
	timeOutValue = (ticksPerSecond / 1000) * DEFAULT_TIME_OUT;				

	//set last handle time to now to start right away without delays
	lastHandleTime = milliseconds() - timeOutValue;
}

Err loadGame()
{
	/* this function is important. 
	 * it should take maybe a second or two.
	 * everything loaded here should be freed
	 * at end*/
	MapStruct * mapRec;
	MemHandle mapRecH;
	UInt16 err;
	
	//create offscreens and get permanent display win
	mapWin = WinCreateOffscreenWindow(map.mapRect.extent.x, MAP_SEGMENT_EXTENT_Y, nativeFormat, (UInt16 *)&err);
	ErrFatalDisplayIf(err != errNone, "In loadGame(), couldn't allocate large enough window (not enough dynamic memory)");		
	//ofsWin is win to draw to in updateGame
	ofsWin = WinCreateOffscreenWindow(playArea.extent.x, playArea.extent.y, nativeFormat, (UInt16 *)&err);			
	ErrFatalDisplayIf(err != errNone, "In loadGame(), couldn't allocate large enough window (not enough dynamic memory)");	
	gameWin = WinGetDisplayWindow();
		
	/* get gamestruct from database . the resid is the 
	 * levelselected variable which is dmresid that was changed in
	 * new game or main form, even if it is a new game it is still put
	 * in and taken out of the db. check fro errors*/
	 //the game is a record not resource
	recH = DmGetResource(GAMETYPE, GAMEID);
	ErrFatalDisplayIf(!recH, "In loadGame, couldn't load game structure");
	recP = (GameStruct *) MemHandleLock(recH);
	game = *recP;
	
	/* load map from database. get id of resource from gamestruct
	 * assign the pointer mapdata the contents of where mapP 
	 * points to, to reduce dynamic heap*/
	mapRecH = DmGetResource(MAPTYPE, game.mapID);
	ErrFatalDisplayIf(!mapRecH, "In loadGame, couldn't load map structure");
	mapRec = (MapStruct *)MemHandleLock(mapRecH); 
	map = *mapRec;
	MemHandleUnlock(mapRecH);
	DmReleaseResource(mapRecH);
	
	//preload all bitmaps before drawing anything
	preloadBitmaps();	
	
	/*make entire stationary map here and free everything
	map can not be drawn again the entire program because data
	is released, shouldn't need to though*/
	//make rectangle overlay
	makeMapOverlay();	
	//load mapdata from id in mapstruct	
	mapDataH = DmGetResource(MAPDATATYPE, map.data);
	ErrFatalDisplayIf(!mapDataH, "In loadGame(), Couldn't get mapdata from db");
	mapData = (MapData *) MemHandleLock(mapDataH);
	//draw the map to the offscreen window (both segments)
	drawMap(map.mapRect.extent.y - MAP_SEGMENT_EXTENT_Y);
	drawMap(map.mapRect.extent.y - (MAP_SEGMENT_EXTENT_Y / 2));
	
	//load ai script from db	
	//get and lock script from database
	scriptH = DmGetResource(SCRIPTTYPE, map.script);
	ErrFatalDisplayIf(!scriptH, "In loadScript(), couldn't retrieve script from database");
	script = (ScriptType *) MemHandleLock(scriptH);
	
	//set aircraft and bullet info variables
	loadBullets();
	loadAircraft();
	
	return false;
}

UInt32 milliseconds()
{
	//return number of milliseconds since app started

	//divide all ticks by the number of ticks in a second to get
	//seconds, then divide by 1000 to achieve one thousandth of
	//a second or a millisecond
	return (TimGetTicks() / ticksPerSecond) / 1000;
}

void playSound(UInt16 noiseid)
{
	MemHandle audioh;
	
	audioh = DmGetResource(WAVTYPE, (DmResID)noiseid);
	if(audioh)
	{
		//play it async
		SndPlayResource(MemHandleLock(audioh), sndGameVolume, sndFlagAsync);	
		MemHandleUnlock(audioh);
		DmReleaseResource(audioh);					
	}
	else
	{
		ErrDisplay("In playSound(), couldn't retrieve wave file");			
	}		
}

void preloadBitmaps()
{
	//may return an error in future for error checking	
	//may call at appstartup in future instead of at the game
	
	//preload all bmps to memory windows for faster action
   DmResID id;
   UInt16 err;
   WinHandle oldW = WinGetDrawWindow();
   Coord height, width;

   //load bmps into offscreens starting at the first bmp rsc id
   for (id = 0; id < NUM_BMP_PRELOAD; id++)
   {
      //get a bmp and then draw it in custom win
      //save time by only looking at 1 database 
      if(id > 0)  	
      	preloadH[id] = DmGet1Resource(BMPTYPE, OFFSET_PRELOADBMP + id);
      else
     	 preloadH[id] = DmGetResource(BMPTYPE, OFFSET_PRELOADBMP + id);
      ErrFatalDisplayIf(!preloadH[id], "in preloadedBitmaps(), can't retrieve bmps from database");
      preloadBmp[id] = (BitmapType *) MemHandleLock(preloadH[id]);
      BmpGetDimensions(preloadBmp[id], &width, &height, NULL);	 
      preloadWindow[id] = WinCreateOffscreenWindow(width, height, nativeFormat, &err);
      ErrFatalDisplayIf(err, "in preloadedBitmaps(), can't create offscreen bitmap window");	 
       
      WinSetDrawWindow(preloadWindow[id]);
      //in future just use values with wincreate offscreen to 
      //fill in the bounds
      WinGetWindowBounds(&preloadBounds[id]);
      WinPaintBitmap(preloadBmp[id], 0, 0);
      //free and release bitmap, but keep window and rect
   	  MemHandleUnlock(preloadH[id]);
      DmReleaseResource(preloadH[id]);      
   }
   bitmapsPreloaded = true;
   
   WinSetDrawWindow(oldW);	   
}

Int32 random(Int32 maxvalue)
{
	//return random number with maxvalue - 1 being the highest	
	//sysrandommax is 32,767
	
	return SysRandom(0) / (1 + sysRandomMax / maxvalue);
}

void pauseGame()
{
	//stop the game during gameplay
	RectangleType rect;
		
	//get paused gadget bounds
	FrmGetObjectBounds(gameForm, FrmGetObjectIndex(gameForm, gamePause), &rect);	
	//draw paused graphic
	drawPreloadedBitmap(pauseBmp, rect.topLeft.x, rect.topLeft.y, winOverlay);
	
	//set state
	game.state = paused;
	gaming = false;
	//doesn't need to be erased, update game will erase it
}

void unloadBitmaps()
{
	//unload all preloaded bitmaps
   UInt8 i;
   
   for ( i = 0; i < NUM_BMP_PRELOAD; i++)
   {
   		if(preloadWindow[i])
   		{
     		destroyWin(preloadWindow[i]);
   		}	
   }
   bitmapsPreloaded = false;		
}

void newMapSegment()
{
	/*important.makes new segment. first copy top half of window
	 * to bottom and draw the map into the top half*/
	RectangleType rect;
	
	//subtract half a segment
	mapWinYOffset -= MAP_SEGMENT_EXTENT_Y / 2;	
	
	//copy top half to bottom half
	rect.topLeft.x = 0;
	rect.extent.x = MAP_SEGMENT_EXTENT_X;
	rect.topLeft.y = 0;
	rect.extent.y = MAP_SEGMENT_EXTENT_Y / 2;
	//copy top to bottom
	WinCopyRectangle(mapWin, mapWin, &rect, 0, MAP_SEGMENT_EXTENT_Y / 2, winPaint);
	//draw new top half
	drawMap(mapWinYOffset);
	//calc new objs/ai
	calcScriptCmd();
}

void updateMap()
{
	//if map is at end start repeating
	if(game.curRect.topLeft.y < MAP_END_START_REPEAT)
	{
		//need to update all bomb, bulklet, player, obj positions
		//because they depend on game.curRect		
		game.objectYOffset += MAP_END_REPEAT_Y - game.curRect.topLeft.y;
		//set currect to beginning of repeat loop
		game.curRect.topLeft.y = MAP_END_REPEAT_Y;
		//set mapWinOffset to 0
		mapWinYOffset = 0;
		//draw first half
		drawMap(0);
		//draw second half(visible one)
		drawMap(MAP_END_REPEAT_Y);
	}
	else
	{
		//set the y pos of next so that the craft has to go up some
		game.curRect.topLeft.y -= MAP_DEFAULT_PROGRESS_Y;	
	}
	
	/*wait until aircraft is past bottom segment
	 * because it will be erased when a new segment is
	 * created and the map will jump to a new place*/	
	if(game.curRect.topLeft.y < mapWinYOffset + MAP_SEGMENT_LOAD_Y_OFFSET
	   && game.objectYOffset == 0)
		newMapSegment();
}

void handleKeyHold(EventType * event)
{
	//do nothing for a key hold as it would disturb repeat key event
	//and is only sent once	
}


void handleKeyUp(EventType * event)
{
	//set key that was lifted to false

	
	//set five way to not pushed
	if(event->data.keyUp.chr == vchrNavChange)
	{
		switch(event->data.keyUp.keyCode & (navChangeBitsAll))
		{
			case navChangeUp:		
				dirPushed[up] = false;			
				break;
			case navChangeDown:		
				dirPushed[down] = false;
				break;
			case navChangeLeft:		
				dirPushed[left] = false;
				break;	
			case navChangeRight:		
				dirPushed[right] = false;
				break;	
			case navChangeSelect:		
				dirPushed[select] = false;
				break;
			default:
				//no such one
				break;							
		}		
	}
	
	//if it's a hard key
	if(TxtCharIsHardKey(event->data.keyUp.modifiers, event->data.keyUp.chr))
	{
		switch(event->data.keyUp.keyCode & keyBitsAll)
		{
			case prefs.mgKey:
				hardPushed[mgKey] = false;
				break;
			case prefs.rocketKey:
				hardPushed[rocketKey] = false;
				break;				
			case prefs.cannonKey:
				hardPushed[cannonKey] = false;
				break;
			case prefs.bombKey:
				hardPushed[bombKey] = false;
				break;
			case prefs.pauseKey:
				break;
			default:	
				//nothing
				break;	
		}		
	}
	
}

void repeatHardKey()
{
	/* repeat all currently held keys by using keystate*/
	UInt8 i;
	
	//repeat 5way
	for(i = 0; i < 5; i ++)
	{
		//if its pushed
		if(dirPushed[i])
		{
			//increase speed/time
      		dirTimeHeld[i] += game.timerValue - dirTimePushed[i];
       		if(dirSpeed[i] != STRAFE)
      		{
      			dirSpeed[i] = calcDirectionSpeed(dirTimeHeld[i]);
      		}			
		}
	}	      			
	
	//repeat hard keys
	//if the hard key was pushed 
	if(hardPushed[mgKey] && game.user.hasMg)
	{
		if(game.timerValue > hardLastAction[mgKey] + info[game.user.craft.mgType].timeout)
		{
			//shoot again
			org.x = game.user.oldpos.x;
			org.y = game.user.oldpos.y;	
			x = game.user.oldpos.x;
			y = game.user.oldpos.y - RANGE_BULLET;	
			bulletNew(x, y, org, game.user.craft.mgType, false);	
			hardLastAction[mgKey] = game.timerValue;		
		}	
	}
	if(hardPushed[rocketKey] && game.user.hasRocket)
	{
		if(game.timerValue > hardLastAction[rocketKey] + info[game.user.craft.rocketType].timeout)
		{
			//shoot again
			org.x = game.user.oldpos.x;
			org.y = game.user.oldpos.y;	
			x = game.user.oldpos.x;
			y = game.user.oldpos.y - RANGE_ROCKET;	
			bulletNew(x, y, org, game.user.craft.rocketType, false);	
			hardLastAction[rocketKey] = game.timerValue;				
		}	
	}	
	if(hardPushed[cannonKey] && game.user.hasCannon)
	{
		if(game.timerValue > hardLastAction[cannonKey] + info[game.user.craft.cannonType].timeout)
		{
			//shoot again
			org.x = game.user.oldpos.x;
			org.y = game.user.oldpos.y;	
			x = game.user.oldpos.x;
			y = game.user.oldpos.y - RANGE_CANNON;	
			bulletNew(x, y, org, game.user.craft.mgType, false);		
			hardLastAction[cannonKey] = game.timerValue;					
		}	
	}				
	if(hardPushed[bombKey] && game.user.hasBomb)
	{
		if(game.timerValue > hardLastAction[bombKey] + info[game.user.craft.bombType].timeout)
		{
			//shoot again
			org.x = game.user.oldpos.x;
			org.y = game.user.oldpos.y;	
			bombNew(org, game.user.craft.bombType);		
			hardLastAction[bombKey] = game.timerValue;					
		}	
	}	
}

void updateGame()
{
	/* this function is also important. it is called every single eventloop
	 * regardless of what happens. should be bug free. make optimisized cuz
	 * it is called maybe 10-20 times per second, depending on the frame rate
	 * should only take maybe 20 ms on a t|e. most lengthy function. 
	 * calculates any updates and draws them*/
	UInt16 i;
	
	//update screen position
	updateMap();
			
	//set draw window to update screen
	gameWin = WinSetDrawWindow(ofsWin);
	
	//do all updates and calculations here:

	//repeats held hard keys
	repeatHardKey();
	
	//calculate if a bullet has hit something
	for(i = 0; i < game.numBulletsOnScreen; i++)
	{
		//calc if one has hit anything
		calcBulletHit(&bullet[i], i);
	}
	
	//calculate new user position from input
	calcUserPos();	
		
	//calculates ai moves
	for(i = 0; i < game.numPlayersOnScreen; i++)
		calcAIMove(&player[i]);	

	//ai update positions		
	for(i = 0; i < game.numPlayersOnScreen; i++)
		updateAI(&player[i]);			
			
	//calculate bullet positions and if they are 
	//out of range, remove them	
	for(i = 0; i < game.numBulletsOnScreen; i++)	
		if(calcBulletPos(&bullet[i]))
			bulletRemove(i);
			
	for(i = 0; i < game.numBombsOnScreen; i++)
		if(calcBombPos(&bomb[i]))
		{
			calcBombHit(&bomb[i]);
			bombRemove(i);		
		}
	
	//draw everything in right drawing order/layout			
	//1.don't draw anything until map has been copied			
	copyMap();
	//2.draw all objs
	drawObjectives();
	//3.draw bombs
	drawBombs();		
	//4.draw all players	
	drawPlayers();
	//5.draw all bullets
	drawBullets();
	//6.controls may be able to be drawn every 5 frames
	drawControls();
	//7.do sound right here in future
	
	WinSetDrawWindow(gameWin); 
	//copy offsreen to the gameWindow
	WinCopyRectangle(ofsWin, gameWin, &playArea, 0, 0, winPaint);
}

void makeMapOverlay()
{
	Int16 i,k;
	UInt32 j;
	Coord x,y;
	//for drawing map
	UInt8 numBlocksPerRow;
	UInt16 numBlocksPerColumn;	
		
	//to know number of rows and columns
	numBlocksPerRow = map.mapRect.extent.x / map.blockRect.extent.x;
	numBlocksPerColumn = map.mapRect.extent.y / map.blockRect.extent.y;	
	
	//make array of rectangles
	//draws from left side down to right side down
	
	//for every block in every column(top to bottom)
	for(k = 0; k < numBlocksPerColumn; k++)
	{	
		
		//for every block in every row (side-side)
		for(i = 0; i < numBlocksPerRow; i++)
		{
			
			//x is the number of columns times width of block
			x = i * map.blockRect.extent.x;
			//y is the number of rows * width of block
			y = k * map.blockRect.extent.y;
			//j is the number of blocks drawn so far to calc what type this one is
			j = (k * numBlocksPerRow) + i;
			//make rect
			rectLayer[j].topLeft.x = x;
			rectLayer[j].topLeft.y = y;
			rectLayer[j].extent.x = map.blockRect.extent.x;
			rectLayer[j].extent.y = map.blockRect.extent.y;
		}
	}
}
