#include "ZdcMonDraw.h"

#include <onlmon/OnlMonClient.h>
#include <onlmon/OnlMonDB.h>

#include <TAxis.h>  // for TAxis
#include <TCanvas.h>
#include <TDatime.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <TPad.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TText.h>

#include <cstring>  // for memset
#include <ctime>
#include <fstream>
#include <iostream>  // for operator<<, basic_ostream, basic_os...
#include <sstream>
#include <vector>  // for vector

ZdcMonDraw::ZdcMonDraw(const std::string &name)
  : OnlMonDraw(name)
{
  return;
}

int ZdcMonDraw::Init()
{
  return 0;
}

int ZdcMonDraw::MakeCanvas(const std::string &name)
{
  OnlMonClient *cl = OnlMonClient::instance();
  int xsize = cl->GetDisplaySizeX();
  int ysize = cl->GetDisplaySizeY();
  if (name == "ZdcMon1")
  {
    // xpos (-1) negative: do not draw menu bar
    TC[0] = new TCanvas(name.c_str(), "ZDC-SMD Monitor", -xsize * 0.9, -ysize * 0.9, xsize * 0.9, ysize * 0.9);
    // root is pathetic, whenever a new TCanvas is created root piles up
    // 6kb worth of X11 events which need to be cleared with
    // gSystem->ProcessEvents(), otherwise your process will grow and
    // grow and grow but will not show a definitely lost memory leak
    gSystem->ProcessEvents();
    Pad[0] = new TPad("zdcpad1", "who needs this?", 0.05, 0.5, 0.5, 0.9, 0);
    Pad[1] = new TPad("zdcpad2", "who needs this?", 0.5, 0.5, 0.95, 0.9, 0);
    Pad[2] = new TPad("zdcpad3", "who needs this?", 0.05, 0.05, 0.5, 0.45, 0);
    Pad[3] = new TPad("zdcpad4", "who needs this?", 0.5, 0.05, 0.95, 0.45, 0);
    Pad[0]->Draw();
    Pad[1]->Draw();
    Pad[2]->Draw();
    Pad[3]->Draw();
    // this one is used to plot the run number on the canvas
    transparent[0] = new TPad("transparent0", "this does not show", 0, 0, 1, 1);
    transparent[0]->SetFillStyle(4000);
    transparent[0]->Draw();
    TC[0]->SetEditable(false);
  }
  else if (name == "ZdcMon2")
  {
    // xpos negative: do not draw menu bar
    TC[1] = new TCanvas(name.c_str(), "ZDC North and South Channels", -xsize * 0.9, -ysize * 0.9, xsize * 0.9, ysize * 0.9);
    gSystem->ProcessEvents();

    Pad[4] = new TPad("zdcpad5", "who needs this?", 0.05, 0.65, 0.35, 0.95, 0);
    Pad[5] = new TPad("zdcpad6", "who needs this?", 0.35, 0.65, 0.65, 0.95, 0);
    Pad[6] = new TPad("zdcpad7", "who needs this?", 0.65, 0.65, 0.95, 0.95, 0);
    Pad[7] = new TPad("zdcpad8", "who needs this?", 0.05, 0.35, 0.35, 0.65, 0);
    Pad[8] = new TPad("zdcpad9", "who needs this?", 0.35, 0.35, 0.65, 0.65, 0);
    Pad[9] = new TPad("zdcpad10", "who needs this?", 0.65, 0.35, 0.95, 0.65, 0);

    Pad[4]->Draw();
    Pad[5]->Draw();
    Pad[6]->Draw();
    Pad[7]->Draw();
    Pad[8]->Draw();
    Pad[9]->Draw();

    // this one is used to plot the run number on the canvas
    transparent[1] = new TPad("transparent1", "this does not show", 0, 0, 1, 1);
    transparent[1]->SetFillStyle(4000);
    transparent[1]->Draw();
    TC[1]->SetEditable(false);
  }
  // DRAW SMD GOOD AND SMALL VALUES
  else if (name == "SmdValues")
  {
    // xpos negative: do not draw menu bar
    TC[2] = new TCanvas(name.c_str(), "Smd Values", 0, -ysize / 2, xsize, ysize / 2);
    gSystem->ProcessEvents();
    Pad[10] = new TPad("Smd Value", "Smd Value", 0.05, 0.05, 0.35, 0.9, 0);
    Pad[11] = new TPad("Smd Value (good)", "Smd Value (good)", 0.35, 0.05, 0.65, 0.9, 0);
    Pad[12] = new TPad("Smd Value (small)", "Smd Value (small)", 0.65, 0.05, 0.95, 0.9, 0);

    Pad[10]->Draw();
    Pad[11]->Draw();
    Pad[12]->Draw();

    // this one is used to plot the run number on the canvas
    transparent[2] = new TPad("transparent1", "this does not show", 0, 0, 1, 1);
    transparent[2]->SetFillStyle(4000);
    transparent[2]->Draw();
    TC[2]->SetEditable(false);
  }

  // DRAW SMD NORTH AND SOUTH
  else if (name == "SmdNorthandSouth")
  {
    // xpos negative: do not draw menu bar
    TC[3] = new TCanvas(name.c_str(), "Smd North and South", -xsize * 0.9, -ysize * 0.9, xsize * 0.9, ysize * 0.9);
    gSystem->ProcessEvents();

    Pad[13] = new TPad("Smd Ver North (good)", "Smd Ver North (good)", 0.02, 0.05, 0.26, 0.35, 0);
    Pad[14] = new TPad("Smd Hor North (good)", "Smd Hor North (good)", 0.26, 0.05, 0.5, 0.35, 0);
    Pad[15] = new TPad("Smd Ver North (small)", "Smd Ver North (small)", 0.5, 0.05, 0.74, 0.35, 0);
    Pad[16] = new TPad("Smd Hor North (small)", "Smd Hor North (small)", 0.74, 0.05, 0.98, 0.35, 0);

    Pad[17] = new TPad("Smd Ver North", "Smd Ver North", 0.02, 0.35, 0.26, 0.65, 0);
    Pad[18] = new TPad("Smd Hor North", "Smd Hor North", 0.26, 0.35, 0.5, 0.65, 0);
    Pad[19] = new TPad("Smd Ver South", "Smd Ver South", 0.5, 0.35, 0.74, 0.65, 0);
    Pad[20] = new TPad("Smd Hor South", "Smd Hor South", 0.74, 0.35, 0.98, 0.65, 0);

    Pad[21] = new TPad("Smd sum Ver North", "Smd sum Ver North", 0.02, 0.65, 0.26, 0.95, 0);
    Pad[22] = new TPad("Smd sum Hor North", "Smd sum Hor North", 0.26, 0.65, 0.5, 0.95, 0);
    Pad[23] = new TPad("Smd sum Ver South", "Smd sum Ver South", 0.5, 0.65, 0.74, 0.95, 0);
    Pad[24] = new TPad("Smd sum Hor South", "Smd sum Hor South", 0.74, 0.65, 0.98, 0.95, 0);

    Pad[13]->Draw();
    Pad[14]->Draw();
    Pad[15]->Draw();
    Pad[16]->Draw();
    Pad[17]->Draw();
    Pad[18]->Draw();
    Pad[19]->Draw();
    Pad[20]->Draw();
    Pad[21]->Draw();
    Pad[22]->Draw();
    Pad[23]->Draw();
    Pad[24]->Draw();

    // this one is used to plot the run number on the canvas
    transparent[3] = new TPad("transparent1", "this does not show", 0, 0, 1, 1);
    transparent[3]->SetFillStyle(4000);
    transparent[3]->Draw();
    TC[3]->SetEditable(false);
  }

  else if (name == "SmdAdcNorthIndividual")
  {
    // xpos negative: do not draw menu bar
    TC[4] = new TCanvas(name.c_str(), "SMD ADC North Individual values", -xsize * 0.9, -ysize * 0.9, xsize * 0.9, ysize * 0.9);
    gSystem->ProcessEvents();
    //  North Horizontal

    // xmin, ymin, xmax, ymax
    // First Line
    Pad[21] = new TPad("smd_adc_n_hor0", "smd_adc_n_hor0", 0.02, 0.74, 0.26, 0.98, 0);
    Pad[22] = new TPad("smd_adc_n_hor1", "smd_adc_n_hor1", 0.26, 0.74, 0.50, 0.98, 0);
    Pad[23] = new TPad("smd_adc_n_hor2", "smd_adc_n_hor2", 0.50, 0.74, 0.74, 0.98, 0);
    Pad[24] = new TPad("smd_adc_n_hor3", "smd_adc_n_hor3", 0.74, 0.74, 0.98, 0.98, 0);
    // Second Line
    Pad[25] = new TPad("smd_adc_n_hor4", "smd_adc_n_hor4", 0.02, 0.50, 0.26, 0.74, 0);
    Pad[26] = new TPad("smd_adc_n_hor5", "smd_adc_n_hor5", 0.26, 0.50, 0.50, 0.74, 0);
    Pad[27] = new TPad("smd_adc_n_hor6", "smd_adc_n_hor6", 0.50, 0.50, 0.74, 0.74, 0);
    Pad[28] = new TPad("smd_adc_n_hor7", "smd_adc_n_hor7", 0.74, 0.50, 0.98, 0.74, 0);
    // Third Line
    Pad[29] = new TPad("smd_adc_n_ver8", "smd_adc_n_ver8", 0.02, 0.26, 0.26, 0.50, 0);
    Pad[30] = new TPad("smd_adc_n_ver9", "smd_adc_n_ver9", 0.26, 0.26, 0.50, 0.50, 0);
    Pad[31] = new TPad("smd_adc_n_ver10", "smd_adc_n_ver10", 0.50, 0.26, 0.74, 0.50, 0);
    Pad[32] = new TPad("smd_adc_n_ver11", "smd_adc_n_ver11", 0.74, 0.26, 0.98, 0.50, 0);
    // Fourth Line
    Pad[33] = new TPad("smd_adc_n_ver12", "smd_adc_n_ver12", 0.02, 0.02, 0.26, 0.26, 0);
    Pad[34] = new TPad("smd_adc_n_ver13", "smd_adc_n_ver13", 0.26, 0.02, 0.50, 0.26, 0);
    Pad[35] = new TPad("smd_adc_n_ver14", "smd_adc_n_ver14", 0.50, 0.02, 0.74, 0.26, 0);

    for (int i = 21; i < 36; i++)
    {
      Pad[i]->Draw();
    }

    // this one is used to plot the run number on the canvas
    transparent[4] = new TPad("transparent1", "this does not show", 0, 0, 1, 1);
    transparent[4]->SetFillStyle(4000);
    transparent[4]->Draw();
    TC[4]->SetEditable(false);
  }

  else if (name == "SmdAdcSouthIndividual")
  {
    // xpos negative: do not draw menu bar
    TC[5] = new TCanvas(name.c_str(), "SMD ADC South Individual values", -xsize * 0.9, -ysize * 0.9, xsize * 0.9, ysize * 0.9);
    gSystem->ProcessEvents();
    //  North Horizontal

    // xmin, ymin, xmax, ymax
    // First Line
    Pad[36] = new TPad("smd_adc_s_hor16", "smd_adc_s_hor16", 0.02, 0.74, 0.26, 0.98, 0);
    Pad[37] = new TPad("smd_adc_s_hor17", "smd_adc_s_hor17", 0.26, 0.74, 0.50, 0.98, 0);
    Pad[38] = new TPad("smd_adc_s_hor18", "smd_adc_s_hor18", 0.50, 0.74, 0.74, 0.98, 0);
    Pad[39] = new TPad("smd_adc_s_hor19", "smd_adc_s_hor19", 0.74, 0.74, 0.98, 0.98, 0);
    // Second Line
    Pad[40] = new TPad("smd_adc_s_hor20", "smd_adc_s_hor20", 0.02, 0.50, 0.26, 0.74, 0);
    Pad[41] = new TPad("smd_adc_s_hor21", "smd_adc_s_hor21", 0.26, 0.50, 0.50, 0.74, 0);
    Pad[42] = new TPad("smd_adc_s_hor22", "smd_adc_s_hor22", 0.50, 0.50, 0.74, 0.74, 0);
    Pad[43] = new TPad("smd_adc_s_hor23", "smd_adc_s_hor23", 0.74, 0.50, 0.98, 0.74, 0);
    // Third Line
    Pad[44] = new TPad("smd_adc_s_ver24", "smd_adc_s_ver24", 0.02, 0.26, 0.26, 0.50, 0);
    Pad[45] = new TPad("smd_adc_s_ver25", "smd_adc_s_ver25", 0.26, 0.26, 0.50, 0.50, 0);
    Pad[46] = new TPad("smd_adc_s_ver26", "smd_adc_s_ver26", 0.50, 0.26, 0.74, 0.50, 0);
    Pad[47] = new TPad("smd_adc_s_ver27", "smd_adc_s_ver27", 0.74, 0.26, 0.98, 0.50, 0);
    // Fourth Line
    Pad[48] = new TPad("smd_adc_s_ver28", "smd_adc_s_ver28", 0.02, 0.02, 0.26, 0.26, 0);
    Pad[49] = new TPad("smd_adc_s_ver29", "smd_adc_s_ver29", 0.26, 0.02, 0.50, 0.26, 0);
    Pad[50] = new TPad("smd_adc_s_ver30", "smd_adc_s_ver30", 0.50, 0.02, 0.74, 0.26, 0);

    for (int i = 36; i < 51; i++)
    {
      Pad[i]->Draw();
    }

    // this one is used to plot the run number on the canvas
    transparent[5] = new TPad("transparent1", "this does not show", 0, 0, 1, 1);
    transparent[5]->SetFillStyle(4000);
    transparent[5]->Draw();
    TC[5]->SetEditable(false);
  }

  else if (name == "SmdMultiplicities")
  {
    // xpos negative: do not draw menu bar
    TC[6] = new TCanvas(name.c_str(), "Smd Multiplicities", -xsize / 2, -ysize / 2, xsize / 2, ysize / 2);
    gSystem->ProcessEvents();
    Pad[51] = new TPad("smd_north_hor_hits", "smd_north_hor_hits", 0.05, 0.5, 0.5, 0.98, 0);
    Pad[52] = new TPad("smd_north_ver_hits", "smd_north_ver_hits", 0.5, 0.5, 0.98, 0.98, 0);
    Pad[53] = new TPad("smd_south_hor_hits", "smd_south_hor_hits", 0.05, 0.05, 0.5, 0.5, 0);
    Pad[54] = new TPad("smd_south_ver_hits", "smd_south_ver_hits", 0.5, 0.05, 0.95, 0.5, 0);

    Pad[51]->Draw();
    Pad[52]->Draw();
    Pad[53]->Draw();
    Pad[54]->Draw();

    // this one is used to plot the run number on the canvas
    transparent[6] = new TPad("transparent1", "this does not show", 0, 0, 1, 1);
    transparent[6]->SetFillStyle(4000);
    transparent[6]->Draw();
    TC[6]->SetEditable(false);
  }

  else if (name == "waveform")
  {
    // xpos (-1) negative: do not draw menu bar
    TC[7] = new TCanvas(name.c_str(), "ZDC Wave form", -xsize * 0.9, -ysize * 0.9, xsize * 0.9, ysize * 0.9);
    // root is pathetic, whenever a new TCanvas is created root piles up
    // 6kb worth of X11 events which need to be cleared with
    // gSystem->ProcessEvents(), otherwise your process will grow and
    // grow and grow but will not show a definitely lost memory leak
    gSystem->ProcessEvents();
    Pad[55] = new TPad("zdc waveform", "who needs this?", 0.05, 0.5, 0.5, 0.9, 0);
    Pad[55]->Draw();
    // this one is used to plot the run number on the canvas
    transparent[0] = new TPad("transparent0", "this does not show", 0, 0, 1, 1);
    transparent[0]->SetFillStyle(4000);
    transparent[0]->Draw();
    TC[7]->SetEditable(false);
  }

  return 0;
}

