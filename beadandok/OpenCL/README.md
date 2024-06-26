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
### Futási idő ezred másodpercben a képméret (pixelek) függvényében, állandóra vett kernel mérettel

![Kép1](https://github.com/mrByco/parralel-L27NCJ/assets/20614904/bf74d28c-cee4-4ce2-8957-4b086c018fe9)

*A futási időket méretenként összeadtuk, az így kapott eredmény a logaritmikus Y tengely

### Futási idő ezred másodpercben a kernel méret (pixelek) függvényében, állandó képmérettel
![Kép2](https://github.com/mrByco/parralel-L27NCJ/assets/20614904/9f72353f-e419-4238-9017-f988e1cc5254)

*A futási időket kernel méretenként összeadtuk, az így kapott eredmény a logaritmikus Y tengely

A részletes adatokat a jegyzékbe feltöltött xlsx és csv állomány tartalmazza.


