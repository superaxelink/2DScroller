#include "GameClass.h"
#include "MenuHandler.h"
#include "../timer.h"
#include <sstream>

/* Run the code with ctrl + shift + p and looking for run build task and the name of the task
 or with ctrl + shit + b  */

/* Here I've been using surface or software rendering with SDL_SURFACE

SDL_Texture on the other hand, is used in a hardware rendering, textures are stored in VRAM and you 
don't have access to it directly as with SDL_Surface. 
The rendering operations are accelerated by GPU, using, internally, 
either OpenGL or DirectX (available only on Windows) API, which in turn are using your video hardware, 
hence hardware rendering name

Hardware rendering is by orders of magnitude faster than software rendering and should be always be 
considered as primary option.
*/

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc, char* args[]){

  // Inicializar la semilla del generador de números aleatorios
  srand(time(nullptr));

  Timer fpsTimer;
  Timer capTimer;

  GameClass gameClass;

  //In memory text stream
  std::string timeText;
  //Main loop flag
	bool quit = false;
  //while application is running
  int countedFrames = 0;
  fpsTimer.start();
  Uint32 prevTicks = 0;
  const int FRAMES_PER_SECOND = 10;
  const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
  while(!quit){
    capTimer.start();

    // Calculate FPS based on a one-second interval
    if (fpsTimer.getTicks() - prevTicks >= 1000) {
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
        printf("Average FPS: %.2f\n", avgFPS);
        prevTicks = fpsTimer.getTicks();
        countedFrames = 0;
    }

    // Limit the update and draw to 30 times per second
    if (capTimer.getTicks() - prevTicks >= SKIP_TICKS) {
        gameClass.updateGame(quit);
        gameClass.drawGame();
        ++countedFrames;
        prevTicks += SKIP_TICKS;
    }

    // Wait the remaining time to reach target frame rate
    int frameTicks = capTimer.getTicks();
    if (frameTicks < SKIP_TICKS) {
        SDL_Delay(SKIP_TICKS - frameTicks);
    }

/*     //Calculate and correct fps
		float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
		if( avgFPS > 2000000 ){
			avgFPS = 0;
    //To calculate frames per second, you just take the number of rendered frames and divide it 
    //by the seconds passed. Now it is possible for there to be a very small amount of time 
    //passed for the first frame and have it give us a really high fps. This is why we correct 
    //the value if it is really high. 
      printf("tacos");
		}
    gameClass.updateGame(quit);
    gameClass.drawGame();
    ++countedFrames;

    //If frame finished early
    //caping frame with the captimer
		int frameTicks = capTimer.getTicks();
		if( frameTicks < SCREEN_TICK_PER_FRAME ){
			//Wait remaining time
			SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks ); //parameter is time in miliseconds
    //Finally here we have the code to cap the frame rate. First we get how many ticks the frame took to 
    //complete. If the number of ticks the frame took to execute is less than the ticks needed per frame, 
    //we then delay for the remaining time to prevent the application from running too fast.
    
    //There's a reason we'll be using VSync for these tutorials as opposed to manually capping the frame
    //rate. When running this application, you'll notice that it runs slightly fast. 
    //Since we're using integers (because floating point numbers are not precise), the ticks per frame 
    //will be 16ms as opposed to the exact 16 2/3ms. This solution is more of a stop gap in case you have 
    //to deal with hardware that does not support VSync.
		} */
  }
  gameClass.close();

  return 0;
}