int ZdcMonDraw::Draw(const std::string &what)
{
  int iret = 0;
  int idraw = 0;
  if (what == "ALL" || what == "FIRST")
  {
    iret += DrawFirst(what);
    idraw++;
  }
  if (what == "ALL" || what == "SECOND")
  {
    iret += DrawSecond(what);
    idraw++;
  }

  if (what == "ALL" || what == "SMDVALUES")
  {
    iret += DrawSmdValues(what);
    idraw++;
  }

  if (what == "ALL" || what == "SMDN&S")
  {
    iret += DrawSmdNorthandSouth(what);
    idraw++;
  }

  if (what == "ALL" || what == "SMD_N_IND")
  {
    iret += DrawSmdAdcNorthIndividual(what);
    idraw++;
  }

  if (what == "ALL" || what == "SMD_S_IND")
  {
    iret += DrawSmdAdcSouthIndividual(what);
    idraw++;
  }

  if (what == "ALL" || what == "SMD_MULTIPLICITIES")
  {
    iret += DrawSmdMultiplicities(what);
    idraw++;
  }

  if (what == "ALL" || what == "ZDC_WAVEFORM")
  {
    iret += DrawWaveForm(what);
    idraw++;
  }

  if (!idraw)
  {
    std::cout << __PRETTY_FUNCTION__ << " Unimplemented Drawing option: " << what << std::endl;
    iret = -1;
  }
  return iret;
}

