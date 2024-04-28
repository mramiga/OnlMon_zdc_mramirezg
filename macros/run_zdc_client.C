#include "CommonFuncs.C"

#include <onlmon/zdc/ZdcMonDraw.h>

#include <onlmon/OnlMonClient.h>

// cppcheck-suppress unknownMacro
R__LOAD_LIBRARY(libonlzdcmon_client.so)

void zdcDrawInit(const int online = 0)
{

  OnlMonClient *cl = OnlMonClient::instance();
  // register histos we want with monitor name
  //zdc
  cl->registerHisto("zdc_adc_north","ZDCMON_0");
  cl->registerHisto("zdc_adc_south","ZDCMON_0");
  

  cl->registerHisto("smd_adc_n_hor_ind0", "ZDCMON_0");
  cl->registerHisto("zdc_S1","ZDCMON_0");
  cl->registerHisto("zdc_S2","ZDCMON_0");
  cl->registerHisto("zdc_S3","ZDCMON_0");
  cl->registerHisto("zdc_N1","ZDCMON_0");
  cl->registerHisto("zdc_N2","ZDCMON_0");
  cl->registerHisto("zdc_N3","ZDCMON_0");
  cl->registerHisto("h_waveform","ZDCMON_0");
 

 // smd
  // Individual smd_adc channel histos
  
  for(int i=0; i<8;i++)
  {
   cl->registerHisto(Form("smd_adc_n_hor_ind%d", i),"ZDCMON_0");
   cl->registerHisto(Form("smd_adc_s_hor_ind%d", i),"ZDCMON_0");
  }

  for(int i=0; i<7;i++)
  {
   cl->registerHisto(Form("smd_adc_n_ver_ind%d", i),"ZDCMON_0");
   cl->registerHisto(Form("smd_adc_s_ver_ind%d", i),"ZDCMON_0");
  }

  // SMD hit Multiplicities
  cl->registerHisto("smd_north_hor_hits", "ZDCMON_0");
  cl->registerHisto("smd_north_ver_hits", "ZDCMON_0");
  cl->registerHisto("smd_south_hor_hits", "ZDCMON_0");
  cl->registerHisto("smd_south_ver_hits", "ZDCMON_0");
  // // no threshold
  // cl->registerHisto("smd_north_hor_hits_nth", "ZDCMON_0");
  // cl->registerHisto("smd_north_ver_hits_nth", "ZDCMON_0");
  // cl->registerHisto("smd_south_hor_hits_nth", "ZDCMON_0");
  // cl->registerHisto("smd_south_ver_hits_nth", "ZDCMON_0");
  

  // north smd
  cl->registerHisto("smd_hor_north", "ZDCMON_0");
  cl->registerHisto("smd_ver_north", "ZDCMON_0");
  cl->registerHisto("smd_sum_hor_north", "ZDCMON_0");
  cl->registerHisto("smd_sum_ver_north", "ZDCMON_0");
  cl->registerHisto("smd_hor_north_small", "ZDCMON_0");
  cl->registerHisto("smd_ver_north_small", "ZDCMON_0");
  cl->registerHisto("smd_hor_north_good", "ZDCMON_0");
  cl->registerHisto("smd_ver_north_good", "ZDCMON_0");
  // south smd
  cl->registerHisto("smd_hor_south", "ZDCMON_0");
  cl->registerHisto("smd_ver_south", "ZDCMON_0");
  cl->registerHisto("smd_sum_hor_south", "ZDCMON_0");
  cl->registerHisto("smd_sum_ver_south", "ZDCMON_0");
  // smd values
  cl->registerHisto("smd_value", "ZDCMON_0");
  cl->registerHisto("smd_value_good", "ZDCMON_0");
  cl->registerHisto("smd_value_small", "ZDCMON_0");
  cl->registerHisto("smd_xy_north", "ZDCMON_0");
  cl->registerHisto("smd_xy_south", "ZDCMON_0");

  cl->AddServerHost("localhost");  // check local host first
  CreateHostList(online);

  // get my histos from server, the second parameter = 1 
  // says I know they are all on the same node
  cl->requestHistoBySubSystem("ZDCMON_0", 1);
  OnlMonDraw *zdcmon = new ZdcMonDraw("ZDCMONDRAW");    // create Drawing Object
  cl->registerDrawer(zdcmon);              // register with client framework
}

void zdcDraw(const char *what="ALL")
{
  OnlMonClient *cl = OnlMonClient::instance();  // get pointer to framewrk
  cl->requestHistoBySubSystem("ZDCMON_0",1);      // update histos
  cl->Draw("ZDCMONDRAW",what);                      // Draw Histos of registered Drawers
}

void zdcSavePlot()
{
    OnlMonClient *cl = OnlMonClient::instance();  // get pointer to framewrk
    cl->SavePlot("ZDCMONDRAW");                  // Save Plots
    return;
}

void zdcHtml()
{
  OnlMonClient *cl = OnlMonClient::instance();  // get pointer to framewrk
  cl->MakeHtml("ZDCMONDRAW");                       // create html output
  return;
}

