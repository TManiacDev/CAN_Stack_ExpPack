/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * FTSwitchPanel.cpp

 * @author TManiac
 * @date 14.08.2022
 * @version 
 *
 */
#include "FTSwitchPanel.h"

FT_SwitchPanel::FT_SwitchPanel()
{
  // TODO Auto-generated constructor stub

}

FT_SwitchPanel::FT_SwitchPanel(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanInterface) : CanFT2p0{p2CanInterface}
{

}

FT_SwitchPanel::~FT_SwitchPanel() {
  // TODO Auto-generated destructor stub
}

Std_ReturnType FT_SwitchPanel::Init(void)
{
  Std_ReturnType returnValue = E_NOT_OK;
  GetHwInterface()->ConnectUpperLayerIndication((ComStack_PduType)CanIf_RxPduIdType::CanIf_Rx_SwitchPanel_Mini4_Ctrl, this);
  CanFT2p0::Init();
  returnValue = E_OK;
  return returnValue;
}

Std_ReturnType FT_SwitchPanel::SendState(void)
{
  Std_ReturnType returnValue = E_NOT_OK;


  TxIndication(CanIf_TxPduIdType::CanIf_Tx_SwitchPanel_Mini4, &myPanelPdu);
  GetHwInterface()->Receive(CanIf_RxPduIdType::CanIf_Rx_SwitchPanel_Mini4_Ctrl, &myPanelCtrlPdu);
  panelData[0] = panelCtrlData[0];
  panelData[1] = panelCtrlData[1];

  return returnValue;
}