int ZdcMonDraw::DrawFirst(const std::string & /* what */)
{
  OnlMonClient *cl = OnlMonClient::instance();
  TH1 *zdc_adc_south = cl->getHisto("ZDCMON_0", "zdc_adc_south");
  TH1 *zdc_adc_north = cl->getHisto("ZDCMON_0", "zdc_adc_north");
  TH2 *smd_xy_north = (TH2 *) cl->getHisto("ZDCMON_0", "smd_xy_north");
  TH2 *smd_xy_south = (TH2 *) cl->getHisto("ZDCMON_0", "smd_xy_south");

  if (!gROOT->FindObject("ZdcMon1"))
  {
    MakeCanvas("ZdcMon1");
  }
  TC[0]->SetEditable(true);
  TC[0]->Clear("D");
  Pad[0]->cd();
  gPad->SetLogy();
//  gPad->SetLogx();
  if (zdc_adc_south)
  {
    //zdc_adc_south->Scale(1 / zdc_adc_south->Integral(), "width");
    zdc_adc_south->DrawCopy();
  }
  else
  {
    DrawDeadServer(transparent[0]);
    TC[0]->SetEditable(false);
    return -1;
  }
  Pad[1]->cd();
  gPad->SetLogy();
//  gPad->SetLogx();
  if (zdc_adc_north)
  {
    //zdc_adc_north->Scale(1 / zdc_adc_north->Integral(), "width");
    zdc_adc_north->DrawCopy();
  }

  Pad[2]->cd();
  if (smd_xy_south)
  {
    smd_xy_south->DrawCopy("colz");
  }
  Pad[3]->cd();
  if (smd_xy_north)
  {
    smd_xy_north->DrawCopy("colz");
  }

  TText PrintRun;
  PrintRun.SetTextFont(62);
  PrintRun.SetTextSize(0.04);
  PrintRun.SetNDC();          // set to normalized coordinates
  PrintRun.SetTextAlign(23);  // center/top alignment
  std::ostringstream runnostream;
  std::string runstring;
  time_t evttime = cl->EventTime("CURRENT");
  // fill run number and event time into string
  runnostream << ThisName << "_1 Run " << cl->RunNumber()
              << ", Time: " << ctime(&evttime);
  runstring = runnostream.str();
  transparent[0]->cd();
  PrintRun.DrawText(0.5, 1., runstring.c_str());
  TC[0]->Update();
  TC[0]->Show();
  TC[0]->SetEditable(false);

  return 0;
}

