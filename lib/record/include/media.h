#pragma once

class Media
{
	private:
		string sDevPath;
		uint16_t uRate;
		uint32_t uResolution;
		int32_t iFd;
	public:
		Media(string path = "/dev/video0", uint16_t rate = 30, uint32_t resolution = 1080*720): 
			sDevPath(path), uRate(rate), uResolution(resolution){}
		~Media(void);

		void setDevPath(string &sPath);
		string getDevPath();

		size_t readFrame(uint8_t *buf, size_t maxSize);
		void setFrameRate(uint16_t rate);
		void setFrameResolution(uint32_t resolution);

		void showMediaInfo();
}
