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

/*
local float fsearch = search_begin(strcat("data/levels/","*.level"),TRUE,FALSE);
	local float fsize = search_getsize(fsearch);
	local int i;
	local string levname;
	
	//name already exists in levels folder?
	if (fsearch != -1){
		for(i=0;i<fsize;i++){
			levname = search_getfilename(fsearch,i);
			levname = strreplace("data/levels/","",levname);
			levname = strreplace(".level","",levname);
			if(levname == uiMessageText){
				levelOverwriteName = levname;
				//UI_Warning(strcat("Map name ",levname, " already exists. Overwrite?"));
				Level_OverwriteOn();
				return;
			}
		}
	}
	search_end(fsearch);
*/

void AnimEv_LoadEvent(entity subject)
{
	//local int i;
	local float fsearch,f,frm=0;
	local float notfound=-1;
	local int lnnum=0;
	local string ln,flname,text;
	/*
	for(i=0;i<ANIM_EV_TOTAL;i++){
		//if exists a frame for that model
		if(frametoname(subject.modelindex,(float)i)!= ""){
			fsearch = search_begin(strcat("data/animevent/",subject.model,ftos(subject.frame),".event"),TRUE,FALSE);
			//if exists an event file with that model name and that i frame
			if (fsearch != -1){
				//open selectedmodel_selectedframe.event file
				f = fopen(strcat("data/animevent/",uiMessageText,".event"), FILE_READ);
				//store vars
				//subject.animEvTime[i]=evtime,subject.animEvName[i]=evname,subject.animEvFrame[i]=evfr
				
				//close file
			}
		}
	}
	*/
	flname=strcat("data/animevent/",subject.model,".event");
	fsearch = search_begin(flname,TRUE,FALSE);
	if(fsearch != -1){
		f = fopen(flname, FILE_READ);
		// if f != not found
		if (f != -1){  
			// this line sets ln to the string read from the file with the file handle of f
			ln = fgets(f);
			// while there is still text
			while(ln != __NULL__){
				//read modfrmX_evtime
				if(strstrofs(ln,strcat("modfrm",ftos(frm),"_evtime:")) != notfound){
					text = strcat("modfrm",ftos(frm),"_evtime:");
					ln = strreplace(text,"",ln);
					subject.animEvTime[frm] = stof(ln);
				}
				//read modfrmX_evname
				if(strstrofs(ln,strcat("modfrm",ftos(frm),"_evname:")) != notfound){
					text = strcat("modfrm",ftos(frm),"_evname:");
					ln = strreplace(text,"",ln);
					subject.animEvName[frm] = ln;
				}
				//comment, new line directly
				else if(strstrofs(ln,"//") != notfound){
					ln = fgets(f);
				}
				//update frm number
				lnnum++;
				if(frametoname(subject.modelindex,frm)!= ""){
					frm++;
				}
				//reset text, just in case..
				text = "";
				//go to new line
				ln = fgets(f);   
			} 
		} 
		fclose(f);
	}
	search_end(fsearch);
}

void AnimEv_Execute(entity subject,string funcname)
{
	callfunction(funcname);
	//subject.nexthink = time + 0.01;
	subject.think();
}


void AnimEv_Run(entity subject)
{
	if(frametoname(subject.modelindex,subject.frame)!= ""){
		if(subject.animEvTime[subject.frame] == subject.animTime[subject.frame]){
			AnimEv_Execute(subject,subject.animEvName[subject.frame]);
		}
	}
}

void AnimEv_SaveEvent(entity subject)
{
	local float f,frm;
	local string flname,texttime,textfunc;
	flname=strcat("data/animevent/",subject.model,".event");
	f = fopen(flname, FILE_APPEND);
	for(frm=0;frm<15;frm++){
		if(frametoname(subject.modelindex,frm)!= ""){
			texttime = strcat("modfrm",ftos(frm),"_evtime:",ftos(uiTimelineTime));
			fputs(f,texttime,"\n");
			textfunc = strcat("modfrm",ftos(frm),"_evname:",uiTimelineFunc);
			fputs(f,textfunc,"\n");
			frm++;
		}
	}
	fclose(f);
}