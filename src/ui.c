//ui.c- for user interface

//includes:
#include <PalmOS.h>
#include "globals.h"
#include "gameglobals"


//globals
ButtonType * button;
MemHandle buttonH;
UInt16 numButtons = 0;
Boolean uiInit;

//functions:
void diffListDraw(UInt16 itemNum, RectangleType * bounds, char ** itemsText)
{
	//draw list
	char temp[8];
	FontID oldf;
	oldf = FntSetFont(menuFont);
	
	switch(itemNum)
	{
		case 0:
			StrCopy((char *)&temp, "Easy"); 
			break;
		case 1:
			StrCopy((char *)&temp, "Medium"); 
			break;	
		case 2:
			StrCopy((char *)&temp, "Hard"); 
			break;
		default:
			break;	
	}
	
	drawText((char *)&temp, bounds->topLeft.x, bounds->topLeft.y);
	FntSetFont(oldf);
}

void mapListDraw(UInt16 itemNum, RectangleType * bounds, char ** itemsText)
{
	//draw list
	char temp[18];
	MemHandle recordH;
	MapStruct * record;
	PontType a,b;
	
	recordH = DmGetResource(MAPTYPE, MAPID + itemNum + 1);
	ErrFatalDisplayIf(!recordH, "in listdraw(), couldnt get record name");
	record = (MapStruct *)MemHandleLock(recordH);
	
	//make format = 1.xxxxxx
	StrIToA((char *)&temp, (Int32)itemNum + 1);	
	temp[1] = '.';
	StrNCopy((char *)&(temp[2]), record->name, sizeof(char) * 17);
	temp[17] = chrNull;
	
	drawText((char *)&temp, bounds->topLeft.x, bounds->topLeft.y);

	//cross out if not available
	if(itemNum >= prefs.level - 1)
	{
		a.x = bounds->topLeft.x;
		a.y = bounds->topLeft.y + (bounds->extent.y / 2);   
		b.x = bounds->topLeft.x + bounds->extent.x;
		b.y = bounds->topLeft.y + (bounds->extent.y / 2);
		WinDrawLine(a.x, a.y, b.x, b.y); 
	}	

	//unlock and release
	MemHandleUnlock(recordH);
	DmReleaseResource(recordH);
}

void sendButtonEvent(UInt16 id)
{
	EventType event;
	MemSet(&event, sizeof(EventType), 0); 
	event.eType = ctlSelectEvent; 	
	event.data.ctlSelect.controlID = id;
	
	EvtAddEventToQueue(&event);	
}

void drawButton(UInt8 i)
{
	Int16 stringWidth, stringHeight;
	FontID oldf;	
	Coord x,y;
	
	WinEraseRectangle(button[i].rect, 0);
	
	if(!customFont)
	{
		//set font
		if(button[i].pushed)
			oldf = FntSetFont(menuHighlightedFont);
		else
			oldf = FntSetFont(menuFont);	
		//figure out length/width/height	
		stringWidth = FntCharsWidth(button[i].text, StrLen(button[i].text));
		stringHeight = FntCharHeight(); 				
		//center text
		x = button[i].rect.topLeft.x;
		x += (button[i].rect.extent.x - stringWidth) / 2;
		y = button[i].rect.topLeft.y;
		y += (button[i].rect.extent.y - stringHeight) / 2;
		drawText(button[i].text, x, y);	
	}
	else
	{
		//draw pictures for letters
	}
	
	FntSetFont(oldf);		
}

void drawForm(FormType * form)
{
	FrmDrawForm(form);
	
	//draw buttons
	for(i = 0; i < numButtons; i++)
	{
		drawButton(i);	
	}	
	
}

RectangleType getObjectRect(UInt16 id)
{
	//get rectangle of object
	FormType * form;
	RectangleType rect;
	
	form = FrmGetActiveForm();
	FrmGetObjectBounds(form, FrmGetObjectIndex(form, id), &rect);	
	
	return rect;
}

