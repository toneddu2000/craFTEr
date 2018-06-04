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

//spawn
void EntFunc_SpawnTest()
{
	local vector spawnpos;
	
	edEntity = spawn();
	edEntity.gameClass = ENT_CLASS_BLANK;
	spawnpos = inputCursor3dOrg + ED_PLACE_FIXORG;
	setmodel(edEntity,PLAYER_MODEL);
	Util_EntityPropCommon(edEntity);
	setorigin(edEntity,spawnpos);
	setsize(edEntity,edEntity.entSizeMin,edEntity.entSizeMax);
	edEntity.edPlacedOrg = spawnpos;
}

//touch
void EntFunc_TouchTest()
{
	
}