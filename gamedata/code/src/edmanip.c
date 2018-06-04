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

//manip
void Ed_Cursor()
{
	if(inputCursor == TRUE){
		makevectors(input_angles);
		traceline(unproject([inputCursorOrigin_x, inputCursorOrigin_y, 0]), unproject([inputCursorOrigin_x, inputCursorOrigin_y, 5000]), MOVE_EVERYTHING, camera);
		//make sure cursor won't place at super top origins, when user touches header buttons
		if(inputCursorOrigin_y > (UI_HEADER_HEIGHT * 2)){
			inputCursor3dOrg = trace_endpos;
			inputCursor3dOrg_x = floor(trace_endpos_x / Ed_GridSize()) * Ed_GridSize();
			inputCursor3dOrg_y = floor(trace_endpos_y / Ed_GridSize()) * Ed_GridSize();
			inputCursor3dOrg_z = edElevation;
		}
	}
}

void Ed_MoveZ()
{
	local int i,j,g,p;
	local vector pos,dir=[0,0,0];
	
	if(inputCursor == TRUE){
		if(inputCursorDir != 0){
			
			if(inputCursorMoveBlock == FALSE){
				makevectors(world.angles);
				if(inputCursorDir == 1){
					dir = (v_up * Ed_GridSize());
				}
				else{
					//TONEDDUFIXME:instead of looking for first selected elem, it should be better to compare all selected elements and use the one below the others
					if(edSelectedArray[0].origin_z > (ED_GROUND_MARGIN + Ed_GridSize())){
						dir = (-v_up * Ed_GridSize());
					}
				}
			
				traceline(edSelectedArray[0].origin, edSelectedArray[0].origin + dir, MOVE_EVERYTHING, edSelectedArray[0]);
				pos = trace_endpos;
				pos_x = edSelectedArray[0].origin_x;
				pos_y = edSelectedArray[0].origin_y;
				pos_z = floor(trace_endpos_z / Ed_GridSize()) * Ed_GridSize();
							
				if(edSelectedArray[0] != world){
					if(edSelectedArray[0].gameClass == ENT_CLASS_GROUP){	
						setorigin(edSelectedArray[0],pos + edSelectedArray[0].edGroupedEnt[0].edParentOffset[0]);
						//all grouped  elements compare their origin to group entity
						for(g = 0 ; g < ED_TOTAL_SELECTED ; g++){
							if(edSelectedArray[0].edGroupedEnt[g] != world){
								setorigin(edSelectedArray[0].edGroupedEnt[g],edSelectedArray[0].origin + edSelectedArray[0].edGroupedEnt[g].edParentOffset[g]);
								Util_ResetSize(edSelectedArray[0].edGroupedEnt[g]);
							}
						}
					}
					else if(edSelectedArray[0].gameClass == ENT_CLASS_PREFAB){
						setorigin(edSelectedArray[0],pos + edSelectedArray[0].edGroupedEnt[0].edParentOffset[0]);
						//all prefab elements link their origin to parent entity
						for(p = 0 ; p < ED_TOTAL_SELECTED ; p++){
							if(edSelectedArray[0].edGroupedEnt[p] != world){
								setorigin(edSelectedArray[0].edGroupedEnt[p],edSelectedArray[0].origin + edSelectedArray[0].edGroupedEnt[p].edParentOffset[p]);
								Util_ResetSize(edSelectedArray[0].edGroupedEnt[p]);
							}
						}
					}
					//normal multi-selection
					else{
						//first element of selection array is parent
						setorigin(edSelectedArray[0],pos);
						edSelectedArray[0].edPlacedOrg = pos;
						for(i = 0; i < ED_TOTAL_SELECTED ; i++){
							if(edSelectedArray[i] != world){
								//move objects with relative offset to move elem group
								setorigin(edSelectedArray[i],edSelectedArray[0].origin + edMoveOffset[i]);	
								Util_ResetSize(edSelectedArray[i]);
								edSelectedArray[i].edPlacedOrg = pos;
								//move all collision objects with parent
								if(edSelectedArray[i].gameClass == ENT_CLASS_MESH){
									for(j = 0 ; j < ED_TOTAL_SELECTED ; j++){
										if(edSelectedArray[i].edCollisionChildren[j] != world){
											setorigin(edSelectedArray[i].edCollisionChildren[j],edSelectedArray[i].origin+edSelectedArray[i].edCollisionChildren[j].edParentOffset[j]);
											Util_ResetSize(edSelectedArray[i].edCollisionChildren[j]);
											edSelectedArray[i].edCollisionChildren[j].edPlacedOrg = edSelectedArray[i].edCollisionChildren[j].origin;
										}
									}
								}
							}
						}
					}
				}
				inputCursorMoveBlock = TRUE;
			}	
		}
	}
}

