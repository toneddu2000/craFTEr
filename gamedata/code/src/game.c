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

void Game_Precache()
{
	//model

	//player
	precache_model(PLAYER_MODEL);
	//sound

	//particles
	PART_ITEM_TORCHSMALL = particleeffectnum("items.torchsmall");
	PART_ITEM_TORCHBIG = particleeffectnum("items.torchbig");
	PART_ITEM_ARMOR = particleeffectnum("items.armor");
	PART_ITEM_HBOX = particleeffectnum("items.hbox");
	PART_ITEM_AMMO = particleeffectnum("items.ammo");
	PART_ITEM_TELEPORT = particleeffectnum("items.teleport");
	//
	PART_CHAR_HEADSHOT = particleeffectnum("items.headshot2");
	PART_CHAR_BODYSHOT = particleeffectnum("items.bodyshot");
	//
	PART_DEFER_EXPL = particleeffectnum("test.tr_rocket");
}

void Game_Prop()
{
	gameCanStart = TRUE;
}

void Game_Over()
{
}

void Game_New()
{
	localcmd("map game\n");
}

void Game_EditorLaunch()
{
	localcmd("map editor\n");
}

void Game_StateBasedOnMap()
{
	if(mapname == "maps/menu.bsp"){
		gameState = GAME_STATE_MENU;
	}
	else if(mapname == "maps/editor.bsp"){
		gameState = GAME_STATE_ED;
	}
	else if(mapname == "maps/game.bsp"){
		gameState = GAME_STATE_PRERUNNING;
	}
	else{
		error(strcat("mapname ",mapname," not loaded.\n"));
	}
}

void Game_StateMenu()
{
	gameState = GAME_STATE_MENU;
}

void Game_StateEd()
{
	gameState = GAME_STATE_ED;
}

void Game_StatePrerunning()
{
	gameState = GAME_STATE_PRERUNNING;
}

void Game_CommonInit()
{
	UI_Init();
	View_Init();
	Render_Init();
	Camera_Init();
	Player_Init();
	Level_Init();
}

void Game_FileCheck()
{
	local float f,notfound=-1;
	local string flname="system/pippo.game";
	f = fopen(flname, FILE_READ);
	if (f != notfound){
		gameFileFound = TRUE;
	}
	else{
		gameFileFound = FALSE;
	}
	fclose(f);
}

void Game_InitBasedOnMap()
{
	Game_Precache();
	Game_Prop();
	if(mapname == "maps/menu.bsp"){
		UI_Init();
		Menu_Init();
		View_Init();
	}
	else if(mapname == "maps/editor.bsp"){
		Game_CommonInit();
		Ed_Init();
	}
	else if(mapname == "maps/game.bsp"){
		Game_CommonInit();
		Weap_Init();
		Fx_Init();
	}
	else{
		error(strcat("mapname ",mapname," not valid.\n"));
	}
	Game_StateBasedOnMap();
}

void Game_WaitBeforeStart()
{
	//apparently FTE needs to wait a bit before recgnise mapname.
	gameDelayer = spawn();
	gameDelayer.nextthink = time + GAME_DELAYER_TIME;
	gameDelayer.think = Game_InitBasedOnMap;
}

void Game_Init()
{
	Game_WaitBeforeStart();
}

void Game_Restart()
{
	UI_Message("Game restarting..");
}