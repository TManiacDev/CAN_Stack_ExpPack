/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Doxy_Page_T01_CanIf_AppDemo.h

 * @author TManiac
 * @date Nov. 01, 2022
 * @version 
 *
 * This file holds the documentation of the tutorial 01.
 * At first there is the German page and then below there is the English page too. This style will be done in all doxy page files.
 */
#ifndef _DOXY_PAGE_T01_CANIF_APPDEMO_H_
#define _DOXY_PAGE_T01_CANIF_APPDEMO_H_


/** @page de_page_T01_CanIf_AppDemo Tutorial 01: CanIf_AppDemo
 *  @tableofcontents{HTML:3}
 *
  The English version is @ref eng_page_T01_CanIf_AppDemo "here".

  ########
  @section de_secTut_01_open Einleitung

  Dieses Tutorial beschreibt den grundsätzlichen Umgang mit dem ExpansionPack.
  Beginnend mit dem Aufsetzen eines neuen Projektes in der STM32CubeIDE über das Laden des Packs und dessen Konfiguration, sowie dem Empfang und dem Senden von einfachen CAN Messages.
  Die Tutorialbeschreibung ist sehr Bilder lastig, man muss also relativ viel scrollen. Ich denke aber, dass die Bilder jeden helfen sich zu Recht zu finden.

  ########
  @section de_secDownload Das STM32CubeIDE Expansion Package herunter laden

  Es macht Sinn das ExpansionPack vor Beginn zu downloaden. Wenn man sich im Repository bewegt, hat man das ExpansionPack schon vorliegen.
  Nun auch auf [github](https://github.com/TManiacDev/CAN_Stack_ExpPack)

  ########
  @section de_secNewProject Starten eines neuen Projektes

  Nach dem Start der STM32CubeIDE wird man nach dem *Workspace* gefragt in welchem man arbeiten möchte.
  Ich nutze für das gesamte Projekt um den *CAN Stack* durchgängig den Workspace wie im folgenden Bild.
  @image html T01_P00_select_workspace.png "Select Workspace directory" width=500
  Hierbei sei erwähnt, dass das "projects"-Verzeichnis eben auch jenem entspricht, welches als Spiegel zum Repository gepflegt wird.
  Möchte man das Tutorial unabhängig durch spielen, so macht es Sinn ein abweichendes Verzeichnis anzugeben.

  Beim ersten Start der STM32CubeIDE wird man von dem "Information Center" begrüßt. Hier wählen wir natürlich für's Erste aus, dass wir ein neues Projekt starten möchten.
  @image html T01_P01_start_new_project.png "Start new STM32 project" width=80%
  Später wird dieses "Information Center"-Fenster nicht unmittelbar beim Start angezeigt. Ich werde am @ref de_secRestartIDE "Ende des Tutorials" kurz auf den Neustart der STM32CubeIDE eingehen.

  Ein STM32CubeIDE-Projekt (und auch ein STM32CubeMX-Projekt) baut natürlich auf einen bekannten STM32-Mikrocontroller auf.
  Ich habe ein Nucleo-F439ZI Board, auf welchen ich arbeite.
  Das NUCLEO-F439ZI hat, wie fast alle anderen NUCLEO-Boards auch, standardmäßig kein CAN. Man kommt aber über die "ARDUINO(R) UnoV3" Verbinder an die notwendigen Pins heran.
  So habe ich mir ein "Extension Board" mit zwei CAN Transceiver gebastelt. Wir werden später die verwendeten Port-Pins auswählen.
  @image html T01_P02_select_board.png "Select Board or MCU" width=80%

  Die folgenden Dialoge sollten selbst erklärend sein. Wichtig ist, dass das ExpansionPack in C++ geschrieben ist. Die Voreinstellung ist hier leider immer C.
  Die Auswahl des verwendeten STM32Cube Firmware Package spielt aktuell noch keine Rolle, also sollte das aktuellste verwendet werden.
  @image html T01_P03_create_project.png "Steps to create project" width=80%
  Das Initialisieren der gesamten MCU-Peripherie ist nicht unbedingt erforderlich. Da es aber auch die Takterzeugung beinhaltet, ist es in den meißten Fällen sinnvoll.

  Mit "Open Associated Perspective" wird in der STM32CubeIDE (entsprechend der Eclipse Umgebung) immer die Ansicht geöffnet, welche eben für den Arbeitsschritt am besten geeignet oder evtl sogar erforderlich ist.
  Hier wird im folgenden die Perspective geöffnet, welche die Konfiguration mit grafischer Unterstützung ermöglicht. Die Perspective sieht wie folgt aus:
  @image html T01_P04_new_project.png "New project perspective" width=80%

  Ich möchte hier nicht explizit auf den Aufbau der STM32CubeIDE eingehen. Wichtig an dieser Stelle ist, das wir auf der linken Seite den "normalen" Eclipse Project Browser haben.
  Der Großteil der Arbeitsfläche wird von der Darstellung der "*.ioc"-Datei verwendet. Die Ansicht des Controllers ist auf den jeweilgen Footprint angepasst.
  Wie man auf dem Bild erkennen kann, hat der STM32F439ZIT auf meinem NUCLEO-F439ZI Board einen LQFP144 Footprint.

  Die STM32CubeIDE benennt die neu erzeugte "*.ioc"-Datei genauso wie das Projekt. Demnach haben wir jetzt eine "CanIf_AppDemo.ioc".

  Da wir den CAN-Controller verwenden wollen, müssen wir diesen auch konfigurieren.
  CAN stellt eine "Connectivity" Peripherie dar.
  Also finden wir unter diesem Punkt auch die Module "CAN1" und "CAN2".
  Bei meinem NUCLEO-F439ZI gibt es standardmäßig keine Vorbereitung für CAN, also sind diese Module deaktiviert.
  Wählt man "CAN1" (oder auch "CAN2") aus, so erscheint eine zusätzliche Spalte mit der Bezeichnung "CAN1 Mode and Configuration".
  Die Darstellung mit diesen drei Spalten ist jener Aufbau welcher für die Konfiguration der STM32Cube-Elemente (welche intern immer als Pack gehandhabt werden) verwendet wird.

  Im Bereich "Mode" aktiviert man die jeweiligen Module. Wir aktivieren nun das CAN1 Module durch setzen des Hakens "Activated".
  @image html T01_P05_activate_can1.png "CAN1 activated" width=80%

  Jetzt werden im Bereich "Configuration" vier Tabs angezeigt. Der Tab "User Constants" spielt für uns keine Rolle. Dieser Tab wird in jeden Modul angezeigt.
  "Parameter Settings" beinhaltet die Startup Parameter des CAN-Controllers und NVIC Settings die Einstellung der verwendeten Interrupt-Callbacks.
  Das *ExpansionPack CAN Stack* übernimmt auch die Konfiguration der Startup Parameter, also lassen wir die "Parameter Settings" hier wie sie sind.
  Die Konfiguration der Interrupt-Callbacks werden wir später aufgreifen.
  @image html T01_P06_other_parameter.png "Parameter and NVIC Settings" width=80%
  Im Tab "GPIO Settings" werden die Port-Pins eingestellt, bzw angezeigt.
  Die Funktion der Pins lassen sich durch anklicken des Pins in der µC-Darstellung direkt auswählen.
  Bei meinem CAN-Transceiver-Board sind CAN1_RX an PB8 und CAN1_TX an PB9 angebunden. So nehme ich diese Einstellung hier auch vor.
  @image html T01_P07_select_pinout.png "GPIO Settings" width=80%

  Nun wird es Zeit die Konfiguration das erste Mal zu speichern.
  Beim Klick auf die "Diskette" speichert STM32CubeIDE (entsprechend der Eclipse-Umgebung) die jeweils aktive Datei.
  Da wir gerade die "CanIf_AppDemo.ioc" bearbeitet haben, wird diese gespeichert.
  Beim speichern einer "*.ioc-Datei" fragt die STM32CubeIDE standardmäßig ob der Source Code generiert werden soll.
  (Das sollte man später im Hinterkopf behalten, wenn man testweise Code ändert.)
  Danach wird man gefragt ob man zur C/C++ Perspective wechseln möchte.
  @image html T01_P08_first_save.png "Save CanIf_AppDemo.ioc and generate code" width=80%

  Der erzeugte Code sollte build-fähig sein. Das können wir durch den Klick auf den "Hammer" probieren
  @image html T01_P09_new_main_c.png "Build generated code" width=40%

  Im Project Browser sind nun auch die neuen Dateien sichtbar.
  Die C/C++ Perspective bietet uns eine "Outline"-Übersicht über die aktive Datei.
  Im unteren Bereich der IDE findet man weitere hilfreiche Fenster.
  Details sollte man sich selber in diversen Eclipse Tutorials erarbeiten.

  ###########
  @subsection de_subsecMain_c Kurzer Überblick über den Aufbau der main.c Datei

  Ich möchte hier an Hand der @c main.c Datei ganz kurz auf ein paar Besonderheiten im Umgang mit der Code Generierung in der STM32CubeIDE eingehen.
  Vielleicht verschiebe ich das Kapitel mal und mache es etwas ausführlicher. Dann kann man auch Besonderheiten bei der Bearbeitung der @c *.ftl Templates eingehen.

  @image html T01_P10_basics_on_main_c_teil1.png "how to work on main.c" width=50%
  STM nutzt eine Doxygen taugliche Formatierung, so dass man auch die Lizenzinformationen in der Source Code Doku einbinden kann.
  Der Dateikopf ist in einem

       USER CODE BEGIN Header
       [...]
       USER CODE END Header

  Block eingeordnet.
  Alles was in solch einem Block steht, wird bei einer erneuten Generierung nicht geändert.
  Diese Blöcke werden aber durch den Generator vorgegeben. Es macht also keinen Sinn selber solche Blöcke zu ergänzen.
  Man sieht hier zum Beispiel die "User Code" Blöcke für Includes und typedefs.

  Es sei aber erwähnt, das der Code "verschwindet" wenn die Datei bei der Code Generation entfernt wird, zum Beispiel dann wenn man ein Modul deaktiviert.

  @image html T01_P10_basics_on_main_c_teil2.png "Handles to work with the hardware" width=50%
  STM nutzt "Handle"-Strukturen um mit der jeweiligen Peripherie (bis auf GPIO) zu arbeiten.
  Standardmäßig wird das Handle-Objekt im Kontext der @c main.c erzeugt.
  Dieses endhält neben dem Pointer zu den Registern auch eine Struktur zur Initialisierung.

  @image html T01_P10_basics_on_main_c_teil3.png "Function declerations" width=50%
  Diese @c MX_(HW-Module)_Init() Funktionen werden für jedes Modul generiert.
  Logisch werden diese Funktionen weiter unten dann mit den Parametern aus dem @c *.ioc File gefüttert.

  Darüber hinaus haben wir hier auch Platz um eigene (einfache) Funktionen zu deklarieren ("User Code * PFP") und auch zu definieren ("User Code * 0").
  Wie gesagt, was man in solch einen Block hinein schreibt, bleibt auch bei einer Re-Generation erhalten.

  @image html T01_P10_basics_on_main_c_teil4.png "main() Function" width=50%
  Die eigentliche @c main() Funktion ruft der Reihe nach die @c Init() -Funktionen auf und geht anschließend in die für Mikrocontroller typische @c while(1) Schleife.

  Die Reihenfolge der @c MX_(HW-Module)_Init() Funktionen wird leider vom Code Generator vorgegeben.
  So lange man ausschließlich die HAL nutzt, spielt das keine Rolle.
  Da wir in unserem Expansion Pack aber HAL-Aufgaben übernehmen wollen, braucht es da einen gezielten Ansatz.

  Nach der @c main() kommen dann die einzelnen @c MX_(HW-Module)_Init() Funktionen. Als Beispiel hier nur kurz @c MX_CAN1_Init() Funktionen
  @image html T01_P10_basics_on_main_c_teil5.png "Init the CAN1 Controller" width=50%
  Grundsätzlich wird nur die Init-Struktur gefüllt und dann die eigentliche @c HAL_CAN_Init() aufgerufen.
  Nur wo werden die Pins zu geordnet. Dazu komme ich dann wenn es so weit ist.

  ########
  @section de_secPackIntegration Wie kommt das Expansion Package in die STM32CubeIDE
  @subsection de_subsecManagePack Manage Software Packs

  Nun wollen wir aber endlich das STM32Cube ExpansionPack zu unserem Projekt hinzufügen. Als erstes müssen wir der IDE sagen wo sie das ExpansionPack findet.
  @image html T01_P11_manage_software_packs.png "Open manage software packs dialog" width=80%
  Wir gehen also wieder in die Ansicht der @c CanIf_AppDemo.ioc Datei und wählen "Manage Software Packs".

  @image html T01_P12_load_pack.png "load pack" width=80%
  Man kann das ExpansionPack entweder lokal von der Festplatte oder per URL aus der Ferne integrieren.
  Wir hatten @ref de_secDownload "am Anfang" das ExpansionPack herunter geladen (oder wir haben es parallel in einem Development-Verzeichnis).
  Dieses ExpansionPack suchen wir hier und wählen es aus.

  @image html T01_P13_accept_license.png "License agrement" width=80%
  Wenn wir dann die Lizenzbedingungen gelesen und akzeptiert haben, ist das ExpansionPack integriert.

  Man findet hier in dem Fenster auch ein paar nützliche Informationen zum Umgang mit dem ExpansionPack. Da steht zum Beispiel etwas zu den MX-Funktionen.

  ########
  @subsection de_subsecSelectComp Auswahl der Module

  Jetzt müssen wir noch auswählen, welche Komponenten aus dem ExpansionPack genutzt werden sollen.
  @image html T01_P14_select_component.png "load pack" width=80%
  Es öffnet sich der "Software Pack Component Selector". Erst einmal ein kleines Bild. Ins Detail gehen wir gleich.
  @image html T01_P15_pack_selector.png "Software Pack Component Selector" width=30%
  Hier sind unter anderem alle von STMicroelectronics verfügbaren ExpansionPacks auswählbar.
  Klickt man auf @c Install wird das jeweilige ExpansionPack bei STM herunter geladen und installiert.
  Wir scrollen aber ein wenig nach unten und suchen @c TM_Engineering.CAN_Stack.
  @image html T01_P16_select_appdemo.png "Select the Demo Application" width=80%
  Durch Klick auf ">" kann man die einzelnen Module, oder genauer gesagt die einzelnen Bundles öffnen.
  Naiv wählen wir die Demo Application @c CanIf_AppDemo (deswegen haben wir unser Projekt am Anfang auch so benannt) aus.

  Nun werden da aber ein paar gelbe Warnschilder mit Ausrufezeichen angezeigt.
  @image html T01_P17_additional_info.png "Bundle warnings and Info" width=80%
  Klickt man auf den @image{inline} html DetailsButton.png "(i) button" Button (siehe beige/roter Pfeil) kann man ein paar Informationen zum jeweils aktiven Element bekommen.
  So steht zum Beispiel bei unserer Application: "This component has unresolved dependencies". Es braucht also noch irgend ein anderes Modul.
  Weiter steht da "There are solutions within this pack". Die Lösung des Problems liegt also nahe. <br>
  Mit dem @image{inline} html DependenciesButton.png "chain button" Button (grün/roter Pfeil) dann kann man die Abhängigkeiten unmittelbar anzeigen.
  In unserem Fall braucht die @c DemoApplication eine Komponente @c bxCAN/Master

  Wir ergänzen also die noch notwendigen Module die sich alle im Bundle Board Support befinden.
  - Man kann durch Auswahl der einzelnen Module versuchen das Problem selber zu lösen
  - Man kann auch einzele Probleme mit "Select" lösen. ( So lernt man vielleicht etwas über den Aufbau des Packs)
  - Mit "Show" kann man die Lösung vor selektieren.
  - Und mit "Resolve" löst man alle verketteten Probleme mit einmal. Also in unserem Fall werden die fünf erforderlichen Module ausgewählt.

  Bundle | Module | Inhalt
  ------ | ------ | ------
  CanDrv | CanDrv_APIclass    | Das ist eine virtuelle Klasse Can. Diese stellt das API für alle kompatiblen CanDrv bereit
  ^      | bxCAN / Master     | Dies ist die Umsetzung des CanDrv_bxCAN für den STM bxCAN Controller. Für das Tutorial reicht uns der Master Controller
  CanIf  | general            | Hier sind die Header Files mit den Compiler Abhängigkeiten oder auch eine Klasse zur Handhabung von Versionsinformationen zur Laufzeit enthalten
  ^      | ComIf              | Darin ist eine virtuelle Klasse enthalten, welche zur Abstraktion von Kommunikation Interface Klassen ähnlich dem AUTOSAR Ansatz vorgesehen ist
  ^      | CanIf              | Dies ist unsere abgeleitete Interface Klasse für die Kommunikation über CAN

  @image html T01_P18_select_modules.png "Select needed modules" width=80%

  Haben wir diese fünf Module aktiv, werden wir mit grünen Häkchen belohnt und können den Selector wieder schließen.

  ########
  @section secConfigPack Konfiguration der Module

  Das Aktivieren der Module erfolgt auf dem gleichen Weg, wie wir zu Beginn das CAN-Modul aktiviert haben.
  In der linken Spalte des @c CanIf_AppDemo.ioc Viewers findet man jetzt einen weiteren Punkt "Software Packs".
  Unter diesen Punkt werden alle aktiven ExpansionPacks aufgeführt. Aktuell haben wir nur ein Pack, also ist hier auch nur unser @c TM_Engineering.CAN_Stack zu finden.
  Aktiviert man hier die Module erhält man im Configuration Abschnitt die Tabs "CAN Driver", "CAN Interface" und "User Constants".
  Der Tab "User Constants" ist der gleiche den wir schon aus den Einstellungen des CAN-Modules kennen.

  @subsection de_subsecCanDrvSetting CAN Driver
  Der Tab CAN Driver beinhaltet die Konfigurationsparameter welche unmittelbar auf die Hardware wirken.
  In der AUTOSAR Spec werden diese Parameter durch das CAN-Modul bearbeitet.
  @image html T01_P19_config_modules.png "Config the Hardware Settings of the CanDrv module" width=80%
  Auch in dem "Configuration" Abschnitt gibt es wieder einen (i) Button um mehr über die einzelnen Parameter zu erfahren.

  ###Bitrate Generator
  Mit diese Parameter werden durch den Source Code Generator die notwendigen Hardware Parameter für das Bit Timing berechnet um die jeweiligen Baudraten zu erzeugen.
  Neben diesen Parametern wird die Clock des CAN Modules aus den Systemparametern genutzt.
  @remark Aktuell existiert kein Support für System Clock Switch während der Laufzeit!!!

  Parameter               | Beschreibung
  ---------               | ------------
  List of Bitrates        | Hier wird die Liste der gewünschten Bitraten angelegt. Die einzelnen Bitraten werden durch Kommas getrennt.<br>Die hier gewählten Baudraten sind während der Laufzeit auswählbar.<br>
  Bittiming Sample Point  | Sample Point als Prozent oder Kommazahl. Der Sample Point muss entweder größer 50% oder eben 0.5 < x < 1 sein

  ###bxCAN Master Setup / bxCAN Slave Setup
  Hier werden die Startup Parameter des bxCAN Master Controllers festgelegt.<br>
  Wenn man den bxCAN Slave auch aktiviert hat wird ein identischer Abschnitt für diesen angezeigt.

  Parameter              | Wert              | Beschreibung
  ---------              | ----              |------------
  Initial Bitrate        | [ Zahl, Integer ] | Hier kann eine Bitrate ausgewählt werden welche zuvor im Bereich "Bitrate Generator" definiert wurde
  Controller Mode        | Normal            | Standard. Der Controller nimmt ganz normal am Bus teil
  ^                      | Loopback          | CAN-Tx und CAN-Rx des Controllers werden innerhalb des µC verbunden. Damit lässt sich ohne weiteren Teilnehmer ein aktives Busverhalten simulieren.
  ^                      | Silent            | Der Controller nimmt nicht an der Arbitrierung Teil. Damit kann man auf einem Bus mithören ohne diesen zu beeinflussen
  ^                      | Silent & Loopback | Kombination aus den beiden
  Time Triggered Mode    | true / false      | Zeitstempel
  Auto Bus off           | true              | Der CAN Controller geht nach einem Bus-Off von allein in den aktiven Zustand
  ^                      | false             | Der CAN Controller muss per Software vom Bus-Off in den aktiven Zustand gebracht werden.
  ^                      | -                 | Der Bus-Off Zustand kann erst verlassen werden wenn 128 mal 11 rezessive Bits empfangen wurden (Siehe CAN-Error Mangement)
  Auto Wake up           | true              | Der CAN Controller wacht bei eingehenden NAchrichten von alleine auf
  ^                      | false             | Der CAN Controller muss per Software geweckt werden
  Auto Retransmission    | true / false      | Wählt aus ob die Nachrichten bei fehlgeschlagener Arbitrierung erneut gesendet werden sollen
  ^                      | @attention        | This value is inverted to the Bit 4 NART: No automatic retransmission of the bxCAN controller. The inversion is done inside the HAL Init function.
  Receive FIFO Locked    | true              | Neue Nachrichten überschreiben den vollen Rx-FIFO
  ^                      | false             | Es werden keine weiteren Nachrichten mehr angenommen, wenn der Rx-FIFO voll ist
  time based priority on transmission | true | Das Senden erfolgt in der zeitlichen Reihenfolge wie die Messages dem Tx-FIFO übergeben werden
  ^                      | false             | Das Senden unterliegt den normalen Arbitrierungsregeln, es wird also entsprechend der CAN-Id der Vorrang gegeben
  CAN Hardware filter    | [ Zahl, Integer ] | Gibt die maximale Anzahl der genutzten Hardware Filter für diesen Controller an.<br>Der bxCAN Slave hat die restlichen Filter des bxCAN Masters zur Verfügung

  ###Software Message Buffer
  Der bxCAN Controller stellt nur einen drei Nachrichten großen Receive FIFO und sowie drei Transmit Mailboxen zur Verfügung.
  Ich habe dem Modul je einen Software Buffer für Receive und Transmit spendiert. Die Größe kann hier über die Parameter eingestellt werden.
  
  @subsection de_subsecCanInterface CAN Interface

  Ich muss hier dann noch das System mit den PDUs erklären.

  @image html T01_P20_config_canif.png "Parameter on CAN Interface" width=40%

  ###RX/TX PDU Configuration
  Alle Parameter sind als Komma-Listen zu benutzten.
  Das heißt auch, dass in jeder Liste die gleiche Anzahl an Elementen vorhanden sein muss.
  Stimmt die Anzahl der Elemente eines Parameters nicht, so wird der Source Code Generator eine Fehlermeldung generieren.<br>
  In diesem Fall sind die generierten Konfigurationsdateien nutzlos.

  @todo Vielleicht kennt jemand ja einen Weg diese Konfiguration in Tabellenform ähnlich der FreeRTOS Konfiguration in der STM32CubeIDE umzusetzen.

  Ziel ist es, dass die Konfiguration hier nur für Nachrichten ohne Übertragungsprotokoll notwendig ist.
  Das CanFT2p0, sowie das IsoTp -Protokoll führen die Konfiguration schon selber durch.
  ####Kurzbeschreibung
  Die Tabelle gibt einen ersten Überblick. Die Parameter werden danach im Detail beschrieben.

  Parameter             | Wert (Aufbau)   | Beschreibung
  ---------             | -------------   | ------------
  Name L-PDU            | Name            | Name als String
  CAN Id                | S:0x123         | Standard 11bit Identifier in hexadezimal Format
  ^                     | E:0x123456      | Extended 29bit Identifier in hexadezimal Format
  CAN Id Masking        | S/E:0x0         | Aufbau genauso wie CAN Id
  HW Controller         | Master oder M   | wählt den bxCAN Master als Controller aus
  ^                     | Slave oder S    | wählt den bxCAN Slave als Controller aus
  assigned N-PDU        | Name            | gibt den Namen der Nachricht im UpperLayer (was in der Regel das Übertragungsprotokoll ist) an
  assigned upper layer  | undef           | es wurde kein spezielles UpperLayer ausgewählt. Die Message muss im CAN Interface abgeholt werden
  ^                     | CanTP           | das UpperLayer dieser Message ist das IsoTP
  ^                     | CanFT           | das UpperLayer dieser Nachricht ist das CANFT2.0 Protokoll
  ^                     | ...             | die möglichen Protokolle können erweitert werden.


  ####Name list of Interface L-PDUs
  Liste der L-PDU Namen.<br>
  Mit Hilfe der PDU-Namen wird der jeweilige "Kommunikationspfad" ausgewählt.
  So wird zum Beispiel der Funktion @c CanIf::Transmit() die @ref CanIf_TxPduIdType "TxPduId" und ein Pointer zu den zu sendenden Datenbytes übergeben.<br>
  Die Namen werden hier in der Oberfläche immer ohne irgendwelche Prefixe oder Ergänzungen genannt.
  Im Code werden die Namen dann mit dem Prefix des jeweiligen Modules sowie mit Rx-/Tx-Kennung versehen.
  Die erzeugten Namen aller Module sind dann in der EcuNames_Cfg.h zu finden.

  Wir können im Tutorial die Namen erst einmal so belassen. Ich werde bei den folgenden Punkten nur dann explizit erwähnen, das wir etwas ändern, wo es notwendig ist.

  ####List of CAN Ids / List of CAN Id Masking
  Diese zwei Parameter werden zur Konfiguration der Hardware Filter genutzt.

  Das erste Zeichen gibt an ob das Extended Id Bit (IDE) gesetzt werden soll.
  Aktuell wird nur geprüft ob das erste Zeichen ein 'E' oder ein 'e' ist.
  Ist dies nicht der Fall, dann wird von Standard CAN ausgegangen.
  Das Trennzeichen an zweiter Stelle ist egal.
  Alle Zeichen ab der dritten Stelle bis zum nächsten Komma werden unverändert in den Source Code übernommen.
  Es stehen also alle gängigen Formationen (hex, dec, oct, bin) zur Verfügung.

  CanId1, CanId2 oder auch IdMask1 und IdMask2 sind keine gültigen Zahlen.
  Demnach müssen wir hier im Tutorial gültige CAN-Ids eingeben

  ####List of message length
  Anzahl der Datenbytes

  ####List of CAN HW Controller
  Der verwendete CAN Controller per Name.
  Aktuell werden die Namen des bxCan Modules unterstützt.
  Also können Master oder Slave benannt werden.
  Alternativ kann mit dem ersten Buchstaben, also 'M' oder 'S' abgekürzt werden.<br>
  Die FDCAN Controller der neueren STM32 werden durchnummeriert. Ich werde aber auch Master als CAN1 und Slave als CAN2 akzeptieren.

  Wir nutzen im Tutorial nur den Master des bxCAN. Also müssen wir aus dem Slave auch einen Master (oder Kurzform "M") machen.

  ####List of assigned N-PDU
  Hier wird der Name des übergelagerten PDU benannt.
  Diese Namen sollten durch die Konfiguration des jeweiligen Protokollmodules entstehen

  Im Tutorial nutzen wir keine höheren Layer. Da diese Namen trotzdem vom Compiler gesucht werden, müssen diese Dummynamen bleiben.

  ####List the assigned upper layer
  Verwendetes Transport Layer (siehe auch @ref CanIf_UpperLayerType).
  Das CanIf muss wissen an welches Protokollmodul eine empfangene Nachricht weiter gereicht werden muss, bzw wohin ein erfolgreiches Versenden zurück gemeldet werden muss.<br>
  AUTOSAR nutzt hierzu die Kombination aus "übergeordneten Layer" und "PDU-Id". Mit C++ läst sich das auch einfach in Funktionspointeraufrufen realisieren.
  Es wird also die Zukunft zeigen, wie weit wir das hier nutzen.

  Damit das CanIf nicht versucht das IsoTP-Protokoll anzusprechen, müssen wir das @c CanTP zweimal zu @c undef ändern.

  Nach der Änderung der Parameter sollte die Konfiguration so aussehen
  @image html T01_P21_change_parameter.png "Change parameter CAN Interface" width=40%

  ########
  @section secFirstCodeGen Den Code für das CanIf Modul generieren

  Jetzt noch das Modul für die DemoApplication aktivieren und wir können den Code Generator starten.
  @image{inline} html T01_P22_file_generation.png "Start Code Generator" width=30%

  Wenn man jetzt im Projekt Browser mal in die vielen neuen Verzeichnisse hinein schaut, wird man neue Dateien entdecken.
  @image html T01_P23_file_generation_done.png "All generated files" width=80%

  Alles was sich im Verzeichnis mit dem Application Namen befindet, sind generierte Dateien.
  Im Unterverzeichnis "Target" werden die eigentlichen Konfigurationen erzeugt.
  Das Verzeichnis "App" beinhaltet die eigentliche Application.<br>
  Die generierten Dateien verhalten sich sich genauso wie wir es in der @c main.c kennen gelernt haben.
  Es werden also nur Änderungen innerhalb der "User Code Blöcke" über eine Code Generation hinweg beibehalten.<br>
  Schaut man zum Beispiel einmal in die EcuNames_Cfg.h so findet man ziemlich am Anfang (die Kommentare sind für die Doku geändert)

      / * USER CODE BEGIN EcuNames_Cfg__h 0 * /

      / ** @brief this enum shows the naming conventions of used PDU names * /
      typedef enum
      {
        N_PDU_Dummy_for_Test,
        L_PDU_Dummy_for_Test,
        CanUndefUl_Rx_Target1,
        CanUndefUl_Rx_Target2,
        CanUndefUl_Tx_Target1,
        CanUndefUl_Tx_Target2
      }CanUL_PDU_for_Test;

      / * USER CODE END EcuNames_Cfg__h 0 * /

   Man kann dieses enum also frei bearbeiten. Hier sind auch unsere Rx und Tx PDU Namen Target1 und Target2 als Dummy angelegt.

  Im Verzeichnis "Drivers/BSP" gibt es jetzt ein Verzeichnis "TM_Engineering_board".
  Darin sind die kopierten Dateien aus dem Board Support Package.
  Diese Dateien werden bei jeder Code Generation neu hier her kopiert. Änderungen da drin können also nur zu Versuchszwecken durch geführt werden und sind nicht angedacht.

  In der oben geöffneten @c main() kann man auch erkennen das eine @c MX_CanIf_AppDemo_Init() und eine @c MX_CanIf_AppDemo_Process() Funktion aufgerufen wird.
  Beide Funktionen sind in der @c CanIf_AppDemo.cpp implementiert.
  Wir können also abseits der eigentlichen @c main() mit C++ objektorientiert weiter arbeiten.


  @section de_HALvsPACK Das ExpansionPack übernimmt Aufgaben aus der HAL

  Also wollen wir mal ausprobieren ob sich die "CanIf_AppDemo" bauen lässt.
  @image html T01_P24_multiple_definition.png "Linker error multiple definition of `HAL_CAN_MspInit'" width=80%
  Wir erinnern uns daran, dass in der Information des ExpansionPack etwas stand, dass wir das Generieren der HAL-Funktionen deaktivieren müssen.
  Und genau das ist der Grund für diesen Linker Fehler.

  Wir müssen also noch ein mal in die Konfiguration zurück.
  @image html T01_P25_deactivate_mx_can.png "Advanced Project Settings" width=80%
  Der @c CanIf_AppDemo.ioc Viewer hat ein Tab "Project Manager".
  Hier findet man verschiedene Einstellmöglichkeiten für den Umgang mit dem STM32Cube Code Generator.
  Im Bereich "Advanced Settings" findet man die Möglichkeit die Generierung für die aktiven Module zu beeinflussen.
  So kann man unter anderem auch wählen ob man die HAL oder gar eine Low Level Ansatz für die Module nutzen möchte.

  Im Bereich "Generated Function Calls" werden alle durch den Code Generator erzeugbaren Funktionen aufgelistet.
  Das @c TM_Enineering.CAN_Stack Modul soll die Aufgaben des @c CAN1 (oder evtl auch des @c CAN2) Modules übernehmen.
  Wir müssen somit die Code Generierung sowie den Funktionsaufruf der MX_CAN1_Init() unterbinden.

  Haben wir das getan, können wir den Code Generator noch einmal starten und anschließend das Projekt erfolgreich compilieren.

  @section de_FirstDebug Es wird Zeit für die Hardware

  Wir wollen Software für einen STM32 Mikrocontroller programmieren. Also brauchen wir auch einen Controller welcher unsere Software ausführen soll.

  Wie ich zum Start des Tutorials erwähnt habe, möchte ich als Beispiel ein Nulceo-F439ZI Board, welches per Aufsteckboard mit CAN Transciever erweitert wurde, nutzen.
  @image html general_P00_nucleo_board.jpg "The NUCLEO-F439ZI with CAN" width=80%
  Die Beschreibung des Aufsteckboards soll hier nicht explizit erklärt werden. Bei Interesse kann ich das irgendwann mal ergänzen.

  Wir verbinden den auf dem NUCLEO-Board vorhandenen ST-Link mit dem PC und starten den Debug Modus über die STM32CubeIDE.
  @image html T01_P26_launch_debug.png "Debug Button"




## Diese Punkte muss ich noch ins Tutorial aufnehmen
 - ich muss noch an das blaue LED denken
 - Build führt zu Fehler  multiple definition of `HAL_CAN_MspInit'
 - Deaktivierung des Code Generators für das STM-CAN-Modul
 - Was ist mit den Interupt Callbacks



   @section de_secRestartIDE Was ist bei einem "normalen" Öffnen der IDE anders als beim ersten Start
   Die "*.ioc" wird nicht automatisch geöffnet
 * */

