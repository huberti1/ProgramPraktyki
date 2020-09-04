#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <filesystem>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_net.h>
//#include <SDL_gpu.h>
//#include <SFML/Network.hpp>
//#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <functional>
#ifdef __ANDROID__
#include <android/log.h> //__android_log_print(ANDROID_LOG_VERBOSE, "ProgramPraktyki", "Example number log: %d", number);
#include <jni.h>
#endif
#include <SDL2_gfxPrimitives.h>


// NOTE: Remember to uncomment it on every release
//#define RELEASE

#if defined _MSC_VER && defined RELEASE
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

//240 x 240 (smart watch)
//240 x 320 (QVGA)
//360 x 640 (Galaxy S5)
//640 x 480 (480i - Smallest PC monitor)

int windowWidth = 240;
int windowHeight = 320;
SDL_Point mousePos;
SDL_Point realMousePos;
bool keys[SDL_NUM_SCANCODES];
bool buttons[SDL_BUTTON_X2 + 1];

#define PLAYER_ROTATION_SPEED 0.1
#define PI 3.14159265358979323846


void logOutputCallback(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	std::cout << message << std::endl;
}

int random(int min, int max)
{
	return min + rand() % ((max + 1) - min);
}

int SDL_QueryTextureF(SDL_Texture* texture, Uint32* format, int* access, float* w, float* h)
{
	int wi, hi;
	int result = SDL_QueryTexture(texture, format, access, &wi, &hi);
	*w = wi;
	*h = hi;
	return result;
}

SDL_Texture* renderText(SDL_Texture* previousTexture, TTF_Font* font, SDL_Renderer* renderer, const std::string& text, SDL_Color color)
{
	if (previousTexture) {
		SDL_DestroyTexture(previousTexture);
	}
	SDL_Surface* surface;
	if (text.empty()) {
		surface = TTF_RenderUTF8_Blended(font, " ", color);
	}
	else {
		surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
	}
	if (surface) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		return texture;
	}
	else {
		return 0;
	}
}

struct Text {
	std::string text;
	SDL_Texture* t = 0;
	SDL_FRect dstR{};

	void setText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color c = { 255,255,255 })
	{
		this->text = text;
		t = renderText(t, font, renderer, text, c);
	}

	void setText(SDL_Renderer* renderer, TTF_Font* font, int value, SDL_Color c = { 255,255,255 })
	{
		setText(renderer, font, std::to_string(value), c);
	}

	void draw(SDL_Renderer* renderer)
	{
		SDL_RenderCopyF(renderer, t, 0, &dstR);
	}
};

int eventWatch(void* userdata, SDL_Event* event)
{
	// WARNING: Be very careful of what you do in the function, as it may run in a different thread
	if (event->type == SDL_APP_TERMINATING || event->type == SDL_APP_WILLENTERBACKGROUND) {

	}
	return 0;
}


int
SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
	int offsetx, offsety, d;
	int status;


	offsetx = 0;
	offsety = radius;
	d = radius - 1;
	status = 0;

	while (offsety >= offsetx) {
		status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
		status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
		status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
		status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
		status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
		status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
		status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
		status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}


int
SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
	int offsetx, offsety, d;
	int status;


	offsetx = 0;
	offsety = radius;
	d = radius - 1;
	status = 0;

	while (offsety >= offsetx) {

		status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
			x + offsety, y + offsetx);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
			x + offsetx, y + offsety);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
			x + offsetx, y - offsety);
		status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
			x + offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}

float speedX = 5;
float speedY = 3;
int x = 50;
int y = 50;

int radius = 10;


Uint32 my_callbackfunc(Uint32 interval, void* param)
{
#if 0
	SDL_Event event;
	SDL_UserEvent userevent;

	/* In this example, our callback pushes an SDL_USEREVENT event
	into the queue, and causes our callback to be called again at the
	same interval: */

	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = NULL;
	userevent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
#endif
	//	std::cout << "Hello World!" << std::endl;
	x += speedX;
	y += speedY;
	if (x + radius / 2 > windowWidth || x - radius / 2 < 0) {
		speedX = -speedX;
	}
	if (y + radius / 2 > windowHeight || y - radius / 2 < 0) {
		speedY = -speedY;
	}
	return(interval);
}

float getAngle(int x1, int y1, int x2, int y2)
{
	float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
	return angle >= 0 ? angle : 360 + angle;
}

void calcSlope(int x1, int y1, int x2, int y2, float* dx, float* dy)
{
	int steps = std::max(abs(x1 - x2), abs(y1 - y2));
	if (steps == 0) {
		*dx = *dy = 0;
		return;
	}
	*dx = (x1 - x2);
	*dx /= steps;
	*dy = (y1 - y2);
	*dy /= steps;
}

std::string readWholeFile(std::string path)
{
	std::ifstream ifs(path);
	// TODO: Error handling?
	std::stringstream ss(path);
	ss << ifs.rdbuf();
	return ss.str();
}

struct Line {
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	SDL_Color color{};
};

struct Circle {
	int x = 0, y = 0, r = 0;
	SDL_Color color{};
};

struct Objects {
	std::vector <Line> lines;
	std::vector <Circle> circles;
	std::vector <Circle> filledCircles;

