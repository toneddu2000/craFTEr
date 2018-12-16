/*
MIT License

Copyright (c) 2018 Antonio "toneddu2000" Latronico

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

void CUI_ListDownClick(entity subject)
{
	local float barstep = subject.cuiDim_y / subject.cuiListTotal;
	
	if(subject.cuiListIndex > 0){
		subject.cuiListIndex--;
		
	}
	if(subject.cuiListBarPosY > subject.cuiCoords_y+barstep){
		subject.cuiListBarPosY-=barstep;
		subject.cuiListCanGoDown = FALSE;
	}
	if(subject.cuiListBarPosY <= subject.cuiCoords_y+barstep){
		if(subject.cuiListTextIndex>0 && subject.cuiListCanGoUp == TRUE){
			subject.cuiListTextIndex--;
		}
		if(subject.cuiListBarPosY == subject.cuiCoords_y+barstep){
			subject.cuiListCanGoUp = TRUE;
		}
	}
	//uiListText = subject.cuiListTextArray[subject.cuiListIndex];
}

void CUI_ListUpClick(entity subject)
{
	local float barstep = subject.cuiDim_y / subject.cuiListTotal;
	
	if(subject.cuiListTextArray[subject.cuiListIndex+1] != ""){
		subject.cuiListIndex++;
	}
	if(subject.cuiListBarPosY < subject.cuiCoords_y+subject.cuiDim_y){
		subject.cuiListBarPosY+=barstep;
		subject.cuiListCanGoUp = FALSE;
	}
	if(subject.cuiListBarPosY >= subject.cuiCoords_y+subject.cuiDim_y){
		if(subject.cuiListTextIndex< UI_LIST_ELEM_TOTAL && subject.cuiListCanGoDown == TRUE){
			subject.cuiListTextIndex++;
		}
		if(subject.cuiListBarPosY == subject.cuiCoords_y+subject.cuiDim_y){
			subject.cuiListCanGoDown = TRUE;
		}
	}
	//uiListText = subject.cuiListTextArray[subject.cuiListIndex];
		/*
		if(subject.cuiListIndex < 8){
			subject.cuiListBarPosY+=barstep;
		}
		*/
	
}

void CUI_HoverOn(entity subject)
{
	if(subject.cuiClass == CUI_CLASS_BUTTON){
		subject.cuiBgCol = UI_HOVER_COLOR;
		subject.cuiAlpha = 1;
	}
}

void CUI_HoverOff(entity subject)
{
	if(subject.cuiClass == CUI_CLASS_BUTTON && subject.cuiActive == FALSE){
		subject.cuiBgCol = subject.cuiBgColOld;
		subject.cuiAlpha = subject.cuiAlphaOld;
	}
}

void CUI_Hover(entity subject)
{
	local float xaxis = subject.cuiCoords_x + subject.cuiDim_x;
	local float yaxis = subject.cuiCoords_y + subject.cuiDim_y;
	
	if(inputCursor == TRUE && subject.cuiClass == CUI_CLASS_BUTTON){
		if(inputCursorOrigin_x < xaxis && inputCursorOrigin_x > subject.cuiCoords_x && inputCursorOrigin_y < yaxis && inputCursorOrigin_y > subject.cuiCoords_y){
			CUI_HoverOn(subject);
		}
		else{
			CUI_HoverOff(subject);
		}
	}
}

