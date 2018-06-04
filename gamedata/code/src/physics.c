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

void Physics_RelocateOrigin(entity subject)
{
	//important use setorigin instead of origin and reset size and model (thanks Spike!) http://forums.insideqc.com/viewtopic.php?f=16&p=58831#p58830
	tracebox(subject.origin,subject.mins,subject.maxs,subject.origin+subject.velocity,0,subject);
	setorigin(subject,trace_endpos);
	//setmodel(subject,subject.model);
	Util_ResetSize(subject);
}

void Physics_CollisionCheck(entity subject)
{
	local float fwdfrac,tracerangeforward=0.3;
	local vector neworg;
	//check for collided objects (NOTE: MOVE_HITMODEL is NECESSARY, otherwise static meshes collision won't work correctly!)
	makevectors(subject.angles);
	tracebox(subject.origin,subject.mins,subject.maxs,subject.origin+subject.velocity,MOVE_HITMODEL,subject);
	debugTraceFracForward = trace_fraction;
	fwdfrac = subject.physicsForwardFrac;
	//empty space in front of ent? tracebox for movements
	if(trace_fraction >= tracerangeforward){
		Physics_RelocateOrigin(subject);
	}
	//space blocked in front of ent? tracebox for steps
	else{
		//if(trace_fraction < 1){
		neworg = subject.origin;
		if(subject.gameClass == ENT_CLASS_PLAYER){
			if(input_movevalues_x > 0){
				neworg_z+=subject.size_z/5;
			}
		}
		else{
			if(subject.velocity_x != 0 || subject.velocity_y != 0){
				neworg_z+=subject.size_z/5;
			}
		}
		setorigin(subject,neworg);
		setsize(subject,subject.mins,subject.maxs);
	}
}

void Physics_Gravity(entity subject)
{	
	local float dist = 100,tracefracgrv = 0.7;
	local vector tracedir;
	
	if(subject){
		makevectors(world.angles);
		tracedir=-v_up*dist;
		subject.velocity = -v_up;
		subject.velocity *= 20;
		//tracebox for collision
		tracebox(subject.origin,subject.mins,subject.maxs,subject.origin+tracedir,MOVE_HITMODEL,subject);
		subject.physicsFallFrac = trace_fraction;
		//tracebox for movements
		if(subject.physicsFallFrac >= cvar("physics_tracefrac_gravity")){
			tracebox(subject.origin,subject.mins,subject.maxs,subject.origin+subject.velocity,MOVE_HITMODEL,subject);
			setorigin(subject,trace_endpos);
			setsize(subject,subject.mins,subject.maxs);
		}
	}
}

void Physics_OrientAI(entity subject)
{
	local vector orientpl = vectoangles(player.origin - subject.origin);
	local vector orientcrumb = vectoangles(subject.crumbActual.origin - subject.origin);
	local float r = random(100);
	
	if(subject.entHealth > 0){
		if(subject.aiState == AI_STATE_CHASE || subject.aiState == AI_STATE_ATTACKFAR || subject.aiState == AI_STATE_ATTACKNEAR){
			subject.angles_y = orientpl_y;
		}
		else{
			if(subject.crumbFollow == TRUE){
				subject.angles_y = orientcrumb_y;
			}
			else{
				subject.angles_y += 0.1 * (frametime * r);
			}
		}
	}
}

void Physics_MoveForwardAI(entity subject)
{
	local vector step = [0,0,0.5];
	
	if(subject != world){
		switch(subject.aiState){
			case AI_STATE_PATROL:
				if(subject.crumbFollow == TRUE){
					makevectors(subject.angles);
					subject.velocity = (normalize(subject.crumbActual.origin - subject.origin) + step);
					subject.velocity *= subject.entSpeedPatrol;
				}
				else{
					subject.velocity = [0,0,0];
				}
			break;
			case AI_STATE_CHASE:
				makevectors(subject.angles);
				subject.velocity = v_forward;
				subject.velocity *= subject.entSpeedChase;
			break;
			case AI_STATE_ATTACKFAR:
				subject.velocity = [0,0,0];
			break;
			case AI_STATE_ATTACKNEAR:
				subject.velocity = [0,0,0];
			break;
			case AI_STATE_INJURED:
				subject.velocity = [0,0,0];
			break;
			case AI_STATE_DEAD:
				subject.velocity = [0,0,0];
			break;
			default:
				UI_Warning("Physics_AI - no state");
			break;
		}
		//Physics_RelocateOrigin(subject);
		Physics_CollisionCheck(subject);
	}
}

void Physics_AI(entity subject)
{
	Physics_Gravity(subject);
	Physics_MoveForwardAI(subject);
	Physics_OrientAI(subject);
	touchtriggers(subject);
}

void Physics_MoveForwardPlayer()
{	
	if(player){
		makevectors([player.angles_x,input_angles_y,player.angles_z]);
		player.velocity = v_forward;
		player.velocity *= input_movevalues_x * (input_timelength * 0.3);
		Physics_CollisionCheck(player);
	}
}

void Physics_TraceStep(entity subject)
{
	if(subject.gameClass == ENT_CLASS_PLAYER){
		makevectors([subject.angles_x,input_angles_y,subject.angles_z]);
	}
	else{
		makevectors(subject.angles);
	}
	tracebox(subject.origin,subject.mins,subject.maxs,subject.origin+([0,0,cvar("physics_tracefrac_step_height")]+(v_forward*cvar("physics_tracefrac_step_depth"))),MOVE_HITMODEL,subject);
	debugTraceStepOrg = trace_endpos;
}

void Physics_MoveForwardCamera()
{	
	local vector inputvel;
	local float flyingvel = 0.9;
	
	if(camera){
		//little trick to avoid accidental camera movement while pressing button..dunno..
		if(inputMouse1Pressed == FALSE){
			if(viewTop == TRUE){
				makevectors(world.angles);
			}
			else{
				makevectors(input_angles);
			}
			inputvel = (v_forward * input_movevalues_x) + (v_right * input_movevalues_y);
			camera.velocity = (camera.velocity + (inputvel /25)) * cameraSpeed;
			tracebox(camera.origin,camera.mins,camera.maxs,camera.origin+camera.velocity,0,camera);
			Physics_RelocateOrigin(camera);
		}
	}
}

void Physics_PlayerExecute()
{
	if(gameState == GAME_STATE_ED){
		Physics_MoveForwardCamera();
	}
	else if(gameState == GAME_STATE_RUNNING){
		if(player != world){
			Physics_Gravity(player);
			Physics_MoveForwardPlayer();
			touchtriggers(player);
		}
	}
}