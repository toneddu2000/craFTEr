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

void Render_Cube(vector side,vector place,string shd)
{
	// front
	R_BeginPolygon(shd);
		R_PolygonVertex([-side_x,side_y,side_z]+place,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side_x,side_y,side_z]+place,[1,1,0],[1,1,1],1);
		R_PolygonVertex([side_x,side_y,-side_z]+place,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side_x,side_y,-side_z]+place,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// top
	R_BeginPolygon(shd);
		R_PolygonVertex([side_x,-side_y,side_z]+place,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side_x,side_y,side_z]+place,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side_x,side_y,side_z]+place,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side_x,-side_y,side_z]+place,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// right
	R_BeginPolygon(shd);
		R_PolygonVertex([side_x,side_y,-side_z]+place,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side_x,side_y,side_z]+place,[1,1,0],[1,1,1],1);
		R_PolygonVertex([side_x,-side_y,side_z]+place,[1,0,0],[1,1,1],1);
		R_PolygonVertex([side_x,-side_y,-side_z]+place,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// left
	R_BeginPolygon(shd);
		R_PolygonVertex([-side_x,-side_y,side_z]+place,[0,1,0],[1,1,1],1);
		R_PolygonVertex([-side_x,side_y,side_z]+place,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side_x,side_y,-side_z]+place,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side_x,-side_y,-side_z]+place,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// bottom
	R_BeginPolygon(shd);
		R_PolygonVertex([side_x,-side_y,side_z]+place,[0,1,0],[1,1,1],1);
		R_PolygonVertex([-side_x,-side_y,side_z]+place,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side_x,-side_y,-side_z]+place,[1,0,0],[1,1,1],1);
		R_PolygonVertex([side_x,-side_y,-side_z]+place,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// back
	R_BeginPolygon(shd);
		R_PolygonVertex([side_x,side_y,-side_z]+place,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side_x,-side_y,-side_z]+place,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side_x,-side_y,-side_z]+place,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side_x,side_y,-side_z]+place,[0,0,0],[1,1,1],1);
	R_EndPolygon();
}

