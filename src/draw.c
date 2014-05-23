//draw.c- drawing the game

#include <PalmOS.h>
#include "globals.h"
#include "gameglobals.h"
#include "MathLib.h"

//functions
Coord mapScale(Coord y)
{
	//scale to map
	return y - game.curRect.topLeft.y;
}

void drawBombs()
{
	UInt16 i;
	UInt16 bmpID;
	Coord y;
	
	//draw all onscreen bombs
	for(i = 0; i < game.numBombsOnScreen; i++)
	{
		//bmpid is the type of bomb + bombs starting position in the bmp enum
		bmpID = bInfo[bomb[i].type].bmp;	
		y = mapScale(bomb[i].nextpos.y) - game.objectYOffset;
		drawPreloadedBitmap(bmpID, bomb[i].nextpos.x, y, winOverlay);
	}	
}

void drawBullets()
{
	UInt16 i;
	UInt16 bmpID;
	Coord y;
	
	//draw all onscreen bullets
	for(i = 0; i < game.numBulletsOnScreen; i++)
	{
		//bmpid is the type of bullet + bullets starting position in the bmp enum
		bmpID = bInfo[bullet[i].type].bmp;	
		y = mapScale(bullet[i].nextpos.y) - game.objectYOffset;
		drawPreloadedBitmap(bmpID, bullet[i].nextpos.x, y, winOverlay);
	}	
}

void drawBitmap(DmResID type, Coord x, Coord y)
{	
	MemHandle bmpH;
	BitmapType * bmpP;
	WinDrawOperation oldo;
		
	oldo = WinSetDrawMode(winPaint);
	
	bmpH = DmGetResource(BMPTYPE, BMPID + type);	
	ErrFatalDisplayIf(!bmpH, "In drawBitmap(), couldn't load bitmap from database");
	bmpP = (BitmapType *) MemHandleLock(bmpH);
	WinPaintBitmap(bmpP, x, y); 		
	MemHandleUnlock(bmpH);
	DmReleaseResource(bmpH);

	WinSetDrawMode(oldo);
}

void drawControls()
{

	//draw health
	drawHealth();
	//draw lives
	drawLives();
	//draw score
	drawScore();
	
}

void drawLives()
{
	//draw number of lives let with propellor bitmap images
	
}

void drawScore()
{
	//draw score with bold green font by drawing it in 
	//window and overlaying with green rectangle	
}

void drawHealth()
{
	//set percentage in by drawing odometer style damage meter
	double percent;
	double angle;
	PointType center;
	Coord hypside;
	Coord adjside;
	Coord oppside;	
	RectangleType rect;
	Coord x,y;
	IndexedColorType org,index;
	RGBColorType color;
	
	percent = ((double)aInfo[game.user.type].orgHealth) / ((double)game.user.health);	
	angle = ((double)percent) * ((double)180); 
	angle /= 57.29578;
	
	FrmGetObjectBounds(gameForm, FrmGetObjectIndex(gameForm, gameHealth), &rect);
	
	//draw odometer picture
	drawPreloadedBitmap(damageOdometerBmp, rect.topLeft.x, mapScale(rect.topLeft.y), winOverlay);
	
	//make center bottom target of odomoter
	center.x = rect.topLeft.x + (rect.extent.x / 2);	
	center.y = rect.topLeft.y + rect.extent.y;
	
	//figure out sidelength of oldpos to start
	hypside = HEALTH_DIAMETER;
		
	//figure out side length of adj with sine to find x
	adjside = hypside * cos(angle);
		
	//calc oppside to find y position
	oppside = hypside * sin(angle);	
	
	//coords of line
	x = center.x + adjside;
	y = center.y + oppside;
	
	//dark-green color
	color.r = 17;
	color.g = 104;
	color.b = 56;
	index = WinRGBToIndex(&color);
	org = WinSetForeColor(index);
	//draw the line
	WinDrawLine(center.x, center.y, x, y);
	WinSetForeColor(org);
}

