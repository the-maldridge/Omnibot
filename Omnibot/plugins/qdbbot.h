#ifndef _QDBBOT_
#define _QDBBOT_

#include <vector>
#include <deque>
#include <map>
#include <sstream>

#include "OmniPluginInterface.h"
#include "Threads/OmniThreadedClass.h"
#include "Threads/OmniThread.h"
#include "Threads/OmniMutex.h"

class qdbbot:public OmniPlugin
{
	public: 
		void onMessage(ircMessage&);
		void onOmniCommConnect(OmniCommChannel*);
		bool init(PluginUtils*);
		void wrapUp();
		std::string name();

	private:

		PluginUtils* utils;
		std::map<std::string, std::string> entities;
		void initHtmlMap();

		struct bashQuote{
			std::string num;
			std::vector<std::string> lines;
		};

		typedef std::vector<char> bashBuffer; 

		bool refreshCache();
		std::string search(std::string);
		bashQuote* nextBash();
		bashQuote* bashNum(std::string);
		bashBuffer* webget(std::string);
		

		void printQuote(bashQuote*, std::string);



		OmniMutex* cacheMutex;
		std::deque<bashQuote*>* cache;

		//parsing subfucntions
		bashQuote* parseQuote(std::stringstream*);
		std::string getNum(std::string);
		std::string getInitialLine(std::string);
		std::vector<std::string> getBashNums(std::stringstream&);
		std::string trimBodyLine(std::string);
		std::string unescapehtml(std::string, int);


		static const std::string baseURL;
		static const int GLBUFFERSIZE = 600;
		static const size_t CACHE_MIN = 5;
		static const unsigned int SPAM_INTV = 500000;

		static size_t writeMemCallback(void*, size_t, size_t, void*);

		class cachebuilder: public OmniThreadedClass
		{
			public:
				cachebuilder(qdbbot*);
				void runA();
				void runB();
				void runC();
				void runD();

			private:
				qdbbot* bot;

		};

		OmniThread* cacheThread;

};

#endif
