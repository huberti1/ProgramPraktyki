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
#define PLAYER_SPEED 0.1
#define PLAYER_SPEED_INCREASE 0.001
#define PLAYER_SPEED_LIMIT 1
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

	void adjustSize(float wMultiplier, float hMultiplier)
	{
		float w, h;
		SDL_QueryTextureF(t, 0, 0, &w, &h);
		dstR.w = w * wMultiplier;
		dstR.h = h * hMultiplier;
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
	int dx = 1;
	int dy = -1;
	int energy = 3;
};

struct Circle {
	int x = 0, y = 0, r = 0;
	SDL_Color color{};
	int dx = 1;
	int dy = -1;
	int speed = random(1, 10);
	int energy = 3;

	void move()
	{
		x += dx * speed;
		y += dy * speed;
		if (x - r < 0) {
			dx = -dx;
			x = r;
		}
		if (x + r > windowWidth) {
			dx = -dx;
			x = windowWidth - r;
		}
		if (y - r < 0) {
			dy = -dy;
			y = r;
		}
		if (y + r > windowHeight) {
			dy = -dy;
			y = windowHeight - r;
		}
	}
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

enum class State {
	Game,
	Menu,
};

struct Button {
	SDL_Rect r{};
	SDL_Color color{};
	Text text;

	void draw(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &r);
		text.draw(renderer);
	}
};

struct Entity {
	SDL_FRect r{};
	SDL_Texture* t = 0;
	float angle = 0;
	float speed = 0.1;
	int energy = 100;

	void draw(SDL_Renderer* renderer)
	{
		SDL_RenderCopyExF(renderer, t, 0, &r, angle, 0, SDL_FLIP_NONE);
	}
};

// NOTE: Source: https://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d
SDL_FPoint rotatePoint(float cx, float cy, float angle, SDL_FPoint p)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	p.x -= cx;
	p.y -= cy;

	// rotate point
	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;

	// translate point back:
	p.x = xnew + cx;
	p.y = ynew + cy;
	return p;
}

SDL_FORCE_INLINE SDL_bool SDL_RectEmpty(const SDL_FRect* r)
{
	return ((!r) || (r->w <= 0) || (r->h <= 0)) ? SDL_TRUE : SDL_FALSE;
}

SDL_bool SDL_HasIntersection(const SDL_FRect* A, const SDL_FRect* B)
{
	int Amin, Amax, Bmin, Bmax;

	if (!A) {
		SDL_InvalidParamError("A");
		return SDL_FALSE;
	}

	if (!B) {
		SDL_InvalidParamError("B");
		return SDL_FALSE;
	}

	/* Special cases for empty rects */
	if (SDL_RectEmpty(A) || SDL_RectEmpty(B)) {
		return SDL_FALSE;
	}

	/* Horizontal intersection */
	Amin = A->x;
	Amax = Amin + A->w;
	Bmin = B->x;
	Bmax = Bmin + B->w;
	if (Bmin > Amin)
		Amin = Bmin;
	if (Bmax < Amax)
		Amax = Bmax;
	if (Amax <= Amin)
		return SDL_FALSE;

	/* Vertical intersection */
	Amin = A->y;
	Amax = Amin + A->h;
	Bmin = B->y;
	Bmax = Bmin + B->h;
	if (Bmin > Amin)
		Amin = Bmin;
	if (Bmax < Amax)
		Amax = Bmax;
	if (Amax <= Amin)
		return SDL_FALSE;

	return SDL_TRUE;
}

