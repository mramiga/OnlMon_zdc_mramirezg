#ifndef ZDC_ZDCMON_H
#define ZDC_ZDCMON_H

#include <onlmon/OnlMon.h>

#include <onlmon/OnlMon.h>
#include <cmath>
#include <vector>

class CaloWaveformFitting;
class TowerInfoContainer;
class Event;
class TH1;
class TH2;
class Packet;

class ZdcMon : public OnlMon
{
 public:
  ZdcMon(const std::string &name = "ZDCMON");
  virtual ~ZdcMon();

  int process_event(Event *evt);
  int Init();
  int BeginRun(const int runno);
  int Reset();


 protected:
  std::vector<float> anaWaveformFast(Packet *p, const int channel);
  CaloWaveformFitting *WaveformProcessingFast = nullptr;

  double PI = 3.14159;
  int evtcnt = 0;
  int idummy = 0;

  //zdc
  TH1 *zdc_adc_north = nullptr;
  TH1 *zdc_adc_south = nullptr;

  TH1 *zdc_N1 = nullptr;
  TH1 *zdc_N2 = nullptr;
  TH1 *zdc_N3 = nullptr;
  TH1 *zdc_S1 = nullptr;
  TH1 *zdc_S2 = nullptr;
  TH1 *zdc_S3 = nullptr;

  // //waveform
  // TH2 *h_waveform = nullptr;
  // smd
  // Individual Channels
  TH1 *smd_adc_n_hor_ind0 = nullptr;
  TH1 *smd_adc_n_hor_ind[8] = {nullptr};
  TH1 *smd_adc_s_hor_ind[8] = {nullptr};
  TH1 *smd_adc_n_ver_ind[7] = {nullptr};
  TH1 *smd_adc_s_ver_ind[7] = {nullptr};

  // SMD hit Multiplicities
  TH1 *smd_north_hor_hits = nullptr;
  TH1 *smd_north_ver_hits = nullptr;
  TH1 *smd_south_hor_hits = nullptr;
  TH1 *smd_south_ver_hits = nullptr;

  // north smd
  TH1 *smd_hor_north = nullptr;
  TH1 *smd_ver_north = nullptr;
  TH1 *smd_sum_hor_north = nullptr;
  TH1 *smd_sum_ver_north = nullptr;
  TH1 *smd_hor_north_small = nullptr;
  TH1 *smd_ver_north_small = nullptr;
  TH1 *smd_hor_north_good = nullptr;
  TH1 *smd_ver_north_good = nullptr;
  // south smd
  TH1 *smd_hor_south = nullptr;
  TH1 *smd_ver_south = nullptr;
  TH1 *smd_sum_hor_south = nullptr;
  TH1 *smd_sum_ver_south = nullptr;
  // smd values
  TH2 *smd_value = nullptr;
  TH2 *smd_value_good = nullptr;
  TH2 *smd_value_small = nullptr;
  TH2 *smd_xy_north = nullptr;
  TH2 *smd_xy_south = nullptr;

  float smd_adc[32] = {0.0f};
  float zdc_adc[16] = {0.0f};
  float smd_sum[4] = {0.0f};
  float smd_pos[4] = {0.0f};

  float gain[32] = {0.0f};
  float smd_south_rgain[16] = {0.0f};
  float smd_north_rgain[16] = {0.0f};
  float overflow0[40] = {0.0f};
  float overflow1[40] = {0.0f};

  void CompSmdAdc();
  void CompSmdPos();
  void CompSumSmd();
  void CompZdcAdc();
};

#endif /* ZDC_ZDCMON_H */
