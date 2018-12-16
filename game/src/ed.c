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

void Ed_Restart()
{
	edEntitySearch = world;
	while ((edEntitySearch = nextent(edEntitySearch))){
		if(edEntitySearch != world){
			if(edEntitySearch.edPlaceable == TRUE){
				Util_ResetPlacedPosition(edEntitySearch);
				Util_ResetSize(edEntitySearch);
			}
		}
	}
	gameCanStart = TRUE;
	Game_Restart();
}

void Ed_LayerInit()
{
	local int i;
	
	for(i = 0 ; i < ED_TOTAL_SELECTED ; i++){
		edLayerArray[i] = spawn();
		edLayerArray[i].edLayerActive = TRUE;
		edLayerNameArray[i] = strcat("LAYER ",itos(i));
	}
}

void Ed_Init()
{
	edElevation = 8;
	edPlayerPlaced = FALSE;
	Ed_RotPivotInit();
	Ed_LayerInit();
}

void Ed_Visualize()
{
	if(gameState == GAME_STATE_ED){
		Ed_RotatePivot();
		Ed_Cursor();
	}
}

void Ed_PostVisualize()
{
}