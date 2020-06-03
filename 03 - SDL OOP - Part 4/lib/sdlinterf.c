// SDL-Interface-Funktionen für C / C++
//
// Klaus Kusche, 2012, vereinheitlichte Version für alle Beispiele
// Klaus Kusche, 2014, umgestellt auf SDL Version 2, mit Pixel-Array

#include <stdio.h>
#include <stdlib.h>

#include "sdlinterf.h"
#include "SDL2/SDL.h"

// ein Wert kleiner als der kleinste Koordinatenwert
#define MINVAL -1
// ein Wert größer als der größte Koordinatenwert
#define MAXVAL 9999

// kleinste / größte Koordinaten des rechteckigen Bildausschnittes,
// der vom nächsten sdlUpdate aktualisiert werden muss
// (ursprünglich: gar keiner).
static int minX = MAXVAL, maxX = MINVAL, minY = MAXVAL, maxY = MINVAL;

static SDL_Window *myWindow;
static SDL_Renderer *myRenderer;
static SDL_Texture *myTexture;
// Array von Pixeln
static Uint32 myPixArray[SDL_Y_SIZE * SDL_X_SIZE];

// zyklische Farbtabelle mit 192 Farben für Fraktale
static struct colors {
  int r, g, b;
} colormap[192];

void sdlInit(void)
{
  int i;
  
  if (SDL_Init(SDL_INIT_VIDEO)  != 0) { 
    fprintf(stderr, "Could not initialize SDL: %s.\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  atexit(SDL_Quit);
  
  myWindow = SDL_CreateWindow("SDL Graphics",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    SDL_X_SIZE, SDL_Y_SIZE, 0);
  if (myWindow == NULL) {
    fprintf(stderr, "Could not create SDL Window: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  myRenderer = SDL_CreateRenderer(myWindow, -1, 0);
  if (myRenderer == NULL) {
    fprintf(stderr, "Could not create SDL Renderer: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  myTexture = SDL_CreateTexture(myRenderer, SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                SDL_X_SIZE, SDL_Y_SIZE);
  if (myTexture == NULL) {
    fprintf(stderr, "Could not create SDL Renderer: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  if (SDL_SetTextureBlendMode(myTexture, SDL_BLENDMODE_NONE) != 0) { 
    fprintf(stderr, "Could not set SDL blend mode: %s.\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  sdlSetBlack();

  for (i = 0; i < 64; ++i) {
    colormap[i].r = 0;
    colormap[i].g = 4 * i;
    colormap[i].b = 255 - 4 * i;
    colormap[64 + i].r = 4 * i;
    colormap[64 + i].g = 255 - 4 * i;
    colormap[64 + i].b = 0;
    colormap[128 + i].r = 255 - 4 * i;
    colormap[128 + i].g = 0;
    colormap[128 + i].b = 4 * i;
  }
}

void sdlExit(void)
{
  SDL_Quit();
}

static inline Uint32 getPixVal(int r, int g, int b)
{
  // ARGB-Wert berechnen, Alpha ist fix 255
  return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff) | 0xff000000;
}

static inline void putPixel(int x, int y, Uint32 pixel)
{
  myPixArray[y * SDL_X_SIZE + x] = pixel;
}

void sdlSetBlack(void)
{
  Uint32 pixel = getPixVal(0, 0, 0);
  Uint32 *p;

  for (p = myPixArray; p < myPixArray + SDL_X_SIZE * SDL_Y_SIZE; ++p) {
    *p = pixel;
  }

  // alles ist modifiziert
  minX = 0;
  minY = 0;
  maxX = SDL_X_SIZE - 1;
  maxY = SDL_Y_SIZE - 1;
}

void sdlDrawPoint(int x, int y, int r, int g, int b)
{
  if ((x < 0) || (x >= SDL_X_SIZE) ||
      (y < 0) || (y >= SDL_Y_SIZE)) {
    fprintf(stderr, "Point %d/%d is offscreen\n", x, y);
    exit(EXIT_FAILURE);
  }

  putPixel(x, y, getPixVal(r, g, b));

  // ev. modifizierten Bereich vergrößern
  if (x < minX) minX = x;
  if (y < minY) minY = y;
  if (x > maxX) maxX = x;
  if (y > maxY) maxY = y;
}

void sdlDrawCyclicPoint(int x, int y, int color)
{
  if (color < 0) {
    sdlDrawPoint(x, y, 0, 0, 0);
  } else {
    struct colors *cPtr = &(colormap[color % 192]);
    sdlDrawPoint(x, y, cPtr->r, cPtr->g, cPtr->b);    
  }
}

void sdlDrawRect(int centerX, int centerY, int extX, int extY,
                 int r, int g, int b)
{
  Uint32 pixel;

  int firstX = centerX - extX;
  int firstY = centerY - extY;
  int lastX = centerX + extX;
  int lastY = centerY + extY;

  Uint32 *p1, *p2, *e1, *e2;

  if ((extX < 0) || (extY < 0) ||
      (firstX < 0) || (firstY < 0)  ||
      (lastX >= SDL_X_SIZE) || (lastY >= SDL_Y_SIZE)) { 
    fprintf(stderr, "Rect (%d/%d +- %d/%d) offscreen.\n",
            centerX, centerY, extX, extY);
    exit(EXIT_FAILURE);
  }
  
  pixel = getPixVal(r, g, b);
   
  p1 = myPixArray + firstY * SDL_X_SIZE + firstX;
  e1 = myPixArray + lastY * SDL_X_SIZE + firstX;
  while (p1 <= e1) {
    p2 = p1;
    e2 = p1 + extX + extX;
    while (p2 <= e2) {
      *(p2++) = pixel;
    }
    p1 += SDL_X_SIZE;
  }

  // ev. modifizierten Bereich vergrößern
  if (firstX < minX) minX = firstX;
  if (firstY < minY) minY = firstY;
  if (lastX > maxX) maxX = lastX;
  if (lastY > maxY) maxY = lastY;
}

void sdlDrawLine(int x1, int y1, int x2, int y2, int r, int g, int b)
{
  Uint32 pixel;
  int exchanged;
  int t;
  int deltaX, deltaY, stepY, error;
  int x, y;

  if ((x1 < 0) || (x1 >= SDL_X_SIZE) ||
      (y1 < 0) || (y1 >= SDL_Y_SIZE) ||
      (x2 < 0) || (x2 >= SDL_X_SIZE) ||
      (y2 < 0) || (y2 >= SDL_Y_SIZE)) {
    fprintf(stderr, "Line %d/%d  - %d/%d is offscreen\n",
            x1, y1, x2, y2);
    exit(EXIT_FAILURE);
  }

  // ev. modifizierten Bereich vergrößern 
  // (vorher, weil x1/x2/y1/y2 unten verändert werden)
  if (x1 <= x2) {
    if (x1 < minX) minX = x1;
    if (x2 > maxX) maxX = x2;
  } else {
    if (x2 < minX) minX = x2;
    if (x1 > maxX) maxX = x1;
  }
  if (y1 <= y2) {
    if (y1 < minY) minY = y1;
    if (y2 > maxY) maxY = y2;
  } else {
    if (y2 < minY) minY = y2;
    if (y1 > maxY) maxY = y1;
  }

  pixel = getPixVal(r, g, b); 

  exchanged = (abs(y2 - y1) > abs(x2 - x1));
  if (exchanged) {
    t = x1; x1 = y1; y1 = t;
    t = x2; x2 = y2; y2 = t;
  }
  if (x1 > x2) {
    t = x1; x1 = x2; x2 = t;
    t = y1; y1 = y2; y2 = t;
  }
  deltaX = x2 - x1;
  deltaY = abs(y2 - y1);
  error = deltaX / 2;
  y = y1;
  if (y1 < y2) stepY = 1;
  else stepY = -1;
  for (x = x1; x <= x2; ++x) {
     if (exchanged) putPixel(y, x, pixel);
     else putPixel(x, y, pixel);
     error = error - deltaY;
     if (error < 0) {
       y = y + stepY;
       error = error + deltaX;
     }
  }
}

static void drawCircLine(int centerX, int centerY, int x1, int x2, int y,
                         Uint32 pixel, int part)
{
  int i, mY, pY;

  if (x1 < 0) x1 = 0;
  if (y < 0) y = 0;
  mY = centerY - y;
  pY = centerY + y;
  if (part & SDL_CIRC_FILLED) {
    x2 = 0;
  } else if (x2 > x1) {
    x2 = x1;
  }

  for (i = x1; i >= x2; --i) {
    if (part & SDL_CIRC_UPPER_LEFT)
      putPixel(centerX - i, mY, pixel);
    if (part & SDL_CIRC_UPPER_RIGHT)
      putPixel(centerX + i, mY, pixel);
    if (part & SDL_CIRC_LOWER_LEFT)
      putPixel(centerX - i, pY, pixel);
    if (part & SDL_CIRC_LOWER_RIGHT)
      putPixel(centerX + i, pY, pixel);
  }
}

void sdlDrawCirc(int centerX, int centerY, int radX, int radY,
                 int r, int g, int b)
{
  sdlDrawCircPart(centerX, centerY, radX, radY, r, g, b,
                  SDL_CIRC_ALL | SDL_CIRC_FILLED );
}

void sdlDrawCircPart(int centerX, int centerY, int radX, int radY,
                     int r, int g, int b, int part)
{
  Uint32 pixel;
  int x, y, oldX, lastX = 0, lastY = 0;
  int chgX, chgY;
  int err;
  int sqrX, sqrY;
  int stopX, stopY;
  int leftX, upperY, rightX, lowerY;

  leftX =  centerX - ((part & SDL_CIRC_LEFT) ? radX : 0);
  upperY = centerY - ((part & SDL_CIRC_UPPER) ? radY : 0);
  rightX = centerX + ((part & SDL_CIRC_RIGHT) ? radX : 0);
  lowerY = centerY + ((part & SDL_CIRC_LOWER) ? radY : 0);
  if ((radX < 0) || (radY < 0) ||
      (leftX < 0) || (upperY < 0) ||
      (rightX >= SDL_X_SIZE) || (lowerY >= SDL_Y_SIZE)) { 
    fprintf(stderr, "Circ %d/%d +- %d/%d is offscreen\n",
            centerX, centerY, radX, radY);
    exit(EXIT_FAILURE);
  }

  pixel = getPixVal(r, g, b); 

  // if both rad's are zero, the algorithm fails badly
  if ((radX == 0) && (radY == 0)) {
    putPixel(centerX, centerY, pixel);
  } else {
    sqrX = 2 * radX * radX;
    sqrY = 2 * radY * radY;
    
    x = radX;
    y = 0;
    chgX = radY * radY * (1 - 2 * radX);
    chgY = radX * radX;
    err = 0;
    stopX = sqrY * radX;
    stopY = 0;

    while (stopX >= stopY) {
      drawCircLine(centerX, centerY, x, x, y, pixel, part);
      lastX = x; lastY = y;
      ++y;
      stopY += sqrX;
      err += chgY;
      chgY += sqrX;
      if (2 * err + chgX > 0) {
        --x;
        stopX -= sqrY;
        err += chgX;
        chgX += sqrY;
      }
    }

    x = 0;
    oldX = 0;
    y = radY;
    chgX = radY * radY;
    chgY = radX * radX * (1 - 2 * radY);;
    err = 0;
    stopX = 0;
    stopY = sqrX * radY;

    while (stopX <= stopY) {
      ++x;
      stopX += sqrY;
      err += chgX;
      chgX += sqrY;
      if (2 * err + chgY > 0) {
        drawCircLine(centerX, centerY, x - 1, oldX, y, pixel, part);
        oldX = x;
        --y;
        stopY -= sqrX;
        err += chgY;
        chgY += sqrX;
      }
    }
    
    // Lücken an den Stößen zwischen oberer und unterer Schleife füllen,
    // vor allem bei extrem flachen Ellipsen
    for ( ; y > lastY; --y) {
      drawCircLine(centerX, centerY, x - 1, oldX, y, pixel, part);
    }
    if ((lastX > x) && !(part & SDL_CIRC_FILLED)) {
      drawCircLine(centerX, centerY, lastX - 1, x, lastY, pixel, part);
    }
  }
  
  // ev. modifizierten Bereich vergrößern
  
  if (leftX < minX) minX = leftX;
  if (upperY < minY) minY = upperY;
  if (rightX > maxX) maxX = rightX;
  if (lowerY > maxY) maxY = lowerY;
}

static void sdlQuitOnEvent(void)
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      exit(EXIT_FAILURE);
    }
  }
}

void sdlUpdate(void)
{
  sdlQuitOnEvent();
  // Wenn seit letztem Mal nichts geändert wurde: Kein Update  
  if (maxX > MINVAL) {
    // Begrenzung für neu zu zeichnende Fläche
    SDL_Rect updRect;
    updRect.x = minX;
    updRect.y = minY;
    updRect.w = (maxX - minX) + 1;
    updRect.h = (maxY - minY) + 1;

    if ((updRect.w == SDL_X_SIZE) && (updRect.h == SDL_Y_SIZE)) {
      // Full screen update
      if (SDL_UpdateTexture(myTexture, NULL, myPixArray,
                            sizeof(Uint32) * SDL_X_SIZE) != 0) { 
        fprintf(stderr, "Could not update SDL texture: %s.\n", SDL_GetError());
        exit(EXIT_FAILURE);
      }
      if (SDL_RenderCopy(myRenderer, myTexture, NULL, NULL) != 0) { 
        fprintf(stderr, "Could not display SDL texture: %s.\n", SDL_GetError());
        exit(EXIT_FAILURE);
      }      
    } else {
      if (SDL_UpdateTexture(myTexture, &updRect,
                            myPixArray + minY * SDL_X_SIZE + minX,
                            sizeof(Uint32) * SDL_X_SIZE) != 0) { 
        fprintf(stderr, "Could not update SDL texture: %s.\n", SDL_GetError());
        exit(EXIT_FAILURE);
      }
      if (SDL_RenderCopy(myRenderer, myTexture, &updRect, &updRect) != 0) { 
        fprintf(stderr, "Could not display SDL texture: %s.\n", SDL_GetError());
        exit(EXIT_FAILURE);
      }
    }
    SDL_RenderPresent(myRenderer);

    minX = MAXVAL;
    maxX = MINVAL;
    minY = MAXVAL;
    maxY = MINVAL;
  }
}

void sdlMilliSleep(int ms)
{
  sdlQuitOnEvent();
  SDL_Delay(ms);
}
