/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanFT2p0TL_Doxy.h

 * @author TManiac
 * @date Apr 3, 2022
 * @version 
 *
 */
#ifndef _CANFT2P0TL_DOXY_H_
#define _CANFT2P0TL_DOXY_H_

/*
 * das hier ist das Network Layer
 * also nutzen wir die N-PDU Namen
 *
 * --------
 * I-PDU Interaction Layer PDU for Communication Services Layer
 * L-PDU Data Link Layer PDU for Communication Abstraction and Micro controller Abstraction Layer
 * N-PDU Network Layer PDU for Transport Protocol
 *
 * PDU Protocol Data Unit
 * SDU Service Data Unit -> Payload of the PDU
 */

/***************************************/
/***********CAN FT2.0 TP module **********/

/** @defgroup CanFT2p0_group Fueltech FTCAN2.0 Protocol
 *  @brief To handle the Fueltech FTCAN2.0 protocol
 *  @details
 *  @tableofcontents
 *  @section FT_Intro   Einleitung
 *  Die Beschreibung des Protokolles steht auf der [Fueltech Homepage](https://www.fueltech.net/pages/manuals) zum Download.
 *  Diese Originalbeschreibung ist in englischer Sprache verfasst. Ich werde also hier in deutscher Sprache die wichtigsten Informationen noch einmal zusammenfassen.
 *  Bei Unklarheiten ist auf jeden Fall das von Fueltech veröffentlichte Dokument zu Rate zu ziehen. <br>
 *  Meine Informationen basieren auf der Dokumentenversion R020 vom 19.08.2020
 *
 *  Die Protokollbeschreibung ist von Fueltech offen formuliert. Aber die ECUs akzeptieren Nachrichten nur von bekannten Produkten. Damit ist die ProduktID sehr wichtig.
 *
 *  @subsection FT_phy  Physical Layer
 *  Fueltech sieht ausschließlich CAN2.0B im extended mode auf 1Mbit vor.
 *
 *  @subsection FT_identifier  Codierung der CAN ID
 *  Die CAN ID wird dazu benutzt um den Absender sowie die Übertragungsart zu codieren. Dazu wird die 29bit CAN ID wie folgt auf geteilt:
 *
 *  |  28   |  27   |  26   |  25   |  24   |  23   |  22   |  21   |  20   |  19   |  18   |  17   |  16   |  15   |  14   |  13   |  12   |  11   |  10   |   9   |   8   |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
 *  | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
 *  |  <b>0x1</b>  | <b>0xF</b>          |||| <b>0xF</b>                 |||| <b>0xF</b>                 |||| <b>0xF</b>                 |||| <b>0xF</b>                 |||| <b>0xF</b>                 |||| <b>0xF</b>                 ||||
 *  | ProductID                                                                                               ||||||||||||||| DataFieldID         ||| MessageID                             |||||||||||
 *  |  14   |  13   |  12   |  11   |  10   |   9   |   8   |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   | 0x0: Standard       ||| X     | < Response bit          ||||||||||
 *  | ProductTypeID                                                        ||||||||||  Unique Identifier                ||||| 0x2: FTCAN2.0       |||  -    |||||||||||
 *
 *  Damit ergeben sich die wichtigsten CAN IDs.
 *
 *  | Product Type | ProductTypeID | ProductID Range || CAN Base ID | Anmerk. |
 *  | ------------ | :-----------: | :----: | :-----: | ----------- | ------- |
 *  | WB O2 Nano   | 0x0240        | 0x4800 | 0x481F  | 0x14000000  |         |
 *  | SwitchPanel  | 0x0244        | 0x4880 | 0x4887  | 0x12200320  | Die verschiedene Panels werden über die UniqueID unterschieden |
 *  | FT500        | 0x0280        | 0x5000 | 0x501F  | 0x14000000  | Meine Testumgebung |
 *  | FT600        | 0x0281        | 0x5020 | 0x503F  | 0x14080000  | |
 *
 *  @subsection FT_DataField  Nutzdaten-Codierung
 *  Die Bits 11-13 der CAN ID geben an in welcher Art die Nutzdaten codiert sind.
 *
 *  | DatafieldID | Bedeutung |
 *  | :---------: | --------- |
 *  | 0x0 | Standard CAN |
 *  | 0x1 | Standard CAN über Gateway/Bridge/Converter |
 *  | 0x2 | FTCAN 2.0 |
 *  | 0x3 | FTCAN 2.0 über Gateway/Bridge/Converter |
 *  | Ob und wie die Gateway Nutzung freigestellt ist, weiß ich bisher nicht ||
 *
 *  Fueltech nutzt immer 2 Bytes, bzw 16bit zur Übertragung eines Messwertes, sowie auch für die MeassureIDs.
 *
 *  @subsubsection FT_stCAN Standard CAN Communication
 *  Ganz Kurz: so wie von Bosch geplant. 8 Datenbytes werden für Daten genutzt.<br>
 *  Die ECUs nutzen dieses System bei den RTSB (= Real Time Simple Broadcast) Daten. <br>
 *  Das SwitchPanel nutzt auch nur eine Standard CAN Communication.
 *
 *  @subsubsection FT_FT2p0  FTCAN 2.0 Communication
 *  Das Datenbyte 0 enthält einen Zähler.
 *  - Ist dieser Zähler 0xFF so handelt es sich um eine einzelne Nachricht (es kann ja auch nicht weiter gezählt werden)
 *  - Ist dieser Zähler 0x00 so wird eine segmented Übertragung begonnen. Die Datenbytes 1+2 enthalten die Anzahl der noch folgenden Nutz-Datenbytes (ohne den jeweiligen Zähler im Byte 0)
 *  - Es wird immer fortlaufend alle angereihten Nachrichten gesendet. Es erfolgt kein FlowControl.
 *
 *  @section FT_Shorty Was muss bedacht werden
 *  Das Protokoll umfasst alle Schichten oberhalb der OSI Schicht 2. Also von der Vermittlung bis zur Anwendungsschicht. Hier bedarf es evtl später einer sauberen Trennung.
 *  - die meißten Module nutzen mehr als eine CAN ID
 *  - Es gibt CAN Messages welche SingleFrame, SegmentedFrame oder SplitFrame sind
 *  - <b>SingleFrame:</b> Eine CAN Message ist eine abgeschlossene Info
 *  - <b>SegmentedFrame:</b> Es werden mehr als 8 (bzw 7) Datenbytes über die gleiche CAN ID übertragen
 *  - <b>SplitFrame:</b> Es werden angereihte CAN IDs genutzt um ein größeres Datenpacket zu übertragen (-> RTSB = Real Time Simple Broadcast)
 *
 *  @section Modules   Besonderheiten der Module
 *  @subsection SW_Panel    SwitchPanel
 *  Dieses Modul nutzt ausschließlich SingleFrame Nachrichten sowohl für den Status als auch für die Steuerung mit einer festen Codierung. Es wird keine MeassureID genutzt.<br>
 *  Es gibt keine Seriennummer oder sonstige Informationen auf dem CAN Bus
 *
 *  @subsection NANO        WideBand O2 Nano
 *  Dieses Modul nutzt das FTCAN2.0 Protokol sehr sauber.<br>
 *  Es wird eine richtig codierte SingleFrame Nachricht für die Messwertausgabe genutzt.<br>
 *  SegmentedFrame (mit abweichender CAN ID) wird für die Übergabe von Serialnummer und Messbereichseinstellung genutzt.
 *
 *  @subsection ECU         FT500 ECU (and other)
 *  Dieses Modul nutzt wohl den größten Umfang an Möglichkeiten
 *
 *  Die Daten des Real Time Simple Broadcast (RTSB) 
 *  | CAN ID (FT500) | CAN ID (FT600/550/450) | byte 1 & 2 | byte 3 & 4 | byte 5 & 6 | byte 7 & 8 |
 *  | -------------: | ---------------------: | ---------- | ---------- | ---------- | ---------- |
 *  | 0x14000600     | 0x14080600             | TPS        | MAP        | Air temp   | Engine Temp |
 *  | 0x14000601     | 0x14080601             | Oil Pressure | Fuel Pressure | Water Pressure | Gear |
 *  | 0x14000602     | 0x14080602             | Exhaust O2 | RPM | Oil Temp | Pit Limit |
 *  | 0x14000603     | 0x14080603             | Wheel Speed FR | Wheel Speed FL | Wheel Speed RR | Wheel Speed RL |
 *  | 0x14000604     | 0x14080604             | Traction Ctrl | Slip Traction Ctrl | Retard Traction Ctrl | Cut Heading |
 *  | 0x14000605     | 0x14080605             | Shock sensor FR |Shock sensor FL |Shock sensor RR | Shock sensor RL |
 *  | 0x14000606     | 0x14080606             | G-forge (accel) | G-force (lateral) | Yaw-rate (frontal) | Yaw-rate (lateral) |
 *  | 0x14000607     | 0x14080607             | Lambda Correction | Fuel Flow Tota |
 *  | 0x14000608     | 0x14080608             | Primary Injection time | Secondary Injection time | Oil Temperature | Transmisssion Temperature |
 *  */