void newButton(RectangleType rect, char * text, UInt16 id)
{
	//make new button
	ButtonType temp;
	Err err;
	
	temp.rect = rect;
	StrCopy(temp.text, text);
	temp.id = id;
	temp.pushed = false;
	temp.visible = true;
	
	//if there is at least one button
	if(buttonH)
	{
		ButtonType stack[numButtons];
				
		//copy into stack
		MemMove((ButtonType *)&stack, button, sizeof(ButtonType) * numButtons);
		//resize button variable to +1 sizeof(button structure)			
		err = MemHandleResize(buttonH, sizeof(ButtonType) * (numButtons + 1));
		if(err == memErrChunkLocked)
		{
			//needs to be unlocked first
			MemHandleUnlock(buttonH);
			err = MemHandleResize(buttonH, sizeof(ButtonType) * (numButtons + 1));
			ErrFatalDisplayIf(err, "In buttonNew(), error resizing button stack");
			button = (ButtonType *)MemHandleLock(buttonH);				
			
		}
		else
		{
			//resizing didnt work
			ErrDisplay("In buttonNew(), Couldn't resize button stack");			
		}
		MemMove(button, &stack, sizeof(ButtonType) * numButtons);
		numButtons++;
		button[numButtons-1] = temp;			
	}
	else
	{
		//there is no Buttons
		//make new memhandle to a button which is size of one button
		buttonH = MemHandleNew(sizeof(ButtonType));
		ErrFatalDisplayIf(!buttonH, "In ButtonNew(), Couldn't make new handle to ButtonType");
		button = (ButtonType *)MemHandleLock(buttonH);
		button[0] = temp;
	}	
	
	
}

void removeButton(UInt16 id)
{	 
	ButtonType stack[numButtons - 1];	
	UInt16 i;
	UInt8 n;
	Err err;
	
	//find right button
	for(i = 0; i < numButtons; i++)
	{
		if(button[i].id == id)
			n = i;
	}
	
	if(numButtons < 1)
	{
		ErrDisplay("In buttonRemove(), there are no buttons to remove");
	}		
	
	//move all button data to temp var:
	for(i = 0; i < n; i++)
	{
		//move each button until one to delete appears
		temp[i] = button[i];
	}
	for(i = n + 1; i < numButtons; i++)
	{
		//move each button until end
		temp[i - 1] = button[i];		
	}	
	
	//buttons are in place and top button is useless, can now resize
	//no longer need to unlock chunk
	numButtons--;	
	//resize to the number of buttons
	err = MemHandleResize(buttonH, sizeof(ButtonType) * numButtons);
	if(err == memErrChunkLocked)
	{
		//unlock
		MemHandleUnlock(buttonH);
		if(err = MemHandleResize(buttonH, sizeof(ButtonType) * numButtons))
		{	
			ErrFatalDisplay("In buttonNew, couldn't resize button stack");
		}
		button = (ButtonType *)MemHandleLock(buttonH);		 
	}		
	else if(err != 0)
	{
		//some other error
		ErrFatalDisplay("In buttonNew, couldn't resize button stack");	
	} 
	//copy orginal back to stack
	MemMove(button, (ButtonType *)&temp, sizeof(ButtonType) * numButtons);	
	
}

Boolean uiHandleEvent(EventType * event)
{
	UInt16 i;
	Coord x,y;
	Boolean handled = false;
	
	switch(event->eType)
	{
		case penDownEvent:
			x = event->screenX;
			y = event->screenY;
			for(i = 0; i < numButtons; i++)
			{
				if(RctPtInRectangle(x, y, &(button[i].rect)))
				{
					button[i].pushed = true;
					drawButton(i);	
					break;				
				}
				else
				{
					button[i].pushed = false;
				}
			}
			handled = true;
			break;
		
		case penMoveEvent:
			x = event->screenX;
			y = event->screenY;
			for(i = 0; i < numButtons; i++)
			{
				if(button[i].pushed && RctPtInRectangle(x, y, &(button[i].rect))
				{
					button[i].pushed = true;
					drawButton(i);
					break;
				}	
				else
				{
					button[i].pushed = false;
				}	
			}
			handled = true;
			break;		
		
		case penUpEvent:
			x = event->screenX;
			y = event->screenY;
			for(i = 0; i < numButtons; i++)
			{
				if(button[i].pushed && RctPtInRectangle(x, y, &(button[i].rect))
				{
					button[i].pushed = true;
					drawButton(i);
					sendButtonEvent(i);
					break;
				}	
				else
				{
					button[i].pushed = false;	
				}
			}			
			handled = true;
			break;				
	}
	
	return handled;
}