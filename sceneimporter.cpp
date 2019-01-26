#include "include/sceneimporter.h"
#include "include/sdlxx.h"

using namespace sdlxx;

SceneImporter::SceneImporter() {
}

SceneImporter::~SceneImporter() {
}

void SceneImporter::load(std::string path) {
    // read in BMP file or some **** like that
    // make an SDL_Surface outta it
    auto surf_ = Sdl_surface::load_bmp(path);
    SDL_Surface * surface = surf_;

    // check out dem pixels
    //void * pixels = surface.pixels;
    SDL_PixelFormat * fmt;// = surface.format;

    // turn dem pixels into The Scene

    //for each pixel
    //  if blank:
    //    skip
    //  otherwise:
    //    for each object of pixel's color:
    //      if pixel within object's recorded bounds:
    //        skip
    //      otherwise:
    //        if pixel adjacent to object's recorded bounds:
    //          update object's recorded bounds to include pixel
    //          skip
    //    create new object of pixel's color, with bounds including the pixel

    Uint32 temp;
    Uint8 * pixel;
    Uint8 red, green, blue;

    fmt = surface->format;
    SDL_LockSurface(surface);
    pixel = ((Uint8*)surface->pixels);
    SDL_UnlockSurface(surface);


    for (int y = 0; y < surface->h; ++y) {
        for (int x = 0; x < surface->w; ++x) {
            /* Get Blue component */
            SDL_LockSurface(surface);
            blue = (Uint8)(*(pixel + fmt->Bshift));

            /* Get Green component */
            green = (Uint8)(*(pixel + fmt->Rshift));

            /* Get Red component */
            red = (Uint8)(*(pixel + fmt->Gshift));



            if (red > 0 && red < 255) {
                printf("Pixel Color -> R: %d,  G: %d,  B: %d, x: %d, y: %d\n", red, green, blue, x, y);
            }

            pixel += fmt->BytesPerPixel;

            SDL_UnlockSurface(surface);
        }
    }
    printf("w: %d, h: %d\n", surface->w, surface->h);
}