/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * TM_Doxy.h

 * @author TManiac
 * @date 17.04.2022
 * @version 
 *
 */
#ifndef _GENERAL_TM_DOXY_H_
#define _GENERAL_TM_DOXY_H_


/** @mainpage
 *  @tableofcontents
 *  @section opener Vorwort
 *
 *  Diese Anleitung wird in deutscher Sprache verfasst. Einfach weil es für mich einfacher ist.
 *  Es werden wahrscheinlich zwischen drin ein paar englische Begriffe vorhanden sein.
 *
 *  Der Inhalt dieses STM32Cube Expansion Packages basiert auf der Idee der [AUTOSAR](https://www.autosar.org) Struktur.
 *  Man wird ein paar Parallelen zur AUTOSAR Definition finden. Aber diese Implementation ist definitiv nicht AUTOSAR kompatibel.
 *  Die Implementation wird sogar, entgegen dem AUTOSAR Ansatz in C++ umgesetzt.
 *
 *  Das Projekt "konfigurierbarer CAN COM Stack" habe ich schon mehrmals begonnen.
 *  Und erst jetzt habe ich durch die Verwendung des Code Generators in der STM32CubeIDE ein handhabbares Mittel gefunden das Ganze nach meiner Vorstellung umzusetzen.
 *  Man wird in dem vorliegenden Code natürlich immer wieder über Stücke stolpern, welche aus den älteren Anläufen stammen.
 *  So weit ich selber darüber stolpere und es für verbesserungswürdig halte, werde ich früher oder später diese Elemente gerade ziehen.
 *  Ein Punkt ist zum Beispiel, dass ursprünglich in C begonnen und dann auf C++ umgeschwenkt wurde.
 *  <br>
 *  Gerne dürfen Mitwirkende nach der Veröffentlichung Unstimmigkeiten beseitigen.
 *
 *  @section disclaimer Lizenzierung
 *  Bei diesem STM32Cube Expansion Package handelt es sich um ein Community Projekt. 
 *  Es ist also von STMicroelectronics nicht zertifiziert. <b>Die Nutzung erfolgt auf eigene Verantwortung.</b>
 *
 *  @section content Inhalt
 *
 *  - @ref intro
 *  - @subpage history
 *  - @subpage abrev
 *  - @subpage arch
 *  - @subpage folder
 *  - @subpage api
 *  - @subpage addpack
 *  - @subpage examples
 *  - @subpage searchfor
 *
 *  @section intro Einleitung
 *  ##### ...oder was macht dieses Modul
 *
 *  Grob gesagt, wird mit diesem STM32Cube Expansion Package ein konfigurierbarer Kommunikations Stack bereit gestellt.
 *  Vorerst beschränkt sich dieser Stack auf die Kommunikation über CAN.
 *
 *  Das Expansion Package stellt alle Module bereit, welche zur Kommunikation mit höheren Protokollen notwendig sind.
 *  Die möglichen Protokolle werden mit der Zeit erweitert. Anfangs stehen das IsoTP sowie das FT2.0 Protokoll zur Verfügung.
 *
 *  Das Expansion Package baut auf die HAL von ST Microelectronics auf und kann über die STM32CubeIDE, bzw die STM32CubeMX vollständig konfiguriert werden.
 *  Dabei werden Teile der HAL Konfiguation innerhalb des Packages umgesetzt und erweitern somit die bisherigen Möglichkeiten der HAL.
 *
 *  Durch die Verwendung der STM32CubeIDE/STM32CubeMX in Verbindung mit der HAL lässt sich der Stack auf allen MCUs mit bxCAN Einheit nutzen.
 *  Es sei an der Stelle vermerkt, dass mir nicht möglich ist, alle erdenklich möglichen STM32 MCUs zu testen.
 *  Es darf gerne Feedback gegeben werden.
 *
 *  Das Expansion Package ist Open Source und darf gerne erweitert werden.
 *
 *  @image html overview.svg "Expansion Package overview"
 *  */



#endif /* _GENERAL_TM_DOXY_H_ */
