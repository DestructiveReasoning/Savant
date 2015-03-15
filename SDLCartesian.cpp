#include "./SDLCartesian.h"

SDL_Cartesian::SDL_Cartesian(int _width, int _height, std::string _infix) :
	width(_width),
	height(_height),
	infix(_infix),
	running(true)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(("f(x) = " + infix).c_str(), SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,width,height);
	pixels = new Uint32[width * height];
	rpn = Math::infixToRPN(infix);
	SDL_SetRenderDrawColor(renderer,0xff,0xff,0,0xff);
}

void SDL_Cartesian::update()
{
	xScale = width/10;
	yScale = xScale;
	for(int c = 0; c < width * height; c++) pixels[c] = 0xff000000; //Clear Screen
	for(int c = 0; c < width; c++)
	{
		pixels[c+(height/2)*width] = 0xff444444;	//Draw X axis
	}
	for(int c = 0; c < height; c++)
	{
		pixels[width/2 + c*width] = 0xff444444;		//Draw Y axis
	}
	SDL_UpdateTexture(texture,NULL,pixels,width * sizeof(Uint32));
}

void SDL_Cartesian::render()
{
	
	double x;
	double y;
	last = {0,-Math::evaluateRPN(rpn,(-width/2),false) + height/2};
	for(int i = 1; i < width; i++)
	{
		//y = Math::evaluateRPN(rpn,(i - width)*xScale/width,false);
		y = -Math::evaluateRPN(rpn,(i-width/2),false);
		int coordinate = (int)(i + (y + height/2)*width);
		next = {(double)i,-Math::evaluateRPN(rpn,(i - width/2), false) + height/2};
		SDL_RenderDrawLine(renderer,last.x,last.y,next.x,next.y);
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
