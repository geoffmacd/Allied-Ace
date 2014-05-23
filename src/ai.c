//ai.c - controls computer controlled choppers

#include <PalmOS.h>
#include "globals.h"
#include "gameglobals.h"

//functions
void loadAircraft()
{
	//load craft info	
	
	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0].x = 10;
	aInfo[bf109].mgPt[0].y = 6;
	aInfo[bf109].mgPt[1].x = 22;
	aInfo[bf109].mgPt[1].y = 6;
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt.x = 16;
	aInfo[bf109].cannonPt.y = 2;
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;		
	

	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0].x = 10;
	aInfo[bf109].mgPt[0].y = 6;
	aInfo[bf109].mgPt[1].x = 22;
	aInfo[bf109].mgPt[1].y = 6;
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt.x = 16;
	aInfo[bf109].cannonPt.y = 2;
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;	
	
	
	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0] = {10,6};
	aInfo[bf109].mgPt[1] = {22,6};
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt = {16,2};
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;	
	

	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0] = {10,6};
	aInfo[bf109].mgPt[1] = {22,6};
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt = {16,2};
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;	
	
	
	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0] = {10,6};
	aInfo[bf109].mgPt[1] = {22,6};
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt = {16,2};
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;					
	

	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0] = {10,6};
	aInfo[bf109].mgPt[1] = {22,6};
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt = {16,2};
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;	
	
	
	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0] = {10,6};
	aInfo[bf109].mgPt[1] = {22,6};
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt = {16,2};
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;	
	

	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0] = {10,6};
	aInfo[bf109].mgPt[1] = {22,6};
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt = {16,2};
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;	
	
	
	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0] = {10,6};
	aInfo[bf109].mgPt[1] = {22,6};
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt = {16,2};
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;	
	

	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0] = {10,6};
	aInfo[bf109].mgPt[1] = {22,6};
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt = {16,2};
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;	
	
	
	aInfo[bf109].bmp = bf109Bmp;	
	//mg info
	aInfo[bf109].hasMg = true;
	aInfo[bf109].doubleMg = true;
	aInfo[bf109].mgType = mg8mm;
	aInfo[bf109].mgPt[0] = {10,6};
	aInfo[bf109].mgPt[1] = {22,6};
	//cannon info
	aInfo[bf109].hasCannon = true;	
	aInfo[bf109].cannonType = cannon20mm;
	aInfo[bf109].cannonPt = {16,2};
	//rocket info
	aInfo[bf109].hasRocket = false;
	//rear mg info
	aInfo[bf109].hasRearMg = false;
	//for bombs
	aInfo[bf109].hasBomb = false;
	//for ai if shooting alot		
	aInfo[bf109].bursting = false;	
	//orignal health/armour
	aInfo[bf109].orgHealth = HEALTH_bf109;				
}

Boolean cmdIsAI(ObjectiveType type)
{
	//see what type of cmd it is
	switch(type)
	{
		case spitfire:
		case hurricane:
		case p51d:
		case yak9:
		case bf109:
		case ju87:
		case me110:
		case fw190:
		case zero:
		case me262:
			return true;
	}
	return false;
}


void sortScript()
{
	//this saves dynamic space
	UInt16 i, k, size;
	Err err;
	ScriptType temp[map.numCmds];
	
	//get rid of all map cmds
	for(i = 0; i < map.numCmds; i++)
	{
		if(!cmdIsAI(script[i].type))
		{
			//copy next cmd into this one if there is			
			for(k = i; k < map.numCmds;k++)
			{
				//if there is a cmd left
				if(k != (map.numCmds - 1))
				{
					//if it still isn't ai then continue
					if(!cmdIsAI(script[k + 1].type))
					{
						continue;
					}
					else
					{
						//copy it into new, discard old
						MemMove(&temp[i], &script[k + 1], sizeof(ScriptType));						
						size++;
						//get out of loop
						break;
					}	
				}
			}
		}	
		//leave it if it is an ai	
	}	
	
	//resize script to value of size
	err = MemHandleResize(scriptH, sizeof(ScriptType) * size);
	if(err == memErrChunkLocked)
	{
		//unlock
		MemHandleUnlock(scriptH);
		if(err = MemHandleResize(scriptH, sizeof(ScriptType) * size))
		{
			ErrFatalDisplay("In sortscript, couldn't resize script");
		}
		script = (ScriptType *)MemHandleLock(scriptH);		 
	}		
	else if(err != 0)
	{
		//some other error
		ErrFatalDisplay("In sortscript, couldn't resize script");	
	}	
	
	//move all script into new one
	MemMove(script, &temp, sizeof(ScriptType) * size);
}

