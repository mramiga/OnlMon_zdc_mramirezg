#include "ServerFuncs.C"

#include <onlmon/zdc/ZdcMon.h>

#include <onlmon/OnlMonServer.h>

// cppcheck-suppress unknownMacro
R__LOAD_LIBRARY(libonlzdcmon_server.so)


void run_zdc_server(const std::string &name = "ZDCMON", unsigned int serverid = 0, const std::string &prdffile = "/sphenix/lustre01/sphnxpro/commissioning/ZDC/junk/junk_seb14-00028671-0000.prdf")
// void run_zdc_server(const std::string &name = "ZDCMON", unsigned int serverid = 0, const std::string &prdffile = "/sphenix/lustre01/sphnxpro/commissioning/GL1/cosmics/GL1_cosmics_gl1daq-00034390-0000.prdf")

{

  OnlMon *m = new ZdcMon(name);                     // create subsystem Monitor object
  m->SetMonitorServerId(serverid);
                                                //  m->AddTrigger("PPG(Laser)");  // high efficiency triggers selection at et pool
                                                //  m->AddTrigger("ONLMONBBCLL1"); // generic bbcll1 minbias trigger (defined in ServerFuncs.C)
 
  OnlMonServer *se = OnlMonServer::instance();  // get pointer to Server Framework
  se->registerMonitor(m);                       // register subsystem Monitor with Framework
  start_server(prdffile);
  return;
}
