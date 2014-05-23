//bullet.c, controls all bullet moves, etc

#include <PalmOS.h>
#include "globals.h"
#include "gameglobals.h"
#include "MathLib.h"

void loadBullets()
{
	//load bullets

//mg8mm
	bInfo[mg8mm].range  = RANGE_BULLET;
	bInfo[mg8mm].category = mg;
	bInfo[mg8mm].speed = SPEED_BULLET;
	bInfo[mg8mm].damage = DAMAGE_MG_8MM;
	bInfo[mg8mm].timeout = TIMEOUT_MG_8MM;
	bInfo[mg8mm].bmp = mg8mmBmp + type;	
//mg12mm	
	bInfo[mg12mm].range  = RANGE_BULLET;
	bInfo[mg12mm].category = mg;
	bInfo[mg12mm].speed = SPEED_BULLET;
	bInfo[mg12mm].damage = DAMAGE_MG_8MM;
	bInfo[mg12mm].timeout = TIMEOUT_MG_8MM;
	bInfo[mg12mm].bmp = mg8mmBmp + type;	
//mg13mm	
	bInfo[mg13mm].range  = RANGE_BULLET;
	bInfo[mg13mm].category = mg;
	bInfo[mg13mm].speed = SPEED_BULLET;
	bInfo[mg13mm].damage = DAMAGE_MG_8MM;
	bInfo[mg13mm].timeout = TIMEOUT_MG_8MM;
	bInfo[mg13mm].bmp = mg8mmBmp + type;	
//mg16mm
	bInfo[mg16mm].range  = RANGE_BULLET;
	bInfo[mg16mm].category = mg;
	bInfo[mg16mm].speed = SPEED_BULLET;
	bInfo[mg16mm].damage = DAMAGE_MG_8MM;
	bInfo[mg16mm].timeout = TIMEOUT_MG_8MM;
	bInfo[mg16mm].bmp = mg8mmBmp + type;	
//cannon20mm
	bInfo[cannon20mm].range  = RANGE_BULLET;
	bInfo[cannon20mm].category = mg;
	bInfo[cannon20mm].speed = SPEED_BULLET;
	bInfo[cannon20mm].damage = DAMAGE_MG_8MM;
	bInfo[cannon20mm].timeout = TIMEOUT_MG_8MM;
	bInfo[cannon20mm].bmp = mg8mmBmp + type;	
//mgff20mm	
	bInfo[mgff20mm].range  = RANGE_BULLET;
	bInfo[mgff20mm].category = mg;
	bInfo[mgff20mm].speed = SPEED_BULLET;
	bInfo[mgff20mm].damage = DAMAGE_MG_8MM;
	bInfo[mgff20mm].timeout = TIMEOUT_MG_8MM;
	bInfo[mgff20mm].bmp = mg8mmBmp + type;	
//rocket21cm
	bInfo[rocket21cm].range  = RANGE_BULLET;
	bInfo[rocket21cm].category = mg;
	bInfo[rocket21cm].speed = SPEED_BULLET;
	bInfo[rocket21cm].damage = DAMAGE_MG_8MM;
	bInfo[rocket21cm].timeout = TIMEOUT_MG_8MM;
	bInfo[rocket21cm].bmp = mg8mmBmp + type;	
//cannon30mm	
	bInfo[cannon30mm].range  = RANGE_BULLET;
	bInfo[cannon30mm].category = mg;
	bInfo[cannon30mm].speed = SPEED_BULLET;
	bInfo[cannon30mm].damage = DAMAGE_MG_8MM;
	bInfo[cannon30mm].timeout = TIMEOUT_MG_8MM;
	bInfo[cannon30mm].bmp = mg8mmBmp + type;	
//pL200	
	bInfo[pL200].range  = RANGE_BULLET;
	bInfo[pL200].category = mg;
	bInfo[pL200].speed = SPEED_BULLET;
	bInfo[pL200].damage = DAMAGE_MG_8MM;
	bInfo[pL200].timeout = TIMEOUT_MG_8MM;
	bInfo[pL200].bmp = mg8mmBmp + type;	
//pL500	
	bInfo[pL500].range  = RANGE_BULLET;
	bInfo[pL500].category = mg;
	bInfo[pL500].speed = SPEED_BULLET;
	bInfo[pL500].damage = DAMAGE_MG_8MM;
	bInfo[pL500].timeout = TIMEOUT_MG_8MM;
	bInfo[pL500].bmp = mg8mmBmp + type;	
//pL1000
	bInfo[pL1000].range  = RANGE_BULLET;
	bInfo[pL1000].category = mg;
	bInfo[pL1000].speed = SPEED_BULLET;
	bInfo[pL1000].damage = DAMAGE_MG_8MM;
	bInfo[pL1000].timeout = TIMEOUT_MG_8MM;
	bInfo[pL1000].bmp = mg8mmBmp + type;						
}