void copyMap()
{
	RectangleType copy;
	//RectangleType rect = playArea;
	//Int16 t1;
	
	//topleft of map in mapWin
	copy.topLeft.x = game.curRect.topLeft.x;
	copy.topLeft.y = game.curRect.topLeft.y - mapWinYOffset;
	copy.extent = playArea.extent;
		
	WinCopyRectangle(mapWin, NULL, &copy, 0, 0, winPaint);	

	
	/*
	//remove white space
	if(game.curRect.topLeft.y < 0)
	{
		//its negative, erase white space above
		t1 = -(game.curRect.topLeft.y);
		rect.topLeft.x = 0;
		rect.topLeft.y = 0;
		rect.extent.x = playArea.extent.x;
		rect.extent.y = t1;	
		WinEraseRectangle(&rect, 0);			
	}
	else if((game.curRect.topLeft.y + playArea.extent.y) > game.curRect.extent.y)
	{
		//there is white space under neath, erase it
		t1 = game.curRect.extent.y - game.curRect.topLeft.y;
		t1 = playArea.extent.y - t1;
		rect.topLeft.x = 0;
		rect.topLeft.y = playArea.extent.y - t1;
		rect.extent.x = playArea.extent.x;
		rect.extent.y = t1;
		WinEraseRectangle(&rect, 0);		
	}
	*/
}

void drawMap(Coord y)
{
	WinHandle org;
	UInt16 i;
	MapBmp type;
	UInt16 start;
	UInt8 numBlocksPerRow;
		
	//to know number of rows and columns
	numBlocksPerRow = map.mapRect.extent.x / map.blockRect.extent.x;
	
	//multiple blocks for every row with the current row
	start = numBlocksPerRow * (y / map.blockRect.extent.y);
		
	//double buffer
	org = WinSetDrawWindow(mapWin);

	//draw a half a segment(40 rows):	
	//for every block
	for(i = start; i < start + (numBlocksPerRow * 40) && i < map.numBlocks; i++)
	{
		type = mapData[i].type;	
		//now only draw it from database without preloading	
		drawBitmap(mapData[i].type, rectLayer[i].topLeft.x, rectLayer[i].topLeft.y);
	}	
	WinSetDrawWindow(org);	
	//call copyMap to draw to the screen
}

void drawObjectives()
{
	UInt16 i;
	UInt16 type;
	Coord x,y;

	//overlay all objectives on screen
	//draw every obj
	for(i = 0; i < game.numObjsOnScreen; i++)
	{
		//if it's within range
		if(obj[i].pos.y > (game.curRect.topLeft.y - OBJ_Y_PREPLACEMENT) 
		&& obj[i].pos.y < (game.curRect.topLeft.y + playArea.extent.y))
		{
			//draw it 
			type = obj[i].bmp;
			y = mapScale(obj[i].pos.y) - game.objectYOffset;
			x = obj[i].pos.x;
			drawPreloadedBitmap(type, x, y, winOverlay);		
		}
	}		
}

void drawPlayers()
{
	//draw user with nextpos coords
	//figure out how many enemies to draw and draw them
	UInt8 i;
	Coord y;
	
	//user 
	y = mapScale(game.user.nextpos.y) - game.objectYOffset;
	drawPreloadedBitmap(aInfo[game.user.type].bmp, game.user.nextpos.x, y, winOverlay);
	
	//draw enemies
	//enemy variable will be resized when more enemies are added
	for(i = 0; i < game.numPlayersOnScreen; i++)
	{
		y = mapScale(player[i].nextpos.y) - game.objectYOffset;		
		drawPreloadedBitmap(aInfo[player[i].type].bmp, player[i].nextpos.x, y, winOverlay);
	}
	
}

void drawPreloadedBitmap(UInt16 bmpID, Coord x, Coord y, WinDrawOperation op)
{	
	
	//simple, just copy it to screen coords
	ErrFatalDisplayIf(!preloadWindow[bmpID - 1], "in drawPreloadedBitmap(), null bmp win id");		
	//draw to the draw window
   	WinCopyRectangle(preloadWindow[bmpID - 1], mapWin, &preloadBounds[bmpID - 1], x, y, op);
}


void drawText(char * string, Coord x, Coord y)
{
	WinDrawOperation old;
	old = WinSetDrawMode(winOverlay);
	WinPaintChars(string, StrLen(string), x, y);
	WinSetDrawMode(old);	
}