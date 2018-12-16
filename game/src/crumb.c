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

void Crumb_Touch()
{	
	if(other.gameClass == ENT_CLASS_NPC){
		if(self.crumbNext != world){
			other.crumbActual = self.crumbNext;
		}
		else{
			other.crumbActual = other.crumbFirstEnt;
		}
		//UI_Warning(strcat("Monster passes on crumb n. ",etos(self)));
	}
}

void Crumb_Think()
{	
	self.nextthink = time + GAME_THINK_REFRESH;
	self.think = Crumb_Think;
}

void Crumb_Prop(entity subject)
{
	setmodel(subject,"");
	setsize(subject,[-64,-64,-64],[64,64,64]);
	subject.solid = SOLID_TRIGGER;
	setsize(subject,subject.mins,subject.maxs);
	subject.gameClass = ENT_CLASS_CRUMB;
	subject.touch = Crumb_Touch;
	Util_EntityPropCommon(subject);
}