void addObjective(ObjectiveType type, PointType pos)
{
	/* adds a member to be controlled by computer.
	 * needs revision*/ 
	ObjStruct stack[game.numObjsOnScreen]; 
	ObjStruct temp;
	
	temp.type = type;
	temp.pos = pos;
	
	switch(type)
	{
		case munitionsObj:
			temp.bmp = munitionsBmp;
			temp.health = OBJ_HEALTH_MAJOR;
			break;
		case coalplantObj:
			temp.bmp = coalplantBmp;
			temp.health = OBJ_HEALTH_MAJOR;
			break;
		case v2Obj:
			temp.bmp = v2Bmp;
			temp.health = OBJ_HEALTH_MAJOR;
			break;
		case aagunObj:
			temp.bmp = aagunBmp;
			temp.health = OBJ_HEALTH_MINOR;
			break;
		case art88mmObj:
			temp.bmp = art88mmBmp;
			temp.health = OBJ_HEALTH_MEDIUM;
			break;
		case howitzersObj:
			temp.bmp = howitzersBmp;
			temp.health = OBJ_HEALTH_MINOR;
			break;
		case radarstationObj:
			temp.bmp = radarstationBmp;
			temp.health = OBJ_HEALTH_MEDIUM;
			break;
		case panzersObj:
			temp.bmp = panzersBmp;
			temp.health = OBJ_HEALTH_MINOR;
			break;
		case kingtigersObj:
			temp.bmp = kingtigersBmp;
			temp.health = OBJ_HEALTH_MEDIUM;
			break;
		case bunkerObj:
			temp.bmp = bunkerBmp;
			temp.health = OBJ_HEALTH_MINOR;
			break;
	}
	
	
	//if there is at least one ai
	if(objH)
	{
		//resize player variable to +1 sizeof(player structure)	
		Err err = true;	
		
		//move data from stack to temp
		MemMove(&stack, obj, sizeof(ObjStruct) * game.numObjsOnScreen);
			
		err = MemHandleResize(objH, sizeof(ObjStruct) * (game.numObjsOnScreen + 1));
		if(err == memErrChunkLocked)
		{
			//needs to be unlocked first
			MemHandleUnlock(objH);
			err = MemHandleResize(objH, sizeof(ObjStruct) * (game.numObjsOnScreen + 1));
			ErrFatalDisplayIf(err, "In addAI(), error resizing player stack");
			obj = (ObjStruct *)MemHandleLock(objH);			
		}
		else
		{
			//resizing didnt work
			ErrDisplay("In addAI(), Couldn't resize player stack");			
		}
		
		//didn't need to unlock		
		MemMove(obj, &stack, sizeof(ObjStruct) * game.numObjsOnScreen);
		game.numObjsOnScreen++;
		//set that player data to temp
		obj[game.numObjsOnScreen-1] = temp;		
	}
	else
	{
		//there is no players at all
		//make new memhandle to a player which is size of one player
		objH = MemHandleNew(sizeof(ObjStruct));
		ErrFatalDisplayIf(!objH, "In addAI(), Couldn't make new handle to PlayerStruct");
		obj = (ObjStruct *)MemHandleLock(objH); 
		game.numObjsOnScreen = 1;
		//set that player data to temp
		obj[0] = temp;
	}	
}

