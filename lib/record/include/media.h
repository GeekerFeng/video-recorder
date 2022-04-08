#pragma once

class Media
{
	private:
		string sDevPath;
		uint16_t uRate;
		uint16_t uRate;
		uint32_t uResWight;
		uint32_t uResHeight;
		int32_t iFd;
	public:
		Media(string path = "/dev/video0", uint16_t rate = 30, uint32_t resWight = 1080, uint16_t resHeight = 720): 
			sDevPath(path), uRate(rate), uResolution(resolution){}
		~Media(void);

		void setDevPath(string &sPath);
		string getDevPath();

		size_t readFrame(uint8_t *buf, size_t maxSize);
		void setFrameRate(uint16_t rate);
		void setFrameResolution(uint32_t resolution);

		void showMediaInfo();
		
		int open(void);
		int close(void);
}