void CUI_EvMouseReleased(entity subject)
{
	local float xaxis = subject.cuiCoords_x + subject.cuiDim_x;
	local float yaxis = subject.cuiCoords_y + subject.cuiDim_y;
	local float dwaxisx,dwaxisy,upaxisx,upaxisy,okaxisx,okaxisy,cancelaxisx,cancelaxisy;
	
	if(inputCursor){
		if(inputCursorOrigin_x < xaxis && inputCursorOrigin_x > subject.cuiCoords_x && inputCursorOrigin_y < yaxis && inputCursorOrigin_y > subject.cuiCoords_y){
			//avoid click other cui elements on different cuiVis
			if(subject.cuiClicked){
				if(subject.cuiClass == CUI_CLASS_BUTTON){
					subject.cuiOnRelease();
				}
				if(subject.cuiClass == CUI_CLASS_LIST){
					//set coords of list children elem
					dwaxisx = subject.cuiChildLsDown.cuiCoords_x + subject.cuiChildLsDown.cuiDim_x;
					dwaxisy = subject.cuiChildLsDown.cuiCoords_y + subject.cuiChildLsDown.cuiDim_y;
					upaxisx = subject.cuiChildLsUp.cuiCoords_x + subject.cuiChildLsUp.cuiDim_x;
					upaxisy = subject.cuiChildLsUp.cuiCoords_y + subject.cuiChildLsUp.cuiDim_y;
					okaxisx = subject.cuiChildLsOk.cuiCoords_x + subject.cuiChildLsOk.cuiDim_x;
					okaxisy = subject.cuiChildLsOk.cuiCoords_y + subject.cuiChildLsOk.cuiDim_y;
					cancelaxisx = subject.cuiChildLsCancel.cuiCoords_x + subject.cuiChildLsCancel.cuiDim_x;
					cancelaxisy = subject.cuiChildLsCancel.cuiCoords_y + subject.cuiChildLsCancel.cuiDim_y;
					//click on down arrow
					if(inputCursorOrigin_x < dwaxisx && inputCursorOrigin_x > subject.cuiChildLsDown.cuiCoords_x && inputCursorOrigin_y < dwaxisy && inputCursorOrigin_y > subject.cuiChildLsDown.cuiCoords_y){
						CUI_ListUpClick(subject);
					}
					//click on up arrow
					if(inputCursorOrigin_x < upaxisx && inputCursorOrigin_x > subject.cuiChildLsUp.cuiCoords_x && inputCursorOrigin_y < upaxisy && inputCursorOrigin_y > subject.cuiChildLsUp.cuiCoords_y){
						CUI_ListDownClick(subject);
					}
					//click on ok but
					if(inputCursorOrigin_x < okaxisx && inputCursorOrigin_x > subject.cuiChildLsOk.cuiCoords_x && inputCursorOrigin_y < okaxisy && inputCursorOrigin_y > subject.cuiChildLsOk.cuiCoords_y){
						subject.cuiChildLsOk.cuiOnRelease();
					}
					//click on cancel but
					if(inputCursorOrigin_x < cancelaxisx && inputCursorOrigin_x > subject.cuiChildLsCancel.cuiCoords_x && inputCursorOrigin_y < cancelaxisy && inputCursorOrigin_y > subject.cuiChildLsCancel.cuiCoords_y){
						subject.cuiChildLsCancel.cuiOnRelease();
					}
				}
			}
			CUI_HoverOn(subject);
			subject.cuiActive = TRUE;
		}
		else{
			CUI_HoverOff(subject);
			subject.cuiActive = FALSE;
		}
	}
}

void CUI_TriggerButton1Released()
{
	local entity head;
	
	head = cuiEntity;
	cuiEntity = world;
	//cycle trough all the ui entities finding the one which is in the correct hover position while mouse button is clicking
	while ((cuiEntity = nextent(cuiEntity))){
		if(cuiEntity.classname == "uielement"){
			CUI_EvMouseReleased(cuiEntity);
		}
	}
}

