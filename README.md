## Parallel Biszterszky Mátyás L27NCJ

Paraméterezhető Gauss szűrő algoritmus megvalsósítva 4 fajta technológiával. Mindegyik programban lesz beépített időmérés így az egyes technológiákat össze lehet hasonlítani.


Az algoritmus megadott as méretű random generált fekete fehér képpel dolgozik, azért dolgozunk véletlenszerűen előállított bemenettel mert így tetszőlegesen változtatható a mérete. A (látványos) tesztelés érdekében a lementett nyers raw-file áthonvertálható az ffmpeg könyvtár segítségével png-re.

Mindegyik beadandóhoz tartozik egy run.sh script a beadandó könyvtárában, ez lefordítja a programot, futtatja majd a kapott képet png-re konvertálja.


# Időmérés

Mindegyik program a futása során egyetlen egy számot küld ki az stdout-ra, ez az algoritmus tiszta futási ideje, kernelszámítás nélkül. A projektek mappái mellett található egy Measurements mappa, a lefordított programok behelyezve, megfelelően elnevezve innen lehet futtatni az algoritmusokat, a measure_all.sh script segítségével. Az előre megadott paraméterek segítségével lefuttatja a programokat, és az eredményt az stdout-ról olvasva egy elemzésnél feldolgozandó .csv fileba menti.

# Paraméterezhetősség

A guassian szűrő egyik tulajdonsága az algalmazott kernel mérete, ennek a sugarát megadva lehet változtatni a program bonyolultságán.

# Párhuzamosítás

A képet vízszintes szeletekre bontva tudnak a szálak párhuzamosan dolgozni a képen. A szálak az eredményt a 2 dimenziós output float tömb szeparált részeire írják így írásnál nem lehet ütközés.

# Választott technológia
C# Threading.

## Eredmények

Futtatási eredmények grafikonon, külömböző probléma méret esetén

![radius1](https://github.com/mrByco/parralel-L27NCJ/blob/master/beadandok/ResultImages/r1.png?raw=true)
![radius3](https://github.com/mrByco/parralel-L27NCJ/blob/master/beadandok/ResultImages/r3.png?raw=true)
![radius7](https://github.com/mrByco/parralel-L27NCJ/blob/master/beadandok/ResultImages/r7.png?raw=true)
![radius20](https://github.com/mrByco/parralel-L27NCJ/blob/master/beadandok/ResultImages/r20.png?raw=true)