SDL_bool SDL_IntersectRectAndLine(const SDL_FRect* rect, int* X1, int* Y1, int* X2, int* Y2)
{
	int x = 0;
	int y = 0;
	int x1, y1;
	int x2, y2;
	int rectx1;
	int recty1;
	int rectx2;
	int recty2;
	int outcode1, outcode2;

	if (!rect) {
		SDL_InvalidParamError("rect");
		return SDL_FALSE;
	}

	if (!X1) {
		SDL_InvalidParamError("X1");
		return SDL_FALSE;
	}

	if (!Y1) {
		SDL_InvalidParamError("Y1");
		return SDL_FALSE;
	}

	if (!X2) {
		SDL_InvalidParamError("X2");
		return SDL_FALSE;
	}

	if (!Y2) {
		SDL_InvalidParamError("Y2");
		return SDL_FALSE;
	}

	/* Special case for empty rect */
	if (SDL_RectEmpty(rect)) {
		return SDL_FALSE;
	}

	x1 = *X1;
	y1 = *Y1;
	x2 = *X2;
	y2 = *Y2;
	rectx1 = rect->x;
	recty1 = rect->y;
	rectx2 = rect->x + rect->w - 1;
	recty2 = rect->y + rect->h - 1;

	/* Check to see if entire line is inside rect */
	if (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
		y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
		return SDL_TRUE;
	}

	/* Check to see if entire line is to one side of rect */
	if ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
		(y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
		return SDL_FALSE;
	}

	if (y1 == y2) {
		/* Horizontal line, easy to clip */
		if (x1 < rectx1) {
			*X1 = rectx1;
		}
		else if (x1 > rectx2) {
			*X1 = rectx2;
		}
		if (x2 < rectx1) {
			*X2 = rectx1;
		}
		else if (x2 > rectx2) {
			*X2 = rectx2;
		}
		return SDL_TRUE;
	}

	if (x1 == x2) {
		/* Vertical line, easy to clip */
		if (y1 < recty1) {
			*Y1 = recty1;
		}
		else if (y1 > recty2) {
			*Y1 = recty2;
		}
		if (y2 < recty1) {
			*Y2 = recty1;
		}
		else if (y2 > recty2) {
			*Y2 = recty2;
		}
		return SDL_TRUE;
	}
}

SDL_FRect lineToFRect(Line line)
{
	SDL_FRect lineR;
	float angle = std::atan2(line.y2 - line.y1, line.x2 - line.x1) * 180 / M_PI;
	lineR.w = std::fabs(line.x1 - line.x2);
	lineR.h = std::fabs(line.y1 - line.y2);
	lineR.x = line.x1; // TODO: Is it ok?
	lineR.y = line.y1; // TODO: Is it ok?
	SDL_FPoint rotatedP = rotatePoint(lineR.x + lineR.w / 2, lineR.y + lineR.h / 2, angle, { lineR.x, lineR.y });
	lineR.x = rotatedP.x;
	lineR.y = rotatedP.y;
	return lineR;
}

SDL_FRect circleToRect(Circle circle)
{
	SDL_FRect circleR;
	circleR.w = circle.r * 2;
	circleR.h = circle.r * 2;
	circleR.x = circle.x - circle.r;
	circleR.y = circle.y - circle.r;
	return circleR;
}