entity CUI_Button(entity parent, float typebut, vector coord,void() onrelease,string lbl, float vis)
{
	local entity subject = spawn();
	
	subject.cuiParent = parent;
	if(subject.cuiParent.cuiClass != CUI_CLASS_WINDOW){
		subject.cuiCoords = [subject.cuiParent.cuiCoords_x + subject.cuiParent.cuiDim_x + coord_x,subject.cuiParent.cuiCoords_y + coord_y,0];
	}
	else{
		subject.cuiCoords = [subject.cuiParent.cuiCoords_x + coord_x,subject.cuiParent.cuiCoords_y + coord_y,0];
	}
	subject.cuiClass = CUI_CLASS_BUTTON;
	subject.classname = "uielement";
	subject.cuiVis = vis;
	if(typebut == CUI_BUTTON_MENU){
		subject.cuiDim_x = 64;
		subject.cuiDim_y = 16;
		subject.cuiAlpha = 0.5;
		subject.cuiBgCol = [0.2,0.3,0.4];
		subject.cuiBgImg = "";
		subject.cuiTextCol = [1,1,1];
		subject.cuiTextDim = UI_FONT_SMALL;
		subject.cuiLabel = lbl;
	}
	else if(typebut == CUI_BUTTON_HEAD){
		subject.cuiDim_x = 12;
		subject.cuiDim_y = 12;
		subject.cuiAlpha = 0.5;
		subject.cuiBgCol = UI_HEADBUT_COLOR;
		subject.cuiLabel = "";
		subject.cuiBgImg = lbl;
		subject.cuiTextCol = [1,1,1];
		subject.cuiTextDim = UI_FONT_SMALL;
	}
	else if(typebut == CUI_BUTTON_PROP){
		subject.cuiDim_x = 8;
		subject.cuiDim_y = 8;
		subject.cuiAlpha = 0.5;
		subject.cuiBgCol = UI_HEADPROP_COLOR;
		subject.cuiLabel = "";
		subject.cuiBgImg = lbl;
		subject.cuiTextCol = [1,1,1];
		subject.cuiTextDim = UI_FONT_SMALL;
	}
	else if(typebut == CUI_BUTTON_LIST_PROP){
		subject.cuiDim_x = 16;
		subject.cuiDim_y = 16;
		subject.cuiAlpha = 1;
		subject.cuiBgCol = [1,1,1];
		subject.cuiLabel = "";
		subject.cuiBgImg = lbl;
		subject.cuiTextCol = [1,0,0];
		subject.cuiTextDim = UI_FONT_SMALL;
	}
	subject.cuiBgColOld = subject.cuiBgCol;
	subject.cuiAlphaOld = subject.cuiAlpha;
	subject.cuiOnRelease = onrelease;
	
	return subject;
}

entity CUI_Label(entity parent,vector coord,vector sz,vector col,string lbl,float vis)
{
	local entity subject = spawn();
	
	subject.cuiParent = parent;
	subject.cuiClass = CUI_CLASS_LABEL;
	subject.classname = "uielement";
	subject.cuiVis = vis;
	subject.cuiAlpha = 1;
	subject.cuiLabel = lbl;
	subject.cuiTextCol = col;
	subject.cuiTextDim = sz;
	subject.cuiDim_x = stringwidth(subject.cuiLabel, TRUE, [subject.cuiTextDim_x,subject.cuiTextDim_y,0]);
	subject.cuiDim_y = stringwidth(subject.cuiLabel, TRUE, [subject.cuiTextDim_x,subject.cuiTextDim_y,0]);
	if(subject.cuiParent.cuiClass != CUI_CLASS_WINDOW){
		subject.cuiCoords = [subject.cuiParent.cuiCoords_x + subject.cuiParent.cuiDim_x + coord_x,subject.cuiParent.cuiCoords_y + coord_y,0];
	}
	else{
		subject.cuiCoords = [subject.cuiParent.cuiCoords_x + coord_x,subject.cuiParent.cuiCoords_y + coord_y,0];
	}
	subject.cuiBgColOld = subject.cuiBgCol;
	
	return subject;
}