/* ############################################################### */
/*                       english docu                              */
/* ############################################################### */

/**  @page eng_page_T01_CanIf_AppDemo Tutorial 01: CanIf_AppDemo (english text)
 *  @tableofcontents{HTML:3}
 *
 *  coming soon (who want to do this?) It should be the same es in @ref de_page_T01_CanIf_AppDemo "German"
 *  <br>
 *  At first wyou get the sections to integrate the pack.
 *

  ########
  @section eng_secPackIntegration How to integrate the Expansion Package to STM32CubeIDE
  @subsection eng_subsecManagePack Manage Software Packs

  @image html T01_P11_manage_software_packs.png "Open manage software packs dialog" width=80%
  Inside the @c CanIf_AppDemo.ioc file view you can find at the top middle the menu "Select Packs/Manage Software Packs"

  @image html T01_P12_load_pack.png "load pack" width=80%
  You can choose to load the pack from the local disc space or via URL from a web space. In my case I have the pack saved on disc space coming with the repository.

  @image html T01_P13_accept_license.png "License agreement" width=80%
  If you have read the license info and agree to it, click on "finish".

  You can find some useful details if you click on the ExpansionPack inside the new view.
  For example there is something with the MX-functions coming from HAL code generation.

  ########
  @subsection eng_subsecSelectComp Select the components coming with the pack

  @image html T01_P14_select_component.png "load pack" width=80%
  Back on the @c CanIf_Appdemo.ioc view you can find the menu "Software Packs/Select Components".
  On this, you open the "Software Pack Component Selector". Here is a small picture on it. Don't worry about no readable, I will go to details on next.
  @image html T01_P15_pack_selector.png "Software Pack Component Selector" width=30%
  You can find all ExpansionPacks delivered from the STMicroelectronics server.
  With a click on @c Install you can download and install the ExpansionPack.
  If you scroll down you can find our ExpansionPack @c TM_Engineering.CAN_Stack.
  @image html T01_P16_select_appdemo.png "Select the Demo Application" width=80%
  With a click on the ">" it will show you the bundles and the components of the pack.
  For the first try we select the Demo Application @c CanIf_AppDemo.

  There will be some warnings signaled with the yellow triangle.
  @image html T01_P17_additional_info.png "Bundle warnings and Info" width=80%
  With a click in the @image{inline} html DetailsButton.png "(i) button" button (like the biscuit/red arrow in the picture) you can find more details to the bundle or component.
  Here is some text to explain the waring(s): "This component has unresolved dependencies". So we know there must be some more components to use this one.
  The next line says: "There are solutions within this pack". There must be an other component inside our pack. We don't need an other pack. <br>
  The @image{inline} html DependenciesButton.png "chain button" button (like green/red arrow) will show you the needed dependencies.
  So, the @c DemoApplication needs a component named @c bxCAN/Master.

  You can choose your way to select the other components.
  The "Component Dependencies" view gives you some shortcuts
  - you can manual select every with a click on the square in the "Selection" column
  - you can click on "Select" button to do the same like above
  - you can click on "Show" button to find where to select like the first point
  - you can click on "Resolve" button to do the same like the second point but includes all other dependencies

  After all you should have selected the following components and get green checkmark for solved dependencies

  Bundle | Module             | Content
  ------ | ------             | ------
  CanDrv | CanDrv_APIclass    | This module contains a virtual class Can which describes the API for all compatible CanDrv
  ^      | bxCAN / Master     | Here is the CanDrv_bxCAN for the STM bxCAN Controller. We need in the tutorial the Master controller only
  CanIf  | general            | The component includes compiler dependencies and runtime version management
  ^      | ComIf              | This component includes a virtual C++ class to abstract communication interfaces like the AUTOSAR idea.
  ^      | CanIf              | This is the derived interface class for communication on the CAN

  @image html T01_P18_select_modules.png "Select needed modules" width=80%

  Now you can close the "Software Pack Component Selector".

  ########
  @section eng_secConfigPack Module Configuration

  Back in the @c CanIf_AppDemo.ioc viewer you can find on the left column a new point named "Software Packs".
  Here will be listed all ExpansionPacks you have selected in the previous window.
  So you can see the @c TM_Engineering.CAN_Stack at this time.
  If you select it, there will be created a second column with to sections.
  On the top there is the c Mode Section. Here you can activate and deactivate the modules.
  On activation of a mode there will appear the configuration tab(s) on the lower section.

  @subsection eng_subsecCanDrvSetting CAN Driver

  The CAN Driver tab contains the configuration parameters for the access to the CAN bus.

  @image html T01_P19_config_modules.png "Config the Hardware Settings of the CanDrv module" width=80%
  If you need some more help you can select the (i) button at the upper right side in the tab. It will give you some more information about the selected parameter.

  ###Bitrate Generator
  The "Bitrate Generator" is inside the code generation ftl file.
  It will calculate the needed timing parameters like @c SeqmentTime1, @c SeqmentTime2 or @c SyncJumpWidth.
  This calcualtion based on the @c APB1 clock which drives the CAN controller.
  @remark Today there is no support on switching the clock during run time!!!

  Parameter               | Beschreibung
  ---------               | ------------
  List of Bitrates        | Give comma seperated list with bitrate values <br>This values are selectable inside the startup configuration and can be switched during runtime<br>
  Bittiming Sample Point  | Sample Point can be given as a percent value (50%-100%) or as a float value (0.5 - 1.0)

  ###bxCAN Master Setup / bxCAN Slave Setup
  This are the startup parameter for th bxCAN Master controller or the bxCAN Slve controller, if activated.

  Parameter              | Value Type        | Beschreibung
  ---------              | ----              |------------
  Initial Bitrate        | [Number, Integer] | select a value you have defined in the "Bitrate Generator"
  Controller Mode        | Normal            | Standard. The controller works as normal CAN device
  ^                      | Loopback          | This is an internal loopback of CAN-Tx und CAN-Rx lines. So it doesn't needs a second CAN device for testing.
  ^                      | Silent            | The controller don't do the arbitration.
  ^                      | Silent & Loopback | combines the two above
  Time Triggered Mode    | true / false      | Time triggered communication mode
  Auto Bus off           | true              | The Bus-Off state is left automatically by hardware once 128 occurrences of 11 recessive bits have been monitored.
  ^                      | false             | The Bus-Off state is left on software request, once 128 occurrences of 11 recessive bits have been monitored and the software has first set and cleared the INRQ bit of the CAN_MCR register.
  ^                      | -                 | For more information see the CAN-Error Management
  Auto Wake up           | true              | The Sleep mode is left automatically by hardware on CAN message detection
  ^                      | false             | The Sleep mode is left on software request by clearing the SLEEP bit of the CAN_MCR register
  Auto Retransmission    | true              | The CAN hardware will automatically retransmit the message until it has been successfully transmitted according to the CAN standard.
  ^                      | false             | A message will be transmitted only once, independently of the transmission result (successful, error or arbitration lost)
  ^                      | @attention        | This value is inverted to the Bit 4 NART: No automatic retransmission of the bxCAN controller. The inversion is done inside the HAL Init function.
  Receive FIFO Locked    | true              | Receive FIFO locked against overrun. Once a receive FIFO is full the next incoming message will be discarde
  ^                      | false             | Receive FIFO not locked on overrun. Once a receive FIFO is full the next incoming message will overwrite the previous one.
  time based priority on transmission | true | Priority driven by the request order (chronologically)
  ^                      | false             | Priority driven by the identifier of the message
  CAN Hardware filter    | [Number, Integer] | This gives the maximum count of used hardware filters for use on the bxCAN Master.<br> The bxCAN has 28 filter banks. The remaining filters will be used by the bxCAN Slave

  ###Software Message Buffer
  The bxCAN controller has only a three message sized receive FIFO and three transmit mailboxes
  So we have configurable software buffers in the CanDrv. The size of this buffers will be given with this two values

 *  */
#endif /* _DOXY_PAGE_T01_CANIF_APPDEMO_H_ */
