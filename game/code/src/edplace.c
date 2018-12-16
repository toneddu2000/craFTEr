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

//place
void Ed_PlaceBlank()
{
	inputTemp3dOrg = inputCursor3dOrg;
	uiPanelEntFuncs = TRUE;
	/*
	local vector spawnpos;
	
	edEntity = spawn();
	edEntity.gameClass = ENT_CLASS_BLANK;
	spawnpos = inputCursor3dOrg + ED_PLACE_FIXORG;
	Util_EntityPropCommon(edEntity);
	setorigin(edEntity,spawnpos);
	setsize(edEntity,edEntity.entSizeMin,edEntity.entSizeMax);
	edEntity.edPlacedOrg = spawnpos;
	*/
	
	/*
		1. aprire dialogo per scrivere entfunc_spawnX - invio -> step 2
		2. aprire dialogo per scrivere entfunc_touchX - invio -> step 3
		3. ent = spawn() e setorigin in spawnpos
		4. ent.entClass = ENT_CLASS_BLANK
	*/
}

void Ed_PlaceBlankSpawn()
{
	if(isfunction(uiElListEntFuncs.cuiListTextArray[uiElListEntFuncs.cuiListTextIndex])){
		callfunction(uiElListEntFuncs.cuiListTextArray[uiElListEntFuncs.cuiListTextIndex]);
	}
	else{
		UI_Warning(strcat("Function ",uiElListEntFuncs.cuiListTextArray[uiElListEntFuncs.cuiListTextIndex]," is not present in game. Beware of uppercase/lowercase!"));
	}
}

void Ed_PlaceBlankSpawnOff()
{
	if(uiPanelEntFuncs == TRUE){
		uiPanelEntFuncs = FALSE;
	}
}

void Ed_PlaceMesh()
{
	edEntity = spawn();
	setorigin(edEntity,inputTemp3dOrg+ED_PLACE_FIXORG);
	setmodel(edEntity,edMeshStored);
	edEntity.gameClass = ENT_CLASS_MESH;
	edEntity.solid = SOLID_BBOX;
	Util_ResetSize(edEntity);
	edEntity.edSelectable = TRUE;
	edEntity.edShader = edShaderStored;
	Util_SetOldSolid(edEntity);
	edEntity.edSelectedByType = TRUE;
	edEntity.levelSaveThis = TRUE;
	edEntity.edLayer = 0;
	//now switch to select mode
	Ed_ModeMeshOff();
}

void Ed_PlaceCrumb()
{
	local int i=0,j;
	local vector spawnpos;
	
	if(edSelectedArray[0].gameClass == ENT_CLASS_NPC ){
		i=1;
	}
	else if (edSelectedArray[0].gameClass == ENT_CLASS_CRUMB){
		i=2;
	}
	else{
		UI_Warning("You must select a breadcrumb or an entity as first selection element");
		Ed_Deselect();
		edMode = ED_MODE_SELECT;
		return;
	}
	edEntity = spawn();
	Crumb_Prop(edEntity);
	spawnpos = inputCursor3dOrg + ED_PLACE_FIXORG;
	setorigin(edEntity,spawnpos);
	edEntity.edPlacedOrg = spawnpos;
	if(i == 1){
		edEntity.crumbParent = edSelectedArray[0];
		edSelectedArray[0].crumbFirstEnt = edEntity;
		edSelectedArray[0].crumbFollow = TRUE;
		edSelectedArray[0].crumbActual = edEntity;
		edEntity.crumbFirst = TRUE;
		edEntity.crumbLast = TRUE;
		edEntity.crumbFirstOrg = edSelectedArray[0].origin;
		//deselect monster and select this crumb for faster crumb placement
		Ed_Deselect();
		edSelectedArray[0] = edEntity;
	}
	else if (i == 2){
		edEntity.crumbPrevious = edSelectedArray[0];
		edSelectedArray[0].crumbNext = edEntity;
		edSelectedArray[0].crumbLast = FALSE;
		edEntity.crumbFirstOrg = edSelectedArray[0].crumbFirstOrg;
		edEntity.crumbParent = edSelectedArray[0].crumbParent;
		edEntity.crumbLast = TRUE;
		edEntity.crumbParent.crumbLastEnt = edEntity;
		//now makes new breadcrumb entity be the only selected. This will makes breadcrumb creation faster
		Ed_Deselect();
		edSelectedArray[0]= edEntity;
		edMode = ED_MODE_CRUMB;
	}
	//place this crumb child in first empty slot crumb's parent
	for(j=0;j<CRUMB_TOTAL;j++){
		if(edEntity.crumbParent.crumbAttached[j] == world){
			edEntity.crumbParent.crumbAttached[j] = edEntity;
		}
	}
	edEntity.nextthink = time + GAME_THINK_REFRESH;
	edEntity.think = Crumb_Think;
}

void Ed_PlaceColEntity()
{
	edEntity = spawn();
	setorigin(edEntity,inputCursor3dOrg+[0,0,8]);
	edEntity.gameClass = ENT_CLASS_MESHCOLLISION;
	edEntity.edSelectable = TRUE;
	edEntity.solid = SOLID_BSP;
	Util_SetOldSolid(edEntity);
	setsize(edEntity,[-32,-32,-32],[32,32,32]);
}
