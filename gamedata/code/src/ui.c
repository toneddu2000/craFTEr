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

void UI_Popup()
{
	uiMessageMode = TRUE;
}

void UI_PopupClose()
{
	uiMessageMode = FALSE;
	uiMessageText = "";
}

void UI_PopupVisualize(float vwidth,float vheight)
{
	if(uiMessageMode){
		//draw bg border
		drawfill(UI_POPUP_COORD+[-1,-1,0], [vwidth-28,62,0],UI_POPUP_COLOR_BG_BORDER, 1);
		//draw bg
		drawfill(UI_POPUP_COORD, [vwidth-30,60,0],UI_POPUP_COLOR_BG, 1);
		//draw text
		drawstring(UI_POPUP_COORD,uiMessageText,UI_FONT_MEDIUM,[1,1,1],1,0);
	}
}

void UI_Warning(string s)
{
	local string w = "Warning: ";
	local string 	oldtext;
	
	if(s != oldtext){
		uiWarningTime = 0;
		uiWarningAlpha = 1;
	}
	//concat string from input
	if(s != ""){
		uiWarningText = strcat(w,s);
		oldtext = s;
	}
}

void UI_WarningDisplay(float vwidth,float vheight)
{
	local float 	sz,wornofftime=120;
	
	uiWarningTime += 0.05;
	sz = stringwidth(uiWarningText, TRUE, UI_FONT_BIG);
	drawstring([20,50,0],uiWarningText,[UI_FONT_BIG_x*(vwidth/sz*0.9),UI_FONT_BIG_y*(vheight/sz*1.7),0],[1,0,0],uiWarningAlpha,0);
	if(uiWarningTime > wornofftime){
		uiWarningAlpha -= 0.006;
	}
	if(uiWarningAlpha <= 0){
		uiWarningText = "";
	}
}

void UI_WarningVisualize(float vwidth,float vheight)
{
	if(uiWarningText != ""){
		UI_WarningDisplay(vwidth,vheight);
	}
	else{
		uiWarningTime = 0;
		uiWarningAlpha = 1;
	}
}

void UI_Message(string s)
{
	local string 	oldtext;
	
	if(s != oldtext){
		uiMessageTime = 0;
		uiMessageAlpha = 1;
	}
	//concat string from input
	if(s != ""){
		uiMessageBigText = strcat(s);
		oldtext = s;
	}
}

void UI_MessageDisplay(float vwidth,float vheight)
{
	local float 	sz,wornofftime=120;
	local vector txtsz;
	
	uiMessageTime += 0.05;
	sz = stringwidth(uiMessageBigText, TRUE, UI_FONT_BIG);
	txtsz = [UI_FONT_BIG_x*(vwidth/sz*0.9),UI_FONT_BIG_x*(vwidth/sz*0.9),0];
	if(txtsz_x > 20){
		txtsz_x = 20;
		txtsz_y = 20;
	}
	drawstring([20,50,0],uiMessageBigText,txtsz,[0,1,0],uiMessageAlpha,0);
	
	if(uiMessageTime > wornofftime){
		uiMessageAlpha -= 0.006;
	}
	if(uiMessageAlpha <= 0){
		uiMessageBigText = "";
	}
}

void UI_MessageVisualize(float vwidth,float vheight)
{
	if(uiMessageBigText != ""){
		UI_MessageDisplay(vwidth,vheight);
	}
	else{
		uiMessageTime = 0;
		uiMessageAlpha = 1;
	}
}

