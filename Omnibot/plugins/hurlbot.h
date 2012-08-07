#include "OmniPluginInterface.h"
#include <deque>
#include <string>

class hURLbot:public OmniPlugin {
	public:
		void onMessage(ircMessage&);
		void onOmniCommConnect(OmniCommChannel*);
		bool init(PluginUtils*);
		void wrapUp();
		std::string name();

	private:
		static const unsigned int MAX_URLS = 50;
		std::deque<std::string> urls;
		PluginUtils* utils;


};