	void draw(SDL_Renderer* renderer)
	{
		for (Line& line : lines) {
			SDL_SetRenderDrawColor(renderer, line.color.r, line.color.g, line.color.b, line.color.a);
			SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
		}
		for (Circle& circle : circles) {
			SDL_SetRenderDrawColor(renderer, circle.color.r, circle.color.g, circle.color.b, circle.color.a);
			SDL_RenderDrawCircle(renderer, circle.x, circle.y, circle.r);
		}
		for (Circle& filledCircle : filledCircles) {
			SDL_SetRenderDrawColor(renderer, filledCircle.color.r, filledCircle.color.g, filledCircle.color.b, filledCircle.color.a);
			SDL_RenderFillCircle(renderer, filledCircle.x, filledCircle.y, filledCircle.r);
		}
	}
};

Objects readObjects(std::string file)
{
	Objects objects;
	std::stringstream iss(file);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(iss, line)) {
		lines.push_back(line);
	}
	std::vector<std::string> attributes;
	{
		for (std::string& line : lines) {
			std::stringstream ss(line);
			std::string s;
			while (std::getline(ss, s, ' ')) {
				attributes.push_back(s);
			}
		}
	}
	SDL_Color currentC = { 255,255,255,255 };
#if 0
	for (std::string& attribute : attributes) {
		for (char& ch : attribute) {
			if (ch == '\n') {
				ch = ' ';
			}
		}
	}
#endif
	for (int i = 0; i < attributes.size(); ++i) {
		if (attributes[i] == "L") {
			objects.lines.push_back(Line());
			objects.lines.back().x1 = std::stoi(attributes[++i]);
			objects.lines.back().y1 = std::stoi(attributes[++i]);
			objects.lines.back().x2 = std::stoi(attributes[++i]);
			objects.lines.back().y2 = std::stoi(attributes[++i]);
			objects.lines.back().color = currentC;
		}
		else if (attributes[i] == "C") {
			objects.circles.push_back(Circle());
			objects.circles.back().x = std::stoi(attributes[++i]);
			objects.circles.back().y = std::stoi(attributes[++i]);
			objects.circles.back().r = std::stoi(attributes[++i]);
			objects.circles.back().color = currentC;
		}
		else if (attributes[i] == "K") {
			objects.filledCircles.push_back(Circle());
			objects.filledCircles.back().x = std::stoi(attributes[++i]);
			objects.filledCircles.back().y = std::stoi(attributes[++i]);
			objects.filledCircles.back().r = std::stoi(attributes[++i]);
			objects.filledCircles.back().color = currentC;
		}
		else if (attributes[i] == "P") {
			std::string color = attributes[++i];
			color = color.erase(0, 1);
			int r, g, b;
			std::sscanf(color.c_str(), "%02x%02x%02x", &r, &g, &b);
			currentC.r = r;
			currentC.g = g;
			currentC.b = b;
		}
	}
	return objects;
}

int main(int argc, char* argv[])
{
	std::srand(std::time(0));
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogSetOutputFunction(logOutputCallback, 0);
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	// TODO: SDL2 not multiple monitor support ???
#if 1 // TODO: Remember to turn it off on reelase
	SDL_Window * window = SDL_CreateWindow("ProgramPraktyki", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
#else
	SDL_Window* window = SDL_CreateWindow("ProgramPraktyki", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	windowWidth = dm.w;
	windowHeight = dm.h;
#endif
	//SDL_MaximizeWindow(window);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Font* robotoF = TTF_OpenFont("res/roboto.ttf", 72);
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_RenderSetScale(renderer, w / (float)windowWidth, h / (float)windowHeight);
	SDL_AddEventWatch(eventWatch, 0);
	bool running = true;
	SDL_AddTimer(20, my_callbackfunc, 0);

	double angle = 0;
	SDL_Rect r;
	r.w = 32;
	r.h = 32;
	r.x = 0;
	r.y = 0;

	SDL_Texture* playerT = IMG_LoadTexture(renderer, "res/player.bmp");

	/*
	l-line
	c-circle
	k-filled circle
	p-change color
	*/
	std::string movingFile = readWholeFile("res/ruchome.txt");
	Objects objects = readObjects(movingFile);

	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				running = false;
				// TODO: On mobile remember to use eventWatch function (it doesn't reach this code when terminating)
			}
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
				//SDL_RenderSetScale(renderer, event.window.data1 / (float)windowWidth, event.window.data2 / (float)windowHeight);
			}
			if (event.type == SDL_KEYDOWN) {
				keys[event.key.keysym.scancode] = true;
			}
			if (event.type == SDL_KEYUP) {
				keys[event.key.keysym.scancode] = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				buttons[event.button.button] = true;
			}
			if (event.type == SDL_MOUSEBUTTONUP) {
				buttons[event.button.button] = false;
			}
			if (event.type == SDL_MOUSEMOTION) {
				float scaleX, scaleY;
				SDL_RenderGetScale(renderer, &scaleX, &scaleY);
				mousePos.x = event.motion.x / scaleX;
				mousePos.y = event.motion.y / scaleY;
				realMousePos.x = event.motion.x;
				realMousePos.y = event.motion.y;
			}
		}
		if (keys[SDL_SCANCODE_A]) {
			angle -= PLAYER_ROTATION_SPEED;
		}
		if (keys[SDL_SCANCODE_D]) {
			angle += PLAYER_ROTATION_SPEED;
		}
		if (keys[SDL_SCANCODE_W]) {
			angle += PLAYER_ROTATION_SPEED;
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_RenderCopyEx(renderer, playerT, 0, &r, getAngle(r.x + r.w / 2, r.y + r.h / 2, mousePos.x, mousePos.y), 0, SDL_FLIP_NONE);
		objects.draw(renderer);
		SDL_RenderPresent(renderer);
	}
	// TODO: On mobile remember to use eventWatch function (it doesn't reach this code when terminating)
	return 0;
}