void Ed_MoveXY()
{	
	local int i,j,g,p;
	local vector pos=[0,0,0];
	
	Ed_SolidReset();
	if(inputCursor == TRUE){
		if(inputMove == TRUE){
			pos = inputCursor3dOrg;
			if(edSelectedArray[0] != world){
				if(edSelectedArray[0].gameClass == ENT_CLASS_GROUP){
					pos_z = edSelectedArray[0].origin_z;
					setorigin(edSelectedArray[0],pos + edSelectedArray[0].edGroupedEnt[0].edParentOffset[0]);
					Util_ResetSize(edSelectedArray[0]);
					edSelectedArray[0].edPlacedOrg = edSelectedArray[0].origin;
					//all grouped  elements compare their origin to group entity
					for(g = 0 ; g < ED_TOTAL_SELECTED ; g++){
						if(edSelectedArray[0].edGroupedEnt[g] != world){
							pos_z = edSelectedArray[0].edGroupedEnt[g].origin_z;
							setorigin(edSelectedArray[0].edGroupedEnt[g],edSelectedArray[0].origin + edSelectedArray[0].edGroupedEnt[g].edParentOffset[g]);
							Util_ResetSize(edSelectedArray[0].edGroupedEnt[g]);
							edSelectedArray[0].edGroupedEnt[g].edPlacedOrg = edSelectedArray[0].edGroupedEnt[g].origin;
						}
					}
				}
				else if(edSelectedArray[0].gameClass == ENT_CLASS_PREFAB){
					pos_z = edSelectedArray[0].origin_z;
					setorigin(edSelectedArray[0],pos + edSelectedArray[0].edGroupedEnt[0].edParentOffset[0]);
					Util_ResetSize(edSelectedArray[0]);
					edSelectedArray[0].edPlacedOrg = edSelectedArray[0].origin;
					//all prefab elements link their origin to parent entity
					for(p = 0 ; p < ED_TOTAL_SELECTED ; p++){
						if(edSelectedArray[0].edGroupedEnt[p] != world){
							pos_z = edSelectedArray[0].edGroupedEnt[p].origin_z;
							setorigin(edSelectedArray[0].edGroupedEnt[p],edSelectedArray[0].origin + edSelectedArray[0].edGroupedEnt[p].edParentOffset[p]);
							Util_ResetSize(edSelectedArray[0].edGroupedEnt[p]);
							edSelectedArray[0].edPlacedOrg = edSelectedArray[0].edGroupedEnt[p].origin;
						}
					}
				}
				//normal multi-selection
				else{
					//first element of selection array is parent
					pos_z = edSelectedArray[0].origin_z;
					setorigin(edSelectedArray[0],pos);
					Util_ResetSize(edSelectedArray[0]);
					edSelectedArray[0].edPlacedOrg = edSelectedArray[0].origin;
					for(i = 0; i < ED_TOTAL_SELECTED ; i++){
						if(edSelectedArray[i] != world){
							pos_z = edSelectedArray[i].origin_z;
							//move objects with relative offset to move elem group
							setorigin(edSelectedArray[i],edSelectedArray[0].origin + edMoveOffset[i]);	
							Util_ResetSize(edSelectedArray[i]);
							edSelectedArray[i].edPlacedOrg = edSelectedArray[i].origin;
							//move all collision objects with parent
							if(edSelectedArray[i].gameClass == ENT_CLASS_MESH){
								for(j = 0 ; j < ED_TOTAL_SELECTED ; j++){
									if(edSelectedArray[i].edCollisionChildren[j] != world){
										setorigin(edSelectedArray[i].edCollisionChildren[j],edSelectedArray[i].origin+edSelectedArray[i].edCollisionChildren[j].edParentOffset[j]);
										Util_ResetSize(edSelectedArray[i].edCollisionChildren[j]);
										edSelectedArray[i].edCollisionChildren[j].edPlacedOrg = edSelectedArray[i].edCollisionChildren[j].origin;
									}
								}
									
							}
						}
					}
				}
			}
		}
	}
}