int ZdcMonDraw::DrawSecond(const std::string & /* what */)
{
  OnlMonClient *cl = OnlMonClient::instance();
  TH1 *zdc_S1 = cl->getHisto("ZDCMON_0", "zdc_S1");
  TH1 *zdc_S2 = cl->getHisto("ZDCMON_0", "zdc_S2");
  TH1 *zdc_S3 = cl->getHisto("ZDCMON_0", "zdc_S3");
  TH1 *zdc_N1 = cl->getHisto("ZDCMON_0", "zdc_N1");
  TH1 *zdc_N2 = cl->getHisto("ZDCMON_0", "zdc_N2");
  TH1 *zdc_N3 = cl->getHisto("ZDCMON_0", "zdc_N3");

  if (!gROOT->FindObject("ZdcMon2"))
  {
    MakeCanvas("ZdcMon2");
  }
  TC[1]->SetEditable(true);
  TC[1]->Clear("D");
  Pad[4]->cd();
  gPad->SetLogy();
  //gPad->SetLogx();
  if (zdc_S1)
  {
    //zdc_S1->Scale(1 / zdc_S1->Integral(), "width");
    zdc_S1->DrawCopy();
  }
  else
  {
    DrawDeadServer(transparent[1]);
    TC[1]->SetEditable(false);
    return -1;
  }

  Pad[5]->cd();
  gPad->SetLogy();
  //gPad->SetLogx();
  if (zdc_S2)
  {
    //zdc_S2->Scale(1 / zdc_S2->Integral(), "width");
    zdc_S2->DrawCopy();
  }
  Pad[6]->cd();
  gPad->SetLogy();
  //gPad->SetLogx();
  if (zdc_S3)
  {
    //zdc_S3->Scale(1 / zdc_S3->Integral(), "width");
    zdc_S3->DrawCopy();
  }

  Pad[7]->cd();
  gPad->SetLogy();
  //gPad->SetLogx();
  if (zdc_N1)
  {
    //zdc_N1->Scale(1 / zdc_N1->Integral(), "width");
    zdc_N1->DrawCopy();
  }

  Pad[8]->cd();
  gPad->SetLogy();
  //gPad->SetLogx();
  if (zdc_N2)
  {
    //zdc_N2->Scale(1 / zdc_N2->Integral(), "width");
    zdc_N2->DrawCopy();
  }

  Pad[9]->cd();
  gPad->SetLogy();
  //gPad->SetLogx();
  if (zdc_N3)
  {
    //zdc_N3->Scale(1 / zdc_N3->Integral(), "width");
    zdc_N3->DrawCopy();
  }
  TText PrintRun;
  PrintRun.SetTextFont(62);
  PrintRun.SetTextSize(0.04);
  PrintRun.SetNDC();          // set to normalized coordinates
  PrintRun.SetTextAlign(23);  // center/top alignment
  std::ostringstream runnostream;
  std::string runstring;
  time_t evttime = cl->EventTime("CURRENT");
  // fill run number and event time into string
  runnostream << ThisName << "_2 Run " << cl->RunNumber()
              << ", Time: " << ctime(&evttime);
  runstring = runnostream.str();
  transparent[1]->cd();
  PrintRun.DrawText(0.5, 1., runstring.c_str());
  TC[1]->Update();
  TC[1]->Show();
  TC[1]->SetEditable(false);

  return 0;
}