entity CUI_Window(entity parent, vector dim, vector coord,vector bgcol,float a, float vis)
{
	local entity subject = spawn();
	
	subject.cuiParent = parent;
	subject.cuiCoords = [subject.cuiParent.cuiCoords_x+coord_x,subject.cuiParent.cuiCoords_y+coord_y,0];
	subject.cuiClass = CUI_CLASS_WINDOW;
	subject.classname = "uielement";
	subject.cuiVis = vis;
	subject.cuiDim_x = dim_x;
	subject.cuiDim_y = dim_y;
	subject.cuiAlpha = a;
	subject.cuiBgCol = bgcol;
	subject.cuiBgImg = "";
	
	return subject;
}

entity CUI_List(entity parent, vector dim, vector coord,vector bgcol,vector barcolor, vector txtcolor,vector txtsz,float a,string butoklbl,void() okrelease,void() cancelrelease,float vis)
{
	local entity subject = spawn();
	local float margin = 15;
	local float barstep;
	local float butsz = 12;
	
	//list main window
	subject.cuiListMargin = butsz;
	subject.cuiParent = parent;
	subject.cuiClass = CUI_CLASS_LIST;
	subject.classname = "uielement";
	subject.cuiVis = vis;
	subject.cuiDim = [dim_x,dim_y,0];
	subject.cuiAlpha = a;
	subject.cuiBgCol = bgcol;
	subject.cuiBgImg = "";
	subject.cuiListTotal = 10;
	subject.cuiListBarHeight = subject.cuiDim_y / subject.cuiListTotal;
	subject.cuiTextDim = txtsz;
	subject.cuiListTextCol = txtcolor;
	subject.cuiListBarCol = barcolor;
	if(subject.cuiParent.cuiClass != CUI_CLASS_WINDOW){
		subject.cuiCoords = [subject.cuiParent.cuiCoords_x + subject.cuiParent.cuiDim_x + coord_x,subject.cuiParent.cuiCoords_y + coord_y,0];
	}
	else{
		subject.cuiCoords = [subject.cuiParent.cuiCoords_x + coord_x,subject.cuiParent.cuiCoords_y + coord_y,0];
	}
	barstep = subject.cuiCoords_y+subject.cuiDim_y / subject.cuiListTotal;
	subject.cuiListBarPosY = barstep;
	//list up arrow
	cuiListUp = spawn();
	cuiListUp.cuiParent = subject;
	cuiListUp.cuiDim = [subject.cuiListMargin,subject.cuiListMargin,0];
	cuiListUp.cuiBgImg = "textures/ed/cui/listarrowup.tga";
	cuiListUp.cuiCoords = [cuiListUp.cuiParent.cuiCoords_x+(cuiListUp.cuiParent.cuiDim_x-subject.cuiListMargin),cuiListUp.cuiParent.cuiCoords_y,0];
	cuiListUp.cuiClass = CUI_CLASS_LISTARROWUP;
	cuiListUp.classname = "uielement";
	cuiListUp.cuiVis = vis;
	cuiListUp.cuiAlpha = 1;
	cuiListUp.cuiBgCol = barcolor;
	//list down arrow
	cuiListDown = spawn();
	cuiListDown.cuiParent = subject;
	cuiListDown.cuiClass = CUI_CLASS_LISTARROWDOWN;
	cuiListDown.classname = "uielement";
	cuiListDown.cuiVis = vis;
	cuiListDown.cuiDim = [subject.cuiListMargin,subject.cuiListMargin,0];
	cuiListDown.cuiBgImg = "textures/ed/cui/listarrowdown.tga";
	cuiListDown.cuiCoords = [cuiListDown.cuiParent.cuiCoords_x+(cuiListDown.cuiParent.cuiDim_x-subject.cuiListMargin),cuiListDown.cuiParent.cuiCoords_y+(cuiListDown.cuiParent.cuiDim_y-cuiListDown.cuiDim_y-subject.cuiListMargin),0];
	cuiListDown.cuiAlpha = 1;
	cuiListDown.cuiBgCol = barcolor;
	//cuiListDown.cuiOnRelease = CUI_ListDownClick;
	//list ok but
	cuiListOk = spawn();
	cuiListOk.cuiParent = subject;
	cuiListOk.cuiDim = [subject.cuiListMargin,subject.cuiListMargin,0];
	cuiListOk.cuiBgImg = "textures/ed/cui/listok.tga";
	cuiListOk.cuiCoords = [cuiListOk.cuiParent.cuiCoords_x+(cuiListOk.cuiParent.cuiDim_x-subject.cuiListMargin),cuiListOk.cuiParent.cuiCoords_y+(cuiListOk.cuiParent.cuiDim_y-subject.cuiListMargin),0];
	cuiListOk.cuiClass = CUI_CLASS_LISTOK;
	cuiListOk.classname = "uielement";
	cuiListOk.cuiVis = vis;
	cuiListOk.cuiLabel = "AAAAAAAAAAAA";
	cuiListOk.cuiAlpha = 1;
	cuiListOk.cuiBgCol = cuiListOk.cuiParent.cuiBgCol+[0.1,0.1,0.1];
	cuiListOk.cuiOnRelease = okrelease;
	//list cancel but
	cuiListCancel = spawn();
	cuiListCancel.cuiParent = subject;
	cuiListCancel.cuiBgImg = "textures/ed/cui/listcancel.tga";
	cuiListCancel.cuiDim = [subject.cuiListMargin,subject.cuiListMargin,0];
	cuiListCancel.cuiCoords_x = cuiListCancel.cuiParent.cuiCoords_x;
	cuiListCancel.cuiCoords_y = cuiListCancel.cuiParent.cuiCoords_y;
	cuiListCancel.cuiClass = CUI_CLASS_LISTCANCEL;
	cuiListCancel.classname = "uielement";
	cuiListCancel.cuiVis = vis;
	cuiListCancel.cuiAlpha = 1;
	cuiListCancel.cuiBgCol = cuiListCancel.cuiParent.cuiBgCol+[0.1,0.1,0.1];
	cuiListCancel.cuiOnRelease = cancelrelease;
	//Ctrl bar
	cuiListCtrlbar = spawn();
	cuiListCtrlbar.cuiParent = subject;
	cuiListCtrlbar.cuiDim = [subject.cuiListMargin,subject.cuiParent.cuiDim_y,0];
	cuiListCtrlbar.cuiCoords = [cuiListCtrlbar.cuiParent.cuiCoords_x+(cuiListCtrlbar.cuiParent.cuiDim_x-subject.cuiListMargin),cuiListCtrlbar.cuiParent.cuiCoords_y,0];
	//cuiListCtrlbar.cuiClass = CUI_CLASS_LISTOK;
	cuiListCtrlbar.classname = "uielement";
	cuiListCtrlbar.cuiVis = vis;
	cuiListCtrlbar.cuiAlpha = 0.4;
	cuiListCtrlbar.cuiBgCol = [0,0,0];
	//children link - needed by click and draw funcs to proper refer to them
	subject.cuiChildLsUp = cuiListUp;
	subject.cuiChildLsDown = cuiListDown;
	subject.cuiChildLsOk = cuiListOk;
	subject.cuiChildLsCancel = cuiListCancel;
	subject.cuiChildLsCtrlbar = cuiListCtrlbar;
	
	return subject;
}