void Render_Icosphere(vector pos,float scalefac, string shd)
{
	local float A,B,C,D,E,F,G,H;
	
	A = 0;
	B = 6 * scalefac;
	C = 5 * scalefac;
	D = 3 * scalefac;
	E = 3 * scalefac;
	F = 2 * scalefac;
	G = 5 * scalefac;
	H = 6 * scalefac;
	
	R_BeginPolygon(shd);
	R_PolygonVertex([A, A, -B]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([C, -D, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-F, -G, -E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([C, -D, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([A, A, -B]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([C, D, -E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([A, A, -B]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-F, -G, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-H, A, -E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([A, A, -B]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-H, A, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-F, G, -E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([A, A, -B]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-F, G, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([C, D, -E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([C, -D, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([C, D, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([H, A, E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([-F, -G, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([C, -D, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([F, -G, E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([-H, A, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-F, -G, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-C, -D, E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([-F, G, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-H, A, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-C, D, E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([C, D, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-F, G, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([F, G, E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([C, -D, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([H, A, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([F, -G, E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([-F, -G, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([F, -G, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-C, -D, E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([-H, A, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-C, -D, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-C, D, E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([-F, G, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-C, D, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([F, G, E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([C, D, -E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([F, G, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([H, A, E]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([F, -G, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([H, A, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([A, A, B]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([-C, -D, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([F, -G, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([A, A, B]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([-C, D, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-C, -D, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([A, A, B]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([F, G, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([-C, D, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([A, A, B]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();

	R_BeginPolygon(shd);
	R_PolygonVertex([H, A, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([F, G, E]+pos,[0,1,0],[1,1,1],1);
	R_PolygonVertex([A, A, B]+pos,[0,1,0],[1,1,1],1);
	R_EndPolygon();
}

void Render_TextOnObjects(entity subject,vector txtsize,string s)
{
	local vector screenpos = project(subject.origin);
	
	if (screenpos_z >= 0){
		screenpos_x -= stringwidth(s, TRUE, txtsize) * 0.5;
		screenpos_y -= txtsize_y * 0.5;
		screenpos_z = 0;
		drawstring(screenpos, s, txtsize, [1,1,1], 1, 0);
	}
}

void Render_PreviewModel(float vwidth, float vheight)
{
	local float distx = -300,distz=300;
	
	if(uiPanelMesh == TRUE){
		clearscene();
		setviewprop(VF_MIN, UI_PREVIEWMODELWIN_COORD);
		setviewprop(VF_SIZE, [UI_PREVIEWMODELWIN_SIZE_x,400,0]);
		drawsetcliparea(0,0,UI_PREVIEWMODELWIN_SIZE_x,vheight);
		setviewprop(VF_DRAWWORLD, FALSE);
		if(uiPanelMeshModel.size_x > 0 && uiPanelMeshModel.size_x < 256 || uiPanelMeshModel.size_y > 0 && uiPanelMeshModel.size_y < 256){
			setviewprop(VF_ORIGIN, [distx,0,distz]);
		}
		else if (uiPanelMeshModel.size_x > 256 && uiPanelMeshModel.size_x < 512 || uiPanelMeshModel.size_y > 256 && uiPanelMeshModel.size_y < 512){
			setviewprop(VF_ORIGIN, [distx*1.5,0,distz*1.5]);
		}
		else{
			setviewprop(VF_ORIGIN, [distx*3,0,distz*3]);
		}
		setviewprop(VF_ANGLES, [25,0,0]);
		setviewprop(VF_PERSPECTIVE, TRUE);
		setviewprop(VF_AFOV, 90);
		addentity(uiPanelMeshModel);
		//addentities(RENDER_MASK_PREVIEWMODEL);
		//dynamiclight_add([0,0,128],1400,[1,1,1],1);
		uiPanelMeshModel.angles_y += frametime * 5.5;
		drawresetcliparea();
		renderscene();
	}
}

void Render_TimelineModel(float vwidth, float vheight)
{
	
	if(uiTimeline == TRUE){
		clearscene();
		setviewprop(VF_MIN, [0,40,0]);
		setviewprop(VF_SIZE, [UI_PREVIEWMODELWIN_SIZE_x,400,0]);
		drawsetcliparea(0,0,UI_PREVIEWMODELWIN_SIZE_x,vheight);
		setviewprop(VF_DRAWWORLD, FALSE);
		setviewprop(VF_ORIGIN, [-200,0,0]);
		setviewprop(VF_ANGLES, [25,0,0]);
		setviewprop(VF_PERSPECTIVE, TRUE);
		setviewprop(VF_AFOV, 90);
		addentity(uiTimelineModel);
		uiTimelineModel.angles_y = inputCursorOrigin_x * 1.5;
		drawresetcliparea();
		renderscene();
	}
}

void Render_CharTracelines()
{
	if(cvar("debug_enabled")==1){
		renderEntity = world;
		while ((renderEntity = nextent(renderEntity))){
			if(renderEntity.gameClass == ENT_CLASS_NPC){
				Render_Cube([6,6,6],renderEntity.origin+renderEntity.entSightHeight,"green");
				Render_Cube([4,4,4],renderEntity.entSightOrg,"red");
				Render_Cube([8,8,8],renderEntity.entMeleeOrg,"red");
				Render_Cube([6,6,2],renderEntity.entOngroundOrg,"yellow");
			}
			if(renderEntity.gameClass == ENT_CLASS_PLAYER){
				Render_Cube([6,6,2],renderEntity.entOngroundOrg,"yellow");
			}
		}
	}
}

void Render_SelectedEntity()
{
	//if(cvar("debug_enabled")==1){
		renderEntity = world;
		while ((renderEntity = nextent(renderEntity))){
			if(renderEntity.edSelected == TRUE){
				Render_Cube([(renderEntity.maxs_x *1.1),(renderEntity.maxs_y*1.1),renderEntity.size_z/10],renderEntity.origin,"greentransp");
			}
		}
	//}
}

void Render_Bbox()
{
	renderEntity = world;
	while ((renderEntity = nextent(renderEntity))){
		if(renderEntity.gameClass == ENT_CLASS_MESHCOLLISION){
			Render_Cube([(renderEntity.maxs_x-renderEntity.mins_x)/2,(renderEntity.maxs_y-renderEntity.mins_y)/2,renderEntity.size_z],renderEntity.origin,"red");
		}
		if(renderEntity.gameClass == ENT_CLASS_GROUP){
			if(renderEntity.edGroupedEnt[0] != world){
				if(renderEntity.edSelected == FALSE){
					Render_Cube([(renderEntity.maxs_x-renderEntity.mins_x)/2,(renderEntity.maxs_y-renderEntity.mins_y)/2,renderEntity.size_z],renderEntity.origin,"blue");
				}
			}
		}
		if(renderEntity.gameClass == ENT_CLASS_PREFAB){
			Render_Cube([(renderEntity.maxs_x-renderEntity.mins_x)/2,(renderEntity.maxs_y-renderEntity.mins_y)/2,(renderEntity.maxs_z-renderEntity.mins_z)/2],renderEntity.origin,"green");
		}
		if(renderEntity.gameClass == ENT_CLASS_CRUMB){
			Render_Cube([(renderEntity.maxs_x-renderEntity.mins_x)/2,(renderEntity.maxs_y-renderEntity.mins_y)/2,(renderEntity.maxs_z-renderEntity.mins_z)/2],renderEntity.origin,"yellow");
		}
	}
}

void Render_TraceStepOrg()
{
	if(cvar("debug_enabled") == 1){
		renderEntity = world;
		while ((renderEntity = nextent(renderEntity))){
			if(renderEntity.gameClass == ENT_CLASS_PLAYER || renderEntity.gameClass == ENT_CLASS_NPC ){
				Render_Cube([8,8,2],renderEntity.physicsStepOrg,"red");
			}
		}
	}
}

void Render_Lights()
{
	renderEntity = world;
	while ((renderEntity = nextent(renderEntity))){
		if(renderEntity != world){
			if(renderEntity.gameClass == ENT_CLASS_BLANK){
				if(renderEntity.entLightRadius != 0){
					dynamiclight_add(renderEntity.origin,renderEntity.compLightRadius,renderEntity.compLightColor);
				}
			}
		}
	}
}

void Render_3dObjects()
{
	local int i;
	renderEntity = world;
	
	while ((renderEntity = nextent(renderEntity))){
		for(i = 0 ; i < ED_TOTAL_SELECTED ; i++){
			//visualize by layer visible
			if(renderEntity.edLayer == i && edLayerArray[i].edLayerActive == TRUE){
				//if type of selectedbytype is the one active
				if(renderEntity.edSelectedByType == TRUE){
					addentity(renderEntity);
				}
			}
		}	
	}
}

void Render_ShadingToggle()
{
	renderShadingToggle = !renderShadingToggle;
	cvar_set("render_shadeless",ftos(renderShadingToggle));
}

void Render_CrumbLines()
{
	local string crumbtxt;
	
	if(cvar("debug_enabled")==1){
		renderEntity = world;
		while ((renderEntity = nextent(renderEntity))){
			if(renderEntity.gameClass == ENT_CLASS_CRUMB){
				if(renderEntity.crumbFirst == TRUE){
					drawline(20,project(renderEntity.crumbParent.origin),project(renderEntity.origin),[1,0,0],1,0);
				}
				else if(renderEntity.crumbLast == TRUE){
					drawline(20,project(renderEntity.crumbPrevious.origin),project(renderEntity.origin),[1,0,0],1,0);
					drawline(20,project(renderEntity.origin),project(renderEntity.crumbParent.origin),[1,0,0],1,0);
				}
				else{
					drawline(20,project(renderEntity.crumbPrevious.origin),project(renderEntity.origin),[1,0,0],1,0);
				}
				if(renderEntity.edSelected == TRUE){
					crumbtxt = strcat("My id: ",etos(renderEntity)," next id: ", etos(renderEntity.crumbNext));
					Render_TextOnObjects(renderEntity,[8,8,0],crumbtxt);
				}	
			}
		}
	}
}

void Render_WeapTraceOrg()
{
	if(player){
		if(cvar("debug_enabled") == 1){
			Render_Cube([2,2,2],weapTraceOrg,"red");
		}
	}
}

void Render_GridAxis()
{
	local float a = 1;
	local float width = 2;
	local float up = edElevation;
	//axis x
	R_BeginPolygon("red");
	R_PolygonVertex([-ED_GRID_SIZE,-width,up],[0,1,0],[1,0,0],a);
	R_PolygonVertex([-ED_GRID_SIZE,width,up],[0,1,0],[1,0,0],a);
	R_PolygonVertex([ED_GRID_SIZE,width,up],[0,1,0],[1,0,0],a);
	R_PolygonVertex([ED_GRID_SIZE,-width,up],[0,1,0],[1,0,0],a);
	R_EndPolygon();
	//axis Y
	R_BeginPolygon("green");
	R_PolygonVertex([-width,-ED_GRID_SIZE,up],[0,1,0],[0,1,0],a);
	R_PolygonVertex([width,ED_GRID_SIZE,up],[0,1,0],[0,1,0],a);
	R_PolygonVertex([width,-ED_GRID_SIZE,up],[0,1,0],[0,1,0],a);
	R_PolygonVertex([-width,ED_GRID_SIZE,up],[0,1,0],[0,1,0],a);
	R_EndPolygon();
}

void Render_3dCursor()
{
	local float a = 1;
	local float width = 2;
	local float up = 0;
	local float sidelong = 64;
	
	//axis x
	R_BeginPolygon("red");
	R_PolygonVertex([-sidelong,-width,up]+inputCursor3dOrg,[0,1,0],[1,0,0],a);
	R_PolygonVertex([-sidelong,width,up]+inputCursor3dOrg,[0,1,0],[1,0,0],a);
	R_PolygonVertex([sidelong,width,up]+inputCursor3dOrg,[0,1,0],[1,0,0],a);
	R_PolygonVertex([sidelong,-width,up]+inputCursor3dOrg,[0,1,0],[1,0,0],a);
	R_EndPolygon();
	//axis Y
	R_BeginPolygon("green");
	R_PolygonVertex([-width,-sidelong,up]+inputCursor3dOrg,[0,1,0],[1,0,0],a);
	R_PolygonVertex([-width,sidelong,up]+inputCursor3dOrg,[0,1,0],[1,0,0],a);
	R_PolygonVertex([width,sidelong,up]+inputCursor3dOrg,[0,1,0],[1,0,0],a);
	R_PolygonVertex([width,-sidelong,up]+inputCursor3dOrg,[0,1,0],[1,0,0],a);
	R_EndPolygon();
}

void Render_RotPivot()
{
	if(edRotPivot){
		if(edMode == ED_MODE_ROTATE){
			if(edSelectedArray[0] != world){
				Render_Icosphere(edRotPivot.origin,vlen(camera.origin-edRotPivot.origin)/300,"blue");
			}
		}
	}
}

void Render_Grid()
{
	local float i;
	local float up = edElevation;
	local vector	col = [1,1,1];
	
	for (i = -ED_GRID_SIZE;i < ED_GRID_SIZE; i+=Ed_GridSize()){
		R_BeginPolygon("greydark");
		R_PolygonVertex([-ED_GRID_SIZE,i,up],[0,1,0],col,1);
		R_PolygonVertex([ED_GRID_SIZE,i,up],[0,1,0],col,1);
		R_EndPolygon();
		R_BeginPolygon("greydark");
		R_PolygonVertex([i,-ED_GRID_SIZE,up],[0,1,0],col,1);
		R_PolygonVertex([i,ED_GRID_SIZE,up],[0,1,0],col,1);
		R_EndPolygon();
	}
}

void Render_Visualize()
{
	Render_CharTracelines();
	if(gameState == GAME_STATE_ED){
		Render_Grid();
		Render_3dCursor();
		Render_SelectedEntity();
		Render_Bbox();
		Render_RotPivot();
		Anim_TimelineFrameVisualize(uiTimelineModel);
	}
	else if(gameState == GAME_STATE_RUNNING){
		Render_WeapTraceOrg();
		Render_TraceStepOrg();
	}
	Render_3dObjects();
	Render_Lights();
}

void Render_PostVisualize(float vwidth,float vheight)
{
	Render_CrumbLines();
	if(gameState == GAME_STATE_ED){
		Render_PreviewModel(vwidth,vheight);
		Render_TimelineModel(vwidth,vheight);
	}
}

void Render_ShaderInit()
{
	renderShadingToggle = TRUE;
	cvar_set("render_shadeless",ftos(renderShadingToggle));
	renderSelectedShader = shaderforname("yellow");
}

void Render_Init()
{
	Render_ShaderInit();
}