void UI_EdModeVisualize(float vwidth,float vheight)
{
	local float a = 0.4,m=1;
	local vector col = [1,1,1],modepos = [10,vheight-12,0];
	local string prfx = "Mode: ";
	
	switch(edMode){
		case ED_MODE_SELECT:
			drawstring(modepos,strcat(prfx,"Select"),UI_FONT_SMALL,col,a,m);
		break;
		case ED_MODE_MOVE:
			drawstring(modepos,strcat(prfx,"Move"),UI_FONT_SMALL,col,a,m);
		break;
		case ED_MODE_ROTATE:
			drawstring(modepos,strcat(prfx,"Rotate"),UI_FONT_SMALL,col,a,m);
		break;
		case ED_MODE_MESH:
			drawstring(modepos,strcat(prfx,"Mesh"),UI_FONT_SMALL,col,a,m);
		break;
		case ED_MODE_ENT:
			drawstring(modepos,strcat(prfx,"Entity"),UI_FONT_SMALL,col,a,m);
		break;
		case ED_MODE_CRUMB:
			drawstring(modepos,strcat(prfx,"Crumb"),UI_FONT_SMALL,col,a,m);
		break;
		default:
			//error if goes here
		break;
	}
}

void UI_StatusBarVisualize(float vwidth,float vheight)
{
	local string s,prfx = " - ";
	local float a = 0.4,m=1;
	local vector placepos = [100,vheight-12,0],col = [1,1,1];
	
	drawfill([0,vheight-16,0], [vwidth,16,0],UI_COLOR_WHITE, 0.4);
	if(edSelectedArray[0] != world){
		if(edSelectedArray[0].gameClass == ENT_CLASS_MESH){
			s = strcat(prfx,"Enemy mesh with ID: ",etos(edSelectedArray[0]));
		}
		else if (edSelectedArray[0].gameClass == ENT_CLASS_NPC){
			s = strcat(prfx,"Enemy entity with ID: ",etos(edSelectedArray[0]));
		}
		else if (edSelectedArray[0].gameClass == ENT_CLASS_ITEM){
			s = strcat(prfx,"Enemy item with ID: ",etos(edSelectedArray[0]));
		}
		else{
			s = strcat(prfx,etos(edSelectedArray[0]));
		}
		drawstring(placepos,s,UI_FONT_SMALL,col,a,m);
	}
	UI_EdModeVisualize(vwidth,vheight);
}

void UI_ModelPreviewVisualize(float vwidth,float vheight)
{
	local string modelsstaticfolder = "models/static/";
	
	if(gameState == GAME_STATE_ED){
		if(uiPanelMesh){
			local int i;
			local string categoryprinted,folderprinted,modelnameprinted,modelname;
			local float modelsearch,modelstot,posx,posy;
			posx = 20;
			posy = 20;
			//get folder name
			Ed_MeshSearch();
			categoryprinted = strreplace(modelsstaticfolder,"",uiMeshCategoriesArray[uiMeshCategoriesIndex]);
			categoryprinted = strreplace("/","",categoryprinted);
			drawstring([posx,posy,0],strcat("Category:\n\r",categoryprinted),UI_FONT_SMALL,[1,1,1],0.8,0);
			folderprinted = strreplace(uiMeshCategoriesArray[uiMeshCategoriesIndex],"",uiMeshFoldersArray[uiMeshFoldersIndex]);
			uiMeshFolderSelected = strreplace("/","",uiMeshFolderSelected);
			drawstring([posx,posy+25,0],strcat("Folder:\n\r",uiMeshFolderSelected),UI_FONT_SMALL,[1,1,1],0.8,0);
			edMeshesFolder = strcat(uiMeshCategoriesArray[uiMeshCategoriesIndex],folderprinted);
			//search for .iqm model
			modelsearch = search_begin(strcat(edMeshesFolder,"*.iqm"),TRUE,FALSE);
			modelstot = search_getsize(modelsearch);
			//store models names in array
			if (modelsearch != -1){
				for(i = 0; i < modelstot ; i++){
					modelname = search_getfilename(modelsearch,i);
					if(modelname != ""){
						//remove collision models from the list
						if(strstrofs(modelname,"_col") == -1){
							uiPanelMeshArray[i]=search_getfilename(modelsearch,i);
						}
					}
				}
			}
			search_end(modelsearch);
			modelnameprinted = strreplace(modelsstaticfolder,"",uiPanelMeshArray[uiPanelMeshIndex]);
			modelnameprinted = strreplace(strcat(categoryprinted,"/"),"",modelnameprinted);
			modelnameprinted = strreplace(folderprinted,"",modelnameprinted);
			modelnameprinted = strreplace(".iqm","",modelnameprinted);
			drawstring([posx,posy+50,0],strcat("Model:\n\r",modelnameprinted),UI_FONT_SMALL,[1,1,1],0.8,0);
			//3d model set to view spinning model
			setmodel(uiPanelMeshModel,uiPanelMeshArray[uiPanelMeshIndex]);
			edMeshStored = uiPanelMeshArray[uiPanelMeshIndex];
			uiPanelMeshModel.solid = SOLID_NOT;
			Util_ResetSize(uiPanelMeshModel);
			makevectors(input_angles);
			edShaderStored = modelnameprinted;
		}
		else{
			setmodel(uiPanelMeshModel,"");
		}
	}
}

