## Just to keep in mind
This are points that I will remember myself, so it will be in German

Wo stehe ich | Was muss noch | Bemerkung
------------ | ------------- | ---------
Die History in der Doxy-Page hängt hinter her | Da ist die letzte Version 0.1.0 | Ich muss dran denken diese mit zu ziehen.
IsoTP_Cfg ist noch ein Dummy | Benötige ich im UDS | VersionsInfo steht noch in IsoTP.h -> muss ins Cfg
UDS | kommt jetzt | Ideen?
Vermischung von CanIf und CanDrv | Wir brauchen CanDrv für bxCAN und FDCAN | mit der Version 0.2.x bxCAN als CanDrv
bxCAN mit der Nutzung von weak Funktionen | Überarbeitung zur Nutzung der Funktionspointer in der HAL | Project Manager -> Advanced Settings -> Register Callback
stm32h7xx_hal_conf.h wird für beide Cores unterschiedlich erzeugt | - | Auch die Darstellung des #define  USE_HAL_FDCAN_REGISTER_CALLBACKS ist in der IDE(C-View) nicht gegeben. Es wird aber richtig compiliert.

**Achtung: Wird irgendetwas an den USER CODE sections in den Freemarker Templates geändert, so kommt es vor das Inhalt der Sections beim Code generieren gelöscht wird**

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
+ **Board Part** Module bxCAN wird erweitert um alle CAN Controller Treiber zu enthalten
+ **Mode Conditions** nutzen um die Konfigurationen entsprechend de Treibers bereit zu stellen

### Feature Requests für bxCAN
+ Die Anzahl der Filterbänke für Master und Slave werden konfiguriert. Das könnte man dynamisch lösen.
+ Die Function HAL_CAN_ConfigFilter() ist schrecklich -> evtl wäre eine Entkopplung der HAL der Weg

## Was fehlt im IsoTP
+ aktuell ist feste Zuordnung auf bxCAN Master mit CanID 0x7EF
+ Anwendung mit UDS und OBD
+ langfristig sollte **DataExchange Common** einen anderen Namen bekommen (vielleicht **DataExchange OBD**?)

### minimum FlowControl 
Antwort auf 0x7DF:
0x7EF:0x30 0x00 0x00 (DLC mind 3)

## Was ist mit RxIndication
+ gem. AUTOSAR wird eine eingegangene CanMessage immer mit RxIndication über das CanIf ins Upperlayer gemeldet und unmittelbar kopiert
+ im Interrupt Mode passiert das in der ISR
+ im Polling mode wird nur die Hardware-Mailbox/Hardware-In-FIFO in einer Task gepollt und dann bei Erfolg die RxIndication aufgerufen

## Bekannte Stolpersteine
### bxCAN AutoRetransmission 
Das Registerbit heißt CAN_MCR:Bit 4 NART  -> No automatic retransmission
STM nutzt in seiner CAN_InitTypeDef und dann in der HAL_CAN_Init() eine Invertierung.  
- Das heißt für ein automatisches erneutes Senden muss das Registerbit NULL sein. Der Wert des InitStruct muss TRUE sein.
- Der Wert aus der IDE muss normal auch TRUE sein um das erneute Senden standardmäßig einzuschalten

### bxCAN Slave ohne CAN2
Aktuell lässt sich der CanDrv_bxCAN Slave aktivieren und auch generieren ohne das CAN2 unter Connectivity aktiv ist.  
Ich muss herausfinden was das für Probleme mit sich bringt

### There is a bug in code generation of FreeRTOS for STM32F4xx controllers
Mit dem Update STM32CubeMX 6.7.0 ist die Datei FREERTOS-STM32F4xx_Configs.xml (Zeile 349) fehlerhaft.
Das Update wird "noch nicht" in die Tutorials übernommen.
Wir sollten in Zukunft die Version der CubeMX und der IP irgendwie mit in die generierten Dateien übernehmen