void addAI(PlayerType type, PointType firstPos)
{
	/* adds a member to be controlled by computer.
	 * needs revision*/ 
	PlayerStruct stack[game.numPlayersOnScreen]; 
	PlayerStruct temp;
	
	//set type for info
	temp.type = type;
	//set position
	temp.health = aInfo[type].orgHealth;
	temp.oldpos = firstPos;
	temp.nextpos = firstPos;
	temp.dirSpeed[left]= 0;
	temp.dirSpeed[right]= 0;	
	temp.dirSpeed[down]= 0;	
	temp.dirSpeed[up]= 0;	
	temp.dirSpeed[select]= 0;		
	
	//if there is at least one ai
	if(playerH)
	{
		//resize player variable to +1 sizeof(player structure)	
		Err err = true;	
		
		//move data from stack to temp
		MemMove(&stack, player, sizeof(PlayerStruct) * game.numPlayersOnScreen);
			
		err = MemHandleResize(playerH, sizeof(PlayerStruct) * (game.numPlayersOnScreen + 1));
		if(err == memErrChunkLocked)
		{
			//needs to be unlocked first
			MemHandleUnlock(playerH);
			err = MemHandleResize(playerH, sizeof(PlayerStruct) * (game.numPlayersOnScreen + 1));
			ErrFatalDisplayIf(err, "In addAI(), error resizing player stack");
			player = (PlayerStruct *)MemHandleLock(playerH);			
		}
		else
		{
			//resizing didnt work
			ErrDisplay("In addAI(), Couldn't resize player stack");			
		}
		
		//didn't need to unlock		
		MemMove(player, &stack, sizeof(PlayerStruct) * game.numPlayersOnScreen);
		game.numPlayersOnScreen++;
		//set that player data to temp
		player[game.numPlayersOnScreen-1] = temp;		
	}
	else
	{
		//there is no players at all
		//make new memhandle to a player which is size of one player
		playerH = MemHandleNew(sizeof(PlayerStruct));
		ErrFatalDisplayIf(!playerH, "In addAI(), Couldn't make new handle to PlayerStruct");
		player = (PlayerStruct *)MemHandleLock(playerH); 
		game.numPlayersOnScreen = 1;
		//set that player data to temp
		player[0] = temp;
	}	
}

void updateAI(PlayerStruct * ai)
{
	/* extremely important. moves user depending on what keys 
	 * are pressed. may be wrong or too slow/fast.*/
	PointType * old = &(ai->oldpos);
	PointType * next = &(ai->nextpos);
	

	//if turing left	
	if(dirSpeed[left] && old->x > game.curRect.topLeft.x)
	{
		//subtract x coord to move left				
		next->x -= dirSpeed[left];
	}
	//if right point isnt past right x of map
	if(dirSpeed[right] && old->x + aInfo[ai->type].rect.extent.x
	< game.curRect.topLeft.x + game.curRect.extent.x)
	{
		//move right
		next->x += dirSpeed[right];
	}
	//if its up and user isnt above maximum line
	if(dirSpeed[up] && old->y > game.curRect.topLeft.y - game.objectYOffset)
	{
		//move up a bit, although the screen is already moved up
		next->y -= dirSpeed[up];	
	} 
	//if  its down and the user isn't below the actual screen
	if(dirSpeed[down] && old->y < game.curRect.topLeft.y - game.objectYOffset + playArea.extent.y)
	{
		//move down a little
		next->y += dirSpeed[down];		
	} 
			
	//set the y pos of next so has to go up
	next->y -= MAP_DEFAULT_PROGRESS_Y;	
	*old = *next;	
}

Coord calcAIBulletPosition(Difficulty diff, Boolean xcoord)
{
	Coord x,y;
	

}

void calcAIMove(PlayerStruct * ai)
{	
	/* complicated function that calculates ai moves.
	 * first calcuates shooting. ai attacks should be on diff difficulties:
	 * 
	 * easy:
	 * -ai takes long to find user's x coord
	 * -hesitates sometimes in shots
	 * -shoots off target often
	 * -collides with other ai occasionally
	 * -slow speed, not mobile
	 * 
	 * medium:
	 * -ai can put the user on target within a reasonable amount of time
	 * -hesitates once in awhile
	 * -fast speed, mobile
	 * -rarely collides with other ai
	 * -sometimes shoots off target
	 * 
	 * hard(ace):
	 * -ai always manages to put the user in it's target
	 * -rarely hesitates
	 * -fastest speed, very agile
	 * -never collides
	 * -sometimes shoots off target */
	UInt16 distance;
	Coord x,y;
	
	//calculate the pos of an enemy
	switch(prefs.difficulty)
	{
		case easy:
easy:		//calculate easy enemy

			//calculate where to move to or stay still
			calcAIPos(ai, easy);			
			break;	
		
		case medium:
medium:		//calculate medium enemy

			//calculate where to move to or stay still
			calcAIPos(ai, medium);	
			break;
		
		case hard:
hard:		//calculate hard enemy

			//calculate where to move to or stay still
			calcAIPos(ai, hard);				
			break;
			
		default:
			break;	
	}	
	
}

