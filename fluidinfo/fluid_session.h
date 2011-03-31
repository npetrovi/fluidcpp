#ifndef _FLUID_SESSION_
#define _FLUID_SESSION_

#include "generic_stuff.h"
#include "fluid_security.h"
//#include "fluid_session_details.h"

namespace fluidinfo{
  
  class Session {
      public :
	      /*
	    Session():CURLInitialized(false),_name(""),SSL(false),sandboxMode(false) { 
		
	    }*/
	    explicit Session(std::string name="", authentication* auth=NULL):_name(name),SSL(false),sandboxMode(false) { 
	      CURLInitialized = false; 
	      if ( auth != NULL )
		      AuthObj = *auth;
	    }
	    virtual ~Session() { 
	      if ( CURLInitialized == true && curl_box) {
		  curl_global_cleanup();
		  //memory leak
		  curl_box = NULL;
	      }
	    }
	    inline void setAuthentication(const authentication& auth) { AuthObj = auth;  } 
	    inline void setName(std::string name="") { _name = name; }
	    inline void setSSL(bool _ssl=true) { SSL = _ssl; }
	    inline void setSandbox(bool sandbox=true) { sandboxMode = sandbox; }
	    inline CURLM* curl_multi_handle() const { return curl_box; }
	    
	   inline bool Start() {
		 curl_res = curl_global_init(CURL_GLOBAL_ALL);
	       
	       if  ( curl_res ) 
		 return false;
	       
	       curl_box = curl_multi_init();
	       if (!curl_box)
		 return false; 
	       
	       return true;
	    }
	    authentication AuthObj;
	    
      protected:

	    std::string _name;
	
	    

	    bool SSL;
	    bool CURLInitialized;
	    bool sandboxMode;
	    
	    CURLM *curl_box;
	    CURLcode curl_res;
	    
	//    friend class SessionDetails;
	    
  };
  
};

#endif