void calcBombHit(BombStruct * b, UInt16 bombNum)
{	 
	 UInt8 i;
	 Coord x,y;
	 RectangleType extRect;
	 UInt8 damage;
	 x = b->nextpos.x;
	 y = b->nextpos.y;	
	 	 
	 for(i = 0; i < game.numObjsOnScreen; i++)
	 {
	 	//set rectangle data to outside of obj rect
	 	extRect.topLeft.x = obj[i].nextpos.x + (preloadBounds[obj[i].bmp].extent.x / 2);
	 	extRect.topLeft.y = obj[i].nextpos.y + (preloadBounds[obj[i].bmp].extent.y / 2);
	 	extRect.topLeft.x -= preloadBounds[obj[i].bmp].extent.x;
	 	extRect.topLeft.y -= preloadBounds[obj[i].bmp].extent.y;
	 	extRect.extent.x = (preloadBounds[obj[i].bmp].extent.x * 3) / 2;
	 	extRect.extent.y = (preloadBounds[obj[i].bmp].extent.y * 3) / 2;
	 
	 	//see if the bullet's current position is in extRect
	 	if(RctPtInRectangle(x, y, &extRect))
	 	{	 		
	 		switch(b->type)
	 		{
	 			case pL200:
	 				damage = BOMB_DAMAGE_200;
	 				break;
	 			case pL500:
	 				damage = BOMB_DAMAGE_500;
	 				break;
	 			case pL1000:
	 				damage = BOMB_DAMAGE_1000;
	 				break;		
	 		}
	 		//take damage off
	 		if(obj[i].health > damage)
	 		{ 
	 			//the bullet has hit the player, take away health
	 			obj[i].health -= damage;	 			
	 		}
	 		else
	 		{
	 			//the objective is destroyed make it burn
	 			//do burning of objective animation right here
	 			removeObj(i);
	 		}
	 		
	 		//remove bullet from the bullet struct with memresize
	 		bombRemove(bombNum);
	 		break; 		
	 	}
	 	//end of for loop go to next player
	 }
	
}

void bombNew(PointType start, BombType type)
{
	BombStruct stack[game.numBombsOnScreen + 1];
	BombStruct temp;		
	Err err = true;
	
	//add new bullet info to temp
	temp.nextpos = start;
	temp.type = type;
	temp.dropTime = game.timerValue;
	switch(type)
	{
		case pL200;
			temp.bmp = bomb200pLBmp;
			break;
		case pL500:
			temp.bmp = bomb500pLBmp;
			break;
		case pL1000:
			temp.bmp = bomb1000pLBmp;
			break;
	}
	if(y > start.y)
		temp.downAngle = true;

	
	//if there is at least one bullet
	if(bombH)
	{
		//copy into stack
		MemMove((BombStruct *)&stack, bomb, sizeof(BombStruct) * game.numBombsOnScreen);
		//resize bullet variable to +1 sizeof(bullet structure)			
		err = MemHandleResize(bombH, sizeof(BombStruct) * (game.numBombsOnScreen + 1));
		if(err == memErrChunkLocked)
		{
			//needs to be unlocked first
			MemHandleUnlock(bombH);
			err = MemHandleResize(bombH, sizeof(BombStruct) * (game.numBombsOnScreen + 1));
			ErrFatalDisplayIf(err, "In bombNew(), error resizing bullet stack");
			bomb = (BombStruct *)MemHandleLock(bombH);				
			
		}
		else
		{
			//resizing didnt work
			ErrDisplay("In bombNew(), Couldn't resize bullet stack");			
		}
			
		//increase num of bomb
		game.numBombsOnScreen++;
		//move back
		MemMove(bomb, (BombStruct *)&stack, sizeof(BombStruct) * game.numBombsOnScreen - 1);		
		//set that bomb data to temp
		bullet[game.numBombsOnScreen-1] = temp;			
	}
	else
	{
		//there is no bomb
		//make new memhandle to a bullet which is size of one bullet
		bombH = MemHandleNew(sizeof(BombStruct));
		ErrFatalDisplayIf(!bombH, "In bombNew(), Couldn't make new handle to BulletStruct");
		bomb = (BombStruct *)MemHandleLock(bombH);
		game.numBombsOnScreen = 1;
		//set that bullet data to temp
		bomb[0] = temp;
	}
}

