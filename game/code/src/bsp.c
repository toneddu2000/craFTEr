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

void Bsp_CubeCreate(string shd, vector midpoint, float radius,float cont)
{
	static brushface_t tmp_faces[6]; //MUST be static or global. the qcvm does not support taking the address of a regular local, not fully anyway.
	int tmp_numfaces = 6i;
	int tmp_contents = CONTENTBIT_SOLID;
	//a plane is defined as an infinitely large flat surface moved X units away from the origin along its normal (hence the negative axis get a negated midpoint. They're all then equally pushed out by the 'radius' value, hence why that is NOT negated.
	//moving eg a floor plane (ie: '0 0 1') along the x+y axis does not change its position along its normal (the z axis), so the dist wouldn't change in that case. to move a plane (or entire brush) by some model-space displacement, dist += displacement*planenormal; (the same goes for the st texturing planes, though they're not normalised and they might be negated... same principal applies)
	//define the 6 planes
	tmp_faces[0].planenormal = [1,0,0];//left
	tmp_faces[1].planenormal = [-1,0,0];//right
	tmp_faces[2].planenormal = [0,1,0];//front
	tmp_faces[3].planenormal = [0,-1,0];//back
	tmp_faces[4].planenormal = [0,0,1];//top
	tmp_faces[5].planenormal = [0,0,-1];//bottom
	for (int facenum = 0i; facenum < tmp_numfaces; facenum++){
		//position the plane through the given midpoint, and push it out by the radius along its normal.
		tmp_faces[facenum].planedist = (tmp_faces[facenum].planenormal * midpoint) + radius;
		tmp_faces[facenum].shadername = shd;
	}
	//give the brush to the engine
	brush_create(world.modelindex, &tmp_faces[0], tmp_numfaces, cont);
}

void Bsp_BoxCreate(string shd, vector midpoint, float radius,float cont)
{
	//create as static because qcvm can't handle pointers on local vars
	static brushface_t tmp_faces[6i];
	//define the 6 planes
	tmp_faces[0].planenormal = [1,0,0];//left
	tmp_faces[1].planenormal = [-1,0,0];//right
	tmp_faces[2].planenormal = [0,1,0];//front
	tmp_faces[3].planenormal = [0,-1,0];//back
	tmp_faces[4].planenormal = [0,0,1];//top
	tmp_faces[5].planenormal = [0,0,-1];//bottom
	//define distance of each face respect of midpoint
	tmp_faces[0].planedist = (tmp_faces[0].planenormal * midpoint) + radius * 4;
	tmp_faces[1].planedist = (tmp_faces[1].planenormal * midpoint) + radius * 4;
	tmp_faces[2].planedist = (tmp_faces[2].planenormal * midpoint) + radius * 0.5;
	tmp_faces[3].planedist = (tmp_faces[3].planenormal * midpoint) + radius * 0.5;
	tmp_faces[4].planedist = (tmp_faces[4].planenormal * midpoint) + radius * 0.5;
	tmp_faces[5].planedist = (tmp_faces[5].planenormal * midpoint) + radius * 0.5;
	//add shader to each face
	tmp_faces[0].shadername = "red";
	tmp_faces[1].shadername = "green";
	tmp_faces[2].shadername = "blue";
	tmp_faces[3].shadername = "yellow";
	tmp_faces[4].shadername = "white";
	tmp_faces[5].shadername = "greydark";
	//give the brush to the engine
	brush_create(world.modelindex, &tmp_faces[0], 6i, cont);
}

