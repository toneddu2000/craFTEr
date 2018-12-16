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

//mesh
void Ed_MeshFolderUp()
{
	if(uiPanelMesh){
		if(uiMeshFoldersIndex < uiMeshFoldersTotal-1){
			uiMeshFoldersIndex++;
		}
	}
}

void Ed_MeshFolderDown()
{
	if(uiPanelMesh){
		if(uiMeshFoldersIndex > 0){
			uiMeshFoldersIndex--;
		}
	}
}

void Ed_MeshCategoryUp()
{
	if(uiPanelMesh){
		if(uiMeshCategoriesIndex < uiMeshCategoriesTotal-1){
			uiMeshCategoriesIndex++;
		}
	}
}

void Ed_MeshCategoryDown()
{
	if(uiPanelMesh){
		if(uiMeshCategoriesIndex > 0){
			uiMeshCategoriesIndex--;
		}
	}
}

void Ed_MeshModelDecrement()
{
	if(uiPanelMesh){
		edMeshesFolder = "";
		uiPanelMeshArray[uiPanelMeshIndex]="";
		uiPanelMeshIndex--;
		if(uiPanelMeshIndex <= 0){
			uiPanelMeshIndex = 0;
		}
	}
}

void Ed_MeshModelIncrement()
{
	if(uiPanelMesh){
		edMeshesFolder = "";
		uiPanelMeshArray[uiPanelMeshIndex]="";
		if(uiPanelMeshArray[uiPanelMeshIndex+1] != ""){
			uiPanelMeshIndex++;
		}
	}
}

void Ed_MeshFlatLight()
{
	cvar_set("render_shadeless","1");
}

void Ed_MeshSearch()
{
	local float catsearch,foldsearch,c,f;
	local string modelsstaticfolder = "models/static/";
	
	//first search for category
	catsearch = search_begin(strcat(modelsstaticfolder,"*"),TRUE,FALSE);
	uiMeshCategoriesTotal = search_getsize(catsearch);
	for(c = 0 ; c < uiMeshCategoriesTotal ; c++){
		uiMeshCategoriesArray[c] = search_getfilename(catsearch,c);
	}
	search_end(catsearch);
	//second search for files
	foldsearch = search_begin(strcat(uiMeshCategoriesArray[uiMeshCategoriesIndex],"*"),TRUE,FALSE);
	uiMeshFolderSelected = strreplace(uiMeshCategoriesArray[uiMeshCategoriesIndex],"",uiMeshFoldersArray[uiMeshFoldersIndex]);
	uiMeshFoldersTotal = search_getsize(foldsearch);
	for(f = 0 ; f < uiMeshFoldersTotal ; f++){
		uiMeshFoldersArray[f] = search_getfilename(foldsearch,f);
	}
	search_end(foldsearch);
}

void Ed_MeshCollision(entity subject)
{
	local float modelsearch = search_begin(strcat(edMeshesFolder,"*.iqm"),TRUE,FALSE);
	local int i,j=0,modelstot = search_getsize(modelsearch);
	local string modelcolname,modelused;
	local vector pos;
	
	if (modelsearch != -1){
		for(i = 0; i < modelstot ; i++){
			modelcolname = search_getfilename(modelsearch,i);
			modelused = strreplace(".iqm","",edMeshStored);
			modelused = strcat(modelused,"_col");
			if(modelcolname != ""){
				if(strstrofs(modelcolname,modelused) != -1){
					edEntity = spawn();
					edEntity.edCollisionParent = subject;
					subject.edCollisionChildren[j] = edEntity;
					pos = (inputTemp3dOrg+ED_PLACE_FIXORG) + edEntity.mins;
					
					setmodel(edEntity,modelcolname);
					setorigin(edEntity,subject.origin+edEntity.size);
					edEntity.gameClass = ENT_CLASS_MESHCOLLISION;
					edEntity.solid = SOLID_BBOX;
					Util_SetOldSolid(edEntity);
					//Quake encases a bounding box around an entity in the format 'X Y Z' (below origin, called mins),
					// 'X Y Z' (above origin, called maxs) to give it a particular size (maxs - mins) and an origin (size - maxs).
					Util_ResetSize(edEntity);
					subject.edCollisionChildren[j].edParentOffset[j] = pos;
					edEntity.forceshader = shaderforname("invisible");
					//Render_Cube([(edEntity.maxs_x-edEntity.mins_x)*2,(edEntity.maxs_y-edEntity.mins_y)*2,edEntity.size_z],edEntity.origin,"yellow");
					edEntity.edSelectable = TRUE;
					edEntity.edLayer = 0;
					j++;
				}
			}
		}
	}
	search_end(modelsearch);
}