void UI_ModelPreviewInit()
{
	uiPanelMesh = FALSE;
	uiPanelMeshIndex = 0;
	uiPanelMeshModel = spawn();
	setorigin(uiPanelMeshModel,[0,0,32]);
	uiPanelMeshModel.renderflags = RF_NOSHADOW;
}

void UI_TimelineVisualize(float posx,float posy)
{
	local int i;
	local float a = 0.8,arrowpos,lineincr,margin=0;
	local string dur,perc,endframe,frmname;
	local vector col = [1,0,0],barsize=[300,150,0];
	
	if(uiTimeline == TRUE){
		lineincr = barsize_x/10;
		arrowpos = ((lineincr)*animTimelinePercentage)/10;
		//draw bg a little largen than barsize_x because otherwise time line would screw up
		drawfill([posx-10,posy,0],[barsize_x+30,barsize_y,0],UI_WINPROP_COLOR, 0.2);
		//draw lines(except first and last) white
		for(i=0;i<barsize_x;i+=lineincr){
			if(i != 0){
				drawpic([posx+margin+i,posy+10,0],"textures/ed/tl_line.tga",[8,8,0],[1,1,1],0.5);
			}
		}
		//draw first and last vertical lines red
		drawpic([posx,posy+10,0],"textures/ed/tl_line.tga",[8,8,0],[1,0,0],0.7);
		drawpic([posx+barsize_x,posy+10,0],"textures/ed/tl_line.tga",[8,8,0],[1,0,0],0.5);
		//draw small lines
		for(i=0;i<barsize_x;i+=lineincr/2){
			if(i!=0){
				drawpic([posx+margin+i,posy+14,0],"textures/ed/tl_line.tga",[8,4,0],[1,1,1],0.2);
			}
		}
		//draw arrow
		drawpic([posx+arrowpos,posy+20,0],"textures/ed/animarrow.tga",[8,8,0],[1,0,0],0.8);
		//print utils
		dur = strcat("Duration: " ,ftos(animTimelineDuration)," sec.");
		perc = strcat("Percentage: ",ftos(animTimelinePercentage));
		endframe = strcat("End frame: ",ftos(uiTimelineModel.animIdleEndFrame));
		uiTimelineTime = uiTimelineModel.animIdleTime;
		drawstring([posx,posy+30,0],dur,[8,8,0],[1,1,1],a,0);
		drawstring([posx,posy+40,0],perc,[8,8,0],[1,1,1],a,0);
		drawstring([posx,posy+50,0],strcat("Timeline: ",ftos(uiTimelineTime)),[8,8,0],[1,1,1],a,0);
		drawstring([arrowpos,posy-2,0],ftos(uiTimelineTime),[6,6,0],[1,0,0],a,0);
		drawstring([posx,posy+60,0],endframe,[8,8,0],[1,1,1],a,0);
		frmname = frametoname(uiTimelineModel.modelindex,uiTimelineModel.frame);
		drawstring([posx,posy+70,0],strcat("Anim: ",frmname),[8,8,0],[1,1,1],a,0);
		drawstring([posx,posy+80,0],strcat("Playback speed: ",ftos(uiTimelineSpeed)),[8,8,0],[1,1,1],a,0);
		//drawstring([posx,posy+70,0],ftos(arrowpos),[8,8,0],[1,1,1],a,0);
		//drawstring([posx,posy+90,0],strcat("Line incr: ",ftos(lineincr)),[8,8,0],[1,1,1],a,0);
		//drawstring([posx,posy+100,0],itos(i),[8,8,0],[1,1,1],a,0);
	}
}