int ZdcMonDraw::DrawSmdValues(const std::string & /* what */)
{
  OnlMonClient *cl = OnlMonClient::instance();
  TH2 *smd_value = (TH2 *) cl->getHisto("ZDCMON_0", "smd_value");
  TH2 *smd_value_good = (TH2 *) cl->getHisto("ZDCMON_0", "smd_value_good");
  TH2 *smd_value_small = (TH2 *) cl->getHisto("ZDCMON_0", "smd_value_small");
  if (!gROOT->FindObject("SmdValues"))
  {
    MakeCanvas("SmdValues");
  }

  TC[2]->SetEditable(true);
  TC[2]->Clear("D");
  Pad[10]->cd();
  if (smd_value)
  {
    smd_value->DrawCopy();
  }
  else
  {
    DrawDeadServer(transparent[2]);
    TC[2]->SetEditable(false);
    return -1;
  }

  Pad[11]->cd();
  if (smd_value_good)
  {
    smd_value_good->DrawCopy();
  }
  Pad[12]->cd();
  if (smd_value_small)
  {
    smd_value_small->DrawCopy();
  }

  TText PrintRun;
  PrintRun.SetTextFont(62);
  PrintRun.SetTextSize(0.04);
  PrintRun.SetNDC();          // set to normalized coordinates
  PrintRun.SetTextAlign(23);  // center/top alignment
  std::ostringstream runnostream;
  std::string runstring;
  time_t evttime = cl->EventTime("CURRENT");
  // fill run number and event time into string
  runnostream << ThisName << "_3 Run " << cl->RunNumber()
              << ", Time: " << ctime(&evttime);
  runstring = runnostream.str();
  transparent[2]->cd();
  PrintRun.DrawText(0.5, 1., runstring.c_str());
  TC[2]->Update();
  TC[2]->Show();
  TC[2]->SetEditable(false);

  return 0;
}

