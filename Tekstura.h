#pragma once
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern SDL_Renderer* gameRenderer;
extern SDL_Window* gameWindow;
extern TTF_Font* gameFont;

class Tekstura
{
public:
	Tekstura();
	~Tekstura();

	void render(int x, int y, SDL_Rect* Clip, double kut, SDL_Point* centar, SDL_RendererFlip zrcaljenje);
	bool loadScaledFromFile(std::string putanja, int duzina, int visina);  // ucitavanje png tekstura i skaliranje na odredjene dimenzije
	bool loadShadedText(std::string tekst, SDL_Color bojaTeksta, SDL_Color bojaPozadine);
	bool loadBlendedText(std::string tekst, SDL_Color bojaTeksta, int prelom);

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode mode);
	void setAlpha(Uint8 alpha);
	int getDuzina();
	int getVisina();

	void free(); // oslobodjenje zauzetih resursa 

private:

	int _width;
	int _height;
	SDL_Texture* _texture;

};

