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

    SDL_Color * color;
    Uint8 *index;

    fmt = surface->format;



    index = (Uint8 *)surface->pixels;
    for (int y = 0; y < surface->h; ++y) {
        for (int x = 0; x < surface->w; ++x) {
            SDL_LockSurface(surface);
            
            /* Get the topleft pixel */
            color = &fmt->palette->colors[*index];

            SDL_UnlockSurface(surface);

            if (color->r > 0 && color->r < 255) {
                printf("Pixel Color-> Red: %d, Green: %d, Blue: %d. Index: %d\n",
                    color->r, color->g, color->b, *index);
            }
            index += fmt->BytesPerPixel;
        }
    }
    printf("w: %d, h: %d\n", surface->w, surface->h);
}