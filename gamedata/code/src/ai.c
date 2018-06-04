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

void AI_DamageBasedOnDistance()
{
	local float playerdist = vlen((self.origin + self.entSightHeight)-(player.origin + player.entSightHeight));
	if(self.gameClass == ENT_CLASS_NPC){
		self.entAttackDamageCurrent = random(20);
		if(self.aiState == AI_STATE_ATTACKNEAR){
			if(playerdist < 100){
				self.entAttackDamageCurrent = self.aiAttackNearDamage + 5 + random(8);
			}
			else{
				self.entAttackDamageCurrent = self.aiAttackNearDamage + 3;
			}
		}
		else{
			self.entAttackDamageCurrent = self.aiAttackFarDamage;
		}
	}
	
}

void AI_RoamCrumb()
{
	
}

void AI_AwakeSound()
{
	if(self.soundAwakeUsed == FALSE){
		self.soundAwakeUsed = TRUE;
		if(self.entSoundAwake != ""){
			Sound_PlayEnemyAwake(self);
		}
	}
}

void AI_PatrolSound()
{
	if(self.aiAwake == FALSE){
		if(self.gameClass == ENT_CLASS_NPC){
			if(self.entSoundAwake != ""){
				Sound_PlayEnemyPatrol(self);
			}
		}
	}
}

void AI_ScanForPlayer(entity subject)
{
	makevectors(self.angles);
	//traceline(self.origin+self.entSightHeight,(self.origin+self.entSightHeight)+(v_forward*AI_PATROL_RADIUS),0,self);
	tracebox(self.origin+self.entSightHeight,self.mins,self.maxs,(self.origin+self.entSightHeight)+(v_forward*AI_PATROL_RADIUS),0,self);
	self.entSightOrg = trace_endpos;
	//traceFrac = trace_fraction;
	if(trace_fraction < 1){
		if(trace_ent.gameClass == ENT_CLASS_PLAYER){
			self.aiAwake = TRUE;
		}
	}
}

void AI_Idle()
{
	local float r = random(100);
	if(self.aiAwake == FALSE){
		self.aiState = AI_STATE_IDLE;
		self.angles_y += 0.1 * (frametime * r);
		AI_PatrolSound();
		AI_ScanForPlayer(self);
	}
}

void AI_Orient(entity subject,entity pivot)
{
	local vector orientpl = vectoangles(pivot.origin - subject.origin);
	local vector orientcrumb = vectoangles(subject.crumbActual.origin - subject.origin);
	local float updiff = vlen([0,0,subject.origin_z] - [0,0,pivot.origin_z]);
	
	//TONEDDUFIXME entity must have orientation limits on axis x, infact using all subject.angles will make entity stuck in ground
	if(subject.aiAwake == TRUE){
		subject.angles_y = orientpl_y;
	}
	else{
		if(subject.aiState == AI_STATE_PATROL){
			if(subject.crumbFollow == TRUE){
				subject.angles_y = orientcrumb_y;
			}
		}
	}
}

void AI_Patrol()
{
	if(self.aiAwake == FALSE){
		self.aiState = AI_STATE_PATROL;
		AI_PatrolSound();
		AI_ScanForPlayer(self);
	}	
}

void AI_PatrolCheck()
{
	if(self.crumbFollow == TRUE){
		AI_Patrol();
	}
	else{
		AI_Idle();
	}
}

//AI STATES
void AI_StateDead()
{
	self.aiState = AI_STATE_DEAD;
	self.aiAwake = FALSE;
	Anim_Reset(self);
	if(self.soundDeadUsed == FALSE){
		Sound_PlayEnemyDead(self);
		self.soundDeadUsed = TRUE;
	}
}

void AI_StateChase()
{
	self.aiState = AI_STATE_CHASE;
	//UI_Warning("AI CHASE");
}

void AI_StateRoam()
{
	if(self.crumbFollow == TRUE){
		self.aiState = AI_STATE_PATROL;
		//UI_Warning("AI ROAM");
	}
	else{
		self.aiState = AI_STATE_IDLE;
		//UI_Warning("AI IDLE");
	}
}

void AI_StateAttackFarWaitReset()
{
	self.aiState = AI_STATE_ATTACKFAR;
}

void AI_StateAttackFarWait()
{
	self.aiState = AI_STATE_ATTACKFARWAIT;
	self.nextthink = time + 5;
	self.think = AI_StateAttackFarWaitReset;
}

