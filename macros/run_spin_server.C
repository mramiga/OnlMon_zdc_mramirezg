#include "ServerFuncs.C"

#include <onlmon/spin/SpinMon.h>

#include <onlmon/OnlMonServer.h>

// cppcheck-suppress unknownMacro
R__LOAD_LIBRARY(libonlspinmon_server.so)
 
//void run_spin_server(const std::string &name = "SPINMON", unsigned int serverid = 0, const std::string &prdffile = "/sphenix/lustre01/sphnxpro/commissioning/GL1/junk/GL1_junk_gl1daq-00040314-0000.evt") 
void run_spin_server(const std::string &name = "SPINMON", unsigned int serverid = 0, const std::string &prdffile = "/sphenix/lustre01/sphnxpro/commissioning/GL1/junk/GL1_junk_gl1daq-00040382-0000.evt")
{
  OnlMon *m = new SpinMon(name);                     // create subsystem Monitor object
  m->SetMonitorServerId(serverid);
                                                //  m->AddTrigger("PPG(Laser)");  // high efficiency triggers selection at et pool
                                                //  m->AddTrigger("ONLMONBBCLL1"); // generic bbcll1 minbias trigger (defined in ServerFuncs.C)
  OnlMonServer *se = OnlMonServer::instance();  // get pointer to Server Framework
  se->registerMonitor(m);                       // register subsystem Monitor with Framework
  start_server(prdffile);
  return;
}
