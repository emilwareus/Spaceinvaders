#pragma once

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

struct Bitmap
{
	int index;
};

void InitializeGraphics(void* hwnd);
bool LoadBitmapFromFile(const char* filename, Bitmap& bitmap);
void BeginGraphics();
void DrawBitmap(Bitmap bitmap, int x, int y);
void DrawString(const char* text, int x, int y);
void EndGraphics();
void FreeBitmap(Bitmap bitmap);
void ShutdownGraphics();

#endif GRAPHICS_H_