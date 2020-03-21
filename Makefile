clearlibs:
	-rm -f simpletext.o
	-rm -f pseudo_physics.o
	-rm -f gralispr.o
	-rm -f gralist.o
	-rm -f grali_shapes.o
	-rm -f cfread.o
	-rm -f errlib.o
	-rm -f threadsched.o
	-rm -f grali_mono_text.o
	-rm -f sprites.o
	-rm -f grlitranspri.o
crts:
	gcc  --std=gnu11 -O0 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  benchco.c Lay_Z_file.o grali_mono_text.o cfread.o gralist.o errlib.o threadsched.o simpletext.o libco.a liblthread.a -o bench -lm  -latomic `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags xext x11-xcb xcb-keysyms xcb-shm cairo-xcb `
work:
	gcc  --std=gnu11 -Ofast -ffast-math -mtune=native -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  UI_mainTextUI.c UI_globalvarsTextUI.o Lay_Z_file.o grali_mono_text.o cfread.o gralist.o errlib.o threadsched.o simpletext.o libco.a  -o txwrk -lm  -latomic liblthread.a `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags xext x11-xcb xcb-keysyms xcb-shm cairo-xcb `
wfast:
	gcc  --std=gnu11 -Ofast -ffast-math -march=native -mtune=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  UI_mainTextUI.c UI_globalvarsTextUI.o grali_mono_text.o cfread.o gralist.o errlib.o Lay_Z_file.o pseudo_physics.o threadsched.o simpletext.o -o txfst -lm  -latomic libco.a liblthread.a `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags xext x11-xcb xcb-keysyms xcb-shm cairo-xcb `
wslo:
	gcc  --std=gnu11 -O0 -mtune=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  UI_mainTextUI.c UI_globalvarsTextUI.o grali_mono_text.o slow_cfread.o slow_gralist.o slow_errlib.o slow_pseudo_physics.o libco.a liblthread.a slow_threadsched.o slow_Lay_Z_file.o slow_simpletext.o -o txslo -lm  -latomic `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags xext x11-xcb xcb-keysyms xcb-shm cairo-xcb `
pparts:
		gcc  --std=gnu11 -O0 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall    UI_globalvarsTextUI.o Lay_Z_file.o grali_mono_text.o cfread.o gralist.o errlib.o  threadsched.o simpletext.o libco.a UIpixelparticlesTextUI.c -o pixie_parts.o -lm liblthread.a -latomic `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags xext x11-xcb xcb-keysyms xcb-shm cairo-xcb `
lty:
	-rm -f loopthreads
	gcc -O3 -ffast-math --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  loopthreads.c cfread.o gralist.o gralispr.o errlib.o pseudo_physics.o threadsched.o -o loopthreads -lm liblthread.a libco.a `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags xext x11-xcb xcb-keysyms xcb-shm cairo-xcb`
newsched:
	-rm -f threads_batch.o
	gcc -O3 -ffast-math --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  -Wno-unused-variable threads_batch.c -c -o threads_batch.o -lm   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-shm`
lsched:
	gcc -O3 -ffast-math --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  -Wno-unused-variable threadsched.c -c -o threadsched.o -lm   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-shm`
lazy:
	-rm -f Lay_Z_file.o
	gcc -O0 --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  -Wno-unused-variable Lay_Z_file.c -c -o Lay_Z_file.o   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu;`
spriteslib:
	-rm -f	sprites.o
	gcc -O3 -ffast-math --std=gnu11  -g -pg -fms-extensions -march=native -D_REENTRANT -pthread  -Wall -c sprites.c -o sprites.o -lm  `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags  x11-xcb xcb-shm  xcb-keysyms`
physics:
	-rm -f	physics.o
	gcc -O3 --std=gnu11 -march=native -ffast-math -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall -c pseudo_physics.c  -o pseudo_physics.o -lm  `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags  x11-xcb xcb-shm  xcb-keysyms`
	gcc --std=gnu11 -O3 -ffast-math -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall -c pseudo_physics.c  -o e.z.physics.o -lm  `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags  x11-xcb xcb-shm  xcb-keysyms`
glst:
	rm -f gralist.o
	gcc  -Ofast --std=gnu11 -mtune=native -march=native -ffast-math -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall -c -Wno-int-to-pointer-cast -Wno-unused-variable -Winline  gralist.c -o gralist.o   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-keysyms xcb-shm cairo-xcb`
