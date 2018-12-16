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

void Weap_ModelChange()
{
	switch(weap.weapNumber){
		
	}
}

void Weap_DamageChange()
{
	switch(weap.weapNumber){
		
	}
}

void Weap_DamageBasedOnDistance(entity subject)
{
	local float monstdist = vlen((player.origin + player.entSightHeight)-(subject.origin + subject.entSightHeight));
	
	switch(weap.weapNumber){
	}
}

void Weap_ChangeUp()
{
	Weap_ModelChange();
	Weap_DamageChange();
}

void Weap_ChangeDown()
{
	Weap_ModelChange();
	Weap_DamageChange();
}

float Weap_FireTime()
{
	return 1;
}

void Weap_FireAnim()
{
	if(weapShot == TRUE){
	}
}

void Weap_FireTrace()
{
	makevectors(input_angles);
	//traceline(player.origin+player.entSightHeight,(player.origin+player.entSightHeight)+v_forward*5000,MOVE_EVERYTHING,player);
	traceline(cameraAttachedOrg,cameraAttachedOrg+v_forward*5000,MOVE_HITMODEL,player);
	//trace_endpos = weapTraceOrg;
	if(trace_fraction < 1){
		if(trace_ent.gameClass == ENT_CLASS_NPC || trace_ent.gameClass == ENT_CLASS_PLAYER){
			local float r = rint(random(3));
			if(r == 0){
				pointparticles(PART_CHAR_HEADSHOT,trace_endpos+[0,0,15],[0,0,0]);
			}
			else if(r == 1){
				pointparticles(PART_CHAR_BODYSHOT,trace_endpos+[0,0,15],[0,0,0]);
			}
			else if(r == 2){
				pointparticles(PART_CHAR_HEADSHOT,trace_endpos+[0,0,15],v_forward*200);
			}
			else{
				pointparticles(PART_CHAR_HEADSHOT,trace_endpos+[0,0,15],v_forward*-400+v_up*400);
			}
			
			Weap_DamageBasedOnDistance(trace_ent);
			Ent_HealthSubtract(trace_ent,5+random(10));
		}
	}
}

void Weap_FireTrigger()
{
	local float wtime = Weap_FireTime();
	
	if(time < weapFireTime){
		return;
	}
	weapShot = TRUE;
	Weap_FireTrace();
	weapFireTime = time + wtime;
}

void Weap_ProjectileTouch()
{
	if(self != world){
		if(other!=self.weapParent){
			if(other.entCanBeDamaged == TRUE){
				Ent_HealthSubtract(other,self.weapParent.aiAttackFarDamage + random(5));
			}
		}
	}
}


void Weap_ProjectileThink()
{
	local float life = time + 2;
	if(self != world){
		makevectors(self.weapParent.angles);
		self.velocity = v_forward;
		self.velocity *= self.weapProjVelocity;
		tracebox(self.origin,self.mins,self.maxs,self.origin+self.velocity,MOVE_EVERYTHING,self);
		setorigin(self,trace_endpos);
		setsize(self,self.mins,self.maxs);
		if(trace_fraction < 0.4){
			if(trace_ent.entCanBeDamaged == TRUE){
				Ent_HealthSubtract(trace_ent,self.weapParent.aiAttackFarDamage + random(5));
			}
			remove(self);
		}
		
		if(time  > life){
			remove(self);
		}
		self.nextthink = time + GAME_THINK_REFRESH;
		self.think = Weap_ProjectileThink;
	}
}

void Weap_ProjectileSpawn(entity subject)
{
	weapProjectile = spawn();
	makevectors(subject.angles);
	setorigin(weapProjectile,subject.origin+subject.entSightHeight+[0,0,30]+(v_forward*100));
	weapProjectile.gameClass = ENT_CLASS_PROJECTILE;
	weapProjectile.weapParent = subject;
	setmodel(weapProjectile,subject.entProjectileModel);
	weapProjectile.scale = 0.4;
	weapProjectile.solid = SOLID_NOT;
	setsize(weapProjectile,[-12,-12,-12],[12,12,12]);
	weapProjectile.weapProjVelocity = subject.entProjVelocity;
	weapProjectile.weapProjLife = subject.entProjLife;
	weapProjectile.touch = Weap_ProjectileTouch;
	weapProjectile.drawmask = MASK_ENGINE;
	weapProjectile.nextthink = time + GAME_THINK_REFRESH;
	weapProjectile.think = Weap_ProjectileThink;
}

void Weap_InstantShot(entity subject,float aimdist)
{
	makevectors(subject.angles);
	tracebox(subject.origin + subject.entSightHeight,subject.mins,subject.maxs,(subject.origin + subject.entSightHeight)+(v_forward*aimdist),MOVE_EVERYTHING,subject);
	subject.entMeleeOrg = trace_endpos;
	if(trace_fraction < 1){
		if(trace_ent.entCanBeDamaged == TRUE){
			
			//TONEDDUFIXME: temp, add damage based on distance/weap
			Ent_HealthSubtract(trace_ent,subject.aiAttackNearDamage+random(5));
		}
	}
}

void Weap_Visualize()
{
	Weap_FireAnim();
}

void Weap_Init()
{
	weap = spawn();
	weap.weapNumber = 0;
	setmodel(weap,"");
	weap.renderflags = RF_VIEWMODEL;
	weap.drawmask = MASK_VIEWMODEL;
	//prop
	weapShot = FALSE;
}