void UI_TimelineModelInit()
{
	uiTimeline = FALSE;
	uiTimelineSpeed = 0.25;
	uiTimelineEntIndex = 0;
	uiTimelineModel = spawn();
	setorigin(uiTimelineModel,[0,0,32]);
	precache_model("models/enemies/REMOVE_werewolf/werewolf.iqm");
	setmodel(uiTimelineModel,"models/enemies/REMOVE_werewolf/werewolf.iqm");
	setsize(uiTimelineModel,uiTimelineModel.mins,uiTimelineModel.maxs);
	uiTimelineModel.renderflags = RF_NOSHADOW;
}

void UI_ListLevels(entity subject)
{
	local float levelssearch,levelstot;
	local int i;
	local string levname;
	if(levelOpen == TRUE){
		levelssearch = search_begin(strcat("data/levels/","*.level"),TRUE,FALSE);
		levelstot = search_getsize(levelssearch);
		//store models names in array
		if (levelssearch != -1){
			for(i = 0; i < levelstot ; i++){
				levname = search_getfilename(levelssearch,i);
				if(levname != ""){
					levname = strreplace("data/levels/","",levname);
					levname = strreplace(".level","",levname);
					subject.cuiListTextArray[i] = levname;
				}
			}
		}
		search_end(levelssearch);
	}
}

void UI_ListLayers(entity subject)
{
	local int i;
	
	if(edLayerOpen == TRUE){
		for(i = 0; i < ED_TOTAL_SELECTED ; i++){
			subject.cuiListTextArray[i] = edLayerNameArray[i];	
		}
	}
}

void UI_ListSelByType(entity subject)
{
	local int i;
	local string s;
	
	if(edSelByTypeOpen == TRUE){
		for(i = 0; i < ENT_CLASS_GROUP ; i++){
			switch(i){
				case ENT_CLASS_NULL:
					s = "All types";
				break;
				case ENT_CLASS_PLAYER:
					s = "Player type";
				break;
				case ENT_CLASS_NPC:
					s = "Enemy type";
				break;
				case ENT_CLASS_WEAP:
					s = "Weapon type";
				break;
				case ENT_CLASS_ITEM:
					s = "Item type";
				break;
				case ENT_CLASS_MESH:
					s = "Mesh type";
				break;
				case ENT_CLASS_MESHCOLLISION:
					s = "Mesh collision type";
				break;
				case ENT_CLASS_GROUP:
					s = "Group type";
				break;
			}
			subject.cuiListTextArray[i] = s;			
		}
	}
}

void UI_ListPrefabs(entity subject)
{
	local float prefabsearch,prefabtot;
	local int i;
	local string prefabname;
	if(edPrefabOpen == TRUE){
		prefabsearch = search_begin(strcat("data/prefabs/","*.prefab"),TRUE,FALSE);
		prefabtot = search_getsize(prefabsearch);
		//store models names in array
		if (prefabsearch != -1){
			for(i = 0; i < prefabtot ; i++){
				prefabname = search_getfilename(prefabsearch,i);
				if(prefabname != ""){
					prefabname = strreplace("data/prefabs/","",prefabname);
					prefabname = strreplace(".prefab","",prefabname);
					subject.cuiListTextArray[i] = prefabname;
				}
			}
		}
		search_end(prefabsearch);
	}
}