/** @addtogroup CanFT2p0_group
 *  @{ */
/** @defgroup CanFT2p0_Cfg FT2.0 Layer Configuration containers */

/** @defgroup CanFT2p0_Spec_DataBase   Spec-Definitions
 *  @brief Database that holds the spec defined informations */

/** @defgroup CanFT2p0_Types Type definitions for FT2.0 Layer Module
 *  @brief there are no special public types then the configuration
 *         all types defined in the COM stack */

/** @defgroup CanFT2p0_Func Function definitions for CAN FT2.0 Layer Module */

/** @defgroup CanFT2p0_SchM  Scheduled Tasks */
/** @} */ // end of grouping CanFT2p0

/** @addtogroup CanFT2p0_Cfg
 *  @{ */
/** @defgroup CanFT2p0_DataBase Fueltech defined configuration */
/** @defgroup CanFT_Cfg     The Configuration from the Code Generation */
/** @} */

/** @addtogroup CanFT2p0_Types
 *  @{ */
/** @defgroup CanFT2p0_ProductTypeIDs List the known ProductTypeIDs */

/** @defgroup CanFT2p0_UniqueIDs List the defined Unique IDs used inside the protocol */

/** @defgroup CanFT2p0_DataFieldIDs List the defined DataField IDs used inside the protocol */

/** @defgroup CanFT2p0_DataIDs List the defined Data IDs used inside the protocol */
/** @} */


#endif /* _CANFT2P0TL_DOXY_H_ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
