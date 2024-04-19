# Projekt struktúra

A fő jegyzék két aljegyzéket tartalmaz
## OpenMP
A korábban elkészült OpenMP guassian blur másolata, a mérésekhez szabva, paraméterezhetően változtatható felbontással.

## OpenCL

Egy python projekt mely két megoldást tartalmaz. Az A fő megoldást a main.py és a guassian_blur.cl fileok tartalmazzák.
A main_separabel.py egy kísérlet további optimalizálásra. Ez viszont más jóval optimálisabb algoritmust használ mint a korábbi processzor alapú megoldás.

# Futtatás

## OpenMP
A futtatáshoz c fordító szükséges. Futtassuk a run.sh szkriptet az OpenMP jegyzéken belül, ez elkészíti a futtatható álományt.

## OpenCL
A program függőségeit a requirements.txt tartalmazza. A függőségek telepítése után megfelelő argumentumokkal futtatható a program.

## Mérések futtatása

A make_measurings.sh szkript tartalmazza a mérési paramétereket és futtatja a programokat, illetve rögzíti az eredményeket. FONTOS hogy nem ez felel a mérésekért. *A mérési eredmények a gausz algoritmus tiszta futási idejét mérik, ennek a jelenlegi konfigurációban nem része a kernel kiszámítása*.


## Mért eredmények

Konifguráció

- i7 7700k
- GTX 1050 ti
- Windows 11
- 16gb ram




A részletes adatokat a jegyzékbe feltöltött xlsx és csv állomány tartalmazza.


