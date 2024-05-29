#include <stdio.h>
#include <stdlib.h>
#include "../deps/raylib/src/raylib.h"
#include <math.h>

typedef struct{
	int x;
	double time;
} frames;

int main ()
{
	SetTraceLogLevel(LOG_DEBUG | LOG_INFO | LOG_WARNING);
	InitWindow(1280, 720, "Input Latency Tester");
	

	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(1000);

	frames arr[200] = {0};
	int index = 0;

	bool screen = false;
	bool show = false;

	SetRandomSeed(GetFrameTime());

	int latency = 100;

	Color correctScreen = {0};

	int guesses = 0;
	int correct = 0;

	int longest = 0;

	while(!WindowShouldClose())
	{
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if(screen == show)
			{
				correctScreen = GREEN;
				correct++;
			}
			else
			{
				correctScreen = RED;
			}
			
			guesses++;
			
			screen = GetRandomValue(0, 1);

			longest = 0;
		}
		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && abs(GetMouseDelta().x) < 5)
		{
			show = !show;
		}
		
		if(IsWindowFocused())
		{
			HideCursor();
		}

		if(IsKeyPressed(KEY_SPACE))
		{
			correct = 0;
			guesses = 0;
		}

		if(IsKeyPressed(KEY_F11))
		{
			SetWindowMonitor(0);
			ToggleFullscreen();
		}

		if(GetFrameTime()*1000 > longest)
		{
			longest = GetFrameTime()*1000;
		}

		latency += GetMouseWheelMove();

		double now = GetTime();

		arr[index].x = GetMouseX();
		arr[index].time = now;
		index = ( index + 1) % 200;

		BeginDrawing();
		ClearBackground(BLACK);

		int x = GetMouseX();

		if(show == screen)
		{
			double target = now - (latency / 1000.0);
			frames * closest = arr;
			for(int i = 1; i < 200; i++)
			{
				if(fabs(closest->time-target) > fabs(arr[i].time - target))
				{
					closest = &arr[i];
				}
			}
			x = closest->x;
		}

		DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), correctScreen);
		correctScreen.a = fmax(correctScreen.a - GetFrameTime(), 0);

		DrawRectangle(x, 0, GetRenderWidth()*0.01, GetRenderHeight(), WHITE);

		DrawFPS(1,1);
		char str[10] = {0};
		snprintf(str, 10, "%ims", latency);
		DrawText(str, 1, 20, 20, GREEN);
		snprintf(str, 10, "%i/%i", correct, guesses);
		DrawText(str, 1, 50, 15, GREEN);
		snprintf(str, 10, "max %i ms", longest);
		DrawText(str, 1, GetRenderHeight()-50, 15, GREEN);

		snprintf(str, 10, "%i", show+1);
		DrawText(str, GetRenderWidth()/2, 0, 30, WHITE);
		EndDrawing();
	}

	return 0;
}