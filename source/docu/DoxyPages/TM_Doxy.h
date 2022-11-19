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
 * @details
 * This file is the entry of the documentation. It holds the doxygen mainpage
 */
#ifndef _GENERAL_TM_DOXY_H_
#define _GENERAL_TM_DOXY_H_


/** @mainpage
 *  @tableofcontents{HTML:3}
 *  @section preopener English Preface
 *  This documentation will be written in German language, because this is my language. The source code internal documentation will be in English language.
 *  If you want to add translation(s) feel free of it :-).
 *  I have done the translation on the important "Integration" and "Usage" section.
 *
 *  @section de_opener Vorwort
 *
 *  Diese Anleitung wird in deutscher Sprache verfasst. Allein weil es für mich einfacher ist.
 *  Außerdem findet man schon jede Menge Anleitungen, Tutorials, Demos und so weiter in Englisch.
 *  Die Source Code (interne) Docu belasse ich aber in englischer Sprache.
 *
 *  Der Inhalt dieses STM32Cube Expansion Packages basiert auf der Idee der [AUTOSAR](https://www.autosar.org) Struktur.
 *  Man wird ein paar Parallelen zur AUTOSAR Definition finden. Aber diese Implementation ist definitiv nicht AUTOSAR kompatibel.
 *  Die Implementation wird sogar, entgegen dem AUTOSAR Ansatz in C++ umgesetzt.
 *
 *  Das Projekt "konfigurierbarer CAN COM Stack" habe ich schon mehrmals begonnen.
 *  Und erst jetzt habe ich durch die Verwendung des Code Generators in der STM32CubeIDE ein handhabbares Mittel gefunden das Ganze annähernd nach meiner Vorstellung umzusetzen.
 *  Man wird in dem vorliegenden Code natürlich immer wieder über Stücke stolpern, welche aus den älteren Anläufen stammen.
 *  So weit ich selber darüber stolpere und es für verbesserungswürdig halte, werde ich früher oder später diese Elemente gerade ziehen.
 *  Ein Punkt ist zum Beispiel, dass ursprünglich in C begonnen und dann auf C++ umgeschwenkt wurde. So sind eben die meisten Enum Definitionen noch mit typedef statt mit class.
 *  <br>
 *  Gerne dürfen Mitwirkende nach der Veröffentlichung Unstimmigkeiten beseitigen.
 *
 *  @section de_disclaimer Lizenzierung
 *  Bei diesem STM32Cube Expansion Package handelt es sich um ein Community Projekt. 
 *  Es ist also von STMicroelectronics nicht zertifiziert. <b>Die Nutzung erfolgt auf eigene Verantwortung.</b>
 *
 *  @section content Inhalt
 *
 *  - @ref de_intro
 *  - @subpage history
 *  - @subpage abrev
 *  - @subpage arch
 *  - @subpage folder
 *  - @subpage api
 *  - @subpage de_addpack
 *  - @subpage examples
 *  - @subpage searchfor
 *
 *  @section de_intro Einleitung
 *  ##### ...oder was macht dieses Modul
 *
 *  Grob gesagt, wird mit diesem STM32Cube Expansion Package ein konfigurierbarer Kommunikations Stack bereit gestellt.
 *  Vorerst beschränkt sich dieser Stack auf die Kommunikation über CAN.
 *
 *  Das Expansion Package stellt alle Module bereit, welche zur Kommunikation mit höheren Protokollen notwendig sind.
 *  Die möglichen Protokolle werden mit der Zeit erweitert. Anfangs stehen das IsoTP sowie das FTCAN2.0 Protokoll (von [Fueltech](https://www.fueltech.net)) zur Verfügung.
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

/*
 * Ich versuche mich im State Maschine zeichnen per Graphviz und Doxygen :-(
 *
 *      PreInit -> HwInit -> FilterInit -> Ready -> Ready;
 *      Shutdown -> ErrorState -> ErrorState;
 *
 *\dot
 *  digraph example {
 *      node [shape = circle, width="1", margin=0]
 *      { preInit [ label="PreInit", fixedsize=true ];
 *      hwInit [ label="HwInit" ];
 *      FilterInit;
 *      Ready;
 *      {rank=same; Stopped[fixedsize=true ]; ErrorState ; Shutdown };}
 *      preInit:se -> hwInit:ne [ arrowhead="open", style="dashed", label="++Op" ];
 *      preInit:se -> ErrorState:nw [ arrowhead="open", style="dotted", label="--Op" ];
 *      hwInit:se -> FilterInit:ne [ arrowhead="open", style="dashed", label="++Op" ];
 *      FilterInit:se -> Ready:ne [ arrowhead="open", style="dashed", label="++Op" ];
 *      Ready:se -> Stopped:ne [ arrowhead="open", style="dashed", label="++Op" ];
 *      Stopped:se -> Stopped:sw [ arrowhead="open", style="dashed", label="++Op" ];
 *      Stopped:nw -> Ready:sw [ arrowhead="open", style="dotted", label="--Op" ];
 *      Shutdown:ne -> ErrorState:nw [ arrowhead="open", style="dashed", label="++Op" ];
 *      Shutdown:se -> ErrorState:sw [ arrowhead="open", style="dotted", label="--Op" ];
 *  }
 *  \enddot
 */

#endif /* _GENERAL_TM_DOXY_H_ */
