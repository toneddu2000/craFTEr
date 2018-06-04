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

//grid
float Ed_GridSize()
{
	switch(edGrid){
		case ED_GRID_16:
			return 16;
		case ED_GRID_32:
			return 32;
		case ED_GRID_64:
			return 64;
		case ED_GRID_128:
			return 128;
		case ED_GRID_256:
			return 256;
		case ED_GRID_512:
			return 512;
		case ED_GRID_1024:
			return 1024;
		case ED_GRID_2048:
			return 2048;
		default:
		break;
	}
	return 128;
}

void Ed_GridIncrement()
{
	edGrid++;
	if(edGrid > ED_GRID_2048){
		edGrid = ED_GRID_2048;
	}
}

void Ed_GridDecrement()
{
	edGrid--;
	if(edGrid < ED_GRID_16){
		edGrid = ED_GRID_16;
	}
}

void Ed_ElevationDown()
{
	edElevation -= Ed_GridSize();
	if(edElevation < 0){
		edElevation = 32;
	}
}

void Ed_ElevationUp()
{
	edElevation += Ed_GridSize();
	if(edElevation > 2048){
		edElevation = 2048;
	}
}