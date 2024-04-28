#ifndef ZDC_ZDCMONDRAW_H
#define ZDC_ZDCMONDRAW_H

#include <onlmon/OnlMonDraw.h>

#include <string>  // for allocator, string

class OnlMonDB;
class TCanvas;
class TGraphErrors;
class TPad;
const int NUM_CANV = 2 + 1 + 1 + 1 + 1 + 1 + 1 + 1;
const int NUM_PAD = 4 + 3 + 12 + 2 + 4 + 15 + 15 + 4 + 1;

class ZdcMonDraw : public OnlMonDraw
{
 public:
  ZdcMonDraw(const std::string &name);

  ~ZdcMonDraw() override {}

  int Init() override;
  int Draw(const std::string &what = "ALL") override;
  int MakeHtml(const std::string &what = "ALL") override;
  int SavePlot(const std::string &what = "ALL", const std::string &type = "png") override;

 protected:
  int MakeCanvas(const std::string &name);
  int DrawFirst(const std::string &what = "ALL");
  int DrawSecond(const std::string &what = "ALL");
  int DrawSmdValues(const std::string &what = "ALL");
  int DrawSmdNorthandSouth(const std::string &what = "ALL");
  int DrawSmdXY(const std::string &what = "ALL");
  int DrawSmdAdcNorthIndividual(const std::string &what = "ALL");
  int DrawSmdAdcSouthIndividual(const std::string &what = "ALL");
  int DrawSmdMultiplicities(const std::string &what = "ALL");
  // int DrawWaveForm(const std::string &what = "ALL");

  TCanvas *TC[NUM_CANV] = {nullptr};
  TPad *transparent[NUM_CANV] = {nullptr};
  TPad *Pad[NUM_PAD] = {nullptr};
};

#endif /* ZDC_ZDCMONDRAW_H */