grlispr:
	gcc -Ofast -ffast-math --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT   -Wall -c gralisprites.c -o gralispr.o   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags  x11-xcb xcb-shm  xcb-keysyms`
cfread:
	gcc -g -pg -fms-extensions -Wall -c configreader.c -o cfread.o
errlib:
	gcc -ffast-math -g -pg -fms-extensions -Wall -c errorlib.c  -o errlib.o

monotxt:
	gcc -Ofast -ffast-math  --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread	-Wall -c grali_mono_text.c  grali_mono_text.o -o grali_mono_text.o -lm -lXext `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-keysyms xcb-shm cairo-xcb`
spltext:
	gcc  -ffast-math --std=gnu11 -march=native  -g -pg -fms-extensions -Wall -c -pthread  grali_simple_txt.c  -o simpletext.o `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-shm cairo-xcb`
txt:
	gcc  grali_mono_text.c  --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread	-Wall -c  -o grali_mono_text.o -lm -lXext `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-keysyms xcb-shm cairo-xcb`
	gcc  --std=gnu11 -march=native  -g -pg -fms-extensions -Wall -c -pthread	grali_simple_txt.c -o simpletext.o  `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-shm cairo-xcb`
tspr:
	rm -f grlitranspri.o
	gcc -O3 -ffast-math --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread	-Wall -c grali_from_LG_sprites.c -o grlitranspri.o -lm -lXext `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-keysyms xcb-shm cairo-xcb`
lpy:
	gcc -O3 -ffast-math --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  loopthreads.c grali_mono_text.o cfread.o gralist.o gralispr.o errlib.o  pseudo_physics.o threadsched.o -o loopy -lm  `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags xext x11-xcb xcb-keysyms xcb-shm cairo-xcb`
uigv:
	gcc -Ofast --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -Wall -c UI_globalvarsTextUI.c -o UI_globalvarsTextUI.o
allmake:
	-rm -f simpletext.o
	-rm -f pseudo_physics.o
	-rm -f gralispr.o
	-rm -f gralist.o
	-rm -f grali_shapes.o
	-rm -f cfread.o
	-rm -f errlib.o
	-rm -f threadsched.o
	-rm -f grali_mono_text.o
	-rm -f sprites.o
	-rm -f Lay_Z_file.o
	-rm -f grlitranspri.o
	-rm -f UI_globalvarsTextUI.o
	gcc -Ofast --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -Wall -c UI_globalvarsTextUI.c -o UI_globalvarsTextUI.o
	gcc -Ofast --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall -c pseudo_physics.c  -o pseudo_physics.o -lm  `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags  x11-xcb xcb-shm  xcb-keysyms`
	gcc  -Ofast --std=gnu11 -march=native -ffast-math -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall -c -Wno-int-to-pointer-cast -Wno-unused-variable -Winline  gralist.c -o gralist.o   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-keysyms xcb-shm cairo-xcb`
	gcc -Ofast -ffast-math --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT   -Wall -c gralisprites.c -o gralispr.o   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags  x11-xcb xcb-shm  xcb-keysyms`
	gcc -Ofast -ffast-math --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  -Wno-unused-variable threadsched.c -c -o threadsched.o -lm   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-shm`
	gcc -Ofast -g -ffast-math -march=native -pg -fms-extensions -Wall -c configreader.c  -o cfread.o
	gcc -Ofast -g -march=native -ffast-math -ffast-math -pg -fms-extensions -Wall -c errorlib.c  -o errlib.o
	gcc -Ofast -c -g -pg -Wall -ffast-math -fms-extensions --std=gnu11 -march=native -D_REENTRANT grali_mono_text.c  -o grali_mono_text.o -lm -lXext -pthread `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-keysyms xcb-shm cairo-xcb`
	gcc  --std=gnu11 -march=native -ffast-math -g -pg -fms-extensions -Wall -c -pthread	grali_simple_txt.c -o simpletext.o  `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-shm cairo-xcb`
	gcc -Ofast --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -Wall -c UI_globalvarsTextUI.c -o UI_globalvarsTextUI.o
	gcc -O0 --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  -Wno-unused-variable Lay_Z_file.c -c -o Lay_Z_file.o   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu;`
allslow:
	-rm -f slow_simpletext.o
	-rm -f slow_pseudo_physics.o
	-rm -f slow_gralispr.o
	-rm -f slow_gralist.o
	-rm -f slow_grali_shapes.o
	-rm -f slow_cfread.o
	-rm -f slow_errlib.o
	-rm -f slow_threadsched.o
	-rm -f slow_grali_mono_text.o
	-rm -f slow_sprites.o
	-rm -f slow_grlitranspri.o
	-rm -f slow_Lay_Z_file.o
	-rm -f slow_UI_globalvarsTextUI.o
	gcc  --std=gnu11 -O0 -g -pg -fms-extensions -D_REENTRANT -Wall -c UI_globalvarsTextUI.c -o slow_UI_globalvarsTextUI.o
	gcc  --std=gnu11 -O0 -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall -c pseudo_physics.c  -o slow_pseudo_physics.o -lm  `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags  x11-xcb xcb-shm  xcb-keysyms`
	gcc  --std=gnu11 -O0  -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall -c -Wno-int-to-pointer-cast -Wno-unused-variable -Winline  gralist.c -o slow_gralist.o   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-keysyms xcb-shm cairo-xcb`
	gcc --std=gnu11 -O0 -g -pg -fms-extensions -D_REENTRANT   -Wall -c gralisprites.c -o slow_gralispr.o   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags  x11-xcb xcb-shm  xcb-keysyms`
	gcc --std=gnu11 -O0 -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  -Wno-unused-variable threadsched.c -c -o slow_threadsched.o -lm   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-shm`
	gcc -g -pg -O0 -fms-extensions -Wall -c configreader.c  -o slow_cfread.o
	gcc -g -pg -O0 -fms-extensions -Wall -c errorlib.c  -o slow_errlib.o
	gcc  grali_mono_text.c -O0 --std=gnu11 -g -pg -fms-extensions -D_REENTRANT -pthread	-Wall -c  -o slow_grali_mono_text.o -lm -lXext `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-keysyms xcb-shm cairo-xcb`
	gcc  --std=gnu11 -O0 -g -pg -fms-extensions -Wall -c -pthread	grali_simple_txt.c -o slow_simpletext.o  `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags x11-xcb xcb-shm cairo-xcb`
	gcc -O0 --std=gnu11 -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  -Wno-unused-variable Lay_Z_file.c -c -o slow_Lay_Z_file.o   `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu;`
llegl:
	gcc  --std=gnu11 -O0 -ffast-math -mtune=native -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  regl.c -o regal -lm -lEGL -latomic -lwayland-egl -lwayland-client -lwayland-cursor `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags xext x11-xcb xcb-keysyms xcb-shm cairo-xcb `
segl:
	gcc  --std=gnu11 -O0 -ffast-math -mtune=native -march=native -g -pg -fms-extensions -D_REENTRANT -pthread  -Wall  segul.c -o seegl -lm -lEGL -latomic -lwayland-egl -lwayland-client -lwayland-cursor `PKG_CONFIG_PATH=/usr/x86_64-linux-gnu; pkg-config --libs --cflags xext x11-xcb xcb-keysyms xcb-shm cairo-xcb `
