#ifndef HCAL_HCALMON_H
#define HCAL_HCALMON_H

#include <onlmon/OnlMon.h>

#include <vector>

class CaloWaveformFitting;
class TowerInfoContainer;
class Event;
class TH1;
class TProfile;
class TH2;
class Packet;
class runningMean;
class eventReceiverClient;

class HcalMon : public OnlMon
{
 public:
  HcalMon(const std::string& name);
  virtual ~HcalMon();

  int process_event(Event* evt);
  int Init();
  int BeginRun(const int runno);
  int Reset();
  std::vector<float> getSignal(Packet* p, const int channel);
  std::vector<float> anaWaveform(Packet* p, const int channel);
  void set_anaGL1(bool state)
  {
    anaGL1 = state;
    return;
  }
  void set_trig1(int val)
  {
    trig1 = val;
    return;
  }
  void set_trig2(int val)
  {
    trig2 = val;
    return;
  }

 protected:
  int evtcnt = 0;
  int idummy = 0;
  static const int Nsector = 32;
  const int Ntower = 1536;
  const int m_nChannels = 192;
  int packetlow = 8001;
  int packethigh = 8008;
  // TH1 *hcalhist1 = nullptr;
  // TH2 *hcalhist2 = nullptr;
  TH2* h2_hcal_hits = nullptr;
  TH2* h2_hcal_hits_trig1 = nullptr;
  TH2* h2_hcal_hits_trig2 = nullptr;
  TH1* h_waveform_twrAvg = nullptr;
  TH1* h_waveform_time = nullptr;
  TH1* h_waveform_pedestal = nullptr;
  TH2* h2_hcal_rm = nullptr;
  TH2* h2_hcal_mean = nullptr;
  TH2* h2_hcal_waveform = nullptr;
  TH2* h2_hcal_correlation = nullptr;
  TH2* h2_hcal_time = nullptr;
  TH1* h_sectorAvg_total = nullptr;
  TH1* h_event = nullptr;
  TH1* h_ntower = nullptr;
  TH1* h1_packet_chans = nullptr;
  TH1* h1_packet_length = nullptr;
  TH1* h1_packet_number = nullptr;
  TH1* h1_packet_event = nullptr;
  TH1* h_rm_sectorAvg[32] = {nullptr};
  TH1* h_rm_tower[24][64]{{nullptr}};
  TH1* h_hcal_trig = {nullptr};
  TH2* h_caloPack_gl1_clock_diff = {nullptr};
  TProfile* h_evtRec = {nullptr};

  eventReceiverClient* erc = {nullptr};
  bool anaGL1 = false;

  CaloWaveformFitting* WaveformProcessing = nullptr;

  std::vector<runningMean*> rm_vector_sectAvg;
  std::vector<runningMean*> rm_vector_twr;
  std::vector<runningMean*> rm_vector_twrTime;
  std::vector<runningMean*> rm_packet_number;
  std::vector<runningMean*> rm_packet_length;
  std::vector<runningMean*> rm_packet_chans;

  int trig1 = 1;
  int trig2 = 3;
};

#endif /* HCAL_HCALMON_H */
