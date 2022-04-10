#pragma once

class Media
{
	private:
		string sDevPath;
		uint16_t uRate;
		uint16_t uResWight;
		uint16_t uResHeight;
		int32_t iFd;
		bool isOpen;
	public:
		Media(string path = "/dev/video0", uint16_t rate = 30, uint16_t resWight = 1080, uint16_t resHeight = 720): 
			sDevPath(path), uRate(rate), uResWight(resWight), uResHeight(resHeight){}
		~Media(void);

		void setDevPath(string &sPath);
		string getDevPath();

		size_t readFrame(uint8_t *buf, size_t maxSize);
		void setFrameRate(uint16_t rate);
		void setFrameResolution(uint16_t resWight, uint16_t resHeight);

		void showMediaInfo();
		
		int open(void);
		int close(void);
}
