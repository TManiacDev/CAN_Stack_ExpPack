/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Doxy_Page_Architecture.h

 * @author TManiac
 * @date Apr 24, 2022
 * @version 
 *
 */
#ifndef _DOXY_PAGE_ARCHITECTURE_H_
#define _DOXY_PAGE_ARCHITECTURE_H_

/** @page arch Architektur
 *
 *  @tableofcontents
 *
 *  @section secArIntro Übersicht
 *  Beschreibung des Aufbaus und des Zusammenhanges der einzelnen Module
 *
 *  @image html overview.svg "Expansion Package overview"
 *
 *  | OSI-Layer                       ||         Protokolle (Modul)         |||
 *  | :---: | ------------------------ | :--------: | :--------: | :--------: |
 *  |   7   | Anwendungsschicht        | UDS ISO14229-1 (UDS-Modul) | Legislated OBD ISO15031-5 | Fueltech FTCAN2.0 |
 *  |   6   | Datendarstellungsschicht | - | - | ^ |
 *  |   5   | Sitzungschicht           | ISO15765-3 (IsoTP-Modul)   | ISO15765-4 | ^ |
 *  |   4   | Transportschicht         | ISO15765-2 (IsoTP-Modul)   | ISO15765-4 | ^ |
 *  |   3   | Vermittlungsschicht      | ISO15765-2 (IsoTP-Modul    | ISO15765-4 | ^ |
 *  |   -                             || used Network is free / Interface Module |||
 *  |   2   | Sicherungsschicht        | CAN | (LIN) | (FleyRay) |
 *  |   1   | Bitübertragungsschicht   | CAN | (LIN) | (FlexRay) |
 *
 *  AUTOSAR beschreibt ein PDU-Router Module. Dieses Module routet unter anderem die PDUs zwischen CanTP und DCM.
 *  Da ich aktuell noch nicht so viele mögliche Module habe, verzichte ich auf diesen PDU-Router.
 *  Die Verknüpfung wird direkt in der Konfiguration des UDS Modules hergestellt.
 *
 *  @section secHALusage Verwendung der STM HAL
 *  Das Expansion Package verwendet aktuell die HAL als unmittelbare Hardware Abstraktion.
 *  Die Initialisierung des CAN HAL Modules erfolgt über das CAN Interface Module.
 *
 *  @section secCanIf CAN Interface
 *  Das Can Interface stellt die Verbindung zu den ST abhängigen Komponenten her.
 *  So wird das CAN HAL Module initialisiert, und auch die Interrupt Routinen bereitgestellt.
 *
 *  @section secTP Transport Protokolle
 *  Die implementierten Transportprotokolle sind auf gleicher Ebene angeordnet.
 *  Eine Ausnahme stellt das UDS Protokoll dar, welches auf dem IsoTP aufsetzt.
 * */




#endif /* _DOXY_PAGE_ARCHITECTURE_H_ */