void Bsp_BoxPureblack(string shd,vector midpoint,float cont)
{
	local int i;
	local float rad = 32;
	
	//create as static because qcvm can't handle pointers on local vars
	static brushface_t tmp_faces[6i];
	//define the 6 planes
	tmp_faces[0].planenormal = [1,0,0];//left
	tmp_faces[1].planenormal = [-1,0,0];//right
	tmp_faces[2].planenormal = [0,1,0];//front
	tmp_faces[3].planenormal = [0,-1,0];//back
	tmp_faces[4].planenormal = [0,0,1];//top
	tmp_faces[5].planenormal = [0,0,-1];//bottom
	
	//add shader to each face
	tmp_faces[0].shadername = shd;
	tmp_faces[1].shadername = shd;
	tmp_faces[2].shadername = shd;
	tmp_faces[3].shadername = shd;
	tmp_faces[4].shadername = shd;
	tmp_faces[5].shadername = shd;
	//define distance of each face respect of midpoint
	for(i=0;i<6;i++){
		tmp_faces[i].planedist = (tmp_faces[0].planenormal * midpoint) + rad;
		tmp_faces[i]->sdir = '0 0 0';
		tmp_faces[i]->sbias = 0;
		tmp_faces[i]->tdir = '0 0 0';
		tmp_faces[i]->tbias = 0;
	}
	//give the brush to the engine
	brush_create(world.modelindex, &tmp_faces[0], 6i, cont);
}

void Bsp_PlaneCreate()
{
	static brushface_t tmp_faces[6]; //MUST be static or global. the qcvm does not support taking the address of a regular local, not fully anyway.
	int tmp_numfaces = 6i;
	int tmp_contents = CONTENTBIT_SOLID;
	local float rad = ED_GRID_SIZE;
	local vector midpoint = [0,0,0];
	//
	tmp_faces[0].planenormal = [1,0,0];//left
	tmp_faces[1].planenormal = [-1,0,0];//right
	tmp_faces[2].planenormal = [0,1,0];//front
	tmp_faces[3].planenormal = [0,-1,0];//back
	tmp_faces[4].planenormal = [0,0,1];//top
	tmp_faces[5].planenormal = [0,0,-1];//bottom
	//
	tmp_faces[0].planedist = (tmp_faces[0].planenormal * midpoint) + rad * 1;
	tmp_faces[1].planedist = (tmp_faces[1].planenormal * midpoint) + rad * 1;
	tmp_faces[2].planedist = (tmp_faces[2].planenormal * midpoint) + rad * 1;
	tmp_faces[3].planedist = (tmp_faces[3].planenormal * midpoint) + rad * 1;
	tmp_faces[4].planedist = (tmp_faces[4].planenormal * midpoint) + 2;
	tmp_faces[5].planedist = (tmp_faces[5].planenormal * midpoint) + 2;
	//
	tmp_faces[0].shadername = "pureblack";
	tmp_faces[1].shadername = "pureblack";
	tmp_faces[2].shadername = "pureblack";
	tmp_faces[3].shadername = "pureblack";
	tmp_faces[4].shadername = "pureblack";
	tmp_faces[5].shadername = "pureblack";
	//
	
	brush_create(world.modelindex, &tmp_faces[0], tmp_numfaces, -2);
}

void Bsp_RoomCreate(string shd, float rad,float cont)
{
	local float sd = rad * 2;
	local vector frw =[0,sd,0],bck=[0,-sd,0],lft=[-sd,0,0],rgt=[sd,0,0],dwn=[0,0,-sd],up=[0,0,sd];
	
	Bsp_BoxCreate(shd,up,rad,cont);
	Bsp_BoxCreate(shd,dwn,rad,cont);
	Bsp_BoxCreate(shd,frw,rad,cont);
	Bsp_BoxCreate(shd,bck,rad,cont);
	Bsp_BoxCreate(shd,lft,rad,cont);
	Bsp_BoxCreate(shd,rgt,rad,cont);
}