int main(int argc, char* argv[])
{
	
	std::srand(std::time(0));
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogSetOutputFunction(logOutputCallback, 0);
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_GetMouseState(&mousePos.x, &mousePos.y);

#if 1 // TODO: Remember to turn it off on reelase
	SDL_Window * window = SDL_CreateWindow("ProgramPraktyki", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
#else
	SDL_Window* window = SDL_CreateWindow("ProgramPraktyki", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	windowWidth = dm.w;
	windowHeight = dm.h;
#endif

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Font* robotoF = TTF_OpenFont("res/roboto.ttf", 72);
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_RenderSetScale(renderer, w / (float)windowWidth, h / (float)windowHeight);
	SDL_AddEventWatch(eventWatch, 0);
	bool running = true;
	SDL_AddTimer(20, my_callbackfunc, 0);

gameBegin:
	SDL_Texture* bulletT = IMG_LoadTexture(renderer, "res/bullet.png");
	Entity firstPlayer;
	firstPlayer.r.w = 32;
	firstPlayer.r.h = 32;
	firstPlayer.r.x = 0;
	firstPlayer.r.y = 0;
	firstPlayer.t = IMG_LoadTexture(renderer, "res/player1.png");
	firstPlayer.speed = PLAYER_SPEED;
	bool firstPlayerSlowDownOnAccelerationKeyRelease = false;
	Entity secondPlayer;
	secondPlayer.r.w = 32;
	secondPlayer.r.h = 32;
	secondPlayer.r.x = windowWidth - secondPlayer.r.w;
	secondPlayer.r.y = 0;
	secondPlayer.t = IMG_LoadTexture(renderer, "res/player2.png");
	secondPlayer.speed = PLAYER_SPEED;
	bool secondPlayerSlowDownOnAccelerationKeyRelease = false;
	std::vector<Entity> bullets;

	Text pointsTxt;
	pointsTxt.setText(renderer, robotoF, "0");
	pointsTxt.adjustSize(0.3, 0.3);
	pointsTxt.dstR.x = windowWidth / 2 - pointsTxt.dstR.w / 2;
	pointsTxt.dstR.y = 5;

	/*
	l-line
	c-circle
	k-filled circle
	p-change color
	*/
	std::string movingFile = readWholeFile("res/ruchome.txt");
	Objects objects = readObjects(movingFile);
#if 1 // NOTE: If there is collision randomize position one more time
	{
		int i = 0;
		for (Line& line : objects.lines) {
			int length = std::abs(line.x2 - line.x1);
			SDL_Point position = { random(0, windowWidth - length), random(0, windowHeight - length) };
			line.x1 = position.x;
			line.y1 = position.y;
			line.x2 = position.x;
			line.y2 = position.y;
		collisionCheckBegin:
			for (int j = 0; j < i; ++j) {
				SDL_FRect r = lineToFRect(objects.lines[i]);
				SDL_FRect r2 = lineToFRect(objects.lines[j]);
				if (SDL_HasIntersection(&r, &r2)) {
					line.x1 = position.x;
					line.y1 = position.y;
					line.x2 = position.x;
					line.y2 = position.y;
					goto collisionCheckBegin;
				}
			}
			for (int j = 0; j < objects.circles.size(); ++j) {
				SDL_FRect r = lineToFRect(objects.lines[i]);
				SDL_FRect r2 = circleToRect(objects.circles[j]);
				if (SDL_HasIntersection(&r, &r2)) {
					line.x1 = position.x;
					line.y1 = position.y;
					line.x2 = position.x;
					line.y2 = position.y;
					goto collisionCheckBegin;
				}
			}
			for (int j = 0; j < objects.filledCircles.size(); ++j) {
				SDL_FRect r = lineToFRect(objects.lines[i]);
				SDL_FRect r2 = circleToRect(objects.filledCircles[j]);
				if (SDL_HasIntersection(&r, &r2)) {
					line.x1 = position.x;
					line.y1 = position.y;
					line.x2 = position.x;
					line.y2 = position.y;
					goto collisionCheckBegin;
				}
			}
			++i;
		}
	}

	{
		int i = 0;
		for (Circle& circle : objects.circles) {
			SDL_Point position = { random(circle.r, windowWidth - circle.r), random(circle.r, windowHeight - circle.r) };
			circle.x = position.x;
			circle.y = position.y;
		collisionCheckBegin2:
			for (int j = 0; j < objects.lines.size(); ++j) {
				SDL_FRect r = circleToRect(objects.circles[i]);
				SDL_FRect r2 = lineToFRect(objects.lines[j]);

				if (SDL_HasIntersection(&r, &r2)) {
					circle.x = position.x;
					circle.y = position.y;
					goto collisionCheckBegin2;
				}
			}
			for (int j = 0; j < i; ++j) {
				SDL_FRect r = circleToRect(objects.circles[i]);
				SDL_FRect r2 = circleToRect(objects.circles[j]);
				if (SDL_HasIntersection(&r, &r2)) {
					circle.x = position.x;
					circle.y = position.y;
					goto collisionCheckBegin2;
				}
			}
			for (int j = 0; j < objects.filledCircles.size(); ++j) {
				SDL_FRect r = circleToRect(objects.circles[i]);
				SDL_FRect r2 = circleToRect(objects.filledCircles[j]);
				if (SDL_HasIntersection(&r, &r2)) {
					circle.x = position.x;
					circle.y = position.y;
					goto collisionCheckBegin2;
				}
			}
			++i;
		}
	}
	{
		int i = 0;
		for (Circle& filledCircle : objects.filledCircles) {
			SDL_Point position = { random(filledCircle.r, windowWidth - filledCircle.r), random(filledCircle.r, windowHeight - filledCircle.r) };
			filledCircle.x = position.x;
			filledCircle.y = position.y;
		collisionCheckBegin3:
			for (int j = 0; j < i; ++j) {
				SDL_FRect r = circleToRect(objects.filledCircles[i]);
				SDL_FRect r2 = lineToFRect(objects.lines[j]);
				if (SDL_HasIntersection(&r, &r2)) {
					filledCircle.x = position.x;
					filledCircle.y = position.y;
					goto collisionCheckBegin3;
				}
			}
			for (int j = 0; j < objects.circles.size(); ++j) {
				SDL_FRect r = circleToRect(objects.filledCircles[i]);
				SDL_FRect r2 = circleToRect(objects.circles[j]);
				if (SDL_HasIntersection(&r, &r2)) {
					filledCircle.x = position.x;
					filledCircle.y = position.y;
					goto collisionCheckBegin3;
				}
			}
			for (int j = 0; j < i; ++j) {
				SDL_FRect r = circleToRect(objects.filledCircles[i]);
				SDL_FRect r2 = circleToRect(objects.filledCircles[j]);
				if (SDL_HasIntersection(&r, &r2)) {
					filledCircle.x = position.x;
					filledCircle.y = position.y;
					goto collisionCheckBegin3;
				}
			}
			++i;
		}
	}
	
#endif
	// TODO: Does it make sense to randomize position of circles when they are in file already?
	for (Circle& circle : objects.circles) {
		SDL_Point position = { random(circle.r, windowWidth - circle.r), random(circle.r, windowHeight - circle.r) };
		circle.x = position.x;
		circle.y = position.y;
		// TOOO: They cannot collide with other objects

	}
	for (Circle& circle : objects.filledCircles) {
		SDL_Point position = { random(circle.r, windowWidth - circle.r), random(circle.r, windowHeight - circle.r) };
		circle.x = position.x;
		circle.y = position.y;
		// TOOO: They cannot collide with other objects
	}
#if 1 // INIT_MENU_STATE
	int buttonSplit = 5;
	Button onePlayerBtn;
	onePlayerBtn.r.w = 100;
	onePlayerBtn.r.h = 30;
	onePlayerBtn.r.x = windowWidth / 2 - onePlayerBtn.r.w - buttonSplit;
	onePlayerBtn.r.y = windowHeight / 2 - onePlayerBtn.r.h / 2;
	onePlayerBtn.text.setText(renderer, robotoF, "1");
	onePlayerBtn.text.adjustSize(0.3, 0.3);
	onePlayerBtn.text.dstR.x = onePlayerBtn.r.x + onePlayerBtn.r.w / 2 - onePlayerBtn.text.dstR.w / 2;
	onePlayerBtn.text.dstR.y = onePlayerBtn.r.y + onePlayerBtn.r.h / 2 - onePlayerBtn.text.dstR.h / 2;
	onePlayerBtn.color = { 0, 150, 150 };
	Button twoPlayersBtn;
	twoPlayersBtn.r.w = 100;
	twoPlayersBtn.r.h = 30;
	twoPlayersBtn.r.x = windowWidth / 2 + buttonSplit;
	twoPlayersBtn.r.y = windowHeight / 2 - twoPlayersBtn.r.h / 2;
	twoPlayersBtn.text.setText(renderer, robotoF, "2");
	twoPlayersBtn.text.adjustSize(0.3, 0.3);
	twoPlayersBtn.text.dstR.x = twoPlayersBtn.r.x + twoPlayersBtn.r.w / 2 - twoPlayersBtn.text.dstR.w / 2;
	twoPlayersBtn.text.dstR.y = twoPlayersBtn.r.y + twoPlayersBtn.r.h / 2 - twoPlayersBtn.text.dstR.h / 2;
	twoPlayersBtn.color = { 0, 150, 150 };
	Text playerCountTxt;
	playerCountTxt.setText(renderer, robotoF, "Amount of players:");
	playerCountTxt.adjustSize(0.2, 0.32);
	playerCountTxt.dstR.x = windowWidth / 2 - playerCountTxt.dstR.w / 2;
	playerCountTxt.dstR.y = onePlayerBtn.r.y - playerCountTxt.dstR.h - 5;
	int playerCount = 1;
#endif

	State state = State::Menu;

	while (running) {
		if (state == State::Game) {
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
					if (event.key.keysym.scancode == SDL_SCANCODE_W) {
						firstPlayerSlowDownOnAccelerationKeyRelease = true;
					}
					if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
						secondPlayerSlowDownOnAccelerationKeyRelease = true;
					}
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
				if (firstPlayer.angle < 0) {
					firstPlayer.angle = 360.0;
				}
				else {
					firstPlayer.angle -= PLAYER_ROTATION_SPEED;
				}
			}
			if (keys[SDL_SCANCODE_D]) {
				if (firstPlayer.angle > 360) {
					firstPlayer.angle = 0.0;
				}
				else {
					firstPlayer.angle += PLAYER_ROTATION_SPEED;
				}
			}
			if (keys[SDL_SCANCODE_W]) {
				firstPlayer.r.x -= std::sin(firstPlayer.angle * (M_PI / 180)) * firstPlayer.speed;
				firstPlayer.r.y += std::cos(firstPlayer.angle * (M_PI / 180)) * firstPlayer.speed;
				firstPlayer.speed += PLAYER_SPEED_INCREASE;
				if (firstPlayer.speed > PLAYER_SPEED_LIMIT) {
					firstPlayer.speed = PLAYER_SPEED_LIMIT;
				}
#if 1 // NOTE: Reflection from borders
				if (firstPlayer.r.x < 0 || firstPlayer.r.x + firstPlayer.r.w > windowWidth) {
					SDL_FPoint leftUpRotatedP = rotatePoint((float)firstPlayer.r.x + firstPlayer.r.w / 2, (float)firstPlayer.r.y + firstPlayer.r.y / 2, firstPlayer.angle, { firstPlayer.r.x, firstPlayer.r.y });
					SDL_FPoint rightUpRotatedP = rotatePoint((float)firstPlayer.r.x + firstPlayer.r.w / 2, (float)firstPlayer.r.y + firstPlayer.r.y / 2, firstPlayer.angle, { firstPlayer.r.x + firstPlayer.r.w, firstPlayer.r.y });
					SDL_FPoint rightDownRotatedP = rotatePoint((float)firstPlayer.r.x + firstPlayer.r.w / 2, (float)firstPlayer.r.y + firstPlayer.r.y / 2, firstPlayer.angle, { firstPlayer.r.x + firstPlayer.r.w, firstPlayer.r.y + firstPlayer.r.h });
					SDL_FPoint leftDownRotatedP = rotatePoint((float)firstPlayer.r.x + firstPlayer.r.w / 2, (float)firstPlayer.r.y + firstPlayer.r.y / 2, firstPlayer.angle, { firstPlayer.r.x, firstPlayer.r.y + firstPlayer.r.h });
					firstPlayer.speed = -firstPlayer.speed;
					float highestX = std::max(leftUpRotatedP.x, rightUpRotatedP.x);
					{
						highestX = std::max(highestX, rightDownRotatedP.x);
						highestX = std::max(highestX, leftDownRotatedP.x);
						if (highestX > windowWidth) {
							firstPlayer.speed = -firstPlayer.speed;
							firstPlayer.r.x = windowWidth - firstPlayer.r.w * 2;
						}
					}
					float highestY = std::max(leftUpRotatedP.y, rightUpRotatedP.y);
					{
						highestY = std::max(highestY, leftDownRotatedP.y);
						highestY = std::max(highestY, rightDownRotatedP.y);
						if (highestY > windowHeight) {
							firstPlayer.speed = -firstPlayer.speed;
							firstPlayer.r.y = windowHeight - firstPlayer.r.h * 2;
						}
					}
					float lowestX = std::min(leftUpRotatedP.x, rightUpRotatedP.x);
					{
						lowestX = std::min(lowestX, rightDownRotatedP.x);
						lowestX = std::min(lowestX, leftDownRotatedP.x);
						if (lowestX < 0) {
							firstPlayer.speed = -firstPlayer.speed;
							firstPlayer.r.x = firstPlayer.r.w * 2;
						}
					}
					float lowestY = std::min(leftUpRotatedP.y, rightUpRotatedP.y);
					{
						lowestY = std::min(lowestY, rightDownRotatedP.y);
						lowestY = std::min(lowestY, leftDownRotatedP.y);
						if (lowestY < 0) {
							firstPlayer.speed = -firstPlayer.speed;
							firstPlayer.r.y = firstPlayer.r.h * 2;
						}
					}
				}
#endif
			}
			if (firstPlayerSlowDownOnAccelerationKeyRelease) {
				firstPlayer.r.x -= std::sin(firstPlayer.angle * (M_PI / 180)) * firstPlayer.speed;
				firstPlayer.r.y += std::cos(firstPlayer.angle * (M_PI / 180)) * firstPlayer.speed;
				firstPlayer.speed -= PLAYER_SPEED_INCREASE; // TODO: Air resistance?
				if (firstPlayer.speed <= PLAYER_SPEED) {
					firstPlayer.speed = PLAYER_SPEED;
					firstPlayerSlowDownOnAccelerationKeyRelease = false;
				}
			}
			if (keys[SDL_SCANCODE_SPACE]) {
				bullets.push_back(Entity());
				bullets.back() = firstPlayer;
				bullets.back().t = bulletT;
			}
#if 1 // NOTE: Player 2 code: should be same as player 1 but with other movement
			if (keys[SDL_SCANCODE_LEFT]) {
				if (firstPlayer.angle < 0) {
					firstPlayer.angle = 360.0;
				}
				else {
					firstPlayer.angle -= PLAYER_ROTATION_SPEED;
				}
			}
			if (keys[SDL_SCANCODE_RIGHT]) {
				if (firstPlayer.angle > 360) {
					firstPlayer.angle = 0.0;
				}
				else {
					firstPlayer.angle += PLAYER_ROTATION_SPEED;
				}
			}
			if (keys[SDL_SCANCODE_UP]) {
				firstPlayer.r.x -= std::sin(firstPlayer.angle * (M_PI / 180)) * firstPlayer.speed;
				firstPlayer.r.y += std::cos(firstPlayer.angle * (M_PI / 180)) * firstPlayer.speed;
				firstPlayer.speed += PLAYER_SPEED_INCREASE;
				if (firstPlayer.speed > PLAYER_SPEED_LIMIT) {
					firstPlayer.speed = PLAYER_SPEED_LIMIT;
				}
#if 1 // NOTE: Reflection from borders
				if (secondPlayer.r.x < 0 || secondPlayer.r.x + secondPlayer.r.w > windowWidth	) {
					SDL_FPoint leftUpRotatedP = rotatePoint((float)secondPlayer.r.x + secondPlayer.r.w / 2, (float)secondPlayer.r.y + secondPlayer.r.y / 2, secondPlayer.angle, { secondPlayer.r.x, secondPlayer.r.y });
					SDL_FPoint rightUpRotatedP = rotatePoint((float)secondPlayer.r.x + secondPlayer.r.w / 2, (float)secondPlayer.r.y + secondPlayer.r.y / 2, secondPlayer.angle, { secondPlayer.r.x + secondPlayer.r.w, secondPlayer.r.y });
					SDL_FPoint rightDownRotatedP = rotatePoint((float)secondPlayer.r.x + secondPlayer.r.w / 2, (float)secondPlayer.r.y + secondPlayer.r.y / 2, secondPlayer.angle, { secondPlayer.r.x + secondPlayer.r.w, secondPlayer.r.y + secondPlayer.r.h });
					SDL_FPoint leftDownRotatedP = rotatePoint((float)secondPlayer.r.x + secondPlayer.r.w / 2, (float)secondPlayer.r.y + secondPlayer.r.y / 2, secondPlayer.angle, { secondPlayer.r.x, secondPlayer.r.y + secondPlayer.r.h });
					secondPlayer.speed = -secondPlayer.speed;
					float highestX = std::max(leftUpRotatedP.x, rightUpRotatedP.x);
					{
						highestX = std::max(highestX, rightDownRotatedP.x);
						highestX = std::max(highestX, leftDownRotatedP.x);
						if (highestX > windowWidth) {
							secondPlayer.speed = -secondPlayer.speed;
							secondPlayer.r.x = windowWidth - secondPlayer.r.w * 2;
						}
					}
					float highestY = std::max(leftUpRotatedP.y, rightUpRotatedP.y);
					{
						highestY = std::max(highestY, leftDownRotatedP.y);
						highestY = std::max(highestY, rightDownRotatedP.y);
						if (highestY > windowHeight) {
							secondPlayer.speed = -secondPlayer.speed;
							secondPlayer.r.y = windowHeight - secondPlayer.r.h * 2;
						}
					}
					float lowestX = std::min(leftUpRotatedP.x, rightUpRotatedP.x);
					{
						lowestX = std::min(lowestX, rightDownRotatedP.x);
						lowestX = std::min(lowestX, leftDownRotatedP.x);
						if (lowestX < 0) {
							secondPlayer.speed = -secondPlayer.speed;
							secondPlayer.r.x = secondPlayer.r.w * 2;
						}
					}
					float lowestY = std::min(leftUpRotatedP.y, rightUpRotatedP.y);
					{
						lowestY = std::min(lowestY, rightDownRotatedP.y);
						lowestY = std::min(lowestY, leftDownRotatedP.y);
						if (lowestY < 0) {
							secondPlayer.speed = -secondPlayer.speed;
							secondPlayer.r.y = secondPlayer.r.h * 2;
						}
					}
				}
#endif
			}
			if (secondPlayerSlowDownOnAccelerationKeyRelease) {
				secondPlayer.r.x -= std::sin(secondPlayer.angle * (M_PI / 180)) * secondPlayer.speed;
				secondPlayer.r.y += std::cos(secondPlayer.angle * (M_PI / 180)) * secondPlayer.speed;
				secondPlayer.speed -= PLAYER_SPEED_INCREASE; // TODO: Air resistance?
				if (secondPlayer.speed <= PLAYER_SPEED) {
					secondPlayer.speed = PLAYER_SPEED;
					secondPlayerSlowDownOnAccelerationKeyRelease = false;
				}
			}
			if (keys[SDL_SCANCODE_RETURN]) {
				bullets.push_back(Entity());
				bullets.back() = secondPlayer;
				bullets.back().t = bulletT;
			}
#endif
			for (Entity& b : bullets) {
				b.r.x -= std::sin(b.angle * (M_PI / 180)) * b.speed;
				b.r.y += std::cos(b.angle * (M_PI / 180)) * b.speed;
			}
			{
				int i = 0;
				for (Entity& b : bullets) {
					if (b.r.x + b.r.w < 0 || b.r.x > windowWidth || b.r.y + b.r.h < 0 || b.r.y > windowHeight) {
						bullets.erase(bullets.begin() + i--);
					}
					++i;
				}
			}
			for (Line& line : objects.lines) {
				line.x1 += line.dx;
				line.y1 += line.dy;
				line.x2 += line.dx;
				line.y2 += line.dy;
				int maxX = std::max(line.x1, line.x2);
				int maxY = std::max(line.y1, line.y2);
				int minX = std::min(line.x1, line.x2);
				int minY = std::min(line.y1, line.y2);
				if (maxX > windowWidth || minX < 0) {
					line.dx = -line.dx;
				}
				if (maxY > windowHeight || minY < 0) {
					line.dy = -line.dy;
				}
			}
			for (Circle& circle : objects.circles) {
				circle.move();

			}
			for (Circle& filledCircle : objects.filledCircles) {
				filledCircle.move();
			}
#if 1 // NOTE: Bullet - element collision
			{
				int i = 0;
				for (Circle& circle : objects.circles) {
					SDL_FRect circleR = circleToRect(circle);
					int j = 0;
					if (SDL_HasIntersection(&circleR, &firstPlayer.r)) {
						circle.dx = -circle.dx;
						circle.dy = -circle.dy;
												
					}
					for (Entity& b : bullets) {
							if (SDL_HasIntersection(&circleR, &b.r)) {
							bullets.erase(bullets.begin() + j--);
							if (--circle.energy <= 0) {
								objects.circles.erase(objects.circles.begin() + i--);
								int points = std::stoi(pointsTxt.text);
								++points;
								pointsTxt.setText(renderer, robotoF, std::to_string(points));
								break;
							}
						}
						++j;
					}
					++i;
				}
			}
			{
				int i = 0;
				for (Circle& filledCircle : objects.filledCircles) {
					SDL_FRect circleR;
					circleR.w = filledCircle.r * 2;
					circleR.h = filledCircle.r * 2;
					circleR.x = filledCircle.x - filledCircle.r;
					circleR.y = filledCircle.y - filledCircle.r;
					int j = 0;
					if (SDL_HasIntersection(&circleR, &firstPlayer.r))	{
						filledCircle.dx = -filledCircle.dx;
						filledCircle.dy = -filledCircle.dy;
					}
					for (Entity& b : bullets) {
						if (SDL_HasIntersection(&circleR, &b.r)) {
							bullets.erase(bullets.begin() + j--);
							if (--filledCircle.energy <= 0) {
								objects.filledCircles.erase(objects.filledCircles.begin() + i--);
								int points = std::stoi(pointsTxt.text);
								++points;
								pointsTxt.setText(renderer, robotoF, std::to_string(points));
								break;
							}
						}
						++j;
					}
					++i;
				}
			}
			{
				int i = 0;
				for (Line& line : objects.lines) {
					int j = 0;
					if (SDL_IntersectRectAndLine(&firstPlayer.r, &line.x1, &line.y1, &line.x2, &line.y2))	{
						line.dx = -line.dx;
						line.dy = -line.dy;
					}
					for (Entity& b : bullets) {
						if (SDL_IntersectRectAndLine(&b.r, &line.x1, &line.y1, &line.x2, &line.y2)) {
							bullets.erase(bullets.begin() + j--);
							if (--line.energy <= 0) {
								objects.lines.erase(objects.lines.begin() + i--);
								int points = std::stoi(pointsTxt.text);
								++points;
								pointsTxt.setText(renderer, robotoF, std::to_string(points));
								break;
							}
						}
						++j;
					}
					++i;
				}
			}
#endif
#if 1 // NOTE: Player-element collision
			{
				int i = 0;
				for (Line& line : objects.lines) {
					SDL_FRect lineR = lineToFRect(line);
					if (SDL_HasIntersection(&firstPlayer.r, &lineR)) {
						if (--line.energy <= 0) {
							objects.lines.erase(objects.lines.begin() + i--);
							int points = std::stoi(pointsTxt.text);
							++points;
							pointsTxt.setText(renderer, robotoF, std::to_string(points));
							break;
						}
					}
					if (SDL_HasIntersection(&secondPlayer.r, &lineR)) {
						if (--line.energy <= 0) {
							objects.lines.erase(objects.lines.begin() + i--);
							int points = std::stoi(pointsTxt.text);
							++points;
							pointsTxt.setText(renderer, robotoF, std::to_string(points));
							break;
						}
					}
				}
			}
			{
				int i = 0;
				for (Circle& circle : objects.circles) {
					SDL_FRect circleR = circleToRect(circle);
					if (SDL_HasIntersection(&circleR, &firstPlayer.r)) {
						if (--circle.energy <= 0) {
							objects.circles.erase(objects.circles.begin() + i--);
							int points = std::stoi(pointsTxt.text);
							++points;
							pointsTxt.setText(renderer, robotoF, std::to_string(points));
							break;
						}
					}
					if (SDL_HasIntersection(&circleR, &secondPlayer.r)) {
						if (--circle.energy <= 0) {
							objects.circles.erase(objects.circles.begin() + i--);
							int points = std::stoi(pointsTxt.text);
							++points;
							pointsTxt.setText(renderer, robotoF, std::to_string(points));
							break;
						}
					}
					++i;
				}
			}
			{
				int i = 0;
				for (Circle& filledCircle : objects.filledCircles) {
					SDL_FRect circleR = circleToRect(filledCircle);
					if (SDL_HasIntersection(&circleR, &firstPlayer.r)) {
						if (--filledCircle.energy <= 0) {
							objects.filledCircles.erase(objects.filledCircles.begin() + i--);
							int points = std::stoi(pointsTxt.text);
							++points;
							pointsTxt.setText(renderer, robotoF, std::to_string(points));
							break;
						}
					}
					if (SDL_HasIntersection(&circleR, &secondPlayer.r)) {
						if (--filledCircle.energy <= 0) {
							objects.filledCircles.erase(objects.filledCircles.begin() + i--);
							int points = std::stoi(pointsTxt.text);
							++points;
							pointsTxt.setText(renderer, robotoF, std::to_string(points));
							break;
						}
					}
					++i;
				}
			}
#endif
			if (objects.circles.empty() && objects.filledCircles.empty() && objects.lines.empty()) {
				goto gameBegin;
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
			firstPlayer.draw(renderer);
			if (playerCount == 2) {
				secondPlayer.draw(renderer);
			}
			objects.draw(renderer);
			for (Entity& bullet : bullets) {
				bullet.draw(renderer);
			}
			pointsTxt.draw(renderer);
			SDL_RenderPresent(renderer);
		}
		else if (state == State::Menu) {
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
					if (SDL_PointInRect(&mousePos, &onePlayerBtn.r)) {
						playerCount = 1;
						state = State::Game;
					}
					else if (SDL_PointInRect(&mousePos, &twoPlayersBtn.r)) {
						playerCount = 2;
						state = State::Game;
					}
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
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
			playerCountTxt.draw(renderer);
			onePlayerBtn.draw(renderer);
			twoPlayersBtn.draw(renderer);
			SDL_RenderPresent(renderer);
			
		}
	}
	// TODO: On mobile remember to use eventWatch function (it doesn't reach this code when terminating)
	return 0;
}