int ZdcMonDraw::DrawSmdNorthandSouth(const std::string & /* what */)
{
  OnlMonClient *cl = OnlMonClient::instance();

  // get pointer for each histogram
  TH1 *smd_hor_south = cl->getHisto("ZDCMON_0", "smd_hor_south");
  TH1 *smd_ver_south = cl->getHisto("ZDCMON_0", "smd_ver_south");
  TH1 *smd_hor_north = cl->getHisto("ZDCMON_0", "smd_hor_north");
  TH1 *smd_ver_north = cl->getHisto("ZDCMON_0", "smd_ver_north");

  TH1 *smd_hor_north_small = cl->getHisto("ZDCMON_0", "smd_hor_north_small");
  TH1 *smd_ver_north_small = cl->getHisto("ZDCMON_0", "smd_ver_north_small");
  TH1 *smd_hor_north_good = cl->getHisto("ZDCMON_0", "smd_hor_north_good");
  TH1 *smd_ver_north_good = cl->getHisto("ZDCMON_0", "smd_ver_north_good");

  TH1 *smd_sum_hor_south = cl->getHisto("ZDCMON_0", "smd_sum_hor_south");
  TH1 *smd_sum_ver_south = cl->getHisto("ZDCMON_0", "smd_sum_ver_south");
  TH1 *smd_sum_hor_north = cl->getHisto("ZDCMON_0", "smd_sum_hor_north");
  TH1 *smd_sum_ver_north = cl->getHisto("ZDCMON_0", "smd_sum_ver_north");

  if (!gROOT->FindObject("SmdNorthandSouth"))
  {
    MakeCanvas("SmdNorthandSouth");
  }
  TC[3]->SetEditable(true);
  TC[3]->Clear("D");
  Pad[13]->cd();

  // VERTICAL AND HORIZONTAL NORTH (good and small)
  if (smd_ver_north_good)
  {
    smd_ver_north_good->DrawCopy();
  }
  else
  {
    DrawDeadServer(transparent[3]);
    TC[3]->SetEditable(false);
    return -1;
  }
  Pad[14]->cd();
  if (smd_hor_north_good)
  {
    smd_hor_north_good->DrawCopy();
  }
  Pad[15]->cd();
  if (smd_ver_north_small)
  {
    smd_ver_north_small->DrawCopy();
  }
  Pad[16]->cd();
  if (smd_hor_north_small)
  {
    smd_hor_north_small->DrawCopy();
  }

  // VERTICAL AND HORIZONTAL NORTH
  Pad[17]->cd();
  if (smd_ver_north)
  {
    smd_ver_north->DrawCopy();
  }
  Pad[18]->cd();
  if (smd_hor_north)
  {
    smd_hor_north->DrawCopy();
  }

  // VERTICAL AND HORIZONTAL SOUTH (good and small do not exist for south)
  Pad[19]->cd();
  if (smd_ver_south)
  {
    smd_ver_south->DrawCopy();
  }
  Pad[20]->cd();
  if (smd_hor_south)
  {
    smd_hor_south->DrawCopy();
  }

  // SUMS
  Pad[21]->cd();
  if (smd_sum_ver_north)
  {
    smd_sum_ver_north->DrawCopy();
  }
  Pad[22]->cd();
  if (smd_sum_hor_north)
  {
    smd_sum_hor_north->DrawCopy();
  }
  Pad[23]->cd();
  if (smd_sum_ver_south)
  {
    smd_sum_ver_south->DrawCopy();
  }
  Pad[24]->cd();
  if (smd_sum_hor_north)
  {
    smd_sum_hor_south->DrawCopy();
  }

  TText PrintRun;
  PrintRun.SetTextFont(62);
  PrintRun.SetTextSize(0.04);
  PrintRun.SetNDC();          // set to normalized coordinates
  PrintRun.SetTextAlign(23);  // center/top alignment
  std::ostringstream runnostream;
  std::string runstring;
  time_t evttime = cl->EventTime("CURRENT");
  // fill run number and event time into string
  runnostream << ThisName << "_4 Run " << cl->RunNumber()
              << ", Time: " << ctime(&evttime);
  runstring = runnostream.str();
  transparent[3]->cd();
  PrintRun.DrawText(0.5, 1., runstring.c_str());
  TC[3]->Update();
  TC[3]->Show();
  TC[3]->SetEditable(false);
  return 0;
}

int ZdcMonDraw::DrawSmdAdcNorthIndividual(const std::string & /* what */)
{
  OnlMonClient *cl = OnlMonClient::instance();

  // Array that holds pointer to the histogram of each channel
  TH1 *smd_adc_n_hor_ind[8];
  TH1 *smd_adc_n_ver_ind[7];
  // Horizontal
  for (int i = 0; i < 8; ++i)
  {
    smd_adc_n_hor_ind[i] = (TH1 *) cl->getHisto("ZDCMON_0", Form("smd_adc_n_hor_ind%d", i));  // Retrieve histogram pointer using 'histName'
  }
  // Vertical
  for (int i = 0; i < 7; ++i)
  {
    smd_adc_n_ver_ind[i] = (TH1 *) cl->getHisto("ZDCMON_0", Form("smd_adc_n_ver_ind%d", i));  // Retrieve histogram pointer using 'histName'
  }

  if (!gROOT->FindObject("SmdAdcNorthIndividual"))
  {
    MakeCanvas("SmdAdcNorthIndividual");
  }

  TC[4]->SetEditable(true);
  TC[4]->Clear("D");
  Pad[21]->cd();
  gPad->SetLogy(1); // log scale for the y-axis

  if (smd_adc_n_hor_ind[0])
  {
    smd_adc_n_hor_ind[0]->DrawCopy();
  }
  else
  {
    DrawDeadServer(transparent[4]);
    TC[4]->SetEditable(false);
    return -1;
  }

  for (int i = 1; i < 8; ++i)
  {
    Pad[21 + i]->cd();
    gPad->SetLogy(1); // log scale for the y-axis
    if (smd_adc_n_hor_ind[i])
    {
      smd_adc_n_hor_ind[i]->DrawCopy();
    }
  }

  for (int i = 0; i < 7; ++i)
  {
    Pad[29 + i]->cd();
    gPad->SetLogy(1); // log scale for the y-axis
    if (smd_adc_n_ver_ind[i])
    {
      smd_adc_n_ver_ind[i]->DrawCopy();
    }
  }

  TText PrintRun;
  PrintRun.SetTextFont(62);
  PrintRun.SetTextSize(0.04);
  PrintRun.SetNDC();          // set to normalized coordinates
  PrintRun.SetTextAlign(23);  // center/top alignment
  std::ostringstream runnostream;
  std::string runstring;
  time_t evttime = cl->EventTime("CURRENT");
  // fill run number and event time into string
  runnostream << ThisName << "_5 Run " << cl->RunNumber()
              << ", Time: " << ctime(&evttime);
  runstring = runnostream.str();
  transparent[4]->cd();
  PrintRun.DrawText(0.5, 1., runstring.c_str());
  TC[4]->Update();
  TC[4]->Show();
  TC[4]->SetEditable(false);
  return 0;
}

