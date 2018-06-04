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

void Ent_HealthSubtract(entity subject,float h)
{
	if(subject.entCanBeDamaged == TRUE){
		subject.entHealth -= h;
	}
	if(subject.entHealth <= 0){
		subject.aiState = AI_STATE_DEAD;
	}
}

//BINARY FILE SAVE/LOAD
int stringSize = 100;
string textOutput;
void Bin_Write()
{
	local string text ="models/enemies/myenemy/enemy4.iqm";
	local float fp = fopen("myfile.bin",FILE_WRITE);
	fwrite(fp,(void *)text,stringSize);
	fclose(fp);
}

void Bin_Read()
{
	local float fp = fopen("myfile.bin",FILE_READ);
	fread(fp,(void *)textOutput,stringSize);
	fclose(fp);
}

//HASH TABLE
float mytable;
void HashTb_Create()
{
	//hashtable(float tabsize, optional float defaulttype) hash_createtab
	mytable = hash_createtab(10);
	//void(hashtable table, string name, __variant value, optional float typeandflags) hash_add 
	hash_add(mytable,"nome","Pippo ",HASH_ADD&EV_STRING);
	hash_add(mytable,"cognome","Zazz ",HASH_ADD&EV_STRING);
}

string HashTb_Get(float hashtb)
{
	local string str;
	//__variant(hashtable table, string name, optional __variant deflt, optional float requiretype, optional float index) hash_get
	str = hash_getkey(hashtb,1);
	return str;
}