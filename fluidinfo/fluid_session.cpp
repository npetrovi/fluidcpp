#include "fluid_session.h"
#include "fluid_session_details.h"

size_t fluidinfo::Session::HeaderFunction(void* ptr, size_t size, size_t nmemb, void* user)
{
    //std::cerr << "Header Function " << std::endl;
  //  std::cerr << "---> " << (char*)ptr ;
    if ( strstr((char*)ptr, "X-Fluiddb-Error-Class:") )
    {
		//should we throw directly?
		fluidinfo::SessionDetails *p = (fluidinfo::SessionDetails*)user;
		char *what = strchr((char*)ptr, ':')+3;
		what[strlen(what)-1] = '\0';
		what[strlen(what)-1] = '\0';
		p->setError(std::string(what));
    }
    
    else if ( strstr((char*)ptr, "401 Unauthorized") )
	{
		fluidinfo::SessionDetails *p = (fluidinfo::SessionDetails*)user;
		p->setError("Unauthorized");
	}
	
	else { }
    
    //useless if exception gets thrown
    return size * nmemb;
}
