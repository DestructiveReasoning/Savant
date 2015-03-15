#include "./SDLCartesian.h"

SDL_Cartesian::SDL_Cartesian(int _width, int _height, std::string _infix) :
	width(_width),
	height(_height),
	infix(_infix),
	xOffset(0),
	yOffset(0),
	running(true)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(("f(x) = " + infix).c_str(), SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,width,height);
	pixels = new Uint32[width * height];
	rpn = Math::infixToRPN(infix);
	SDL_SetRenderDrawColor(renderer,0xff,0xff,0,0xff);
	xScale = width/10.0f;
	yScale = xScale;
}

void SDL_Cartesian::update()
{
	keys = SDL_GetKeyboardState(NULL);
	if(keys[SDL_SCANCODE_MINUS])	
	{
		yScale = xScale -= 0.2;
		if(xScale < 4) xScale = yScale = 4;
	}
	if(keys[SDL_SCANCODE_EQUALS])	
	{
		yScale = xScale += 0.2;
		if(xScale > width/2) xScale = yScale = width/2;
	}
	if(keys[SDL_SCANCODE_LEFT])
	{
		xOffset -= 1;
	}
	if(keys[SDL_SCANCODE_RIGHT])
	{
		xOffset += 1;
	}
	if(keys[SDL_SCANCODE_UP])
	{
		yOffset -= 1;
	}
	if(keys[SDL_SCANCODE_DOWN])
	{
		yOffset += 1;
	}
	if(keys[SDL_SCANCODE_HOME])
	{
		xOffset = yOffset = 0;
		xScale = yScale = width/10.0f;
	}
	if(keys[SDL_SCANCODE_ESCAPE])
	{
		running = false;
	}

	for(int c = 0; c < width * height; c++) pixels[c] = 0xff000000; //Clear Screen
	for(int c = 0; c < width; c++)
	{
		int coordinate = (int)(c + (-yOffset + height/2) * width);
		if(coordinate >= 0 && coordinate < width * height && Math::absolute(yOffset) < height/2)
			pixels[coordinate] = 0xff444444;	//Draw X axis
	}
	for(int c = 0; c < height; c++)
	{
		int coordinate = (int)(width/2 - xOffset + (c)*width);
		if(coordinate >= 0 && coordinate < width * height && Math::absolute(xOffset) < width/2)
			pixels[coordinate] = 0xff444444;		//Draw Y axis
	}
	SDL_UpdateTexture(texture,NULL,pixels,width * sizeof(Uint32));
}

void SDL_Cartesian::render()
{
	
	double x;
	double y;
	last = {(double)xOffset,-Math::evaluateRPN(rpn,(-width/2) / xScale,false)*yScale + (double)height/2 - (double)yOffset};
	for(int i = 0 + xOffset; i < width + xOffset; i++)
	{
		//y = Math::evaluateRPN(rpn,(i - width)*xScale/width,false);
		y = -Math::evaluateRPN(rpn,(i-width/2),false);
		int coordinate = (int)(i + (y + height/2)*width);
		next = {(double)(i - xOffset),-Math::evaluateRPN(rpn,(i - width/2)/xScale, false) * yScale + (double)(height/2 - yOffset)};
		if(i != xOffset)SDL_RenderDrawLine(renderer,last.x,last.y,next.x,next.y);
		last = next;
		//if(coordinate >= 0 && coordinate < width * height) pixels[coordinate] = 0xffffff00;
	}
}

void SDL_Cartesian::run()
{
	while(running)
	{
		SDL_PollEvent(&mainEvent);
		if(mainEvent.type == SDL_QUIT) running = false;
		SDL_RenderClear(renderer);
		update();
		SDL_RenderCopy(renderer,texture,NULL,NULL);
		render();
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}
}

SDL_Cartesian::~SDL_Cartesian()
{
	rpn = std::string();
	delete[] pixels;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
