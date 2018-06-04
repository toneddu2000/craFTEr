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

//void(entity e, float chan, string samp, float vol, float atten, optional float speedpct, optional float flags, optional float timeofs) sound
void Sound_SetListener()
{
	if(player){
		makevectors(input_angles);
		SetListener(player.origin,v_forward,v_right,v_up);
	}
}

void Sound_PlayWeapon(entity subject,string audiof)
{
	sound(subject,CHAN_WEAPON,audiof,1,SOUND_ATTENUATION_DEFAULT);
}

void Sound_PlayEnemyAwake(entity subject)
{
	local float sndtime = getsoundtime(subject,CHAN_VOICE);
	
	//if(sndtime == -1 || sndtime == 0){
		sound(subject,CHAN_VOICE,subject.entSoundAwake,1,SOUND_ATTENUATION_DEFAULT);
	//}
}

void Sound_PlayEnemyPatrol(entity subject)
{
	local float sndtime = getsoundtime(subject,CHAN_VOICE);
	
	if(sndtime == -1 || sndtime == 0){
		sound(subject,CHAN_VOICE,subject.entSoundPatrol,1,SOUND_ATTENUATION_DEFAULT);
	}
}

void Sound_PlayEnemyDead(entity subject)
{
	local float sndtime = getsoundtime(subject,CHAN_VOICE);
	
	if(sndtime == -1 || sndtime == 0){
		sound(subject,CHAN_VOICE,subject.entSoundDead,1,SOUND_ATTENUATION_DEFAULT);
	}
}

void Sound_PlayEnemyAttackNear(entity subject)
{
	local float sndtime = getsoundtime(subject,CHAN_VOICE);
	
	if(sndtime == -1 || sndtime == 0){
		sound(subject,CHAN_VOICE,subject.entSoundAttackNear,1,SOUND_ATTENUATION_DEFAULT);
	}
}

void Sound_PlayEnemyAttackFar(entity subject)
{
	local float sndtime = getsoundtime(subject,CHAN_VOICE);
	
	if(sndtime == -1 || sndtime == 0){
		sound(subject,CHAN_VOICE,subject.entSoundAttackFar,1,SOUND_ATTENUATION_DEFAULT);
	}
}

void Sound_PlayEnemyInjured(entity subject)
{
	local float sndtime = getsoundtime(subject,CHAN_VOICE);
	
	if(sndtime == -1 || sndtime == 0){
		if(subject.entInjured == TRUE){
			sound(subject,CHAN_VOICE,subject.entSoundInjured,1,SOUND_ATTENUATION_DEFAULT);
		}
	}
}

void Sound_Visualize()
{
	Sound_SetListener();
}