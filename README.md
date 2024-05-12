## Parallel Biszterszky Mátyás L27NCJ

Paraméterezhető Gauss-szűrő algoritmus megvalósítva négyfajta technológiával. Mindegyik programban lesz beépített időmérés, így az egyes technológiákat össze lehet hasonlítani. Az algoritmus megadott méretű, random generált fekete-fehér képpel dolgozik, azért dolgozunk véletlenszerűen előállított bemenettel, mert így tetszőlegesen változtatható a mérete. A (látványos) tesztelés érdekében a lementett nyers raw-fájl átkonvertálható az ffmpeg könyvtár segítségével png-re. Mindegyik beadandóhoz tartozik egy run.sh script a beadandó könyvtárában, ez lefordítja a programot, futtatja, majd a kapott képet png-re konvertálja.


# Időmérés

Mindegyik program a futása során egyetlen egy számot küld ki az stdout-ra, ez az algoritmus tiszta futási ideje, kernelszámítás nélkül. A projektek mappái mellett található egy Measurements mappa, a lefordított programok behelyezve, megfelelően elnevezve innen lehet futtatni az algoritmusokat, a measure_all.sh script segítségével. Az előre megadott paraméterek segítségével lefuttatja a programokat, és az eredményt az stdout-ról olvasva egy elemzésnél feldolgozandó .csv fileba menti.

# Paraméterezhetősség

A guassian szűrő egyik tulajdonsága az algalmazott kernel mérete, ennek a sugarát megadva lehet változtatni a program bonyolultságán.

# Párhuzamosítás

A képet vízszintes szeletekre bontva tudnak a szálak párhuzamosan dolgozni a képen. A szálak az eredményt a 2 dimenziós output float tömb szeparált részeire írják így írásnál nem lehet ütközés.

## További párhuzamosítás OpenCL esetében

1. A párhuzamosítás pixelenként történik. A végleges kép pixeleinek kiszámolása külön szálon történik, akár egyszerre is. Így elméletben a kép mérete irrelevánssá válik, amíg van elég szálunk.
2. (Plusz feladat) A kép pixeleit alapul véve, a kép pixeljei helyett a kernel minden egyes pixelét vesszük külön szálnak. Ebben az esetben valószínűleg a szálkezelés már több erőforrást vesz igénybe, mint a tényleges számítás. Ennek alátámasztására írtam egy kis méretű opencl programot, egy négyzetesen futó algoritmust, ami a megoldás jegyzékében belül a measure_threading mappában található.

A programnak van egy paramétere, ennek a függvényében változik a futási ideje négyzetesen.

A programot több beállítással is futtattam, a futtatáskor ügyeltem arra, hogy az elvégzett összeadások és iterációk száma minden esetben megegyezzen. A következőt tapasztaltam:

A futási idő a párhuzamosítással csökkent addig a pontig, amíg át nem léptem az eszközön használható párhuzamos szálak számát. Mivel esetemben 24 mag volt a videokártyán, és a maximum work group mérete 256, dimenziónként ez a szám 6144. 6144 párhuzamosan elvégzett számításig a teszt programom tökéletesen futott. Ha a párhuzamos szálak számát e fölé növeltem, a program futási ideje megnőtt.

<img width="713" alt="Screenshot 2024-05-12 at 13 42 13" src="https://github.com/mrByco/parralel-L27NCJ/assets/20614904/edf5d3cf-a1da-45de-99b7-f437709dc89d">



## Eredmények

[Processzoron futó párhuzamosítások (2023)](https://github.com/mrByco/parralel-L27NCJ/tree/master/beadandok/CPU)

## Video kártyás párhuzamosítás


[Videokártyán futó párhuzamosítások (2024)](https://github.com/mrByco/parralel-L27NCJ/tree/master/beadandok/OpenCL)

