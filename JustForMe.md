## Just to keep in mind
This are points that I will remember myself, so it will be in German

Wo stehe ich | Was muss noch | Bemerkung
------------ | ------------- | ---------
Das Repo umfasst nur CanIf | Protokolle im Pack ergänzen | -
Vermischung von CanIf und CanDrv | Wir brauchen CanDrv für bxCAN und FDCAN | oder man erzeugt zwei CanIf Klassen
bxCAN mit der Nutzung von weak Funktionen | Überarbeitung zur Nutzung der Funktionspointer in der HAL | Project Manager -> Advanced Settings -> Register Callback
stm32h7xx_hal_conf.h wird für beide Cores unterschiedlich erzeugt | - | Auch die Umsetzung des #define  USE_HAL_FDCAN_REGISTER_CALLBACKS ist in der IDE nicht gegeben

## Zum Umbau auf CanDrv
### Ziel
Entkoppeln des CanIf
### Vorgaben CanIf
+ CanIf muss Hardware unabhängig sein
+ Die Verbindung zur Hardware erfolgt über einen Treiber (CanDrv)

### Vorgaben CanDrv
+ Basisklasse mit virtuellen Funktionen -> Can-Modul like AUTOSAR
+ Das CanIf kennt nur diese Basisklasse
+ Spezialisierung der Hardware durch abgleitete Klassen (CanDrv_bxCAN,CanDrv_FDCAN)
+ die Konfiguration erzeugt ein Objekt des Hardware-Treibers
+ der Software-Buffer wandert in den CanDrv (Umsetzung in der abgeleiteten Klasse)