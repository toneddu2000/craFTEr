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

//sel
void Ed_Select()
{
	local int i;
	
	Ed_ModeMoveOff();
	Ed_SolidMakeAll();
	makevectors(input_angles);
	//TEMPREMOVE!!
	traceline(unproject([inputCursorOrigin_x, inputCursorOrigin_y, 0]), unproject([inputCursorOrigin_x, inputCursorOrigin_y, 5000]), MOVE_EVERYTHING, camera);
	if(trace_fraction < 1.0){
		if(trace_ent != world){
			for(i = 0; i < ED_TOTAL_SELECTED ; i++){
				if(edSelectedArray[i] == world){
					//search if same object is already in select list and which it's selectable (grouped children entities are not selectable by their own)
					if(trace_ent.edSelected == FALSE && trace_ent.edSelectable == TRUE){
						edSelectedArray[i] = trace_ent;
						//UI_Warning(strcat(etos(trace_ent)," SELECTED"));
						edSelectedArray[i].edSelected = TRUE;
						//important! Store here relative offset for every selected elem. Input_Move() will use it to move elem group!
						edMoveOffset[i]	= trace_ent.origin - edSelectedArray[0].origin ;
						//edSelectedArray[i].forceshader = renderSelectedShader;
					}
					//exit for loop when you find first empty slot. Otherwise 1st selected entity will occupy every free slot in array..
					break;
				}
			}
		}
	}
}

void Ed_Deselect()
{
	local int i,j;
	
	Ed_ModeMoveOff();
	Ed_SolidReset();
	//first, unflag all selected objects
	for(i = 0; i < ED_TOTAL_SELECTED ; i++){
		if(edSelectedArray[i] != world){
			//reset original shader to every mesh
			//edSelectedArray[i].forceshader = shaderforname(edSelectedArray[i].edShader);
			edSelectedArray[i].edSelected = FALSE;
		}
	}
	//second, purge all slots
	for(j = 0; j < ED_TOTAL_SELECTED ; j++){
		edSelectedArray[j] = world;
	}
}

void Ed_SelectCrumbTarget()
{
	Ed_Deselect();
	edMode = ED_MODE_SELECT;
}

void Ed_SelectByType()
{
	local float sel = uiElListSelByType.cuiListIndex;
	if(sel > ENT_CLASS_GROUP){
		sel = ENT_CLASS_GROUP;
	}
	//if(sel != ED_CLASS_NULL){
		//if selection is all types, reset everything: make all types renderable
		if(sel == ENT_CLASS_NULL){
			while ((edEntitySearch = nextent(edEntitySearch))){
				if(edEntitySearch != camera && edEntitySearch!=world){
					edEntitySearch.edSelectedByType = TRUE;
				}
			}
		}
		//otherwise let's unplug all the types we don't want to render
		else{
			while ((edEntitySearch = nextent(edEntitySearch))){
				if(edEntitySearch.gameClass == sel){
					if(edEntitySearch != camera && edEntitySearch!=world){
						edEntitySearch.edSelectedByType = TRUE;
					}
				}
				else{
					if(edEntitySearch != camera && edEntitySearch!=world){
						edEntitySearch.edSelectedByType = FALSE;
					}
				}
			}
		}
	//}
	edSelByTypeOpen=FALSE;
}