void UI_ListTimelineMeshes(entity subject)
{
	local float mdlsearch,mdlstot;
	local int i;
	local string mdlname;
	local string prefixpath = "models/enemies/REMOVE_werewolf/";//test! replace with folder search mechanism
	if(uiTimelineMenu == TRUE){
		mdlsearch = search_begin(strcat(prefixpath,"*.iqm"),TRUE,FALSE);
		mdlstot = search_getsize(mdlsearch);
		//store models names in array
		if (mdlsearch != -1){
			for(i = 0; i < mdlstot ; i++){
				mdlname = search_getfilename(mdlsearch,i);
				if(mdlname != ""){
					subject.cuiListTextArray[i] = mdlname;
				}
			}
		}
		search_end(mdlsearch);
	}
}

void UI_ListEntFuncs(entity subject)
{
	local float f;
	local string ln;
	local int i = 0;
	if(uiPanelEntFuncs == TRUE){
		f = fopen("system/entfuncs.func", FILE_READ);
		if (f != -1){
			ln = fgets(f);
			while(ln != __NULL__){
				if(ln != ""){
					subject.cuiListTextArray[i] = ln;
					i++;
				}
				//go to new line
				ln = fgets(f);   
			} 
		} 
		fclose(f);
	}
}

void UI_ElemInit()
{
	local float minx = getviewprop(VF_MIN_X);
	local float miny = getviewprop(VF_MIN_Y);
	local float sizex = getviewprop(VF_SIZE_X);
	local float sizey = getviewprop(VF_SIZE_Y);
	local vector butpropcoord = [130,17,0];
	local vector propcolcoord = [20,40,0];
	
	//basic elems
	uiElScreen = CUI_Window(uiElScreen,[sizex,sizey,0],[minx,miny,0],UI_HEAD_COLOR,0,UI_VIS_NULL);
	uiElHeader = CUI_Window(uiElScreen,[sizex,UI_HEADER_HEIGHT,0],[minx,miny,0],UI_COLOR_GRAY,1,UI_VIS_ED_LAYOUT);
	
	//header
	uiElWinPropMesh = CUI_Window(uiElScreen,UI_WINPROP_SIZE,UI_WINPROP_COORD,UI_WINPROP_COLOR,0.8,UI_VIS_PROPMESH);
	uiElButHeadSel = CUI_Button(uiElHeader,CUI_BUTTON_HEAD,[4,4,0],Ed_ModeSelect,UI_BUT_IMG_SEL,UI_VIS_ED_LAYOUT);
	uiElButHeadMove = CUI_Button(uiElButHeadSel,CUI_BUTTON_HEAD,UI_BUTHEAD_COORD,Ed_ModeMove,UI_BUT_IMG_MOVE,UI_VIS_ED_LAYOUT);
	uiElButHeadRot = CUI_Button(uiElButHeadMove,CUI_BUTTON_HEAD,UI_BUTHEAD_COORD,Ed_ModeRotate,UI_BUT_IMG_ROT,UI_VIS_ED_LAYOUT);
	uiElButHeadMesh = CUI_Button(uiElButHeadRot,CUI_BUTTON_HEAD,UI_BUTHEAD_COORD,Ed_ModeMesh,UI_BUT_IMG_MESH,UI_VIS_ED_LAYOUT);
	uiElButHeadChar = CUI_Button(uiElButHeadMesh,CUI_BUTTON_HEAD,UI_BUTHEAD_COORD,Ed_ModeChar,UI_BUT_IMG_CHAR,UI_VIS_ED_LAYOUT);
	uiElButHeadCrumb = CUI_Button(uiElButHeadChar,CUI_BUTTON_HEAD,UI_BUTHEAD_COORD,Ed_ModeCrumb,UI_BUT_IMG_CRUMB,UI_VIS_ED_LAYOUT);
	uiElButHeadLayer = CUI_Button(uiElButHeadCrumb,CUI_BUTTON_HEAD,[UI_BUTHEAD_COORD_x*4,UI_BUTHEAD_COORD_y,UI_BUTHEAD_COORD_z],Ed_ModeLayerOn,UI_BUT_IMG_LAYER,UI_VIS_ED_LAYOUT);
	uiElButHeadSelByType = CUI_Button(uiElButHeadLayer,CUI_BUTTON_HEAD,UI_BUTHEAD_COORD,Ed_ModeSelByTypeOn,UI_BUT_IMG_SELBYTYPE,UI_VIS_ED_LAYOUT);
	uiElButHeadPrefab = CUI_Button(uiElButHeadSelByType,CUI_BUTTON_HEAD,UI_BUTHEAD_COORD,Ed_ModePrefabOn,UI_BUT_IMG_PREFAB,UI_VIS_ED_LAYOUT);
	uiElButHeadTimeline = CUI_Button(uiElButHeadPrefab,CUI_BUTTON_HEAD,UI_BUTHEAD_COORD,Ed_ModeTimelineMenuOn,UI_BUT_IMG_TIMELINE,UI_VIS_ED_LAYOUT);
	uiElButHeadSave = CUI_Button(uiElHeader,CUI_BUTTON_HEAD,[sizex-UI_BUTHEAD_COORD_x*8,4,UI_BUTHEAD_COORD_z],Ed_ModeLevelSave,UI_BUT_IMG_SAVE,UI_VIS_ED_LAYOUT);
	uiElButHeadLoad = CUI_Button(uiElButHeadSave,CUI_BUTTON_HEAD,UI_BUTHEAD_COORD,Ed_ModeLevelOpenOn,UI_BUT_IMG_LOAD,UI_VIS_ED_LAYOUT);
	
	//mesh panel
	uiElButMeshCatUp = CUI_Button(uiElScreen,CUI_BUTTON_PROP,butpropcoord,Ed_MeshCategoryUp,UI_BUT_IMG_FOLDUP,UI_VIS_PROPMESH);
	uiElButMeshCatDown = CUI_Button(uiElButMeshCatUp,CUI_BUTTON_PROP,UI_BUTHEAD_COORD,Ed_MeshCategoryDown,UI_BUT_IMG_FOLDDOWN,UI_VIS_PROPMESH);
	uiElButMeshFolderDown = CUI_Button(uiElScreen,CUI_BUTTON_PROP,butpropcoord+[0,25,0],Ed_MeshFolderDown,UI_BUT_IMG_DBARWLEFT,UI_VIS_PROPMESH);
	uiElButMeshFolderUp = CUI_Button(uiElButMeshFolderDown,CUI_BUTTON_PROP,UI_BUTHEAD_COORD,Ed_MeshFolderUp,UI_BUT_IMG_DBARWRIGHT,UI_VIS_PROPMESH);
	uiElButMeshDecr = CUI_Button(uiElScreen,CUI_BUTTON_PROP,butpropcoord+[0,50,0],Ed_MeshModelDecrement,UI_BUT_IMG_ARWLEFT,UI_VIS_PROPMESH);
	uiElButMeshIncr = CUI_Button(uiElButMeshDecr,CUI_BUTTON_PROP,UI_BUTHEAD_COORD,Ed_MeshModelIncrement,UI_BUT_IMG_ARWRIGHT,UI_VIS_PROPMESH);
	uiElButMeshPlace = CUI_Button(uiElButMeshIncr,CUI_BUTTON_PROP,UI_BUTHEAD_COORD,Ed_PlaceMesh,UI_BUT_IMG_MESH,UI_VIS_PROPMESH);
	
	//lists
	uiElListLevel = CUI_List(uiElScreen,[200,300,0],[200,30,0],UI_DARK_COLOR,UI_BRIGHT_COLOR,[1,1,1],UI_FONT_MEDIUM,1,"ok",Ed_ModeLevelOpen,Ed_ModeLevelOpenOff,UI_VIS_LEVELLOAD);
	uiElListLayer = CUI_List(uiElScreen,[200,300,0],[200,30,0],UI_DARK_COLOR,UI_BRIGHT_COLOR,[1,1,1],UI_FONT_MEDIUM,1,"ok",Ed_ModeLayerOff,Ed_ModeLayerOff,UI_VIS_LAYER);
	uiElButLayerToggle = CUI_Button(uiElListLayer,CUI_BUTTON_LIST_PROP,[-80,uiElListLayer.cuiListBarPosY,0],Ed_ModeLayerToggle,UI_BUT_IMG_LAYERTOGGLE,UI_VIS_LAYER);
	uiElButLayerAddObj = CUI_Button(uiElListLayer,CUI_BUTTON_LIST_PROP,[-50,uiElListLayer.cuiListBarPosY,0],Ed_ModeLayerAddObj,UI_BUT_IMG_LAYERADDOBJ,UI_VIS_LAYER);
	uiElListSelByType = CUI_List(uiElScreen,[200,300,0],[200,30,0],UI_DARK_COLOR,UI_BRIGHT_COLOR,[1,1,1],UI_FONT_MEDIUM,1,"Select",Ed_SelectByType,Ed_ModeSelByTypeOff,UI_VIS_SELBYTYPE);
	uiElListPrefab = CUI_List(uiElScreen,[200,300,0],[200,30,0],UI_DARK_COLOR,UI_BRIGHT_COLOR,[1,1,1],UI_FONT_MEDIUM,1,"Select",Ed_ModePrefabLoad,Ed_ModePrefabOff,UI_VIS_PREFAB);
	uiElListEntFuncs = CUI_List(uiElScreen,[200,300,0],[200,30,0],UI_DARK_COLOR,UI_BRIGHT_COLOR,[1,1,1],UI_FONT_MEDIUM,1,"Select spawn function",Ed_PlaceBlankSpawn,Ed_PlaceBlankSpawnOff,UI_VIS_ENTFUNCS);
	uiElListTimelineMeshes = CUI_List(uiElScreen,[200,300,0],[200,30,0],UI_DARK_COLOR,UI_BRIGHT_COLOR,[1,1,1],UI_FONT_MEDIUM,1,"Add event",Ed_ModeTimelineOn,Ed_ModeTimelineMenuOff,UI_VIS_TIMELINEMENU);
	
	
	//level overwrite
	uiElWinLevOverwrite = CUI_Window(uiElScreen,[300,200,0],[50,100,0],UI_WINPROP_COLOR,0.8,UI_VIS_LEVELOVERWRITE);
	uiElLblLevOverwrite = CUI_Label(uiElWinLevOverwrite,[15,15,0],UI_FONT_BIG,[1,1,1],strcat("Level ",levelOverwriteName," already exists, overwrite?"),UI_VIS_LEVELOVERWRITE);
	uiElButLevOverwrite = CUI_Button(uiElWinLevOverwrite,CUI_BUTTON_LIST_PROP,[uiElWinLevOverwrite.cuiCoords_x/2,50,0],Level_Overwrite,"textures/ed/cui/listok.tga",UI_VIS_LEVELOVERWRITE);
	uiElButLevOverwriteExit = CUI_Button(uiElButLevOverwrite,CUI_BUTTON_LIST_PROP,[0,20,0],Level_OverwriteOff,UI_BUT_IMG_CLOSE,UI_VIS_LEVELOVERWRITE);
	
	//timeline
	uiElWinPropTime = CUI_Window(uiElScreen,UI_WINPROP_SIZE,UI_WINPROP_COORD,UI_WINPROP_COLOR,1,UI_VIS_TIMELINE);
	uiElButTimeFrmDecr = CUI_Button(uiElWinPropTime,CUI_BUTTON_PROP,[250,50,0],Ed_ModeTimelineFrameDecrease,"textures/ed/arwleft.tga",UI_VIS_TIMELINE);
	uiElButTimeFrmIncr = CUI_Button(uiElButTimeFrmDecr,CUI_BUTTON_PROP,[16,0,0],Ed_ModeTimelineFrameIncrease,"textures/ed/arwright.tga",UI_VIS_TIMELINE);
	uiElButTimeSpeedDecr = CUI_Button(uiElWinPropTime,CUI_BUTTON_PROP,[250,70,0],Ed_ModeTimelineSpeedDecrease,"textures/ed/folderdown.tga",UI_VIS_TIMELINE);
	uiElButTimeSpeedIncr = CUI_Button(uiElButTimeSpeedDecr,CUI_BUTTON_PROP,[16,0,0],Ed_ModeTimelineSpeedIncrease,"textures/ed/folderup.tga",UI_VIS_TIMELINE);
	uiElButTimeClose = CUI_Button(uiElWinPropTime,CUI_BUTTON_PROP,[uiElWinPropTime.cuiDim_x+uiElWinPropTime.cuiCoords_x-50,0,0],Ed_ModeTimelineOff,UI_BUT_IMG_CLOSE,UI_VIS_TIMELINE);
}