void AI_StateAttackFarTrace()
{
	traceline(self.origin+self.entSightHeight,(self.origin+self.entSightHeight)+v_forward*5000,MOVE_EVERYTHING,self);
	if(trace_fraction < 1){
		if(trace_ent.gameClass == ENT_CLASS_PLAYER){
			AI_DamageBasedOnDistance();
			//TONEDDUFIXME: health subtract - should it be tied to weapon trace even for non-player ents?
			Ent_HealthSubtract(trace_ent,self.entAttackDamageCurrent);
		}
	}
}

void AI_StateAttackNearTrace()
{
	traceline(self.origin+self.entSightHeight,(self.origin+self.entSightHeight)+v_forward*5000,MOVE_EVERYTHING,self);
	if(trace_fraction < 1){
		if(trace_ent.gameClass == ENT_CLASS_PLAYER){
			AI_DamageBasedOnDistance();
			//TONEDDUFIXME: health subtract - should it be tied to weapon trace even for non-player ents?
			Ent_HealthSubtract(trace_ent,self.entAttackDamageCurrent);
		}
	}
}


void AI_StateAttackFar()
{
	self.aiState = AI_STATE_ATTACKFAR;
	Anim_Reset(self);
	if(self.gameClass == ENT_CLASS_NPC){
		AI_StateAttackFarTrace();
		if(self.soundWeaponUsed == FALSE){
			Sound_PlayEnemyAttackFar(self);
			self.soundWeaponUsed = TRUE;
		}
	}
}

void AI_StateAttackNearMix()
{
	//UI_Warning("AI ATTACK NEAR MIX");
	self.animMixTime++;
	if(self.animMixTime > 100){
		self.animMix = FALSE;
		self.soundWeaponUsed = FALSE;
		self.animMixTime = 0;
	}
}

void AI_StateAttackFarMix()
{
	//UI_Warning("AI ATTACK FAR MIX");
	self.animMixTime++;
	if(self.animMixTime > 100){
		self.animMix = FALSE;
		self.soundWeaponUsed = FALSE;
		self.animMixTime = 0;
	}
}

void AI_StateAttackNear()
{
	self.aiState = AI_STATE_ATTACKNEAR;
	Anim_Reset(self);
	if(self.gameClass == ENT_CLASS_NPC){
		//UI_Warning("AI ATTACKNEAR EXECUTE");
		AI_StateAttackNearTrace();
		if(self.soundWeaponUsed == FALSE){
			Sound_PlayEnemyAttackNear(self);
			self.soundWeaponUsed = TRUE;
		}
	}
}

void AI_StateInjured()
{
	Anim_Reset(self);
	if(self.gameClass == ENT_CLASS_NPC){
		//if(self.soundInjuredUsed == FALSE){
			Sound_PlayEnemyInjured(self);
			self.soundInjuredUsed = TRUE;
		//}
	}	
}

void AI_StateCheck()
{
	self.aiPlayerDist = vlen(self.origin - player.origin);
	if(self.entHealth >0){
		if(self.entInjured == TRUE){
			AI_StateInjured();
		}
		else{
			AI_PatrolCheck();
			//TONEDDUFIXME:AI_Orient() could stay out of the block below? Othwerise put it back there!
			AI_Orient(self,player);
			if(self.aiAwake == TRUE){
				AI_AwakeSound();
				if(self.aiPlayerDist >= AI_ATTACKFAR_DISTANCE){
					AI_StateChase();
				}
				else if (self.aiPlayerDist < AI_ATTACKFAR_DISTANCE && self.aiPlayerDist >= AI_ATTACKNEAR_DISTANCE){
					if(self.aiAttackNearOnly == FALSE){
						self.aiState = AI_STATE_ATTACKFAR;
						if(self.gameClass == ENT_CLASS_NPC){
							//TONEDDUFIXME: add here anim-mix for skeletal models (IQM events?)
							AI_StateAttackFar();
						}
					}
					else{
						AI_StateChase();
					}
				}
				else if (self.aiPlayerDist < AI_ATTACKNEAR_DISTANCE){
					self.aiState = AI_STATE_ATTACKNEAR;
					if(self.gameClass == ENT_CLASS_NPC){
						//TONEDDUFIXME: add here anim-mix for skeletal models (IQM events?)
						AI_StateAttackNear();
					}
				}
			}
			else{
				AI_StateRoam();
				//TONEDDUFIXME: just a temp placeholder! It needs some sort of cone-of-vision moving around that sees in every direction and angles at every x millisec
				if(self.aiPlayerDist < AI_AWAKE_RADIUS){
					self.aiAwake = TRUE;
				}
			}
		}
	}
	else{
		AI_StateDead();
	}
}