void bombRemove(UInt16 n)
{
	BombStruct bombTemp[game.numBombsOnScreen - 1];	 	
	UInt16 i;
	Err err;
	
	if(game.numBombsOnScreen < 1)
	{
		ErrDisplay("In bombRemove(), there are no bullets to remove");
	}
	
	//in future put animation of explosion right here		
	
	//move all bullet data to temp var:
	for(i = 0; i < n; i++)
	{
		//move each bullet until one to delete appears
		bombTemp[i] = bomb[i];
	}
	for(i = n + 1; i < game.numBombsOnScreen; i++)
	{
		//move each bullet until end
		bombTemp[i - 1] = bomb[i];		
	}	
	
	//bullets are in place and top bullet is useless, can now resize
	//no longer need to unlock chunk
	game.numBombsOnScreen--;	
	//resize to the number of bullets
	err = MemHandleResize(bombH, sizeof(BombStruct) * (game.numBombsOnScreen));
	if(err == memErrChunkLocked)
	{
		//unlock
		MemHandleUnlock(bulletH);
		if(err = MemHandleResize(bombH, sizeof(BombStruct) * game.numBombsOnScreen))
		{	
			ErrFatalDisplay("In bombNew, couldn't resize bullet stack");
		}
		bomb = (BombStruct *)MemHandleLock(bombH);		 
	}		
	else if(err != 0)
	{
		//some other error
		ErrFatalDisplay("In bulletNew, couldn't resize bullet stack");	
	} 
	//copy orginal back to stack
	MemMove(bomb, (BombStruct *)&bombTemp, sizeof(BombStruct) * game.numBombsOnScreen);
}

Boolean calcBombPos(BombStruct * b)
{
	/* really important. calculates next position of the bullet
	 * calculate the next position before drawing screen,
	 * uses trigonometry to figure out diagonal coords*/
	
	PointType pos;


	//see if bullet has gone past it's range:
	if(b->dropTime + BOMB_TRIGGER_TIME > game.timerValue)
	{
		//remove bullet here
		//explode it
		return true;
	}

	//just increase/decrease the y coord for movement		
	if(b->downAngle)
	{
		b->nextpos.y += BOMB_SPEED;	
	}
	else
	{
		b->nextpos.y -= BOMB_SPEED;	
	}
	
	//don't remove bullet
	return false;		
}

void calcBulletHit(BulletStruct * b, UInt16 bulletNum)
{
	/* IMPORTANT. checks if the bullet has hit something and then reports 
	 * damage to it. will first use fast method of making a 
	 * rectangle a bit larger than each player and then using
	 * rctptinrectangle(), to see if the bullet is in there.
	 * then check to see if it has touched the player more 
	 * in depth for speed. if it has touched it take some health
	 * off the player depending on what kind of bullet it was.
	 * will also in future show explosion for rocket*/
	 
	 UInt8 i;
	 Coord x,y;
	 RectangleType extRect;
	 
	 //set x coord to the middle of the bullet
	 x = b->nextpos.x + (bInfo[b->type].rect.extent.x / 2);
	 //set y coord middle
	 y = b->nextpos.y + (bInfo[b->type].rect.extent.y / 2);
	  		 
	 for(i = 0; i < game.numPlayersOnScreen; i++)
	 {
	 	//set rectangle data
	 	extRect.topLeft = player[i].nextpos;
	 	extRect.extent = aInfo[player[i].type].rect.extent;
	 
	 	//see if the bullet's current position is in extRect
	 	if(RctPtInRectangle(x, y, &extRect))
	 	{	 		
	 		//take damage off
	 		if(player[i].health > bInfo[b->type].damage)
	 		{ 
	 			//the bullet has hit the player, take away health
	 			player[i].health -= bInfo[b->type].damage;	 			
	 		}
	 		else
	 		{
	 			//the player has died, kill him
	 			removeAI(i);
	 		}	 
	 		//draw mg hit explosion graphic
	 		//remove bullet from the bullet struct with memresize
	 		bulletRemove(bulletNum);
	 		break; 		
	 	}
	 	//end of for loop go to next player
	 }	
}