int ZdcMonDraw::DrawSmdAdcSouthIndividual(const std::string & /* what */)
{
  OnlMonClient *cl = OnlMonClient::instance();

  // Array that holds pointer to the histogram of each channel
  TH1 *smd_adc_s_hor_ind[8];
  TH1 *smd_adc_s_ver_ind[7];
  // Horizontal
  for (int i = 0; i < 8; ++i)
  {
    smd_adc_s_hor_ind[i] = (TH1 *) cl->getHisto("ZDCMON_0", Form("smd_adc_s_hor_ind%d", i));  // Retrieve histogram pointer using 'histName'
  }
  // Vertical
  for (int i = 0; i < 7; ++i)
  {
    smd_adc_s_ver_ind[i] = (TH1 *) cl->getHisto("ZDCMON_0", Form("smd_adc_s_ver_ind%d", i));  // Retrieve histogram pointer using 'histName'
  }

  if (!gROOT->FindObject("SmdAdcSouthIndividual"))
  {
    MakeCanvas("SmdAdcSouthIndividual");
  }

  TC[5]->SetEditable(true);
  TC[5]->Clear("D");
  Pad[36]->cd();
  gPad->SetLogy(1); // log scale for the y-axis

  if (smd_adc_s_hor_ind[0])
  {
    smd_adc_s_hor_ind[0]->DrawCopy();
  }
  else
  {
    DrawDeadServer(transparent[5]);
    TC[5]->SetEditable(false);
    return -1;
  }

  for (int i = 1; i < 8; ++i)
  {
    Pad[36 + i]->cd();
    gPad->SetLogy(1); // log scale for the y-axis
    if (smd_adc_s_hor_ind[i])
    {
      smd_adc_s_hor_ind[i]->DrawCopy();
    }
  }

  for (int i = 0; i < 7; ++i)
  {
    Pad[44 + i]->cd();
    gPad->SetLogy(1); // log scale for the y-axis
    if (smd_adc_s_ver_ind[i])
    {
      smd_adc_s_ver_ind[i]->DrawCopy();
    }
  }

  TText PrintRun;
  PrintRun.SetTextFont(62);
  PrintRun.SetTextSize(0.04);
  PrintRun.SetNDC();          // set to normalized coordinates
  PrintRun.SetTextAlign(23);  // center/top alignment
  std::ostringstream runnostream;
  std::string runstring;
  time_t evttime = cl->EventTime("CURRENT");
  // fill run number and event time into string
  runnostream << ThisName << "_6 Run " << cl->RunNumber()
              << ", Time: " << ctime(&evttime);
  runstring = runnostream.str();
  transparent[5]->cd();
  PrintRun.DrawText(0.5, 1., runstring.c_str());
  TC[5]->Update();
  TC[5]->Show();
  TC[5]->SetEditable(false);
  return 0;
}

int ZdcMonDraw::DrawSmdMultiplicities(const std::string & /* what */)
{
  OnlMonClient *cl = OnlMonClient::instance();
  TH1 *smd_north_hor_hits = (TH1 *) cl->getHisto("ZDCMON_0", "smd_north_hor_hits");
  TH1 *smd_north_ver_hits = (TH1 *) cl->getHisto("ZDCMON_0", "smd_north_ver_hits");
  TH1 *smd_south_hor_hits = (TH1 *) cl->getHisto("ZDCMON_0", "smd_south_hor_hits");
  TH1 *smd_south_ver_hits = (TH1 *) cl->getHisto("ZDCMON_0", "smd_south_ver_hits");

  if (!gROOT->FindObject("SmdMultiplicities"))
  {
    MakeCanvas("SmdMultiplicities");
  }

  TC[6]->SetEditable(true);
  TC[6]->Clear("D");
  Pad[51]->cd();
  if (smd_north_hor_hits)
  {
    smd_north_hor_hits->DrawCopy();
  }
  else
  {
    DrawDeadServer(transparent[6]);
    TC[6]->SetEditable(false);
    return -1;
  }

  Pad[52]->cd();
  if (smd_north_ver_hits)
  {
    smd_north_ver_hits->DrawCopy();
  }
  Pad[53]->cd();
  if (smd_south_hor_hits)
  {
    smd_south_hor_hits->DrawCopy();
  }
  Pad[54]->cd();
  if (smd_south_ver_hits)
  {
    smd_south_ver_hits->DrawCopy();
  }

  TText PrintRun;
  PrintRun.SetTextFont(62);
  PrintRun.SetTextSize(0.04);
  PrintRun.SetNDC();          // set to normalized coordinates
  PrintRun.SetTextAlign(23);  // center/top alignment
  std::ostringstream runnostream;
  std::string runstring;
  time_t evttime = cl->EventTime("CURRENT");
  // fill run number and event time into string
  runnostream << ThisName << "_7 Run " << cl->RunNumber()
              << ", Time: " << ctime(&evttime);
  runstring = runnostream.str();
  transparent[6]->cd();
  PrintRun.DrawText(0.5, 1., runstring.c_str());
  TC[6]->Update();
  TC[6]->Show();
  TC[6]->SetEditable(false);

  return 0;
}

