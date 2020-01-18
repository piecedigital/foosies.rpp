# mkdir output
# cd src/deps/raylib
# gcc -c $(ls ./*.c) -std=c99 -static-libgcc -D_DEFAULT_SOURCE -Wno-missing-braces -Werror=pointer-arith -fno-strict-aliasing -Iexternal/glfw/include -Iexternal/glfw/deps/mingw -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP -D_DEBUG -D_CONSOLE -O1
# gcc -shared -o ../../../output/raylib.dll $(ls ./*.o) -std=c99 -L. -static-libgcc -D_DEFAULT_SOURCE -Wno-missing-braces -Werror=pointer-arith -fno-strict-aliasing -lgdi32 -lwinmm -lopengl32 -Iexternal/glfw/include -Iexternal/glfw/deps/mingw -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP -D_DEBUG -D_CONSOLE -O1 -Wl,--out-implib,./libraylib.lib
# cd ../../..

# -Isrc/ui/game src/ui/game/*.cpp /
g++ -o output/foosiespp.exe $(ls src/*.cpp) -Isrc/ui/dev src/ui/dev/*.cpp -Isrc/deps/imgui src/deps/imgui/*.cpp -std=c++17 -static-libstdc++ -Isrc -Ibin -Isrc/deps/raylib -Isrc/deps/raylib/external -Isrc/deps/raylib/external/glfw/include -Lbin -Lsrc/deps/raylib -lraylib -lggponet -lopengl32 -lgdi32 -lwinmm -DWIN32 -D_WIN32 -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP -D_DEBUG -D_CONSOLE -Wl,--subsystem,console -g

# ,-emainCRTStartup