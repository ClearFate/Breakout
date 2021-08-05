#include "Tekstura.h"

void Tekstura::render(int x, int y, SDL_Rect* Clip, double kut, SDL_Point* centar, SDL_RendererFlip zrcaljenje) {

    SDL_Rect odrediste{ x, y, _width, _height };

    if (Clip != NULL) {
        odrediste.w = Clip->w;
        odrediste.h = Clip->h;
    }
    SDL_RenderCopyEx(gameRenderer, _texture, Clip, &odrediste, kut, centar, zrcaljenje);
}

bool Tekstura::loadFromFile(std::string putanja) {
    free(); // JAKO BITNO , OSLOBODI PRETHODNU TEKSTURU UKOLIKO POSTOJI

    SDL_Surface* ucitanaPodloga = IMG_Load(putanja.c_str());
    if (ucitanaPodloga == NULL) {
        printf("Metoda LoadFromFile - GRESKA: %s\n", IMG_GetError());
    }
    else {
        // SDL_SetColorKey();
        _texture = SDL_CreateTextureFromSurface(gameRenderer, ucitanaPodloga);
        if (_texture == NULL) {
            printf("Greska pretvorbe surface-a u teksturu!\n");
        }
        else {
            _width = ucitanaPodloga->w;
            _height = ucitanaPodloga->h;
        }

        SDL_FreeSurface(ucitanaPodloga);
    }

    return (_texture != NULL);
}

bool Tekstura::loadScaledFromFile(std::string putanja, int duzina, int visina) {
    free();

    SDL_Surface* originalnaSlika = IMG_Load(putanja.c_str());
    if (originalnaSlika == NULL) {
        printf("IMG_Load - Greska: %s\n", IMG_GetError());
    }
    else {
        SDL_Surface* resizeSlika = SDL_CreateRGBSurfaceWithFormat(0, duzina, visina, 32, SDL_PIXELFORMAT_RGBA32);  // jako bitno da resizeSlika prije nego se primjeni BlitScaled nije NULL 
        if (resizeSlika == NULL) {
            printf("SDL_CreateRGBSurfaceWithFormat nije uspio alocirati SDL_Surface* resizeSlika!\n");
        }
        else {
            if (SDL_BlitScaled(originalnaSlika, NULL, resizeSlika, NULL) != 0) {
                printf("SDL_BlitScaled greska: %s\n", SDL_GetError());
            }
            else {

                _texture = SDL_CreateTextureFromSurface(gameRenderer, resizeSlika);
                if (_texture == NULL) {
                    printf("PT - loadScaled - greska prilkom pretvorbe surface-a u teksturu!\n");
                }
                else {

                    _width = resizeSlika->w;
                    _height = resizeSlika->h;
                }

                SDL_FreeSurface(resizeSlika);
            }
        }

        SDL_FreeSurface(originalnaSlika);
    }

    return (_texture != NULL);
}

bool Tekstura::loadShadedText(std::string tekst, SDL_Color bojaTeksta, SDL_Color bojaPozadine) {
    free(); // BITNO

    SDL_Surface* ucitaniTekst = TTF_RenderText_Shaded(gameFont, tekst.c_str(), bojaTeksta, bojaPozadine);
    if (ucitaniTekst == NULL) {
        printf("LoadShadedtext - Greska: %s\n", TTF_GetError());
    }
    else {
        _texture = SDL_CreateTextureFromSurface(gameRenderer, ucitaniTekst);
        if (_texture == NULL) {
            printf("LoadShadedtext - Greska: %s\n", SDL_GetError());
        }
        else {
            _width = ucitaniTekst->w;
            _height = ucitaniTekst->h;
        }

        SDL_FreeSurface(ucitaniTekst);
    }

    return (_texture != NULL);
}


bool Tekstura::loadBlendedText(std::string tekst, SDL_Color bojaTeksta, int prelom) {
    free(); // BITNO

    SDL_Surface* ucitaniTekst = TTF_RenderText_Blended_Wrapped(gameFont, tekst.c_str(), bojaTeksta, prelom);
    if (ucitaniTekst == NULL) {
        printf("LoadShadedtext - Greska: %s\n", TTF_GetError());
    }
    else {
        _texture = SDL_CreateTextureFromSurface(gameRenderer, ucitaniTekst);
        if (_texture == NULL) {
            printf("LoadShadedtext - Greska: %s\n", SDL_GetError());
        }
        else {
            _width = ucitaniTekst->w;
            _height = ucitaniTekst->h;
        }

        SDL_FreeSurface(ucitaniTekst);
    }

    return (_texture != NULL);
}

void Tekstura::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(_texture, red, green, blue);
}

void Tekstura::setBlendMode(SDL_BlendMode mode) {
    SDL_SetTextureBlendMode(_texture, mode);
}

void Tekstura::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(_texture, alpha);
}

int Tekstura::getWidth() {
    return _width;
}

int Tekstura::getHeight() {
    return _height;
}

void Tekstura::free() {
    if (_texture != NULL) {

        SDL_DestroyTexture(_texture);
        _texture = NULL;
    }
}