void calcAIPos(PlayerStruct * ai, Difficulty diff)
{
	/* this function calculates	where to move the ai to.
	 * the ai cannot chnage directions rapidly, it must be going
	 * a particular way for the delay before it can change direction
	 * make sure to calc x and y positions. make the ai move closer
	 * to the user and further away on hard. make sure to just go
	 * back and fourth on easy and add some turns in medium*/


	//set the y pos of next so that ai has to go down at half user goes up
	ai->nextpos.y += (MAP_DEFAULT_PROGRESS_Y / 2);	
	//set new to old
	ai->oldpos = ai->nextpos;
}

void calcScriptCmd()
{
	/* intreprets any command out of the cmd stack pointer. shouldn't take too
	 * much processing time*/
	 UInt16 i;
	 PointType pos;
	 
	 for(i = 0; i < map.numCmds; i++)
	 {
	 	//if y coord of obj is in second segment of mapWin just created
		if(script[i].y > (mapWinYOffset) 
		&& script[i].y < (mapWinYOffset + (MAP_SEGMENT_EXTENT_Y / 2)))
		{
			if(cmdIsAI(script[i].type))
			{
				//place ai
				pos.x = script[i].x;
				pos.y = script[i].y;
				//minus 5 to get playertype value
				addAI((PlayerType)script[i].type - 5, pos);
			}
			else
			{	
				//place stationary objective
				pos.x = script[i].x;
				pos.y = script[i].y;
				addObjective(script[i].type, pos);
			}
		}
	 }
}

void removeObj(UInt8 objNum)
{
	ObjStruct objTemp[game.numObjsOnScreen - 1];	 	
	UInt16 i;
	Err err;
	
	if(game.numObjsOnScreen < 1)
	{
		ErrDisplay("In removeAI(), there are no players to remove");
	}		
	
	//move all player data to temp var:
	for(i = 0; i < objNum; i++)
	{
		//move each player until one to delete appears
		objTemp[i] = obj[i];
	}
	for(i = objNum + 1; i < game.numObjsOnScreen; i++)
	{
		//move each player until end
		objTemp[i - 1] = obj[i];		
	}	
	
	//players are in place and top player is useless, can now resize
	game.numObjsOnScreen--;	
	//resize to the number of players
	err = MemHandleResize(objH, sizeof(ObjStruct) * (game.numObjsOnScreen));
	if(err == memErrChunkLocked)
	{
		//unlock
		MemHandleUnlock(objH);
		if(err = MemHandleResize(objH, sizeof(ObjStruct) * game.numObjsOnScreen))
		{	
			ErrFatalDisplay("In removeAI, couldn't resize player stack");
		}
		obj = (ObjStruct *)MemHandleLock(objH);		 
	}		
	else if(err != errNone)
	{
		//some other error
		ErrFatalDisplay("In removeAI, couldn't resize player stack");	
	} 
	//copy orginal back to stack
	MemMove(obj, (ObjStruct *)&objTemp, sizeof(ObjStruct) * game.numObjsOnScreen);	
}

void removeAI(UInt8 aiNum)
{
	PlayerStruct playerTemp[game.numPlayersOnScreen - 1];	 	
	UInt16 i;
	Err err;
	
	if(game.numPlayersOnScreen < 1)
	{
		ErrDisplay("In removeAI(), there are no players to remove");
	}		
	
	//move all player data to temp var:
	for(i = 0; i < aiNum; i++)
	{
		//move each player until one to delete appears
		playerTemp[i] = player[i];
	}
	for(i = aiNum + 1; i < game.numPlayersOnScreen; i++)
	{
		//move each player until end
		playerTemp[i - 1] = player[i];		
	}	
	
	//players are in place and top player is useless, can now resize
	game.numPlayersOnScreen--;	
	//resize to the number of players
	err = MemHandleResize(playerH, sizeof(PlayerStruct) * (game.numPlayersOnScreen));
	if(err == memErrChunkLocked)
	{
		//unlock
		MemHandleUnlock(playerH);
		if(err = MemHandleResize(playerH, sizeof(PlayerStruct) * game.numPlayersOnScreen))
		{	
			ErrFatalDisplay("In removeAI, couldn't resize player stack");
		}
		player = (PlayerStruct *)MemHandleLock(playerH);		 
	}		
	else if(err != errNone)
	{
		//some other error
		ErrFatalDisplay("In removeAI, couldn't resize player stack");	
	} 
	//copy orginal back to stack
	MemMove(player, (PlayerStruct *)&playerTemp, sizeof(PlayerStruct) * game.numPlayersOnScreen);	
}