void UI_ElemVisualize()
{
	CUI_Visualize(UI_VIS_NULL);
	if(gameState == GAME_STATE_MENU){
		CUI_Visualize(UI_VIS_MENU);
	}
	else if(gameState == GAME_STATE_PRERUNNING){
		
	}
	else if(gameState == GAME_STATE_ED){
		CUI_Visualize(UI_VIS_ED_LAYOUT);
		if(uiPanelMesh == TRUE){
			CUI_Visualize(UI_VIS_PROPMESH);
		}
		else if(levelOpen == TRUE){
			CUI_Visualize(UI_VIS_LEVELLOAD);
			UI_ListLevels(uiElListLevel);
		}
		else if(edLayerOpen == TRUE){
			CUI_Visualize(UI_VIS_LAYER);
			UI_ListLayers(uiElListLayer);
		}
		else if(edSelByTypeOpen == TRUE){
			CUI_Visualize(UI_VIS_SELBYTYPE);
			UI_ListSelByType(uiElListSelByType);
		}
		else if(levelOverwrite == TRUE){
			CUI_Visualize(UI_VIS_LEVELOVERWRITE);
		}
		else if(edPrefabOpen == TRUE){
			CUI_Visualize(UI_VIS_PREFAB);
			UI_ListPrefabs(uiElListPrefab);
		}
		else if(uiTimelineMenu == TRUE){
			CUI_Visualize(UI_VIS_TIMELINEMENU);
			UI_ListTimelineMeshes(uiElListTimelineMeshes);			
		}
		else if(uiPanelEntFuncs == TRUE){
			CUI_Visualize(UI_VIS_ENTFUNCS);
			UI_ListEntFuncs(uiElListEntFuncs);
		}
		else if(uiTimeline == TRUE){
			CUI_Visualize(UI_VIS_TIMELINE);
		}
	}
}