void CUI_DrawColor(vector comporg, vector compdim, vector compcolor, float compalpha)
{
	drawfill(comporg,compdim,compcolor,compalpha);
}

void CUI_DrawImage(string compimg, vector comporg, vector compdim, vector compcolor, float compalpha)
{
	drawpic(comporg,compimg,compdim,compcolor,compalpha);
}

void CUI_DrawButBackground(string compimg, vector comporg, vector compdim, vector compcolor, float compalpha)
{
	drawfill(comporg,compdim,compcolor,compalpha);
	drawpic(comporg,compimg,compdim,compcolor,compalpha);
	//(vector position, vector size, vector rgb, float alpha, optional float drawflag) drawfill 
}

void CUI_DrawListText(entity subject)
{
	local int i,tot=subject.cuiListTotal;
	local float h,barheight,marghor,margv,w,barselectedpos;
	local vector textpos,barpos,textdim;
	local string s;
	
	textdim = [subject.cuiTextDim_x,subject.cuiTextDim_y,0];
	marghor = subject.cuiDim_x / 10;
	barheight = subject.cuiDim_y / subject.cuiListTotal;
	margv = barheight/2;
	h = subject.cuiCoords_y-subject.cuiListBarHeight;
	barpos = [subject.cuiCoords_x,subject.cuiListBarPosY - barheight,0];
	
	//first draw controls bar
	//drawfill([(subject.cuiCoords_x+subject.cuiDim_x) - (subject.cuiDim_x / 10),subject.cuiCoords_y,0],[subject.cuiListMargin,subject.cuiDim_y,0],[0,0,0],0.4);
	barselectedpos = subject.cuiListBarPosY - barheight;
	
	//then draw bar
	if(barpos_y > subject.cuiCoords_y - subject.cuiListBarHeight){
		drawfill([subject.cuiCoords_x,barselectedpos,0],[subject.cuiDim_x,barheight,0],subject.cuiListBarCol,0.8);
	}
	//then draw text
	for (i=subject.cuiListTextIndex ; i < 30; i++){
		h += (subject.cuiListBarHeight) ;
		textpos = [subject.cuiCoords_x+marghor,(h+margv)-(textdim_y/2),0];
		if(subject.cuiListTextArray[i]!= ""){
			if(textpos_y < (subject.cuiCoords_y + subject.cuiDim_y)){
				s = subject.cuiListTextArray[i];
				w = stringwidth(s, TRUE, textdim);
				//if text exceeds list window margins..
				if(w > subject.cuiDim_x - marghor){				
					s = strcat(substring(s,0,subject.cuiDim_x/20)," ...");
				}
				drawstring(textpos,s,textdim,subject.cuiListTextCol,1,0);
			}
		}
	}
	
}

