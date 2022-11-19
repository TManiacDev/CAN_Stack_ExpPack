/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * FTSwitchPanel.h

 * @author TManiac
 * @date 14.08.2022
 * @version 
 *
 */
#ifndef TMANIACENGINEERING__FUELTECH_SWITCHPANEL_H_
#define TMANIACENGINEERING__FUELTECH_SWITCHPANEL_H_

#include "CanFT2p0.h"

/** @addtogroup FT_SwitchPanel
 *  @{ */

/** the class to work with the Fueltech SwitchPanels */
class FT_SwitchPanel : public CanFT2p0
{
public:
  FT_SwitchPanel();
  FT_SwitchPanel(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanInterface);
  virtual ~FT_SwitchPanel();

  Std_ReturnType Init(void);

  Std_ReturnType SendState(void);


private:
  uint8_t panelData[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  CanIf_PduInfoType myPanelPdu = { panelData, 8 };
  uint8_t panelCtrlData[8] = {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  CanIf_PduInfoType myPanelCtrlPdu = { panelCtrlData, 8 };
};
/** @} */ // end of grouping FT_SwitchPanel
#endif /* TMANIACENGINEERING__FUELTECH_SWITCHPANEL_H_ */