void UI_PostVisualize(float vwidth,float vheight)
{
	if(gameState == GAME_STATE_MENU){
		
	}
	else if(gameState == GAME_STATE_ED){
		UI_WarningVisualize(vwidth,vheight);
		UI_MessageVisualize(vwidth,vheight);
		UI_ModelPreviewVisualize(vwidth,vheight);
		UI_StatusBarVisualize(vwidth,vheight);
		//TONEDDUFIXME:temp -- put it in proper func!!
		uiElButLayerToggle.cuiCoords_y = uiElListLayer.cuiListBarPosY - 24;
		uiElButLayerAddObj.cuiCoords_y = uiElListLayer.cuiListBarPosY - 24;
		if(edLayerArray[uiElListLayer.cuiListIndex].edLayerActive == TRUE){
			uiElButLayerToggle.cuiAlpha = 1;
		}
		else{
			uiElButLayerToggle.cuiAlpha = 0.4;
		}
		UI_TimelineVisualize(UI_TIMELINEWIN_COORD_x,UI_TIMELINEWIN_COORD_y);
		UI_PopupVisualize(vwidth,vheight);
	}
	else if(gameState == GAME_STATE_PRERUNNING){
		
	}
	else if(gameState == GAME_STATE_RUNNING){
		
	}
	UI_ElemVisualize();
	UI_WarningVisualize(vwidth,vheight);
	UI_MessageVisualize(vwidth,vheight);
}

void UI_Init()
{
	uiMessageMode = FALSE;
	uiLoadingText = "Loading level, please wait..";
	UI_ElemInit();
	UI_ModelPreviewInit();
	UI_TimelineModelInit();
}