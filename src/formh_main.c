//main.c - starts application up and initializes all necessary variables

#include <PalmOS.h>
#include "globals.h"
#include "bitmaps.h"

//functions:
void eraseMenuSelection(int select)
{

	FontID oldf = FntSetFont(menuHighlightedFont);				
	WinEraseChars((char *)&menu.selections[select], StrLen(menu.selections[select]), menu.labels[select].topLeft.x, menu.labels[select].topLeft.y);
	FntSetFont(oldf);		
}

void menuInit()
{	
	Err err;
	//get menu selections
	//draw selections and bitmap background	

	//StrCopy((char *) &menu.selections[0], menuNewGame);
	//StrCopy((char *) &menu.selections[1], menuContinueGame);
	//StrCopy((char *) &menu.selections[2], menuOptions);
	//StrCopy((char *) &menu.selections[3], menuExit);
	newButton(getObjectRect(menuSelect1), menuNewGame, menuSelect1);
	newButton(getObjectRect(menuSelect2), menuContinueGame, menuSelect2);
	newButton(getObjectRect(menuSelect3), menuOptions, menuSelect3);
	newButton(getObjectRect(menuSelect4), menuExit, menuSelect4);
			
	ofsWin = WinCreateOffscreenWindow(GAMEPLAY_EXTENT_X, GAMEPLAY_EXTENT_Y, genericFormat, (UInt16 *)&err);			
	ErrFatalDisplayIf(err != errNone, "In loadGame(), couldn't allocate large enough window (not enough dynamic memory)");		

	//paint back ground
	drawPreloadedBitmap(menuBackBmp, 0, 0, winPaint);
	
	//draw menu selection	
	//drawMenuSelection();	
	
	uiInit = true;			
}

void drawMenuSelection(int forget)
{
	//needs work
	int i;
	Coord y;
	Coord x;
	WinDrawOperation oldo;
	FontID oldf = FntSetFont(menuFont);
	FormType * form;

	form = FrmGetActiveForm();
	oldo = WinSetDrawMode(winOverlay);
		
	if(forget != 0)
	{
	FrmGetObjectBounds(form, FrmGetObjectIndex(form, menuSelect1), &menu.labels[0]);			
	WinPaintChars((char *)&menu.selections[0], StrLen(menu.selections[0]), x, y);		
	}	
	if(forget != 1)
	{
	FrmGetObjectBounds(form, FrmGetObjectIndex(form, menuSelect2), &menu.labels[1]);			
	WinPaintChars((char *)&menu.selections[1], StrLen(menu.selections[1]), x, y);		
	}
	if(forget != 2)
	{
	FrmGetObjectBounds(form, FrmGetObjectIndex(form, menuSelect3), &menu.labels[2]);			
	WinPaintChars((char *)&menu.selections[2], StrLen(menu.selections[2]), x, y);		
	}
	if(forget != 3)
	{
	FrmGetObjectBounds(form, FrmGetObjectIndex(form, menuSelect4), &menu.labels[3]);			
	WinPaintChars((char *)&menu.selections[3], StrLen(menu.selections[3]), x, y);		
	}
	
	WinSetDrawMode(oldo);
	FntSetFont(oldf);
}

void menuHighlight(int highlightIndex, Boolean highlight)
{
	FontID oldf;
	WinHandle org;
	RectangleType r;
	WinDrawOperation oldo;

	//create double buffering
	org = WinSetDrawWindow(ofsWin);
	drawPreloadedBitmap(menuBackBmp, 0, 0, winPaint);	
	
	//if its highlighted	
	if(highlight)
	{				

		drawMenuSelection(highlightIndex);
		oldo = WinSetDrawMode(winOverlay);
		oldf = FntSetFont(menuHighlightedFont);	
		WinPaintChars((char *)&menu.selections[highlightIndex], StrLen(menu.selections[highlightIndex]), menu.labels[highlightIndex].topLeft.x, menu.labels[highlightIndex].topLeft.y);		
		FntSetFont(oldf);
		WinSetDrawMode(oldo);

		menu.pressed[highlightIndex] = true;
	}
	else
	{		
		eraseMenuSelection(highlightIndex);	
		//just draw menu	
		drawMenuSelection();
	}	
				
	WinGetBounds(ofsWin, &r);		
	WinCopyRectangle(ofsWin, org, &r, 0, 0, winPaint);	
	WinSetDrawWindow(org);	
}

