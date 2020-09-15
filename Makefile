build-debug-win: make-output-folders
	cp output/win/debug/imgui.ini output/imgui.ini || :
	g++ -o output/win/debug/foosiespp.exe $(shell ls src/*.cpp) -Isrc/ui/game src/ui/game/*.cpp -Isrc/ui/dev src/ui/dev/*.cpp -Isrc/deps/imgui src/deps/imgui/*.cpp -std=c++17 -static-libstdc++ -Isrc -Ibin -Isrc/deps/raylib -Isrc/deps/raylib/external -Isrc/deps/raylib/external/glfw/include -Lbin -Lsrc/deps/raylib -lraylib -lggponet -lopengl32 -lgdi32 -lwinmm -DWIN32 -D_WIN32 -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP -D_DEBUG -D_CONSOLE -Wl,--subsystem,console -g -O0
	# -e mainCRTStartup
	cp output/win/raylib.dll output/win/debug/raylib.dll
	cp bin/ggponet.dll output/win/debug/ggponet.dll
	cp -r assets/ output/win/debug/assets/
	cp output/imgui.ini output/win/debug/imgui.ini

build-debug-win-no-assets: make-output-folders
	cp output/win/debug/imgui.ini output/imgui.ini || :
	g++ -o output/win/debug/foosiespp.exe $(shell ls src/*.cpp) -Isrc/ui/game src/ui/game/*.cpp -Isrc/ui/dev src/ui/dev/*.cpp -Isrc/deps/imgui src/deps/imgui/*.cpp -std=c++17 -static-libstdc++ -Isrc -Ibin -Isrc/deps/raylib -Isrc/deps/raylib/external -Isrc/deps/raylib/external/glfw/include -Lbin -Lsrc/deps/raylib -lraylib -lggponet -lopengl32 -lgdi32 -lwinmm -DWIN32 -D_WIN32 -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP -D_DEBUG -D_CONSOLE -Wl,--subsystem,console -g -O0
	# -e mainCRTStartup
	cp output/win/raylib.dll output/win/debug/raylib.dll
	cp bin/ggponet.dll output/win/debug/ggponet.dll
	cp output/imgui.ini output/win/debug/imgui.ini

update-assets-debug:
	cp -r assets/ output/win/debug/assets/

build-release-win: make-output-folders
	g++ -o output/win/release/foosiespp.exe $(shell ls src/*.cpp) -Isrc/ui/game src/ui/game/*.cpp -Isrc/ui/dev src/ui/dev/*.cpp -Isrc/deps/imgui src/deps/imgui/*.cpp -std=c++17 -static-libstdc++ -Isrc -Ibin -Isrc/deps/raylib -Isrc/deps/raylib/external -Isrc/deps/raylib/external/glfw/include -Lbin -Lsrc/deps/raylib -lraylib -lggponet -lopengl32 -lgdi32 -lwinmm -DWIN32 -D_WIN32 -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP -DNDEBUG -DNCONSOLE -Wl,--subsystem,console -O1
	# -e mainCRTStartup
	cp output/win/raylib.dll output/win/release/raylib.dll
	cp bin/ggponet.dll output/win/release/ggponet.dll
	cp -r assets/ output/win/debug/assets/

build-release-win-no-assets: make-output-folders
	g++ -o output/win/release/foosiespp.exe $(shell ls src/*.cpp) -Isrc/ui/game src/ui/game/*.cpp -Isrc/ui/dev src/ui/dev/*.cpp -Isrc/deps/imgui src/deps/imgui/*.cpp -std=c++17 -static-libstdc++ -Isrc -Ibin -Isrc/deps/raylib -Isrc/deps/raylib/external -Isrc/deps/raylib/external/glfw/include -Lbin -Lsrc/deps/raylib -lraylib -lggponet -lopengl32 -lgdi32 -lwinmm -DWIN32 -D_WIN32 -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP -DNDEBUG -DNCONSOLE -Wl,--subsystem,console -O1
	# -e mainCRTStartup
	cp output/win/raylib.dll output/win/release/raylib.dll
	cp bin/ggponet.dll output/win/release/ggponet.dll

update-assets-release:
	cp -r assets/ output/win/release/assets/

compile-raylib:
	gcc -c $(shell ls ./src/deps/raylib/*.c) -std=c99 -static-libgcc -D_DEFAULT_SOURCE -Wno-missing-braces -Werror=pointer-arith -fno-strict-aliasing -Isrc/deps/raylib/external/glfw/include -Isrc/deps/raylib/external/glfw/deps/mingw -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP -O1
	mv *.o ./src/deps/raylib

compile-raylib-shared: compile-raylib
	gcc -shared -o output/win/raylib.dll $(shell ls ./src/deps/raylib/*.o) -std=c99 -L. -static-libgcc -D_DEFAULT_SOURCE -Wno-missing-braces -Werror=pointer-arith -fno-strict-aliasing -lgdi32 -lwinmm -lopengl32 -Isrc/deps/raylib/external/glfw/include -Isrc/deps/raylib/external/glfw/deps/mingw -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP -D_DEBUG -D_CONSOLE -O1 -Wl,--out-implib,./src/deps/raylib/libraylib.lib

make-output-folders:
	mkdir -p output/win/debug
	mkdir -p output/win/release

run-debug:
	output/win/debug/foosiespp.exe --address 127.0.0.1 --port 8888 &
	output/win/debug/foosiespp.exe --address 127.0.0.1 --port 8888 &
run-release:
	output/win/release/foosiespp.exe --address 127.0.0.1 --port 8888 &
	output/win/release/foosiespp.exe --address 127.0.0.1 --port 8888 &