int ZdcMonDraw::DrawWaveForm(const std::string & /* what */)
{
  OnlMonClient *cl = OnlMonClient::instance();
  TH2 *h_waveform = (TH2 *) cl->getHisto("ZDCMON_0", "h_waveform");

  if (!gROOT->FindObject("waveform"))
  {
    MakeCanvas("waveform");
  }
  TC[7]->SetEditable(true);
  TC[7]->Clear("D");
  if (!h_waveform)
  {
    DrawDeadServer(transparent[0]);
    TC[7]->SetEditable(false);
    return -1;
  }
  Pad[55]->cd();
  gPad->SetLogz();
  h_waveform->SetXTitle("Sample Number");
  h_waveform->SetYTitle("Amplitude");
  h_waveform->DrawCopy("colz");

  TText PrintRun;
  PrintRun.SetTextFont(62);
  PrintRun.SetTextSize(0.04);
  PrintRun.SetNDC();          // set to normalized coordinates
  PrintRun.SetTextAlign(23);  // center/top alignment
  std::ostringstream runnostream;
  std::string runstring;
  time_t evttime = cl->EventTime("CURRENT");
  // fill run number and event time into string
  runnostream << ThisName << "_1 Run " << cl->RunNumber()
              << ", Time: " << ctime(&evttime);
  runstring = runnostream.str();
  transparent[0]->cd();
  PrintRun.DrawText(0.5, 1., runstring.c_str());
  TC[7]->Update();
  TC[7]->Show();
  TC[7]->SetEditable(false);

  return 0;
}

int ZdcMonDraw::SavePlot(const std::string &what, const std::string &type)
{
  OnlMonClient *cl = OnlMonClient::instance();
  int iret = Draw(what);
  if (iret)  // on error no png files please
  {
    return iret;
  }
  int icnt = 0;
  for (TCanvas *canvas : TC)
  {
    if (canvas == nullptr)
    {
      continue;
    }
    icnt++;
    std::string filename = ThisName + "_" + std::to_string(icnt) + "_" +
                           std::to_string(cl->RunNumber()) + "." + type;
    cl->CanvasToPng(canvas, filename);
  }
  return 0;
}

int ZdcMonDraw::MakeHtml(const std::string &what)
{
  int iret = Draw(what);
  if (iret)  // on error no html output please
  {
    return iret;
  }

  OnlMonClient *cl = OnlMonClient::instance();

  // Register the 1st canvas png file to the menu and produces the png file.
  std::string pngfile = cl->htmlRegisterPage(*this, TC[0]->GetTitle(), "1", "png");
  cl->CanvasToPng(TC[0], pngfile);

  // idem for 2nd canvas.
  pngfile = cl->htmlRegisterPage(*this, TC[1]->GetTitle(), "2", "png");
  cl->CanvasToPng(TC[1], pngfile);

  //SMD North and South vertical/horizontal ADC sums
  pngfile = cl->htmlRegisterPage(*this, TC[3]->GetTitle(), "3", "png");
  cl->CanvasToPng(TC[3], pngfile);

  //SMD hit multiplicities
  pngfile = cl->htmlRegisterPage(*this, TC[6]->GetTitle(), "4", "png");
  cl->CanvasToPng(TC[6], pngfile);

  // Now register also EXPERTS html pages, under the EXPERTS subfolder.

  //SMD North ADC Individual channels
  pngfile = cl->htmlRegisterPage(*this, Form("EXPERTS/%s", TC[2]->GetTitle()), "5", "png");
  cl->CanvasToPng(TC[2], pngfile);

  //SMD South ADC Individual channels
  pngfile = cl->htmlRegisterPage(*this, Form("EXPERTS/%s", TC[4]->GetTitle()), "6", "png");
  cl->CanvasToPng(TC[4], pngfile);

  //2d hist of SMD ADC vs. channel number
  pngfile = cl->htmlRegisterPage(*this, Form("EXPERTS/%s", TC[5]->GetTitle()), "7", "png");
  cl->CanvasToPng(TC[5], pngfile);

  /*
  std::string logfile = cl->htmlRegisterPage(*this, "EXPERTS/Log", "log", "html");
  std::ofstream out(logfile.c_str());
  out << "<HTML><HEAD><TITLE>Log file for run " << cl->RunNumber()
      << "</TITLE></HEAD>" << std::endl;
  out << "<P>Some log file output would go here." << std::endl;
  out.close();

  std::string status = cl->htmlRegisterPage(*this, "EXPERTS/Status", "status", "html");
  std::ofstream out2(status.c_str());
  out2 << "<HTML><HEAD><TITLE>Status file for run " << cl->RunNumber()
       << "</TITLE></HEAD>" << std::endl;
  out2 << "<P>Some status output would go here." << std::endl;
  out2.close();
  cl->SaveLogFile(*this);
  */
  return 0;
}
