/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Doxy_Page_SearchFor.h

 * @author TManiac
 * @date Apr 24, 2022
 * @version 
 *
 * this file/page is multilingual
 *
 * It holds some ideas and feature requests (in my head)
 */
#ifndef _DOXY_PAGE_SEARCHFOR_H_
#define _DOXY_PAGE_SEARCHFOR_H_


/** @page searchfor Hier wird Hilfe benötigt
 *  @tableofcontents
 *  Kleine Zahlen stehen für eine hohe Priorität
 *
 *  @section nextstep Next Steps / Das ist unmittelbar noch geplant
 *
 * | Prio  | Beschreibung | Description |
 * | :---: | ------------ | ----------- |
 * | immer | Doku, Doku, Doku ........ :-D | documentation is the most important thing |
 * |  0    | saubere Platzierung der Doku im Expansion Package.<br>Ich muss einen Platz für Bilder und auch diese "Pages" hier finden. | Maybe we need a better handling of this docu with pictures and so on |
 * |  1    | Konfiguration des ISO TP Modules analog zum CAN Interface | visual configuration of IsoTP inside the STM32CubeIDE or STM32CubeMX |
 * |  2    | Konfiguration des FT2.0 Modules analog zum CAN Interface (erledigt) | configuration of the FT2.0 module |
 * |  3    | Erweitern mit UDS Modul | add UDS |
 * | 10    | Beispiele anbieten für: | Examples for: |
 * | 10.1  | OBD Tester ||
 * | 10.2  | OBD Slave ||
 * | 10.3  | Fueltech to OBD ||
 * | 10.4  | Fueltech WB-O2 Nano Simalutor ||
 *
 *  @section musthave Must Have / Das wird unbedingt gebraucht
 *
 *  Prio  | Beschreibung
 *  :---: | ------------
 *   1    | Validierung der PDU Namen in der Konfiguration (das wird wohl mit den "String Listen" nicht funktionieren)
 *   2    | Der Code Generator kopiert keine Bilder und auch nicht das Doxygen Konfiguration File :-(
 *   5    | Umsetzung XCP Protokolls
 *
 *  @section nicetohave Nice To Have / Das wäre schön noch zu haben
 *
 *  Prio  | Beschreibung
 *  :---: | ------------
 *    0   | Konfiguration von "String-Listen" zu Tabellen ändern
 *    ^   | + dazu braucht es Einblick in die Entwicklung von Eclipse Erweiterungen
 *    ^   | + das FreeRTOS Module nutzt Tabellen für die Konfiguration Tasks und so
 *    ^   | + der PackCreator ist scheinbar komplett OpenSource -> vielleicht wäre das ein Ansatz (siehe STM32PackCreator.jar)
 *    1   | noch etwas
 *
 *    */



#endif /* _DOXY_PAGE_SEARCHFOR_H_ */
