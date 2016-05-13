#include "gmLog.hpp"

#include "gmInterfacePreviewController.hpp"

namespace gm
{
    namespace Interface
    {
        namespace Preview
        {
            Controller* Controller::instance = nullptr;
            
            Controller::Controller()
            {
                log_trace(Log::New, this);
                
                if (instance)
                {
                    throw "instance already existing";
                }
                
                instance = this;
            }
            
            Controller::~Controller()
            {
                log_trace(Log::Del, this);
            }
        }
    }
}