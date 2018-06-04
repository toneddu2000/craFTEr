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

void Player_Think()
{
	if(gameState == GAME_STATE_ED){
		self.renderflags = RF_EXTERNALMODEL;
	}
	else if(gameState == GAME_STATE_RUNNING){
		self.renderflags = self.renderflags & ~RF_EXTERNALMODEL;
	}
	self.nextthink = time + 0.5;
	self.think = Player_Think;
}

void Player_Prop(entity subject)
{
	//important!without a model, traceline wouldn't work correctly!
	setmodel(subject,PLAYER_MODEL);
	Skel_Create(subject);
	skel_build(subject.skeletonindex, subject, subject.modelindex, 0, 0, 0, 1);
	subject.gameClass = ENT_CLASS_PLAYER;
	subject.entHealth = PLAYER_HEALTH_MAX;
	subject.entCanBeDamaged = TRUE;
	//setsize(subject,[-16,-16,-24],[16,16,32]);
	setsize(subject,[-20,-20,-20],[20,20,96]);
	subject.solid = SOLID_SLIDEBOX;
	setsize(subject,subject.mins,subject.maxs);
	//subject.drawmask = MASK_ENGINE;
	subject.nextthink = time + 0.5;
	subject.think = Player_Think;
}

void Player_Init()
{	
	if(player == world){
		player = spawn();
		Player_Prop(player);
		setorigin(player,[-200,0,200]);
		Util_EntityPropCommon(player);
		Util_SetOldSolid(player);
		Util_ResetSize(player);
	}
}