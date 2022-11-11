/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Doxy_Page_AddPack.h

 * @author TManiac
 * @date Apr 24, 2022
 * @version 
 *
 */
#ifndef _DOXY_PAGE_ADDPACK_H_
#define _DOXY_PAGE_ADDPACK_H_


/** @page addpack Das Package integrieren
 *  @tableofcontents
 *
 *  @section secDownload Das STM32CubeIDE Expansion Package herunter laden
 *  Ok, noch ist alles lokal. Also kommt noch.
 *
 *
 *  @section secManagePack Wie kommt das Expansion Package in die STM32CubeIDE
 *  Na über das Menu Manage Software Package
 *  @image html pre_Manage_Software_Packs.png "Manage Software Packs"
 *  @image html pre_Load_From_Local.png "Locales Laden des Packs"
 *
 *  @image html pre_Select_Pack_File.png "Select Pack File"
 *
 *  @section secSelectComp Auswahl der Module
 *  Was ist alles auswählbar und welche Abhängigkeiten gibt es.
 *
 *  @section secConfigPack Konfiguration der Module
 *  @subsection secConfigMain Basis Parameter
 *
 *  @image html config_parameter.png "Parameter Settings"
 *
 *  ####Baudrate Parameter
 *   Durch diese Parameter werden durch den Source Code Generator die notwendigen Hardware Parameter berechnet um die jeweiligen Baudraten zu erzeugen.
 *   Neben diesen Parametern wird die Clock des CAN Modules aus den Systemparametern genutzt.
 *
 *   Aktuell existiert kein Support für System Clock Switch während der Laufzeit!!!
 *
 *  #####List of Bitrates
 *    Hier wird die Liste der gewünschten Bitraten angelegt. Die einzelnen Bitraten werden durch Kommas getrennt.
 *
 *  #####Bittiming Sample Point
 *    Sample Point als Prozent oder Kommazahl. Der Sample Point muss entweder größer 50% oder eben 0.5 < x < 1 sein
 *    @todo Ich muss das FTL anpassen Sample Point größer 100% vermeiden
 *
 *  ####Basic Parameters
 *    Wird noch nicht genutzt. Hier nur ein Paltzhalter
 *
 *  @subsection secConfigHw CAN Controller Parameter
 *
 *  @image html config_canhw.png "Parameter für bxCan Master und Slave"
 *
 *  Parameter | Beschreibung
 *  --------- | ------------
 *  Bitrate at Controller Startup |  Hier kann eine Bitrate ausgewählt werden welche zuvor im Bereich "Baudrate Parameter" definiert wurde
 *  Controller Mode               |  Dies sind identische Parameter wie bei der Konfiguration über die HAL.
 *  Time Triggered Mode           | ^
 *  Auto Bus off                  | ^
 *  Auto Wake up                  | ^
 *  Auto Retransmission           | ^
 *  Receive FIFO Locked           | ^
 *  time based priority on transmission | ^
 *
 *  @subsection secConfigCanIf Konfiguration des Interface Modules
 *
 *  @image html config_canif.png "Parameter für CAN Interface"
 *
 *  ####Parameter Settings
 *    Größe des Rx bzw des Tx Buffers
 *
 *    Im Gegensatz zu AUTOSAR habe ich die Buffer im CanIf Module umgesetzt.
 *    Das bxCan Modul hat nur drei Rx Mailboxen.
 *    Das Hardware Module entspricht der STM HAL, welche ja unverändert übernommen wird.
 *
 *  ####RX/TX PDU Configuration
 *    Alle Parameter sind als Komma-Listen zu benutzten.
 *    Das heißt auch, dass in jeder Liste die gleiche Anzahl an Elementen vorhanden sein muss.
 *    Stimmt die Anzahl der Elemente eines Parameters nicht, so wird der Source Code Generator eine Fehlermeldung im generieren.
 *
 *  #####Name list of Interface L-PDUs
 *    Liste der L-PDU Namen.
 *  #####List of CAN Ids / List of CAN Id Masking
 *    Diese zwei Parameter werden zur Konfiguration der Hardware Filter genutzt.
 *
 *    Das erste Zeichen gibt an ob das Extended Id Bit (IDE) gesetzt werden soll.
 *    Aktuell wird nur geprüft ob das erste Zeichen ein 'E' oder ein 'e' ist.
 *    Ist dies nicht der Fall, dann wird von Standard CAN ausgegangen.
 *    Das Trennzeichen an zweiter Stelle ist egal.
 *    Alle Zeichen ab der dritten Stelle bis zum nächsten Komma werden unverändert in den Source Code übernommen.
 *    Es stehen also alle gängigen Formationen (hex, dec, oct, bin) zur Verfügung.
 *
 *  #####List of message length
 *    Anzahl der Datenbytes
 *
 *  #####List of CAN HW Controller
 *    Der verwendete CAN Controller per Name.
 *    Aktuell werden die Namen des bxCan Modules unterstützt.
 *    Also können Master oder Slave benannt werden.
 *    Alternativ kann mit dem ersten Buchstaben, also 'M' oder 'S' abgekürzt werden.
 *
 *  #####List of assigned N-PDU
 *    Hier müssen zwingend die gleichen Namen wie im entsprechenden Protokoll Layer verwendet werden.
 *
 *    Aktuell habe ich noch keine Möglichkeit die Namen aus dem Protokoll Layer per Auswahl zur Verfügung zu stellen.
 *    Ich werde aber im Code Generator die Namen überprüfen.
 *
 *  #####List the assigned upper layer
 *    Verwendetes Transport Layer
 *
 *
 *
 *  @subsection secConfigIsoTP Konfiguration des ISO TP Modules
 *
 *  @image html config_isotp.png "Parameter für ISO TP"
 * */



#endif /* _DOXY_PAGE_ADDPACK_H_ */
