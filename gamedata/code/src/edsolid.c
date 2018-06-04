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

//solid
void Ed_SolidMakeAll()
{
	//this will make possible selection of even non-solid entities since MOVE_EVERYTHING doesn't do its job, huh..
	edEntitySearch = world;
	while ((edEntitySearch = nextent(edEntitySearch))){
		if(edEntitySearch != world){
			edEntitySearch.solid = SOLID_BBOX;
		}
	}
}

void Ed_SolidReset()
{
	//this will reset every object after de-selection, gah..
	edEntitySearch = world;
	while ((edEntitySearch = nextent(edEntitySearch))){
		if(edEntitySearch != world){
			edEntitySearch.solid = edEntitySearch.edSolidOld;
			Util_ResetSize(edEntitySearch);
		}
	}
}

void Ed_SolidIngame()
{
	//this will reset every object after de-selection, gah..
	edEntitySearch = world;
	while ((edEntitySearch = nextent(edEntitySearch))){
		if(edEntitySearch != world){
			if(edEntitySearch.gameClass == ENT_CLASS_MESH){
				edEntitySearch.solid = SOLID_NOT;
				Util_ResetSize(edEntitySearch);
			}
		}
	}
}