void doMenuAction(int command)
{	
	//do menu action
	switch(command)
	{	
		case 0:
			//goto new game
			//FrmGotoForm(NewGameForm);
			break;

		case 1:
			//goto continue game
			resuming = true;
			FrmGotoForm(GameForm);
			break;
			
		case 2:
			//options form
			//FrmGotoForm(OptionsForm);
			break;
			
		case 3:
			//exit
			break;
			
		default:	
			ErrDisplay("No such menu action");
			break;						
	}
}


Boolean MainFormHandleEvent(EventType * event)
{
	Boolean handled = false;
	Coord x,y;
	//Boolean pointed = false;
	//int i;
	FormType * form;

	
	switch(event->eType){
		
		case frmOpenEvent:
			form = FrmGetActiveForm();
			menuInit();				
			drawForm(form);
			handled = true;
			break;
			
	  /*case penDownEvent:
			//if pen is in rectangle of label highlight it and mark it as being pressed
			x = event->screenX;
			y = event->screenY;
			for(i = 1; i < 5; i++)
			{
				pointed = RctPtInRectangle(x, y, &menu.labels[i-1]);
				if(pointed)
				{
					//unhighlight others
					if(highlighted > 0)
						menuHighlight(highlighted - 1, false);
					highlighted = i;					
					menuHighlight(highlighted-1, true);

				}	
				else
				{
					keyed = false;
				}
				break;	
			}
			handled = true;
			break;
			
		case penUpEvent:
			//if pen lifts over a label and that label was being pressed do the action of it
			x = event->screenX;
			y = event->screenY;
			
			if(highlighted >= 1)
			{ 
				pointed = RctPtInRectangle(x, y, &menu.labels[highlighted-1]);
				if(pointed)
				{				
					doMenuAction(highlighted-1);
				}
				else
				{
					//unhighlight it
					menuHighlight(highlighted-1, false);
					keyed = false;
				}	
				highlighted = 0;
			}
			handled = true;
			break;*/
			
		case ctlSelectEvent:
			switch(event->data.ctlSelect.controlID)
			{
				case menuSelect1: 
					doMenuAction(0);
					break;	
				case menuSelect2: 
					doMenuAction(1); 
					break;		
				case menuSelect3: 
					doMenuAction(2); 
					break;	
				case menuSelect4:  
					doMenuAction(3);
					break;											
			}	
				
			/*//scroll through selection
			if(keyed = false)
			{
				highlighted = 1;
				menuHighlight(highlighted-1, true);
				keyed = true;
				handled = true;
				break;
			}
							
			switch(event->data.keyDown.chr)
			{
				case vchrPageUp:
					menuHighlight(highlighted-1, false);
					if(highlighted < 2)
						highlighted = 4;
					else
						highlighted -= 1;
					menuHighlight(highlighted-1, true);	
					break;
						
				case vchrPageDown:
					menuHighlight(highlighted-1, false);				
					if(highlighted >= 4)
						highlighted = 1;
					else
						highlighted++;	
					menuHighlight(highlighted-1, true);					
					break;	
						
				default:
					break;	
				
			}*/
			handled = true;
			break;
			
		case frmCloseEvent:
			uiInit = false;
			WinDeleteWindow(ofsWin, false);			
			removeButton(menuSelect1);
			removeButton(menuSelect2);
			removeButton(menuSelect3);
			removeButton(menuSelect4);
			handled = false;
			break;		
			
		default:
			break;				
	}
	return handled;
}
