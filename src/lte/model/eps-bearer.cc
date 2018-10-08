/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Nicola Baldo <nbaldo@cttc.es>
 */


#include "eps-bearer.h"

#include <ns3/fatal-error.h>


namespace ns3 {


GbrQosInformation::GbrQosInformation ()
  : gbrDl (0),
    gbrUl (0),
    mbrDl (0),
    mbrUl (0)
{
}

AllocationRetentionPriority::AllocationRetentionPriority ()
  : priorityLevel (0),
    preemptionCapability (false),
    preemptionVulnerability (false)
{
}

EpsBearer::EpsBearer ()
  : qci (NGBR_VIDEO_TCP_DEFAULT)
{
}

EpsBearer::EpsBearer (Qci x)
  : qci (x)
{
}

EpsBearer::EpsBearer (Qci x, struct GbrQosInformation y)
  : qci (x), gbrQosInfo (y)
{
}

bool
EpsBearer::IsGbr () const
{
  // 3GPP 23.203 Section 6.1.7.2
  switch (qci)
    {
    case GBR_CONV_VOICE:
    case GBR_CONV_VIDEO:
    case GBR_GAMING:
    case GBR_NON_CONV_VIDEO:
      return true;
    case NGBR_IMS:
    case NGBR_VIDEO_TCP_OPERATOR:
    case NGBR_VOICE_VIDEO_GAMING:
    case NGBR_VIDEO_TCP_PREMIUM:
    case NGBR_VIDEO_TCP_DEFAULT:
      return false;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return false;
    }
}

uint8_t EpsBearer::GetPriority (uint8_t q) const
{
  switch (q)
    {
    case 1:
      return 2;
    case 2:
      return 4;
    case 3:
      return 3;
    case 4:
      return 5;
    case 5:
      return 1;
    case 6:
      return 6;
    case 7:
      return 7;
    case 8:
      return 8;
    case 9:
      return 9;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return 0;
    }
}

uint8_t
EpsBearer::GetPriority () const
{
  // 3GPP 23.203 Section 6.1.7.2
  switch (qci)
    {
    case GBR_CONV_VOICE:
      return 2;
    case GBR_CONV_VIDEO:
      return 4;
    case GBR_GAMING:
      return 3;
    case GBR_NON_CONV_VIDEO:
      return 5;
    case NGBR_IMS:
      return 1;
    case NGBR_VIDEO_TCP_OPERATOR:
      return 6;
    case NGBR_VOICE_VIDEO_GAMING:
      return 7;
    case NGBR_VIDEO_TCP_PREMIUM:
      return 8;
    case NGBR_VIDEO_TCP_DEFAULT:
      return 9;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return 0;
    }
}

uint16_t EpsBearer::GetPacketDelayBudgetMs (uint8_t q) const
{
  // 3GPP 23.203 Section 6.1.7.2
  switch (q)
    {
    case 2:
      return 100;
    case 4:
      return 150;
    case 3:
      return 10;
    case 5:
      return 300;
    case 1:
      return 100;
    case 6:
      return 300;
    case 7:
      return 100;
    case 8:
      return 300;
    case 9:
      return 300;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return 0;
    }
}

uint16_t
EpsBearer::GetPacketDelayBudgetMs () const
{
  // 3GPP 23.203 Section 6.1.7.2
  switch (qci)
    {
    case GBR_CONV_VOICE:
      return 100;
    case GBR_CONV_VIDEO:
      return 150;
    case GBR_GAMING:
      return 10;
    case GBR_NON_CONV_VIDEO:
      return 300;
    case NGBR_IMS:
      return 100;
    case NGBR_VIDEO_TCP_OPERATOR:
      return 300;
    case NGBR_VOICE_VIDEO_GAMING:
      return 100;
    case NGBR_VIDEO_TCP_PREMIUM:
      return 300;
    case NGBR_VIDEO_TCP_DEFAULT:
      return 300;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return 0;
    }
}

double  EpsBearer::GetPacketErrorLossRate (uint8_t q) const
{
  switch(q)
  {
    {
    case 2:
      return 1.0e-2;
    case 4:
      return 1.0e-3;
    case 3:
      return 1.0e-1;
    case 5:
      return 1.0e-6;
    case 1:
      return 1.0e-6;
    case 6:
      return 1.0e-6;
    case 7:
      return 1.0e-3;
    case 8:
      return 1.0e-6;
    case 9:
      return 1.0e-6;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return 0;
    }
  }
}

double
EpsBearer::GetPacketErrorLossRate () const
{
  // 3GPP 23.203 Section 6.1.7.2
  switch (qci)
    {
    case GBR_CONV_VOICE:
      return 1.0e-2;
    case GBR_CONV_VIDEO:
      return 1.0e-3;
    case GBR_GAMING:
      return 1.0e-1;
    case GBR_NON_CONV_VIDEO:
      return 1.0e-6;
    case NGBR_IMS:
      return 1.0e-6;
    case NGBR_VIDEO_TCP_OPERATOR:
      return 1.0e-6;
    case NGBR_VOICE_VIDEO_GAMING:
      return 1.0e-3;
    case NGBR_VIDEO_TCP_PREMIUM:
      return 1.0e-6;
    case NGBR_VIDEO_TCP_DEFAULT:
      return 1.0e-6;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return 0;
    }
}



} // namespace ns3