void CUI_Visualize(float viscontext)
{
	local entity head;
	
	head = cuiEntity;
	cuiEntity = world;
	//cycle trought all uientities in level
	while ((cuiEntity = nextent(cuiEntity))){
		//discard non-ui elements
		if(cuiEntity.classname == "uielement"){
			//filter by visibility context
			if(cuiEntity.cuiVis == viscontext){
				CUI_Hover(cuiEntity);
				//avoid clicking on elements placed in different contexts (and hidden, though)
				cuiEntity.cuiClicked = TRUE;
				//differentiate by uielement type
				switch(cuiEntity.cuiClass){
					case CUI_CLASS_WINDOW:
						if(cuiEntity.cuiBgImg != ""){
							CUI_DrawImage(cuiEntity.cuiBgImg,cuiEntity.cuiCoords,cuiEntity.cuiDim,cuiEntity.cuiBgCol,cuiEntity.cuiAlpha);
						}
						else{
							CUI_DrawColor(cuiEntity.cuiCoords,cuiEntity.cuiDim,cuiEntity.cuiBgCol,cuiEntity.cuiAlpha);
						}
						if(cuiEntity.cuiLabel != ""){
							drawstring(cuiEntity.cuiCoords+[2,2,0],cuiEntity.cuiLabel,[4,4,0],[1,1,1],0.3,0);
						}
					break;
					case CUI_CLASS_BUTTON:
						if(cuiEntity.cuiBgImg != ""){
							CUI_DrawImage(cuiEntity.cuiBgImg,cuiEntity.cuiCoords,cuiEntity.cuiDim,cuiEntity.cuiBgCol,cuiEntity.cuiAlpha);
						}
						else{
							CUI_DrawColor(cuiEntity.cuiCoords,cuiEntity.cuiDim,cuiEntity.cuiBgCol,cuiEntity.cuiAlpha);
						}
						if(cuiEntity.cuiLabel != ""){
							drawstring(cuiEntity.cuiCoords+[(cuiEntity.cuiDim_x/2)-(stringwidth(cuiEntity.cuiLabel, TRUE, [cuiEntity.cuiTextDim_x,cuiEntity.cuiTextDim_y,0]) * 0.5),cuiEntity.cuiDim_y/2,0],cuiEntity.cuiLabel,[cuiEntity.cuiTextDim_x,cuiEntity.cuiTextDim_y,0],cuiEntity.cuiTextCol,cuiEntity.cuiAlpha,0);
						}
					break;
					case CUI_CLASS_LABEL:
						if(cuiEntity.cuiLabel != ""){
							local float sw = stringwidth(cuiEntity.cuiLabel, TRUE, [cuiEntity.cuiTextDim_x,cuiEntity.cuiTextDim_y,0]);
							drawstring(cuiEntity.cuiCoords+[cuiEntity.cuiDim_x-sw,cuiEntity.cuiTextDim_y/2,0],cuiEntity.cuiLabel,[cuiEntity.cuiTextDim_x,cuiEntity.cuiTextDim_y,0],cuiEntity.cuiTextCol,cuiEntity.cuiAlpha,0);
						}
					break;
					case CUI_CLASS_LIST:
						CUI_DrawColor(cuiEntity.cuiCoords,cuiEntity.cuiDim,cuiEntity.cuiBgCol,cuiEntity.cuiAlpha);
						CUI_DrawListText(cuiEntity);
						CUI_DrawColor(cuiEntity.cuiChildLsCtrlbar.cuiCoords,[cuiEntity.cuiChildLsCtrlbar.cuiDim_x,cuiEntity.cuiDim_y,0],UI_DARKER_COLOR,1);				
						CUI_DrawColor(cuiEntity.cuiChildLsCancel.cuiCoords,cuiEntity.cuiChildLsCancel.cuiDim,UI_DARKER_COLOR,1);
						CUI_DrawColor(cuiEntity.cuiChildLsOk.cuiCoords,cuiEntity.cuiChildLsOk.cuiDim,UI_DARKER_COLOR,1);
						CUI_DrawColor(cuiEntity.cuiChildLsUp.cuiCoords,cuiEntity.cuiChildLsUp.cuiDim,cuiEntity.cuiBgCol,1);
						CUI_DrawColor(cuiEntity.cuiChildLsDown.cuiCoords,cuiEntity.cuiChildLsDown.cuiDim,cuiEntity.cuiBgCol,1);
						CUI_DrawImage(cuiEntity.cuiChildLsUp.cuiBgImg,cuiEntity.cuiChildLsUp.cuiCoords,cuiEntity.cuiChildLsUp.cuiDim,[1,1,1],1);
						CUI_DrawImage(cuiEntity.cuiChildLsDown.cuiBgImg,cuiEntity.cuiChildLsDown.cuiCoords,cuiEntity.cuiChildLsDown.cuiDim,[1,1,1],1);
						CUI_DrawImage(cuiEntity.cuiChildLsCancel.cuiBgImg,cuiEntity.cuiChildLsCancel.cuiCoords,cuiEntity.cuiChildLsCancel.cuiDim,[1,1,1],1);
						CUI_DrawImage(cuiEntity.cuiChildLsOk.cuiBgImg,cuiEntity.cuiChildLsOk.cuiCoords,cuiEntity.cuiChildLsOk.cuiDim,[1,1,1],1);		
					break;
					default:
					break;
				}
			}
			else{
				//ui element is in a different visibility context, so don't click on it
				cuiEntity.cuiClicked = FALSE;
			}
		}
	}
	cuiEntity = head;
}
