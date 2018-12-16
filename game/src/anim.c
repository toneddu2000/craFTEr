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

void Anim_WeapPlayOnce(entity subject,float frmstart,float frmend)
{
	//important, without this frame won't "jump" to current first frame and will be stuck to old animation first frame
	if(subject.frame < frmstart){
		subject.frame = frmstart;
	}
	else if(subject.frame < frmend && subject.frame >= frmstart){
		subject.frame += GAME_FRAMEINCREMENT * (frametime * GAME_FRAMESPERSEC);
	}
	else{
		weapShot = FALSE;
		subject.frame = frmstart;
	}
}

void Anim_PlayFire(entity subject,float frmstart,float frmend)
{
	if(subject.frame < frmend){
		subject.frame += GAME_FRAMEINCREMENT * (frametime * GAME_FRAMESPERSEC);
	}
	else{
		subject.frame = frmstart;
	}
}

void Anim_SkelPlayLoop(entity subject,string frm)
{
	subject.frame = frameforname(subject.modelindex,frm);
	subject.frame1time += frametime;
}

void Anim_SkelPlayOnce(entity subject,string frm)
{
	local float dur = frameduration(subject.modelindex,frameforname(subject.modelindex,frm));
	subject.frame1time = 0;
	subject.frame = frameforname(subject.modelindex,frm);
	subject.frame1time += frametime;
}

void Anim_VisualizeFrameLoop(entity subject,string framename, float loopflag)
{
	local float mdl,frm,durat,ft;
	
	if(subject){
		if(subject.gameClass == ENT_CLASS_NPC){
			mdl = subject.modelindex;
			frm = frameforname(mdl,framename);
			durat = frameduration(mdl,frm);	
			if(subject.frame == frm){		
				if(loopflag){
					ft = subject.frame1time;	
					if(ft > durat){
						ft = 0;
						subject.frame1time = ft;
					}
				}
				else{
					if(ft < durat){
						ft = subject.frame1time;
					}
					else{
						ft = 0;
						subject.frame1time = ft;	
					}
				}
				UI_Message(strcat("duration: " ,ftos(durat), " - frametime: ",ftos(subject.frame1time), " - ft: ",ftos(ft)));
			}
		}
	}
}

void Anim_Run(entity subject,string framename)
{
	local float mdl,frm,durat,ft;
	
	if(subject){
		mdl = subject.modelindex;
		frm = frameforname(mdl,framename);
		durat = frameduration(mdl,frm);
		
		if(subject.frame == frm){
			/*
			if(strstrofs(framename,"_loop") != notfound){
				ft = subject.frame1time;	
				if(ft > durat){
					ft = 0;
					subject.frame1time = ft;
				}
			}
			else{
				if(ft < durat){
					ft = subject.frame1time;
				}
				else{
					ft = 0;
					subject.frame1time = ft;	
				}
			}
			*/
			if(subject.animLoop[frm] == TRUE){
				ft = subject.frame1time;	
				if(ft > durat){
					ft = 0;
					subject.frame1time = ft;
				}
			}
			else{
				if(ft < durat){
					ft = subject.frame1time;
				}
				else{
					ft = 0;
					subject.frame1time = ft;	
				}
			}
			subject.animTime[frm] = ft;
		}
	}
}

void Anim_RunTest(entity subject,string framename)
{
	local float mdl,frm,durat,ft;
	local float evtframe = 0.5;
	
	if(subject != world){
		mdl = subject.modelindex;
		frm = frameforname(mdl,framename);
		subject.frame = frm;
		durat = frameduration(mdl,frm);
		if(subject.aiState == AI_STATE_IDLE || subject.aiState == AI_STATE_PATROL || subject.aiState == AI_STATE_CHASE){
			subject.frame1time += frametime;	
			if(subject.frame1time > durat){
				subject.frame1time = 0;
			}
		}
		else{
			if(subject.frame1time < durat){
				subject.frame1time += frametime;
			}
		}
		subject.animTime[frm] = ft;
		
	}
}

void Anim_Reset(entity subject)
{
	/*if(subject != world){
		if(subject.animCanReset == TRUE){
			subject.frame1time = 0;
			subject.animCanReset = FALSE;
		}
	}*/
}

void Anim_Init(entity subject)
{
	local float mdl,frm,notfound = -1;
	local string framename;
	
	if(subject){
		mdl = subject.modelindex;	
		for(frm=0;frm<ANIM_TOTAL;frm++){
			framename = frametoname(subject.modelindex,frm);
			if(framename != ""){
				if(strstrofs(framename,"_loop") != notfound){
					//subject.animLoop[frm] = TRUE;
					subject.animTestLoop = TRUE;
				}
				else{
					//subject.animLoop[frm] = FALSE;
					subject.animTestLoop = FALSE;
				}
				//subject.animDuration[frm] = frameduration(mdl,frm);
				subject.animTestDuration = frameduration(mdl,frm);
			}
		}
	}
}

void Anim_VisualizeAndSetFrame(entity subject,string framename,float loopflag)
{
	local float mdl,duration,frm,percentage;
	
	if(subject != world){
		if(subject.gameClass == ENT_CLASS_NPC){
			mdl = subject.modelindex;
			frm = frameforname(mdl,framename);
			duration = frameduration(mdl,frm);	
			subject.frame = frm;
			if(loopflag == TRUE){
				//just resetting for viewing / testing purposes.. in loop mode animation will continue anyway
				if(subject.animIdleTime > duration){
					subject.animIdleTime = 0;
				}
				subject.animIdleTime += frametime;
			}
			else{
				//if animation reached end frame, mouse input will reset animtime / end frame(just for testing purposes)
				if(inputMouse1Pressed == TRUE && subject.animIdleEndFrame == TRUE){
					subject.animIdleEndFrame = FALSE;
					subject.animIdleTime = 0;
				}
				if(subject.animIdleTime < duration && subject.animIdleEndFrame == FALSE){
					subject.animIdleTime += frametime;
				}
				else{
					subject.animIdleEndFrame = TRUE;
				}
			}
			subject.frame1time = subject.animIdleTime;
			percentage = rint(( subject.animIdleTime / duration ) * 100);
			animTimelinePercentage = percentage;
			animTimelineWidth = rint( duration  * 100);
			UI_Message(strcat("duration: " ,ftos(duration), " - percentage: ",ftos(animTimelinePercentage), " - animtime: ",ftos(subject.animIdleTime)," - end frame: ",ftos(subject.animIdleEndFrame)));
		}
	}
}

void Anim_TimelineFrameVisualize(entity subject)
{
	local float mdl,duration,frm,percentage;
	
	if(uiTimeline == TRUE){
		if(subject != world){
			mdl = subject.modelindex;
			frm = uiTimelineFrameIndex;
			duration = frameduration(mdl,frm);
			subject.frame = frm;
			if(uiTimelinePlay == TRUE){
				//when reached end of anim, restart
				if(subject.animIdleTime > duration){
					subject.animIdleTime = 0;
				}
				subject.animIdleTime += frametime * uiTimelineSpeed;
			}
			subject.frame1time = subject.animIdleTime;
			percentage = rint(( subject.animIdleTime / duration ) * 100);
			animTimelinePercentage = percentage;
			animTimelineWidth = duration  * 100;
			animTimelineDuration = duration;
			//UI_Message(strcat("duration: " ,ftos(duration), " - percentage: ",ftos(animTimelinePercentage), " - animtime: ",ftos(subject.animIdleTime)," - end frame: ",ftos(subject.animIdleEndFrame)));
		}
	}
}
