#include "utils.h"

bool Utils::squareCollision(int o1x1, int o1x2, int o1y1, int o1y2,
 int o2x1, int o2x2, int o2y1, int o2y2){
  if(o2y2 <= o1y1){return false;} //bottom1 above top2
  if(o1y2 <= o2y1 ){return false;} //top1 above bottom2
  if(o1x2 <= o2x1){return false;} //right1 past left2
  if(o2x2 <= o1x1 ){return false;} //left1 past right2
  //If none of the sides from A are outside B
  return true;
};

SDL_Texture* Utils::loadTexture( std::string path, SDL_Renderer* gRenderer, 
	int &width, int &height, bool rescale, int newWidth, int newHeight){

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr ){
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
		return NULL;
	}
	else{
		//Color key image
		//SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
/*  SDL_SetColorKey: Esta función de SDL se utiliza para establecer un color clave en una superficie 
		para lograr transparencia de color. Toma tres argumentos:
    loadedSurface: La superficie en la que deseas establecer el color clave.
    SDL_TRUE: Indica que deseas habilitar la funcionalidad de color clave.
    SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF): Este es el color que se considerará transparente. 
		Estás utilizando SDL_MapRGB para crear un valor que representa un color en el formato de la 
		superficie loadedSurface. En este caso, estás utilizando el valor 0 para el componente rojo (R), 
		0xFF (255 en decimal) para el componente verde (G) y nuevamente 0xFF (255) para
		el componente azul (B). Esto representa el color RGB #00FFFF, que es un tono de cian. 
		Cualquier píxel en loadedSurface con este valor de color será considerado transparente.

		Entonces, lo que hace esta línea de código es decirle a SDL que, cuando renderice la textura 
		correspondiente a loadedSurface, cualquier píxel que tenga el color RGB #00FFFF se mostrará 
		como transparente, lo que significa que no se dibujará en la ventana y permitirá que los 
		elementos detrás de la textura sean visibles. Esto es útil para crear imágenes con fondos 
		transparentes en SDL cuando no se utiliza un canal alfa en las imágenes.
 */

		if(rescale){
			//Rescale the surface to a new size
	  	SDL_Surface* newSurface = SDL_CreateRGBSurface(0, newWidth, newHeight, 
				loadedSurface->format->BitsPerPixel,
        loadedSurface->format->Rmask, loadedSurface->format->Gmask,
        loadedSurface->format->Bmask, loadedSurface->format->Amask);
    	if (newSurface == nullptr) {
        // Handle error, maybe return original surface or nullptr
      	return nullptr;
    	}
    	SDL_BlitScaled(loadedSurface, nullptr, newSurface, nullptr);
			newTexture = SDL_CreateTextureFromSurface( gRenderer, newSurface );
		}else{
			newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		}

		if( newTexture == nullptr ){
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
			return NULL;
		}else{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void Utils::render(int x, int y, int w, int h, SDL_Rect* clip, SDL_Renderer* renderer, SDL_Texture* texture){
	
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, w, h}; //where are we going to draw and with what size

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( renderer, texture, clip, &renderQuad);
}

void Utils::drawText(const std::string& text, SDL_Renderer* const renderer, 
	TTF_Font* const font, int x, int y, bool centered){
	//THIS IS A PRETTY INEFICIENT FUNCTION BECAUSE CREATES AND DESTROYS SURFACE AND TEXTURE ON EVERY ITERATION
  SDL_Color color = { 0, 0, 0 }; // Color del texto (blanco en este caso)
  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (!surface) {
    return;
  }//A PROPER ERROR MANAGEMENT IS REQUIRED IN MANY PARTS OF THE PROJECT
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
		SDL_FreeSurface(surface); // Liberar la superficie
    return;
  }
  int textWidth = surface->w;
  int textHeight = surface->h;

	int posx;
	if(centered){
		//pass half the screen to center
		posx = (x - textWidth)/2;
	}else{
		posx = x;
	}

  SDL_Rect destRect = { posx, y, textWidth, textHeight }; // Posición y tamaño del texto
  SDL_RenderCopy(renderer, texture, NULL, &destRect);

	// Liberar recursos
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

/* En este ejemplo, rand() devuelve un entero aleatorio en el rango [0, RAND_MAX], 
donde RAND_MAX es una constante definida en la biblioteca estándar de C++. 
Luego, dividimos este valor por RAND_MAX para obtener un número aleatorio en el rango [0, 1]. 
La función static_cast<double> se utiliza para convertir el resultado a un valor de tipo double. */
double Utils::random(){
	return ((double) rand() / (RAND_MAX));
}

double Utils::randomness(){
	return ((double) rand() / (RAND_MAX));
}