void Bsp_Room()
{
	static brushface_t cube1[6i],cube2[6i],cube3[6i],cube4[6i],cube5[6i],cube6[6i];
	local float sd = ED_GRID_SIZE-256,sp = sd *2;
	local vector frw =[0,sp,0],bck=[0,-sp,0],lft=[sp,0,0],rgt=[-sp,0,0],dwn=[0,0,-sp],up=[0,0,sp];
	local int i;
	
	Bsp_PlaneCreate();
	//define the 6 planes - first cube
	cube1[0].planenormal = [1,0,0];//left
	cube1[1].planenormal = [-1,0,0];//right
	cube1[2].planenormal = [0,1,0];//front
	cube1[3].planenormal = [0,-1,0];//back
	cube1[4].planenormal = [0,0,1];//top
	cube1[5].planenormal = [0,0,-1];//bottom
	for(i=0;i<6;i++){
		cube1[i].shadername = "red";
		cube1[i].planedist = (cube1[i].planenormal * frw) + sd;
	}
	brush_create(world.modelindex, &cube1[0], 6i, CONTENTBIT_NONE);
	//define the 6 planes - second cube
	cube2[0].planenormal = [1,0,0];//left
	cube2[1].planenormal = [-1,0,0];//right
	cube2[2].planenormal = [0,1,0];//front
	cube2[3].planenormal = [0,-1,0];//back
	cube2[4].planenormal = [0,0,1];//top
	cube2[5].planenormal = [0,0,-1];//bottom
	for(i=0;i<6;i++){
		cube2[i].shadername = "green";
		cube2[i].planedist = (cube2[i].planenormal * bck) + sd;
	}
	brush_create(world.modelindex, &cube2[0], 6i, CONTENTBIT_NONE);	
	//define the 6 planes - third cube
	cube3[0].planenormal = [1,0,0];//left
	cube3[1].planenormal = [-1,0,0];//right
	cube3[2].planenormal = [0,1,0];//front
	cube3[3].planenormal = [0,-1,0];//back
	cube3[4].planenormal = [0,0,1];//top
	cube3[5].planenormal = [0,0,-1];//bottom
	for(i=0;i<6;i++){
		cube3[i].shadername = "blue";
		cube3[i].planedist = (cube3[i].planenormal * lft) + sd;
	}
	brush_create(world.modelindex, &cube3[0], 6i, CONTENTBIT_NONE);
	//define the 6 planes - fourth cube
	cube4[0].planenormal = [1,0,0];//left
	cube4[1].planenormal = [-1,0,0];//right
	cube4[2].planenormal = [0,1,0];//front
	cube4[3].planenormal = [0,-1,0];//back
	cube4[4].planenormal = [0,0,1];//top
	cube4[5].planenormal = [0,0,-1];//bottom
	for(i=0;i<6;i++){
		cube4[i].shadername = "yellow";
		cube4[i].planedist = (cube4[i].planenormal * rgt) + sd;
	}
	brush_create(world.modelindex, &cube4[0], 6i, CONTENTBIT_NONE);
	//define the 6 planes - fifth cube
	cube5[0].planenormal = [1,0,0];//left
	cube5[1].planenormal = [-1,0,0];//right
	cube5[2].planenormal = [0,1,0];//front
	cube5[3].planenormal = [0,-1,0];//back
	cube5[4].planenormal = [0,0,1];//top
	cube5[5].planenormal = [0,0,-1];//bottom
	for(i=0;i<6;i++){
		cube5[i].shadername = "white";
		cube5[i].planedist = (cube5[i].planenormal * dwn) + sd;
	}
	brush_create(world.modelindex, &cube5[0], 6i, CONTENTBIT_NONE);
	//define the 6 planes - sixth cube
	cube6[0].planenormal = [1,0,0];//left
	cube6[1].planenormal = [-1,0,0];//right
	cube6[2].planenormal = [0,1,0];//front
	cube6[3].planenormal = [0,-1,0];//back
	cube6[4].planenormal = [0,0,1];//top
	cube6[5].planenormal = [0,0,-1];//bottom
	for(i=0;i<6;i++){
		cube6[i].shadername = "greydark";
		cube6[i].planedist = (cube6[i].planenormal * up) + sd;
	}
	brush_create(world.modelindex, &cube6[0], 6i, CONTENTBIT_NONE);
	
	//
	bspLoaded = TRUE;
}

void Bsp_Init()
{
	bspLoaded = FALSE;
	bspEntity = spawn();
	bspEntity.nextthink = time + GAME_LEVEL_LOADING_TIME;
	bspEntity.think = Bsp_Room;
}