void Ed_RotateSimple(entity subject)
{	
	subject.angles_y += 15;
	subject.edPlacedAngles = edSelectedArray[0].angles;
}

//by Spike
void Ed_RotateAroundPivot(entity source,entity external,float angleincr)
{
	vector pivot = source.origin;
	vector startangles = source.angles;
	vector endangles = source.angles + (source.avelocity * angleincr);
	float pitchscale = 1; //stupid bug. should be for model types rather than solid, but whatever.
	startangles_x *= pitchscale;
	endangles_x *= pitchscale;

	external.angles_x *= -1; //assuming mdl
	makevectors(external.angles);
	vector efw = v_forward;
	//v_right is redundant as it can be calculated with a simple crossproduct if needed.
	vector eup = v_up;

	makevectors(startangles);
	//figure out where the origin is in modelspace.
	vector mo, mf, mu, org = external.origin - pivot;
	mo_x = org * v_forward;
	mo_y = org * v_right;
	mo_z = org * v_up;
	
	mf_x = efw * v_forward;
	mf_y = efw * v_right;
	mf_z = efw * v_up;
	
	mu_x = eup * v_forward;
	mu_y = eup * v_right;
	mu_z = eup * v_up;
	//change the frame of reference, rotating everything around the pivot.
	makevectors(endangles);
	//figure out where that modelspace position is in worldspace
	org = mo_x*v_forward + mo_y*v_right + mo_z*v_up + pivot;
	efw = mf_x*v_forward + mf_y*v_right + mf_z*v_up;
	eup = mu_x*v_forward + mu_y*v_right + mu_z*v_up;
	//and move it there.
	external.angles = vectoangles(efw, eup); //assuming mdl
	setorigin(external, org);
	Util_ResetSize(external);
}

void Ed_Rotate()
{
	
	local int i,j=0,elemnum=0;
	local vector pivotrot,temporg=[0,0,0];
	
	//multi selection rotation
	if(edSelectedArray[0] != world && edSelectedArray[0].gameClass != ENT_CLASS_GROUP){
		//only 1 elem selected and not a group = rotate around its pivot-origin
		if(edSelectedArray[1] == world){
			Ed_RotateSimple(edSelectedArray[0]);
		}
		//multi selection = rotate elem around common pivot (common point between elem origins)
		if(edSelectedArray[1] != world){
			//first loop to increment elemnum and add every entity origin
			for(i = 0 ; i < ED_TOTAL_SELECTED ; i++){
				if(edSelectedArray[i] != world){
					elemnum++;
					temporg += edSelectedArray[i].origin;
				}
			}
			pivotrot = temporg;
			pivotrot_x = pivotrot_x / elemnum;
			pivotrot_y = pivotrot_y / elemnum;
			pivotrot_z = pivotrot_z / elemnum;
			setorigin(edRotPivot,pivotrot);
			//second loop to actually rotate elem around pivot
			for(j = 0 ; j < ED_TOTAL_SELECTED ; j++){
				if(edSelectedArray[j] != world){
					Ed_RotateAroundPivot(edRotPivot,edSelectedArray[j],45);
				}
			}
		}
	}
	//group rotation
	if(edSelectedArray[0] != world && edSelectedArray[0].gameClass == ENT_CLASS_GROUP){
		//only 1 elem for a group? weird
		if(edSelectedArray[0].edGroupedEnt[1] == world){
			edSelectedArray[0].angles_y += 90;
		}
		//multi selection = grouped child elem elem around parent elem
		if(edSelectedArray[0].edGroupedEnt[1] != world){
			for(i = 0 ; i < ED_TOTAL_SELECTED ; i++){
				if(edSelectedArray[0].edGroupedEnt[i] != world){
					Ed_RotateAroundPivot(edRotPivot,edSelectedArray[0].edGroupedEnt[i],ED_ROTATE_INCREMENT);
				}
			}
		}
	}
	
}

void Ed_RotPivotInit()
{
	edRotPivot = spawn();
	setorigin(edRotPivot,[0,0,0]);
	edRotPivot.angles = [0,0,0];
}

void Ed_RotatePivot()
{
	if(edRotPivot){
		edRotPivot.avelocity_y = ED_ROTATE_INCREMENT;
	}
}