void bulletNew(Coord x, Coord y, PointType start, BulletType type, Boolean multiAngle)
{
	BulletStruct stack[game.numBulletsOnScreen + 1];
	BulletStruct temp;		
	Err err = true;
	
	//add new bullet info to temp	
	//set type for info		
	temp.type = type;	
	//starting point
	temp.start = start;		
	temp.target.x = x;
	temp.target.y = y;
	temp.oldpos.x = start.x;
	temp.oldpos.y = start.y;
	temp.nextpos.x = start.x;
	temp.nextpos.y = start.y;
	temp.multiAngle = multiAngle;
	//calculate angle
	if(multiAngle)
		temp.angle = calcAngle(temp.nextpos, start, &temp);
	else
		temp.angle = 90;

	//if there is at least one bullet
	if(bulletH)
	{
		//copy into stack
		MemMove((BulletStruct *)&stack, bullet, sizeof(BulletStruct) * game.numBulletsOnScreen);
		//resize bullet variable to +1 sizeof(bullet structure)			
		err = MemHandleResize(bulletH, sizeof(BulletStruct) * (game.numBulletsOnScreen + 1));
		if(err == memErrChunkLocked)
		{
			//needs to be unlocked first
			MemHandleUnlock(bulletH);
			err = MemHandleResize(bulletH, sizeof(BulletStruct) * (game.numBulletsOnScreen + 1));
			ErrFatalDisplayIf(err, "In bulletNew(), error resizing bullet stack");
			bullet = (BulletStruct *)MemHandleLock(bulletH);				
			
		}
		else
		{
			//resizing didnt work
			ErrDisplay("In bulletNew(), Couldn't resize bullet stack");			
		}
			
		//increase num of bullets
		game.numBulletsOnScreen++;
		//move back
		MemMove(bullet, (BulletStruct *)&stack, sizeof(BulletStruct) * game.numBulletsOnScreen - 1);		
		//set that bullet data to temp
		bullet[game.numBulletsOnScreen-1] = temp;			
	}
	else
	{
		//there is no bullet
		//make new memhandle to a bullet which is size of one bullet
		bulletH = MemHandleNew(sizeof(BulletStruct));
		ErrFatalDisplayIf(!bulletH, "In bulletNew(), Couldn't make new handle to BulletStruct");
		bullet = (BulletStruct *)MemHandleLock(bulletH);
		game.numBulletsOnScreen = 1;
		//set that bullet data to temp
		bullet[0] = temp;
	}
}

void bulletRemove(UInt16 n)
{
	BulletStruct bulletTemp[game.numBulletsOnScreen - 1];	 	
	UInt16 i;
	Err err;
	
	if(game.numBulletsOnScreen < 1)
	{
		ErrDisplay("In bulletRemove(), there are no bullets to remove");
	}		
	
	//move all bullet data to temp var:
	for(i = 0; i < n; i++)
	{
		//move each bullet until one to delete appears
		bulletTemp[i] = bullet[i];
	}
	for(i = n + 1; i < game.numBulletsOnScreen; i++)
	{
		//move each bullet until end
		bulletTemp[i - 1] = bullet[i];		
	}	
	
	//bullets are in place and top bullet is useless, can now resize
	//no longer need to unlock chunk
	game.numBulletsOnScreen--;	
	//resize to the number of bullets
	err = MemHandleResize(bulletH, sizeof(BulletStruct) * (game.numBulletsOnScreen));
	if(err == memErrChunkLocked)
	{
		//unlock
		MemHandleUnlock(bulletH);
		if(err = MemHandleResize(bulletH, sizeof(BulletStruct) * game.numBulletsOnScreen))
		{	
			ErrFatalDisplay("In bulletNew, couldn't resize bullet stack");
		}
		bullet = (BulletStruct *)MemHandleLock(bulletH);		 
	}		
	else if(err != 0)
	{
		//some other error
		ErrFatalDisplay("In bulletNew, couldn't resize bullet stack");	
	} 
	//copy orginal back to stack
	MemMove(bullet, (BulletStruct *)&bulletTemp, sizeof(BulletStruct) * game.numBulletsOnScreen);
}

Boolean calcBulletPos(BulletStruct * b)
{
	/* really important. calculates next position of the bullet
	 * calculate the next position before drawing screen,
	 * uses trigonometry to figure out diagonal coords*/
	
	PointType pos;
	double hypside;
	double adjside;
	double oppside;
	double angle;


	//see if bullet has gone past it's range:
	if(b->distance > bInfo[b->type].range)
	{
		//remove bullet here
		return true;
	}
	
	if(b->multiAngle)
	{
		//figure out sidelength of oldpos to start
		hypside = distance(b->start, b->oldpos);
		hypside += bInfo[b->type].speed;
		
		angle = 57.29578 / b->angle;
		
		//figure out side length of adj with sine to find x
		adjside = hypside * cos(angle);
		
		//calc oppside to find y position
		oppside = hypside * sin(angle);
		
		pos.x = b->oldpos.x;
		pos.y = b->oldpos.y;
		
		//if angle is going left then subtract x
		if(b->reverseAngle)
		{
			 pos.x -= adjside;
		}
		else
		{
			pos.x += adjside;	
		}
		//if its down add y coord
		if(b->downAngle)
		{
			pos.y += oppside;
		}
		else
		{
			pos.y -= oppside;	
		}
			
		//set next pos of bullet 
		b->nextpos = pos;
	}
	else
	{
		//just increase/decrease the y coord for movement	
		b->nextpos = b->oldpos;		
		if(b->downAngle)
		{
			b->nextpos.y += bInfo[b->type].speed;	
		}
		else
		{
			b->nextpos.y -= bInfo[b->type].speed;	
		}
	}
	
	//increase distance travelled
	b->distance += bInfo[b->type].speed;
	
	//don't remove bullet
	return false;		
}
